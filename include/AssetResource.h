/* 
 * API Asset Resource
 * @author ECHOES Technologies (FPO)
 * @date 27/09/2012
 * 
 * THIS PROGRAM IS CONFIDENTIAL AND PROPRIETARY TO ECHOES TECHNOLOGIES SAS
 * AND MAY NOT BE REPRODUCED, PUBLISHED OR DISCLOSED TO OTHERS WITHOUT
 * COMPANY AUTHORIZATION.
 * 
 * COPYRIGHT 2012 BY ECHOES TECHNOLGIES SAS
 * 
 */

#ifndef ASSETRESOURCE_H
#define	ASSETRESOURCE_H

#include "PublicApiResource.h"

class AssetResource : public PublicApiResource
{
    public:
        AssetResource();
        AssetResource(const AssetResource& orig);
        virtual ~AssetResource();

    protected:
        int assetId, probeId, pluginId;
        
        std::string getAssetsList();
        std::string getAsset();
        std::string getPluginsListForAsset();
        std::string getProbesListForAsset();
        virtual void processGetRequest(const Wt::Http::Request &request, Wt::Http::Response &response);

        std::string postProbeForAsset(std::string sRequest);
        virtual void processPostRequest(const Wt::Http::Request &request, Wt::Http::Response &response);

        virtual void processPutRequest(const Wt::Http::Request &request, Wt::Http::Response &response);
        
        std::string patchAsset(std::string sRequest);
        virtual void processPatchRequest(const Wt::Http::Request &request, Wt::Http::Response &response);

        virtual void processDeleteRequest(const Wt::Http::Request &request, Wt::Http::Response &response);

        virtual void handleRequest(const Wt::Http::Request &request, Wt::Http::Response &response);
};


#endif	/* ASSETRESOURCE_H */
