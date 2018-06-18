type error;

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

let stream = Xs.create(~producer, ());

stream |> Xs.(addListener(listener(~next=Js.log, ())));