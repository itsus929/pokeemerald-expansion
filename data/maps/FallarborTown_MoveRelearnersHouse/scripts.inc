FallarborTown_MoveRelearnersHouse_MapScripts::
    .byte 0

FallarborTown_MoveRelearnersHouse_EventScript_MoveRelearner::
    lock
    faceplayer

    msgbox FallarborTown_MoveRelearnersHouse_Text_Intro, MSGBOX_YESNO
    goto_if_eq VAR_RESULT, NO, FallarborTown_MoveRelearnersHouse_EventScript_Decline

    msgbox FallarborTown_MoveRelearnersHouse_Text_ChooseMon, MSGBOX_DEFAULT
    chooseboxmon SELECT_PC_MON_NORMAL
    waitstate

    goto_if_eq VAR_0x8004, PARTY_NOTHING_CHOSEN, FallarborTown_MoveRelearnersHouse_EventScript_Decline

    special IsSelectedMonEgg
    goto_if_eq VAR_RESULT, TRUE, FallarborTown_MoveRelearnersHouse_EventScript_Egg

    callnative Script_CheckSelectedMonTradeEvolution
    goto_if_eq VAR_RESULT, FALSE, FallarborTown_MoveRelearnersHouse_EventScript_CantEvolve

    msgbox FallarborTown_MoveRelearnersHouse_Text_Confirm, MSGBOX_YESNO
    goto_if_eq VAR_RESULT, NO, FallarborTown_MoveRelearnersHouse_EventScript_Decline

    callnative Script_EvolveSelectedMonByTrade
    release
    end

FallarborTown_MoveRelearnersHouse_EventScript_Egg::
    msgbox FallarborTown_MoveRelearnersHouse_Text_Egg, MSGBOX_DEFAULT
    release
    end

FallarborTown_MoveRelearnersHouse_EventScript_CantEvolve::
    msgbox FallarborTown_MoveRelearnersHouse_Text_CantEvolve, MSGBOX_DEFAULT
    release
    end

FallarborTown_MoveRelearnersHouse_EventScript_Decline::
    msgbox FallarborTown_MoveRelearnersHouse_Text_Decline, MSGBOX_DEFAULT
    release
    end

FallarborTown_MoveRelearnersHouse_Text_Intro:
    .string "Some POKéMON evolve under unusual\n"
    .string "circumstances.\p"
    .string "Trading is one of them.\p"
    .string "I can help with that.\p"
    .string "Want me to take a look?$"

FallarborTown_MoveRelearnersHouse_Text_ChooseMon:
    .string "Which POKéMON needs help evolving?$"

FallarborTown_MoveRelearnersHouse_Text_Confirm:
    .string "Yes, this one can evolve through a\n"
    .string "trade.\p"
    .string "Would you like me to help?$"

FallarborTown_MoveRelearnersHouse_Text_Egg:
    .string "Let's wait until that EGG hatches.$"

FallarborTown_MoveRelearnersHouse_Text_CantEvolve:
    .string "This POKéMON doesn't need my help\n"
    .string "right now.$"

FallarborTown_MoveRelearnersHouse_Text_Decline:
    .string "No problem.\p"
    .string "Come back if you need me.$"
