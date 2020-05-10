/**
 * Start listening on port 8080
 */

let () = {
  print_string("Startinq Noschool amqp message listener");
  print_newline()
};

let receiverElevPriv   = ReceiverElevPriv.connection;
let receiverNewUser    = ReceiverNewUser.connection;
let receiverViewCourse = ReceiverViewCourse.connection;

//cron JOB for weekly send csv files
open BsCron
 
// Make a job that will fire every second when started
let job =
  CronJob.make(
    `CronString("15 * * * * *"),
    _ => Js.log("Just doing my job every hour and 15 minutes every day"),
    (),
  );

// Firing every second, printing 'Just doing my job'
start(job);

//Connexion a une file poubelle
let senderDlq = MoveToDLQ.connection;

type express;
type response;
type handler = (string, response) => unit;
[@bs.send] external get : (express, string, handler) => unit = "";
[@bs.send] external send : (response, string) => unit = "";
[@bs.send] external listen : (express, int) => unit = "";
[@bs.module] external express : unit => express = "express";
let app = express();
get(app, "/", (_, res) => {
  send(res, "QSI NoSchool 2k20 DSI");
});
listen(app, 8080)

Js.log("5 Exchanges Running");