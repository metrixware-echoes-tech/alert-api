/* 
 * Header of API AlertResource
 * @author ECHOES Technologies (GDR)
 * @date 05/02/2013
 * 
 * THIS PROGRAM IS CONFIDENTIAL AND PROPRIETARY TO ECHOES TECHNOLOGIES SAS
 * AND MAY NOT BE REPRODUCED, PUBLISHED OR DISCLOSED TO OTHERS WITHOUT
 * COMPANY AUTHORIZATION.
 * 
 * COPYRIGHT 2013 BY ECHOES TECHNOLGIES SAS
 * 
 */

#ifndef ALERTRESOURCE_H
#define	ALERTRESOURCE_H

#include <Wt/Mail/Client>
#include <Wt/Mail/Message>

#include "Conf.h"
#include "PublicApiResource.h"
#include "MediaResource.h"
#include "itooki/ItookiSMSSender.h"

class AlertResource : public PublicApiResource
{
    public :
        AlertResource();
        virtual ~AlertResource();

        /**
         * Select an Alert
         * @param aleId Identifier of Alert
         * @param orgId Identifier of Organization
         * @return Alert Wt Dbo Pointer
         */
        static Wt::Dbo::ptr<Echoes::Dbo::Alert> selectAlert(const long long &aleId, const long long &orgId, Echoes::Dbo::Session &session);
        /**
         * Select an Alert with a ID string
         * @param aleId String of Identifier of Alert
         * @param orgId String of Identifier of Organization
         * @return Alert Wt Dbo Pointer
         */
        static Wt::Dbo::ptr<Echoes::Dbo::Alert> selectAlert(const std::string &aleId, const std::string &orgId, Echoes::Dbo::Session &session);

    protected:
        EReturnCode getRecipientsForAlert(std::string &responseMsg);       
        EReturnCode getTrackingsForAlertsList(std::string &responseMsg);
//        EReturnCode getTrackingAlertList(std::string &responseMsg);
        EReturnCode getAlertsList(std::string &responseMsg);
        EReturnCode getAlert(std::string &responseMsg);
        virtual void processGetRequest(Wt::Http::Response &response);

        /**
         * method to send a MAIL 
         * @param collection of informations values that matches the alert
         * @param the alert
         * @param the alert tracking required and concerned by the sms
         * @param the media value concern by the alert
         * @param if the user as use all his sms, the value here is 1 if not it's 0
         * @return HTTP Code
         */
        EReturnCode sendMAIL
        (
            std::vector<Wt::Dbo::ptr<Echoes::Dbo::InformationValue>> ivaPtrVector,
            Wt::Dbo::ptr<Echoes::Dbo::Alert> alePtr,
            Wt::Dbo::ptr<Echoes::Dbo::AlertTracking> atrPtr,
            Wt::Dbo::ptr<Echoes::Dbo::AlertMediaSpecialization> amsPtr,
            bool overSMSQuota = false
        );

        /**
         * method to send an SMS with the call of the API
         * @param collection of informations values that matches the alert
         * @param the alert
         * @param the alert tracking required and concerned by the sms
         * @param the media value concern by the alert
         * @return HTTP Code
         */
        EReturnCode sendSMS
        (
            std::vector<Wt::Dbo::ptr<Echoes::Dbo::InformationValue>> ivaPtrVector,
            Wt::Dbo::ptr<Echoes::Dbo::Alert> alePtr,
            Wt::Dbo::ptr<Echoes::Dbo::AlertTracking> atrPtr,
            Wt::Dbo::ptr<Echoes::Dbo::AlertMediaSpecialization> amsPtr
        );

        /**
         * method to put a date and content in Alertetracking table 
         * @param collection of informations values that matches the alert
         * @param the alert
         * @param the alert tracking required and concerned by the sms
         * @param the media value concern by the alert
         * @return HTTP Code
         */
        EReturnCode sendMobileApp
        (
         std::vector<Wt::Dbo::ptr<Echoes::Dbo::InformationValue >> ivaPtrVector,
         Wt::Dbo::ptr<Echoes::Dbo::Alert> alePtr,
         Wt::Dbo::ptr<Echoes::Dbo::AlertTracking> atrPtr,
         Wt::Dbo::ptr<Echoes::Dbo::AlertMediaSpecialization> amsPtr
        );
        
        EReturnCode postAlert(std::string &responseMsg, const std::string &sRequest);
        EReturnCode postAlertTracking(std::string &responseMsg, const std::string &sRequest);
        virtual void processPostRequest(Wt::Http::Response &response);

        virtual void processPutRequest(Wt::Http::Response &response);

        EReturnCode deleteAlert(std::string &responseMsg);
        virtual void processDeleteRequest(Wt::Http::Response &response);
};
#endif	/* ALERTRESOURCE_H */

