# reason-xstream
## ReasonML bindings for xstream

Original JavaScript lib:
https://github.com/staltz/xstream

## Example

```reason
/*
Tick every second incremental numbers,
only pass even numbers, then map them to their square,
and stop after 5 seconds has passed
*/

let stream = Xs.periodic(1000)
  |> Xs.filter(i => i mod 2 === 0)
  |> Xs.map(i => i * i)
  |> Xs.endWhen(
    Xs.periodic(5000)
      |> Xs.take(1)
    );

/*
So far, the stream is idle.
As soon as it gets its first listener, it starts executing.
*/

stream
|> Xs.addListener(
  Xs.listener(
    ~next= i => Js.log(i),
    ~error= err => Js.log(err),
    ~complete= () => Js.log("completed"),
    ()
  )
);
```
