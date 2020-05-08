module Amqp = AmqpConnectionManager;
[@bs.val] external setTimeout: (unit => unit, int) => int = "setTimeout";
let dlq_queue_name = "DLQ";
let amqp_u = "qzscetiz"
let amqp_p = "iLJmX80CVSklfcVeS1NH81AwaHLSikPh"
let amqp_host = "crow.rmq.cloudamqp.com"
let amqp_url = "amqp://"++amqp_u++":"++amqp_p++"@"++amqp_host++"/"++amqp_u

// Create a connetion manager
let connection = Amqp.connect([|amqp_url|], ());

Amqp.AmqpConnectionManager.on(
  connection,
  `disconnect(err => Js.Console.error(err)),
)
|> ignore;

Amqp.AmqpConnectionManager.on(
  connection,
  `connect(_ => Js.Console.info("connected "++dlq_queue_name++"!")),
)
|> ignore;

// Set up a channel writing for messages to the queue.
  let dlqchannelWrapper =
  Amqp.AmqpConnectionManager.createChannel(
    connection,
    {
      "json": true,
      "setup": channel =>
        // `channel` here is a regular amqplib `ConfirmChannel`.
        Js.Promise.(
          all([|
            Amqp.Channel.assertQueue(channel, dlq_queue_name, {"durable": true})
            |> then_(_ => resolve()),
          |])
          |> then_(_ => resolve())
        ),
    },
  );

  let dlq = (msg: Amqp.Queue.message) => {
    let message = msg.content->Node.Buffer.toString->Js.Json.parseExn;
    Amqp.ChannelWrapper.sendToQueue(
      dlqchannelWrapper,
      dlq_queue_name,
      message,
      Js.Obj.empty(),
    )
    |> Js.Promise.then_(msg => {
        Js.Console.info("Message moved to DLQ");
        Js.Promise.make((~resolve, ~reject as _) =>
          setTimeout(() => resolve(. msg), 1000) |> ignore
        );
      })
  };
