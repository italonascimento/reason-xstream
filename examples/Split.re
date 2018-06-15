let source = Xs.periodic(50) |> Xs.take(10);

let separator =
  XsExtra.concat([|Xs.periodic(167) |> Xs.take(2), Xs.never()|]);

source
|> XsExtra.split(separator)
|> Xs.(
     subscribe(
       listener(
         ~next=
           stream =>
             stream
             |> addListener(
                  listener(
                    ~next=Js.log,
                    ~complete=() => Js.log("inner completed"),
                    (),
                  ),
                ),
         ~complete=() => Js.log("outer completed"),
         (),
       ),
     )
   );