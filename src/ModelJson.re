let createContent = (username : string, email : string, content : string, subject : string) => {
    let message =
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
                          ("email", string(email)),
                          ("name", string(username)),
                        ]),
                      |]),
                    ),
                    ("subject", string(subject)),
                  ]),
                |]),
              ),
              (
                "from",
                object_([("email", string("admin@noschool2k20.fr")), ("name", string("NoReply NoSchool 2K20"))]),
              ),
              (
                "content",
                jsonArray([|
                  object_([
                    ("type", string("text/plain")),
                    ("value", string(content)),
                  ]),
                |]),
              ),
            ])
          );
     Js.Console.info(message)
     message
 };