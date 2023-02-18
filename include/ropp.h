#pragma once

#include <string>
#include <regex>

#include "json.hpp"
#include "responses.h"
#include "helper.h"

using json = nlohmann::json;

namespace RoPP
{
    class Auth
    {
        public:
            std::string get_csrf();
            std::string get_auth_ticket();
            std::string read_cookie();
            
            void set_cookie(std::string_view cookie);
        protected:
            std::string m_Cookie;

        private:
            void cookie_check();
    };

    class Avatar : public Auth
    {
        public:
            std::vector<long> get_currently_wearing(long user_id);
            Responses::AvatarResponse get_avatar(long user_id);
            Responses::OutfitDetailsResponse get_outfit_details(long outfit_id);
            Responses::GetOutfitsResponse get_outfits(long user_id, int page=1, int items_per_page=25, bool is_editable=false);

            bool set_body_colors(json colors);
            bool set_body_scales(json scales);
            bool set_player_avatar_type(std::string_view avatar_type);
            bool remove_asset(long asset_id);
            bool wear_asset(long asset_id);
    };
    
    class Asset : public Auth
    {
        public:
            json buy_asset();
            //TODO: buy limited

            Responses::AssetInfo get_asset_info();
            Responses::ResaleData get_resale_data();
            std::vector<Responses::ResellerData> get_asset_resellers(std::string sort="Asc", int limit=10);


        public:
            Asset(long asset_id, std::string_view cookie)
            {
                this->m_AssetID = asset_id;
                this->m_Cookie = cookie;
            }

            Asset(long asset_id)
            {
                this->m_AssetID = asset_id;
            }

            void set_asset_id(long asset_id)
            {
                this->m_AssetID = asset_id;
            }

        private:
            long m_AssetID = 0;
    };

    class Chat : public Auth
    {
        public:
            Responses::ConversationAddResponse add_users_to_conversation(std::vector<int64_t> user_ids);
            Responses::ChatSettings get_chat_settings();
            std::vector<Responses::ChatMessage> get_messages(int32_t page_size=10, std::string exclusive_start_messageid="");
            Responses::ChatConversationsResponse get_conversations(std::vector<int64_t> conversation_ids={});
            std::vector<Responses::RolloutFeature> get_rollout_features(std::vector<std::string> feature_names);
            int64_t get_unread_conversation_count();
            std::vector<Responses::ChatConversationWithMessages> get_unread_messages(std::vector<int64_t> conversation_ids={}, int32_t page_size=10);
            std::vector<Responses::ChatConversation> get_user_conversations(int32_t page_number=1, int32_t page_size=10);
            bool mark_conversation_as_read(std::string end_message_id);
            bool mark_conversation_as_seen(std::vector<int64_t> conversation_ids={});
            std::vector<Responses::ChatConversationWithMessages> multi_get_latest_messages(std::vector<int64_t> conversation_ids, int32_t page_size=10);
            Responses::RemoveFromConversationResponse remove_from_conversation(int64_t user_id);
            Responses::RenameGroupConversationResponse rename_group_conversation(std::string NewTitle);
            Responses::SendMessageResponse send_message(std::string message, bool is_experience_invite=false, std::vector<std::string> decorators={""});
            std::string update_user_typing_status(bool is_typing);
            Responses::OneToOneConversationResponse start_one_to_one_conversation(int64_t user_id);
            Responses::StartGroupConversationResponse start_group_conversation(std::vector<int64_t> user_id, std::string title);

        public:
            Chat(int64_t conversation_id, std::string_view cookie)
            {
                this->m_ConversationID = conversation_id;
                this->m_Cookie = cookie;
            }

            Chat(int64_t conversation_id)
            {
                this->m_ConversationID = conversation_id;
            }

            Chat(std::string_view cookie)
            {
                this->m_Cookie = cookie;
            }

            Chat()
            {
                this->m_ConversationID = 0;
            }

            void SetConversationID(long conversation_id)
            {
                this->m_ConversationID = conversation_id;
            }

        private:
            int64_t m_ConversationID = 0;
    };

    class Game : public Auth
    {
        public:
            Responses::PlaceInfoResponse GetPlaceInfo();
            std::vector<Responses::GamePass> GetGamepasses(std::string Sort="Asc", int Limit=10);
            std::vector<Responses::Badge> GetGameBadges(std::string Sort="Asc", int Limit=10);
            Responses::ExperienceVotes GetVotes();
            Responses::DeveloperProductCreateResponse CreateDeveloperProduct(std::string Name, std::string Description, long Price, long IconImageAssetID=0);
            std::vector<Responses::GameInstance> GetGameInstances(std::string Type="Public", std::string Sort="Asc", int Limit=100, bool ExcludeFullGames=false);
            Responses::GameSocialLinks GetSocialLinks();

            long GetUniverseID();


        public:
            Game(long PlaceID, std::string_view cookie)
            {
                this->PlaceID = PlaceID;
                this->UniverseID = GetUniverseID();
                this->m_Cookie = cookie;
            }

            Game(long PlaceID)
            {
                this->PlaceID = PlaceID;
                this->UniverseID = GetUniverseID();
            }

            void SetPlaceID(long PlaceID)
            {
                this->PlaceID = PlaceID;
            }

        private:
            long PlaceID = 0;
            long UniverseID = 0;
    };

    class Group : public Auth
    {
        public:
            Responses::Group get_group_info();
            void delete_group_wall_post(int64_t post_id);
            void delete_group_wall_posts_by_user(int64_t user_id);
            Responses::GroupRoles get_group_roles();
            void set_group_role(int64_t user_id, int64_t role_id);
            Responses::GroupRole get_user_role(int64_t user_id);
            Responses::ChangeRoleResponse change_role(int64_t user_id, int change);
            Responses::ChangeRoleResponse demote(int64_t user_id);
            void remove_user(int64_t user_id);
            Responses::AuditPage get_audit_log(std::string action_type="All", int64_t user_id=0, std::string sort="Asc", int32_t limit=10);
            std::vector<Responses::GroupNamehistory> get_name_history(std::string sort="Asc", int32_t limit=10);
            std::vector<Responses::GroupWallPost> get_group_wall(std::string sort="Asc", int32_t limit=10);
            std::vector<Responses::GroupExperience> get_games(std::string access_filter="All", std::string sort="Asc", int32_t limit=10);

        public:
            Group(int64_t group_id, std::string_view cookie)
            {
                this->m_GroupID = group_id;
                this->m_Cookie = cookie;
            }

            Group(int64_t group_id)
            {
                this->m_GroupID = group_id;
            }

            Group()
            {
                this->m_GroupID = 0;
            }

            void SetGroupID(int64_t group_id)
            {
                this->m_GroupID = group_id;
            }

        private:
            int64_t m_GroupID = 0;
    };

    class Trade : public Auth
    {
        public:
            std::vector<Responses::TradeData> get_trades(std::string trade_status_type="Inbound", std::string sort="Asc", int32_t limit=10);
            json get_trade_info(int64_t trade_id);
            Responses::CanTradeWithResponse can_trade_with(int64_t user_id);
            //TODO: counter
            int send_trade_request(int64_t target_uid, json user_offer, json user_request);
            void accept_trade(int64_t trade_id);
            void decline_trade(int64_t trade_id);

        public:
            Trade(std::string_view cookie)
            {
                this->m_Cookie = cookie;
            }
    };

    class User
    {
        public:
            Responses::User GetUser();

            std::vector<Responses::User> GetFriends(std::string Sort="Alphabetical");
            std::vector<Responses::User> GetFollowers(std::string Sort="Asc", int Limit=10);
            std::vector<Responses::User> GetFollowings(std::string Sort="Asc", int Limit=10);
            std::vector<Responses::Experience> GetExperiences(std::string Sort="Asc", int Limit=10);
            std::vector<Responses::Experience> GetFavoriteExperiences(std::string Sort="Asc", int Limit=10);
            std::vector<std::string> GetPastUsernames(std::string Sort="Asc", int Limit=10);
            std::vector<Responses::GroupWithRole> GetGroups();
            std::vector<Responses::Badge> GetBadges();
            Responses::Group GetPrimaryGroup();
            std::vector<Responses::InventoryAsset>  GetInventory(std::vector<std::string> AssetType, std::string Sort="Asc", int Limit=10);

            bool CanInventoryBeViewed();

        public:
            User(long UID)
            {
                this->UID = UID;
            }

            User()
            {
                this->UID = 0;
            }

            void SetUID(long UID)
            {
                this->UID = UID;
            }

        private:
            long UID = 0;
    };


    class Session : public Auth
    {
        public:

            //get requests


            Responses::User GetUser();
            
            std::string GetDescription();

            std::vector<Responses::FriendsOnline> GetFriendsOnline();
            Responses::BirthdateResponse GetBirthDate();
            Responses::PhoneInfo GetPhoneInfo();
            Responses::FriendRequestsResponse GetFriendRequests(std::string Sort="Asc", int Limit=10);

            int GetFriendsCount();

            long GetRobuxBalance();
            long GetUserID();

            bool HasPremium();
            bool IsFavoriteGame(int64_t PlaceID);
            
            //post requests

            double UnlockPin(int Pin);

            bool SendFriendRequest(long UID);
            bool LockPin();

            void SetFavoriteGame(int PlaceID, bool Favorite);
            void SetDescription(std::string Description);
            void SetGender(std::string Gender);
            void ChangePassword(std::string OldPassword, std::string NewPassword);
            void AcceptFriendRequest(long UID);
            void DeclineFriendRequest(long UID);
            void DeclineAllFriendRequests();
            void BlockUser(long UID);
            void UnblockUser(long UID);

            Session(std::string_view cookie)
            {
                this->m_Cookie = cookie;
            }
    };

    class Other : public Auth
    {
        public:

            std::vector<Responses::UserPresence> GetUsersPresence(std::vector<long> UIDs);
            std::vector<Responses::SearchedUser> UserSearch(std::string Keyword, int Limit=10);
            json GroupSearch(std::string Keyword, bool prioritizeExactMatch=true, int Limit=10);
            std::string ValidateUsername(std::string Username);
            long GetGameUniverseID(long PlaceID);
            long get_uid_from_cookie(std::string Cookie);
            Responses::GamePassProductInfoResponse get_gamepass_product_info(int64_t gamepass_id);
            void buy_gamepass(int64_t gamepass_id);

    };
}