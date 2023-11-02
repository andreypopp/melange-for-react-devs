module App = {
  let orders: Orders.t = [|
    Sandwich(Portabello),
    Hotdog,
    Burger({lettuce: true, tomatoes: true, bacon: 2, onions: 3, cheese: 1}),
    Sandwich(Unicorn),
    Burger({lettuce: false, tomatoes: false, bacon: 0, onions: 0, cheese: 0}),
  |];

  [@react.component]
  let make = () =>
    <div>
      <h1> {React.string("Order confirmation")} </h1>
      <Orders orders />
      <h2> {React.string("Remove")} </h2>
      <Orders_Remove orders />
      <h2> {React.string("Remove")} </h2>
      <Orders_List orders={orders |> Array.to_list} />
    </div>;
};

let node = ReactDOM.querySelector("#root");
switch (node) {
| None =>
  Js.Console.error("Failed to start React: couldn't find the #root element")
| Some(root) => ReactDOM.render(<App />, root)
};
