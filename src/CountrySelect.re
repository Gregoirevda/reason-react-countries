[@bs.val] external require: string => string = "";
require("./sprite.css");

module SearchIcon {
  [@react.component]
  let make = (()) => <i
    style={ReactDOMRe.Style.make(~marginLeft="10px", ())}
    className="material-icons">{"search" |> React.string}</i>
}

module DropIcon {
  [@react.component]
  let make = (~up) => <i className="material-icons">{(up ? "arrow_drop_up" : "arrow_drop_down") |> React.string}</i>
}

let searchIconCallback = () => <SearchIcon />

let components: BsReactSelect.Select.components = {
  indicatorSeparator: None,
  dropdownIndicator: Some(searchIconCallback),
};

let customStyles: BsReactSelect.Select.styles = {
  valueContainer: (provided) => {
    let custom = ReactDOMRe.Style.make(~order="1", ());
    ReactDOMRe.Style.combine(provided, custom)
  },
  indicatorsContainer: (provided) => {
    let custom = ReactDOMRe.Style.make(~order="0", ());
    ReactDOMRe.Style.combine(provided, custom)
  }
}

let batch_countries_amount = 10;

[@react.component]
let make = (~className, ~country, ~onChange) => {
  // Mapping between interface option(string) and internal representation option(Country.t)
  let (internalCountry, setInternalCountry) = React.useState(() => None);
  // Full list of countries
  let (countries, setCountries) = React.useState(() => [||]);
  // List of countries displayed
  // Display 10 countries => 100ms (Goal)
  // Display 100 countries => 200ms
  // Display 241 (all) countries => ~300ms
  // Displaying only a set of countries makes it feel like the list is limited to that set.
  // Rendering countries in batches takes 150ms and the user has a full list. (No loading on infinite scroll or more complex code to handle)
  let (searchResult, setSearchResult) = React.useState(() => [||]);
  let (batchCountriesCurrentIndex, setBatchCountriesCurrentIndex) = React.useState(() => 0);
  let (showSelect, setShowSelect) = React.useState(() => false);
  let onKeyUp = event => {
    switch (ReactEvent.Keyboard.keyCode(event)) {
      | 13 => setShowSelect(_ => true)
      | 27 => setShowSelect(_ => false)
      | _ => ()
    };
  };

  React.useEffect0(() => {
      Api.Country.getAll()
        |> Js.Promise.then_(countries => {
          setCountries(_ => countries); 
          setSearchResult(_ => Js.Array.slice(~start=batchCountriesCurrentIndex, ~end_=batch_countries_amount, countries))
          setBatchCountriesCurrentIndex(batchIndex => batchIndex + batch_countries_amount);
          Js.Promise.resolve();
        })
        |> ignore;
    None;
  });

  React.useEffect2(() => {
      if(!showSelect && Js.Array.length(countries) > 0 && Js.Array.length(searchResult) > batch_countries_amount) {
        setSearchResult(searchResult => Js.Array.slice(~start=0, ~end_=batch_countries_amount, countries));
        setBatchCountriesCurrentIndex(_ => batch_countries_amount)
      }
      if(showSelect && Js.Array.length(countries) > 0 && batchCountriesCurrentIndex < Js.Array.length(countries)) {
      setSearchResult(searchResult => Js.Array.concat(Js.Array.slice(~start=batchCountriesCurrentIndex, ~end_=(batchCountriesCurrentIndex+ batch_countries_amount), countries), searchResult));
      setBatchCountriesCurrentIndex(batchIndex => batchIndex + batch_countries_amount)
      }
      None;
  }, (batchCountriesCurrentIndex, showSelect))

  React.useEffect2(() => {
    switch country {
      | None => setInternalCountry(_ => None)
      | Some(country) => {
        let internalCountry = Js.Array.find((item: Api.Country.t) => item.value == country, countries)
        setInternalCountry(_ => internalCountry)
      }
    };
    None;
  }, (country, countries));

  <div style={ReactDOMRe.Style.make(~width="20vmax", ~minHeight="100px", ())}>
    <div 
      tabIndex={0}
      style={ReactDOMRe.Style.make(~width="10vmax", ~height="36px", ~border="1px solid rgb(204, 204, 204)", ~display="flex", ~alignItems="center", ~justifyContent="space-between", ~paddingLeft="10px", ~marginBottom="10px", ~borderRadius="3px", ())}
      onClick={_ => {
        setShowSelect(showSelect => !showSelect)
      }}
      onKeyUp={onKeyUp}
    >
      <span>{
        switch (internalCountry: option(Api.Country.t))  {
          | None => "" |> React.string
          | Some(country) => country.label |> React.string
        }
      }
      </span>
      <DropIcon up={!showSelect} />
    </div>
    {showSelect ? <BsReactSelect.Select 
        autoFocus={true}
        value={internalCountry} 
        onChange={newCountry => {
          setShowSelect(_ => false)
          setInternalCountry(_ => newCountry)
          switch newCountry {
            | None => onChange(None)
            | Some(country) => onChange(Some(country.value))
          }
        }} 
        options={searchResult} 
        isSearchable={true}
        placeholder="Search"
        components={components}
        hideSelectedOptions={false}
        menuIsOpen={true}
        onBlur={(event) => {
            // TODO remaining bug: when select is shown, clicking on button shows it again, because mouse event propagtes
        //    ReactEvent.Mouse.preventDefault(event);
        //    ReactEvent.Mouse.stopPropagation(event);
          setShowSelect(_ => false) 
        }}
        styles={customStyles}
        onKeyDown={onKeyUp}
        controlShouldRenderValue={false}
        isClearable={false}
        backspaceRemovesValue={false}
        getOptionValue={country => country.label}
        getOptionLabel={country => <div style={ReactDOMRe.Style.make(~display="flex", ~justifyContent="center", ())}>
// too many http calls        <div style={ReactDOMRe.Style.make(~display="inline-block",~marginRight="10px",  ~height="18px", ~width="24px", ())} className={"flag flag-icon-background flag-icon-" ++ country.value}></div>
         // requires polyfill for IE <svg className="icon icon-af"><use xlinkHref="./assets/symbol-defs.svg#icon-af"></use></svg>
          <span style={ReactDOMRe.Style.make(~marginRight="10px", ())} className={"icon icon-" ++ country.value}></span> // SVG sprite
          <div style={ReactDOMRe.Style.make(~flexGrow="2", ())}>{country.label |> React.string}</div>
          </div>
        }
      /> : <span />}
  </div>
}

