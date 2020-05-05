//send email with sendgrid;

module Amqp = AmqpConnectionManager;

external jsonToObjects : Js.Json.t => Js.t({..}) = "%identity";

let sendMail= (msg: Amqp.Queue.message, channel) => {

  let message = msg.content->Node.Buffer.toString->Js.Json.parseExn;

  let headersDict =
  Js.Dict.(
    {
      let dict = empty();
      let apiKey = "jmDshemWSbqg-ErGe2PHmg.hZuFOWNAGLKfYw3xoeS9GKHdPzzWeHEZTrIY0U8L4wU";
      
      dict->set("Content-type", "application/json");
      dict->set("Authorization","Bearer SG."++apiKey)
      dict;
    }
  );
let headers = Axios.Headers.fromDict(headersDict);
  let result = Js.Promise.(
    Axios.postDatac("https://api.sendgrid.com/v3/mail/send",{jsonToObjects(message)}, Axios.makeConfig(~headers, ()))
    |> then_((response) => {
      Amqp.Channel.ack(channel, msg);
      Js.Console.info(response);
      Js.Console.info("Email envoyé");
      resolve(response##data)
    })
    |> catch((error) => {
      Amqp.Channel.nack(channel, msg);
      Js.Console.info(error);
      resolve(error)
    })
  );
  result;
}