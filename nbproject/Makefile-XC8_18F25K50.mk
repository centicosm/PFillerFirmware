#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Include project Makefile
ifeq "${IGNORE_LOCAL}" "TRUE"
# do not include local makefile. User is passing all local related variables already
else
include Makefile
# Include makefile containing local settings
ifeq "$(wildcard nbproject/Makefile-local-XC8_18F25K50.mk)" "nbproject/Makefile-local-XC8_18F25K50.mk"
include nbproject/Makefile-local-XC8_18F25K50.mk
endif
endif

# Environment
MKDIR=gnumkdir -p
RM=rm -f 
MV=mv 
CP=cp 

# Macros
CND_CONF=XC8_18F25K50
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
IMAGE_TYPE=debug
OUTPUT_SUFFIX=cof
DEBUGGABLE_SUFFIX=cof
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/FeederController.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
else
IMAGE_TYPE=production
OUTPUT_SUFFIX=hex
DEBUGGABLE_SUFFIX=cof
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/FeederController.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
endif

# Object Directory
OBJECTDIR=build/${CND_CONF}/${IMAGE_TYPE}

# Distribution Directory
DISTDIR=dist/${CND_CONF}/${IMAGE_TYPE}

# Source Files Quoted if spaced
SOURCEFILES_QUOTED_IF_SPACED=configuration_bits.c main.c PLCD.c PDelay.c PSerial_RS232.c PScale.c PFiller_Init.c PFiller_Interrupts.c PFiller_Interface.c PFiller_SpeedTable.c PFlash.c

# Object Files Quoted if spaced
OBJECTFILES_QUOTED_IF_SPACED=${OBJECTDIR}/configuration_bits.o ${OBJECTDIR}/main.o ${OBJECTDIR}/PLCD.o ${OBJECTDIR}/PDelay.o ${OBJECTDIR}/PSerial_RS232.o ${OBJECTDIR}/PScale.o ${OBJECTDIR}/PFiller_Init.o ${OBJECTDIR}/PFiller_Interrupts.o ${OBJECTDIR}/PFiller_Interface.o ${OBJECTDIR}/PFiller_SpeedTable.o ${OBJECTDIR}/PFlash.o
POSSIBLE_DEPFILES=${OBJECTDIR}/configuration_bits.o.d ${OBJECTDIR}/main.o.d ${OBJECTDIR}/PLCD.o.d ${OBJECTDIR}/PDelay.o.d ${OBJECTDIR}/PSerial_RS232.o.d ${OBJECTDIR}/PScale.o.d ${OBJECTDIR}/PFiller_Init.o.d ${OBJECTDIR}/PFiller_Interrupts.o.d ${OBJECTDIR}/PFiller_Interface.o.d ${OBJECTDIR}/PFiller_SpeedTable.o.d ${OBJECTDIR}/PFlash.o.d

# Object Files
OBJECTFILES=${OBJECTDIR}/configuration_bits.o ${OBJECTDIR}/main.o ${OBJECTDIR}/PLCD.o ${OBJECTDIR}/PDelay.o ${OBJECTDIR}/PSerial_RS232.o ${OBJECTDIR}/PScale.o ${OBJECTDIR}/PFiller_Init.o ${OBJECTDIR}/PFiller_Interrupts.o ${OBJECTDIR}/PFiller_Interface.o ${OBJECTDIR}/PFiller_SpeedTable.o ${OBJECTDIR}/PFlash.o

# Source Files
SOURCEFILES=configuration_bits.c main.c PLCD.c PDelay.c PSerial_RS232.c PScale.c PFiller_Init.c PFiller_Interrupts.c PFiller_Interface.c PFiller_SpeedTable.c PFlash.c


CFLAGS=
ASFLAGS=
LDLIBSOPTIONS=

############# Tool locations ##########################################
# If you copy a project from one host to another, the path where the  #
# compiler is installed may be different.                             #
# If you open this project with MPLAB X in the new host, this         #
# makefile will be regenerated and the paths will be corrected.       #
#######################################################################
# fixDeps replaces a bunch of sed/cat/printf statements that slow down the build
FIXDEPS=fixDeps

.build-conf:  ${BUILD_SUBPROJECTS}
ifneq ($(INFORMATION_MESSAGE), )
	@echo $(INFORMATION_MESSAGE)
endif
	${MAKE}  -f nbproject/Makefile-XC8_18F25K50.mk dist/${CND_CONF}/${IMAGE_TYPE}/FeederController.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}

MP_PROCESSOR_OPTION=18F25K50
MP_PROCESSOR_OPTION_LD=18f25k50
MP_LINKER_DEBUG_OPTION=  -u_DEBUGSTACK
# ------------------------------------------------------------------------------------
# Rules for buildStep: assemble
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: compile
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/configuration_bits.o: configuration_bits.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/configuration_bits.o.d 
	@${RM} ${OBJECTDIR}/configuration_bits.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -p$(MP_PROCESSOR_OPTION) -k -oi --verbose -w3 -ms --extended -sa -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/configuration_bits.o   configuration_bits.c 
	@${DEP_GEN} -d ${OBJECTDIR}/configuration_bits.o 
	@${FIXDEPS} "${OBJECTDIR}/configuration_bits.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/main.o: main.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/main.o.d 
	@${RM} ${OBJECTDIR}/main.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -p$(MP_PROCESSOR_OPTION) -k -oi --verbose -w3 -ms --extended -sa -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/main.o   main.c 
	@${DEP_GEN} -d ${OBJECTDIR}/main.o 
	@${FIXDEPS} "${OBJECTDIR}/main.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/PLCD.o: PLCD.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/PLCD.o.d 
	@${RM} ${OBJECTDIR}/PLCD.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -p$(MP_PROCESSOR_OPTION) -k -oi --verbose -w3 -ms --extended -sa -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/PLCD.o   PLCD.c 
	@${DEP_GEN} -d ${OBJECTDIR}/PLCD.o 
	@${FIXDEPS} "${OBJECTDIR}/PLCD.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/PDelay.o: PDelay.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/PDelay.o.d 
	@${RM} ${OBJECTDIR}/PDelay.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -p$(MP_PROCESSOR_OPTION) -k -oi --verbose -w3 -ms --extended -sa -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/PDelay.o   PDelay.c 
	@${DEP_GEN} -d ${OBJECTDIR}/PDelay.o 
	@${FIXDEPS} "${OBJECTDIR}/PDelay.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/PSerial_RS232.o: PSerial_RS232.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/PSerial_RS232.o.d 
	@${RM} ${OBJECTDIR}/PSerial_RS232.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -p$(MP_PROCESSOR_OPTION) -k -oi --verbose -w3 -ms --extended -sa -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/PSerial_RS232.o   PSerial_RS232.c 
	@${DEP_GEN} -d ${OBJECTDIR}/PSerial_RS232.o 
	@${FIXDEPS} "${OBJECTDIR}/PSerial_RS232.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/PScale.o: PScale.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/PScale.o.d 
	@${RM} ${OBJECTDIR}/PScale.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -p$(MP_PROCESSOR_OPTION) -k -oi --verbose -w3 -ms --extended -sa -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/PScale.o   PScale.c 
	@${DEP_GEN} -d ${OBJECTDIR}/PScale.o 
	@${FIXDEPS} "${OBJECTDIR}/PScale.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/PFiller_Init.o: PFiller_Init.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/PFiller_Init.o.d 
	@${RM} ${OBJECTDIR}/PFiller_Init.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -p$(MP_PROCESSOR_OPTION) -k -oi --verbose -w3 -ms --extended -sa -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/PFiller_Init.o   PFiller_Init.c 
	@${DEP_GEN} -d ${OBJECTDIR}/PFiller_Init.o 
	@${FIXDEPS} "${OBJECTDIR}/PFiller_Init.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/PFiller_Interrupts.o: PFiller_Interrupts.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/PFiller_Interrupts.o.d 
	@${RM} ${OBJECTDIR}/PFiller_Interrupts.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -p$(MP_PROCESSOR_OPTION) -k -oi --verbose -w3 -ms --extended -sa -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/PFiller_Interrupts.o   PFiller_Interrupts.c 
	@${DEP_GEN} -d ${OBJECTDIR}/PFiller_Interrupts.o 
	@${FIXDEPS} "${OBJECTDIR}/PFiller_Interrupts.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/PFiller_Interface.o: PFiller_Interface.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/PFiller_Interface.o.d 
	@${RM} ${OBJECTDIR}/PFiller_Interface.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -p$(MP_PROCESSOR_OPTION) -k -oi --verbose -w3 -ms --extended -sa -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/PFiller_Interface.o   PFiller_Interface.c 
	@${DEP_GEN} -d ${OBJECTDIR}/PFiller_Interface.o 
	@${FIXDEPS} "${OBJECTDIR}/PFiller_Interface.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/PFiller_SpeedTable.o: PFiller_SpeedTable.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/PFiller_SpeedTable.o.d 
	@${RM} ${OBJECTDIR}/PFiller_SpeedTable.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -p$(MP_PROCESSOR_OPTION) -k -oi --verbose -w3 -ms --extended -sa -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/PFiller_SpeedTable.o   PFiller_SpeedTable.c 
	@${DEP_GEN} -d ${OBJECTDIR}/PFiller_SpeedTable.o 
	@${FIXDEPS} "${OBJECTDIR}/PFiller_SpeedTable.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/PFlash.o: PFlash.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/PFlash.o.d 
	@${RM} ${OBJECTDIR}/PFlash.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -p$(MP_PROCESSOR_OPTION) -k -oi --verbose -w3 -ms --extended -sa -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/PFlash.o   PFlash.c 
	@${DEP_GEN} -d ${OBJECTDIR}/PFlash.o 
	@${FIXDEPS} "${OBJECTDIR}/PFlash.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
else
${OBJECTDIR}/configuration_bits.o: configuration_bits.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/configuration_bits.o.d 
	@${RM} ${OBJECTDIR}/configuration_bits.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION) -k -oi --verbose -w3 -ms --extended -sa -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/configuration_bits.o   configuration_bits.c 
	@${DEP_GEN} -d ${OBJECTDIR}/configuration_bits.o 
	@${FIXDEPS} "${OBJECTDIR}/configuration_bits.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/main.o: main.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/main.o.d 
	@${RM} ${OBJECTDIR}/main.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION) -k -oi --verbose -w3 -ms --extended -sa -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/main.o   main.c 
	@${DEP_GEN} -d ${OBJECTDIR}/main.o 
	@${FIXDEPS} "${OBJECTDIR}/main.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/PLCD.o: PLCD.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/PLCD.o.d 
	@${RM} ${OBJECTDIR}/PLCD.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION) -k -oi --verbose -w3 -ms --extended -sa -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/PLCD.o   PLCD.c 
	@${DEP_GEN} -d ${OBJECTDIR}/PLCD.o 
	@${FIXDEPS} "${OBJECTDIR}/PLCD.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/PDelay.o: PDelay.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/PDelay.o.d 
	@${RM} ${OBJECTDIR}/PDelay.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION) -k -oi --verbose -w3 -ms --extended -sa -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/PDelay.o   PDelay.c 
	@${DEP_GEN} -d ${OBJECTDIR}/PDelay.o 
	@${FIXDEPS} "${OBJECTDIR}/PDelay.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/PSerial_RS232.o: PSerial_RS232.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/PSerial_RS232.o.d 
	@${RM} ${OBJECTDIR}/PSerial_RS232.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION) -k -oi --verbose -w3 -ms --extended -sa -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/PSerial_RS232.o   PSerial_RS232.c 
	@${DEP_GEN} -d ${OBJECTDIR}/PSerial_RS232.o 
	@${FIXDEPS} "${OBJECTDIR}/PSerial_RS232.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/PScale.o: PScale.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/PScale.o.d 
	@${RM} ${OBJECTDIR}/PScale.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION) -k -oi --verbose -w3 -ms --extended -sa -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/PScale.o   PScale.c 
	@${DEP_GEN} -d ${OBJECTDIR}/PScale.o 
	@${FIXDEPS} "${OBJECTDIR}/PScale.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/PFiller_Init.o: PFiller_Init.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/PFiller_Init.o.d 
	@${RM} ${OBJECTDIR}/PFiller_Init.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION) -k -oi --verbose -w3 -ms --extended -sa -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/PFiller_Init.o   PFiller_Init.c 
	@${DEP_GEN} -d ${OBJECTDIR}/PFiller_Init.o 
	@${FIXDEPS} "${OBJECTDIR}/PFiller_Init.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/PFiller_Interrupts.o: PFiller_Interrupts.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/PFiller_Interrupts.o.d 
	@${RM} ${OBJECTDIR}/PFiller_Interrupts.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION) -k -oi --verbose -w3 -ms --extended -sa -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/PFiller_Interrupts.o   PFiller_Interrupts.c 
	@${DEP_GEN} -d ${OBJECTDIR}/PFiller_Interrupts.o 
	@${FIXDEPS} "${OBJECTDIR}/PFiller_Interrupts.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/PFiller_Interface.o: PFiller_Interface.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/PFiller_Interface.o.d 
	@${RM} ${OBJECTDIR}/PFiller_Interface.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION) -k -oi --verbose -w3 -ms --extended -sa -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/PFiller_Interface.o   PFiller_Interface.c 
	@${DEP_GEN} -d ${OBJECTDIR}/PFiller_Interface.o 
	@${FIXDEPS} "${OBJECTDIR}/PFiller_Interface.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/PFiller_SpeedTable.o: PFiller_SpeedTable.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/PFiller_SpeedTable.o.d 
	@${RM} ${OBJECTDIR}/PFiller_SpeedTable.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION) -k -oi --verbose -w3 -ms --extended -sa -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/PFiller_SpeedTable.o   PFiller_SpeedTable.c 
	@${DEP_GEN} -d ${OBJECTDIR}/PFiller_SpeedTable.o 
	@${FIXDEPS} "${OBJECTDIR}/PFiller_SpeedTable.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/PFlash.o: PFlash.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/PFlash.o.d 
	@${RM} ${OBJECTDIR}/PFlash.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION) -k -oi --verbose -w3 -ms --extended -sa -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/PFlash.o   PFlash.c 
	@${DEP_GEN} -d ${OBJECTDIR}/PFlash.o 
	@${FIXDEPS} "${OBJECTDIR}/PFlash.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: link
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
dist/${CND_CONF}/${IMAGE_TYPE}/FeederController.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk    
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_LD} $(MP_EXTRA_LD_PRE)   -p$(MP_PROCESSOR_OPTION_LD)  -w -x -u_DEBUG -m"outpaw.map" -u_EXTENDEDMODE -g -z__MPLAB_BUILD=1  -u_CRUNTIME -z__MPLAB_DEBUG=1 -z__MPLAB_DEBUGGER_PK3=1 $(MP_LINKER_DEBUG_OPTION) -l ${MP_CC_DIR}\\..\\lib  -o dist/${CND_CONF}/${IMAGE_TYPE}/FeederController.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}  ${OBJECTFILES_QUOTED_IF_SPACED}   
else
dist/${CND_CONF}/${IMAGE_TYPE}/FeederController.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk   
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_LD} $(MP_EXTRA_LD_PRE)   -p$(MP_PROCESSOR_OPTION_LD)  -w  -m"outpaw.map" -u_EXTENDEDMODE -g -z__MPLAB_BUILD=1  -u_CRUNTIME -l ${MP_CC_DIR}\\..\\lib  -o dist/${CND_CONF}/${IMAGE_TYPE}/FeederController.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX}  ${OBJECTFILES_QUOTED_IF_SPACED}   
endif


# Subprojects
.build-subprojects:


# Subprojects
.clean-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r build/XC8_18F25K50
	${RM} -r dist/XC8_18F25K50

# Enable dependency checking
.dep.inc: .depcheck-impl

DEPFILES=$(shell mplabwildcard ${POSSIBLE_DEPFILES})
ifneq (${DEPFILES},)
include ${DEPFILES}
endif
