#pragma once

#include "ChatService.h"
#include "LoginService.h"

#include <boost/smart_ptr.hpp>
#include <memory>
#include <string>
#include <map>
#include <vector>

class WebSocketSession;

class InteractionHandler
{
private:
    std::map<std::string, boost::weak_ptr<WebSocketSession>> sessions;
    std::shared_ptr<LoginService> loginService;
    std::shared_ptr<ChatService> chatService;

    std::shared_ptr<std::vector<std::string>> getUsernames();

public:
    explicit InteractionHandler(const std::shared_ptr<LoginService>& loginService,
        const std::shared_ptr<ChatService>& chatService);

    void processMessage(const std::string& message, const boost::weak_ptr<WebSocketSession>& sender);
    void loginClient(const boost::weak_ptr<WebSocketSession>& session, const std::string& username, const std::string& reply);
    void sendMessage(const std::string& receiver, const std::string& message, const std::string& sender);
    void sendUsersList(const boost::weak_ptr<WebSocketSession>& session);
    void leaveClient(const std::string& username);
};