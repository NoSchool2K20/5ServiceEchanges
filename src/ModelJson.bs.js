// Generated by BUCKLESCRIPT, PLEASE EDIT WITH CARE
'use strict';

var Json_encode = require("@glennsl/bs-json/src/Json_encode.bs.js");

function formatMessage(emailReceiver, nameReceiver, subject, emailSender, nameSender, value) {
  return Json_encode.object_(/* :: */[
              /* tuple */[
                "personalizations",
                [Json_encode.object_(/* :: */[
                        /* tuple */[
                          "to",
                          [Json_encode.object_(/* :: */[
                                  /* tuple */[
                                    "email",
                                    emailReceiver
                                  ],
                                  /* :: */[
                                    /* tuple */[
                                      "name",
                                      nameReceiver
                                    ],
                                    /* [] */0
                                  ]
                                ])]
                        ],
                        /* :: */[
                          /* tuple */[
                            "subject",
                            subject
                          ],
                          /* [] */0
                        ]
                      ])]
              ],
              /* :: */[
                /* tuple */[
                  "from",
                  Json_encode.object_(/* :: */[
                        /* tuple */[
                          "email",
                          emailSender
                        ],
                        /* :: */[
                          /* tuple */[
                            "name",
                            nameSender
                          ],
                          /* [] */0
                        ]
                      ])
                ],
                /* :: */[
                  /* tuple */[
                    "content",
                    [Json_encode.object_(/* :: */[
                            /* tuple */[
                              "type",
                              "text/plain"
                            ],
                            /* :: */[
                              /* tuple */[
                                "value",
                                value
                              ],
                              /* [] */0
                            ]
                          ])]
                  ],
                  /* [] */0
                ]
              ]
            ]);
}

exports.formatMessage = formatMessage;
/* No side effect */
