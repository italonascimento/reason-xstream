XsExtra.(fromDiagram("--1-2-----3--4----5|")
  |> throttle(60)
  |> Xs.(subscribe(
    listener(~next=v => Js.log(v), ()),
  ))
)