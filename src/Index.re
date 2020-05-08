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