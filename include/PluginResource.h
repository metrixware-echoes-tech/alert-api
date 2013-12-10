/* 
 * Header of API PluginResource
 * @author ECHOES Technologies (GDR)
 * @date 10/02/2013
 * 
 * THIS PROGRAM IS CONFIDENTIAL AND PROPRIETARY TO ECHOES TECHNOLOGIES SAS
 * AND MAY NOT BE REPRODUCED, PUBLISHED OR DISCLOSED TO OTHERS WITHOUT
 * COMPANY AUTHORIZATION.
 * 
 * COPYRIGHT 2013 BY ECHOES TECHNOLGIES SAS
 * 
 */

#ifndef PLUGINRESOURCE_H
#define	PLUGINRESOURCE_H

#include "PublicApiResource.h"

class PluginResource : public PublicApiResource
{
    public :
        PluginResource();
        virtual ~PluginResource();
        
    protected :
        EReturnCode getPluginsList(std::string &responseMsg);
        EReturnCode getPlugin(std::string &responseMsg);
        EReturnCode getAliasForPlugin(std::string &responseMsg);
        EReturnCode getInformationsListForPlugin(std::string &responseMsg);
        virtual void processGetRequest(Wt::Http::Response &response);

        EReturnCode postPlugin(std::string &responseMsg, const std::string &sRequest);
        virtual void processPostRequest(Wt::Http::Response &response);

        EReturnCode putPlugin(std::string &responseMsg, const std::string &sRequest);
        EReturnCode putAliasForPlugin(std::string &responseMsg, const std::string &sRequest);
        virtual void processPutRequest(Wt::Http::Response &response);

        EReturnCode deletePlugin(std::string &responseMsg);
        virtual void processDeleteRequest(Wt::Http::Response &response);
};

#endif	/* PLUGINRESOURCE_H */

