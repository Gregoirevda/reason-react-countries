'use strict';

var Curry = require("bs-platform/lib/js/curry.js");
var React = require("react");
var CountrySelect$ReasonReactExamples = require("./CountrySelect.bs.js");

function App(Props) {
  var match = React.useState((function () {
          return "us";
        }));
  var setCountry = match[1];
  var country = match[0];
  console.log("Selected country", country);
  return React.createElement("div", {
              style: {
                display: "flex",
                height: "100%",
                alignItems: "center",
                justifyContent: "center"
              }
            }, React.createElement(CountrySelect$ReasonReactExamples.make, {
                  className: "test",
                  country: country,
                  onChange: (function (newCountry) {
                      return Curry._1(setCountry, (function (param) {
                                    return newCountry;
                                  }));
                    })
                }));
}

var make = App;

exports.make = make;
/* react Not a pure module */
