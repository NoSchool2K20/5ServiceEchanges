// Generated by BUCKLESCRIPT, PLEASE EDIT WITH CARE
'use strict';

var Curry = require("bs-platform/lib/js/curry.js");
var AmqpConnectionManager = require("bs-amqp-connection-manager/src/AmqpConnectionManager.bs.js");
var AmqpConnectionManager$1 = require("amqp-connection-manager");

var amqp_u = "qzscetiz";

var amqp_p = "iLJmX80CVSklfcVeS1NH81AwaHLSikPh";

var amqp_host = "crow.rmq.cloudamqp.com";

var amqp_url = "amqp://qzscetiz:iLJmX80CVSklfcVeS1NH81AwaHLSikPh@crow.rmq.cloudamqp.com/qzscetiz";

var connection = AmqpConnectionManager$1.connect([amqp_url], undefined);

Curry._2(AmqpConnectionManager.AmqpConnectionManager.on, connection, /* `disconnect */[
      -381393828,
      (function (err) {
          console.error(err);
          return /* () */0;
        })
    ]);

Curry._2(AmqpConnectionManager.AmqpConnectionManager.on, connection, /* `connect */[
      360725482,
      (function (param) {
          console.info("connected!");
          return /* () */0;
        })
    ]);

var Amqp = /* alias */0;

exports.Amqp = Amqp;
exports.amqp_u = amqp_u;
exports.amqp_p = amqp_p;
exports.amqp_host = amqp_host;
exports.amqp_url = amqp_url;
exports.connection = connection;
/* connection Not a pure module */
