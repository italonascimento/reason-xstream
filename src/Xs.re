type xs;

type stream('a);

type subscription;

[@bs.send.pipe: subscription] external unsubscribe : unit => unit = "";

[@bs.deriving abstract]
type listener('a, 'e) = {
  [@bs.optional]
  next: 'a => unit,
  [@bs.optional]
  error: 'e => unit,
  [@bs.optional]
  complete: unit => unit,
};

[@bs.module "xstream"] external xs : xs = "default";

/* FACTORIES */
[@bs.send.pipe: xs] external create : unit => stream('a) = "";

let create = () => xs |> create();

[@bs.send.pipe: xs] external createWithMemory : unit => stream('a) = "";

let createWithMemory = () => xs |> createWithMemory();

[@bs.send.pipe: xs] external never : unit => stream('a) = "";

let never = () => xs |> never();

[@bs.send.pipe: xs] external empty : unit => stream('a) = "";

let empty = () => xs |> empty();

[@bs.send.pipe: xs] external throw : 'b => stream('a) = "";

let throw = err => xs |> throw(err);

[@bs.send.pipe: xs] external streamOf : 'a => stream('a) = "of";

let streamOf = value => xs |> streamOf(value);

[@bs.send.pipe: xs] external fromArray : array('a) => stream('a) = "";

let fromArray = arr => xs |> fromArray(arr);

[@bs.send.pipe: xs]
external fromPromise : Js.Promise.t('a) => stream('a) = "";

let fromPromise = p => xs |> fromPromise(p);

[@bs.send] external periodic : (xs, int) => stream(int) = "";

let periodic = xs |> periodic;

[@bs.send.pipe: xs]
external combine : (stream('a), stream('b)) => stream(('a, 'b)) = "";

let combine = (a, b) => xs |> combine(a, b);

[@bs.send.pipe: xs]
external combine3 :
  (stream('a), stream('b), stream('c)) => stream(('a, 'b, 'c)) =
  "combine";

let combine3 = (a, b, c) => xs |> combine3(a, b, c);

let fromList = l => fromArray(Array.of_list(l));

type merge;

[@bs.get] external merge : xs => merge = "";

[@bs.send]
external apply :
  (merge, Js.Nullable.t('b), array(stream('a))) => stream('a) =
  "";

let merge = sources => apply(merge(xs), Js.Nullable.null, sources);

/* OPERATORS */
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

[@bs.send.pipe: stream('a)]
external setDebugListener : Js.Nullable.t(listener('a, 'e)) => unit =
  "setDebugListener";

let setDebugListener = listener =>
  setDebugListener(Js.Nullable.fromOption(listener));