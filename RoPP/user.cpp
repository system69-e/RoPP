#include "ropp.h"
#include "../include/helper.h"
#include "../include/request.hpp"
#include "../include/responses.h"

FriendsResponse RoPP::User::GetFriends(string Sort)
{
   json res = Helper::MakeRobloxRequest
    (
        "https://friends.roblox.com/v1/users/" + std::to_string(this->UID) + "/friends?userSort=" + Sort,
        "GET"
    ).JsonObj;

    return FriendsResponse().Parse(res);
}

FollowersResponse RoPP::User::GetFollowers(string Sort, int Limit)
{
    json res = Helper::MakeRobloxRequest
    (
        "https://friends.roblox.com/v1/users/" + std::to_string(this->UID) + "/followers?sortOrder=" + Sort + "&limit=" + std::to_string(Limit),
        "GET"
    ).JsonObj;

    return FollowersResponse().Parse(res);
}

FollowingsResponse RoPP::User::GetFollowings(string Sort, int Limit)
{
    json res = Helper::MakeRobloxRequest
    (
        "https://friends.roblox.com/v1/users/" + std::to_string(this->UID) + "/followings?sortOrder=" + Sort + "&limit=" + std::to_string(Limit),
        "GET"
    ).JsonObj;

    return FollowingsResponse().Parse(res);
}

int RoPP::User::GetFriendsCount()
{
    json res = Helper::MakeRobloxRequest
    (
        "https://friends.roblox.com/v1/users/" + std::to_string(this->UID) + "/friends/count",
        "GET"
    ).JsonObj;

    return res["count"];
}

int RoPP::User::GetFollowersCount()
{
    json res = Helper::MakeRobloxRequest
    (
        "https://friends.roblox.com/v1/users/" + std::to_string(this->UID) + "/followers/count",
        "GET"
    ).JsonObj;

    return res["count"];
}

int RoPP::User::GetFollowingsCount()
{
    json res = Helper::MakeRobloxRequest
    (
        "https://friends.roblox.com/v1/users/" + std::to_string(this->UID) + "/followings/count",
        "GET"
    ).JsonObj;

    return res["count"];
}

std::string RoPP::User::GetUsername()
{
    json res = Helper::MakeRobloxRequest
    (
        "https://users.roblox.com/v1/users/" + std::to_string(this->UID),
        "GET"
    ).JsonObj;

    return res["name"];
}

std::string RoPP::User::GetDisplayName()
{
    json res = Helper::MakeRobloxRequest
    (
        "https://users.roblox.com/v1/users/" + std::to_string(this->UID),
        "GET"
    ).JsonObj;

    return res["displayName"];
}

std::string RoPP::User::GetDescription()
{
    json res = Helper::MakeRobloxRequest
    (
        "https://users.roblox.com/v1/users/" + std::to_string(this->UID),
        "GET"
    ).JsonObj;

    return res["description"];
}

json RoPP::User::GetGroups()
{
    json res = Helper::MakeRobloxRequest
    (
        "https://groups.roblox.com/v1/users/" + std::to_string(this->UID) + "/groups/roles",
        "GET"
    ).JsonObj;

    return res;
}

int RoPP::User::GetGroupsCount()
{
    json res = Helper::MakeRobloxRequest
    (
        "https://groups.roblox.com/v1/users/" + std::to_string(this->UID) + "/groups/roles",
        "GET"
    ).JsonObj;

    return res["data"].size();
}

json RoPP::User::GetBadges()
{
    json res = Helper::MakeRobloxRequest
    (
        "https://badges.roblox.com/v1/users/" + std::to_string(this->UID) + "/badges",
        "GET"
    ).JsonObj;

    return res;
}

int RoPP::User::GetBadgesCount()
{
    json res = Helper::MakeRobloxRequest
    (
        "https://badges.roblox.com/v1/users/" + std::to_string(this->UID) + "/badges",
        "GET"
    ).JsonObj;

    return res["data"].size();
}

std::string RoPP::User::GetCreationDate()
{
    json res = Helper::MakeRobloxRequest
    (
        "https://users.roblox.com/v1/users/" + std::to_string(this->UID),
        "GET"
    ).JsonObj;

    return res["created"];
}

UserExperienceResponse RoPP::User::GetExperiences(string Sort, int limit)
{
    json res = Helper::MakeRobloxRequest
    (
        "https://games.roblox.com/v2/users/" + std::to_string(this->UID) + "/games?sortOrder=" + Sort + "&limit=" + std::to_string(limit),
        "GET"
    ).JsonObj;

    return UserExperienceResponse().Parse(res);
}

UserFavoriteExperiences RoPP::User::GetFavoriteExperiences(string Sort, int limit)
{
    json res = Helper::MakeRobloxRequest
    (
        "https://games.roblox.com/v2/users/" + std::to_string(this->UID) + "/favorite/games?sortOrder=" + Sort + "&limit=" + std::to_string(limit),
        "GET"
    ).JsonObj;

    return UserFavoriteExperiences().Parse(res);
}

json RoPP::User::GetPresence()
{
    json data = 
    {
        {"userIds", {this->UID}}
    };

    json res = Helper::MakeRobloxRequest
    (
        "https://presence.roblox.com/v1/presence/users",
        "POST",
        data
    ).JsonObj;

    return res;
}

json RoPP::User::GetPastUsernames(string Sort, int limit)
{
    json res = Helper::MakeRobloxRequest
    (
        "https://users.roblox.com/v1/users/" + std::to_string(this->UID) + "/usernames?sortOrder=" + Sort + "&limit=" + std::to_string(limit),
        "GET"
    ).JsonObj;

    return res;
}

json RoPP::User::GetPrimaryGroup()
{
    json res = Helper::MakeRobloxRequest
    (
        "https://groups.roblox.com/v1/users/" + std::to_string(this->UID) + "/primary-group",
        "GET"
    ).JsonObj;

    return res;
}

json RoPP::User::GetInventory(string AssetType, string Sort, int Limit)
{
    json res = Helper::MakeRobloxRequest
    (
        "https://inventory.roblox.com/v1/users/" + std::to_string(this->UID) + "/assets/" + AssetType + "?sortOrder=" + Sort + "&limit=" + std::to_string(Limit),
        "GET"
    ).JsonObj;

    return res;
}

bool RoPP::User::CanInventoryBeViewed()
{
    json res = Helper::MakeRobloxRequest
    (
        "https://inventory.roblox.com/v1/users/" + std::to_string(this->UID) + "/can-view-inventory",
        "GET"
    ).JsonObj;

    return res["canView"];
}

json RoPP::User::GetCurrentlyWearing()
{
    return Helper::MakeRobloxRequest
    (
        "https://avatar.roblox.com/v1/users/" + std::to_string(this->UID) + "/currently-wearing",
        "GET"
    ).JsonObj;;
}

json RoPP::User::GetAvatar()
{
    return Helper::MakeRobloxRequest
    (
        "https://avatar.roblox.com/v1/users/" + std::to_string(this->UID) + "/avatar",
        "GET"
    ).JsonObj;;
}