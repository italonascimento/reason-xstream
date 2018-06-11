open Xs;

[@bs.module "xstream/extra/sampleCombine"] external jsSampleCombine:
  (. stream('b)) => ((. stream('a)) => stream(('a, 'b))) = "default";
let sampleCombine =
  combined =>
    source =>
      jsSampleCombine(.combined)(.source);