[%%mel.raw {|import "./orders.css"|}];

type t = list(Order.t);

let taxRate = 0.12;

[@react.component]
let make = (~orders as initialOrders: t) => {
  let (orders, setOrders) = React.useState(() => initialOrders);

  let subtotal =
    orders
    |> List.fold_left((acc, order) => acc +. Order.toPrice(order), 0.);
  let total = subtotal *. (1. +. taxRate);

  <table className="orders">
    {orders
     |> List.mapi((index, order) =>
          <Order_Remove
            key={"order-" ++ string_of_int(index)}
            order
            onRemoveClick={() =>
              setOrders(orders =>
                orders |> List.filteri((i, _value) => i != index)
              )
            }
          />
        )
     |> Array.of_list
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
