[%%mel.raw {|import "./orders.css"|}];

module Array = Js.Array;

type t = array(Order.t);

let taxRate = 0.12;

[@react.component]
let make = (~orders as initialOrders: t) => {
  let (orders, setOrders) = React.useState(() => initialOrders);

  let subtotal =
    orders |> Array.reduce((acc, order) => acc +. Order.toPrice(order), 0.);
  let total = subtotal *. (1. +. taxRate);

  <table className="orders">
    {orders
     |> Array.mapi((order, index) =>
          <Order_Remove
            key={"order-" ++ string_of_int(index)}
            order
            onRemoveClick={() =>
              setOrders(orders =>
                orders |> Array.filteri((_value, i) => i != index)
              )
            }
          />
        )
     |> React.array}
    <tr className="total">
      <td colSpan=2> {React.string("Subtotal")} </td>
      <td> {subtotal |> Format.currency} </td>
    </tr>
    <tr className="total">
      <td colSpan=2> {React.string("Sales tax")} </td>
      <td> {taxRate |> Format.percent} </td>
    </tr>
    <tr className="total">
      <td colSpan=2> {React.string("Total")} </td>
      <td> {total |> Format.currency} </td>
    </tr>
  </table>;
};
