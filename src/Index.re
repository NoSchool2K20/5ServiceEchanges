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