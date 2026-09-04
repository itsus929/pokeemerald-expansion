@ Auto-created from the tested Mauville Training Ground.
@ Used only by Emerald/original-region Pokemon Center 2F maps.

@ ============================================================
@ TRAINING GROUND
@ ============================================================

@ ------------------------------------------------------------
@ LEFT: LEVEL UP MOVE TRAINER
@ ------------------------------------------------------------

EmeraldTrainingCenter_EventScript_MoveTrainer::
        lock
        faceplayer
        msgbox EmeraldTrainingCenter_Text_MoveTrainerIntro, MSGBOX_YESNO
        goto_if_eq VAR_RESULT, NO, EmeraldTrainingCenter_EventScript_MoveTrainerBye
        getpartysize
        goto_if_eq VAR_RESULT, 0, EmeraldTrainingCenter_EventScript_NoPokemon
        setmoverelearnerstate MOVE_RELEARNER_LEVEL_UP_MOVES
        bufferstring STR_VAR_3, MoveRelearner_Text_LevelUpMoveLWR
        msgbox EmeraldTrainingCenter_Text_MoveTrainerChoose, MSGBOX_DEFAULT
        chooseboxmon SELECT_PC_MON_MOVE_RELEARNER
        waitstate
        goto_if_eq VAR_0x8004, PARTY_NOTHING_CHOSEN, EmeraldTrainingCenter_EventScript_MoveTrainerBye
        special Special_HasMoveToRelearn
        goto_if_eq VAR_RESULT, FALSE, EmeraldTrainingCenter_EventScript_MoveTrainerNone
        msgbox MoveRelearner_Text_WhichXmoveShouldTeach, MSGBOX_DEFAULT
        special TeachMoveRelearnerMove
        msgbox EmeraldTrainingCenter_Text_MoveTrainerDone, MSGBOX_DEFAULT
        release
        end

EmeraldTrainingCenter_EventScript_MoveTrainerNone::
        msgbox EmeraldTrainingCenter_Text_MoveTrainerNone, MSGBOX_DEFAULT
        release
        end

EmeraldTrainingCenter_EventScript_MoveTrainerBye::
        msgbox EmeraldTrainingCenter_Text_MoveTrainerBye, MSGBOX_DEFAULT
        release
        end

@ ------------------------------------------------------------
@ MIDDLE: EV TRAINER
@ ------------------------------------------------------------

EmeraldTrainingCenter_EventScript_EVTrainer::
        lock
        faceplayer
        showmoneybox 0, 0
        msgbox EmeraldTrainingCenter_Text_EVTrainerIntro, MSGBOX_YESNO
        goto_if_eq VAR_RESULT, NO, EmeraldTrainingCenter_EventScript_EVTrainerBye
        getpartysize
        goto_if_eq VAR_RESULT, 0, EmeraldTrainingCenter_EventScript_NoPokemonMoney
        msgbox EmeraldTrainingCenter_Text_EVChooseMon, MSGBOX_DEFAULT
        chooseboxmon SELECT_PC_MON_NORMAL
        waitstate
        goto_if_eq VAR_0x8004, PARTY_NOTHING_CHOSEN, EmeraldTrainingCenter_EventScript_EVTrainerBye
        special IsSelectedMonEgg
        goto_if_eq VAR_RESULT, TRUE, EmeraldTrainingCenter_EventScript_EggNoTraining
        msgbox EmeraldTrainingCenter_Text_EVChooseStat, MSGBOX_DEFAULT
        dynmultichoice 0, 0, FALSE, 6, 0, DYN_MULTICHOICE_CB_NONE, EmeraldTrainingCenter_Text_HP, EmeraldTrainingCenter_Text_Attack, EmeraldTrainingCenter_Text_Defense, EmeraldTrainingCenter_Text_SpAtk, EmeraldTrainingCenter_Text_SpDef, EmeraldTrainingCenter_Text_Speed, EmeraldTrainingCenter_Text_Cancel
        goto_if_eq VAR_RESULT, MULTI_B_PRESSED, EmeraldTrainingCenter_EventScript_EVTrainerBye
        goto_if_eq VAR_RESULT, 6, EmeraldTrainingCenter_EventScript_EVTrainerBye
        copyvar VAR_0x8005, VAR_RESULT
        callnative Script_CheckSelectedMonEVTraining
        goto_if_eq VAR_RESULT, 1, EmeraldTrainingCenter_EventScript_EVStatMax
        goto_if_eq VAR_RESULT, 2, EmeraldTrainingCenter_EventScript_EVTotalMax
        goto_if_ne VAR_RESULT, 0, EmeraldTrainingCenter_EventScript_EVTrainerBye
        msgbox EmeraldTrainingCenter_Text_EVConfirm, MSGBOX_YESNO
        goto_if_eq VAR_RESULT, NO, EmeraldTrainingCenter_EventScript_EVTrainerBye
        checkmoney 5000
        goto_if_eq VAR_RESULT, FALSE, EmeraldTrainingCenter_EventScript_EVNoMoney
        playse SE_SHOP
        removemoney 5000
        updatemoneybox
        waitse
        callnative Script_TrainSelectedMonEV
        msgbox EmeraldTrainingCenter_Text_EVSuccess, MSGBOX_DEFAULT
        hidemoneybox
        release
        end

EmeraldTrainingCenter_EventScript_EVStatMax::
        msgbox EmeraldTrainingCenter_Text_EVStatMax, MSGBOX_DEFAULT
        hidemoneybox
        release
        end

EmeraldTrainingCenter_EventScript_EVTotalMax::
        msgbox EmeraldTrainingCenter_Text_EVTotalMax, MSGBOX_DEFAULT
        hidemoneybox
        release
        end

EmeraldTrainingCenter_EventScript_EVNoMoney::
        msgbox EmeraldTrainingCenter_Text_EVNoMoney, MSGBOX_DEFAULT
        hidemoneybox
        release
        end

EmeraldTrainingCenter_EventScript_EVTrainerBye::
        msgbox EmeraldTrainingCenter_Text_EVBye, MSGBOX_DEFAULT
        hidemoneybox
        release
        end

@ ------------------------------------------------------------
@ RIGHT: IV SPECIALIST
@ ------------------------------------------------------------

EmeraldTrainingCenter_EventScript_IVTrainer::
        lock
        faceplayer
        showmoneybox 0, 0
        msgbox EmeraldTrainingCenter_Text_IVTrainerIntro, MSGBOX_YESNO
        goto_if_eq VAR_RESULT, NO, EmeraldTrainingCenter_EventScript_IVTrainerBye
        getpartysize
        goto_if_eq VAR_RESULT, 0, EmeraldTrainingCenter_EventScript_NoPokemonMoney
        msgbox EmeraldTrainingCenter_Text_IVChooseMon, MSGBOX_DEFAULT
        chooseboxmon SELECT_PC_MON_NORMAL
        waitstate
        goto_if_eq VAR_0x8004, PARTY_NOTHING_CHOSEN, EmeraldTrainingCenter_EventScript_IVTrainerBye
        special IsSelectedMonEgg
        goto_if_eq VAR_RESULT, TRUE, EmeraldTrainingCenter_EventScript_EggNoTraining
        msgbox EmeraldTrainingCenter_Text_IVChooseStat, MSGBOX_DEFAULT
        dynmultichoice 0, 0, FALSE, 6, 0, DYN_MULTICHOICE_CB_NONE, EmeraldTrainingCenter_Text_HP, EmeraldTrainingCenter_Text_Attack, EmeraldTrainingCenter_Text_Defense, EmeraldTrainingCenter_Text_SpAtk, EmeraldTrainingCenter_Text_SpDef, EmeraldTrainingCenter_Text_Speed, EmeraldTrainingCenter_Text_Cancel
        goto_if_eq VAR_RESULT, MULTI_B_PRESSED, EmeraldTrainingCenter_EventScript_IVTrainerBye
        goto_if_eq VAR_RESULT, 6, EmeraldTrainingCenter_EventScript_IVTrainerBye
        copyvar VAR_0x8005, VAR_RESULT
        callnative Script_CheckSelectedMonIVTraining
        goto_if_eq VAR_RESULT, FALSE, EmeraldTrainingCenter_EventScript_IVAlreadyPerfect
        msgbox EmeraldTrainingCenter_Text_IVConfirm, MSGBOX_YESNO
        goto_if_eq VAR_RESULT, NO, EmeraldTrainingCenter_EventScript_IVTrainerBye
        checkmoney 10000
        goto_if_eq VAR_RESULT, FALSE, EmeraldTrainingCenter_EventScript_IVNoMoney
        playse SE_SHOP
        removemoney 10000
        updatemoneybox
        waitse
        callnative Script_TrainSelectedMonIV
        msgbox EmeraldTrainingCenter_Text_IVSuccess, MSGBOX_DEFAULT
        hidemoneybox
        release
        end

EmeraldTrainingCenter_EventScript_IVAlreadyPerfect::
        msgbox EmeraldTrainingCenter_Text_IVAlreadyPerfect, MSGBOX_DEFAULT
        hidemoneybox
        release
        end

EmeraldTrainingCenter_EventScript_IVNoMoney::
        msgbox EmeraldTrainingCenter_Text_IVNoMoney, MSGBOX_DEFAULT
        hidemoneybox
        release
        end

EmeraldTrainingCenter_EventScript_IVTrainerBye::
        msgbox EmeraldTrainingCenter_Text_IVBye, MSGBOX_DEFAULT
        hidemoneybox
        release
        end

@ ------------------------------------------------------------
@ SHARED
@ ------------------------------------------------------------

EmeraldTrainingCenter_EventScript_EggNoTraining::
        msgbox EmeraldTrainingCenter_Text_EggNoTraining, MSGBOX_DEFAULT
        hidemoneybox
        release
        end

EmeraldTrainingCenter_EventScript_NoPokemon::
        msgbox EmeraldTrainingCenter_Text_NoPokemon, MSGBOX_DEFAULT
        release
        end

EmeraldTrainingCenter_EventScript_NoPokemonMoney::
        msgbox EmeraldTrainingCenter_Text_NoPokemon, MSGBOX_DEFAULT
        hidemoneybox
        release
        end

@ ============================================================
@ TEXT
@ ============================================================

EmeraldTrainingCenter_Text_MoveTrainerIntro:
        .string "I specialize in moves your POKéMON\n"
        .string "could already have learned.\p"
        .string "If it has forgotten one, I can help\n"
        .string "bring it back.\p"
        .string "No charge. Interested?$"

EmeraldTrainingCenter_Text_MoveTrainerChoose:
        .string "Choose a POKéMON.\p"
        .string "I'll see what moves it has earned.$"

EmeraldTrainingCenter_Text_MoveTrainerNone:
        .string "That POKéMON has no moves to relearn\n"
        .string "right now.$"

EmeraldTrainingCenter_Text_MoveTrainerDone:
        .string "There you go.\p"
        .string "A good move should never go to waste.$"

EmeraldTrainingCenter_Text_MoveTrainerBye:
        .string "Come back whenever you need me.$"

EmeraldTrainingCenter_Text_EVTrainerIntro:
        .string "I handle focused EV training.\p"
        .string "For 5,000, I'll push one stat as far\n"
        .string "as your POKéMON can currently go.\p"
        .string "Want to train?$"

EmeraldTrainingCenter_Text_EVChooseMon:
        .string "Which POKéMON are we training?$"

EmeraldTrainingCenter_Text_EVChooseStat:
        .string "Which stat should we focus on?$"

EmeraldTrainingCenter_Text_EVConfirm:
        .string "Focused training costs 5,000.\p"
        .string "Ready?$"

EmeraldTrainingCenter_Text_EVStatMax:
        .string "That stat is already fully trained.$"

EmeraldTrainingCenter_Text_EVTotalMax:
        .string "This POKéMON has reached its total\n"
        .string "EV training limit.$"

EmeraldTrainingCenter_Text_EVNoMoney:
        .string "You're short on funds.\p"
        .string "Training costs 5,000.$"

EmeraldTrainingCenter_Text_EVSuccess:
        .string "Done.\p"
        .string "That stat has been pushed as far as\n"
        .string "your remaining EVs allow.$"

EmeraldTrainingCenter_Text_EVBye:
        .string "No problem. Come back when you're\n"
        .string "ready to train.$"

EmeraldTrainingCenter_Text_IVTrainerIntro:
        .string "I specialize in a POKéMON's natural\n"
        .string "potential.\p"
        .string "For 10,000, I can perfect one IV.\p"
        .string "Interested?$"

EmeraldTrainingCenter_Text_IVChooseMon:
        .string "Which POKéMON should I examine?$"

EmeraldTrainingCenter_Text_IVChooseStat:
        .string "Which stat should I perfect?$"

EmeraldTrainingCenter_Text_IVConfirm:
        .string "Perfecting that IV costs 10,000.\p"
        .string "Proceed?$"

EmeraldTrainingCenter_Text_IVAlreadyPerfect:
        .string "That IV is already perfect.\p"
        .string "Save your money.$"

EmeraldTrainingCenter_Text_IVNoMoney:
        .string "You don't have enough.\p"
        .string "I charge 10,000 per IV.$"

EmeraldTrainingCenter_Text_IVSuccess:
        .string "Finished.\p"
        .string "That IV is now perfect.$"

EmeraldTrainingCenter_Text_IVBye:
        .string "Come back when you're ready.$"

EmeraldTrainingCenter_Text_EggNoTraining:
        .string "Let's wait until that EGG hatches.$"

EmeraldTrainingCenter_Text_NoPokemon:
        .string "You'll need a POKéMON first.$"

EmeraldTrainingCenter_Text_HP:
        .string "HP$"

EmeraldTrainingCenter_Text_Attack:
        .string "Attack$"

EmeraldTrainingCenter_Text_Defense:
        .string "Defense$"

EmeraldTrainingCenter_Text_SpAtk:
        .string "Sp. Atk$"

EmeraldTrainingCenter_Text_SpDef:
        .string "Sp. Def$"

EmeraldTrainingCenter_Text_Speed:
        .string "Speed$"

EmeraldTrainingCenter_Text_Cancel:
        .string "Cancel$"


@ ============================================================
@ TRAINING CENTER INFORMATION
@ ============================================================

EmeraldTrainingCenter_EventScript_InfoAttendant::
        lock
        faceplayer
        msgbox EmeraldTrainingCenter_Text_Info, MSGBOX_DEFAULT
        release
        end

EmeraldTrainingCenter_Text_Info:
        .string "Welcome to the TRAINING CENTER!\p"
        .string "The MOVE TRAINER on the left can\n"
        .string "restore level-up moves your POKéMON\l"
        .string "has already earned.\p"
        .string "The EV TRAINER in the middle can\n"
        .string "focus a stat's training for 5,000.\p"
        .string "The IV SPECIALIST on the right can\n"
        .string "perfect one IV for 10,000.$"

@ ============================================================================
@ PRE-MAUVILLE TRAINING CENTER BOUNCER
@ ============================================================================

EmeraldTrainingCenter_EventScript_Bouncer::
    msgbox EmeraldTrainingCenter_Text_Bouncer, MSGBOX_NPC
    end

EmeraldTrainingCenter_Text_Bouncer:
    .string "Sorry, the upstairs training\n"
    .string "facilities aren't open yet.\p"
    .string "They'll be available once you reach\n"
    .string "MAUVILLE CITY.$"
