/* 
 * API OrganizationResource
 * @author ECHOES Technologies (GDR)
 * @date 18/02/2013
 * 
 * THIS PROGRAM IS CONFIDENTIAL AND PROPRIETARY TO ECHOES TECHNOLOGIES SAS
 * AND MAY NOT BE REPRODUCED, PUBLISHED OR DISCLOSED TO OTHERS WITHOUT
 * COMPANY AUTHORIZATION.
 * 
 * COPYRIGHT 2013 BY ECHOES TECHNOLGIES SAS
 * 
 */

#include "OrganizationResource.h"

using namespace std;

OrganizationResource::OrganizationResource() : PublicApiResource::PublicApiResource()
{
}

OrganizationResource::OrganizationResource(const OrganizationResource& orig) : PublicApiResource::PublicApiResource(orig)
{
}

OrganizationResource::~OrganizationResource() 
{
}

unsigned short OrganizationResource::getOrganization(std::string &responseMsg)
{
     unsigned short res = 500;
     Wt::Dbo::Transaction transaction(_session);
     Wt::Dbo::ptr<Organization> organization = _session.find<Organization>().where("\"ORG_ID\" = ?").bind(this->_session.user().get()->currentOrganization.id());
    try
    {
        if(organization)
        {
            organization.modify()->setId(organization.id());
            responseMsg = organization.modify()->toJSON();
            res = 200;
        }
        else 
        {
            res = 404;
            responseMsg = "{\"message\":\"Organization not found\"}";
        }

        transaction.commit();
    }
    catch (Wt::Dbo::Exception const& e) 
    {
        Wt::log("error") << e.what();
        res = 503;
        responseMsg = "{\"message\":\"Service Unavailable\"}";
    }
    return res;
}

unsigned short OrganizationResource::getUsersForOrganization(std::string &responseMsg)
{
    unsigned short res = 500;
    unsigned idx = 0;
    try
    {
        Wt::Dbo::Transaction transaction(_session);

        std::string queryStr =  "SELECT usr FROM \"T_USER_USR\" usr where \"USR_ID\" IN"
            "("
                "SELECT \"T_USER_USR_USR_ID\" FROM \"TJ_USR_ORG\" where \"T_ORGANIZATION_ORG_ORG_ID\" IN "
                "("
                    "SELECT \"T_ORGANIZATION_ORG_ORG_ID\" from \"TJ_USR_ORG\" where \"T_USER_USR_USR_ID\" = " + boost::lexical_cast<std::string > (this->_session.user().id()) +
                ")"
            ")"
            "AND \"USR_DELETE\" IS NULL";

        Wt::Dbo::Query<Wt::Dbo::ptr<User> > queryRes = _session.query<Wt::Dbo::ptr<User> >(queryStr);

        Wt::Dbo::collection<Wt::Dbo::ptr<User> > user = queryRes.resultList();

        if (user.size() > 0)
        {
            responseMsg = "[\n";
            for (Wt::Dbo::collection<Wt::Dbo::ptr<User> >::const_iterator i = user.begin(); i != user.end(); i++) 
            {
                i->modify()->setId(i->id());
                responseMsg += "\t" + i->modify()->toJSON();
                ++idx;
                if(user.size()-idx > 0)
                {
                    responseMsg += ",\n";
                }
            }
            responseMsg += "\n]\n";
            res = 200;
        }
        else 
        {
            res = 404;
            responseMsg = "{\"message\":\"User not found\"}";
        }

        transaction.commit();
    }
    catch (Wt::Dbo::Exception const& e) 
    {
        Wt::log("error") << e.what();
        res = 503;
        responseMsg = "{\"message\":\"Service Unavailable\"}";
    }
    return res;
}

unsigned short OrganizationResource::getRolesForOrganization(std::string &responseMsg)
{
    unsigned short res = 500;
    unsigned idx = 0;
    try
    {
        Wt::Dbo::Transaction transaction(_session);

        Wt::Dbo::collection<Wt::Dbo::ptr<UserRole> > userRoles = _session.find<UserRole>()
                .where("\"URO_ORG_ORG_ID\" = ?").bind(this->_session.user().get()->currentOrganization.id())
                .where("\"URO_DELETE\" IS NULL");

        std::cout << this->_session.user().get()->currentOrganization.id() << std::endl;
        if (userRoles.size() > 0)
        {
            responseMsg = "[\n";
            for (Wt::Dbo::collection<Wt::Dbo::ptr<UserRole> >::const_iterator i = userRoles.begin(); i != userRoles.end(); i++) 
            {
                i->modify()->setId(i->id());
                responseMsg += "\t" + i->modify()->toJSON();
                ++idx;
                if(userRoles.size()-idx > 0)
                {
                    responseMsg += ",\n";
                }
            }
            responseMsg += "\n]\n";
            res = 200;
        }
        else 
        {
            res = 404;
            responseMsg = "{\"message\":\"Roles not found\"}";
        }

        transaction.commit();
    }
    catch (Wt::Dbo::Exception const& e) 
    {
        Wt::log("error") << e.what();
        res = 503;
        responseMsg = "{\"message\":\"Service Unavailable\"}";
    }
    return res;
}

 unsigned short OrganizationResource::getMediasForUserForOrganization(std::string &responseMsg)
 {
 unsigned short res = 500;
    unsigned idx = 0;
    try
    {
        Wt::Dbo::Transaction transaction(_session);
        string queryStr = "SELECT med FROM \"T_MEDIA_MED\" med where \"MED_ID\" IN"
                " ("
                " SELECT \"MEV_MED_MED_ID\" FROM \"T_MEDIA_VALUE_MEV\" "
                " WHERE \"MEV_USR_USR_ID\" = " + boost::lexical_cast<std::string>(vPathElements[2]) +
                " AND \"MEV_DELETE\" IS NULL"
                " )"
                " AND \"MED_DELETE\" IS NULL";
 
        Wt::Dbo::Query<Wt::Dbo::ptr<Media> > queryRes = _session.query<Wt::Dbo::ptr<Media> >(queryStr);

        Wt::Dbo::collection<Wt::Dbo::ptr<Media> > media = queryRes.resultList();
        
        if (media.size() > 0)
        {
            responseMsg += "[\n";
            for (Wt::Dbo::collection<Wt::Dbo::ptr<Media> >::const_iterator i = media.begin(); i != media.end(); i++) 
            {
                i->modify()->setId(i->id());
                responseMsg += "\t" + i->modify()->toJSON();
                ++idx;
                if(media.size()-idx > 0)
                {
                    responseMsg += ",\n";
                }
            }
            responseMsg += "\n]\n";               

            res = 200;
        }
        else 
        {
            res = 404;
            responseMsg = "{\"message\":\"Media not found\"}";
        }

        transaction.commit();
    }
    catch (Wt::Dbo::Exception const& e) 
    {
        Wt::log("error") << e.what();
        res = 503;
        responseMsg = "{\"message\":\"Service Unavailable\"}";
    }
    return res;
 }
 
unsigned short OrganizationResource::getMediasValuesForUserForOrganization(std::string &responseMsg)
{
    unsigned short res = 500;
    int idx = 0;
    try
    {
        Wt::Dbo::Transaction transaction(_session);
        Wt::Dbo::ptr<User> user = _session.find<User>().where("\"USR_ID\" = ?").bind(vPathElements[2])
                                                         .where("\"CURRENT_ORG_ID\" = ?").bind(_session.user().get()->currentOrganization.id())
                                                        .where("\"USR_DELETE\" is NULL");
        if(user)
        {
            Wt::Dbo::collection<Wt::Dbo::ptr<MediaValue>> mediaValues = _session.find<MediaValue>().where("\"MEV_USR_USR_ID\" = ?").bind(user.id())
                                                                                                   .where("\"MEV_MED_MED_ID\" = ?").bind(vPathElements[4])
                                                                                                   .where("\"MEV_DELETE\" is NULL");
            responseMsg = "[\n";
            if(mediaValues.size() > 0)
            {
                for (Wt::Dbo::collection<Wt::Dbo::ptr<MediaValue> >::const_iterator i = mediaValues.begin(); i != mediaValues.end(); i++) 
                {
                    i->modify()->setId(i->id());
                    responseMsg += "\t" + i->modify()->toJSON();
                    ++idx;
                    if(mediaValues.size()-idx > 0)
                    {
                        responseMsg += ",\n";
                    }
                }
                responseMsg += "\n]\n";
                res = 200;
            }
            else
            {
                responseMsg = "{\"message\":\"Media value not found\"}";
                 res = 404;
            }
        }
        else 
        {
             responseMsg = "{\"message\":\"User not found\"}";
             res = 404;
        }
        
        transaction.commit();
    }
    catch (Wt::Dbo::Exception const& e) 
    {
        Wt::log("error") << e.what();
        res = 503;
        responseMsg = "{\"message\":\"Service Unavailable\"}";
    }
    return res;
}

unsigned short OrganizationResource::getQuotasAsset(std::string &responseMsg)
{
    unsigned short res = 500;
    try
    {
        Wt::Dbo::Transaction transaction(_session);
        
        Wt::Dbo::ptr<PackOption> ptrPackOption = _session.find<PackOption>()
                .where("\"POP_PCK_PCK_ID\" = ?").bind(this->_session.user()->currentOrganization->pack.id())
                .where("\"POP_OPT_OPT_ID\" = 1")
                .limit(1);
        if (ptrPackOption.get())
        {
            Wt::Dbo::ptr<OptionValue> ptrOptionValue = _session.find<OptionValue>()
                    .where("\"OPT_ID_OPT_ID\" = ?").bind(ptrPackOption->pk.option.id())
                    .where("\"ORG_ID_ORG_ID\" = ?").bind(this->_session.user()->currentOrganization.id())
                    .limit(1);
            if (ptrOptionValue.get())
            {
                responseMsg += ptrOptionValue.modify()->toJSON();
                res = 200;
            }
            else
            {
                responseMsg = "{\"message\":\"Option not found\"}";
                res = 404;
            }
        }
        else
        {
            responseMsg = "{\"message\":\"Option not found\"}";
            res = 404;
        }

        transaction.commit();
    }
    catch (Wt::Dbo::Exception const& e) 
    {
        Wt::log("error") << e.what();
        res = 503;
        responseMsg = "{\"message\":\"Service Unavailable\"}";
    } 
    return res;
}

unsigned short OrganizationResource::getQuotasSms(std::string &responseMsg)
{
    unsigned short res = 500;
    try
    {
        Wt::Dbo::Transaction transaction(_session);

        Wt::Dbo::ptr<PackOption> ptrPackOption = _session.find<PackOption>()
                .where("\"POP_PCK_PCK_ID\" = ?").bind(this->_session.user()->currentOrganization->pack.id())
                .where("\"POP_OPT_OPT_ID\" = 2")
                .limit(1);
        if (ptrPackOption.get())
        {
            Wt::Dbo::ptr<OptionValue> ptrOptionValue = _session.find<OptionValue>()
                    .where("\"OPT_ID_OPT_ID\" = ?").bind(ptrPackOption.get()->pk.option.id())
                    .where("\"ORG_ID_ORG_ID\" = ?").bind(this->_session.user()->currentOrganization.id())
                    .limit(1);
            if (ptrOptionValue.get())
            {
                responseMsg += ptrOptionValue.modify()->toJSON();
                res = 200;
            }
        }
               
        transaction.commit();
    }
    catch (Wt::Dbo::Exception const& e) 
    {
        Wt::log("error") << e.what();
        res = 503;
        responseMsg = "{\"message\":\"Service Unavailable\"}";
    } 
    return res;
}

void OrganizationResource::processGetRequest(Wt::Http::Response &response)
{
    std::string responseMsg = "", nextElement = "";
    
    nextElement = getNextElementFromPath();
    if(!nextElement.compare(""))
    {
        this->statusCode = getOrganization(responseMsg);
    }
    else
    {
        if(!nextElement.compare("quotas_sms"))
        {
            this->statusCode = getQuotasSms(responseMsg);
        }
        else if(!nextElement.compare("quotas_assets"))
        {
            this->statusCode = getQuotasAsset(responseMsg);
        }
        else if(!nextElement.compare("users"))
        {
            nextElement = getNextElementFromPath();
            if(!nextElement.compare(""))
            {
            this->statusCode = getUsersForOrganization(responseMsg);
            }
            else
            {
                try
                {
                    boost::lexical_cast<unsigned long long>(nextElement);

                    nextElement = getNextElementFromPath();

                    if(!nextElement.compare("medias"))
                    {
                        nextElement = getNextElementFromPath();
                        if(!nextElement.compare(""))
                        {
                            this->statusCode =  getMediasForUserForOrganization(responseMsg);
                        }
                        else
                        {
                            boost::lexical_cast<unsigned long long>(nextElement);
                            nextElement = getNextElementFromPath();
                            if(!nextElement.compare(""))
                            {
                                this->statusCode = getMediasValuesForUserForOrganization(responseMsg);
                            }
                            else
                            {
                                this->statusCode = 400;
                                responseMsg = "{\n\t\"message\":\"Bad Request\"\n}";
                            }
                        }
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
        }
        else if(!nextElement.compare("roles"))
        {
            this->statusCode = getRolesForOrganization(responseMsg);
        }
        else
        {
            this->statusCode = 400;
            responseMsg = "{\n\t\"message\":\"Bad Request\"\n}";
        }
    }

    response.setStatus(this->statusCode);
    response.out() << responseMsg;
    return;
}


void OrganizationResource::processPostRequest(const Wt::Http::Request &request, Wt::Http::Response &response)
{

    return ;
}


void OrganizationResource::processPutRequest(const Wt::Http::Request &request, Wt::Http::Response &response)
{
    return;
}


void OrganizationResource::processPatchRequest(const Wt::Http::Request &request, Wt::Http::Response &response)
{
    return;
}



void OrganizationResource::processDeleteRequest(const Wt::Http::Request &request, Wt::Http::Response &response)
{
    return;
}


void OrganizationResource::handleRequest(const Wt::Http::Request &request, Wt::Http::Response &response)
{
    // Create Session and Check auth
    PublicApiResource::handleRequest(request, response);

    return;
}

