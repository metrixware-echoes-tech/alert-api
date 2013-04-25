#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Environment
MKDIR=mkdir
CP=cp
GREP=grep
NM=nm
CCADMIN=CCadmin
RANLIB=ranlib
CC=gcc
CCC=g++
CXX=g++
FC=gfortran
AS=as

# Macros
CND_PLATFORM=GNU-Linux-x86
CND_DLIB_EXT=so
CND_CONF=Release
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/main.o \
	${OBJECTDIR}/src/AddonResource.o \
	${OBJECTDIR}/src/AlertResource.o \
	${OBJECTDIR}/src/AssetResource.o \
	${OBJECTDIR}/src/Conf.o \
	${OBJECTDIR}/src/CriteriaResource.o \
	${OBJECTDIR}/src/InformationResource.o \
	${OBJECTDIR}/src/MediaResource.o \
	${OBJECTDIR}/src/OrganizationResource.o \
	${OBJECTDIR}/src/PluginResource.o \
	${OBJECTDIR}/src/ProbeResource.o \
	${OBJECTDIR}/src/PublicApiResource.o \
	${OBJECTDIR}/src/SearchTypeResource.o \
	${OBJECTDIR}/src/UnitResource.o \
	${OBJECTDIR}/src/UserResource.o \
	${OBJECTDIR}/src/itooki/ItookiSMSSender.o


# C Compiler Flags
CFLAGS=

# CC Compiler Flags
CCFLAGS=-std=c++0x
CXXFLAGS=-std=c++0x

# Fortran Compiler Flags
FFLAGS=

# Assembler Flags
ASFLAGS=

# Link Libraries and Options
LDLIBSOPTIONS=-L/var/lib/jenkins/jobs/ea-dbo-${target}/workspace/default/dist/Release_SharedObject/GNU-Linux-x86 -L../dbo/dist/Release_SharedObject/GNU-Linux-x86 -lwt -lwtdbo -lwtdbopostgres -lwtfcgi -ldbo -lboost_filesystem -lboost_signals -lboost_system

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/api

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/api: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	g++ -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/api ${OBJECTFILES} ${LDLIBSOPTIONS} -s

${OBJECTDIR}/main.o: main.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O3 -s -Iinclude -I../dbo/include -I/var/lib/jenkins/jobs/ea-dbo-${target}/workspace/include -std=c++0x -MMD -MP -MF $@.d -o ${OBJECTDIR}/main.o main.cpp

${OBJECTDIR}/src/AddonResource.o: src/AddonResource.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -O3 -s -Iinclude -I../dbo/include -I/var/lib/jenkins/jobs/ea-dbo-${target}/workspace/include -std=c++0x -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/AddonResource.o src/AddonResource.cpp

${OBJECTDIR}/src/AlertResource.o: src/AlertResource.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -O3 -s -Iinclude -I../dbo/include -I/var/lib/jenkins/jobs/ea-dbo-${target}/workspace/include -std=c++0x -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/AlertResource.o src/AlertResource.cpp

${OBJECTDIR}/src/AssetResource.o: src/AssetResource.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -O3 -s -Iinclude -I../dbo/include -I/var/lib/jenkins/jobs/ea-dbo-${target}/workspace/include -std=c++0x -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/AssetResource.o src/AssetResource.cpp

${OBJECTDIR}/src/Conf.o: src/Conf.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -O3 -s -Iinclude -I../dbo/include -I/var/lib/jenkins/jobs/ea-dbo-${target}/workspace/include -std=c++0x -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/Conf.o src/Conf.cpp

${OBJECTDIR}/src/CriteriaResource.o: src/CriteriaResource.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -O3 -s -Iinclude -I../dbo/include -I/var/lib/jenkins/jobs/ea-dbo-${target}/workspace/include -std=c++0x -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/CriteriaResource.o src/CriteriaResource.cpp

${OBJECTDIR}/src/InformationResource.o: src/InformationResource.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -O3 -s -Iinclude -I../dbo/include -I/var/lib/jenkins/jobs/ea-dbo-${target}/workspace/include -std=c++0x -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/InformationResource.o src/InformationResource.cpp

${OBJECTDIR}/src/MediaResource.o: src/MediaResource.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -O3 -s -Iinclude -I../dbo/include -I/var/lib/jenkins/jobs/ea-dbo-${target}/workspace/include -std=c++0x -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/MediaResource.o src/MediaResource.cpp

${OBJECTDIR}/src/OrganizationResource.o: src/OrganizationResource.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -O3 -s -Iinclude -I../dbo/include -I/var/lib/jenkins/jobs/ea-dbo-${target}/workspace/include -std=c++0x -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/OrganizationResource.o src/OrganizationResource.cpp

${OBJECTDIR}/src/PluginResource.o: src/PluginResource.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -O3 -s -Iinclude -I../dbo/include -I/var/lib/jenkins/jobs/ea-dbo-${target}/workspace/include -std=c++0x -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/PluginResource.o src/PluginResource.cpp

${OBJECTDIR}/src/ProbeResource.o: src/ProbeResource.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -O3 -s -Iinclude -I../dbo/include -I/var/lib/jenkins/jobs/ea-dbo-${target}/workspace/include -std=c++0x -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/ProbeResource.o src/ProbeResource.cpp

${OBJECTDIR}/src/PublicApiResource.o: src/PublicApiResource.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -O3 -s -Iinclude -I../dbo/include -I/var/lib/jenkins/jobs/ea-dbo-${target}/workspace/include -std=c++0x -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/PublicApiResource.o src/PublicApiResource.cpp

${OBJECTDIR}/src/SearchTypeResource.o: src/SearchTypeResource.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -O3 -s -Iinclude -I../dbo/include -I/var/lib/jenkins/jobs/ea-dbo-${target}/workspace/include -std=c++0x -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/SearchTypeResource.o src/SearchTypeResource.cpp

${OBJECTDIR}/src/UnitResource.o: src/UnitResource.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -O3 -s -Iinclude -I../dbo/include -I/var/lib/jenkins/jobs/ea-dbo-${target}/workspace/include -std=c++0x -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/UnitResource.o src/UnitResource.cpp

${OBJECTDIR}/src/UserResource.o: src/UserResource.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -O3 -s -Iinclude -I../dbo/include -I/var/lib/jenkins/jobs/ea-dbo-${target}/workspace/include -std=c++0x -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/UserResource.o src/UserResource.cpp

${OBJECTDIR}/src/itooki/ItookiSMSSender.o: src/itooki/ItookiSMSSender.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/itooki
	${RM} $@.d
	$(COMPILE.cc) -O3 -s -Iinclude -I../dbo/include -I/var/lib/jenkins/jobs/ea-dbo-${target}/workspace/include -std=c++0x -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/itooki/ItookiSMSSender.o src/itooki/ItookiSMSSender.cpp

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/api

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
