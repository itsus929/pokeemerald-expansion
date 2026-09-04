SafariZone_East_Frlg_MapScripts::
    .byte 0


SafariZone_East_Frlg_EventScript_BugFan::
    lock
    faceplayer
    msgbox SafariZone_East_Frlg_Text_BugFan, MSGBOX_DEFAULT
    release
    end


SafariZone_East_Frlg_EventScript_TaurosWoman::
    lock
    faceplayer
    msgbox SafariZone_East_Frlg_Text_TaurosWoman, MSGBOX_DEFAULT
    release
    end


SafariZone_East_Frlg_Text_BugFan:
    .string "Scyther or Pinsir?\p"
    .string "Don't answer too quickly.\n"
    .string "This says a lot about you.$"

SafariZone_East_Frlg_Text_TaurosWoman:
    .string "If you see a Tauros...\n"
    .string "tell it I'm still mad.$"

SafariZone_East_Frlg_Text_TaurosWoman2:
    .string "It knows what it did.$"
