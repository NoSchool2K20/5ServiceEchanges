module Results = {
 [@bs.deriving abstract] type t = {
      data: array(array(string))
  };
};


[@bs.val] [@bs.module "papaparse"] external parse :
  (string) => Results.t = "parse";

let processCell = (s: string) : string => {
  s |.
  Js.String.replaceByRe([%re "/\\&/g"], "&amp;", _) |.
  Js.String.replaceByRe([%re "/</g"], "&lt;", _) |.
  Js.String.replaceByRe([%re "/>/g"], "&gt;", _) |.
  Js.String.replaceByRe([%re "/\\n/g"], "</div><div>", _);
};

let createDefnList = (headers: array(string), cells: array(string)) : string => {
  let rec helper = (acc: string, n: int) : string => {
    if (n == Belt.Array.length(headers)) {
      acc
    } else {
      helper(acc ++ "<dt>" ++ headers[n] ++ "</dt>\n<dd><div>"
        ++ processCell(cells[n]) ++ "</div></dd>\n", n + 1) ;
    }
  };
  
  "<dl>" ++ helper("", 0) ++ "</dl>\n\n";
};


let args = Node.Process.argv;
let csvFile = Belt.Array.getUnsafe(args, Belt.Array.length(args) - 1);

/* Read the entire CSV file as one string */
let allLines = Node.Fs.readFileAsUtf8Sync(csvFile);

/* Parse the CSV  string  */
let parseData = Results.dataGet(parse(allLines));

let headers = Belt.Array.slice(parseData, ~offset=0, ~len=1) |. Belt.Array.getUnsafe(_,0);
let contentRows = Belt.Array.slice(parseData, ~offset=1, ~len=Belt.Array.length(parseData) - 1);


let adminBotEmail = "admin@noschool2k20.fr";
let adminBotName = "NoReply NoSchool 2K20";

//let n = Array.length(contentRows)
//let messageJson = ModelJson.formatMessage(contentRows[0][0],contentRows[0][1],"toto",adminBotEmail,adminBotName,"200")

let writeJson = (rows: array(array(string)),n:int) : Js.Json.t => {
  let email = rows[n][0]
  let name = rows[n][1]
  let subject = rows[n][2]
  
  ModelJson.formatMessage(name,email,subject,adminBotEmail,adminBotName,"200");
      
}
external jsonToObjects : Js.Json.t => Js.t({..}) = "%identity";

for (n in 0 to Array.length(contentRows) - 2){
  let message = writeJson(contentRows,n)
  Js.log(message)
  let _ = APICall.sendMail(jsonToObjects(message))

}

