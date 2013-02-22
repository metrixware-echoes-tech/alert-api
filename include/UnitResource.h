/* 
 * HEADER OF API UnitResource
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


#ifndef UNITRESOURCE_H
#define	UNITRESOURCE_H

#include "includeFile.h"

class UnitResource : public PublicApiResource
{
    public :
        UnitResource();
        virtual ~UnitResource();
        
    protected :

        std::string getSubUnitsForUnit();
        std::string getUnit();
        virtual void processGetRequest(const Wt::Http::Request &request, Wt::Http::Response &response);

        virtual void processPostRequest(const Wt::Http::Request &request, Wt::Http::Response &response);

        virtual void processPutRequest(const Wt::Http::Request &request, Wt::Http::Response &response);
        
        virtual void processPatchRequest(const Wt::Http::Request &request, Wt::Http::Response &response);

        virtual void processDeleteRequest(const Wt::Http::Request &request, Wt::Http::Response &response);

        virtual void handleRequest(const Wt::Http::Request &request, Wt::Http::Response &response);          
};


#endif	/* UNITRESOURCE_H */

