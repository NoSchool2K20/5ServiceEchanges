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
let htmlFile = Belt.Array.getUnsafe(args, Belt.Array.length(args) - 2);

/* Read the entire CSV file as one string */
let allLines = Node.Fs.readFileAsUtf8Sync(csvFile);

/* Parse the CSV  string  */
let parseData = Results.dataGet(parse(allLines));

let headers = Belt.Array.slice(parseData, ~offset=0, ~len=1) |. Belt.Array.getUnsafe(_,0);
let contentRows = Belt.Array.slice(parseData, ~offset=1, ~len=Belt.Array.length(parseData) - 1);

let htmlHeader = {js|
<!DOCTYPE html>
<html>
<head>
  <title>Service Echanges</title>
  <meta http-equiv="Content-Type" content="text/html; charset=utf-8" />
  <style type="text/css">
  body {font-family: helvetica, arial, sans-serif; }
  dl {
    margin: 0.5em 0;
  }
  dt { color: #666; }
  dd { margin-bottom: 0.5em; }
  </style>
</head>
<body>
|js};


let corpsHtml = (headers: array(string),rows: array(array(string))): string => {
 let rec helper = (acc: string, n: int) : string => {
    if (n == Belt.Array.length(headers)) {
      acc
    } else {
       helper(acc ++ "<dt>" ++ headers[n] ++ "</dt>\n<dd><div>"
        ++ rows[0][n] ++ "</div></dd>\n", n + 1) ;
    }
  };
  
  "<dl>" ++ helper("", 0) ++ "</dl>\n\n";
};
  
let htmlString=htmlHeader ++ corpsHtml(headers,contentRows) ++ {js|</body>\n</html>|js}

let _ = Node.Fs.writeFileAsUtf8Sync(htmlFile,htmlString);


