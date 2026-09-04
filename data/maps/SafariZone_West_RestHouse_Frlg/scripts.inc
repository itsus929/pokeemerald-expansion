SafariZone_West_RestHouse_Frlg_MapScripts::
    .byte 0


SafariZone_West_RestHouse_Frlg_EventScript_Scientist::
    lock
    faceplayer
    msgbox SafariZone_West_RestHouse_Frlg_Text_Scientist, MSGBOX_DEFAULT
    release
    end


SafariZone_West_RestHouse_Frlg_EventScript_Gentleman::
    lock
    faceplayer
    msgbox SafariZone_West_RestHouse_Frlg_Text_Gentleman, MSGBOX_DEFAULT
    release
    end


SafariZone_West_RestHouse_Frlg_EventScript_Cooltrainer::
    lock
    faceplayer
    msgbox SafariZone_West_RestHouse_Frlg_Text_Cooltrainer, MSGBOX_DEFAULT
    release
    end


SafariZone_West_RestHouse_Frlg_Text_Scientist:
    .string "I came here to observe\n"
    .string "Pokemon behavior.\p"
    .string "Mostly, they observe me run.$"


SafariZone_West_RestHouse_Frlg_Text_Gentleman:
    .string "A Kangaskhan stared at me.\p"
    .string "I decided we both needed\n"
    .string "some space.$"


SafariZone_West_RestHouse_Frlg_Text_Cooltrainer:
    .string "Cubone is adorable.\p"
    .string "I refuse to think any harder\n"
    .string "about that statement.$"
