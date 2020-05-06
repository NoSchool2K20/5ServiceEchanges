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
//let receiverNewCourse   = ReceiverNewCourse.connection;

let onListen = e =>
  switch (e) {
  | exception (Js.Exn.Error(e)) =>
    (
      switch (Js.Exn.message(e)) {
      | None => "UNKNOWN ERROR"
      | Some(msg) => msg
      }
    )
    |> Logger.error;
    Node.Process.exit(1);
  | _ => "Listening at http://127.0.0.1:8080" |> Logger.info
  };

let server = Express.App.listen(Api.app, ~port=8080, ~onListen, ());

Js.log("Running 5 Exchanges");