/* 
 * Header of API CriterionResource
 * @author ECHOES Technologies (GDR)
 * @date 21/02/2013
 * 
 * THIS PROGRAM IS CONFIDENTIAL AND PROPRIETARY TO ECHOES TECHNOLOGIES SAS
 * AND MAY NOT BE REPRODUCED, PUBLISHED OR DISCLOSED TO OTHERS WITHOUT
 * COMPANY AUTHORIZATION.
 * 
 * COPYRIGHT 2013 BY ECHOES TECHNOLGIES SAS
 * 
 */

#ifndef CRITERIONRESOURCE_H
#define	CRITERIONRESOURCE_H

#include "PublicApiResource.h"

class CriterionResource : public PublicApiResource
{
    public :
        CriterionResource(Echoes::Dbo::Session& session);
        virtual ~CriterionResource();

    protected :
        EReturnCode Error       (const long long &orgId, std::string &responseMsg, const std::vector<std::string> &pathElements = std::vector<std::string>(), const std::string &sRequest = NULL, std::map<string, long long> parameters = std::map<string, long long>());
        
        EReturnCode getCriteriaList(const long long &orgId, std::string &responseMsg, const std::vector<std::string> &pathElements = std::vector<std::string>(), const std::string &sRequest = NULL, std::map<string, long long> parameters = std::map<string, long long>());
        EReturnCode getCriterion(const long long &orgId, std::string &responseMsg, const std::vector<std::string> &pathElements = std::vector<std::string>(), const std::string &sRequest = NULL, std::map<string, long long> parameters = std::map<string, long long>());
        EReturnCode getAliasForCriterion(const long long &orgId, std::string &responseMsg, const std::vector<std::string> &pathElements = std::vector<std::string>(), const std::string &sRequest = NULL, std::map<string, long long> parameters = std::map<string, long long>());
        virtual EReturnCode processGetRequest(const Wt::Http::Request &request, const long long &orgId, std::string &responseMsg);

        EReturnCode putAliasForCriterion(const long long &orgId, std::string &responseMsg, const std::vector<std::string> &pathElements = std::vector<std::string>(), const std::string &sRequest = NULL, std::map<string, long long> parameters = std::map<string, long long>());
        virtual EReturnCode processPutRequest(const Wt::Http::Request &request, const long long &orgId, std::string &responseMsg);
};

#endif	/* CRITERIONRESOURCE_H */

