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
    //Every first day of month `CronString("0 0 0 1 * *"),
    `CronString("15 * * * * *"),
    _ => {
      Js.log("Sending Invoices from invoices.csv for current Executed Each first day of month ");
      ReadCsv.parseCsv();
    },
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