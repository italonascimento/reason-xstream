# ReasonML bindings for xstream

## Usage

```reason
open XStream;

let interval = xs
  |> periodic(1000);

interval
  |> map(i => string_of_int(i + 1) ++ " seconds passed")
  |> subscribe(
    listener(~next= value => Js.log(value), ())
  );

/*
1 seconds passed
2 seconds passed
3 seconds passed
...
*/
```
