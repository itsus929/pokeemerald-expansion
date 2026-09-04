SafariZone_Center_Frlg_MapScripts::
    .byte 0


SafariZone_Center_Frlg_EventScript_StrategyMan::
    lock
    faceplayer
    msgbox SafariZone_Center_Frlg_Text_StrategyMan, MSGBOX_DEFAULT
    release
    end


SafariZone_Center_Frlg_EventScript_TiredWoman::
    lock
    faceplayer
    msgbox SafariZone_Center_Frlg_Text_TiredWoman, MSGBOX_DEFAULT
    release
    end


SafariZone_Center_Frlg_Text_StrategyMan:
    .string "First time here.\n"
    .string "I've got a whole strategy.$"

SafariZone_Center_Frlg_Text_StrategyMan2:
    .string "Stay calm. Move efficiently.\n"
    .string "Never chase anything.$"

SafariZone_Center_Frlg_Text_TiredWoman:
    .string "He said he had a strategy.\p"
    .string "Ten minutes ago, he chased a\n"
    .string "Nidoran into the grass.$"
