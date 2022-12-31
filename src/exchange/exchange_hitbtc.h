//  This file is part of Qt Bitcoin Trader
//      https://github.com/JulyIGHOR/QtBitcoinTrader
//  Copyright (C) 2013-2023 July Ighor <julyighor@gmail.com>
//
//  This program is free software: you can redistribute it and/or modify
//  it under the terms of the GNU General Public License as published by
//  the Free Software Foundation, either version 3 of the License, or
//  (at your option) any later version.
//
//  In addition, as a special exception, the copyright holders give
//  permission to link the code of portions of this program with the
//  OpenSSL library under certain conditions as described in each
//  individual source file, and distribute linked combinations including
//  the two.
//
//  You must obey the GNU General Public License in all respects for all
//  of the code used other than OpenSSL. If you modify file(s) with this
//  exception, you may extend this exception to your version of the
//  file(s), but you are not obligated to do so. If you do not wish to do
//  so, delete this exception statement from your version. If you delete
//  this exception statement from all source files in the program, then
//  also delete it here.
//
//  This program is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  GNU General Public License for more details.
//
//  You should have received a copy of the GNU General Public License
//  along with this program.  If not, see <http://www.gnu.org/licenses/>.

#ifndef EXCHANGE_HITBTC_H
#define EXCHANGE_HITBTC_H

#include "exchange.h"

class Exchange_HitBTC : public Exchange
{
    Q_OBJECT

public:
    Exchange_HitBTC(const QByteArray& pRestSign, const QByteArray& pRestKey);
    ~Exchange_HitBTC();

public slots:
    void clearValues();
    void getHistory(bool);
    void buy(const QString&, double, double);
    void sell(const QString&, double, double);
    void cancelOrder(const QString&, const QByteArray&);

private slots:
    void reloadDepth();
    void sslErrors(const QList<QSslError>&);
    void dataReceivedAuth(const QByteArray&, int, int);
    void secondSlot();
    void quitThread();

private:
    void clearVariables();
    void depthSubmitOrder(const QString&, QMap<double, double>* currentMap, double priceDouble, double amount, bool isAsk);
    void depthUpdateOrder(const QString&, double, double, bool);
    void sendToApi(int reqType, const QByteArray& method, bool auth = false, QByteArray commands = nullptr);
    bool isReplayPending(int);

private:
    bool isFirstAccInfo;

    qint64 lastTickerDate;
    qint64 lastTradesId;
    qint64 lastTradesDate;
    qint64 lastHistoryId;

    JulyHttp* julyHttp;

    QList<DepthItem>* depthAsks;
    QList<DepthItem>* depthBids;

    QMap<double, double> lastDepthAsksMap;
    QMap<double, double> lastDepthBidsMap;
};

#endif // EXCHANGE_HITBTC_H
