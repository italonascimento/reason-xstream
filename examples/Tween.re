XsExtra.(
  tween(
    tweenConfig(
      ~fromValue=20.,
      ~toValue=100.,
      ~duration=1000,
      ~ease= tween |> linear |> easeIn,
      ()
    )
  )
)
|> Xs.(
  subscribe(
    listener(
      ~next=Js.log,
      ()
    )
  )
)