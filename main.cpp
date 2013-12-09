/* 
 * API Asset Ressource
 * @author ECHOES Technologies (TSA)
 * @date 08/08/2012
 * 
 * THIS PROGRAM IS CONFIDENTIAL AND PROPRIETARY TO ECHOES TECHNOLOGIES SAS
 * AND MAY NOT BE REPRODUCED, PUBLISHED OR DISCLOSED TO OTHERS WITHOUT
 * COMPANY AUTHORIZATION.
 * 
 * COPYRIGHT 2012-2013 BY ECHOES TECHNOLGIES SAS
 * 
 */

#ifndef main

#include <signal.h>

#include "Conf.h"

#include "PublicApiResource.h"

#include "AddonResource.h"
#include "AlertResource.h"
#include "AssetResource.h"
#include "CriterionResource.h"
#include "FilterResource.h"
#include "InformationResource.h"
#include "MediaResource.h"
#include "OptionResource.h"
#include "OrganizationResource.h"
#include "PluginResource.h"
#include "ProbeResource.h"
#include "RoleResource.h"
#include "SearchResource.h"
#include "SourceResource.h"
#include "UnitResource.h"
#include "UserResource.h"

#include "ItookiAckReceiver.h"
#include "ItookiAswReceiver.h"

#endif

using namespace std;

/**
 * Main function
 * @param argc Number of arguments passed to the program
 * @param argv Array of arguments passed to the program
 * @return Exit status
 */
int main(int argc, char **argv)
{
    #ifndef main
    int res = EXIT_FAILURE;
    
    try
    {
        // use argv[0] as the application name to match a suitable entry
        // in the Wt configuration file
        Wt::WServer server(argv[0]);

        // On définit la configuration du serveur en lui passant les paramètres d'entrée et son fichier de configuration
        server.setServerConfiguration(argc, argv);

        if (conf.readProperties(server))
        {
            AddonResource        addonResource;
            AlertResource        alertResource;
            AssetResource        assetResource;
            CriterionResource    criteriaResource;
            FilterResource       filterResource;
            InformationResource  informationRessource;
            MediaResource        mediaResource;
            OptionResource       optionRessource;
            OrganizationResource organizationRessource;
            PluginResource       pluginResource;
            ProbeResource        probeResource;
            SearchResource       searchResource;
            SourceResource       sourceResource;
            UnitResource         unitResource;
            UserResource         userResource;
            RoleResource         roleResource;
            ItookiAckReceiver    itookiAckReceiver;
            ItookiAswReceiver    itookiAswReceiver;

            server.addResource(&addonResource,         "/addons");
            server.addResource(&alertResource,         "/alerts");
            server.addResource(&assetResource,         "/assets");
            server.addResource(&criteriaResource,      "/criteria");
            server.addResource(&filterResource,        "/filters");
            server.addResource(&informationRessource,  "/informations");
            server.addResource(&mediaResource,         "/medias");
            server.addResource(&optionRessource,       "/options");
            server.addResource(&organizationRessource, "/organizations");
            server.addResource(&pluginResource,        "/plugins");
            server.addResource(&probeResource,         "/probes");
            server.addResource(&roleResource,          "/roles");
            server.addResource(&searchResource,        "/searches");
            server.addResource(&sourceResource,        "/sources");
            server.addResource(&unitResource,          "/units");
            server.addResource(&userResource,          "/users");
            server.addResource(&itookiAckReceiver,     "/itooki/ack");
            server.addResource(&itookiAswReceiver,     "/itooki/asw");

            Echoes::Dbo::Session::configureAuth();

            // démarrage du serveur en arrière plan
            if (server.start())
            {
                // méthode qui bloque le thread courant en attendant le signal d'exctinction
                int sig = Wt::WServer::waitForShutdown(argv[0]);

                Wt::log("info") << "[Main] Shutdown (signal = " << sig << ")";

                server.stop();

                if (sig == SIGHUP)
                    Wt::WServer::restart(argc, argv, environ);

                res = EXIT_SUCCESS;
            }
        }
        else
            Wt::log("fatal") << "[Main] Every properties are not correctly set in " << WT_CONFIG_XML;
    }
    catch (Wt::WServer::Exception& e)
    {
        cerr << e.what() << endl;
    }
    catch (exception& e)
    {
        cerr << "exception: " << e.what() << endl;
    }
    return res;
    
    #else
    return 0;
    #endif
}

