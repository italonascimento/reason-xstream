type stream('a);

type subscription;

[@bs.send.pipe: subscription] external unsubscribe : unit => unit = "";

type listener('a, 'e);

let listener:
  (~next: 'a => unit, ~error: 'e => unit=?, ~complete: unit => unit=?, unit) =>
  listener('a, 'e);

[@bs.send.pipe: listener('a, 'e)] external next : 'a => unit = "";

[@bs.send.pipe: listener('a, 'e)] external error : 'e => unit = "";

[@bs.send.pipe: listener('a, 'e)] external complete : unit => unit = "";

type producer('a, 'e);

let producer:
  (~start: listener('a, 'e) => unit, ~stop: unit => unit) => producer('a, 'e);

let create: (~producer: producer('a, 'e)=?, unit) => stream('a);

let createWithMemory: (~producer: producer('a, 'e)=?, unit) => stream('a);

let never: unit => stream('a);

let empty: unit => stream('a);

let throw: 'a => stream('b);

let streamOf: 'a => stream('a);

let fromArray: array('a) => stream('a);

let fromPromise: Js.Promise.t('a) => stream('a);

let periodic: int => stream(int);

let combine: (stream('a), stream('b)) => stream(('a, 'b));

let combine3:
  (stream('a), stream('b), stream('c)) => stream(('a, 'b, 'c));

let fromList: list('a) => stream('a);

let merge: array(stream('a)) => stream('a);

[@bs.send.pipe: stream('a)]
external addListener : listener('a, 'e) => unit = "";

[@bs.send.pipe: stream('a)]
external removeListener : listener('a, 'e) => unit = "";

[@bs.send.pipe: stream('a)]
external subscribe : listener('a, 'e) => subscription = "";

[@bs.send.pipe: stream('a)] external map : ('a => 'b) => stream('b) = "";

[@bs.send.pipe: stream('a)] external mapTo : 'b => stream('b) = "";

[@bs.send.pipe: stream('a)]
external filter : ('a => bool) => stream('a) = "";

[@bs.send.pipe: stream('a)] external take : int => stream('a) = "";

[@bs.send.pipe: stream('a)] external drop : int => stream('a) = "";

[@bs.send.pipe: stream('a)] external last : unit => stream('a) = "";

[@bs.send.pipe: stream('a)] external startWith : 'a => stream('a) = "";

[@bs.send.pipe: stream('a)]
external endWhen : stream('b) => stream('a) = "";

[@bs.send.pipe: stream('a)]
external fold : (('b, 'a) => 'b, 'a) => stream('a) = "";

[@bs.send.pipe: stream('a)] external replaceError : 'c => stream('b) = "";

[@bs.send.pipe: stream(stream('a))]
external flatten : unit => stream('a) = "";

[@bs.send.pipe: stream('a)] external remember : unit => stream('a) = "";

[@bs.send.pipe: stream('a)] external debug : ('a => unit) => stream('a) = "";

[@bs.send.pipe: stream('a)]
external imitate : stream('a) => stream('a) = "";

[@bs.send.pipe: stream('a)] external shamefullySendNext : 'a => unit = "";

[@bs.send.pipe: stream('a)] external shamefullySendError : 'e => unit = "";

[@bs.send.pipe: stream('a)]
external shamefullySendComplete : unit => unit = "";

let setDebugListener: (option(listener('a, 'b)), stream('a)) => unit;