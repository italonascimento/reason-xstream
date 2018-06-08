type xs;
type stream('a);
type subscription;
[@bs.send.pipe: subscription] external unsubscribe: unit => unit = "";

[@bs.deriving abstract]
type listener('a, 'e) = {
  [@bs.optional] next: 'a => unit,
  [@bs.optional] error: 'e => unit,
  [@bs.optional] complete: unit => unit,
};


[@bs.module "xstream"] external xs : xs = "default";


/* FACTORIES */
[@bs.send.pipe: xs] external create : unit => stream('a) = "";
[@bs.send.pipe: xs] external createWithMemory : unit => stream('a) = "";
[@bs.send.pipe: xs] external never : unit => stream('a) = "";
[@bs.send.pipe: xs] external empty : unit => stream('a) = "";
[@bs.send.pipe: xs] external throw : 'b => stream('a) = "";
[@bs.send.pipe: xs] external streamOf : 'a => stream('a) = "of";
[@bs.send.pipe: xs] external fromArray : array('a) => stream('a) = "";
[@bs.send.pipe: xs] external fromPromise : Js.Promise.t('a) => stream('a) = "";
[@bs.send.pipe: xs] external periodic : int => stream(int) = "";
[@bs.send.pipe: xs] [@bs.splice]  external merge: array(stream('a)) => stream('a) = "";
[@bs.send.pipe: xs] external combine: stream('a) => stream('b) => stream(('a, 'b)) = "";
[@bs.send.pipe: xs] external combine3: stream('a) => stream('b) => stream('c) => stream(('a, 'b, 'c)) = "combine";
let fromList = l => xs => xs |> fromArray(Array.of_list(l));


/* OPERATORS */
[@bs.send.pipe: stream('a)] external addListener: listener('a, 'e) => unit = "";
[@bs.send.pipe: stream('a)] external removeListener: listener('a, 'e) => unit = "";
[@bs.send.pipe: stream('a)] external subscribe: listener('a, 'e) => subscription = "";
[@bs.send.pipe: stream('a)] external map: ('a => 'b) => stream('b) = "";
[@bs.send.pipe: stream('a)] external mapTo: 'b => stream('b) = "";
[@bs.send.pipe: stream('a)] external filter: ('a => bool) => stream('a) = "";
[@bs.send.pipe: stream('a)] external take: int => stream('a) = "";
[@bs.send.pipe: stream('a)] external drop: int => stream('a) = "";
[@bs.send.pipe: stream('a)] external last: unit => stream('a) = "";
[@bs.send.pipe: stream('a)] external startWith: 'a => stream('a) = "";
[@bs.send.pipe: stream('a)] external endWhen: stream('b) => stream('a) = "";
[@bs.send.pipe: stream('a)] external fold: ((('b, 'a) => 'b), 'a) => stream('a) = "";
[@bs.send.pipe: stream('a)] external replaceError: 'c => stream('b) = "";
[@bs.send.pipe: stream(stream('a))] external flatten: unit => stream('a) = "";
[@bs.send.pipe: stream('a)] external remember: unit => stream('a) = "";
[@bs.send.pipe: stream('a)] external debug: ('a => unit) => stream('a) = "";
[@bs.send.pipe: stream('a)] external imitate: stream('a) => stream('a) = "";
[@bs.send.pipe: stream('a)] external shamefullySendNext: ('a) => unit = "";
[@bs.send.pipe: stream('a)] external shamefullySendError: ('e) => unit = "";
[@bs.send.pipe: stream('a)] external shamefullySendComplete: unit => unit = "";
[@bs.send.pipe: stream('a)] external jsSetDebugListener: Js.Nullable.t(listener('a, 'e)) => unit = "setDebugListener";
let setDebugListener = listener =>
  jsSetDebugListener(Js.Nullable.fromOption(listener));
