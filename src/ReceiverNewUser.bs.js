// Generated by BUCKLESCRIPT, PLEASE EDIT WITH CARE
'use strict';

var AmqpConnectionManager = require("bs-amqp-connection-manager/src/AmqpConnectionManager.bs.js");
var SendMailAMQP$ReasonmlDemoModules = require("./SendMailAMQP.bs.js");

var queue_name = "Qnewuser";

var amqp_u = "qzscetiz";

var amqp_p = "iLJmX80CVSklfcVeS1NH81AwaHLSikPh";

var amqp_host = "crow.rmq.cloudamqp.com";

var amqp_url = "amqp://qzscetiz:iLJmX80CVSklfcVeS1NH81AwaHLSikPh@crow.rmq.cloudamqp.com/qzscetiz";

var connection = AmqpConnectionManager.connect([amqp_url], undefined, /* () */0);

AmqpConnectionManager.AmqpConnectionManager.on(connection, /* `disconnect */[
      -381393828,
      (function (err) {
          console.error(err);
          return /* () */0;
        })
    ]);

AmqpConnectionManager.AmqpConnectionManager.on(connection, /* `connect */[
      360725482,
      (function (param) {
          console.info("connected Qnewuser!");
          return /* () */0;
        })
    ]);

function onMessage(channel, msg) {
  console.log("receiver Qnewuser: got message");
  SendMailAMQP$ReasonmlDemoModules.sendMail(msg, channel);
  JSON.parse(msg.content.toString());
  console.info("TODO: Save to csv local file");
  return /* () */0;
}

var channelWrapper = AmqpConnectionManager.AmqpConnectionManager.createChannel(connection, {
      setup: (function (channel) {
          return Promise.all([
                        AmqpConnectionManager.Channel.assertQueue(channel, queue_name, {
                                durable: true
                              }).then((function (param) {
                                return Promise.resolve(/* () */0);
                              })),
                        AmqpConnectionManager.Channel.prefetch(channel, 1),
                        AmqpConnectionManager.Channel.consume(channel, queue_name, (function (param) {
                                return onMessage(channel, param);
                              }))
                      ]).then((function (param) {
                        return Promise.resolve(/* () */0);
                      }));
        })
    });

var Amqp = /* alias */0;

exports.Amqp = Amqp;
exports.queue_name = queue_name;
exports.amqp_u = amqp_u;
exports.amqp_p = amqp_p;
exports.amqp_host = amqp_host;
exports.amqp_url = amqp_url;
exports.connection = connection;
exports.onMessage = onMessage;
exports.channelWrapper = channelWrapper;
/* connection Not a pure module */
