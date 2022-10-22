#include "ropp.h"
#include "../include/request.hpp"

std::string RoPP::Session::GetCSRF()
{
    Request req("https://auth.roblox.com/v1/authentication-ticket");
    req.set_cookie(".ROBLOSECURITY", this->Cookie);
    req.set_header("Referer", "https://www.roblox.com/");
    req.initalize();
    Response res = req.post();

    return res.headers["x-csrf-token"];
}

std::string RoPP::Session::GetAuthTicket()
{
    Request req("https://auth.roblox.com/v1/authentication-ticket");
    req.set_cookie(".ROBLOSECURITY", this->Cookie);
    req.set_header("Referer", "https://www.roblox.com/");
    req.initalize();
    Response res = req.post();

    string csrfToken = res.headers["x-csrf-token"];
    req.set_header("x-csrf-token", csrfToken);

    res = req.post();
    string ticket = res.headers["rbx-authentication-ticket"];
    return ticket;
}

long RoPP::Session::GetUserID()
{
    Request req("https://users.roblox.com/v1/users/authenticated");
    req.set_cookie(".ROBLOSECURITY", this->Cookie);
    req.set_header("Referer", "https://www.roblox.com/");
    req.initalize();
    Response res = req.get();

    return json::parse(res.data)["id"];
}

std::string RoPP::Session::GetUsername()
{
    Request req("https://users.roblox.com/v1/users/authenticated");
    req.set_cookie(".ROBLOSECURITY", this->Cookie);
    req.set_header("Referer", "https://www.roblox.com/");
    req.initalize();
    Response res = req.get();

    return json::parse(res.data)["name"];
}

void RoPP::Session::SetCookie(std::string cookie)
{
    this->Cookie = cookie;
}

json RoPP::Session::GetBirthDate()
{
    Request req("https://accountinformation.roblox.com/v1/birthdate");
    req.set_cookie(".ROBLOSECURITY", this->Cookie);
    req.set_header("Referer", "https://www.roblox.com/");
    req.initalize();
    Response res = req.get();

    return json::parse(res.data);
}

std::string RoPP::Session::GetDescription()
{
    Request req("https://accountinformation.roblox.com/v1/description");
    req.set_cookie(".ROBLOSECURITY", this->Cookie);
    req.set_header("Referer", "https://www.roblox.com/");
    req.initalize();
    Response res = req.get();

    return json::parse(res.data)["description"];
}