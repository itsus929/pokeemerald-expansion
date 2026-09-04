MtMoon_B1F_Frlg_MapScripts::
    .byte 0

@ Future story route:
@ Mt. Moon B1F hidden tunnel -> Silph Co. upper floors.
@ For now the passage is deliberately sealed.
MtMoon_B1F_Frlg_EventScript_SealedPassage::
    msgbox MtMoon_B1F_Frlg_Text_SealedPassage, MSGBOX_SIGN
    end

MtMoon_B1F_Frlg_Text_SealedPassage:
    .string "{PLAYER}: ...\p"
    .string "The passage is blocked.\p"
    .string "It looks like it keeps going,\n"
    .string "though.$"

