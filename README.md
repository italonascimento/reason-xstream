# ReasonXstream

ReasonML bindings for [xstream](https://github.com/staltz/xstream).

From the original lib description:

> ### An extremely intuitive, small, and fast functional reactive stream library for JavaScript
>
> * Only 26 core operators and factories
> * Only "hot" streams
> * Written in TypeScript
> * Approximately 30 kB in size, when minified
> * On average, faster than RxJS 4, Kefir, Bacon.js, as fast as RxJS 5, and slower than most.js
> * Tailored for Cycle.js, or applications with limited use of subscribe

## Installation

```
npm i -s reason-xstream
```

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

## Documentation

### `listener(~next=?, ~error=?, complete=?)`

Creates a listener, which can listen to a stream's emissions, errors or completion events.

```reason
let listener = Xs.listener(
  ~next= Js.log,
  ~error= Js.log,
  ~complete= () => Js.log("complete")
);

stream |> Xs.addListener(listener);
```

### `producer(~start, ~stop)`

Creates a `producer`, which produces events to be broadcast on a stream.

```reason
type intervalId;
[@bs.val] external setInterval : (unit => unit, int) => intervalId = "";
[@bs.val] external clearInterval : intervalId => unit = "";

let id = ref(None);

let producer: Xs.producer(string, error) =
  Xs.(
    producer(
      ~start=
        listener =>
          id := Some(setInterval(() => listener |> next("yo"), 1000)),
      ~stop=
        () =>
          switch (id^) {
          | None => ()
          | Some(id) => clearInterval(id)
          },
    )
  );

/* Emits "yo" every 1 second */
let stream = Xs.create(~producer, ());
```

### Factories

#### `create(~producer=?)`

Creates a new stream ginven a producer.

```reason
/* New stream without producer */
let stream = Xs.create();

/* Passing optional producer */
let stream = Xs.create(~producer=myProducer, ());
```

#### `createWithMemory(~producer=?)`

Creates a new memory stream given a producer.

```reason
/* New memoryStream without producer */
let stream = Xs.createWithMemory();

/* Passing optional producer */
let stream = Xs.createWithMemory(~producer=myProducer, ());
```

#### `never()`

Creates a stream that never emits any event.

#### `empty()`

Creates a stream that completes immediately.

## TODO

* Create automated tests
* Write documentation/examples