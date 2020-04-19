let args = Node.Process.argv;
let csvFile = Belt.Array.getUnsafe(args, Belt.Array.length(args) - 2);

let allLines = Node.Fs.readFileAsUtf8Sync(csvFile);

module Error = {
   [@bs.deriving abstract] type t = {
    [@bs.as "type"]  type_: string,
    code: string,
    message: string,
    row: int
  }
};

module Meta = {
  [@bs.deriving abstract] type t = {
    delimiter: string,
    linebreak: string,
    aborted: bool,
    fields: array(string),
    truncated: bool
  }
};

module Results = {
 [@bs.deriving abstract] type t = {
      data: array(array(string)),
      error: array(Error.t),
      meta: Meta.t
  };
};


[@bs.val] [@bs.module "papaparse"] external parse :
(string) => Results.t = "parse";

let parseData = Results.dataGet(parse(allLines));

let headers = Belt.Array.slice(parseData,~offset=0,~len=1) |.Belt.Array.getUnsafe(_,0);
let contentRows =Belt.Array.slice(parseData,~offset=1,~len=Belt.Array.length(parseData) - 1);

