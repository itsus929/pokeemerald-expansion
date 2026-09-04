FuchsiaCity_PokemonCenter_1F_Frlg_MapScripts::
    .byte 0


FuchsiaCity_PokemonCenter_1F_Frlg_EventScript_Nurse::
    lock
    faceplayer

    msgbox gText_WouldYouLikeToRestYourPkmn, MSGBOX_YESNO
    goto_if_eq VAR_RESULT, YES, FuchsiaCity_PokemonCenter_1F_Frlg_EventScript_NurseHeal

    message gText_WeHopeToSeeYouAgain
    waitmessage
    release
    end


FuchsiaCity_PokemonCenter_1F_Frlg_EventScript_NurseHeal:
    incrementgamestat GAME_STAT_USED_POKECENTER

    message gText_IllTakeYourPkmn
    waitmessage

    call EventScript_PkmnCenterNurse_TakeAndHealPkmn

    message gText_RestoredPkmnToFullHealth
    waitmessage

    applymovement VAR_0x800B, Movement_PkmnCenterNurse_Bow
    waitmovement 0

    release
    end




FuchsiaCity_PokemonCenter_1F_Frlg_EventScript_Man::
    msgbox FuchsiaCity_PokemonCenter_1F_Frlg_Text_Man, MSGBOX_NPC
    end


FuchsiaCity_PokemonCenter_1F_Frlg_EventScript_Cooltrainer::
    msgbox FuchsiaCity_PokemonCenter_1F_Frlg_Text_Cooltrainer, MSGBOX_NPC
    end


FuchsiaCity_PokemonCenter_1F_Frlg_EventScript_Youngster::
    msgbox FuchsiaCity_PokemonCenter_1F_Frlg_Text_Youngster, MSGBOX_NPC
    end


FuchsiaCity_PokemonCenter_1F_Frlg_Text_Man:
    .string "Nothing makes you appreciate a\n"
    .string "POKéMON CENTER like a long trip.$"


FuchsiaCity_PokemonCenter_1F_Frlg_Text_Cooltrainer:
    .string "FUCHSIA sees Trainers from all\n"
    .string "over.\p"
    .string "Most of them come back looking\n"
    .string "considerably more tired.$"


FuchsiaCity_PokemonCenter_1F_Frlg_Text_Youngster:
    .string "NURSE JOY said my POKéMON need\n"
    .string "rest.\p"
    .string "Apparently that means I do too.$"
