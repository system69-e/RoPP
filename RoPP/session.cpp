#include "../include/ropp.h"
#include "../include/helper.h"
#include "../include/request.hpp"
#include "../include/responses.h"

Responses::BirthdateResponse RoPP::Session::GetBirthDate()
{
    ordered_json res = Helper::MakeAuthedRobloxRequest
    (
        "https://accountinformation.roblox.com/v1/birthdate",
        "GET",
        this->m_Cookie,
        CSRF_REQUIRED
    ).JsonObj;

    return Responses::BirthdateResponse(res);
}

std::string RoPP::Session::GetDescription()
{
    ordered_json res = Helper::MakeAuthedRobloxRequest
    (
        "https://accountinformation.roblox.com/v1/description",
        "GET",
        this->m_Cookie,
        CSRF_REQUIRED
    ).JsonObj;

    return res["description"];
}

Responses::PhoneInfo RoPP::Session::GetPhoneInfo()
{
    ordered_json res = Helper::MakeAuthedRobloxRequest
    (
        "https://accountinformation.roblox.com/v1/phone",
        "GET",
        this->m_Cookie,
        CSRF_REQUIRED
    ).JsonObj;

    return Responses::PhoneInfo(res);
}

long RoPP::Session::GetRobuxBalance()
{
    ordered_json res = Helper::MakeAuthedRobloxRequest
    (
        "https://economy.roblox.com/v1/users/" + std::to_string(this->GetUserID()) + "/currency",
        "GET",
        this->m_Cookie,
        CSRF_REQUIRED
    ).JsonObj;

    return res["robux"];
}

bool RoPP::Session::HasPremium()
{
    ordered_json res = Helper::MakeAuthedRobloxRequest
    (
        "https://premiumfeatures.roblox.com/v1/users/" + std::to_string(this->GetUserID()) + "/validate-membership",
        "GET",
        this->m_Cookie,
        CSRF_NOT_REQUIRED
    ).JsonObj;

    return res;
}

int RoPP::Session::GetFriendsCount()
{
    ordered_json res = Helper::MakeAuthedRobloxRequest
    (
        "https://friends.roblox.com/v1/my/friends/count",
        "GET",
        this->m_Cookie,
        CSRF_NOT_REQUIRED
    ).JsonObj;

    return res["count"];
}

Responses::FriendRequestsResponse RoPP::Session::GetFriendRequests(std::string Sort, int Limit)
{
    ordered_json res = Helper::MakeAuthedRobloxRequest
    (
        "https://friends.roblox.com/v1/my/friends/requests?" + Sort + "&limit=" + std::to_string(Limit),
        "GET",
        this->m_Cookie,
        CSRF_REQUIRED
    ).JsonObj;

    return Responses::FriendRequestsResponse(res);
}

bool RoPP::Session::IsFavoriteGame(int64_t PlaceID)
{
    int64_t UniverseID = RoPP::Other().get_game_universe_id(PlaceID);

    ordered_json res = Helper::MakeAuthedRobloxRequest
    (
        "https://games.roblox.com/v1/games/" + std::to_string(UniverseID) + "/favorites",
        "GET",
        this->m_Cookie,
        CSRF_NOT_REQUIRED
    ).JsonObj;

    return res["isFavorited"];
}

void RoPP::Session::SetFavoriteGame(int PlaceID, bool Favorite)
{
    int64_t UniverseID = RoPP::Other().get_game_universe_id(PlaceID);

    json data = 
    {
        {"isFavorited", Favorite}
    };

    ordered_json res = Helper::MakeAuthedRobloxRequest
    (
        "https://games.roblox.com/v1/games/" + std::to_string(UniverseID) + "/favorites",
        "POST",
        this->m_Cookie,
        CSRF_REQUIRED,
        data
    ).JsonObj;
}

double RoPP::Session::UnlockPin(int Pin)
{
    json data = 
    {
        {"pin", Pin}
    };

    ordered_json res = Helper::MakeAuthedRobloxRequest
        (
            "https://auth.roblox.com/v1/account/pin/unlock",
            "POST",
            this->m_Cookie,
            CSRF_NOT_REQUIRED,
            data
        ).JsonObj;


    return res["unlockedUntil"]; 
}

bool RoPP::Session::LockPin()
{
    ordered_json res = Helper::MakeAuthedRobloxRequest
    (
        "https://auth.roblox.com/v1/account/pin/lock",
        "POST",
        this->m_Cookie,
        CSRF_NOT_REQUIRED
    ).JsonObj;

    return res["success"];
}

void RoPP::Session::ChangePassword(std::string OldPassword, std::string NewPassword)
{
    json data = 
    {
        {"currentPassword", OldPassword},
        {"newPassword", NewPassword}
    };

    Helper::WebResponse res = Helper::MakeAuthedRobloxRequest
    (
        "https://auth.roblox.com/v2/user/passwords/change",
        "POST",
        this->m_Cookie,
        CSRF_REQUIRED,
        data
    );

    if (!res.Res.cookies.empty())
    {
        if (res.Res.cookies.count(".ROBLOSECURITY") == 1)
        {
            this->m_Cookie = res.Res.cookies[".ROBLOSECURITY"];
        }
    }
}

bool RoPP::Session::SendFriendRequest(long UID)
{
    json data = 
    {
        {"friendshipOriginSourceType", "Unknown"}
    };

    ordered_json res = Helper::MakeAuthedRobloxRequest
    (
        "https://friends.roblox.com/v1/users/" + std::to_string(UID) + "/request-friendship",
        "POST",
        this->m_Cookie,
        CSRF_REQUIRED,
        data
    ).JsonObj;

    return res["success"];
}

void RoPP::Session::AcceptFriendRequest(long UID)
{
    ordered_json res = Helper::MakeAuthedRobloxRequest
    (
        "https://friends.roblox.com/v1/users/" + std::to_string(UID) + "/accept-friend-request",
        "POST",
        this->m_Cookie,
        CSRF_REQUIRED
    ).JsonObj;
}

void RoPP::Session::DeclineFriendRequest(long UID)
{
    ordered_json res = Helper::MakeAuthedRobloxRequest
    (
        "https://friends.roblox.com/v1/users/" + std::to_string(UID) + "/accept-friend-request",
        "POST",
        this->m_Cookie,
        CSRF_REQUIRED
    ).JsonObj;
}

void RoPP::Session::DeclineAllFriendRequests()
{
    ordered_json res = Helper::MakeAuthedRobloxRequest
    (
        "https://friends.roblox.com/v1/user/friend-requests/decline-all",
        "POST",
        this->m_Cookie,
        CSRF_REQUIRED
    ).JsonObj;
}

void RoPP::Session::BlockUser(long UID)
{
    ordered_json res = Helper::MakeAuthedRobloxRequest
    (
        "https://accountsettings.roblox.com/v1/users/" + std::to_string(UID) + "/block",
        "POST",
        this->m_Cookie,
        CSRF_REQUIRED
    ).JsonObj;
}

void RoPP::Session::UnblockUser(long UID)
{
    ordered_json res = Helper::MakeAuthedRobloxRequest
    (
        "https://accountsettings.roblox.com/v1/users/" + std::to_string(UID) + "/unblock",
        "POST",
        this->m_Cookie,
        CSRF_REQUIRED
    ).JsonObj;
}

void RoPP::Session::SetDescription(std::string Description)
{
    json data = 
    {
        {"description", Description}
    };

    ordered_json res = Helper::MakeAuthedRobloxRequest
    (
        "https://accountinformation.roblox.com/v1/description",
        "POST",
        this->m_Cookie,
        CSRF_REQUIRED,
        data
    ).JsonObj;
}

void RoPP::Session::SetGender(std::string Gender)
{
    json data = 
    {
        {"gender", Gender}
    };

    ordered_json res = Helper::MakeAuthedRobloxRequest
    (
        "https://accountinformation.roblox.com/v1/gender",
        "POST",
        this->m_Cookie,
        CSRF_REQUIRED,
        data
    ).JsonObj;
}

std::vector<Responses::FriendsOnline> RoPP::Session::GetFriendsOnline()
{
    ordered_json res = Helper::MakeAuthedRobloxRequest
    (
        "https://friends.roblox.com/v1/users/" + std::to_string(this->GetUserID()) + "/friends/online",
        "GET",
        this->m_Cookie,
        CSRF_REQUIRED
    ).JsonObj;

    std::vector<Responses::FriendsOnline> Friends;
    for (size_t i = 0; i < res["data"].size(); i++)
    {
        Friends.push_back(Responses::FriendsOnline(res["data"][i]));
    }

    return Friends;
}

Responses::User RoPP::Session::GetUser()
{
    ordered_json res = Helper::MakeAuthedRobloxRequest
    (
        "https://users.roblox.com/v1/users/" + std::to_string(this->GetUserID()),
        "GET",
        this->m_Cookie,
        CSRF_REQUIRED
    ).JsonObj;

    return Responses::User(res);
}

long RoPP::Session::GetUserID()
{
    ordered_json res = Helper::MakeAuthedRobloxRequest
    (
        "https://users.roblox.com/v1/users/authenticated",
        "GET",
        this->m_Cookie,
        CSRF_REQUIRED
    ).JsonObj;
    
    return res["id"];
}