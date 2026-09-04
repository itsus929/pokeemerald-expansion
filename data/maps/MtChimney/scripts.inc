MtChimney_MapScripts::
        map_script MAP_SCRIPT_ON_LOAD, MtChimney_SetCounterpartGraphics
	map_script MAP_SCRIPT_ON_RESUME, MtChimney_OnResume
	map_script MAP_SCRIPT_ON_TRANSITION, MtChimney_OnTransition
	.byte 0

MtChimney_SetCounterpartGraphics:
        goto_if_eq VAR_COUNTERPART_ID, COUNTERPART_BRENDAN, MtChimney_SetBrendan
        goto_if_eq VAR_COUNTERPART_ID, COUNTERPART_MAY, MtChimney_SetMay
        goto_if_eq VAR_COUNTERPART_ID, COUNTERPART_LEXY, MtChimney_SetLexy
        goto_if_eq VAR_COUNTERPART_ID, COUNTERPART_JUSTIN, MtChimney_SetJustin
        goto_if_eq VAR_COUNTERPART_ID, COUNTERPART_MAAM, MtChimney_SetMaam
        goto_if_eq VAR_COUNTERPART_ID, COUNTERPART_SIR, MtChimney_SetSir
        goto MtChimney_FinishCounterpartLoad

MtChimney_SetBrendan:
        setvar VAR_OBJ_GFX_ID_0, OBJ_EVENT_GFX_BRENDAN_NORMAL
        goto MtChimney_FinishCounterpartLoad

MtChimney_SetMay:
        setvar VAR_OBJ_GFX_ID_0, OBJ_EVENT_GFX_MAY_NORMAL
        goto MtChimney_FinishCounterpartLoad

MtChimney_SetLexy:
        setvar VAR_OBJ_GFX_ID_0, OBJ_EVENT_GFX_LEXY_NORMAL
        goto MtChimney_FinishCounterpartLoad

MtChimney_SetJustin:
        setvar VAR_OBJ_GFX_ID_0, OBJ_EVENT_GFX_JUSTIN_NORMAL
        goto MtChimney_FinishCounterpartLoad

MtChimney_SetMaam:
        setvar VAR_OBJ_GFX_ID_0, OBJ_EVENT_GFX_MAAM_NORMAL
        goto MtChimney_FinishCounterpartLoad

MtChimney_SetSir:
        setvar VAR_OBJ_GFX_ID_0, OBJ_EVENT_GFX_SIR_NORMAL

MtChimney_FinishCounterpartLoad:
        end


MtChimney_OnTransition:
	setvar VAR_JAGGED_PASS_ASH_WEATHER, 1
	end

MtChimney_OnResume:
	setstepcallback STEP_CB_ASH
	end

MtChimney_EventScript_Archie::
	lock
	faceplayer
	call_if_unset FLAG_EVIL_LEADER_PLEASE_STOP, MtChimney_EventScript_ArchieGoStopTeamMagma
	call_if_set FLAG_EVIL_LEADER_PLEASE_STOP, MtChimney_EventScript_ArchieBusyFighting
	closemessage
	applymovement LOCALID_MT_CHIMNEY_ARCHIE, Common_Movement_FaceOriginalDirection
	waitmovement 0
	setflag FLAG_EVIL_LEADER_PLEASE_STOP
	release
	end

MtChimney_EventScript_ArchieGoStopTeamMagma::
	msgbox MtChimney_Text_ArchieGoStopTeamMagma, MSGBOX_DEFAULT
	return

MtChimney_EventScript_ArchieBusyFighting::
	msgbox MtChimney_Text_ArchieIHaveMyHandsFull, MSGBOX_DEFAULT
	return

MtChimney_EventScript_SummitTrigger::
        goto_if_set FLAG_DEFEATED_EVIL_TEAM_MT_CHIMNEY, MtChimney_EventScript_SummitTrigger_End
        goto MtChimney_EventScript_Maxie

MtChimney_EventScript_SummitTrigger_End:
        end


MtChimney_EventScript_Maxie::
        lockall
        playbgm MUS_ENCOUNTER_MAGMA, FALSE

        @ Initial staging.
        @ Player is lined up with Giovanni.
        @ Counterpart is lined up with Maxie.

        msgbox MtChimney_Text_MeteoriteWillActivateVolcano, MSGBOX_DEFAULT

        playse SE_PIN
        applymovement LOCALID_MT_CHIMNEY_MAXIE, Common_Movement_ExclamationMark
        waitmovement 0
        applymovement LOCALID_MT_CHIMNEY_MAXIE, Common_Movement_Delay48
        waitmovement 0

        @ Counterpart recognizes Maxie.
        applymovement LOCALID_MT_CHIMNEY_COUNTERPART, Common_Movement_FaceRight
        applymovement LOCALID_MT_CHIMNEY_MAXIE, Common_Movement_FaceLeft
        waitmovement 0
        msgbox MtChimney_Text_FreakOutRecognition, MSGBOX_DEFAULT

        @ Player hears where this is going.
        applymovement LOCALID_MT_CHIMNEY_COUNTERPART, Common_Movement_FaceDown
        applymovement LOCALID_PLAYER, Common_Movement_FaceUp
        waitmovement 0
        msgbox MtChimney_Text_FreakOutOhNo, MSGBOX_DEFAULT

        @ Counterpart immediately goes back to bothering Maxie.
        applymovement LOCALID_MT_CHIMNEY_COUNTERPART, Common_Movement_FaceRight
        applymovement LOCALID_MT_CHIMNEY_MAXIE, Common_Movement_FaceLeft
        waitmovement 0
        msgbox MtChimney_Text_FreakOutGuy, MSGBOX_DEFAULT

        @ Player joins the chef argument.
        @ Maxie turns toward the player because now BOTH of them
        @ are accusing him of terrorizing restaurant staff.
        applymovement LOCALID_PLAYER, Common_Movement_FaceUp
        applymovement LOCALID_MT_CHIMNEY_MAXIE, Common_Movement_FaceDown
        waitmovement 0
        msgbox MtChimney_Text_FreakOutChef, MSGBOX_DEFAULT

        @ Counterpart gets the last word.
        applymovement LOCALID_MT_CHIMNEY_COUNTERPART, Common_Movement_FaceRight
        applymovement LOCALID_MT_CHIMNEY_MAXIE, Common_Movement_FaceLeft
        waitmovement 0
        msgbox MtChimney_Text_FreakOutStillYou, MSGBOX_DEFAULT

        @ Giovanni has had enough.
        @ Everyone involved in the nonsense looks at him.
        applymovement LOCALID_MT_CHIMNEY_MAXIE, Common_Movement_FaceDown
        applymovement LOCALID_MT_CHIMNEY_MAGMA_GRUNT_1, Common_Movement_FaceUp
        waitmovement 0
        msgbox MtChimney_Text_GiovanniAreWeFinished, MSGBOX_DEFAULT

        @ Counterpart asks PLAYER who Giovanni is.
        applymovement LOCALID_MT_CHIMNEY_COUNTERPART, Common_Movement_FaceDown
        applymovement LOCALID_PLAYER, Common_Movement_FaceUp
        waitmovement 0
        msgbox MtChimney_Text_CounterpartWhosHe, MSGBOX_DEFAULT

        @ Player has officially had enough.
        applymovement LOCALID_MT_CHIMNEY_COUNTERPART, Common_Movement_FaceDown
        applymovement LOCALID_PLAYER, Common_Movement_FaceUp
        waitmovement 0
        msgbox MtChimney_Text_PlayerPlease, MSGBOX_DEFAULT

        @ Everybody resets to the actual confrontation.

        @ Maxie closes out the reunion nonsense.
        @ Maxie and player both look toward counterpart.
        applymovement LOCALID_PLAYER, Common_Movement_FaceUp
        applymovement LOCALID_MT_CHIMNEY_COUNTERPART, Common_Movement_FaceRight
        applymovement LOCALID_MT_CHIMNEY_MAXIE, Common_Movement_FaceLeft
        waitmovement 0
        msgbox MtChimney_Text_MaxieReunionOver, MSGBOX_DEFAULT

        @ Player cuts in about the meteorite.
        @ Player faces toward Maxie's side, Maxie turns down to player.
        applymovement LOCALID_PLAYER, Common_Movement_FaceRight
        applymovement LOCALID_MT_CHIMNEY_MAXIE, Common_Movement_FaceDown
        waitmovement 0
        msgbox MtChimney_Text_MaxieMeteorite, MSGBOX_DEFAULT

        @ Giovanni comments directly on MAXIE'S philosophy.
        @ Counterpart also looks at Maxie for this beat.
        applymovement LOCALID_MT_CHIMNEY_COUNTERPART, Common_Movement_FaceRight
        applymovement LOCALID_MT_CHIMNEY_MAXIE, Common_Movement_FaceDown
        applymovement LOCALID_MT_CHIMNEY_MAGMA_GRUNT_1, Common_Movement_FaceUp
        waitmovement 0
        msgbox MtChimney_Text_GiovanniDifference, MSGBOX_DEFAULT

        @ Player recognizes Giovanni.
        applymovement LOCALID_PLAYER, Common_Movement_FaceRight
        applymovement LOCALID_MT_CHIMNEY_MAGMA_GRUNT_1, Common_Movement_FaceLeft
        waitmovement 0
        msgbox MtChimney_Text_PlayerRecognizesGiovanni, MSGBOX_DEFAULT

        @ Counterpart reacts to PLAYER knowing Giovanni.
        applymovement LOCALID_MT_CHIMNEY_COUNTERPART, Common_Movement_FaceDown
        applymovement LOCALID_PLAYER, Common_Movement_FaceUp
        waitmovement 0
        msgbox MtChimney_Text_CounterpartKnowsGiovanni, MSGBOX_DEFAULT

        @ Player answers counterpart.
        applymovement LOCALID_MT_CHIMNEY_COUNTERPART, Common_Movement_FaceDown
        applymovement LOCALID_PLAYER, Common_Movement_FaceUp
        waitmovement 0
        msgbox MtChimney_Text_PlayerUnfortunately, MSGBOX_DEFAULT

        @ Both return their attention to Giovanni.

        applymovement LOCALID_PLAYER, Common_Movement_FaceRight
        applymovement LOCALID_MT_CHIMNEY_MAGMA_GRUNT_1, Common_Movement_FaceLeft
        waitmovement 0
        msgbox MtChimney_Text_GiovanniAlliance1, MSGBOX_DEFAULT

        @ Giovanni says their interests overlap.
        @ Maxie looks toward Giovanni because this concerns him too.
        applymovement LOCALID_MT_CHIMNEY_MAXIE, Common_Movement_FaceDown
        applymovement LOCALID_MT_CHIMNEY_MAGMA_GRUNT_1, Common_Movement_FaceUp
        waitmovement 0
        msgbox MtChimney_Text_GiovanniOverlap, MSGBOX_DEFAULT

        @ Player calls out the Sabrina/Aqua parallel.
        applymovement LOCALID_PLAYER, Common_Movement_FaceRight
        applymovement LOCALID_MT_CHIMNEY_MAGMA_GRUNT_1, Common_Movement_FaceLeft
        waitmovement 0
        msgbox MtChimney_Text_PlayerSabrinaComparison, MSGBOX_DEFAULT

        @ SABRINA'S PERFECT CLIFF INTERRUPTION.
        @ Everyone turns because WHO THE HELL INVITED HER.
        applymovement LOCALID_PLAYER, Common_Movement_FaceUp
        applymovement LOCALID_MT_CHIMNEY_COUNTERPART, Common_Movement_FaceUp
        applymovement LOCALID_MT_CHIMNEY_MAXIE, Common_Movement_FaceUp
        applymovement LOCALID_MT_CHIMNEY_MAGMA_GRUNT_1, Common_Movement_FaceUp
        waitmovement 0
        msgbox MtChimney_Text_SabrinaCutsIn, MSGBOX_DEFAULT

        @ Back to Giovanni.
        applymovement LOCALID_PLAYER, Common_Movement_FaceRight
        applymovement LOCALID_MT_CHIMNEY_MAGMA_GRUNT_1, Common_Movement_FaceLeft
        waitmovement 0
        msgbox MtChimney_Text_GiovanniAfterSabrina1, MSGBOX_DEFAULT

        @ Player challenges Giovanni's non-answer.
        applymovement LOCALID_PLAYER, Common_Movement_FaceRight
        applymovement LOCALID_MT_CHIMNEY_MAGMA_GRUNT_1, Common_Movement_FaceLeft
        waitmovement 0
        msgbox MtChimney_Text_GiovanniAfterSabrina2, MSGBOX_DEFAULT

        @ Maxie is sick of this conversation and addresses Giovanni.
        applymovement LOCALID_MT_CHIMNEY_MAXIE, Common_Movement_FaceDown
        applymovement LOCALID_MT_CHIMNEY_MAGMA_GRUNT_1, Common_Movement_FaceUp
        waitmovement 0
        msgbox MtChimney_Text_MaxieAreWeFinished, MSGBOX_DEFAULT

        @ Giovanni answers Maxie first.
        applymovement LOCALID_MT_CHIMNEY_MAXIE, Common_Movement_FaceDown
        applymovement LOCALID_MT_CHIMNEY_MAGMA_GRUNT_1, Common_Movement_FaceUp
        waitmovement 0
        msgbox MtChimney_Text_GiovanniNotQuite, MSGBOX_DEFAULT

        @ Then Giovanni turns back to the player.
        applymovement LOCALID_PLAYER, Common_Movement_FaceRight
        applymovement LOCALID_MT_CHIMNEY_MAGMA_GRUNT_1, Common_Movement_FaceLeft
        waitmovement 0
        msgbox MtChimney_Text_GiovanniTest1, MSGBOX_DEFAULT

        @ Player points out the obvious.
        applymovement LOCALID_PLAYER, Common_Movement_FaceRight
        applymovement LOCALID_MT_CHIMNEY_MAGMA_GRUNT_1, Common_Movement_FaceLeft
        waitmovement 0
        msgbox MtChimney_Text_PlayerJustAsk, MSGBOX_DEFAULT

        @ Giovanni responds directly.
        applymovement LOCALID_PLAYER, Common_Movement_FaceRight
        applymovement LOCALID_MT_CHIMNEY_MAGMA_GRUNT_1, Common_Movement_FaceLeft
        waitmovement 0
        msgbox MtChimney_Text_GiovanniEvidence, MSGBOX_DEFAULT

        @ Maxie proposes the battle to Giovanni.
        applymovement LOCALID_MT_CHIMNEY_MAXIE, Common_Movement_FaceDown
        applymovement LOCALID_MT_CHIMNEY_MAGMA_GRUNT_1, Common_Movement_FaceUp
        waitmovement 0
        msgbox MtChimney_Text_MaxieSettleIt, MSGBOX_DEFAULT

        @ Giovanni agrees with Maxie.
        applymovement LOCALID_MT_CHIMNEY_MAXIE, Common_Movement_FaceDown
        applymovement LOCALID_MT_CHIMNEY_MAGMA_GRUNT_1, Common_Movement_FaceUp
        waitmovement 0
        msgbox MtChimney_Text_GiovanniAgreed, MSGBOX_DEFAULT

        @ Final challenge is directed at player and counterpart.
        applymovement LOCALID_MT_CHIMNEY_COUNTERPART, Common_Movement_FaceRight
        applymovement LOCALID_MT_CHIMNEY_MAXIE, Common_Movement_FaceLeft
        applymovement LOCALID_PLAYER, Common_Movement_FaceRight
        applymovement LOCALID_MT_CHIMNEY_MAGMA_GRUNT_1, Common_Movement_FaceLeft
        waitmovement 0
        msgbox MtChimney_Text_GiovanniProveWorth, MSGBOX_DEFAULT

        goto MtChimney_EventScript_StartCounterpartMultiBattle


MtChimney_EventScript_MultiBattleWon::
        @ Re-establish the summit positions after battle.
        turnobject LOCALID_PLAYER, DIR_EAST
        turnobject LOCALID_MT_CHIMNEY_COUNTERPART, DIR_EAST
        turnobject LOCALID_MT_CHIMNEY_MAXIE, DIR_WEST
        turnobject LOCALID_MT_CHIMNEY_MAGMA_GRUNT_1, DIR_WEST

        msgbox MtChimney_Text_SummitVictory, MSGBOX_DEFAULT
        closemessage
        delay 30

        @ Maxie, Giovanni, Sabrina, counterpart, and remaining Magma leave.
        fadescreenswapbuffers FADE_TO_BLACK
        removeobject LOCALID_MT_CHIMNEY_MAXIE
        removeobject LOCALID_MT_CHIMNEY_MAGMA_GRUNT_1
        removeobject LOCALID_MT_CHIMNEY_SABRINA
        removeobject LOCALID_MT_CHIMNEY_TABITHA
        removeobject LOCALID_MT_CHIMNEY_MAGMA_GRUNT_2
        setflag FLAG_HIDE_MT_CHIMNEY_TEAM_MAGMA

        @ Archie must be physically available before we add him.
        clearflag FLAG_HIDE_MT_CHIMNEY_TEAM_AQUA
        setobjectxyperm LOCALID_MT_CHIMNEY_ARCHIE, 10, 12
        addobject LOCALID_MT_CHIMNEY_ARCHIE

        fadescreenswapbuffers FADE_FROM_BLACK

        @ Player is fixed at 10,7 by the summit trigger.
        @ Archie walks straight up to 10,8.
        applymovement LOCALID_MT_CHIMNEY_ARCHIE, MtChimney_Movement_ArchieSummitApproach
        waitmovement LOCALID_MT_CHIMNEY_ARCHIE


        applymovement LOCALID_PLAYER, Common_Movement_FaceLeft
        applymovement LOCALID_MT_CHIMNEY_ARCHIE, Common_Movement_FaceRight
        waitmovement 0

        msgbox MtChimney_Text_ArchieThankYou, MSGBOX_DEFAULT
        closemessage

        @ Archie returns down the same safe path.
        applymovement LOCALID_MT_CHIMNEY_ARCHIE, MtChimney_Movement_ArchieSummitExit
        waitmovement LOCALID_MT_CHIMNEY_ARCHIE
        removeobject LOCALID_MT_CHIMNEY_ARCHIE

        removeobject LOCALID_MT_CHIMNEY_SABRINA

        @ Counterpart stayed through Archie and now checks on player.
        applymovement LOCALID_PLAYER, Common_Movement_FaceUp
        applymovement LOCALID_MT_CHIMNEY_COUNTERPART, Common_Movement_FaceDown
        waitmovement 0
        msgbox MtChimney_Text_CounterpartSummitAftermath, MSGBOX_DEFAULT

        dynmultichoice 0, 0, FALSE, 3, 0, DYN_MULTICHOICE_CB_NONE, MtChimney_Text_ChoiceGramps, MtChimney_Text_ChoicePartWays, MtChimney_Text_ChoiceEmberSpa
        switch VAR_RESULT
        case 0, MtChimney_EventScript_AftermathGramps
        case 1, MtChimney_EventScript_AftermathPartWays
        case 2, MtChimney_EventScript_AftermathEmberSpa
        case MULTI_B_PRESSED, MtChimney_EventScript_AftermathPartWays
        goto MtChimney_EventScript_AftermathPartWays



MtChimney_EventScript_AftermathGramps::
        msgbox MtChimney_Text_AftermathGramps, MSGBOX_DEFAULT
        goto MtChimney_EventScript_CounterpartFinalWalkoff

MtChimney_EventScript_AftermathPartWays::
        msgbox MtChimney_Text_AftermathPartWays, MSGBOX_DEFAULT
        goto MtChimney_EventScript_CounterpartFinalWalkoff

MtChimney_EventScript_AftermathEmberSpa::
        msgbox MtChimney_Text_AftermathEmberSpa, MSGBOX_DEFAULT
        closemessage

        @ Counterpart will be waiting in Ember Spa.
        setflag FLAG_EMBER_SPA_COUNTERPART_PENDING

        @ Mt. Chimney arc cleanup.
        removeobject LOCALID_MT_CHIMNEY_COUNTERPART
        setflag FLAG_HIDE_MT_CHIMNEY_TEAM_AQUA
        setflag FLAG_DEFEATED_EVIL_TEAM_MT_CHIMNEY
        clearflag FLAG_HIDE_FALLARBOR_HOUSE_PROF_COZMO
        setflag FLAG_HIDE_METEOR_FALLS_1F_1R_COZMO
        clearflag FLAG_HIDE_MT_CHIMNEY_LAVA_COOKIE_LADY

        @ Enter Ember Spa normally near its doorway.
        fadescreen FADE_TO_BLACK
        warp MAP_EMBER_SPA_CUSTOM, 13, 35
        waitstate

MtChimney_EventScript_CounterpartFinalWalkoff::
        closemessage

        applymovement LOCALID_MT_CHIMNEY_COUNTERPART, MtChimney_Movement_CounterpartFinalWalkoff
        waitmovement LOCALID_MT_CHIMNEY_COUNTERPART

        removeobject LOCALID_MT_CHIMNEY_COUNTERPART

        setflag FLAG_HIDE_MT_CHIMNEY_TEAM_AQUA
        setflag FLAG_DEFEATED_EVIL_TEAM_MT_CHIMNEY
        clearflag FLAG_HIDE_FALLARBOR_HOUSE_PROF_COZMO
        setflag FLAG_HIDE_METEOR_FALLS_1F_1R_COZMO
        clearflag FLAG_HIDE_MT_CHIMNEY_LAVA_COOKIE_LADY

        releaseall
        end

MtChimney_Movement_CounterpartFinalWalkoff:
        walk_left
        walk_left
        walk_down
        walk_down
        walk_down
        walk_down
        walk_down
        walk_down
        walk_down
        walk_down
        walk_down
        walk_down
        walk_down
        walk_down
        walk_down
        step_end

MtChimney_Text_ChoiceGramps:
        .string "Ask about Gramps$"

MtChimney_Text_ChoicePartWays:
        .string "Part ways for now$"

MtChimney_Text_ChoiceEmberSpa:
        .string "Go to Ember Spa$"

MtChimney_Text_AftermathGramps:
        .string "{PLAYER}: Actually...\p"
        .string "What did you and Gramps talk\n"
        .string "about?\p"
        .string "{RIVAL}: Mt. Moon. Mostly.\p"
        .string "{PLAYER}: Mostly?\p"
        .string "{RIVAL}: He kept asking what I\n"
        .string "saw. What I read.\p"
        .string "Whether anything there felt...\n"
        .string "different.\p"
        .string "{PLAYER}: Different how?\p"
        .string "{RIVAL}: He wouldn't say.\p"
        .string "{PLAYER}: Of course he wouldn't.\p"
        .string "{RIVAL}: He did tell me one thing.\p"
        .string "If I find another place that feels\n"
        .string "like Mt. Moon...\p"
        .string "Call him before I touch anything.\p"
        .string "{PLAYER}: You touched something.\p"
        .string "{RIVAL}: Immediately.$"

MtChimney_Text_AftermathPartWays:
        .string "{PLAYER}: I still have some stuff\n"
        .string "to do.\p"
        .string "I'll see you eventually.\p"
        .string "{RIVAL}: Eventually?\p"
        .string "{PLAYER}: Eventually.\p"
        .string "{RIVAL}: Good enough for me.$"

MtChimney_Text_AftermathEmberSpa:
        .string "{PLAYER}: We could go to EMBER SPA.\p"
        .string "{RIVAL}: The place that apparently\n"
        .string "just showed up?\p"
        .string "{PLAYER}: That's the one.\p"
        .string "{RIVAL}: ...Sure.\p"
        .string "After today, that barely cracks\n"
        .string "the top ten weird things.$"

MtChimney_Movement_ArchieSummitApproach:
        walk_up
        walk_up
        walk_up
        walk_up
        walk_up
        walk_right
        step_end

MtChimney_Movement_ArchieSummitExit:
        walk_left
        walk_down
        walk_down
        walk_down
        walk_down
        walk_down
        step_end


MtChimney_Text_CounterpartSummitAftermath:
        .string "{RIVAL}: ...So.\p"
        .string "{PLAYER}: Don't.\p"
        .string "{RIVAL}: I was just going to say\n"
        .string "that was a lot.\p"
        .string "{PLAYER}: That was a lot.\p"
        .string "{RIVAL}: Freak Out Guy, Giovanni,\n"
        .string "Sabrina on a cliff...\p"
        .string "{PLAYER}: Please don't summarize\n"
        .string "it.\p"
        .string "{RIVAL}: Fair.\p"
        .string "{RIVAL}: You good?\p"
        .string "{PLAYER}: Ask me after we get off\n"
        .string "this volcano.\p"
        .string "{RIVAL}: Also fair.\p"
        .string "{RIVAL}: So, what now?$"


MtChimney_EventScript_Counterpart::
        lock
        faceplayer
        msgbox MtChimney_Text_CounterpartDuringBoss, MSGBOX_DEFAULT
        release
        end

MtChimney_Movement_CounterpartEntrance:
        walk_right
        walk_up
        walk_right
        face_right
        step_end

MtChimney_Text_CounterpartDuringBoss:
        .string "{RIVAL}: Little busy right now.$"


@ MT. CHIMNEY COUNTERPART MULTI BATTLE
@ ============================================================================

MtChimney_EventScript_StartCounterpartMultiBattle::
        goto_if_eq VAR_COUNTERPART_ID, COUNTERPART_BRENDAN, MtChimney_EventScript_BattleWithBrendan
        goto_if_eq VAR_COUNTERPART_ID, COUNTERPART_MAY, MtChimney_EventScript_BattleWithMay
        goto_if_eq VAR_COUNTERPART_ID, COUNTERPART_LEXY, MtChimney_EventScript_BattleWithLexy
        goto_if_eq VAR_COUNTERPART_ID, COUNTERPART_JUSTIN, MtChimney_EventScript_BattleWithJustin
        goto_if_eq VAR_COUNTERPART_ID, COUNTERPART_MAAM, MtChimney_EventScript_BattleWithMaam
        goto_if_eq VAR_COUNTERPART_ID, COUNTERPART_SIR, MtChimney_EventScript_BattleWithSir
        goto MtChimney_EventScript_BattleWithLexy

MtChimney_EventScript_BattleWithBrendan::
        multi_2_vs_2 TRAINER_MAXIE_MT_CHIMNEY, MtChimney_Text_MaxieDefeat, TRAINER_GRUNT_MT_CHIMNEY_1, MtChimney_Text_GiovanniDefeat, PARTNER_BRENDAN
        goto MtChimney_EventScript_CheckMultiBattleResult

MtChimney_EventScript_BattleWithMay::
        multi_2_vs_2 TRAINER_MAXIE_MT_CHIMNEY, MtChimney_Text_MaxieDefeat, TRAINER_GRUNT_MT_CHIMNEY_1, MtChimney_Text_GiovanniDefeat, PARTNER_MAY
        goto MtChimney_EventScript_CheckMultiBattleResult

MtChimney_EventScript_BattleWithLexy::
        multi_2_vs_2 TRAINER_MAXIE_MT_CHIMNEY, MtChimney_Text_MaxieDefeat, TRAINER_GRUNT_MT_CHIMNEY_1, MtChimney_Text_GiovanniDefeat, PARTNER_CELESTE
        goto MtChimney_EventScript_CheckMultiBattleResult

MtChimney_EventScript_BattleWithJustin::
        multi_2_vs_2 TRAINER_MAXIE_MT_CHIMNEY, MtChimney_Text_MaxieDefeat, TRAINER_GRUNT_MT_CHIMNEY_1, MtChimney_Text_GiovanniDefeat, PARTNER_HIIRO
        goto MtChimney_EventScript_CheckMultiBattleResult

MtChimney_EventScript_BattleWithMaam::
        multi_2_vs_2 TRAINER_MAXIE_MT_CHIMNEY, MtChimney_Text_MaxieDefeat, TRAINER_GRUNT_MT_CHIMNEY_1, MtChimney_Text_GiovanniDefeat, PARTNER_ALECIYA
        goto MtChimney_EventScript_CheckMultiBattleResult

MtChimney_EventScript_BattleWithSir::
        multi_2_vs_2 TRAINER_MAXIE_MT_CHIMNEY, MtChimney_Text_MaxieDefeat, TRAINER_GRUNT_MT_CHIMNEY_1, MtChimney_Text_GiovanniDefeat, PARTNER_ASTER
        goto MtChimney_EventScript_CheckMultiBattleResult

MtChimney_EventScript_CheckMultiBattleResult::
        goto_if_eq VAR_RESULT, 1, MtChimney_EventScript_MultiBattleWon
        fadescreen FADE_TO_BLACK
        special SetCB2WhiteOut
        end


MtChimney_Text_FreakOutRecognition:
        .string "{RIVAL}: Hey!\p"
        .string "MAXIE: ...\p"
        .string "{RIVAL}: Wait. I know you.\p"
        .string "You're the guy from Brock's\n"
        .string "restaurant!$"

MtChimney_Text_FreakOutOhNo:
        .string "{PLAYER}: Oh no.$"

MtChimney_Text_FreakOutGuy:
        .string "{RIVAL}: Hey, Freak Out Guy!\p"
        .string "MAXIE: ...Excuse me?\p"
        .string "{RIVAL}: You scared the chef.$"

MtChimney_Text_FreakOutChef:
        .string "MAXIE: I did not scare the chef.\p"
        .string "{PLAYER}: You absolutely scared\n"
        .string "the chef.\p"
        .string "MAXIE: This is hardly relevant.$"

MtChimney_Text_FreakOutStillYou:
        .string "{RIVAL}: Still you though.\p"
        .string "MAXIE: ...$"

MtChimney_Text_GiovanniAreWeFinished:
        .string "GIOVANNI: Are we finished?$"

MtChimney_Text_CounterpartWhosHe:
        .string "{RIVAL}: Who's he?$"

MtChimney_Text_PlayerPlease:
        .string "{PLAYER}: PLEASE.$"



MtChimney_Text_GiovanniDefeat:
        .string "GIOVANNI: Hm.$"


MtChimney_EventScript_ArchieApproachPlayerEast::
	applymovement LOCALID_MT_CHIMNEY_ARCHIE, MtChimney_Movement_ArchieApproachPlayerEast
	waitmovement 0
	return

MtChimney_EventScript_ArchieApproachPlayerNorth::
	applymovement LOCALID_MT_CHIMNEY_ARCHIE, MtChimney_Movement_ArchieApproachPlayerNorth
	waitmovement 0
	return

MtChimney_EventScript_ArchieExitEast::
	applymovement LOCALID_MT_CHIMNEY_ARCHIE, MtChimney_Movement_ArchieExitEast
	waitmovement 0
	return

MtChimney_EventScript_ArchieExitNorth::
	applymovement LOCALID_MT_CHIMNEY_ARCHIE, MtChimney_Movement_ArchieExitNorth
	waitmovement 0
	return

MtChimney_EventScript_LavaCookieLady::
	lock
	faceplayer
	showmoneybox 0, 0
	msgbox MtChimney_Text_LavaCookiesJust200, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, MtChimney_EventScript_DeclineLavaCookie
	checkmoney 200
	goto_if_eq VAR_RESULT, FALSE, MtChimney_EventScript_NotEnoughMoney
	msgbox MtChimney_Text_ThankYouDear, MSGBOX_DEFAULT
	checkitemspace ITEM_LAVA_COOKIE
	call_if_eq VAR_RESULT, TRUE, MtChimney_EventScript_RemoveMoney
.if OW_SHOW_ITEM_DESCRIPTIONS == OW_ITEM_DESCRIPTIONS_OFF
	giveitem ITEM_LAVA_COOKIE
	goto_if_eq VAR_RESULT, FALSE, MtChimney_EventScript_BagIsFull
	hidemoneybox
	release
	end

MtChimney_EventScript_BagIsFull::
	msgbox gText_TooBadBagIsFull, MSGBOX_DEFAULT
	hidemoneybox
	release
	end
.else
	hidemoneybox
	giveitem ITEM_LAVA_COOKIE
	goto_if_eq VAR_RESULT, FALSE, MtChimney_EventScript_BagIsFull
	release
	end

MtChimney_EventScript_BagIsFull::
	msgbox gText_TooBadBagIsFull, MSGBOX_DEFAULT
	release
	end
.endif @ OW_SHOW_ITEM_DESCRIPTIONS


MtChimney_EventScript_RemoveMoney::
	removemoney 200
	updatemoneybox
	return

MtChimney_EventScript_DeclineLavaCookie::
	msgbox MtChimney_Text_OhFineThen, MSGBOX_DEFAULT
	hidemoneybox
	release
	end

MtChimney_EventScript_NotEnoughMoney::
	msgbox MtChimney_Text_YouveNotGotTheMoney, MSGBOX_DEFAULT
	hidemoneybox
	release
	end

MtChimney_Movement_ArchieApproachPlayerEast:
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_right
	step_end

MtChimney_Movement_ArchieExitEast:
	walk_left
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	step_end

MtChimney_Movement_ArchieApproachPlayerNorth:
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_right
	walk_right
	step_end

MtChimney_Movement_ArchieExitNorth:
	walk_left
	walk_left
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	step_end

MtChimney_Movement_Unused1:
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_left
	walk_left
	walk_down
	walk_down
	walk_down
	walk_down
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_down
	step_end

MtChimney_Movement_Unused2:
	walk_down
	walk_down
	walk_down
	walk_down
	walk_left
	walk_left
	walk_left
	walk_down
	step_end

MtChimney_Movement_Unused3:
	walk_right
	walk_down
	walk_down
	walk_down
	walk_down
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_down
	walk_down
	walk_down
	walk_down
	step_end

MtChimney_Movement_Unused4:
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_left
	walk_left
	walk_down
	walk_down
	walk_down
	walk_left
	walk_left
	walk_down
	walk_down
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_down
	step_end

MtChimney_Movement_Unused5:
	delay_16
	delay_16
	delay_16
	walk_down
	walk_down
	walk_down
	walk_left
	walk_left
	walk_left
	walk_down
	step_end

MtChimney_Movement_Unused6:
	delay_16
	walk_left
	walk_down
	walk_down
	walk_down
	walk_down
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_down
	walk_down
	walk_down
	walk_down
	step_end

MtChimney_Movement_Unused7:
	delay_16
	walk_left
	walk_left
	walk_down
	walk_down
	walk_down
	walk_left
	walk_left
	walk_down
	walk_down
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_down
	step_end

MtChimney_Movement_Unused8:
	delay_16
	walk_down
	walk_left
	walk_left
	walk_left
	walk_left
	walk_in_place_faster_down
	step_end

MtChimney_Movement_Unused9:
	walk_down
	walk_down
	walk_down
	walk_down
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_down
	walk_down
	walk_down
	walk_down
	step_end

MtChimney_Movement_Unused10:
	walk_down
	step_end

MtChimney_Movement_Unused11:
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	step_end

MtChimney_Movement_Unused12:
	delay_16
	delay_16
	walk_in_place_faster_left
	delay_16
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	step_end

MtChimney_Movement_Unused13:
	delay_16
	delay_16
	delay_16
	delay_16
	delay_16
	delay_16
	walk_in_place_faster_left
	delay_16
	walk_down
	walk_down
	step_end

MtChimney_Movement_Unused14:
	lock_facing_direction
	walk_fast_left
	unlock_facing_direction
	face_right
	step_end

MtChimney_Movement_Unused15:
	walk_left
	walk_in_place_faster_right
	delay_16
	step_end

MtChimney_EventScript_BusyAquaGrunt1::
	msgbox MtChimney_Text_MagmaOutnumbersUs, MSGBOX_SIGN
	end

MtChimney_EventScript_BusyAquaGrunt2::
	msgbox MtChimney_Text_LessHabitatForWaterPokemon, MSGBOX_SIGN
	end

MtChimney_EventScript_BusyAquaGrunt3::
	msgbox MtChimney_Text_MagmasNameSimilar, MSGBOX_SIGN
	end

MtChimney_EventScript_Tabitha::
	trainerbattle_single TRAINER_TABITHA_MT_CHIMNEY, MtChimney_Text_TabithaIntro, MtChimney_Text_TabithaDefeat
	msgbox MtChimney_Text_TabithaPostBattle, MSGBOX_AUTOCLOSE
	end

MtChimney_EventScript_Grunt2::
	trainerbattle_single TRAINER_GRUNT_MT_CHIMNEY_2, MtChimney_Text_Grunt2Intro, MtChimney_Text_Grunt2Defeat
	msgbox MtChimney_Text_Grunt2PostBattle, MSGBOX_AUTOCLOSE
	end

MtChimney_EventScript_RocketGirl::
        msgbox MtChimney_Text_RocketGirlOrders, MSGBOX_SIGN
        end

MtChimney_EventScript_BusyMagmaGrunt2::
	msgbox MtChimney_Text_MeteoritesPackAmazingPower, MSGBOX_SIGN
	end

MtChimney_EventScript_BusyMagmaGrunt3::
	msgbox MtChimney_Text_YouBetterNotMessWithUs, MSGBOX_SIGN
	end

MtChimney_EventScript_BusyMagmaGrunt4::
	msgbox MtChimney_Text_AquasNameSimilar, MSGBOX_SIGN
	end

MtChimney_EventScript_BusyMagmaGrunt5::
	msgbox MtChimney_Text_DouseThemInFire, MSGBOX_SIGN
	end

MtChimney_EventScript_BusyMagmaGrunt6::
	msgbox MtChimney_Text_KeepMakingMoreLand, MSGBOX_SIGN
	end

MtChimney_EventScript_MagmaPoochyena::
	msgbox MtChimney_Text_Bufoh, MSGBOX_SIGN
	end

MtChimney_EventScript_AquaPoochyena::
	msgbox MtChimney_Text_Bushaa, MSGBOX_SIGN
	end

MtChimney_EventScript_MeteoriteMachine::
	lockall
	goto_if_unset FLAG_DEFEATED_EVIL_TEAM_MT_CHIMNEY, MtChimney_EventScript_MachineOn
	goto_if_set FLAG_RECEIVED_METEORITE, MtChimney_EventScript_MachineOff
	msgbox MtChimney_Text_RemoveTheMeteorite, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, MtChimney_EventScript_LeaveMeteoriteAlone
	msgbox MtChimney_Text_PlayerRemovedMeteorite, MSGBOX_DEFAULT
	giveitem ITEM_METEORITE
	goto_if_eq VAR_RESULT, FALSE, Common_EventScript_ShowBagIsFull
	setflag FLAG_RECEIVED_METEORITE
	releaseall
	end

MtChimney_EventScript_LeaveMeteoriteAlone::
	msgbox MtChimney_Text_PlayerLeftMeteorite, MSGBOX_DEFAULT
	releaseall
	end

MtChimney_EventScript_MachineOff::
	msgbox MtChimney_Text_MachineMakesNoResponse, MSGBOX_DEFAULT
	releaseall
	end

MtChimney_EventScript_MachineOn::
	msgbox MtChimney_Text_MeteoriteFittedOnMachine, MSGBOX_DEFAULT
	releaseall
	end

MtChimney_EventScript_RouteSign::
	msgbox MtChimney_Text_RouteSign, MSGBOX_SIGN
	end

MtChimney_EventScript_Shelby::
	trainerbattle_single TRAINER_SHELBY_1, MtChimney_Text_ShelbyIntro, MtChimney_Text_ShelbyDefeat, MtChimney_EventScript_DefeatedShelby
	specialvar VAR_RESULT, ShouldTryRematchBattle
	goto_if_eq VAR_RESULT, TRUE, MtChimney_EventScript_RematchShelby
	msgbox MtChimney_Text_ShelbyPostBattle, MSGBOX_DEFAULT
	release
	end

MtChimney_EventScript_DefeatedShelby::
	special PlayerFaceTrainerAfterBattle
	waitmovement 0
	msgbox MtChimney_Text_ShelbyRegister, MSGBOX_DEFAULT
	register_matchcall TRAINER_SHELBY_1
	release
	end

MtChimney_EventScript_RematchShelby::
	trainerbattle_rematch TRAINER_SHELBY_1, MtChimney_Text_ShelbyRematchIntro, MtChimney_Text_ShelbyRematchDefeat
	msgbox MtChimney_Text_ShelbyPostRematch, MSGBOX_AUTOCLOSE
	end

MtChimney_EventScript_Melissa::
	trainerbattle_single TRAINER_MELISSA, MtChimney_Text_MelissaIntro, MtChimney_Text_MelissaDefeat
	msgbox MtChimney_Text_MelissaPostBattle, MSGBOX_AUTOCLOSE
	end

MtChimney_EventScript_Sheila::
	trainerbattle_single TRAINER_SHEILA, MtChimney_Text_SheilaIntro, MtChimney_Text_SheilaDefeat
	msgbox MtChimney_Text_SheilaPostBattle, MSGBOX_AUTOCLOSE
	end

MtChimney_EventScript_Shirley::
	trainerbattle_single TRAINER_SHIRLEY, MtChimney_Text_ShirleyIntro, MtChimney_Text_ShirleyDefeat
	msgbox MtChimney_Text_ShirleyPostBattle, MSGBOX_AUTOCLOSE
	end

MtChimney_EventScript_Grunt1::
	trainerbattle_single TRAINER_GRUNT_MT_CHIMNEY_1, MtChimney_Text_Grunt1Intro, MtChimney_Text_Grunt1Defeat
	msgbox MtChimney_Text_Grunt1PostBattle, MSGBOX_AUTOCLOSE
	end

MtChimney_EventScript_Sawyer::
	trainerbattle_single TRAINER_SAWYER_1, MtChimney_Text_SawyerIntro, MtChimney_Text_SawyerDefeat, MtChimney_EventScript_SawyerDefeated
	specialvar VAR_RESULT, ShouldTryRematchBattle
	goto_if_eq VAR_RESULT, TRUE, MtChimney_EventScript_SawyerRematch
	msgbox MtChimney_Text_SawyerPostBattle, MSGBOX_DEFAULT
	release
	end

MtChimney_EventScript_SawyerDefeated::
	special PlayerFaceTrainerAfterBattle
	waitmovement 0
	msgbox MtChimney_Text_SawyerRegister, MSGBOX_DEFAULT
	register_matchcall TRAINER_SAWYER_1
	release
	end

MtChimney_EventScript_SawyerRematch::
	trainerbattle_rematch TRAINER_SAWYER_1, MtChimney_Text_SawyerRematchIntro, MtChimney_Text_SawyerRematchDefeat
	msgbox MtChimney_Text_SawyerPostRematch, MSGBOX_AUTOCLOSE
	end

MtChimney_Text_MeteoriteWillActivateVolcano:
	.string "The power contained in the METEORITE…\p"
	.string "By amplifying its power with this\n"
	.string "machine, MT. CHIMNEY's volcanic\l"
	.string "activity will instantly intensify…\p"
	.string "Its energy will grow deep inside\n"
	.string "the crater and…\l"
	.string "Fufufu…$"

MtChimney_Text_MaxieReunionOver:
        .string "MAXIE: If the reunion is over...$"

MtChimney_Text_MaxieMeteorite:
        .string "{PLAYER}: You stole the METEORITE.\p"
        .string "MAXIE: Stole?\p"
        .string "Such a crude description.\p"
        .string "Its power is being put toward a\n"
        .string "far greater purpose.\p"
        .string "{PLAYER}: By making a volcano\n"
        .string "erupt?!\p"
        .string "MAXIE: By advancing our cause.$"

MtChimney_Text_GiovanniDifference:
        .string "GIOVANNI: And there lies our\n"
        .string "difference.$"

MtChimney_Text_PlayerRecognizesGiovanni:
        .string "{PLAYER}: ...Giovanni.$"

MtChimney_Text_CounterpartKnowsGiovanni:
        .string "{RIVAL}: You know him too?$"

MtChimney_Text_PlayerUnfortunately:
        .string "{PLAYER}: Unfortunately.$"

MtChimney_Text_GiovanniAlliance1:
        .string "{PLAYER}: You're working with\n"
        .string "TEAM MAGMA?\p"
        .string "GIOVANNI: No.\p"
        .string "{PLAYER}: No?$"

MtChimney_Text_GiovanniOverlap:
        .string "GIOVANNI: Our interests happen to\n"
        .string "overlap.$"

MtChimney_Text_PlayerSabrinaComparison:
        .string "{PLAYER}: Like Sabrina isn't\n"
        .string "working with TEAM AQUA?$"

MtChimney_Text_SabrinaCutsIn:
        .string "SABRINA: Yes.\p"
        .string "Like Sabrina is not working with\n"
        .string "TEAM AQUA.\p"
        .string "{PLAYER}: Sabrin...\p"
        .string "{PLAYER}: You know what?\p"
        .string "I'm not even surprised you're\n"
        .string "just... here.\p"
        .string "{PLAYER}: Whatever. Anyway...$"

MtChimney_Text_GiovanniAfterSabrina1:
        .string "GIOVANNI: As I was saying.\p"
        .string "{PLAYER}: You weren't saying\n"
        .string "anything.\p"
        .string "GIOVANNI: Then we're caught up.$"

MtChimney_Text_GiovanniAfterSabrina2:
        .string "{PLAYER}: That's not an answer.\p"
        .string "GIOVANNI: You're becoming\n"
        .string "observant.$"

MtChimney_Text_MaxieAreWeFinished:
        .string "MAXIE: Are we finished?$"

MtChimney_Text_GiovanniNotQuite:
        .string "GIOVANNI: Not quite.$"

MtChimney_Text_GiovanniTest1:
        .string "GIOVANNI: They've come farther\n"
        .string "than I expected.\p"
        .string "I would like to know why.$"

MtChimney_Text_PlayerJustAsk:
        .string "{PLAYER}: You could just ask.$"

MtChimney_Text_GiovanniEvidence:
        .string "GIOVANNI: I prefer evidence.$"

MtChimney_Text_MaxieSettleIt:
        .string "MAXIE: Then let us settle this.$"

MtChimney_Text_GiovanniAgreed:
        .string "GIOVANNI: Agreed.$"

MtChimney_Text_GiovanniProveWorth:
        .string "GIOVANNI: Prove your worth.$"

MtChimney_Text_MaxieDefeat:
	.string "What?!\p"
	.string "I, MAXIE, was caught off guard?!$"

MtChimney_Text_SummitVictory:
        .string "MAXIE: ...Impossible.\p"
        .string "{RIVAL}: That was AWESOME.\p"
        .string "{PLAYER}: We almost died.\p"
        .string "{RIVAL}: Still awesome.\p"
        .string "GIOVANNI: Hm.\p"
        .string "{PLAYER}: Don't.\p"
        .string "GIOVANNI: I said nothing.\p"
        .string "{PLAYER}: You were about to say\n"
        .string "interesting.\p"
        .string "GIOVANNI: Perhaps.\p"
        .string "MAXIE: Enough!\p"
        .string "TEAM MAGMA will withdraw for\n"
        .string "now.\p"
        .string "But this changes nothing.\p"
        .string "Even without the METEORITE,\n"
        .string "our plans continue.\p"
        .string "The ORB remains.\p"
        .string "GIOVANNI: On the contrary.\p"
        .string "It changes one thing.\p"
        .string "Now I know what they're capable\n"
        .string "of.\p"
        .string "{PLAYER}: And what exactly does\n"
        .string "that mean?\p"
        .string "GIOVANNI: You'll know when you're\n"
        .string "able.\p"
        .string "{PLAYER}: ...I hate when you do\n"
        .string "that.\p"
        .string "{RIVAL}: He does that often?\p"
        .string "{PLAYER}: Unfortunately.$"


MtChimney_Text_TabithaIntro:
	.string "Hehehe!\p"
	.string "So you've come all the way here!\p"
	.string "But you're too late!\n"
	.string "I've already delivered the METEORITE\l"
	.string "from METEOR FALLS to the BOSS!$"

MtChimney_Text_TabithaDefeat:
	.string "Hehehe…\p"
	.string "Even though I've lost, if our leader\n"
	.string "awakens that thing…$"

MtChimney_Text_TabithaPostBattle:
	.string "BOSS, hurry!\n"
	.string "Give it the METEORITE's energy!\p"
	.string "Hehehe…$"

MtChimney_Text_Grunt2Intro:
	.string "We of TEAM MAGMA are working hard for\n"
	.string "everyone's sake.\p"
	.string "Like, if that thing's power made more\n"
	.string "land, there'd be more places to live.\p"
	.string "Everyone'd be happy!$"

MtChimney_Text_Grunt2Defeat:
	.string "Hunh?\n"
	.string "What do you mean I lost?$"

MtChimney_Text_Grunt2PostBattle:
	.string "Our BOSS says, “It will make everyone\n"
	.string "happy.”\p"
	.string "But why does everyone keep getting\n"
	.string "in our way?$"

MtChimney_Text_Grunt1Intro:
	.string "If there were more land, I'd be able\n"
	.string "to get a big house of my own!\p"
	.string "I'm going to build it on hardened lava!$"

MtChimney_Text_Grunt1Defeat:
	.string "My dream of a big house…$"

MtChimney_Text_Grunt1PostBattle:
	.string "A kid like you, you ought to be\n"
	.string "splashing about in the waves!$"

MtChimney_Text_TeamAquaAlwaysMessingWithPlans:
	.string "That annoying TEAM AQUA…\n"
	.string "They always mess with our plans!$"

MtChimney_Text_MeteoritesPackAmazingPower:
	.string "METEORITES pack amazing power!$"

MtChimney_Text_YouBetterNotMessWithUs:
	.string "You'd better not mess with us!\p"
	.string "We're trying to awaken that thing\n"
	.string "for the benefit of everyone!$"

MtChimney_Text_AquasNameSimilar:
	.string "We're TEAM MAGMA!\p"
	.string "They're TEAM AQUA!\p"
	.string "It totally annoys me that they'd\n"
	.string "use a name like ours!$"

MtChimney_Text_DouseThemInFire:
	.string "Yeah!\n"
	.string "Douse them in fire!$"

MtChimney_Text_KeepMakingMoreLand:
	.string "We're going to keep making more land!$"

MtChimney_Text_Bufoh:
	.string "Bufoh!$"

MtChimney_Text_ArchieGoStopTeamMagma:
	.string "ARCHIE: Grr, {PLAYER}!\n"
	.string "I should've guessed you'd show up!\p"
	.string "See for yourself what the fanatics\n"
	.string "of TEAM MAGMA are up to!\p"
	.string "They're trying to inject the stolen\n"
	.string "METEORITE's power into the volcano!\p"
	.string "Doing something like that will cause\n"
	.string "the volcano's eruption!$"

MtChimney_Text_ArchieIHaveMyHandsFull:
	.string "ARCHIE: Grrr…\p"
	.string "I want to stop that MAXIE,\n"
	.string "but I can't!\p"
	.string "Not when I have my hands full battling\n"
	.string "three opponents at once!$"

MtChimney_Text_ArchieThankYou:
	.string "ARCHIE: {PLAYER}!\n"
	.string "Thank you!\p"
	.string "With your help, we thwarted TEAM\n"
	.string "MAGMA's destructive plan!\p"
	.string "But… You…\n"
	.string "Whose side are you on?\p"
	.string "Ah, it doesn't matter.\p"
	.string "We will remain vigilant and keep up\n"
	.string "our pursuit of TEAM MAGMA.\p"
	.string "{PLAYER}, we shall meet again!$"

MtChimney_Text_MagmaOutnumbersUs:
	.string "Darn… TEAM MAGMA outnumbers us!\n"
	.string "We can't keep up with them!$"

MtChimney_Text_LessHabitatForWaterPokemon:
	.string "If they expand the land, there'll be\n"
	.string "less habitats for WATER POKéMON!$"

MtChimney_Text_MagmasNameSimilar:
	.string "We're TEAM AQUA!\p"
	.string "They're TEAM MAGMA!\p"
	.string "It burns me up that they'd use such\n"
	.string "a confusing name!$"

MtChimney_Text_Bushaa:
	.string "Bushaa!$"

MtChimney_Text_LavaCookiesJust200:
	.string "LAVA COOKIES are MT. CHIMNEY's local\n"
	.string "specialty.\p"
	.string "Try one. It's just ¥200.$"

MtChimney_Text_ThankYouDear:
	.string "Thank you, dear!$"

MtChimney_Text_YouveNotGotTheMoney:
	.string "Oh, dear. You can't buy a thing if\n"
	.string "you've not got the money.$"

MtChimney_Text_OhFineThen:
	.string "Oh, fine then.$"

MtChimney_Text_MeteoriteFittedOnMachine:
	.string "A METEORITE is fitted on a mysterious\n"
	.string "machine…\p"
	.string "The machine seems to be storing\n"
	.string "energy in the METEORITE.$"

MtChimney_Text_RemoveTheMeteorite:
	.string "A METEORITE is fitted on a mysterious\n"
	.string "machine…\p"
	.string "Do you want to remove the METEORITE?$"

MtChimney_Text_PlayerRemovedMeteorite:
	.string "{PLAYER} removed the METEORITE from\n"
	.string "the mysterious machine.$"

MtChimney_Text_PlayerLeftMeteorite:
	.string "{PLAYER} left the METEORITE where\n"
	.string "it was.$"

MtChimney_Text_MachineMakesNoResponse:
	.string "This mysterious machine…\n"
	.string "It makes no response whatsoever.$"

MtChimney_Text_RouteSign:
	.string "{DOWN_ARROW} JAGGED PATH\n"
	.string "LAVARIDGE TOWN AHEAD$"

MtChimney_Text_ShelbyIntro:
	.string "I've been to the hot springs and\n"
	.string "refreshed my tired bones.\l"
	.string "Right now I'm feeling strong!$"

MtChimney_Text_ShelbyDefeat:
	.string "Oh, my goodness.\n"
	.string "Now, aren't you something!$"

MtChimney_Text_ShelbyPostBattle:
	.string "Well, well, I've lost. I can't call\n"
	.string "myself an EXPERT now, can I?$"

MtChimney_Text_ShelbyRegister:
	.string "Thank you, child. It was fun, as if\n"
	.string "I were battling my own grandchild.\p"
	.string "Please, come see me again for\n"
	.string "a rematch.$"

MtChimney_Text_ShelbyRematchIntro:
	.string "If you can mesh your heart with those\n"
	.string "of your POKéMON, why, you should be\l"
	.string "able to achieve great things.$"

MtChimney_Text_ShelbyRematchDefeat:
	.string "Oh, my goodness.\n"
	.string "Now, aren't you something!$"

MtChimney_Text_ShelbyPostRematch:
	.string "Perhaps your heart has become one\n"
	.string "with the hearts of your POKéMON.$"

MtChimney_Text_MelissaIntro:
	.string "I've got the fire in me, baby.\n"
	.string "I can't stand it! I have to battle!$"

MtChimney_Text_MelissaDefeat:
	.string "Ooh, that was a scorching-hot match!$"

MtChimney_Text_MelissaPostBattle:
	.string "The heat of MT. CHIMNEY warms\n"
	.string "me up, baby!$"

MtChimney_Text_SheilaIntro:
	.string "I've finally made it to MT. CHIMNEY.\n"
	.string "I want to make my POKéMON battle!$"

MtChimney_Text_SheilaDefeat:
	.string "The way you battle…\n"
	.string "It's like a MT. CHIMNEY eruption!$"

MtChimney_Text_SheilaPostBattle:
	.string "Like I said, I've finally made it to\n"
	.string "MT. CHIMNEY. It would be a shame if\l"
	.string "I only do a little sightseeing…\p"
	.string "I want to get in some battles and buy\n"
	.string "COOKIES as souvenirs.$"

MtChimney_Text_ShirleyIntro:
	.string "Since I bathed in the hot springs,\n"
	.string "I've been feeling great!\l"
	.string "I'm sure I'm going to win!$"

MtChimney_Text_ShirleyDefeat:
	.string "Yowch!\n"
	.string "I'm getting a chill out of the water.$"

MtChimney_Text_ShirleyPostBattle:
	.string "I'll have to take another dip in the\n"
	.string "hot springs. Want to join me?\p"
	.string "Just joking!$"

MtChimney_Text_SawyerIntro:
	.string "This is one fine mountain! Plenty of\n"
	.string "hot people around for company!$"

MtChimney_Text_SawyerDefeat:
	.string "Oh, you're a real firebrand, too!$"

MtChimney_Text_SawyerPostBattle:
	.string "I think I need a dip in LAVARIDGE\n"
	.string "HOT SPRING with the locals!$"

MtChimney_Text_SawyerRegister:
	.string "I like little fireballs like you.\n"
	.string "Let me register you in my POKéNAV.$"

MtChimney_Text_SawyerRematchIntro:
	.string "I'm happily surrounded by hot people\n"
	.string "around these parts. I won't lose!$"

MtChimney_Text_SawyerRematchDefeat:
	.string "Gosh, you're still the same\n"
	.string "firebrand as before!$"

MtChimney_Text_SawyerPostRematch:
	.string "Actually, it really is hot here.\n"
	.string "I'm overdressed for these parts.$"

@ ============================================================================
@ CUSTOM MT. CHIMNEY STAGING
@ ============================================================================

MtChimney_EventScript_Giovanni::
    lock
    faceplayer
    msgbox MtChimney_Text_GiovanniWaiting, MSGBOX_DEFAULT
    release
    end

MtChimney_EventScript_Sabrina::
    lock
    faceplayer
    msgbox MtChimney_Text_SabrinaWatching, MSGBOX_DEFAULT
    release
    end

MtChimney_EventScript_RocketGrunt::
    lock
    faceplayer
    msgbox MtChimney_Text_RocketGruntOrders, MSGBOX_DEFAULT
    release
    end

MtChimney_Text_GiovanniWaiting:
    .string "GIOVANNI: You've made it this far.\p"
    .string "Let's see what you do next.$"

MtChimney_Text_SabrinaWatching:
    .string "SABRINA: ...$"

MtChimney_Text_RocketGruntOrders:
    .string "We're here on orders.\p"
    .string "That's all you need to know.$"



MtChimney_Text_RocketGirlOrders:
        .string "I was told to stand here.\p"
        .string "I was not told why.\p"
        .string "Apparently that part was\n"
        .string "optional.$"


MtChimney_EventScript_FlannerySpaHint::
        msgbox MtChimney_Text_FlannerySpaHint, MSGBOX_NPC
        end

MtChimney_Text_FlannerySpaHint:
        .string "I've lived around here forever.\p"
        .string "And that place definitely wasn't\n"
        .string "there before.\p"
        .string "They call it EMBER SPA?\p"
        .string "I was skeptical at first...\p"
        .string "But it's actually pretty cool.\p"
        .string "You should check it out.$"
