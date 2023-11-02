let currency = value =>
  value |> Js.Float.toFixedWithPrecision(~digits=2) |> React.string;

let percent = value =>
  value
  *. 100.
  |> Js.Float.toFixedWithPrecision(~digits=0)
  |> (s => s ++ "%")
  |> React.string;

let percentNotRecommended = value =>
  value
  *. 100.
  |> Js.Float.toFixedWithPrecision(~digits=0)
  |> String.cat(_, "%")
  |> React.string;
