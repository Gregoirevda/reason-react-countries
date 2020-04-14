module Select {

  type componentProps = {
    innerProps: Js.Json.t
  };

  type components = {
    [@bs.as "IndicatorSeparator"] indicatorSeparator: option(unit => React.element),
    [@bs.as "DropdownIndicator"] dropdownIndicator: option(unit => React.element),
    //[@bs.as "Option"] _option: componentProps => React.element
  };

  type style = ReactDOMRe.Style.t => ReactDOMRe.Style.t

  type styles = {
    valueContainer: style,
    indicatorsContainer: style
  };

  [@bs.module "react-select"] [@react.component]
  external make: (
    ~onChange: option('a) => unit,
    ~options: array('a),
    ~value: option('a),
    ~className: string=?,
    ~isSearchable: bool=?,
    ~placeholder: string=?,
    ~width: string=?,
    ~isSearchable: bool=?,
    ~controlShouldRenderValue: bool=?,
    ~backspaceRemovesValue: bool=?,
    ~isClearable: bool=?,
    ~autoFocus: bool=?,
    ~components: components=?,
    ~style: ReactDOMRe.Style.t=?,
    ~hideSelectedOptions: bool=?,
    ~menuIsOpen: bool=?,
    ~onBlur: ReactEvent.Mouse.t => unit=?,
    ~getOptionLabel: 'a => React.element=?,
    ~getOptionValue: 'a => string=?,
    ~controlShouldRenderValue: bool=?,
    ~onKeyDown: ReactEvent.Keyboard.t => unit=?,
    ~styles: styles=?,
    ~ref: ReactDOMRe.Ref.t=?
  ) => React.element = "default"

};


/* 
   Tried to pass theme to the button used in react-select without success, leaving it here as reference
  Shows why the extra Select module scrope is usefull => default export
 */
[@bs.module "react-select"]
external defaultTheme: Js.Json.t = "defaultTheme";


type theme = {
  [@bs.as "ButtonStyles"] buttonStyles: Js.Json.t
}

let defaultButtonTheme = {
  buttonStyles: defaultTheme
};

