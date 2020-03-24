//send email with sendgrid
let sendMail= (message) => {
    let defaultHeaders = [%bs.raw {|
        {
          "Content-Type": "application/json",
          "Authorization": "la superbe cle"
        }
    |}];

    let payload = Js.Dict.empty();
    Js.Dict.set(payload, "personalizations",message);
    Js.Promise.(
    Fetch.fetchWithInit(
      "https://api.sendgrid.com/v3/mail/send",
      Fetch.RequestInit.make(
        ~method_=Post,
        ~body=Fetch.BodyInit.make(Js.Json.stringify(Js.Json.object_(payload))),
        ~headers=defaultHeaders,
        ()
      )
    )
    |> then_(Fetch.Response.json)
  );
}