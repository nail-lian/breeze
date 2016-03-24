﻿
/*
* breeze License
* Copyright (C) 2016 YaweiZhang <yawei.zhang@foxmail.com>.
*
* Licensed under the Apache License, Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
*
* http://www.apache.org/licenses/LICENSE-2.0
*
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
*/






#ifndef _USER_MANAGER_H_
#define _USER_MANAGER_H_
#include <common.h>
#include "service.h"


struct ServiceUserShell 
{
    ServiceID _uID = InvalidServiceID;
    ClusterID _cltID = InvalidClusterID;
};


struct UserPreviewCache
{
    int _status = 0; //0 no Client no User,  1 Creating User, 2 had User
    UserPreview _preview;
    ClusterID _cltID = InvalidClusterID;
};


struct AccountCache
{
    std::string account;
    std::string token;
    std::vector<UserPreviewCache> _previewCache;
};


class UserMgr : public Service
{
public:
    UserMgr();
    ~UserMgr();
    bool onInit() override final;
    void onStop() override final;
    void onTick() override final;
    void process(const Tracing & trace, const char * block, unsigned int len) override final;
public:
    void onBuildDB(ReadStream & rs, bool isLast);
    void onUserAuthReq(const Tracing & trace, zsummer::proto4z::ReadStream &);
public:
    time_t _lastTime = 0;
    std::map<ServiceID, ServiceUserShell> _userShells;
    std::map<std::string, std::vector<AccountCache>> _accountCache;
    Balance _balance;
};





































#endif
