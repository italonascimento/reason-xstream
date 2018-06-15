open Xs;

[@bs.module "xstream/extra/buffer"]
external buffer: (. stream('b)) => (. stream('a)) => stream(array('a)) = "default";
let buffer =  separator => source => buffer(.separator)(.source);

type concat;
[@bs.module "xstream/extra/concat"] external concat: concat = "default";
[@bs.send] external apply: concat => Js.Nullable.t('b) => array(stream('a)) => stream('a) = "";
let concat = sources => apply(concat, Js.Nullable.null, sources);

[@bs.module "xstream/extra/debounce"]
external debounce: (. int) => (. stream('a)) => stream('a) = "default";
let debounce = period => source => debounce(.period)(.source);

[@bs.module "xstream/extra/delay"]
external delay: (. int) => (. stream('a)) => stream('a) = "default";
let delay = period => source => delay(.period)(.source);

[@bs.module "xstream/extra/dropRepeats"]
external dropRepeats: (. Js.Nullable.t('a => 'a => bool)) => (. stream('a)) => stream('a) = "default";
let dropRepeats = 
  (~isEqual: option('a => 'a => bool)=?, ()) => 
    source => 
      dropRepeats(. Js.Nullable.fromOption(isEqual))(.source);

[@bs.module "xstream/extra/dropUntil"]
external dropUntil: (. stream('b)) => (. stream('a)) => stream('a) = "default";
let dropUntil = other => source => dropUntil(.other)(.source);

[@bs.module "xstream/extra/flattenConcurrently"]
external flattenConcurrently: stream(stream('a)) => stream('a) = "default";

[@bs.module "xstream/extra/flattenSequentially"]
external  flattenSequentially: stream(stream('a)) => stream('a) = "default";

[@bs.module "xstream/extra/sampleCombine"]
external sampleCombine: (. stream('b)) => ((. stream('a)) => stream(('a, 'b))) = "default";
let sampleCombine =
  combined => source => sampleCombine(.combined)(.source);
