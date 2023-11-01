[%%mel.raw {|import "./orders.css"|}];

type t = array(Order.t);

let taxRate = 0.12;

[@react.component]
let make = (~orders as initialOrders: t) => {
  let (orders, _setOrders) = React.useState(() => initialOrders);

  let subtotal =
    orders
    |> Array.fold_left((acc, order) => acc +. Order.toPrice(order), 0.);
  let total = subtotal *. (1. +. taxRate);

  <table className="orders">
    {orders
     |> Array.mapi((index, order) =>
          <Order key={"order-" ++ string_of_int(index)} order />
        )
     |> React.array}
    <tr className="total">
      <td> {React.string("Subtotal")} </td>
      <td> {subtotal |> Format.currency} </td>
    </tr>
    <tr className="total">
      <td> {React.string("Sales tax")} </td>
      <td> {taxRate |> Format.percent} </td>
    </tr>
    <tr className="total">
      <td> {React.string("Total")} </td>
      <td> {total |> Format.currency} </td>
    </tr>
  </table>;
};
