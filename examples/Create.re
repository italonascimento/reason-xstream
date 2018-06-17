type error;

[@bs.val] external setInterval : (unit => unit, int) => int = "";

[@bs.val] external clearInterval : int => unit = "";

let id = ref(0);

let producer: Xs.producer(string, error) =
  Xs.(
    producer(
      ~start=
        listener => id := setInterval(() => listener |> next("yo"), 1000),
      ~stop=() => clearInterval(id^),
    )
  );

let stream = Xs.create(~producer, ());

Js.log(stream);

stream |> Xs.(addListener(listener(~next=Js.log, ())));