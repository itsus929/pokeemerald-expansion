MeteorFalls_1F_1R_MapScripts::
	map_script MAP_SCRIPT_ON_LOAD, MeteorFalls_1F_1R_OnLoad
	.byte 0

MeteorFalls_1F_1R_OnLoad:
    call MeteorFalls_1F_1R_SetCounterpartGraphics
    call_if_set FLAG_SYS_GAME_CLEAR, MeteorFalls_1F_1R_EventScript_OpenStevensCave
    end

MeteorFalls_1F_1R_SetCounterpartGraphics:
    goto_if_eq VAR_COUNTERPART_ID, COUNTERPART_BRENDAN, MeteorFalls_1F_1R_SetBrendan
    goto_if_eq VAR_COUNTERPART_ID, COUNTERPART_MAY, MeteorFalls_1F_1R_SetMay
    goto_if_eq VAR_COUNTERPART_ID, COUNTERPART_LEXY, MeteorFalls_1F_1R_SetLexy
    goto_if_eq VAR_COUNTERPART_ID, COUNTERPART_JUSTIN, MeteorFalls_1F_1R_SetJustin
    goto_if_eq VAR_COUNTERPART_ID, COUNTERPART_MAAM, MeteorFalls_1F_1R_SetMaam
    goto_if_eq VAR_COUNTERPART_ID, COUNTERPART_SIR, MeteorFalls_1F_1R_SetSir
    return

MeteorFalls_1F_1R_SetBrendan:
    setvar VAR_OBJ_GFX_ID_0, OBJ_EVENT_GFX_BRENDAN_NORMAL
    return

MeteorFalls_1F_1R_SetMay:
    setvar VAR_OBJ_GFX_ID_0, OBJ_EVENT_GFX_MAY_NORMAL
    return

MeteorFalls_1F_1R_SetLexy:
    setvar VAR_OBJ_GFX_ID_0, OBJ_EVENT_GFX_LEXY_NORMAL
    return

MeteorFalls_1F_1R_SetJustin:
    setvar VAR_OBJ_GFX_ID_0, OBJ_EVENT_GFX_JUSTIN_NORMAL
    return

MeteorFalls_1F_1R_SetMaam:
    setvar VAR_OBJ_GFX_ID_0, OBJ_EVENT_GFX_MAAM_NORMAL
    return

MeteorFalls_1F_1R_SetSir:
    setvar VAR_OBJ_GFX_ID_0, OBJ_EVENT_GFX_SIR_NORMAL
    return

MeteorFalls_1F_1R_EventScript_OpenStevensCave::
	setmetatile 4, 1, METATILE_MeteorFalls_CaveEntrance_Top, TRUE
	setmetatile 3, 2, METATILE_MeteorFalls_CaveEntrance_Left, TRUE
	setmetatile 4, 2, METATILE_MeteorFalls_CaveEntrance_Bottom, FALSE
	setmetatile 5, 2, METATILE_MeteorFalls_CaveEntrance_Right, TRUE
	return

MeteorFalls_1F_1R_EventScript_MagmaStealsMeteoriteScene::
	lockall
	playbgm MUS_ENCOUNTER_MAGMA, FALSE
	applymovement LOCALID_PLAYER, Common_Movement_FaceDown
	waitmovement 0
	delay 30
	applymovement LOCALID_METEOR_FALLS_MAGMA_GRUNT_1, Common_Movement_WalkInPlaceDown
	waitmovement 0
	msgbox MeteorFalls_1F_1R_Text_WithThisMeteorite, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_METEOR_FALLS_MAGMA_GRUNT_1, Common_Movement_WalkInPlaceFasterUp
	applymovement LOCALID_METEOR_FALLS_MAGMA_GRUNT_2, Common_Movement_WalkInPlaceFasterUp
	waitmovement 0
	playse SE_PIN
	applymovement LOCALID_METEOR_FALLS_MAGMA_GRUNT_1, Common_Movement_ExclamationMark
	waitmovement 0
	applymovement LOCALID_METEOR_FALLS_MAGMA_GRUNT_1, Common_Movement_Delay48
	waitmovement 0
	msgbox MeteorFalls_1F_1R_Text_DontExpectMercyFromMagma, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_METEOR_FALLS_MAGMA_GRUNT_1, MeteorFalls_1F_1R_Movement_MagmaGruntApproachPlayer
	waitmovement 0
	msgbox MeteorFalls_1F_1R_Text_HoldItRightThereMagma, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_PLAYER, Common_Movement_WalkInPlaceFasterLeft
	applymovement LOCALID_METEOR_FALLS_MAGMA_GRUNT_1, Common_Movement_WalkInPlaceFasterLeft
	applymovement LOCALID_METEOR_FALLS_MAGMA_GRUNT_2, Common_Movement_WalkInPlaceFasterLeft
	waitmovement 0
	addobject LOCALID_METEOR_FALLS_ARCHIE
	addobject LOCALID_METEOR_FALLS_AQUA_GRUNT_1
	addobject LOCALID_METEOR_FALLS_AQUA_GRUNT_2
	playbgm MUS_ENCOUNTER_AQUA, FALSE
	applymovement LOCALID_METEOR_FALLS_ARCHIE, MeteorFalls_1F_1R_Movement_ArchieArrive
	applymovement LOCALID_METEOR_FALLS_AQUA_GRUNT_1, MeteorFalls_1F_1R_Movement_AquaGrunt1Arrive
	applymovement LOCALID_METEOR_FALLS_AQUA_GRUNT_2, MeteorFalls_1F_1R_Movement_AquaGrunt2Arrive
	waitmovement 0
	applymovement LOCALID_METEOR_FALLS_MAGMA_GRUNT_1, Common_Movement_WalkInPlaceFasterLeft
	applymovement LOCALID_METEOR_FALLS_MAGMA_GRUNT_2, Common_Movement_WalkInPlaceFasterLeft
	waitmovement 0
        delay 20
        delay 20
        special SpawnCameraObject
        applymovement LOCALID_CAMERA, MeteorFalls_1F_1R_Movement_CameraPanDown
        waitmovement 0
        applymovement LOCALID_METEOR_FALLS_MAGMA_GRUNT_1, Common_Movement_WalkInPlaceFasterDown
        applymovement LOCALID_METEOR_FALLS_MAGMA_GRUNT_2, Common_Movement_WalkInPlaceFasterDown
        applymovement LOCALID_METEOR_FALLS_ARCHIE, Common_Movement_WalkInPlaceFasterDown
        waitmovement 0
        msgbox MeteorFalls_1F_1R_Text_GiovanniEnough, MSGBOX_DEFAULT
        closemessage

        msgbox MeteorFalls_1F_1R_Text_MagmaWhoAreYou, MSGBOX_DEFAULT
        closemessage

        msgbox MeteorFalls_1F_1R_Text_GiovanniObserve, MSGBOX_DEFAULT
        closemessage

        msgbox MeteorFalls_1F_1R_Text_ArchieExcuseMe, MSGBOX_DEFAULT
        closemessage

        msgbox MeteorFalls_1F_1R_Text_GiovanniBothOfYou, MSGBOX_DEFAULT
        closemessage

        applymovement LOCALID_METEOR_FALLS_GIOVANNI, Common_Movement_WalkInPlaceFasterRight
        applymovement 10, Common_Movement_WalkInPlaceFasterLeft
        waitmovement 0
        msgbox MeteorFalls_1F_1R_Text_GiovanniCozmo, MSGBOX_DEFAULT
        closemessage

        msgbox MeteorFalls_1F_1R_Text_CozmoCavern, MSGBOX_DEFAULT
        closemessage

        msgbox MeteorFalls_1F_1R_Text_GiovanniMtMoon, MSGBOX_DEFAULT
        closemessage

        msgbox MeteorFalls_1F_1R_Text_CozmoMtMoon, MSGBOX_DEFAULT
        closemessage

        msgbox MeteorFalls_1F_1R_Text_GiovanniNotHere, MSGBOX_DEFAULT
        closemessage
        delay 20
        applymovement LOCALID_CAMERA, MeteorFalls_1F_1R_Movement_CameraPanUp
        waitmovement 0
        special RemoveCameraObject
        applymovement LOCALID_METEOR_FALLS_MAGMA_GRUNT_1, Common_Movement_WalkInPlaceFasterLeft
        applymovement LOCALID_METEOR_FALLS_MAGMA_GRUNT_2, Common_Movement_WalkInPlaceFasterLeft
        applymovement LOCALID_METEOR_FALLS_GIOVANNI, Common_Movement_WalkInPlaceFasterUp
        waitmovement 0
	msgbox MeteorFalls_1F_1R_Text_BeSeeingYouTeamAqua, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_PLAYER, MeteorFalls_1F_1R_Movement_PushPlayerOutOfWay
	applymovement LOCALID_METEOR_FALLS_MAGMA_GRUNT_1, MeteorFalls_1F_1R_Movement_MagmaGrunt1Exit
	applymovement LOCALID_METEOR_FALLS_MAGMA_GRUNT_2, MeteorFalls_1F_1R_Movement_MagmaGrunt2Exit
	waitmovement 0
	removeobject LOCALID_METEOR_FALLS_MAGMA_GRUNT_1
	removeobject LOCALID_METEOR_FALLS_MAGMA_GRUNT_2
	applymovement LOCALID_METEOR_FALLS_ARCHIE, MeteorFalls_1F_1R_Movement_ArchieApproachPlayer
	waitmovement 0
	msgbox MeteorFalls_1F_1R_Text_ArchieSeenYouBefore, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_METEOR_FALLS_AQUA_GRUNT_1, MeteorFalls_1F_1R_Movement_AquaGrunt1ApproachArchie
	applymovement LOCALID_METEOR_FALLS_AQUA_GRUNT_2, MeteorFalls_1F_1R_Movement_AquaGrunt2ApproachArchie
	waitmovement 0
	msgbox MeteorFalls_1F_1R_Text_BossWeShouldChaseMagma, MSGBOX_DEFAULT
	applymovement LOCALID_METEOR_FALLS_ARCHIE, Common_Movement_WalkInPlaceFasterDown
	waitmovement 0
	msgbox MeteorFalls_1F_1R_Text_ArchieYesNoTellingWhatMagmaWillDo, MSGBOX_DEFAULT
	applymovement LOCALID_METEOR_FALLS_ARCHIE, Common_Movement_WalkInPlaceFasterLeft
	waitmovement 0
	msgbox MeteorFalls_1F_1R_Text_ArchieFarewell, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_METEOR_FALLS_ARCHIE, MeteorFalls_1F_1R_Movement_ArchieExit
	applymovement LOCALID_METEOR_FALLS_AQUA_GRUNT_1, MeteorFalls_1F_1R_Movement_AquaGrunt1Exit
	applymovement LOCALID_METEOR_FALLS_AQUA_GRUNT_2, MeteorFalls_1F_1R_Movement_AquaGrunt2Exit
	waitmovement 0
	fadedefaultbgm
	removeobject LOCALID_METEOR_FALLS_ARCHIE
	removeobject LOCALID_METEOR_FALLS_AQUA_GRUNT_1
	removeobject LOCALID_METEOR_FALLS_AQUA_GRUNT_2
        special SpawnCameraObject
        applymovement LOCALID_CAMERA, MeteorFalls_1F_1R_Movement_CameraPanDown
        waitmovement 0

        applymovement LOCALID_PLAYER, Common_Movement_WalkInPlaceFasterDown
        applymovement LOCALID_METEOR_FALLS_GIOVANNI, Common_Movement_WalkInPlaceFasterUp
        waitmovement 0

        msgbox MeteorFalls_1F_1R_Text_PlayerHowKnow, MSGBOX_DEFAULT
        closemessage

        msgbox MeteorFalls_1F_1R_Text_GiovanniBeenThere, MSGBOX_DEFAULT
        closemessage

        msgbox MeteorFalls_1F_1R_Text_GiovanniCallAlakazam, MSGBOX_DEFAULT
        closemessage

        addobject LOCALID_METEOR_FALLS_ALAKAZAM
        playmoncry SPECIES_ALAKAZAM, CRY_MODE_NORMAL
        waitmoncry
        delay 20

        msgbox MeteorFalls_1F_1R_Text_GiovanniTeleport, MSGBOX_DEFAULT
        closemessage

        delay 12
        removeobject LOCALID_METEOR_FALLS_GIOVANNI
        removeobject LOCALID_METEOR_FALLS_ALAKAZAM
        delay 20

        applymovement LOCALID_CAMERA, MeteorFalls_1F_1R_Movement_CameraPanUp
        waitmovement 0
        special RemoveCameraObject

	setflag FLAG_HIDE_ROUTE_112_TEAM_MAGMA
	setflag FLAG_MET_ARCHIE_METEOR_FALLS
	setflag FLAG_HIDE_FALLARBOR_TOWN_BATTLE_TENT_SCOTT
	setvar VAR_METEOR_FALLS_STATE, 1
	releaseall
	end

MeteorFalls_1F_1R_Movement_MagmaGruntApproachPlayer:
	walk_right
	walk_right
	walk_in_place_faster_up
	step_end

MeteorFalls_1F_1R_Movement_MagmaGrunt1Exit:
	walk_fast_up
	walk_fast_up
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	step_end

MeteorFalls_1F_1R_Movement_MagmaGrunt2Exit:
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	step_end

MeteorFalls_1F_1R_Movement_ArchieArrive:
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	step_end

MeteorFalls_1F_1R_Movement_AquaGrunt1Arrive:
	delay_16
	delay_16
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	step_end

MeteorFalls_1F_1R_Movement_AquaGrunt2Arrive:
	delay_16
	delay_16
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	step_end

MeteorFalls_1F_1R_Movement_ArchieExit:
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	step_end

MeteorFalls_1F_1R_Movement_ArchieApproachPlayer:
	walk_right
	walk_right
	walk_up
	walk_up
	walk_in_place_faster_left
	step_end

MeteorFalls_1F_1R_Movement_AquaGrunt1Exit:
	walk_up
	walk_up
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	step_end

MeteorFalls_1F_1R_Movement_AquaGrunt1ApproachArchie:
	walk_right
	walk_right
	walk_right
	walk_in_place_faster_up
	step_end

MeteorFalls_1F_1R_Movement_AquaGrunt2Exit:
	walk_up
	walk_up
	walk_up
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	step_end

MeteorFalls_1F_1R_Movement_AquaGrunt2ApproachArchie:
	walk_right
	walk_right
	walk_right
	walk_in_place_faster_up
	step_end

MeteorFalls_1F_1R_Movement_PushPlayerOutOfWay:
	walk_in_place_faster_down
	delay_4
	walk_in_place_faster_right
	lock_facing_direction
	walk_left
	unlock_facing_direction
	face_right
	step_end

MeteorFalls_1F_1R_EventScript_ProfCozmo::
	lock
	faceplayer
	goto_if_set FLAG_MET_PROF_COZMO, MeteorFalls_1F_1R_EventScript_MetCozmo
	setflag FLAG_MET_PROF_COZMO
	msgbox MeteorFalls_1F_1R_Text_MeetProfCozmo, MSGBOX_DEFAULT
	release
	end

MeteorFalls_1F_1R_EventScript_MetCozmo::
	msgbox MeteorFalls_1F_1R_Text_WhatsTeamMagmaDoingAtMtChimney, MSGBOX_DEFAULT
	release
	end

MeteorFalls_1F_1R_Text_WithThisMeteorite:
	.string "Hehehe!\p"
	.string "With this METEORITE, that thing in\n"
	.string "MT. CHIMNEY will…$"

MeteorFalls_1F_1R_Text_DontExpectMercyFromMagma:
	.string "Heh?\p"
	.string "I don't know who you are, but if you get\n"
	.string "in the way of TEAM MAGMA, don't\l"
	.string "expect any mercy!$"

MeteorFalls_1F_1R_Text_HoldItRightThereMagma:
	.string "Hold it right there, TEAM MAGMA!\p"
	.string "You're badly mistaken if you think you\n"
	.string "can have your way with the world!$"


MeteorFalls_1F_1R_Text_BeSeeingYouTeamAqua:
        .string "MAGMA GRUNT: Whatever.\p"
        .string "We've got the METEORITE.\p"
        .string "We're going to MT. CHIMNEY.$"


MeteorFalls_1F_1R_Text_ArchieSeenYouBefore:
        .string "ARCHIE: ...\p"
        .string "You again. From SLATEPORT.\p"
        .string "You certainly have a habit of\n"
        .string "appearing at interesting times.$"


MeteorFalls_1F_1R_Text_BossWeShouldChaseMagma:
        .string "AQUA GRUNT: Boss!\p"
        .string "TEAM MAGMA is getting away!$"


MeteorFalls_1F_1R_Text_ArchieYesNoTellingWhatMagmaWillDo:
        .string "ARCHIE: I can see that.\p"
        .string "We're going after them.$"


MeteorFalls_1F_1R_Text_ArchieFarewell:
        .string "ARCHIE: {PLAYER}.\p"
        .string "They're headed for MT. CHIMNEY.\p"
        .string "Do what you will with that\n"
        .string "information.$"

MeteorFalls_1F_1R_Text_MeetProfCozmo:
	.string "I… I'm COZMO…\n"
	.string "I'm a PROFESSOR…\p"
	.string "TEAM MAGMA asked me to guide them\n"
	.string "to METEOR FALLS…\p"
	.string "But they tricked me.\n"
	.string "They even took my METEORITE away…\p"
	.string "And then another similar bunch,\n"
	.string "TEAM AQUA showed up.\p"
	.string "After that…\n"
	.string "I don't understand any of it.\p"
	.string "But that TEAM MAGMA…\p"
	.string "What are they going to do with that\n"
	.string "METEORITE at MT. CHIMNEY?$"

MeteorFalls_1F_1R_Text_WhatsTeamMagmaDoingAtMtChimney:
        .string "COZMO: Mt... Moon?\p"
        .string "I've never heard of such a place.\p"
        .string "And yet...\p"
        .string "He said it like he'd been there\n"
        .string "before.\p"
        .string "What exactly is beyond this cave?$"

MeteorFalls_1F_1R_Text_GiovanniEnough:
        .string "GIOVANNI: Enough.$"


MeteorFalls_1F_1R_Text_MagmaWhoAreYou:
        .string "MAGMA GRUNT: Who are you?$"

MeteorFalls_1F_1R_Text_GiovanniObserve:
        .string "GIOVANNI: Merely an observer.\p"
        .string "Though there has been remarkably\n"
        .string "little worth observing.\p"
        .string "You frightened a scientist, stole a\n"
        .string "stone, and alerted your opposition.$"

MeteorFalls_1F_1R_Text_ArchieExcuseMe:
        .string "ARCHIE: Excuse me?$"

MeteorFalls_1F_1R_Text_GiovanniBothOfYou:
        .string "GIOVANNI: I was speaking to both\n"
        .string "of you.$"


MeteorFalls_1F_1R_Text_GiovanniCozmo:
        .string "GIOVANNI: Professor.\p"
        .string "Your readings.\n"
        .string "Were they limited to this chamber?$"

MeteorFalls_1F_1R_Text_CozmoCavern:
        .string "COZMO: N-no.\p"
        .string "There's another cavern nearby.\p"
        .string "That's actually what's strange.\n"
        .string "It isn't in any of my records.$"

MeteorFalls_1F_1R_Text_GiovanniMtMoon:
        .string "GIOVANNI: ...\p"
        .string "Mt. Moon.$"

MeteorFalls_1F_1R_Text_CozmoMtMoon:
        .string "COZMO: Mt. Moon?\p"
        .string "I've never heard of such a place.$"

MeteorFalls_1F_1R_Text_GiovanniNotHere:
        .string "GIOVANNI: No.\p"
        .string "You wouldn't have.$"


MeteorFalls_1F_1R_Movement_CameraPanDown:
        walk_down
        walk_down
        walk_down
        walk_down
        walk_down
        step_end

MeteorFalls_1F_1R_Movement_CameraPanUp:
        walk_up
        walk_up
        walk_up
        walk_up
        walk_up
        step_end


MeteorFalls_1F_1R_Text_PlayerHowKnow:
        .string "{PLAYER}: How did you know what\n"
        .string "that cave was called?$"

MeteorFalls_1F_1R_Text_GiovanniBeenThere:
        .string "GIOVANNI: Because I've been there.\p"
        .string "Just not here.$"

MeteorFalls_1F_1R_Text_GiovanniCallAlakazam:
        .string "GIOVANNI: Alakazam.$"

MeteorFalls_1F_1R_Text_GiovanniTeleport:
        .string "GIOVANNI: Teleport.$"

@ ============================================================================
@ MT. MOON RETURN - COUNTERPART
@ ============================================================================

MeteorFalls_1F_1R_EventScript_MtMoonReturnCounterpart::
    goto_if_set FLAG_HIDE_METEOR_FALLS_COUNTERPART, MeteorFalls_1F_1R_EventScript_MtMoonReturnCounterpart_End
    goto_if_unset FLAG_HIDE_MT_MOON_TWIN, MeteorFalls_1F_1R_EventScript_MtMoonReturnCounterpart_End

    lockall

    applymovement LOCALID_PLAYER, Common_Movement_FaceRight
    applymovement LOCALID_METEOR_FALLS_COUNTERPART, Common_Movement_FaceLeft
    waitmovement 0

    msgbox MeteorFalls_1F_1R_Text_CounterpartThereYouAre, MSGBOX_DEFAULT
    msgbox MeteorFalls_1F_1R_Text_PlayerWhereWereYou, MSGBOX_DEFAULT
    msgbox MeteorFalls_1F_1R_Text_CounterpartAround, MSGBOX_DEFAULT
    msgbox MeteorFalls_1F_1R_Text_PlayerAroundWhere, MSGBOX_DEFAULT
    msgbox MeteorFalls_1F_1R_Text_CounterpartGramps, MSGBOX_DEFAULT
    msgbox MeteorFalls_1F_1R_Text_PlayerProfessorOak, MSGBOX_DEFAULT
    msgbox MeteorFalls_1F_1R_Text_CounterpartYes, MSGBOX_DEFAULT
    msgbox MeteorFalls_1F_1R_Text_PlayerEveryoneKnowsOak, MSGBOX_DEFAULT
    msgbox MeteorFalls_1F_1R_Text_CounterpartFriendlinessFamily, MSGBOX_DEFAULT
    msgbox MeteorFalls_1F_1R_Text_PlayerNotAnswer, MSGBOX_DEFAULT
    msgbox MeteorFalls_1F_1R_Text_CounterpartNotQuestion, MSGBOX_DEFAULT

    msgbox MeteorFalls_1F_1R_Text_CounterpartBook, MSGBOX_DEFAULT
    msgbox MeteorFalls_1F_1R_Text_PlayerYouReadIt, MSGBOX_DEFAULT
    msgbox MeteorFalls_1F_1R_Text_CounterpartYeah, MSGBOX_DEFAULT
    msgbox MeteorFalls_1F_1R_Text_PlayerAnd, MSGBOX_DEFAULT
    msgbox MeteorFalls_1F_1R_Text_CounterpartAnnihilape, MSGBOX_DEFAULT

    goto_if_set FLAG_HIDE_HOME_MOM, MeteorFalls_1F_1R_EventScript_CounterpartSawXie

MeteorFalls_1F_1R_EventScript_CounterpartSawSol:
    msgbox MeteorFalls_1F_1R_Text_CounterpartSawSol, MSGBOX_DEFAULT
    msgbox MeteorFalls_1F_1R_Text_PlayerYouKnowSol, MSGBOX_DEFAULT
    goto MeteorFalls_1F_1R_EventScript_CounterpartKnowsTwin

MeteorFalls_1F_1R_EventScript_CounterpartSawXie:
    msgbox MeteorFalls_1F_1R_Text_CounterpartSawXie, MSGBOX_DEFAULT
    msgbox MeteorFalls_1F_1R_Text_PlayerYouKnowXie, MSGBOX_DEFAULT

MeteorFalls_1F_1R_EventScript_CounterpartKnowsTwin:
    msgbox MeteorFalls_1F_1R_Text_CounterpartKnowTwin, MSGBOX_DEFAULT
    msgbox MeteorFalls_1F_1R_Text_PlayerHow, MSGBOX_DEFAULT
    msgbox MeteorFalls_1F_1R_Text_CounterpartFriendlinessAgain, MSGBOX_DEFAULT
    msgbox MeteorFalls_1F_1R_Text_PlayerStop, MSGBOX_DEFAULT

    msgbox MeteorFalls_1F_1R_Text_CounterpartMagma, MSGBOX_DEFAULT
    msgbox MeteorFalls_1F_1R_Text_PlayerRight, MSGBOX_DEFAULT
    msgbox MeteorFalls_1F_1R_Text_CounterpartDistracted, MSGBOX_DEFAULT
    msgbox MeteorFalls_1F_1R_Text_PlayerMountain, MSGBOX_DEFAULT
    msgbox MeteorFalls_1F_1R_Text_CounterpartCave, MSGBOX_DEFAULT
    msgbox MeteorFalls_1F_1R_Text_PlayerNotHelping, MSGBOX_DEFAULT

    applymovement LOCALID_METEOR_FALLS_COUNTERPART, MeteorFalls_1F_1R_Movement_CounterpartExit
    waitmovement 0

    setflag FLAG_HIDE_METEOR_FALLS_COUNTERPART
    removeobject LOCALID_METEOR_FALLS_COUNTERPART

    releaseall
    end

MeteorFalls_1F_1R_EventScript_MtMoonReturnCounterpart_End:
    end


MeteorFalls_1F_1R_EventScript_CounterpartTalk::
    lock
    faceplayer
    msgbox MeteorFalls_1F_1R_Text_CounterpartWaiting, MSGBOX_DEFAULT
    release
    end


MeteorFalls_1F_1R_Text_CounterpartThereYouAre:
    .string "{RIVAL}: There you are.$"

MeteorFalls_1F_1R_Text_PlayerWhereWereYou:
    .string "{PLAYER}: Where were you?$"

MeteorFalls_1F_1R_Text_CounterpartAround:
    .string "{RIVAL}: Around.$"

MeteorFalls_1F_1R_Text_PlayerAroundWhere:
    .string "{PLAYER}: Around where?$"

MeteorFalls_1F_1R_Text_CounterpartGramps:
    .string "{RIVAL}: Here. I talked to gramps.$"

MeteorFalls_1F_1R_Text_PlayerProfessorOak:
    .string "{PLAYER}: Professor Oak?$"

MeteorFalls_1F_1R_Text_CounterpartYes:
    .string "{RIVAL}: ...Yes?$"

MeteorFalls_1F_1R_Text_PlayerEveryoneKnowsOak:
    .string "{PLAYER}: Why does everyone know\n"
    .string "him?$"

MeteorFalls_1F_1R_Text_CounterpartFriendlinessFamily:
    .string "{RIVAL}: Friendliness runs in the\n"
    .string "family?$"

MeteorFalls_1F_1R_Text_PlayerNotAnswer:
    .string "{PLAYER}: That's not an answer.$"

MeteorFalls_1F_1R_Text_CounterpartNotQuestion:
    .string "{RIVAL}: Wasn't really a question.$"

MeteorFalls_1F_1R_Text_CounterpartBook:
    .string "{RIVAL}: I read a weird book too.$"

MeteorFalls_1F_1R_Text_PlayerYouReadIt:
    .string "{PLAYER}: You READ it?$"

MeteorFalls_1F_1R_Text_CounterpartYeah:
    .string "{RIVAL}: Yeah.$"

MeteorFalls_1F_1R_Text_PlayerAnd:
    .string "{PLAYER}: And?$"

MeteorFalls_1F_1R_Text_CounterpartAnnihilape:
    .string "{RIVAL}: Got an Annihilape.\p"
    .string "Pretty cool, right?$"

MeteorFalls_1F_1R_Text_CounterpartSawSol:
    .string "{RIVAL}: I saw Sol in there too.$"

MeteorFalls_1F_1R_Text_PlayerYouKnowSol:
    .string "{PLAYER}: You know Sol?!$"

MeteorFalls_1F_1R_Text_CounterpartSawXie:
    .string "{RIVAL}: I saw Xie in there too.$"

MeteorFalls_1F_1R_Text_PlayerYouKnowXie:
    .string "{PLAYER}: You know Xie?!$"

MeteorFalls_1F_1R_Text_CounterpartKnowTwin:
    .string "{RIVAL}: ...Yes?$"

MeteorFalls_1F_1R_Text_PlayerHow:
    .string "{PLAYER}: How?!$"

MeteorFalls_1F_1R_Text_CounterpartFriendlinessAgain:
    .string "{RIVAL}: Friendliness?$"

MeteorFalls_1F_1R_Text_PlayerStop:
    .string "{PLAYER}: Stop.$"

MeteorFalls_1F_1R_Text_CounterpartMagma:
    .string "{RIVAL}: Anyway...\p"
    .string "Weren't those Magma people\n"
    .string "headed for Mt. Chimney?$"

MeteorFalls_1F_1R_Text_PlayerRight:
    .string "{PLAYER}: ...Right.$"

MeteorFalls_1F_1R_Text_CounterpartDistracted:
    .string "{RIVAL}: You got distracted.$"

MeteorFalls_1F_1R_Text_PlayerMountain:
    .string "{PLAYER}: I found an entire\n"
    .string "mountain!$"

MeteorFalls_1F_1R_Text_CounterpartCave:
    .string "{RIVAL}: It's a cave.$"

MeteorFalls_1F_1R_Text_PlayerNotHelping:
    .string "{PLAYER}: Not helping.$"

MeteorFalls_1F_1R_Text_CounterpartWaiting:
    .string "{RIVAL}: You planning on going\n"
    .string "back in?$"



MeteorFalls_1F_1R_Movement_CounterpartExit:
    walk_down
    walk_left
    walk_left
    walk_left
    walk_left
    walk_left
    walk_left
    walk_down
    walk_left
    walk_left
    walk_left
    walk_left
    walk_left
    walk_left
    walk_left
    walk_left
    step_end


@ ============================================================================
@ MT. MOON SIGN
@ ============================================================================

MeteorFalls_1F_1R_EventScript_MtMoonSign::
    msgbox MeteorFalls_1F_1R_Text_MtMoonSign, MSGBOX_SIGN
    end

MeteorFalls_1F_1R_Text_MtMoonSign:
    .string "MT. MOON\p"
    .string "A mystical mountain where\n"
    .string "moonlight gathers.$"
