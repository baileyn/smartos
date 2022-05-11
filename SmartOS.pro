TEMPLATE = subdirs

SUBDIRS += \
    SmartOS_GUI \
    SmartOS_Core

SmartOS_GUI.depends = SmartOS_Core
