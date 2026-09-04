SafariZone_West_Frlg_MapScripts::
    .byte 0


SafariZone_West_Frlg_EventScript_KangaskhanMan::
    lock
    faceplayer
    msgbox SafariZone_West_Frlg_Text_KangaskhanMan, MSGBOX_DEFAULT
    release
    end


SafariZone_West_Frlg_EventScript_CuboneMan::
    lock
    faceplayer
    msgbox SafariZone_West_Frlg_Text_CuboneMan, MSGBOX_DEFAULT
    release
    end


SafariZone_West_Frlg_Text_KangaskhanMan:
    .string "I was NOT chased by that\n"
    .string "Kangaskhan.$"

SafariZone_West_Frlg_Text_KangaskhanMan2:
    .string "I made a tactical retreat.$"

SafariZone_West_Frlg_Text_CuboneMan:
    .string "Cubone looks so cute...\p"
    .string "Then you remember why it wears\n"
    .string "the skull, and now you're sad.$"
