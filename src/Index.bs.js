'use strict';

var React = require("react");
var ReactDOMRe = require("reason-react/src/ReactDOMRe.js");
var App$CountriesList = require("./App.bs.js");

ReactDOMRe.renderToElementWithId(React.createElement(App$CountriesList.make, { }), "root");

/*  Not a pure module */
