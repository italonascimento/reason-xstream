open Xs;

let buffer: (stream('a), stream('b)) => stream(array('b));

let concat: array(stream('a)) => stream('a);

let debounce: (int, stream('a)) => stream('a);

let delay: (int, stream('a)) => stream('a);

let dropRepeats:
  (~isEqual: ('a, 'a) => bool=?, unit, stream('a)) => stream('a);

let dropUntil: (stream('a), stream('b)) => stream('b);

[@bs.module "xstream/extra/flattenConcurrently"]
external flattenConcurrently : stream(stream('a)) => stream('a) = "default";

[@bs.module "xstream/extra/flattenSequentially"]
external flattenSequentially : stream(stream('a)) => stream('a) = "default";

type diagramOptions('a, 'e);

let diagramOptions:
  (~values: Js.Dict.t('a)=?, ~timeUnit: int=?, ~errorValue: 'e=?, unit) =>
  diagramOptions('a, 'e);

let fromDiagram: (~options: diagramOptions('a, 'b)=?, string) => stream('a);

type element;

let fromEvent: (~useCapture: bool=?, element, string) => stream('a);

[@bs.module "xstream/extra/pairwise"]
external pairwise : stream('a) => stream(('a, 'a)) = "default";

let sampleCombine: (stream('a), stream('b)) => stream(('b, 'a));

let sampleCombine2:
  (stream('a), stream('b), stream('c)) => stream(('c, 'a, 'b));

let split: (stream('a), stream('b)) => stream(stream('b));

let throttle: (int, stream('a)) => stream('a);

type easingObject;

type easingFunction = unit => unit;

type tweenConfig;

let tweenConfig:
  (
    ~fromValue: float,
    ~toValue: float,
    ~duration: int,
    ~ease: easingFunction=?,
    ~interval: int=?,
    unit
  ) =>
  tweenConfig;

type tween = tweenConfig => stream(float);

[@bs.module "xstream/extra/tween"] external tween : tween = "default";

[@bs.get] external linear : tween => easingObject = "";

[@bs.get] external power2 : tween => easingObject = "";

[@bs.get] external power3 : tween => easingObject = "";

[@bs.get] external power4 : tween => easingObject = "";

[@bs.get] external exponential : tween => easingObject = "";

[@bs.get] external back : tween => easingObject = "";

[@bs.get] external bounce : tween => easingObject = "";

[@bs.get] external circular : tween => easingObject = "";

[@bs.get] external elastic : tween => easingObject = "";

[@bs.get] external sine : tween => easingObject = "";

[@bs.get] external easeIn : easingObject => easingFunction = "";

[@bs.get] external easeOut : easingObject => easingFunction = "";

[@bs.get] external easeInOut : easingObject => easingFunction = "";