let formatMessage = (emailReceiver, nameReceiver, subject, emailSender, nameSender, value) => {
  Json.Encode.(
    object_([
      (
        "personalizations",
        jsonArray([|
          object_([
            (
              "to",
              jsonArray([|
                object_([
                  ("email", string(emailReceiver)),
                  ("name", string(nameReceiver)),
                ]),
              |]),
            ),
            ("subject", string(subject)),
          ]),
        |]),
      ),
      (
        "from",
        object_([("email", string(emailSender)), ("name", string(nameSender))]),
      ),
      (
        "content",
        jsonArray([|
          object_([
            ("type", string("text/plain")),
            ("value", string(value)),
          ]),
        |]),
      ),
    ])
  );
};