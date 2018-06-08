type xs;
type stream('a);
type subscription;

/* TODO: implement generic error type */
type error = {
  message: string,
};

[@bs.deriving abstract]
type listener('a) = {
  [@bs.optional] next: 'a => unit,
  [@bs.optional] error: error => unit,
  [@bs.optional] complete: unit => unit,
};


[@bs.module "xstream"] external xs : xs = "default";


/* FACTORIES */
[@bs.send.pipe: xs] external create : unit => stream('a) = "";
[@bs.send.pipe: xs] external createWithMemory : unit => stream('a) = "";
[@bs.send.pipe: xs] external never : unit => stream('a) = "";
[@bs.send.pipe: xs] external empty : unit => stream('a) = "";
[@bs.send.pipe: xs] external throw : error => stream('a) = "";
[@bs.send.pipe: xs] external streamOf : 'a => stream('a) = "of";
[@bs.send.pipe: xs] external fromArray : array('a) => stream('a) = "";
[@bs.send.pipe: xs] external fromPromise : Js.Promise.t('a) => stream('a) = "";
[@bs.send.pipe: xs] external periodic : int => stream(int) = "";
[@bs.send.pipe: xs] [@bs.splice]  external merge: array(stream('a)) => stream('a) = "";
[@bs.send.pipe: xs] external combine: stream('a) => stream('b) => stream(('a, 'b)) = "";
[@bs.send.pipe: xs] external combine3: stream('a) => stream('b) => stream('c) => stream(('a, 'b, 'c)) = "combine";
let fromList = l => xs => xs |> fromArray(Array.of_list(l));


/* OPERATORS */
[@bs.send.pipe: stream('a)] external map: ('a => 'b) => stream('b) = "map";
[@bs.send.pipe: stream('a)] external filter: ('a => bool) => stream('a) = "filter";
[@bs.send.pipe: stream('a)] external debug: ('a => unit) => stream('a) = "debug";
[@bs.send.pipe: stream('a)] external shamefullySendNext: ('a) => unit = "shamefullySendNext";
[@bs.send.pipe: stream('a)] external subscribe: listener('a) => subscription = "subscribe";
[@bs.send.pipe: stream('a)] external removeListener: listener('a) => unit = "removeListener";

[@bs.send.pipe: subscription] external unsubscribe: unit => unit = "unsubscribe";
