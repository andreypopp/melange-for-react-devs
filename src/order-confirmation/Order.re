[%%mel.raw {|import "./order.css"|}];

let sprintf = Printf.sprintf;

module Sandwich = {
  type t =
    | Portabello
    | Ham
    | Unicorn;

  let toPrice =
    fun
    | Portabello => 9.
    | Ham => 10.
    | Unicorn => 88.8;

  let toEmoji = t =>
    sprintf(
      "%s(%s)",
      {js|🥪|js},
      switch (t) {
      | Portabello => {js|🍄|js}
      | Ham => {js|🐷|js}
      | Unicorn => {js|🦄|js}
      },
    );
};

module Burger = {
  type t = {
    tomatoes: bool,
    lettuce: bool,
    bacon: int,
    onions: int,
    cheese: int,
  };

  let toEmoji_simple = ({lettuce, tomatoes, bacon, onions, cheese}) => {
    let multiple = (str, n) =>
      switch (n) {
      | 0 => ""
      | 1 => str
      | n => Printf.sprintf("%s%s%d", str, {js|×|js}, n)
      };

    sprintf(
      "%s{%s}",
      {js|🍔|js},
      [|
        lettuce ? {js|🥬|js} : "",
        tomatoes ? {js|🍅|js} : "",
        multiple({js|🥓|js}, bacon),
        multiple({js|🧅|js}, onions),
        multiple({js|🧀|js}, cheese),
      |]
      |> Js.Array.filter(str => str != "")
      |> Js.Array.joinWith(", "),
    );
  };

  let toEmoji = t => {
    let multiple = (str, n) =>
      switch (n) {
      | 0 => ""
      | 1 => str
      | n => Printf.sprintf("%s%s%d", str, {js|×|js}, n)
      };

    let burger = {js|🍔|js};
    switch (t) {
    | {lettuce: false, tomatoes: false, bacon: 0, onions: 0, cheese: 0} => burger
    | {lettuce, tomatoes, bacon, onions, cheese} =>
      sprintf(
        "%s{%s}",
        burger,
        [|
          lettuce ? {js|🥬|js} : "",
          tomatoes ? {js|🍅|js} : "",
          multiple({js|🥓|js}, bacon),
          multiple({js|🧅|js}, onions),
          multiple({js|🧀|js}, cheese),
        |]
        |> Js.Array.filter(str => str != "")
        |> Js.Array.joinWith(", "),
      )
    };
  };

  let toPrice = ({bacon, onions, cheese, _}) => {
    let getCost = (quantity, price) => price *. float_of_int(quantity);

    15.
    +. getCost(bacon, 0.5)
    +. getCost(onions, 0.2)
    +. getCost(cheese, 0.1);
  };
};

type t =
  | Hotdog
  | Sandwich(Sandwich.t)
  | Burger(Burger.t);

let toPrice =
  fun
  | Hotdog => 5.
  | Sandwich(s) => Sandwich.toPrice(s)
  | Burger(b) => Burger.toPrice(b);

let toEmoji =
  fun
  | Hotdog => {js|🌭|js}
  | Sandwich(s) => Sandwich.toEmoji(s)
  | Burger(b) => Burger.toEmoji(b);

[@react.component]
let make = (~order: t) =>
  <tr className="order">
    <td className="emoji"> {order |> toEmoji |> React.string} </td>
    <td className="price"> {order |> toPrice |> Format.currency} </td>
  </tr>;
