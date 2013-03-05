 /* 
 * API Asset Resource
 * @author ECHOES Technologies (FPO)
 * @date 02/11/2012
 * 
 * THIS PROGRAM IS CONFIDENTIAL AND PROPRIETARY TO ECHOES TECHNOLOGIES SAS
 * AND MAY NOT BE REPRODUCED, PUBLISHED OR DISCLOSED TO OTHERS WITHOUT
 * COMPANY AUTHORIZATION.
 * 
 * COPYRIGHT 2012 BY ECHOES TECHNOLGIES SAS
 * 
 */

#include "AssetResource.h"

using namespace std;

AssetResource::AssetResource() {
}

AssetResource::AssetResource(const AssetResource& orig) {
}

AssetResource::~AssetResource() {
    beingDeleted();
}

unsigned short AssetResource::getAssetsList(string &responseMsg) const
{
    unsigned short res = 500;
    unsigned long idx = 0;
    
    try 
    {
        Wt::Dbo::Transaction transaction(*this->session);
        Wt::Dbo::collection<Wt::Dbo::ptr<Asset>> listAssets = this->session->find<Asset> ()
                .where("\"AST_ORG_ORG_ID\" = ? AND \"AST_DELETE\" IS NULL")
                .bind(this->session->user()->currentOrganization.id());

        responseMsg = "[\n";
        for (Wt::Dbo::collection<Wt::Dbo::ptr<Asset>>::const_iterator i = listAssets.begin(); i != listAssets.end(); ++i)
        {
            responseMsg += "\t{\n";
            responseMsg += "\t\t\"id\": " + boost::lexical_cast<string, long long>(i->id()) + ",\n";
            responseMsg += "\t\t\"name\": \"" + i->get()->name.toUTF8() + "\"\n";
            responseMsg += "\t}";
            if (++idx < listAssets.size())
            {
                responseMsg += ",";
            }
            responseMsg += "\n";
        }
        responseMsg += "]";

        transaction.commit();
        res = 200;
    } 
    catch (Wt::Dbo::Exception const& e) 
    {
        Wt::log("error") << e.what();
        res = 503;
        responseMsg = "{\n\t\"message\":\"Service Unavailable\n\"}";
    }
    
    return res;
}

unsigned short AssetResource::getAsset(string &responseMsg) const
{
    unsigned short res = 500;
    
    try 
    {
        Wt::Dbo::Transaction transaction(*this->session);
        Wt::Dbo::ptr<Asset> asset = this->session->find<Asset>()
                .where("\"AST_ORG_ORG_ID\" = ? AND \"AST_ID\" = ? AND \"AST_DELETE\" IS NULL")
                .bind(this->session->user()->currentOrganization.id())
                .bind(this->vPathElements[1]);
        

        if (Utils::checkId<Asset>(asset)) 
        {
            responseMsg += "{\n";
            responseMsg += "\t\"id\": " + boost::lexical_cast<string, long long>(asset.id()) + ",\n";
            responseMsg += "\t\"name\": \"" + asset->name.toUTF8() + "\",\n";
            Wt::Dbo::ptr<AssetArchitecture> assetArchitecture = this->session->find<AssetArchitecture> ()
                .where("\"ASA_ID\" = ? AND \"ASA_DELETE\" IS NULL")
                .bind(asset->assetArchitecture.id());
            if (Utils::checkId<AssetArchitecture>(assetArchitecture)) 
            {
                responseMsg += "\t\"architecture\": \"" + assetArchitecture->name.toUTF8() + "\",\n";
            }
            else 
            {
                responseMsg += "\t\"architecture\": \"Unknown\",\n";
            }
            responseMsg += "\t\"distribution\": {\n";
            Wt::Dbo::ptr<AssetDistribution> assetDistribution = this->session->find<AssetDistribution> ()
                .where("\"ASD_ID\" = ? AND \"ASD_DELETE\" IS NULL")
                .bind(asset->assetDistribution.id());
            if (Utils::checkId<AssetDistribution>(assetDistribution)) 
            {
                responseMsg += "\t\t\"name\": \"" + assetDistribution->name.toUTF8() + "\",\n";
            }
            else 
            {
                responseMsg += "\t\t\"name\": \"Unknown\",\n";
            }
            Wt::Dbo::ptr<AssetRelease> assetRelease = this->session->find<AssetRelease> ()
                .where("\"ASR_ID\" = ? AND \"ASR_DELETE\" IS NULL")
                .bind(asset->assetRelease.id());
            if (Utils::checkId<AssetRelease>(assetRelease)) 
            {
                responseMsg += "\t\t\"release\": \"" + assetRelease->name.toUTF8() + "\"\n";
            }
            else 
            {
                responseMsg += "\t\t\"release\": \"Unknown\"\n";
            }
            responseMsg += "\t}\n";
            responseMsg += "}";

            res = 200;
        } 
        else 
        {
            responseMsg = "{\n\t\"message\":\"Asset not found\"\n}";
            res = 404;
        }

        transaction.commit();
    } 
    catch (Wt::Dbo::Exception const& e) 
    {
        Wt::log("error") << e.what();
        res = 503;
        responseMsg = "{\n\t\"message\":\"Service Unavailable\"\n}";
    }
    
    return res;
}

unsigned short AssetResource::getPluginsListForAsset(string &responseMsg) const
{
    unsigned short res = 500;
    
    try 
    {
        Wt::Dbo::Transaction transaction(*this->session);
        Wt::Dbo::ptr<Asset> asset = this->session->find<Asset> ()
                .where("\"AST_ORG_ORG_ID\" = ? AND \"AST_ID\" = ? AND \"AST_DELETE\" IS NULL")
                .bind(this->session->user()->currentOrganization.id())
                .bind(this->vPathElements[1]);

        if (Utils::checkId<Asset>(asset)) 
        {
            responseMsg = "[\n";
            responseMsg += "\t{\n";
            responseMsg += "\t\t\"id\": 1,\n";
            responseMsg += "\t\t\"name\": \"Linux-System.json\"\n";
            responseMsg += "\t}\n";
            responseMsg += "]";
        } 
        else 
        {
            responseMsg = "{\n\t\"message\":\"Asset not found\"\n}";
            res = 404;
        }

        transaction.commit();
    } 
    catch (Wt::Dbo::Exception const& e) 
    {
        Wt::log("error") << e.what();
        res = 503;
        responseMsg = "{\n\t\"message\":\"Service Unavailable\"\n}";
    }
    
    return res;
}

unsigned short AssetResource::getProbesListForAsset(string &responseMsg) const
{
    unsigned short res = 500;

    try 
    {
        Wt::Dbo::Transaction transaction(*this->session);
        Wt::Dbo::ptr<Asset> asset = this->session->find<Asset> ()
                .where("\"AST_ORG_ORG_ID\" = ? AND \"AST_ID\" = ? AND \"AST_DELETE\" IS NULL")
                .bind(this->session->user()->currentOrganization.id())
                .bind(this->vPathElements[1]);

        if (Utils::checkId<Asset>(asset)) 
        {
            Wt::Dbo::ptr<Probe> probe = this->session->find<Probe> ()
                .where("\"PRB_ID\" = ? AND \"PRB_DELETE\" IS NULL")
                .bind(asset->probe.id());
            if (Utils::checkId<Probe>(probe)) 
            {
                responseMsg += "[\n";
                responseMsg += "\t{\n";
                responseMsg += "\t\t\"id\": " + boost::lexical_cast<string, long long>(probe.id()) + ",\n";
                responseMsg += "\t\t\"name\": \"" + probe->name.toUTF8() + "\"\n";
                responseMsg += "\t}\n";
                responseMsg += "]";

                res = 200;
            }
            else 
            {
                responseMsg = "{\n\t\"message\":\"Probe not found\"\n}";
                res = 404;
            }
        } 
        else 
        {
            responseMsg = "{\n\t\"message\":\"Asset not found\"\n}";
            res = 404;
        }

        transaction.commit();
    } 
    catch (Wt::Dbo::Exception const& e) 
    {
        Wt::log("error") << e.what();
        res = 503;
        responseMsg = "{\n\t\"message\":\"Service Unavailable\"\n}";
    }
    
    return res;
}

void AssetResource::processGetRequest(Wt::Http::Response &response)
{
    string responseMsg = "", nextElement = "";

    nextElement = getNextElementFromPath();
    if(!nextElement.compare(""))
    {
        this->statusCode = getAssetsList(responseMsg);
    }
    else
    {
        try
        {
            boost::lexical_cast<unsigned int>(nextElement);

            nextElement = getNextElementFromPath();

            if(!nextElement.compare(""))
            {
                this->statusCode = getAsset(responseMsg);
            }
            else if(!nextElement.compare("plugins"))
            {
                this->statusCode = getPluginsListForAsset(responseMsg);
            }
            else if(!nextElement.compare("probes"))
            {
                this->statusCode = getProbesListForAsset(responseMsg);
            }
            else
            {
                this->statusCode = 400;
                responseMsg = "{\n\t\"message\":\"Bad Request\"\n}";
            }
        }
        catch(boost::bad_lexical_cast &)
        {
            this->statusCode = 400;
            responseMsg = "{\n\t\"message\":\"Bad Request\"\n}";
        }
    }

    response.setStatus(this->statusCode);
    response.out() << responseMsg;
    return;
}

unsigned short AssetResource::postProbeForAsset(string &responseMsg, const string &sRequest)
{
    unsigned short res = 500;
    Wt::WString name;
    
    try
    {
        Wt::Json::Object result;

        Wt::Json::parse(sRequest, result);

        name = result.get("name");
    }
    catch (Wt::Json::ParseError const& e)
    {
        Wt::log("warning") << "[Asset Ressource] Problems parsing JSON: " << sRequest;
        res = 400;
        responseMsg = "{\n\t\"message\": \"Problems parsing JSON\"\n}";
    }
    catch (Wt::Json::TypeException const& e)
    {
        Wt::log("warning") << "[Asset Ressource] Problems parsing JSON: " << sRequest;
        res = 400;
        responseMsg = "{\n\t\"message\": \"Problems parsing JSON\"\n}";
    }
    
    if(!responseMsg.compare(""))
    {
        try 
        {
            Wt::Dbo::Transaction transaction(*this->session);
            
            // Est-ce que l'asset existe ?
            Wt::Dbo::ptr<Asset> asset = this->session->find<Asset>()
                    .where("\"AST_ORG_ORG_ID\" = ? AND \"AST_ID\" = ? AND \"AST_DELETE\" IS NULL")
                    .bind(this->session->user()->currentOrganization.id())
                    .bind(this->vPathElements[1]);
            if (Utils::checkId<Asset>(asset))
            {
                responseMsg += "{\n";
                // Est-ce que la probe existe pour cet asset ?
                Wt::Dbo::ptr<Probe> probe = this->session->find<Probe> ()
                    .where("\"PRB_ORG_ORG_ID\" = ? AND \"PRB_ID\" = ? AND \"PRB_DELETE\" IS NULL")
                    .bind(asset->probe);
                if (!Utils::checkId<Probe>(probe))
                {
                    Probe *newProbe = new Probe();
                    newProbe->name = "Probe_" + this->session->user()->lastName + "_" + asset->name;
                    newProbe->organization = this->session->user()->currentOrganization;
                    Wt::Dbo::ptr<ProbePackageParameter> probePackageParameter = this->session->find<ProbePackageParameter>()
                            .where("\"PPP_ASA_ASA_ID\" = ? AND PPP_ASD_ASD_ID\" = ? AND PPP_ASR_ASR_ID\" = ? AND \"PPP_DELETE\" IS NULL")
                            .bind(asset->assetArchitecture.id())
                            .bind(asset->assetDistribution.id())
                            .bind(asset->assetRelease.id())
                            .orderBy("\"PPP_PROBE_VERSION DESC\", \"PPP_PACKAGE_VERSION DESC\"")
                            .limit(1);
                    if (Utils::checkId<ProbePackageParameter>(probePackageParameter))
                    {
                        newProbe->probePackageParameter = probePackageParameter;
                    }
                    asset.modify()->probe = this->session->add<Probe>(newProbe);
                    asset->probe.flush();
                }
                responseMsg += "\t\"id\": " + boost::lexical_cast<string, long long>(asset->probe.id()) + ",\n";
                responseMsg += "\t\"name\": \"" + asset->probe->name.toUTF8() + "\",\n";

                // Est-ce que les param pkg de cette probe existent ?
                if (Utils::checkId<ProbePackageParameter>(asset->probe->probePackageParameter))
                {
                    responseMsg += "\t\"version\": \"" + asset->probe->probePackageParameter->probeVersion.toUTF8() + "\",\n";
                    responseMsg += "\t\"package\": {\n";
                    // Est-ce que le pkg de cette probe existent ?
                    if (Utils::checkId<ProbePackage>(asset->probe->probePackageParameter->probePackage))
                    {
                        responseMsg += "\t\t\"filename\": \"" + asset->probe->probePackageParameter->probePackage->filename.toUTF8() + "\",\n";
                    }
                    else
                    {
                        responseMsg += "\t\t\"filename\": \"Unknown\",\n";
                    }
                    responseMsg += "\t\t\"version\": \"" + asset->probe->probePackageParameter->packageVersion.toUTF8() + "\",\n";
                    responseMsg += "\t}\n";

                }
                else
                {
                    responseMsg += "\t\"version\": \"Unknown\",\n";
                    responseMsg += "\t\"package\": {\n";
                    responseMsg += "\t\t\"filename\": \"Unknown\",\n";
                    responseMsg += "\t\t\"version\": \"Unknown\",\n";
                    responseMsg += "\t}\n";
                }
            } 
            else 
            {
                res = 404;
                responseMsg = "{\n\t\"message\":\"Asset not found\"\n}";
            }
            transaction.commit();
        } 
        catch (Wt::Dbo::Exception const& e) 
        {
            Wt::log("error") << "[Asset Ressource] " << e.what();
            res = 503;
            responseMsg = "{\n\t\"message\": \"Service Unavailable\"\n}";
        }
    }
    
    return res;
}

void AssetResource::processPostRequest(const Wt::Http::Request &request, Wt::Http::Response &response)
{
    string responseMsg = "", nextElement = "", sRequest = "";

    sRequest = request2string(request);
    nextElement = getNextElementFromPath();
    if(!nextElement.compare(""))
    {
        this->statusCode = 400;
        responseMsg = "{\n\t\"message\":\"Bad Request\"\n}";
    }
    else
    {   
        try
        {
            boost::lexical_cast<unsigned int>(nextElement);

            nextElement = getNextElementFromPath();

            if(!nextElement.compare("probes"))
            {
                this->statusCode = postProbeForAsset(responseMsg, sRequest);
            }
            else
            {
                this->statusCode = 400;
                responseMsg = "{\n\t\"message\":\"Bad Request\"\n}";
            }
        }
        catch(boost::bad_lexical_cast &)
        {
            this->statusCode = 400;
            responseMsg = "{\n\t\"message\":\"Bad Request\"\n}";
        }
    }

    response.setStatus(this->statusCode);
    response.out() << responseMsg;
    return;
}

unsigned short AssetResource::putAsset(string &responseMsg, const string &sRequest)
{
    unsigned short res = 500;
    Wt::WString arch, distribName, distribRelease;
    
    try
    {
        Wt::Json::Object result;

        Wt::Json::parse(sRequest, result);

        Wt::Json::Object distrib = result.get("distrib");
        arch = result.get("arch");
        distribName = distrib.get("name");
        distribRelease = distrib.get("release");
    }
    catch (Wt::Json::ParseError const& e)
    {
        Wt::log("warning") << "[Asset Ressource] Problems parsing JSON: " << sRequest;
        res = 400;
        responseMsg = "{\n\t\"message\": \"Problems parsing JSON\"\n}";
    }
    catch (Wt::Json::TypeException const& e)
    {
        Wt::log("warning") << "[Asset Ressource] Problems parsing JSON: " << sRequest;
        res = 400;
        responseMsg = "{\n\t\"message\": \"Problems parsing JSON\"\n}";
    }

    if(!responseMsg.compare(""))
    {
        try 
        {
            Wt::Dbo::Transaction transaction(*this->session);
            Wt::Dbo::ptr<Asset> asset = this->session->find<Asset> ()
                    .where("\"AST_ORG_ORG_ID\" = ? AND \"AST_ID\" = ? AND \"AST_DELETE\" IS NULL")
                    .bind(this->session->user()->currentOrganization.id())
                    .bind(this->vPathElements[1]);
            if (Utils::checkId<Asset>(asset)) 
            {
                Wt::Dbo::ptr<AssetArchitecture> assetArchitecture = this->session->find<AssetArchitecture>()
                        .where("\"ASA_NAME\" = ?")
                        .bind(arch);
                if (!Utils::checkId<AssetArchitecture> (assetArchitecture)) 
                {
                    AssetArchitecture *newAssetArchitecture = new AssetArchitecture();
                    newAssetArchitecture->name = arch;
                    assetArchitecture = this->session->add<AssetArchitecture>(newAssetArchitecture);
                    assetArchitecture.flush();
                }
                asset.modify()->assetArchitecture = assetArchitecture;
                
                Wt::Dbo::ptr<AssetDistribution> assetDistribution = this->session->find<AssetDistribution>()
                        .where("\"ASD_NAME\" = ?")
                        .bind(distribName);
                if (!Utils::checkId<AssetDistribution> (assetDistribution)) 
                {
                    AssetDistribution *newAssetDistribution = new AssetDistribution();
                    newAssetDistribution->name = distribName;
                    assetDistribution = this->session->add<AssetDistribution>(newAssetDistribution);
                    assetDistribution.flush();
                }
                asset.modify()->assetDistribution = assetDistribution;
                
                Wt::Dbo::ptr<AssetRelease> assetRelease = this->session->find<AssetRelease>()
                        .where("\"ASR_NAME\" = ?")
                        .bind(distribRelease);
                if (!Utils::checkId<AssetRelease> (assetRelease)) 
                {
                    AssetRelease *newAssetRelease = new AssetRelease();
                    newAssetRelease->name = distribRelease;
                    assetRelease = this->session->add<AssetRelease>(newAssetRelease);
                    assetRelease.flush();
                }
                asset.modify()->assetRelease = assetRelease;
            } 
            else 
            {
                res = 404;
                responseMsg = "{\n\t\"message\":\"Asset not found\"\n}";
            }
            transaction.commit();
        } 
        catch (Wt::Dbo::Exception const& e) 
        {
            Wt::log("error") << "[Asset Ressource] " << e.what();
            res = 503;
            responseMsg = "{\n\t\"message\": \"Service Unavailable\"\n}";
        }
    }
    
    return res;
}

void AssetResource::processPutRequest(const Wt::Http::Request &request, Wt::Http::Response &response)
{
    string responseMsg = "", nextElement = "", sRequest = "";

    sRequest = request2string(request);
    nextElement = getNextElementFromPath();
    if(!nextElement.compare(""))
    {
        this->statusCode = 400;
        responseMsg = "{\n\t\"message\":\"Bad Request\"\n}";
    }
    else
    {   
        try
        {
            boost::lexical_cast<unsigned int>(nextElement);

            nextElement = getNextElementFromPath();

            if(!nextElement.compare(""))
            {
                this->statusCode = putAsset(responseMsg, sRequest);
            }
            else
            {
                this->statusCode = 400;
                responseMsg = "{\n\t\"message\":\"Bad Request\"\n}";
            }
        }
        catch(boost::bad_lexical_cast &)
        {
            this->statusCode = 400;
            responseMsg = "{\n\t\"message\":\"Bad Request\"\n}";
        }
    }

    response.setStatus(this->statusCode);
    response.out() << responseMsg;
    return;
}

void AssetResource::processDeleteRequest(const Wt::Http::Request &request, Wt::Http::Response &response)
{
    return;
}


void AssetResource::handleRequest(const Wt::Http::Request &request, Wt::Http::Response &response)
{
    PublicApiResource::handleRequest(request, response);

    return;
}

