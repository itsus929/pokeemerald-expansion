MauvilleCity_PokemonCenter_2F_MapScripts::
	map_script MAP_SCRIPT_ON_FRAME_TABLE, CableClub_OnFrame
	map_script MAP_SCRIPT_ON_WARP_INTO_MAP_TABLE, CableClub_OnWarp
	map_script MAP_SCRIPT_ON_LOAD, CableClub_OnLoad
	map_script MAP_SCRIPT_ON_TRANSITION, CableClub_OnTransition
	.byte 0

@ The below 3 are unused and leftover from RS
MauvilleCity_PokemonCenter_2F_EventScript_Colosseum::
	call CableClub_EventScript_Colosseum
	end

MauvilleCity_PokemonCenter_2F_EventScript_TradeCenter::
	call CableClub_EventScript_TradeCenter
	end

MauvilleCity_PokemonCenter_2F_EventScript_RecordCorner::
	call CableClub_EventScript_RecordCorner
	end

MauvilleCity_PokemonCenter_2F_EventScript_Youngster::
	msgbox MauvilleCity_PokemonCenter_2F_Text_Youngster, MSGBOX_NPC
	end

MauvilleCity_PokemonCenter_2F_Text_Youngster:
	.string "Did you know that you can link battle\n"
	.string "at the COLOSSEUM here?\p"
	.string "They put up your record on the wall\n"
	.string "for everyone to see.\p"
	.string "It's embarrassing if you lose more\n"
	.string "often than you win…$"



@ ============================================================
@ TRAINING GROUND
@ ============================================================

@ ------------------------------------------------------------
@ LEFT: LEVEL UP MOVE TRAINER
@ ------------------------------------------------------------

MauvilleCity_PokemonCenter_2F_EventScript_MoveTrainer::
        lock
        faceplayer
        msgbox MauvilleCity_PokemonCenter_2F_Text_MoveTrainerIntro, MSGBOX_YESNO
        goto_if_eq VAR_RESULT, NO, MauvilleCity_PokemonCenter_2F_EventScript_MoveTrainerBye
        getpartysize
        goto_if_eq VAR_RESULT, 0, MauvilleCity_PokemonCenter_2F_EventScript_NoPokemon
        setmoverelearnerstate MOVE_RELEARNER_LEVEL_UP_MOVES
        bufferstring STR_VAR_3, MoveRelearner_Text_LevelUpMoveLWR
        msgbox MauvilleCity_PokemonCenter_2F_Text_MoveTrainerChoose, MSGBOX_DEFAULT
        chooseboxmon SELECT_PC_MON_MOVE_RELEARNER
        waitstate
        goto_if_eq VAR_0x8004, PARTY_NOTHING_CHOSEN, MauvilleCity_PokemonCenter_2F_EventScript_MoveTrainerBye
        special Special_HasMoveToRelearn
        goto_if_eq VAR_RESULT, FALSE, MauvilleCity_PokemonCenter_2F_EventScript_MoveTrainerNone
        msgbox MoveRelearner_Text_WhichXmoveShouldTeach, MSGBOX_DEFAULT
        special TeachMoveRelearnerMove
        msgbox MauvilleCity_PokemonCenter_2F_Text_MoveTrainerDone, MSGBOX_DEFAULT
        release
        end

MauvilleCity_PokemonCenter_2F_EventScript_MoveTrainerNone::
        msgbox MauvilleCity_PokemonCenter_2F_Text_MoveTrainerNone, MSGBOX_DEFAULT
        release
        end

MauvilleCity_PokemonCenter_2F_EventScript_MoveTrainerBye::
        msgbox MauvilleCity_PokemonCenter_2F_Text_MoveTrainerBye, MSGBOX_DEFAULT
        release
        end

@ ------------------------------------------------------------
@ MIDDLE: EV TRAINER
@ ------------------------------------------------------------

MauvilleCity_PokemonCenter_2F_EventScript_EVTrainer::
        lock
        faceplayer
        showmoneybox 0, 0
        msgbox MauvilleCity_PokemonCenter_2F_Text_EVTrainerIntro, MSGBOX_YESNO
        goto_if_eq VAR_RESULT, NO, MauvilleCity_PokemonCenter_2F_EventScript_EVTrainerBye
        getpartysize
        goto_if_eq VAR_RESULT, 0, MauvilleCity_PokemonCenter_2F_EventScript_NoPokemonMoney
        msgbox MauvilleCity_PokemonCenter_2F_Text_EVChooseMon, MSGBOX_DEFAULT
        chooseboxmon SELECT_PC_MON_NORMAL
        waitstate
        goto_if_eq VAR_0x8004, PARTY_NOTHING_CHOSEN, MauvilleCity_PokemonCenter_2F_EventScript_EVTrainerBye
        special IsSelectedMonEgg
        goto_if_eq VAR_RESULT, TRUE, MauvilleCity_PokemonCenter_2F_EventScript_EggNoTraining
        msgbox MauvilleCity_PokemonCenter_2F_Text_EVChooseStat, MSGBOX_DEFAULT
        dynmultichoice 0, 0, FALSE, 6, 0, DYN_MULTICHOICE_CB_NONE, MauvilleCity_PokemonCenter_2F_Text_HP, MauvilleCity_PokemonCenter_2F_Text_Attack, MauvilleCity_PokemonCenter_2F_Text_Defense, MauvilleCity_PokemonCenter_2F_Text_SpAtk, MauvilleCity_PokemonCenter_2F_Text_SpDef, MauvilleCity_PokemonCenter_2F_Text_Speed, MauvilleCity_PokemonCenter_2F_Text_Cancel
        goto_if_eq VAR_RESULT, MULTI_B_PRESSED, MauvilleCity_PokemonCenter_2F_EventScript_EVTrainerBye
        goto_if_eq VAR_RESULT, 6, MauvilleCity_PokemonCenter_2F_EventScript_EVTrainerBye
        copyvar VAR_0x8005, VAR_RESULT
        callnative Script_CheckSelectedMonEVTraining
        goto_if_eq VAR_RESULT, 1, MauvilleCity_PokemonCenter_2F_EventScript_EVStatMax
        goto_if_eq VAR_RESULT, 2, MauvilleCity_PokemonCenter_2F_EventScript_EVTotalMax
        goto_if_ne VAR_RESULT, 0, MauvilleCity_PokemonCenter_2F_EventScript_EVTrainerBye
        msgbox MauvilleCity_PokemonCenter_2F_Text_EVConfirm, MSGBOX_YESNO
        goto_if_eq VAR_RESULT, NO, MauvilleCity_PokemonCenter_2F_EventScript_EVTrainerBye
        checkmoney 5000
        goto_if_eq VAR_RESULT, FALSE, MauvilleCity_PokemonCenter_2F_EventScript_EVNoMoney
        playse SE_SHOP
        removemoney 5000
        updatemoneybox
        waitse
        callnative Script_TrainSelectedMonEV
        msgbox MauvilleCity_PokemonCenter_2F_Text_EVSuccess, MSGBOX_DEFAULT
        hidemoneybox
        release
        end

MauvilleCity_PokemonCenter_2F_EventScript_EVStatMax::
        msgbox MauvilleCity_PokemonCenter_2F_Text_EVStatMax, MSGBOX_DEFAULT
        hidemoneybox
        release
        end

MauvilleCity_PokemonCenter_2F_EventScript_EVTotalMax::
        msgbox MauvilleCity_PokemonCenter_2F_Text_EVTotalMax, MSGBOX_DEFAULT
        hidemoneybox
        release
        end

MauvilleCity_PokemonCenter_2F_EventScript_EVNoMoney::
        msgbox MauvilleCity_PokemonCenter_2F_Text_EVNoMoney, MSGBOX_DEFAULT
        hidemoneybox
        release
        end

MauvilleCity_PokemonCenter_2F_EventScript_EVTrainerBye::
        msgbox MauvilleCity_PokemonCenter_2F_Text_EVBye, MSGBOX_DEFAULT
        hidemoneybox
        release
        end

@ ------------------------------------------------------------
@ RIGHT: IV SPECIALIST
@ ------------------------------------------------------------

MauvilleCity_PokemonCenter_2F_EventScript_IVTrainer::
        lock
        faceplayer
        showmoneybox 0, 0
        msgbox MauvilleCity_PokemonCenter_2F_Text_IVTrainerIntro, MSGBOX_YESNO
        goto_if_eq VAR_RESULT, NO, MauvilleCity_PokemonCenter_2F_EventScript_IVTrainerBye
        getpartysize
        goto_if_eq VAR_RESULT, 0, MauvilleCity_PokemonCenter_2F_EventScript_NoPokemonMoney
        msgbox MauvilleCity_PokemonCenter_2F_Text_IVChooseMon, MSGBOX_DEFAULT
        chooseboxmon SELECT_PC_MON_NORMAL
        waitstate
        goto_if_eq VAR_0x8004, PARTY_NOTHING_CHOSEN, MauvilleCity_PokemonCenter_2F_EventScript_IVTrainerBye
        special IsSelectedMonEgg
        goto_if_eq VAR_RESULT, TRUE, MauvilleCity_PokemonCenter_2F_EventScript_EggNoTraining
        msgbox MauvilleCity_PokemonCenter_2F_Text_IVChooseStat, MSGBOX_DEFAULT
        dynmultichoice 0, 0, FALSE, 6, 0, DYN_MULTICHOICE_CB_NONE, MauvilleCity_PokemonCenter_2F_Text_HP, MauvilleCity_PokemonCenter_2F_Text_Attack, MauvilleCity_PokemonCenter_2F_Text_Defense, MauvilleCity_PokemonCenter_2F_Text_SpAtk, MauvilleCity_PokemonCenter_2F_Text_SpDef, MauvilleCity_PokemonCenter_2F_Text_Speed, MauvilleCity_PokemonCenter_2F_Text_Cancel
        goto_if_eq VAR_RESULT, MULTI_B_PRESSED, MauvilleCity_PokemonCenter_2F_EventScript_IVTrainerBye
        goto_if_eq VAR_RESULT, 6, MauvilleCity_PokemonCenter_2F_EventScript_IVTrainerBye
        copyvar VAR_0x8005, VAR_RESULT
        callnative Script_CheckSelectedMonIVTraining
        goto_if_eq VAR_RESULT, FALSE, MauvilleCity_PokemonCenter_2F_EventScript_IVAlreadyPerfect
        msgbox MauvilleCity_PokemonCenter_2F_Text_IVConfirm, MSGBOX_YESNO
        goto_if_eq VAR_RESULT, NO, MauvilleCity_PokemonCenter_2F_EventScript_IVTrainerBye
        checkmoney 10000
        goto_if_eq VAR_RESULT, FALSE, MauvilleCity_PokemonCenter_2F_EventScript_IVNoMoney
        playse SE_SHOP
        removemoney 10000
        updatemoneybox
        waitse
        callnative Script_TrainSelectedMonIV
        msgbox MauvilleCity_PokemonCenter_2F_Text_IVSuccess, MSGBOX_DEFAULT
        hidemoneybox
        release
        end

MauvilleCity_PokemonCenter_2F_EventScript_IVAlreadyPerfect::
        msgbox MauvilleCity_PokemonCenter_2F_Text_IVAlreadyPerfect, MSGBOX_DEFAULT
        hidemoneybox
        release
        end

MauvilleCity_PokemonCenter_2F_EventScript_IVNoMoney::
        msgbox MauvilleCity_PokemonCenter_2F_Text_IVNoMoney, MSGBOX_DEFAULT
        hidemoneybox
        release
        end

MauvilleCity_PokemonCenter_2F_EventScript_IVTrainerBye::
        msgbox MauvilleCity_PokemonCenter_2F_Text_IVBye, MSGBOX_DEFAULT
        hidemoneybox
        release
        end

@ ------------------------------------------------------------
@ SHARED
@ ------------------------------------------------------------

MauvilleCity_PokemonCenter_2F_EventScript_EggNoTraining::
        msgbox MauvilleCity_PokemonCenter_2F_Text_EggNoTraining, MSGBOX_DEFAULT
        hidemoneybox
        release
        end

MauvilleCity_PokemonCenter_2F_EventScript_NoPokemon::
        msgbox MauvilleCity_PokemonCenter_2F_Text_NoPokemon, MSGBOX_DEFAULT
        release
        end

MauvilleCity_PokemonCenter_2F_EventScript_NoPokemonMoney::
        msgbox MauvilleCity_PokemonCenter_2F_Text_NoPokemon, MSGBOX_DEFAULT
        hidemoneybox
        release
        end

@ ============================================================
@ TEXT
@ ============================================================

MauvilleCity_PokemonCenter_2F_Text_MoveTrainerIntro:
        .string "I specialize in moves your POKéMON\n"
        .string "could already have learned.\p"
        .string "If it has forgotten one, I can help\n"
        .string "bring it back.\p"
        .string "No charge. Interested?$"

MauvilleCity_PokemonCenter_2F_Text_MoveTrainerChoose:
        .string "Choose a POKéMON.\p"
        .string "I'll see what moves it has earned.$"

MauvilleCity_PokemonCenter_2F_Text_MoveTrainerNone:
        .string "That POKéMON has no moves to relearn\n"
        .string "right now.$"

MauvilleCity_PokemonCenter_2F_Text_MoveTrainerDone:
        .string "There you go.\p"
        .string "A good move should never go to waste.$"

MauvilleCity_PokemonCenter_2F_Text_MoveTrainerBye:
        .string "Come back whenever you need me.$"

MauvilleCity_PokemonCenter_2F_Text_EVTrainerIntro:
        .string "I handle focused EV training.\p"
        .string "For 5,000, I'll push one stat as far\n"
        .string "as your POKéMON can currently go.\p"
        .string "Want to train?$"

MauvilleCity_PokemonCenter_2F_Text_EVChooseMon:
        .string "Which POKéMON are we training?$"

MauvilleCity_PokemonCenter_2F_Text_EVChooseStat:
        .string "Which stat should we focus on?$"

MauvilleCity_PokemonCenter_2F_Text_EVConfirm:
        .string "Focused training costs 5,000.\p"
        .string "Ready?$"

MauvilleCity_PokemonCenter_2F_Text_EVStatMax:
        .string "That stat is already fully trained.$"

MauvilleCity_PokemonCenter_2F_Text_EVTotalMax:
        .string "This POKéMON has reached its total\n"
        .string "EV training limit.$"

MauvilleCity_PokemonCenter_2F_Text_EVNoMoney:
        .string "You're short on funds.\p"
        .string "Training costs 5,000.$"

MauvilleCity_PokemonCenter_2F_Text_EVSuccess:
        .string "Done.\p"
        .string "That stat has been pushed as far as\n"
        .string "your remaining EVs allow.$"

MauvilleCity_PokemonCenter_2F_Text_EVBye:
        .string "No problem. Come back when you're\n"
        .string "ready to train.$"

MauvilleCity_PokemonCenter_2F_Text_IVTrainerIntro:
        .string "I specialize in a POKéMON's natural\n"
        .string "potential.\p"
        .string "For 10,000, I can perfect one IV.\p"
        .string "Interested?$"

MauvilleCity_PokemonCenter_2F_Text_IVChooseMon:
        .string "Which POKéMON should I examine?$"

MauvilleCity_PokemonCenter_2F_Text_IVChooseStat:
        .string "Which stat should I perfect?$"

MauvilleCity_PokemonCenter_2F_Text_IVConfirm:
        .string "Perfecting that IV costs 10,000.\p"
        .string "Proceed?$"

MauvilleCity_PokemonCenter_2F_Text_IVAlreadyPerfect:
        .string "That IV is already perfect.\p"
        .string "Save your money.$"

MauvilleCity_PokemonCenter_2F_Text_IVNoMoney:
        .string "You don't have enough.\p"
        .string "I charge 10,000 per IV.$"

MauvilleCity_PokemonCenter_2F_Text_IVSuccess:
        .string "Finished.\p"
        .string "That IV is now perfect.$"

MauvilleCity_PokemonCenter_2F_Text_IVBye:
        .string "Come back when you're ready.$"

MauvilleCity_PokemonCenter_2F_Text_EggNoTraining:
        .string "Let's wait until that EGG hatches.$"

MauvilleCity_PokemonCenter_2F_Text_NoPokemon:
        .string "You'll need a POKéMON first.$"

MauvilleCity_PokemonCenter_2F_Text_HP:
        .string "HP$"

MauvilleCity_PokemonCenter_2F_Text_Attack:
        .string "Attack$"

MauvilleCity_PokemonCenter_2F_Text_Defense:
        .string "Defense$"

MauvilleCity_PokemonCenter_2F_Text_SpAtk:
        .string "Sp. Atk$"

MauvilleCity_PokemonCenter_2F_Text_SpDef:
        .string "Sp. Def$"

MauvilleCity_PokemonCenter_2F_Text_Speed:
        .string "Speed$"

MauvilleCity_PokemonCenter_2F_Text_Cancel:
        .string "Cancel$"
