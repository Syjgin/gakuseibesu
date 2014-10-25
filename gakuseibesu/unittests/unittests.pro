SOURCES += unittests.cpp\
            ..\database.cpp
	    
HEADERS += unittests.h \
            ..\database.h \
            ..\grade.h \
            ..\profile.h
	    
	    
QT += testlib sql
CONFIG  += c++11

 # install
 # target.path = $$[QT_INSTALL_EXAMPLES]/qtestlib/tutorial1
 # sources.files = $$SOURCES *.pro
 # sources.path = $$[QT_INSTALL_EXAMPLES]/qtestlib/tutorial1
 INSTALLS += target sources 

FORMS += \
    searchdialog.ui
