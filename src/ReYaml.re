module LoadOptions = {
  module Schema = {
    type t;
    let failsafe: t = [%bs.raw {|"FAILSAFE_SCHEMA"|}];
    let json: t = [%bs.raw {|"JSON_SCHEMA"|}];
    let core: t = [%bs.raw {|"CORE_SCHEMA"|}];
    let defaultSafe: t = [%bs.raw {|"DEFAULT_SAFE_SCHEMA"|}];
    let defaultFull: t = [%bs.raw {|"DEFAULT_FULL_SCHEMA"|}];
  };

  [@bs.deriving abstract]
  type t = {
    [@bs.optional] filename: string,
    [@bs.optional] onWarning: Js.Exn.t => unit,
    [@bs.optional] schema: Schema.t,
    [@bs.optional] json: bool,
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
