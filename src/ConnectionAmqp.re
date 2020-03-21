module Amqp = AmqpConnectionManager;


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