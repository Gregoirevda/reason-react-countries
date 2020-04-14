'use strict';

var Curry = require("bs-platform/lib/js/curry.js");
var React = require("react");
var ReactDOMRe = require("reason-react/src/ReactDOMRe.js");
var Caml_option = require("bs-platform/lib/js/caml_option.js");
var ReactSelect = require("react-select");
var Api$ReasonReactExamples = require("./Api.bs.js");

require("./sprite.css");

function CountrySelect$SearchIcon(Props) {
  return React.createElement("i", {
              className: "material-icons",
              style: {
                marginLeft: "10px"
              }
            }, "search");
}

var SearchIcon = {
  make: CountrySelect$SearchIcon
};

function CountrySelect$DropIcon(Props) {
  var up = Props.up;
  return React.createElement("i", {
              className: "material-icons"
            }, up ? "arrow_drop_up" : "arrow_drop_down");
}

var DropIcon = {
  make: CountrySelect$DropIcon
};

function searchIconCallback(param) {
  return React.createElement(CountrySelect$SearchIcon, { });
}

var components_DropdownIndicator = searchIconCallback;

var components = {
  IndicatorSeparator: undefined,
  DropdownIndicator: components_DropdownIndicator
};

function customStyles_valueContainer(provided) {
  var custom = {
    order: "1"
  };
  return ReactDOMRe.Style.combine(provided, custom);
}

function customStyles_indicatorsContainer(provided) {
  var custom = {
    order: "0"
  };
  return ReactDOMRe.Style.combine(provided, custom);
}

var customStyles = {
  valueContainer: customStyles_valueContainer,
  indicatorsContainer: customStyles_indicatorsContainer
};

function CountrySelect(Props) {
  Props.className;
  var country = Props.country;
  var onChange = Props.onChange;
  var match = React.useState((function () {
          return ;
        }));
  var setInternalCountry = match[1];
  var internalCountry = match[0];
  var match$1 = React.useState((function () {
          return [];
        }));
  var setCountries = match$1[1];
  var countries = match$1[0];
  var match$2 = React.useState((function () {
          return [];
        }));
  var setSearchResult = match$2[1];
  var searchResult = match$2[0];
  var match$3 = React.useState((function () {
          return 0;
        }));
  var setBatchCountriesCurrentIndex = match$3[1];
  var batchCountriesCurrentIndex = match$3[0];
  var match$4 = React.useState((function () {
          return false;
        }));
  var setShowSelect = match$4[1];
  var showSelect = match$4[0];
  var onKeyUp = function ($$event) {
    var match = $$event.keyCode;
    if (match !== 13) {
      if (match !== 27) {
        return /* () */0;
      } else {
        return Curry._1(setShowSelect, (function (param) {
                      return false;
                    }));
      }
    } else {
      return Curry._1(setShowSelect, (function (param) {
                    return true;
                  }));
    }
  };
  React.useEffect((function () {
          Api$ReasonReactExamples.Country.getAll(/* () */0).then((function (countries) {
                  Curry._1(setCountries, (function (param) {
                          return countries;
                        }));
                  Curry._1(setSearchResult, (function (param) {
                          return countries.slice(batchCountriesCurrentIndex, 10);
                        }));
                  Curry._1(setBatchCountriesCurrentIndex, (function (batchIndex) {
                          return batchIndex + 10 | 0;
                        }));
                  return Promise.resolve(/* () */0);
                }));
          return ;
        }), ([]));
  React.useEffect((function () {
          if (!showSelect && countries.length > 0 && searchResult.length > 10) {
            Curry._1(setSearchResult, (function (searchResult) {
                    return countries.slice(0, 10);
                  }));
            Curry._1(setBatchCountriesCurrentIndex, (function (param) {
                    return 10;
                  }));
          }
          if (showSelect && countries.length > 0 && batchCountriesCurrentIndex < countries.length) {
            Curry._1(setSearchResult, (function (searchResult) {
                    return searchResult.concat(countries.slice(batchCountriesCurrentIndex, batchCountriesCurrentIndex + 10 | 0));
                  }));
            Curry._1(setBatchCountriesCurrentIndex, (function (batchIndex) {
                    return batchIndex + 10 | 0;
                  }));
          }
          return ;
        }), /* tuple */[
        batchCountriesCurrentIndex,
        showSelect
      ]);
  React.useEffect((function () {
          if (country !== undefined) {
            var country$1 = country;
            var internalCountry = countries.find((function (item) {
                    return item.value === country$1;
                  }));
            var internalCountry$1 = internalCountry === undefined ? undefined : Caml_option.some(internalCountry);
            Curry._1(setInternalCountry, (function (param) {
                    return internalCountry$1;
                  }));
          } else {
            Curry._1(setInternalCountry, (function (param) {
                    return ;
                  }));
          }
          return ;
        }), /* tuple */[
        country,
        countries
      ]);
  return React.createElement("div", {
              style: {
                minHeight: "100px",
                width: "20vmax"
              }
            }, React.createElement("div", {
                  style: {
                    border: "1px solid rgb(204, 204, 204)",
                    display: "flex",
                    height: "36px",
                    marginBottom: "10px",
                    paddingLeft: "10px",
                    width: "10vmax",
                    borderRadius: "3px",
                    alignItems: "center",
                    justifyContent: "space-between"
                  },
                  tabIndex: 0,
                  onKeyUp: onKeyUp,
                  onClick: (function (param) {
                      return Curry._1(setShowSelect, (function (showSelect) {
                                    return !showSelect;
                                  }));
                    })
                }, React.createElement("span", undefined, internalCountry !== undefined ? internalCountry.label : ""), React.createElement(CountrySelect$DropIcon, {
                      up: !showSelect
                    })), showSelect ? React.createElement(ReactSelect.default, {
                    onChange: (function (newCountry) {
                        Curry._1(setShowSelect, (function (param) {
                                return false;
                              }));
                        Curry._1(setInternalCountry, (function (param) {
                                return newCountry;
                              }));
                        if (newCountry !== undefined) {
                          return Curry._1(onChange, newCountry.value);
                        } else {
                          return Curry._1(onChange, undefined);
                        }
                      }),
                    options: searchResult,
                    value: internalCountry,
                    isSearchable: true,
                    placeholder: "Search",
                    controlShouldRenderValue: false,
                    backspaceRemovesValue: false,
                    isClearable: false,
                    autoFocus: true,
                    components: components,
                    hideSelectedOptions: false,
                    menuIsOpen: true,
                    onBlur: (function ($$event) {
                        return Curry._1(setShowSelect, (function (param) {
                                      return false;
                                    }));
                      }),
                    getOptionLabel: (function (country) {
                        return React.createElement("div", {
                                    style: {
                                      display: "flex",
                                      justifyContent: "center"
                                    }
                                  }, React.createElement("span", {
                                        className: "icon icon-" + country.value,
                                        style: {
                                          marginRight: "10px"
                                        }
                                      }), React.createElement("div", {
                                        style: {
                                          flexGrow: "2"
                                        }
                                      }, country.label));
                      }),
                    getOptionValue: (function (country) {
                        return country.label;
                      }),
                    onKeyDown: onKeyUp,
                    styles: customStyles
                  }) : React.createElement("span", undefined));
}

var batch_countries_amount = 10;

var make = CountrySelect;

exports.SearchIcon = SearchIcon;
exports.DropIcon = DropIcon;
exports.searchIconCallback = searchIconCallback;
exports.components = components;
exports.customStyles = customStyles;
exports.batch_countries_amount = batch_countries_amount;
exports.make = make;
/*  Not a pure module */
