SafariZone_North_RestHouse_Frlg_MapScripts::
    .byte 0


SafariZone_North_RestHouse_Frlg_EventScript_Gentleman::
    lock
    faceplayer
    msgbox SafariZone_North_RestHouse_Frlg_Text_Gentleman, MSGBOX_DEFAULT
    release
    end


SafariZone_North_RestHouse_Frlg_EventScript_Scientist::
    lock
    faceplayer
    msgbox SafariZone_North_RestHouse_Frlg_Text_Scientist, MSGBOX_DEFAULT
    release
    end


SafariZone_North_RestHouse_Frlg_EventScript_Fisher::
    lock
    faceplayer
    msgbox SafariZone_North_RestHouse_Frlg_Text_Fisher, MSGBOX_DEFAULT
    release
    end


SafariZone_North_RestHouse_Frlg_EventScript_BaldingMan::
    lock
    faceplayer
    msgbox SafariZone_North_RestHouse_Frlg_Text_BaldingMan, MSGBOX_DEFAULT
    release
    end


SafariZone_North_RestHouse_Frlg_Text_Gentleman:
    .string "I am not exhausted.\p"
    .string "I am simply enjoying this\n"
    .string "chair very intensely.$"


SafariZone_North_RestHouse_Frlg_Text_Scientist:
    .string "Chansey sightings increase\n"
    .string "whenever I leave the area.\p"
    .string "Suspicious.$"


SafariZone_North_RestHouse_Frlg_Text_Fisher:
    .string "I saw something long and\n"
    .string "blue in the water.\p"
    .string "Naturally, it vanished.$"


SafariZone_North_RestHouse_Frlg_Text_BaldingMan:
    .string "My feet hurt.\n"
    .string "My back hurts.\p"
    .string "I'm still going back out.$"
