SafariZone_Center_RestHouse_Frlg_MapScripts::
    .byte 0


SafariZone_Center_RestHouse_Frlg_EventScript_Scientist::
    lock
    faceplayer
    msgbox SafariZone_Center_RestHouse_Frlg_Text_Scientist, MSGBOX_DEFAULT
    release
    end


SafariZone_Center_RestHouse_Frlg_EventScript_Woman::
    lock
    faceplayer
    msgbox SafariZone_Center_RestHouse_Frlg_Text_Woman, MSGBOX_DEFAULT
    release
    end


SafariZone_Center_RestHouse_Frlg_Text_Scientist:
    .string "I've recorded every\n"
    .string "encounter today.\p"
    .string "My conclusion?\n"
    .string "I have terrible luck.$"


SafariZone_Center_RestHouse_Frlg_Text_Woman:
    .string "I came in here to rest.\p"
    .string "Now I'm deciding if I\n"
    .string "actually want to go back out.$"
