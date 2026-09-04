SafariZone_East_RestHouse_Frlg_MapScripts::
    .byte 0


SafariZone_East_RestHouse_Frlg_EventScript_Scientist::
    lock
    faceplayer
    msgbox SafariZone_East_RestHouse_Frlg_Text_Scientist, MSGBOX_DEFAULT
    release
    end


SafariZone_East_RestHouse_Frlg_EventScript_Rocker::
    lock
    faceplayer
    msgbox SafariZone_East_RestHouse_Frlg_Text_Rocker, MSGBOX_DEFAULT
    release
    end


SafariZone_East_RestHouse_Frlg_EventScript_BaldingMan::
    lock
    faceplayer
    msgbox SafariZone_East_RestHouse_Frlg_Text_BaldingMan, MSGBOX_DEFAULT
    release
    end


SafariZone_East_RestHouse_Frlg_Text_Scientist:
    .string "People swear they have\n"
    .string "special catching tricks.\p"
    .string "They do not.$"


SafariZone_East_RestHouse_Frlg_Text_Rocker:
    .string "Scyther ran.\n"
    .string "Pinsir ran.\p"
    .string "I'm taking this personally.$"


SafariZone_East_RestHouse_Frlg_Text_BaldingMan:
    .string "I threw bait at a Tauros.\p"
    .string "For a moment, it looked like\n"
    .string "I was the bait.$"
