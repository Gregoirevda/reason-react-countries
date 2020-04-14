[@react.component]
let make = () => {
  let (country, setCountry) = React.useState(() => Some("us"));
  Js.log2("Selected country", country);
  
  <div style={ReactDOMRe.Style.make(~height="100%", ~display="flex", ~alignItems="center", ~justifyContent="center", ())}>
    <CountrySelect 
      className="test"
      country
      onChange={newCountry => setCountry(_ => newCountry)}
    />
//  <button onClick={_ => setCountry(_ => Some("be"))}>{"TEST ME" |> React.string}</button>
  </div>
}
