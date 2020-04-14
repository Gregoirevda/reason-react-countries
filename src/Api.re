module Country {
  type t = {
    label: string,
    value: string
  }

  module Decode {  

    let country = json => {
      Json.Decode.{
        label: json |> field("label", string),
        value: json |> field("value", string)
      }
    }

    let countries = json => json |> Json.Decode.(array(country));
  }


  let getAll = () => {
    Js.Promise.(
      Fetch.fetch("https://gist.githubusercontent.com/rusty-key/659db3f4566df459bd59c8a53dc9f71f/raw/4127f9550ef063121c564025f6d27dceeb279623/counties.json")
      |> then_(Fetch.Response.json)
      |> then_(json => json |> Decode.countries |> resolve)
    )
  }
}
