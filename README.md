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

## API Documentation

* [`listener`](#listener)
* [`producer`](#producer)

Factories:

* [`create`](#createproducer)
* [`createWithMemory`](#createwithmemoryproducer)
* [`never`](#never)
* [`empty`](#empty)
* [`throw`](#throw)
* [`streamOf`](#streamofa)
* [`fromArray`](#fromarrayarraya)
* [`fromList`](#fromlistlista)

### Listener

A Listener is a JavaScript object with one to three functions attached to it: `next('a)`, `error('e)`, and `complete()`. There is usually one function for each type of event a stream may emit, but only `next` is always required.

Make use of the `Xs.listener` function to build a listener:

```reason
Xs.listener: (~next: 'a => unit, ~error: option('e => unit)=?, ~complete: option(unit => unit)=?) => Xs.listener('a, 'e)
```

* `next` events are the typical type, they deliver a value;
* `error` events abort (stop) the execution of the stream, and happen when something goes wrong in the stream (or upstream somewhere in the chain of operators);
* `complete` events signal the peaceful stop of the execution of the stream.

#### Example

```reason
let listener = Xs.listener(
  ~next= Js.log,
  ~error= Js.log,
  ~complete= () => Js.log("complete")
);
```

Then, attatch the listener to a stream:

```reason
stream |> Xs.addListener(listener);
```

And remove when you think it's done:

```reason
stream |> Xs.removeListener(listener);
```

---

### Producer

A producer is like a machine that produces events to be broadcast on a stream.

Producers are JavaScript objects with two functions attached: `start(listener)` and `stop()`. Once you call `start` with a `listener`, the producer will start generating events and it will send those to the listener. When you call `stop()`, the producer should quit doing its own thing.

Make use of the `Xs.producer` function to build a producer:

```reason
Xs.producer: (~start: Xs.listener('a, 'e) => unit, ~stop: unit => unit) => Xs.producer('a, 'e)
```

#### Example

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

---

### `create(~producer=?)`

Creates a new stream ginven a producer.

```reason
Xs.create: (~producer: option(Xs.producer('a, 'e))=?) => Xs.stream('a)
```

#### Example

```reason
/* New stream without producer, which never emits any value */
let stream = Xs.create();

/* Passing optional producer */
let stream = Xs.create(~producer=myProducer, ());
```

---

### `createWithMemory(~producer=?)`

Creates a new memory stream given a producer.

```reason
Xs.createWithMemory: (~producer: option(Xs.producer('a, 'e))=?) => Xs.stream('a)
```

#### Example

```reason
/* New memoryStream without producer, which never emits any value */
let stream = Xs.createWithMemory();

/* Passing optional producer */
let stream = Xs.createWithMemory(~producer=myProducer, ());
```

---

### `never()`

Creates a stream that never emits any event.

```reason
Xs.never: unit => Xs.stream('a)
```

#### Marble diagram

```
never
--------------------------
```

---

### `empty()`

Creates a stream that completes immediately.

```reason
Xs.empty: unit => Xs.stream('a)
```

#### Marble diagram

```
empty
-|
```

---

### `throw('e)`

Creates a stream that immediately emits an "error" with the value passed as argument.

```reason
Xs.error: 'e => Xs.stream('a)
```

#### Marble diagram

```
throw(X)
-X
```

---

### `streamOf('a)`

Creates a stream that immediately emits the value passed as argument, then completes.

```reason
Xs.streamOf: 'a => Xs.stream('a)
```

*Note: unlike the original JavaScript equivalent `of`, `streamOf` takes accepts only one argument. Use [`fromArray`](#fromarray) or [`fromList`](#fromlist) if you need to emit more values.*

---

### `fromArray(array('a))`

Converts an array to a stream. The returned stream will emit synchronously all the items in the array, and then complete.

```reason
Xs.fromArray: array('a) => Xs.stream('a)
```

#### Marble diagram

```
fromArray([|1, 2, 3|])
123|
```

---

### `fromList(list('a))`

Similar to `[fromArray](#fromarray)`. Converts a list to a stream. The returned stream will emit synchronously all the items in the list, and then complete.

```reason
Xs.fromArray: array('a) => Xs.stream('a)
```

#### Marble diagram

```
fromArray([1, 2, 3])
123|
```

---

## TODO

* Create automated tests
* Write documentation/examples