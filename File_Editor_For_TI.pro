#########################################################################################################################
#																														#
#													Thomas RICHARD														#
#																														#
#########################################################################################################################
#																														#
#											  Projet : File_Editor_For_TI												#
#																														#
#########################################################################################################################

##################################################### Application #######################################################
APPLICATION		=	File_Editor_For_TI

################################################## Paramètres globaux ###################################################
TEMPLATE	=	subdirs
SUBDIRS		=	TiFile \
				File_Editor_For_TI

message(Application $$APPLICATION)


#################################################### Configuration ######################################################
CONFIG		+=	ordered

################################################ Cibles supplémentaires #################################################
#make_doc.target		=	doc
#make_doc.commands	=	doxygen $${APPLICATION}.doxyfile > doxygen_log.log

#QMAKE_EXTRA_TARGETS		+=	make_doc


