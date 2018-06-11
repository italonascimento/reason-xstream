type stream('a);
type subscription;
[@bs...] external unsubscribe: (unit, subscription) => unit = "";
type listener('a, 'e);
[@bs...] external listener:
  (~next: 'a => unit=?, ~error: 'e => unit=?, ~complete: unit => unit=?,
  unit) => listener('a, 'e) = "";
[@bs...] external next: listener('a, 'e) => option('a => unit) = "next";
[@bs...] external error: listener('a, 'e) => option('e => unit) = "error";
[@bs...] external complete: listener('a, 'e) => option(unit => unit)
  = "complete";
let create: unit => stream('a);
let createWithMemory: unit => stream('a);
let never: unit => stream('a);
let empty: unit => stream('a);
let throw: 'a => stream('b);
let streamOf: 'a => stream('a);
let fromArray: array('a) => stream('a);
let fromPromise: Js.Promise.t('a) => stream('a);
let periodic: int => stream(int);
let combine: (stream('a), stream('b)) => stream(('a, 'b));
let combine3: (stream('a), stream('b), stream('c)) => stream(('a, 'b, 'c));
let fromList: list('a) => stream('a);
let merge: array(stream('a)) => stream('a);
[@bs...] external addListener: (listener('a, 'e), stream('a)) => unit = "";
[@bs...] external removeListener: (listener('a, 'e), stream('a)) => unit = "";
[@bs...] external subscribe: (listener('a, 'e), stream('a)) => subscription
  = "";
[@bs...] external map: ('a => 'b, stream('a)) => stream('b) = "";
[@bs...] external mapTo: ('b, stream('a)) => stream('b) = "";
[@bs...] external filter: ('a => bool, stream('a)) => stream('a) = "";
[@bs...] external take: (int, stream('a)) => stream('a) = "";
[@bs...] external drop: (int, stream('a)) => stream('a) = "";
[@bs...] external last: (unit, stream('a)) => stream('a) = "";
[@bs...] external startWith: ('a, stream('a)) => stream('a) = "";
[@bs...] external endWhen: (stream('b), stream('a)) => stream('a) = "";
[@bs...] external fold: (('b, 'a) => 'b, 'a, stream('a)) => stream('a) = "";
[@bs...] external replaceError: ('c, stream('a)) => stream('b) = "";
[@bs...] external flatten: (unit, stream(stream('a))) => stream('a) = "";
[@bs...] external remember: (unit, stream('a)) => stream('a) = "";
[@bs...] external debug: ('a => unit, stream('a)) => stream('a) = "";
[@bs...] external imitate: (stream('a), stream('a)) => stream('a) = "";
[@bs...] external shamefullySendNext: ('a, stream('a)) => unit = "";
[@bs...] external shamefullySendError: ('e, stream('a)) => unit = "";
[@bs...] external shamefullySendComplete: (unit, stream('a)) => unit = "";
let setDebugListener: (option(listener('a, 'b)), stream('a)) => unit;
