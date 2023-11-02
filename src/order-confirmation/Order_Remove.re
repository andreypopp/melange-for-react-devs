[%%mel.raw {|import "./order.css"|}];

[@react.component]
let make = (~order: Order.t, ~onRemoveClick: unit => unit) =>
  <tr className="order">
    <td className="remove" onClick={_evt => onRemoveClick()}>
      {React.string({js|❌|js})}
    </td>
    <td className="emoji"> {order |> Order.toEmoji |> React.string} </td>
    <td className="price"> {order |> Order.toPrice |> Format.currency} </td>
  </tr>;
