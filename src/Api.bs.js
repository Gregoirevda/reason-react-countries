'use strict';

var Json_decode = require("@glennsl/bs-json/src/Json_decode.bs.js");

function country(json) {
  return {
          label: Json_decode.field("label", Json_decode.string, json),
          value: Json_decode.field("value", Json_decode.string, json)
        };
}

function countries(json) {
  return Json_decode.array(country, json);
}

var Decode = {
  country: country,
  countries: countries
};

function getAll(param) {
  return fetch("https://gist.githubusercontent.com/rusty-key/659db3f4566df459bd59c8a53dc9f71f/raw/4127f9550ef063121c564025f6d27dceeb279623/counties.json").then((function (prim) {
                  return prim.json();
                })).then((function (json) {
                return Promise.resolve(Json_decode.array(country, json));
              }));
}

var Country = {
  Decode: Decode,
  getAll: getAll
};

exports.Country = Country;
/* No side effect */
