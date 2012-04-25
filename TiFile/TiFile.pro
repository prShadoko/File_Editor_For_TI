#########################################################################################################################
#																														#
#													Thomas RICHARD														#
#																														#
#########################################################################################################################
#																														#
#										Projet : File_Editor_For_TI / TiFile											#
#																														#
#########################################################################################################################

############################################## Informations sur le projet ###############################################
PROJECT		=	TiFile
VER_MAJ		=	1
VER_MIN		=	0
VER_PAT		=	0

################################################# Réglages utilisateur ##################################################
win32:CONFIG(debug,debug|release):CONFIG += console

################################################## Suffixe automatique ##################################################
PROJECT_SUFFIX	=
CONFIG(debug, debug|release) {
	PROJECT_SUFFIX	=	d
}

################################################## Paramètres globaux ###################################################
TARGET		=	$${PROJECT}$${PROJECT_SUFFIX}
TEMPLATE	=	app
VERSION		=	$${VER_MAJ}.$${VER_MIN}.$${VER_PAT}

message(Projet $$PROJECT $$VERSION)

#################################################### Configuration ######################################################
CONFIG	+=	warn_on silent

####################################################### Nettoyage #######################################################
win32:QMAKE_DISTCLEAN	+=	*_resource.rc \
							object_script.*

QMAKE_DISTCLEAN			+=	*.log

################################################ Paramètres compilateur #################################################
QMAKE_CXXFLAGS				+=	-Wall -Wold-style-cast -Wredundant-decls -Winit-self -Wundef# -Winline
QMAKE_CXXFLAGS_RELEASE		+=	-O2 -fomit-frame-pointer -s# -fexpensive-optimisations

###################################################### Répertoires ######################################################
RACINE		=	..

DESTDIR		=	$${RACINE}/Final

OBJECTS_DIR	=	$${RACINE}/Temp/$${PROJECT}/objs$${PROJECT_SUFFIX}
MOC_DIR		=	$${RACINE}/Temp/$${PROJECT}/mocs$${PROJECT_SUFFIX}
RCC_DIR		=	$${RACINE}/Temp/$${PROJECT}/rccs$${PROJECT_SUFFIX}

##################################################### Configuration #####################################################
CODECFORTR	=	UTF-8
CODECFORSRC	=	UTF-8

######################################################## Fichiers #######################################################
HEADERS		+=	*.h
SOURCES		+=	*.cpp

OTHER_FILES += \
    TODO.txt
