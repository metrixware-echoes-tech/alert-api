/* 
 * Header of API AddonResource
 * @author ECHOES Technologies (GDR)
 * @date 06/03/2013
 * 
 * THIS PROGRAM IS CONFIDENTIAL AND PROPRIETARY TO ECHOES TECHNOLOGIES SAS
 * AND MAY NOT BE REPRODUCED, PUBLISHED OR DISCLOSED TO OTHERS WITHOUT
 * COMPANY AUTHORIZATION.
 * 
 * COPYRIGHT 2013 BY ECHOES TECHNOLGIES SAS
 * 
 */

#ifndef ADDONRESOURCE_H
#define	ADDONRESOURCE_H

#include "PublicApiResource.h"

class AddonResource : public PublicApiResource
{
    public :
        AddonResource(Echoes::Dbo::Session& session);
        virtual ~AddonResource();

    protected :
        EReturnCode getAddonsList(const long long &grpId, std::string &responseMsg, const std::vector<std::string> &pathElements = std::vector<std::string>(), const std::string &sRequest = "");
        EReturnCode getAddon(const long long &grpId, std::string &responseMsg, const std::vector<std::string> &pathElements = std::vector<std::string>(), const std::string &sRequest = "");
        EReturnCode getSearch_typesForAddon(const long long &grpId, std::string &responseMsg, const std::vector<std::string> &pathElements = std::vector<std::string>(), const std::string &sRequest = "");
        virtual EReturnCode processGetRequest(const Wt::Http::Request &request, const long long &grpId, std::string &responseMsg);
};

#endif	/* ADDONRESOURCE_H */

