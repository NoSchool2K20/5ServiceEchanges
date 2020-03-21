module Amqp = AmqpConnectionManager;


let queue_name : Amqp.Queue.name  = "QviewCourse";
let exchange_name = "EviewCourse";

// Create a connetion manager
let connection = Amqp.connect([|"amqp://qzscetiz:iLJmX80CVSklfcVeS1NH81AwaHLSikPh@crow.rmq.cloudamqp.com/qzscetiz"|], ());


Amqp.AmqpConnectionManager.on(
  connection,
  `disconnect(err => Js.Console.error(err)),
)
|> ignore;

Amqp.AmqpConnectionManager.on(
  connection,
  `connect(_ => Js.Console.info("connected!")),
)
|> ignore;

// Handle an incomming message.
let onMessage = (channel, msg: Amqp.Queue.message) => {
    let message = msg.content->Node.Buffer.toString->Js.Json.parseExn;
    Js.Console.log2("receiver: got message", message);
    Amqp.Channel.ack(channel, msg);
  };

// Set up a channel listening for messages in the queue.
let channelWrapper =
  Amqp.AmqpConnectionManager.createChannel(
    connection,
    {
      "setup": channel =>
        // `channel` here is a regular amqplib `ConfirmChannel`.
        Js.Promise.(
          all([|
            Amqp.Channel.assertQueue(channel, queue_name, {"durable": true})
            |> then_(_ => resolve()),
            Amqp.Channel.prefetch(channel, 1),
            Amqp.Channel.consume(channel, queue_name, onMessage(channel)),
          |])
          |> then_(_ => resolve())
        ),
    },
  );

