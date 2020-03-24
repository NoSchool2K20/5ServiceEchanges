//send email with sendgrid
let sendMail(msg: Js.Json) => {
    let defaultHeaders = [%bs.raw {|
        {
          "Content-Type": "application/json",
          "Authorization": "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"
        }
    |}];

    let payload = Js.Dict.empty();
    Js.Dict.set(payload, Jsontosend);
    let response = Js.Promise.(
        Fetch.fetchWithInit(
            "https://api.sendgrid.com/v3/mail/send",
            Fetch.RequestInit.make(
                ~method_=Post,
                ~body=Fetch.BodyInit.make(Js.Json.stringify(Js.Json.object_(payload))),
                ~headers=headers),
            ()
        )
    )
    |> then_(Fetch.Response.json)

    Js.Console.log2("RESPONSE SENDGRID : "++ response);
}