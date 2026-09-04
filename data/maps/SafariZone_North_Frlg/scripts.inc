SafariZone_North_Frlg_MapScripts::
    .byte 0


SafariZone_North_Frlg_EventScript_ChanseyMan::
    lock
    faceplayer
    msgbox SafariZone_North_Frlg_Text_ChanseyMan, MSGBOX_DEFAULT
    release
    end


SafariZone_North_Frlg_EventScript_ChanseyWoman::
    lock
    faceplayer
    msgbox SafariZone_North_Frlg_Text_ChanseyWoman, MSGBOX_DEFAULT
    release
    end


SafariZone_North_Frlg_Text_ChanseyMan:
    .string "Three days.\p"
    .string "I've been looking for a\n"
    .string "Chansey for THREE DAYS.$"

SafariZone_North_Frlg_Text_ChanseyWoman:
    .string "A Chansey?\p"
    .string "Oh, yeah. I saw one like five\n"
    .string "minutes ago.$"
