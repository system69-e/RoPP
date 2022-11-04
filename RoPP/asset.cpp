#include "ropp.h"
#include "../include/helper.h"
#include "../include/request.hpp"
#include "../include/responses.h"

AssetInfo RoPP::Asset::GetAssetInfo()
{
    AssetInfo AssetInfo;
    Request req("https://economy.roblox.com/v2/assets/" + std::to_string(this->AID) + "/details");
    req.set_header("Referer", "https://www.roblox.com/");
    req.initalize();

    Response res = req.get();

    return AssetInfo.Parse(json::parse(res.data));

    //url for asset info: https://economy.roblox.com/v2/assets/440739240/details
}

json RoPP::Asset::GetAssetOwners(string Sort, int Limit)
{
    Request req("https://inventory.roblox.com/v2/assets/" + std::to_string(this->AID) + "/owners?" + Sort + "&limit=" + std::to_string(Limit));
    req.set_header("Referer", "https://www.roblox.com/");
    req.initalize();

    Response res = req.get();

    return json::parse(res.data);
    //url for asset id 440739240 is https://inventory.roblox.com/v2/assets/440739240/owners?sortOrder=Asc&limit=10
}

void RoPP::Asset::SetCookie(string Cookie)
{
    this->Cookie = Cookie;
}

json RoPP::Asset::GetAssetResellers(string Sort, int Limit)
{
    return Helper::MakeAuthedRobloxRequest
    (
        "https://economy.roblox.com/v1/assets/" + std::to_string(this->AID) + "/resellers?" + Sort + "&limit=" + std::to_string(Limit),
        "GET",
        this->Cookie
    ).JsonObj;
}

json RoPP::Asset::GetResaleData()
{
    return Helper::MakeAuthedRobloxRequest
    (
        "https://economy.roblox.com/v1/assets/" + std::to_string(this->AID) + "/resale-data",
        "GET",
        this->Cookie
    ).JsonObj;
}