#pragma once
#include <string>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QUrl>
#include <QUrlQuery>
class NewsAPI
{
public:
    void getNews(const std::string& symbol);

private:
    // API/network handling
};