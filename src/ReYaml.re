module LoadOptions = {
  type schema;
  let failsafeSchema: schema = [%bs.raw {|"FAILSAFE_SCHEMA"|}];
  let jsonSchema: schema = [%bs.raw {|"JSON_SCHEMA"|}];
  let coreSchema: schema = [%bs.raw {|"CORE_SCHEMA"|}];
  let defaultSafeSchema: schema = [%bs.raw {|"DEFAULT_SAFE_SCHEMA"|}];
  let defaultFullSchema: schema = [%bs.raw {|"DEFAULT_FULL_SCHEMA"|}];

  [@bs.deriving abstract]
  type t = {
    [@bs.optional]
    filename: string,
    [@bs.optional]
    onWarning: Js.Exn.t => unit,
    [@bs.optional]
    schema,
    [@bs.optional]
    json: bool,
  };
};

[@bs.module "js-yaml"] external safeLoadExn: string => Js.Json.t = "safeLoad";
[@bs.module "js-yaml"]
external safeLoadWithOptionsExn: (string, LoadOptions.t) => Js.Json.t =
  "safeLoad";

[@bs.module "js-yaml"]
external safeLoadAllExn: string => array(Js.Json.t) = "safeLoadAll";
[@bs.module "js-yaml"]
external safeLoadAllWithOptionsExn:
  (string, LoadOptions.t) => array(Js.Json.t) =
  "safeLoadAll";

let safeLoad = data =>
  try (Belt.Result.Ok(safeLoadExn(data))) {
  | exn => Belt.Result.Error(Js.String.make(exn))
  };

let safeLoadWithOptions = (data, options) =>
  try (Belt.Result.Ok(safeLoadWithOptionsExn(data, options))) {
  | exn => Belt.Result.Error(Js.String.make(exn))
  };
