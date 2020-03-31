let () = {
  print_string("Startinq Noschool amqp message listener");
  print_newline()
};

let receiverElevPriv   = ReceiverElevPriv.connection;
let receiverNewUser    = ReceiverNewUser.connection;
let receiverViewCourse = ReceiverViewCourse.connection;