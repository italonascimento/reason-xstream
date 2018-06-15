# ReasonXstream

ReasonML bindings for [xstream](https://github.com/staltz/xstream).

From the original lib description:

> An extremely intuitive, small, and fast
> functional reactive stream library for JavaScript
>
> * Only 26 core operators and factories
> * Only "hot" streams
> * Written in TypeScript
> * Approximately 30 kB in size, when minified
> * On average, faster than RxJS 4, Kefir, Bacon.js, as fast as RxJS 5, and slower than most.js
> * Tailored for Cycle.js, or applications with limited use of subscribe


## Example

```reason
/*
Tick every second incremental numbers,
only pass even numbers, then map them to their square,
and stop after 5 seconds has passed
*/
let stream = Xs.(
  periodic(1000)
    |> filter(i => i mod 2 === 0)
    |> map(i => i * i)
    |> endWhen(
      periodic(5000)
        |> take(1)
      )
);

/*
So far, the stream is idle.
As soon as it gets its first listener, it starts executing.
*/
stream
|> Xs.(
  addListener(
    listener(
      ~next= i => Js.log(i),
      ~error= err => Js.log(err),
      ~complete= () => Js.log("completed"),
      ()
    )
  )
);
```

## Currying

With ReasonXstream you may use currying as you would in any idiomatic Reason code.

```reason
/*
Passing one argument at a time for 
a function which takes two arguments
*/
let a = Xs.(periodic(1000)
  |> mapTo("A"));
let b = Xs.(periodic(2000)
  |> mapTo("B"));

let combineWithA = Xs.combine(a);

combineWithA(b) 
|> Xs.(
  subscribe(
    listener(
      ~next= v => Js.log(v),
      ()
    )
  )
);

/*
Passing two arguments at once for 
a function which returns a function
*/
let c = Xs.(periodic(1000)
  |> mapTo("C"));
let d = Xs.(periodic(2000)
  |> mapTo("D"));

/*
same as:
let cWithLatestD = c |> XsExtra.sampleCombine(d);
*/
let cWithLatestD = XsExtra.sampleCombine(d, c);
```

## TODO

* Create automated tests
* Write documentation/examples