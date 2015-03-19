/* 
 * API SearchResource
 * @author ECHOES Technologies (FPO)
 * @date 09/12/2013
 * 
 * THIS PROGRAM IS CONFIDENTIAL AND PROPRIETARY TO ECHOES TECHNOLOGIES SAS
 * AND MAY NOT BE REPRODUCED, PUBLISHED OR DISCLOSED TO OTHERS WITHOUT
 * COMPANY AUTHORIZATION.
 * 
 * COPYRIGHT 2013 BY ECHOES TECHNOLGIES SAS
 * 
 */

#include "SearchResource.h"

using namespace std;

SearchResource::SearchResource(Echoes::Dbo::Session& session) : PublicApiResource::PublicApiResource(session)
{
    /*Call structFillTmp;
    
    structFillTmp.method = "GET";
    structFillTmp.path = "";
    structFillTmp.parameters.push_back("type_id");
    structFillTmp.parameters.push_back("source_id");
    structFillTmp.parameters.push_back("plugin_id");
    structFillTmp.function = boost::bind(&SearchResource::getSearchsList, this, _1, _2, _3, _4, _5);
    calls.push_back(structFillTmp);
    
    structFillTmp.method = "GET";
    structFillTmp.path = "/parameters";
    structFillTmp.parameters.push_back("type_id");
    structFillTmp.parameters.push_back("source_id");
    structFillTmp.parameters.push_back("plugin_id");
    structFillTmp.function = boost::bind(&SearchResource::getParametersList, this, _1, _2, _3, _4, _5);
    calls.push_back(structFillTmp);
    
    structFillTmp.method = "GET";
    structFillTmp.path = "/[0-9]+";
    structFillTmp.function = boost::bind(&SearchResource::getSearch, this, _1, _2, _3, _4, _5);
    calls.push_back(structFillTmp);
    
    structFillTmp.method = "GET";
    structFillTmp.path = "/[0-9]+/parameters";
    structFillTmp.function = boost::bind(&SearchResource::getParametersListForSearch, this, _1, _2, _3, _4, _5);
    calls.push_back(structFillTmp);
    
    structFillTmp.method = "GET";
    structFillTmp.path = "/(\\D)*";
    structFillTmp.function = boost::bind(&SearchResource::Error, this, _1, _2, _3, _4, _5);
    calls.push_back(structFillTmp);
    
    structFillTmp.method = "POST";
    structFillTmp.path = "";
    structFillTmp.function = boost::bind(&SearchResource::postSearch, this, _1, _2, _3, _4, _5);
    calls.push_back(structFillTmp);
    
    structFillTmp.method = "POST";
    structFillTmp.path = ".+";
    structFillTmp.function = boost::bind(&SearchResource::Error, this, _1, _2, _3, _4, _5);
    calls.push_back(structFillTmp);
    
    structFillTmp.method = "PUT";
    structFillTmp.path = "";
    structFillTmp.function = boost::bind(&SearchResource::Error, this, _1, _2, _3, _4, _5);
    calls.push_back(structFillTmp);
    
    structFillTmp.method = "PUT";
    structFillTmp.path = "/[0-9]+";
    structFillTmp.function = boost::bind(&SearchResource::putSearch, this, _1, _2, _3, _4, _5);
    calls.push_back(structFillTmp);
    
    structFillTmp.method = "PUT";
    structFillTmp.path = "/(\\D)*";
    structFillTmp.function = boost::bind(&SearchResource::Error, this, _1, _2, _3, _4, _5);
    calls.push_back(structFillTmp);
    
    structFillTmp.method = "DELETE";
    structFillTmp.path = "";
    structFillTmp.function = boost::bind(&SearchResource::Error, this, _1, _2, _3, _4, _5);
    calls.push_back(structFillTmp);
    
    structFillTmp.method = "DELETE";
    structFillTmp.path = "/[0-9]+";
    structFillTmp.function = boost::bind(&SearchResource::deleteSearch, this, _1, _2, _3, _4, _5);
    calls.push_back(structFillTmp);
    
    structFillTmp.method = "DELETE";
    structFillTmp.path = "/(\\D)*";
    structFillTmp.function = boost::bind(&SearchResource::Error, this, _1, _2, _3, _4, _5);
    calls.push_back(structFillTmp);*/
}

SearchResource::~SearchResource()
{
}

Wt::Dbo::ptr<Echoes::Dbo::Search> SearchResource::selectSearch(const long long &seaId, const long long &orgId, Echoes::Dbo::Session &session)
{
    return selectSearch(boost::lexical_cast<string>(seaId), boost::lexical_cast<string>(orgId), session);
}

Wt::Dbo::ptr<Echoes::Dbo::Search> SearchResource::selectSearch(const string &seaId, const long long &orgId, Echoes::Dbo::Session &session)
{
    return selectSearch(seaId, boost::lexical_cast<string>(orgId), session);
}

Wt::Dbo::ptr<Echoes::Dbo::Search> SearchResource::selectSearch(const string &seaId, const string &orgId, Echoes::Dbo::Session &session)
{
    const string queryStr =
" SELECT sea"
"   FROM " QUOTE("T_SEARCH" SEP TRIGRAM_SEARCH) " sea"
"   WHERE"
"     " QUOTE(TRIGRAM_SEARCH SEP TRIGRAM_SOURCE SEP TRIGRAM_SOURCE ID) " IN"
"       ("
"         SELECT " QUOTE(TRIGRAM_SOURCE ID)
"           FROM " QUOTE("T_SOURCE" SEP TRIGRAM_SOURCE)
"             WHERE"
"               " QUOTE(TRIGRAM_SOURCE ID) " IN"
"                 ("
"                   SELECT " QUOTE("T_SOURCE" SEP TRIGRAM_SOURCE SEP TRIGRAM_SOURCE ID)
"                     FROM " QUOTE("TJ" SEP TRIGRAM_PLUGIN SEP TRIGRAM_SOURCE)
"                       WHERE " QUOTE("T_PLUGIN" SEP TRIGRAM_PLUGIN SEP TRIGRAM_PLUGIN ID) " IN"
"                         ("
"                           SELECT " QUOTE(TRIGRAM_PLUGIN ID)
"                             FROM " QUOTE("T_PLUGIN" SEP TRIGRAM_PLUGIN)
"                               WHERE"
"                                 " QUOTE(TRIGRAM_PLUGIN SEP TRIGRAM_ORGANIZATION SEP TRIGRAM_ORGANIZATION ID) " = " + orgId +
"                                 AND " QUOTE(TRIGRAM_PLUGIN SEP "DELETE") " IS NULL"
"                         )"
"                 )"
"               AND " QUOTE(TRIGRAM_SOURCE SEP "DELETE") " IS NULL"
"       )"
"     AND " QUOTE(TRIGRAM_SEARCH ID) " = " + seaId +
"     AND " QUOTE(TRIGRAM_SEARCH SEP "DELETE") " IS NULL"
"   LIMIT 1";

    Wt::Dbo::Query<Wt::Dbo::ptr<Echoes::Dbo::Search>> queryRes = session.query<Wt::Dbo::ptr<Echoes::Dbo::Search>>(queryStr);

    return queryRes.resultValue();
}

EReturnCode SearchResource::getSearchsList(const long long &orgId, std::string &responseMsg, const std::vector<std::string> &pathElements, const std::string &sRequest, std::map<string, long long> parameters)
{
    EReturnCode res = EReturnCode::INTERNAL_SERVER_ERROR;

    try
    {
        Wt::Dbo::Transaction transaction(m_session, true);
        string queryStr =
" SELECT sea"
"   FROM " QUOTE("T_SEARCH" SEP TRIGRAM_SEARCH) " sea"
"   WHERE"
"     " QUOTE(TRIGRAM_SEARCH SEP TRIGRAM_SOURCE SEP TRIGRAM_SOURCE ID) " IN"
"       ("
"         SELECT " QUOTE(TRIGRAM_SOURCE ID)
"           FROM " QUOTE("T_SOURCE" SEP TRIGRAM_SOURCE)
"             WHERE"
"               " QUOTE(TRIGRAM_SOURCE ID) " IN"
"                 ("
"                   SELECT " QUOTE("T_SOURCE" SEP TRIGRAM_SOURCE SEP TRIGRAM_SOURCE ID)
"                     FROM " QUOTE("TJ" SEP TRIGRAM_PLUGIN SEP TRIGRAM_SOURCE)
"                       WHERE " QUOTE("T_PLUGIN" SEP TRIGRAM_PLUGIN SEP TRIGRAM_PLUGIN ID) " IN"
"                         ("
"                           SELECT " QUOTE(TRIGRAM_PLUGIN ID)
"                             FROM " QUOTE("T_PLUGIN" SEP TRIGRAM_PLUGIN)
"                               WHERE"
"                                 " QUOTE(TRIGRAM_PLUGIN SEP TRIGRAM_ORGANIZATION SEP TRIGRAM_ORGANIZATION ID) " = " + boost::lexical_cast<string>(orgId);

        if (parameters["plugin_id"] > 0)
        {
            queryStr +=
"                                 AND " QUOTE(TRIGRAM_PLUGIN ID) " = " + boost::lexical_cast<string>(parameters["plugin_id"]);
        }

        queryStr +=
"                                 AND " QUOTE(TRIGRAM_PLUGIN SEP "DELETE") " IS NULL"
"                         )";

        if (parameters["source_id"] > 0)
        {
            queryStr +=
"                         AND " QUOTE("T_SOURCE" SEP TRIGRAM_SOURCE SEP TRIGRAM_SOURCE ID) " = " + boost::lexical_cast<string>(parameters["source_id"]);
        }

        queryStr +=
"                 )"
"               AND " QUOTE(TRIGRAM_SOURCE SEP "DELETE") " IS NULL"
"       )"
"     AND " QUOTE(TRIGRAM_SEARCH SEP "DELETE") " IS NULL";

        Wt::Dbo::Query<Wt::Dbo::ptr<Echoes::Dbo::Search>> queryRes = m_session.query<Wt::Dbo::ptr<Echoes::Dbo::Search>>(queryStr);

        Wt::Dbo::collection<Wt::Dbo::ptr<Echoes::Dbo::Search>> seaPtrCol = queryRes.resultList();

        res = serialize(seaPtrCol, responseMsg);

        transaction.commit();
    }
    catch (Wt::Dbo::Exception const& e)
    {
        res = EReturnCode::SERVICE_UNAVAILABLE;
        responseMsg = httpCodeToJSON(res, e);
    }
    return res;
}

EReturnCode SearchResource::getSearch(const long long &orgId, std::string &responseMsg, const std::vector<std::string> &pathElements, const std::string &sRequest, std::map<string, long long> parameters)
{
    EReturnCode res = EReturnCode::INTERNAL_SERVER_ERROR;

    try
    {
        Wt::Dbo::Transaction transaction(m_session, true);

        Wt::Dbo::ptr<Echoes::Dbo::Search> seaPtr = selectSearch(pathElements[1], orgId, m_session);

        res = serialize(seaPtr, responseMsg);

        transaction.commit();
    }
    catch (Wt::Dbo::Exception const& e)
    {
        res = EReturnCode::SERVICE_UNAVAILABLE;
        responseMsg = httpCodeToJSON(res, e);
    }
    return res;
}

EReturnCode SearchResource::getParametersList(const long long &orgId, std::string &responseMsg, const std::vector<std::string> &pathElements, const std::string &sRequest, std::map<string, long long> parameters)
{
    EReturnCode res = EReturnCode::INTERNAL_SERVER_ERROR;
    try
    {
        Wt::Dbo::Transaction transaction(m_session, true);

        string queryStr =
" SELECT sep\n"
"   FROM " QUOTE("TR_SEARCH_PARAMETER" SEP TRIGRAM_SEARCH_PARAMETER) " sep\n";

        if (parameters["type_id"] > 0)
        {
            queryStr +=
"   WHERE\n"
"     " QUOTE(TRIGRAM_SEARCH_PARAMETER ID) " IN\n"
"       (\n"
"         SELECT " QUOTE ("TR_SEARCH_PARAMETER" SEP TRIGRAM_SEARCH_PARAMETER SEP TRIGRAM_SEARCH_PARAMETER ID) "\n"
"           FROM " QUOTE("TJ" SEP TRIGRAM_SEARCH_TYPE SEP TRIGRAM_SEARCH_PARAMETER) "\n"
"           WHERE\n"
"             " QUOTE("TR_SEARCH_TYPE" SEP TRIGRAM_SEARCH_TYPE SEP TRIGRAM_SEARCH_TYPE ID) " IN\n"
"               (\n"
"                 SELECT " QUOTE(TRIGRAM_SEARCH_TYPE ID)
"                   FROM " QUOTE ("TR_SEARCH_TYPE" SEP TRIGRAM_SEARCH_TYPE) "\n"
"                   WHERE\n"
"                     " QUOTE(TRIGRAM_SEARCH_TYPE ID) " = " + boost::lexical_cast<string>(parameters["type_id"]) + "\n" 
"                     AND " QUOTE(TRIGRAM_SEARCH_TYPE SEP "DELETE") " IS NULL\n"
"               )\n"
"       )\n";
        }

        queryStr +=
"   ORDER BY " QUOTE(TRIGRAM_SEARCH_PARAMETER ID)"\n";

        Wt::Dbo::Query<Wt::Dbo::ptr<Echoes::Dbo::SearchParameter>> queryRes = m_session.query<Wt::Dbo::ptr<Echoes::Dbo::SearchParameter>>(queryStr);

        Wt::Dbo::collection<Wt::Dbo::ptr<Echoes::Dbo::SearchParameter>> srpPtrCol = queryRes.resultList();

        res = serialize(srpPtrCol, responseMsg);

        transaction.commit();
    }
    catch (Wt::Dbo::Exception const& e)
    {
        res = EReturnCode::SERVICE_UNAVAILABLE;
        responseMsg = httpCodeToJSON(res, e);
    }
    return res;
}

EReturnCode SearchResource::getParametersListForSearch(const long long &orgId, std::string &responseMsg, const std::vector<std::string> &pathElements, const std::string &sRequest, std::map<string, long long> parameters)
{
    EReturnCode res = EReturnCode::INTERNAL_SERVER_ERROR;
    try
    {
        Wt::Dbo::Transaction transaction(m_session, true);

        Wt::Dbo::ptr<Echoes::Dbo::Search> seaPtr = selectSearch(pathElements[1], orgId, m_session);
        
        Wt::Dbo::collection<Wt::Dbo::ptr<Echoes::Dbo::SearchParameterValue>> sevPtrCol = m_session.find<Echoes::Dbo::SearchParameterValue>()
                .where(QUOTE(TRIGRAM_SEARCH_PARAMETER_VALUE SEP "DELETE") " IS NULL")
                .where(QUOTE(TRIGRAM_SEARCH ID SEP TRIGRAM_SEARCH ID) " = ?").bind(seaPtr.id());

        res = serialize(sevPtrCol, responseMsg);

        transaction.commit();
    }
    catch (Wt::Dbo::Exception const& e)
    {
        res = EReturnCode::SERVICE_UNAVAILABLE;
        responseMsg = httpCodeToJSON(res, e);
    }
    return res;
}

EReturnCode SearchResource::processGetRequest(const Wt::Http::Request &request, const long long &orgId, std::string &responseMsg)
{
    EReturnCode res = EReturnCode::INTERNAL_SERVER_ERROR;
    string nextElement = "";
    unsigned short indexPathElement = 1;
    vector<string> pathElements;
    map<string, long long> parameters;
    
    parameters["type_id"] = 0;
    parameters["plugin_id"] = 0;
    parameters["source_id"] = 0;

    const string sRequest = processRequestParameters(request, pathElements, parameters);

    nextElement = getNextElementFromPath(indexPathElement, pathElements);
    if (nextElement.empty())
    {
        res = getSearchsList(orgId, responseMsg, pathElements, sRequest, parameters);
    }
    else if (nextElement.compare("parameters") == 0)
    {
        res = getParametersList(orgId, responseMsg, pathElements, sRequest, parameters);
    }
    else
    {
        try
        {
            boost::lexical_cast<unsigned long long>(nextElement);

            nextElement = getNextElementFromPath(indexPathElement, pathElements);
            if (nextElement.empty())
            {
                res = getSearch(orgId, responseMsg, pathElements);
            }
            else if (nextElement.compare("parameters") == 0)
            {
                res = getParametersListForSearch(orgId, responseMsg, pathElements);
            }
            else
            {
                res = EReturnCode::BAD_REQUEST;
                const string err = "[Search Resource] bad nextElement";
                responseMsg = httpCodeToJSON(res, err);
            }
        }
        catch (boost::bad_lexical_cast const& e)
        {
            res = EReturnCode::BAD_REQUEST;
            responseMsg = httpCodeToJSON(res, e);
        }
    }

    return res;
}

EReturnCode SearchResource::postSearch(const long long &orgId, std::string &responseMsg, const std::vector<std::string> &pathElements, const std::string &sRequest, std::map<string, long long> parameters)
{
    EReturnCode res = EReturnCode::INTERNAL_SERVER_ERROR;
    long long srcId;
    long long styId;
    int period;

    if (!sRequest.empty())
    {
        try
        {
            Wt::Json::Object result;
            Wt::Json::parse(sRequest, result);

            srcId = result.get("source_id");
            styId = result.get("type_id");
            period = result.get("period").toNumber();
        }
        catch (Wt::Json::ParseError const& e)
        {
            res = EReturnCode::BAD_REQUEST;
            responseMsg = httpCodeToJSON(res, e);
        }
        catch (Wt::Json::TypeException const& e)
        {
            res = EReturnCode::BAD_REQUEST;
            responseMsg = httpCodeToJSON(res, e);
        }
    }
    else
    {
        res = EReturnCode::BAD_REQUEST;
        const string err = "[Search Resource] sRequest is not empty";
        responseMsg = httpCodeToJSON(res, err);
    }

    if (responseMsg.empty())
    {
        try
        {
            Wt::Dbo::Transaction transaction(m_session, true);

            Wt::Dbo::ptr<Echoes::Dbo::SearchType> styPtr = m_session.find<Echoes::Dbo::SearchType>()
                    .where(QUOTE(TRIGRAM_SEARCH_TYPE ID) " = ?").bind(styId)
                    .where(QUOTE(TRIGRAM_SEARCH_TYPE SEP "DELETE") " IS NULL");
            if (!styPtr)
            {
                res = EReturnCode::NOT_FOUND;
                responseMsg = httpCodeToJSON(res, styPtr);
                return res;
            }
            
            Wt::Dbo::ptr<Echoes::Dbo::Source> srcPtr = SourceResource::selectSource(srcId, orgId, m_session);
            if (!srcPtr)
            {
                res = EReturnCode::NOT_FOUND;
                responseMsg = httpCodeToJSON(res, srcPtr);
                return res;
            }
            
            Echoes::Dbo::Search *newSea = new Echoes::Dbo::Search();
            newSea->searchType = styPtr;
            newSea->source = srcPtr;
            newSea->period = period;

            Wt::Dbo::ptr<Echoes::Dbo::Search> newSeaPtr = m_session.add<Echoes::Dbo::Search>(newSea);
            newSeaPtr.flush();

            try
            {
                Wt::Json::Object result;
                Wt::Json::parse(sRequest, result);

                for (Wt::Dbo::collection<Wt::Dbo::ptr<Echoes::Dbo::SearchParameter> >::const_iterator it = styPtr->searchParameters.begin(); it != styPtr->searchParameters.end(); ++it)
                {
                    Echoes::Dbo::SearchParameterValue *newSev = new Echoes::Dbo::SearchParameterValue;

                    newSev->value = result.get(it->get()->name.toUTF8());
                    newSev->name = it->get()->name;
                    newSev->searchParameterValueId.searchParameter= *it;
                    newSev->searchParameterValueId.search = newSeaPtr;

                    m_session.add<Echoes::Dbo::SearchParameterValue>(newSev);
                }
            }
            catch (Wt::Json::ParseError const& e)
            {
                res = EReturnCode::BAD_REQUEST;
                responseMsg = httpCodeToJSON(res, e);
            }
            catch (Wt::Json::TypeException const& e)
            {
                res = EReturnCode::BAD_REQUEST;
                responseMsg = httpCodeToJSON(res, e);
            }

            res = serialize(newSeaPtr, responseMsg, EReturnCode::CREATED);

            transaction.commit();
        }
        catch (Wt::Dbo::Exception const& e)
        {
            res = EReturnCode::SERVICE_UNAVAILABLE;
            responseMsg = httpCodeToJSON(res, e);
        }
    }

    return res;
}

EReturnCode SearchResource::processPostRequest(const Wt::Http::Request &request, const long long &orgId, std::string &responseMsg)
{
    EReturnCode res = EReturnCode::INTERNAL_SERVER_ERROR;
    string nextElement = "";
    unsigned short indexPathElement = 1;
    vector<string> pathElements;
    map<string, long long> parameters;

    const string sRequest = processRequestParameters(request, pathElements, parameters);

    nextElement = getNextElementFromPath(indexPathElement, pathElements);
    if (nextElement.empty())
    {
        res = postSearch(orgId, responseMsg, pathElements, sRequest);
    }
    else
    {
        res = EReturnCode::BAD_REQUEST;
        const string err = "[Search Resource] bad nextElement";
        responseMsg = httpCodeToJSON(res, err);
    }

    return res;
}

EReturnCode SearchResource::putSearch(const long long &orgId, std::string &responseMsg, const std::vector<std::string> &pathElements, const std::string &sRequest, std::map<string, long long> parameters)
{
    EReturnCode res = EReturnCode::INTERNAL_SERVER_ERROR;

    if (sRequest.empty())
    {            
        res = EReturnCode::BAD_REQUEST;
        const string err = "[Search Resource] sRequest is not empty";
        responseMsg = httpCodeToJSON(res, err);
    }

    if (responseMsg.empty())
    {
        try
        {
            Wt::Dbo::Transaction transaction(m_session, true);

            Wt::Dbo::ptr<Echoes::Dbo::Search> seaPtr = m_session.find<Echoes::Dbo::Search>()
                    .where(QUOTE(TRIGRAM_SEARCH SEP "DELETE") " IS NULL")
                    .where(QUOTE(TRIGRAM_SEARCH ID) " = ?").bind(pathElements[1]);

            if (!seaPtr)
            {
                res = EReturnCode::NOT_FOUND;
                responseMsg = httpCodeToJSON(res, seaPtr);
                return res;
            }
            
            Wt::Dbo::collection<Wt::Dbo::ptr<Echoes::Dbo::Plugin> >::const_iterator itPlugin = seaPtr.get()->source.get()->plugins.begin();
            if (itPlugin->get()->organization.id() != orgId)
            {
                res = EReturnCode::NOT_FOUND;
                responseMsg = httpCodeToJSON(res, seaPtr);
                return res;
            }

            try
            {                
                Wt::Json::Object result;
                Wt::Json::parse(sRequest, result);
            
                if (result.contains("period"))
                {
                    seaPtr.modify()->period = result.get("period").toNumber();
                }
                
                Wt::Dbo::ptr<Echoes::Dbo::SearchType> seaTypePtr = seaPtr.get()->searchType;
                            
                for (Wt::Dbo::collection<Wt::Dbo::ptr<Echoes::Dbo::SearchParameter> >::const_iterator it = seaTypePtr->searchParameters.begin(); it != seaTypePtr->searchParameters.end(); ++it)
                {
                    Wt::Dbo::ptr<Echoes::Dbo::SearchParameterValue> seaParaValuePtr = m_session.find<Echoes::Dbo::SearchParameterValue>()
                        .where(QUOTE(TRIGRAM_SEARCH_PARAMETER_VALUE SEP "DELETE") " IS NULL")
                        .where(QUOTE("SEA_ID_SEA_ID") " = ?").bind(seaPtr.id())
                        .where(QUOTE("SEP_ID_SEP_ID") " = ?").bind(it->id());
                                            
                    if(seaParaValuePtr && result.contains(it->get()->name.toUTF8()))
                    {
                        seaParaValuePtr.modify()->value = result.get(it->get()->name.toUTF8());
                    }
                }
                
                res = serialize(seaPtr, responseMsg);
            }
            catch (Wt::Json::ParseError const& e)
            {
                res = EReturnCode::BAD_REQUEST;
                responseMsg = httpCodeToJSON(res, e);
            }
            catch (Wt::Json::TypeException const& e)
            {
                res = EReturnCode::BAD_REQUEST;
                responseMsg = httpCodeToJSON(res, e);
            }
            
            transaction.commit();
        }
        catch (Wt::Dbo::Exception const& e)
        {
            res = EReturnCode::SERVICE_UNAVAILABLE;
            responseMsg = httpCodeToJSON(res, e);
        }
    }

    return res;
}

EReturnCode SearchResource::processPutRequest(const Wt::Http::Request &request, const long long &orgId, std::string &responseMsg)
{
    EReturnCode res = EReturnCode::INTERNAL_SERVER_ERROR;
    string nextElement = "";
    unsigned short indexPathElement = 1;
    vector<string> pathElements;
    map<string, long long> parameters;

    const string sRequest = processRequestParameters(request, pathElements, parameters);

    nextElement = getNextElementFromPath(indexPathElement, pathElements);
    if (nextElement.empty())
    {
        res = EReturnCode::BAD_REQUEST;
        const string err = "[Search Resource] bad nextElement";
        responseMsg = httpCodeToJSON(res, err);
    }
    else
    {
        try
        {
            boost::lexical_cast<unsigned long long>(nextElement);

            nextElement = getNextElementFromPath(indexPathElement, pathElements);

            if (nextElement.empty())
            {
                res = putSearch(orgId, responseMsg, pathElements, sRequest);
            }
            else
            {
                res = EReturnCode::BAD_REQUEST;
                const string err = "[Search Resource] bad nextElement";
                responseMsg = httpCodeToJSON(res, err);
            }
        }
        catch (boost::bad_lexical_cast const& e)
        {
            res = EReturnCode::BAD_REQUEST;
            responseMsg = httpCodeToJSON(res, e);
        }
    }

    return res;
}

EReturnCode SearchResource::deleteSearch(const long long &orgId, std::string &responseMsg, const std::vector<std::string> &pathElements, const std::string &sRequest, std::map<string, long long> parameters)
{
    EReturnCode res = EReturnCode::INTERNAL_SERVER_ERROR;

    try 
    {  
        Wt::Dbo::Transaction transaction(m_session, true);
           
        Wt::Dbo::ptr<Echoes::Dbo::Search> seaPtr = selectSearch(pathElements[1], orgId, m_session);

        if(seaPtr)
        {
            Wt::Dbo::collection<Wt::Dbo::ptr<Echoes::Dbo::Filter>> filPtrCol = m_session.find<Echoes::Dbo::Filter>()
                    .where(QUOTE(TRIGRAM_FILTER SEP TRIGRAM_SEARCH SEP TRIGRAM_SEARCH ID)" = ?").bind(pathElements[1])
                    .where(QUOTE(TRIGRAM_FILTER SEP "DELETE") " IS NULL");

            if (filPtrCol.size() == 0)
            {
                seaPtr.modify()->deleteTag = Wt::WDateTime::currentDateTime();
                res = EReturnCode::NO_CONTENT;
            }
            else
            {
                res = EReturnCode::CONFLICT;
                responseMsg = httpCodeToJSON(res, seaPtr);
            } 
        }
        else
        {
            res = EReturnCode::NOT_FOUND;
            responseMsg = httpCodeToJSON(res, seaPtr);
        }

        transaction.commit();
    }
    catch (boost::bad_lexical_cast const& e)
    {
        res = EReturnCode::BAD_REQUEST;
        responseMsg = httpCodeToJSON(res, e);
    }

    return res;
}

EReturnCode SearchResource::processDeleteRequest(const Wt::Http::Request &request, const long long &orgId, std::string &responseMsg)
{
    EReturnCode res = EReturnCode::INTERNAL_SERVER_ERROR;
    string nextElement = "";
    unsigned short indexPathElement = 1;
    vector<string> pathElements;
    map<string, long long> parameters;

    const string sRequest = processRequestParameters(request, pathElements, parameters);

    nextElement = getNextElementFromPath(indexPathElement, pathElements);
    if (nextElement.empty())
    {
        res = EReturnCode::BAD_REQUEST;
        const string err = "[Search Resource] bad nextElement";
        responseMsg = httpCodeToJSON(res, err);
    }
    else
    {
        try
        {
            boost::lexical_cast<unsigned long long>(nextElement);

            nextElement = getNextElementFromPath(indexPathElement, pathElements);

            if (nextElement.empty())
            {
                res = deleteSearch(orgId, responseMsg, pathElements);
            }
            else
            {
                res = EReturnCode::BAD_REQUEST;
                const string err = "[Search Resource] bad nextElement";
                responseMsg = httpCodeToJSON(res, err);
            }
        }
        catch (boost::bad_lexical_cast const& e)
        {
            res = EReturnCode::BAD_REQUEST;
            responseMsg = httpCodeToJSON(res, e);
        }
    }

    return res;
}

