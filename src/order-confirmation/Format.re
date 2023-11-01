let currency = value =>
  value |> Js.Float.toFixedWithPrecision(~digits=2) |> React.string;

let percent = value => {
  let appendPercent = s => s ++ "%";

  value
  *. 100.
  |> Js.Float.toFixedWithPrecision(~digits=0)
  |> appendPercent
  |> React.string;
};
