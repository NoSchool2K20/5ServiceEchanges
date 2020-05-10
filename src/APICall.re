//send email with sendgrid

let sendMail= (message) => {

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
  let _ = Js.Promise.(
    Axios.postDatac("https://api.sendgrid.com/v3/mail/send",{message}, Axios.makeConfig(~headers, ()))
    |> then_((response) => resolve(Js.log(response##data)))
    |> catch((error) => resolve(Js.log(error)))
  );
  ();
}


external jsonToObjects : Js.Json.t => Js.t({..}) = "%identity";