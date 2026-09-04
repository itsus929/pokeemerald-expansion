PewterCity_Frlg_MapScripts::
    map_script MAP_SCRIPT_ON_LOAD, PewterCity_Frlg_SetCounterpartGraphics
    map_script MAP_SCRIPT_ON_FRAME_TABLE, PewterCity_Frlg_OnFrame
    .byte 0

PewterCity_Frlg_OnFrame:
    map_script_2 VAR_BROCK_INGREDIENT_QUEST, 9, PewterCity_Frlg_EventScript_LoreleiButter
    .2byte 0

PewterCity_Frlg_SetCounterpartGraphics:
    goto_if_eq VAR_COUNTERPART_ID, COUNTERPART_BRENDAN, PewterCity_Frlg_SetBrendan
    goto_if_eq VAR_COUNTERPART_ID, COUNTERPART_MAY, PewterCity_Frlg_SetMay
    goto_if_eq VAR_COUNTERPART_ID, COUNTERPART_LEXY, PewterCity_Frlg_SetLexy
    goto_if_eq VAR_COUNTERPART_ID, COUNTERPART_JUSTIN, PewterCity_Frlg_SetJustin
    goto_if_eq VAR_COUNTERPART_ID, COUNTERPART_MAAM, PewterCity_Frlg_SetMaam
    goto_if_eq VAR_COUNTERPART_ID, COUNTERPART_SIR, PewterCity_Frlg_SetSir
    goto PewterCity_Frlg_FinishMapLoad

PewterCity_Frlg_SetBrendan:
    setvar VAR_OBJ_GFX_ID_0, OBJ_EVENT_GFX_BRENDAN_NORMAL
    goto PewterCity_Frlg_FinishMapLoad

PewterCity_Frlg_SetMay:
    setvar VAR_OBJ_GFX_ID_0, OBJ_EVENT_GFX_MAY_NORMAL
    goto PewterCity_Frlg_FinishMapLoad

PewterCity_Frlg_SetLexy:
    setvar VAR_OBJ_GFX_ID_0, OBJ_EVENT_GFX_LEXY_NORMAL
    goto PewterCity_Frlg_FinishMapLoad

PewterCity_Frlg_SetJustin:
    setvar VAR_OBJ_GFX_ID_0, OBJ_EVENT_GFX_JUSTIN_NORMAL
    goto PewterCity_Frlg_FinishMapLoad

PewterCity_Frlg_SetMaam:
    setvar VAR_OBJ_GFX_ID_0, OBJ_EVENT_GFX_MAAM_NORMAL
    goto PewterCity_Frlg_FinishMapLoad

PewterCity_Frlg_SetSir:
    setvar VAR_OBJ_GFX_ID_0, OBJ_EVENT_GFX_SIR_NORMAL
    goto PewterCity_Frlg_FinishMapLoad

PewterCity_Frlg_FinishMapLoad:
    compare VAR_BROCK_INGREDIENT_QUEST, 9
    goto_if_eq PewterCity_Frlg_LoadButterScene

    @ Lorelei and the return counterpart only exist for the state-9 finale.
    removeobject LOCALID_PEWTER_LORELEI
    removeobject LOCALID_PEWTER_RETURN_COUNTERPART
    end


PewterCity_Frlg_LoadButterScene:
    @ Make absolutely sure the two older counterpart copies are gone.
    setflag FLAG_HIDE_PEWTER_COUNTERPART
    setflag FLAG_HIDE_PEWTER_LANCE_COUNTERPART
    removeobject LOCALID_PEWTER_COUNTERPART
    removeobject LOCALID_PEWTER_LANCE_COUNTERPART

    @ Lorelei is already facing Lance.
    setobjectxyperm LOCALID_PEWTER_LORELEI, 34, 18
    setobjectmovementtype LOCALID_PEWTER_LORELEI, MOVEMENT_TYPE_FACE_UP

    @ Rival has received the less-accurate version of the old man's warp.
    setobjectxyperm LOCALID_PEWTER_RETURN_COUNTERPART, 35, 18
    setobjectmovementtype LOCALID_PEWTER_RETURN_COUNTERPART, MOVEMENT_TYPE_FACE_LEFT
    end


@ ============================================================================
@ PHYSICAL COUNTERPART - PEWTER ARRIVAL
@ ============================================================================

PewterCity_Frlg_EventScript_CounterpartArrival::
    goto_if_set FLAG_HIDE_PEWTER_COUNTERPART, PewterCity_Frlg_EventScript_CounterpartArrival_End

    lockall

    applymovement LOCALID_PLAYER, PewterCity_Frlg_Movement_PlayerFaceCounterpart
    applymovement LOCALID_PEWTER_COUNTERPART, PewterCity_Frlg_Movement_CounterpartFacePlayer
    waitmovement 0

    msgbox PewterCity_Frlg_Text_CounterpartArrival1, MSGBOX_DEFAULT
    msgbox PewterCity_Frlg_Text_CounterpartArrival2, MSGBOX_DEFAULT

    applymovement LOCALID_PEWTER_COUNTERPART, PewterCity_Frlg_Movement_CounterpartLeaves
    waitmovement LOCALID_PEWTER_COUNTERPART

    setflag FLAG_HIDE_PEWTER_COUNTERPART
    removeobject LOCALID_PEWTER_COUNTERPART

    @ Rival has gone ahead to investigate near Lance.
    clearflag FLAG_HIDE_PEWTER_LANCE_COUNTERPART

    releaseall

PewterCity_Frlg_EventScript_CounterpartArrival_End:
    end


PewterCity_Frlg_EventScript_Counterpart::
    lock
    faceplayer
    msgbox PewterCity_Frlg_Text_CounterpartBeforeArrival, MSGBOX_DEFAULT
    release
    end


PewterCity_Frlg_Movement_PlayerFaceCounterpart:
    face_right
    step_end


PewterCity_Frlg_Movement_CounterpartFacePlayer:
    face_left
    step_end


PewterCity_Frlg_Movement_CounterpartLeaves:
    walk_left
    walk_left
    walk_left
    walk_left
    walk_left
    walk_left
    walk_left
    walk_left
    walk_left
    walk_left
    walk_left
    step_end


PewterCity_Frlg_Text_CounterpartArrival1:
    .string "{PLAYER}: HOW are you already here?\p"
    .string "{RIVAL}: What?\p"
    .string "{PLAYER}: You did this in CERULEAN too.\p"
    .string "{RIVAL}: Did what?\p"
    .string "{PLAYER}: GET THERE BEFORE ME.\p"
    .string "{RIVAL}: Maybe you're slow.\p"
    .string "{PLAYER}: I WARPED HERE.\p"
    .string "LIKE I HAVE SUPERPOWERS.\p"
    .string "I WALKED THROUGH A DOOR AND--\p"
    .string "HOW DID YOU GET HERE FIRST?!\p"
    .string "{RIVAL}: I left before you.\p"
    .string "{PLAYER}: YOU WERE EATING PANCAKES.\p"
    .string "{RIVAL}: I eat fast.\p"
    .string "{PLAYER}: THAT DOESN'T EXPLAIN\n"
    .string "ANYTHING.\p"
    .string "{RIVAL}: Anyway.\p"
    .string "We'll cover more ground if we\n"
    .string "split up.$"


PewterCity_Frlg_Text_CounterpartArrival2:
    .string "{RIVAL}: Ask around.\p"
    .string "I'll do the same.\p"
    .string "We'll meet where it matters.$"


PewterCity_Frlg_Text_CounterpartBeforeArrival:
    .string "{RIVAL}: We should probably\n"
    .string "start asking around.$"


@ ============================================================================
@ LANCE-STAGE RIVAL
@ ============================================================================

PewterCity_Frlg_EventScript_LanceCounterpart::
    lock
    faceplayer

    compare VAR_BROCK_INGREDIENT_QUEST, 1
    goto_if_eq PewterCity_Frlg_EventScript_LanceCounterpartBeforeLance

    compare VAR_BROCK_INGREDIENT_QUEST, 2
    goto_if_eq PewterCity_Frlg_EventScript_LanceCounterpartAfterLance

    msgbox PewterCity_Frlg_Text_LanceCounterpartFallback, MSGBOX_DEFAULT
    release
    end


PewterCity_Frlg_EventScript_LanceCounterpartBeforeLance:
    msgbox PewterCity_Frlg_Text_LanceCounterpartBeforeLance, MSGBOX_DEFAULT
    release
    end


PewterCity_Frlg_EventScript_LanceCounterpartAfterLance:
    msgbox PewterCity_Frlg_Text_LanceCounterpartCapeTheory, MSGBOX_DEFAULT

    applymovement LOCALID_PEWTER_LANCE_COUNTERPART, PewterCity_Frlg_Movement_LanceCounterpartLeaves
    waitmovement LOCALID_PEWTER_LANCE_COUNTERPART

    setflag FLAG_HIDE_PEWTER_LANCE_COUNTERPART
    removeobject LOCALID_PEWTER_LANCE_COUNTERPART

    @ Rival's next physical copy is waiting at Savvy's.
    clearflag FLAG_HIDE_PEWTER_SAVVY_COUNTERPART

    release
    end


PewterCity_Frlg_Text_LanceCounterpartBeforeLance:
    .string "{RIVAL}: You talk to him.\p"
    .string "I'll stay here and listen.$"


PewterCity_Frlg_Text_LanceCounterpartFallback:
    .string "{RIVAL}: We should keep moving.$"


@ BROCK'S MYSTERY INGREDIENT SEARCH - PEWTER
@
@ STATE 0 = quest not started
@ STATE 1 = Brock sent player to Pewter
@ STATE 2 = Lance directed player to Savvy
@ STATE 3 = Savvy gave the Cerulean lead
@ ============================================================================


@ ============================================================================
@ LASS
@ ============================================================================

PewterCity_Frlg_EventScript_IngredientLass::
    lock
    faceplayer

    compare VAR_BROCK_INGREDIENT_QUEST, 1
    goto_if_eq PewterCity_Frlg_EventScript_LassSearching

    compare VAR_BROCK_INGREDIENT_QUEST, 2
    goto_if_eq PewterCity_Frlg_EventScript_LassSavvy

    compare VAR_BROCK_INGREDIENT_QUEST, 3
    goto_if_eq PewterCity_Frlg_EventScript_LassAfterSavvy

    msgbox PewterCity_Frlg_Text_LassNormal, MSGBOX_DEFAULT
    release
    end

PewterCity_Frlg_EventScript_LassSearching:
    msgbox PewterCity_Frlg_Text_LassSearching, MSGBOX_DEFAULT
    release
    end

PewterCity_Frlg_EventScript_LassSavvy:
    msgbox PewterCity_Frlg_Text_LassSavvy, MSGBOX_DEFAULT
    release
    end

PewterCity_Frlg_EventScript_LassAfterSavvy:
    msgbox PewterCity_Frlg_Text_LassAfterSavvy, MSGBOX_DEFAULT
    release
    end


@ ============================================================================
@ FAT MAN
@ ============================================================================

PewterCity_Frlg_EventScript_IngredientFatMan::
    lock
    faceplayer

    compare VAR_BROCK_INGREDIENT_QUEST, 1
    goto_if_eq PewterCity_Frlg_EventScript_FatManSearching

    compare VAR_BROCK_INGREDIENT_QUEST, 2
    goto_if_eq PewterCity_Frlg_EventScript_FatManSavvy

    compare VAR_BROCK_INGREDIENT_QUEST, 3
    goto_if_eq PewterCity_Frlg_EventScript_FatManAfterSavvy

    msgbox PewterCity_Frlg_Text_FatManNormal, MSGBOX_DEFAULT
    release
    end

PewterCity_Frlg_EventScript_FatManSearching:
    msgbox PewterCity_Frlg_Text_FatManSearching, MSGBOX_DEFAULT
    release
    end

PewterCity_Frlg_EventScript_FatManSavvy:
    msgbox PewterCity_Frlg_Text_FatManSavvy, MSGBOX_DEFAULT
    release
    end

PewterCity_Frlg_EventScript_FatManAfterSavvy:
    msgbox PewterCity_Frlg_Text_FatManAfterSavvy, MSGBOX_DEFAULT
    release
    end


@ ============================================================================
@ BUG CATCHER
@ ============================================================================

PewterCity_Frlg_EventScript_IngredientBugCatcher::
    lock
    faceplayer

    compare VAR_BROCK_INGREDIENT_QUEST, 1
    goto_if_eq PewterCity_Frlg_EventScript_BugCatcherSearching

    compare VAR_BROCK_INGREDIENT_QUEST, 2
    goto_if_eq PewterCity_Frlg_EventScript_BugCatcherSavvy

    compare VAR_BROCK_INGREDIENT_QUEST, 3
    goto_if_eq PewterCity_Frlg_EventScript_BugCatcherAfterSavvy

    msgbox PewterCity_Frlg_Text_BugCatcherNormal, MSGBOX_DEFAULT
    release
    end

PewterCity_Frlg_EventScript_BugCatcherSearching:
    msgbox PewterCity_Frlg_Text_BugCatcherSearching, MSGBOX_DEFAULT
    release
    end

PewterCity_Frlg_EventScript_BugCatcherSavvy:
    msgbox PewterCity_Frlg_Text_BugCatcherSavvy, MSGBOX_DEFAULT
    release
    end

PewterCity_Frlg_EventScript_BugCatcherAfterSavvy:
    msgbox PewterCity_Frlg_Text_BugCatcherAfterSavvy, MSGBOX_DEFAULT
    release
    end


@ ============================================================================
@ LANCE
@ ============================================================================

PewterCity_Frlg_EventScript_Lance::
    lock
    faceplayer
    call PewterCity_Frlg_EventScript_DragoniteFacePlayer

    compare VAR_BROCK_INGREDIENT_QUEST, 1
    goto_if_eq PewterCity_Frlg_EventScript_LanceQuest

    compare VAR_BROCK_INGREDIENT_QUEST, 2
    goto_if_eq PewterCity_Frlg_EventScript_LanceWaitingOnSavvy

    compare VAR_BROCK_INGREDIENT_QUEST, 3
    goto_if_eq PewterCity_Frlg_EventScript_LanceAfterSavvy

    msgbox PewterCity_Frlg_Text_LanceNormal, MSGBOX_DEFAULT
    release
    end


PewterCity_Frlg_EventScript_LanceQuest:
    msgbox PewterCity_Frlg_Text_LanceQuestStart, MSGBOX_DEFAULT
    msgbox PewterCity_Frlg_Text_LanceSavvyLead, MSGBOX_DEFAULT

    @ Lance gave us the next lead.
    @ Rival stays nearby until the player talks to them.
    setvar VAR_BROCK_INGREDIENT_QUEST, 2

    release
    end


PewterCity_Frlg_EventScript_LanceWaitingOnSavvy:
    msgbox PewterCity_Frlg_Text_LanceWaitingOnSavvy, MSGBOX_DEFAULT
    release
    end


PewterCity_Frlg_EventScript_LanceAfterSavvy:
    msgbox PewterCity_Frlg_Text_LanceAfterSavvy, MSGBOX_DEFAULT
    closemessage

    delay 15

    waitse
    playmoncry SPECIES_DRAGONITE, CRY_MODE_NORMAL
    waitmoncry
    delay 20

    warp MAP_CERULEAN_CITY, 33, 16
    waitstate
    end


@ ============================================================================
@ LANCE RIVAL EXIT CHOREOGRAPHY
@ ============================================================================

PewterCity_Frlg_Movement_LanceCounterpartFacePlayer:
    face_left
    step_end

PewterCity_Frlg_Movement_LanceCounterpartLeaves:
    face_left
    walk_left
    walk_left
    walk_down
    walk_down
    walk_down
    walk_down
    step_end


@ ============================================================================
@ TEXT
@ ============================================================================

PewterCity_Frlg_Text_LanceCounterpartCapeTheory:
    .string "{RIVAL}: I KNEW he'd know something!\p"
    .string "{PLAYER}: How?\p"
    .string "{RIVAL}: It was the cape.\p"
    .string "{PLAYER}: The cape?\p"
    .string "{RIVAL}: Guys with capes always\n"
    .string "know stuff.\p"
    .string "{PLAYER}: That's not--\p"
    .string "{RIVAL}: Byeeeee.$"


PewterCity_Frlg_Text_LassNormal:
    .string "PEWTER is quieter than it looks.\p"
    .string "Usually.$"

PewterCity_Frlg_Text_LassSearching:
    .string "An ingredient?\p"
    .string "That's... not very specific.\p"
    .string "Maybe ask around?$"

PewterCity_Frlg_Text_LassSavvy:
    .string "Oh! LANCE sent you to SAVVY?\p"
    .string "Then you're done asking us.\p"
    .string "If anybody in PEWTER knows,\n"
    .string "it's her.$"

PewterCity_Frlg_Text_LassAfterSavvy:
    .string "SAVVY knew, didn't she?\p"
    .string "She always knows.$"


PewterCity_Frlg_Text_FatManNormal:
    .string "Nothing beats a good meal.$"

PewterCity_Frlg_Text_FatManSearching:
    .string "You're looking for an ingredient?\p"
    .string "You came to the right man.\p"
    .string "{PLAYER}: Do you know where it is?\p"
    .string "...No.$"

PewterCity_Frlg_Text_FatManSavvy:
    .string "SAVVY?\p"
    .string "Yeah. She'd know.\p"
    .string "She knows things she has no\n"
    .string "business knowing.$"

PewterCity_Frlg_Text_FatManAfterSavvy:
    .string "So SAVVY had your answer?\p"
    .string "Of course she did.$"


PewterCity_Frlg_Text_BugCatcherNormal:
    .string "There are interesting people\n"
    .string "everywhere if you pay attention.$"

PewterCity_Frlg_Text_BugCatcherSearching:
    .string "An ingredient?\p"
    .string "Sorry. Haven't heard anything.$"

PewterCity_Frlg_Text_BugCatcherSavvy:
    .string "You're looking for SAVVY?\p"
    .string "South side of town.\p"
    .string "You'll know when you've found her.$"

PewterCity_Frlg_Text_BugCatcherAfterSavvy:
    .string "You're leaving already?\p"
    .string "Guess you found what you needed.$"


PewterCity_Frlg_Text_LanceNormal:
    .string "LANCE: PEWTER has a way of making\n"
    .string "people slow down.\p"
    .string "Usually that's a good thing.$"

PewterCity_Frlg_Text_LanceQuestStart:
    .string "LANCE: You aren't sightseeing.\p"
    .string "{PLAYER}: Brock sent me.\p"
    .string "We're looking for an ingredient.\p"
    .string "LANCE: An ingredient?\p"
    .string "And he sent you to PEWTER?\p"
    .string "{PLAYER}: That's literally all\n"
    .string "he gave me.$"


PewterCity_Frlg_Text_LanceSavvyLead:
    .string "LANCE: Then don't waste your time\n"
    .string "asking everyone in town.\p"
    .string "Find SAVVY.\p"
    .string "{PLAYER}: Savvy?\p"
    .string "LANCE: South side of PEWTER.\p"
    .string "If something happened here,\n"
    .string "she knows about it.$"


PewterCity_Frlg_Text_LanceWaitingOnSavvy:
    .string "LANCE: Find SAVVY.\p"
    .string "South side of town.\p"
    .string "Trust me.$"

PewterCity_Frlg_Text_LanceAfterSavvy:
    .string "LANCE: CERULEAN?\p"
    .string "Then whoever you're chasing\n"
    .string "didn't stay in PEWTER long.\p"
    .string "{PLAYER}: Guess I'm headed back.\p"
    .string "LANCE: DRAGONITE can take you.\p"
    .string "{PLAYER}: Wait, wha--$"


@ ============================================================================
@ EAST PEWTER NPCs
@ ============================================================================

PewterCity_Frlg_EventScript_EastBoy::
    lock
    faceplayer
    msgbox PewterCity_Frlg_Text_EastBoy, MSGBOX_DEFAULT
    release
    end

PewterCity_Frlg_EventScript_EastScientist::
    lock
    faceplayer
    msgbox PewterCity_Frlg_Text_EastScientist, MSGBOX_DEFAULT
    release
    end


PewterCity_Frlg_Text_EastBoy:
    .string "He keeps staring at rocks.\p"
    .string "Like... for HOURS.\p"
    .string "I asked what he was looking for.\p"
    .string "He said, 'context.'$"


PewterCity_Frlg_Text_EastScientist:
    .string "People think museums preserve\n"
    .string "answers.\p"
    .string "They don't.\p"
    .string "They preserve evidence.\p"
    .string "Answers change when we learn\n"
    .string "how to read it.$"


@ ============================================================================
@ Dragonite reacts when Player talks to Lance
@ ============================================================================

PewterCity_Frlg_EventScript_DragoniteFacePlayer:
    getplayerxy VAR_TEMP_0, VAR_TEMP_1

    @ Player is LEFT of Lance at (33,17).
    goto_if_eq VAR_TEMP_0, 33, PewterCity_Frlg_EventScript_DragoniteFaceWest

    @ Player is directly ABOVE Lance at (34,16).
    goto_if_eq VAR_TEMP_1, 16, PewterCity_Frlg_EventScript_DragoniteFaceNorth

    @ Normal interaction: Player is BELOW Lance at (34,18).
    goto PewterCity_Frlg_EventScript_DragoniteFaceSouth


PewterCity_Frlg_EventScript_DragoniteFaceSouth:
    applymovement LOCALID_PEWTER_DRAGONITE, PewterCity_Frlg_Movement_DragoniteFaceSouth
    waitmovement LOCALID_PEWTER_DRAGONITE
    return

PewterCity_Frlg_EventScript_DragoniteFaceNorth:
    applymovement LOCALID_PEWTER_DRAGONITE, PewterCity_Frlg_Movement_DragoniteFaceNorth
    waitmovement LOCALID_PEWTER_DRAGONITE
    return

PewterCity_Frlg_EventScript_DragoniteFaceWest:
    applymovement LOCALID_PEWTER_DRAGONITE, PewterCity_Frlg_Movement_DragoniteFaceWest
    waitmovement LOCALID_PEWTER_DRAGONITE
    return

PewterCity_Frlg_EventScript_DragoniteFaceEast:
    applymovement LOCALID_PEWTER_DRAGONITE, PewterCity_Frlg_Movement_DragoniteFaceEast
    waitmovement LOCALID_PEWTER_DRAGONITE
    return

PewterCity_Frlg_Movement_DragoniteFaceSouth:
    face_down
    step_end

PewterCity_Frlg_Movement_DragoniteFaceNorth:
    face_up
    step_end

PewterCity_Frlg_Movement_DragoniteFaceWest:
    face_left
    step_end

PewterCity_Frlg_Movement_DragoniteFaceEast:
    face_right
    step_end



@ ============================================================================
@ FUCHSIA RETURN / LORELEI'S SUSPICIOUS BUTTER OPERATION
@
@ STATE 9  = returned from Fuchsia, need Lorelei's butter
@ STATE 10 = Lorelei gave Brock's butter
@ ============================================================================


PewterCity_Frlg_EventScript_FuchsiaReturnArrival::
    lockall

    delay 20

    @ Player realizes the old man had... mixed accuracy.
    applymovement LOCALID_PLAYER, PewterCity_Frlg_Movement_ReturnPlayerLooksAtRival
    applymovement LOCALID_PEWTER_RETURN_COUNTERPART, PewterCity_Frlg_Movement_ReturnRivalLooksAtPlayer
    waitmovement 0

    msgbox PewterCity_Frlg_Text_ReturnFlowers, MSGBOX_DEFAULT

    releaseall
    end


PewterCity_Frlg_EventScript_ReturnCounterpart::
    lock
    faceplayer

    compare VAR_BROCK_INGREDIENT_QUEST, 9
    goto_if_eq PewterCity_Frlg_EventScript_ReturnCounterpart_State9

    msgbox PewterCity_Frlg_Text_ReturnCounterpartFallback, MSGBOX_DEFAULT
    release
    end


PewterCity_Frlg_EventScript_ReturnCounterpart_State9:
    msgbox PewterCity_Frlg_Text_ReturnCounterpartState9, MSGBOX_DEFAULT
    release
    end


@ ============================================================================
@ TALKING TO LORELEI STARTS THE BUTTER HANDOFF
@ ============================================================================

PewterCity_Frlg_EventScript_LoreleiButter::
    lockall

    compare VAR_BROCK_INGREDIENT_QUEST, 9
    goto_if_eq PewterCity_Frlg_EventScript_LoreleiButter_FirstTime

    compare VAR_BROCK_INGREDIENT_QUEST, 10
    goto_if_eq PewterCity_Frlg_EventScript_LoreleiButter_RideAgain

    goto PewterCity_Frlg_EventScript_LoreleiButter_NotReady


PewterCity_Frlg_EventScript_LoreleiButter_FirstTime:

    @ Let the player land facing the screen while they witness the deal.
    applymovement LOCALID_PLAYER, PewterCity_Frlg_Movement_PlayerFacesScreen
    waitmovement LOCALID_PLAYER

    @ Lorelei and Lance begin facing one another.
    @ Player is directly below Lorelei and counterpart is beside her.
    msgbox PewterCity_Frlg_Text_ButterDeal1, MSGBOX_DEFAULT
    msgbox PewterCity_Frlg_Text_ButterDeal2, MSGBOX_DEFAULT

    @ Player finally interrupts.
    applymovement LOCALID_PLAYER, PewterCity_Frlg_Movement_PlayerFacesLorelei
    applymovement LOCALID_PEWTER_LORELEI, PewterCity_Frlg_Movement_LoreleiFacesPlayer
    applymovement LOCALID_PEWTER_LANCE, PewterCity_Frlg_Movement_LanceFacesPlayer
    applymovement LOCALID_PEWTER_RETURN_COUNTERPART, PewterCity_Frlg_Movement_CounterpartFacesPlayer
    waitmovement 0

    msgbox PewterCity_Frlg_Text_ButterPlayerInterrupts, MSGBOX_DEFAULT
    msgbox PewterCity_Frlg_Text_ButterBrockReveal, MSGBOX_DEFAULT

    @ Narrative handoff only.
    setvar VAR_BROCK_INGREDIENT_QUEST, 10

    msgbox PewterCity_Frlg_Text_ButterReceivedPlayer, MSGBOX_DEFAULT

    @ Lance realizes which batch the player received.
    @ Lorelei turns back toward him for their argument.
    applymovement LOCALID_PEWTER_LORELEI, PewterCity_Frlg_Movement_LoreleiFacesLance
    waitmovement LOCALID_PEWTER_LORELEI

    msgbox PewterCity_Frlg_Text_ButterFreshArgument, MSGBOX_DEFAULT

    @ Lorelei returns her attention to the player.
    applymovement LOCALID_PEWTER_LORELEI, PewterCity_Frlg_Movement_LoreleiFacesPlayer
    waitmovement LOCALID_PEWTER_LORELEI

    msgbox PewterCity_Frlg_Text_LoreleiOffersRide, MSGBOX_YESNO

    goto_if_eq VAR_RESULT, NO, PewterCity_Frlg_EventScript_LoreleiButter_Stay

    @ Counterpart addresses Lorelei directly.
    applymovement LOCALID_PEWTER_LORELEI, PewterCity_Frlg_Movement_LoreleiFacesCounterpart
    applymovement LOCALID_PEWTER_RETURN_COUNTERPART, PewterCity_Frlg_Movement_CounterpartFacesLorelei
    waitmovement 0

    msgbox PewterCity_Frlg_Text_LoreleiWarp, MSGBOX_DEFAULT

    @ Hide the map transition before state 9 objects disappear.
    fadescreen FADE_TO_BLACK

    @ Hard Rock Cafe warp 1 is the Pewter-facing entrance at (9,2).
    warp MAP_HARD_ROCK_CAFE, 9, 3
    waitstate
    end


PewterCity_Frlg_EventScript_LoreleiButter_Stay:
    msgbox PewterCity_Frlg_Text_LoreleiStay, MSGBOX_DEFAULT
    releaseall
    end


PewterCity_Frlg_EventScript_LoreleiButter_RideAgain:
    msgbox PewterCity_Frlg_Text_LoreleiRideAgain, MSGBOX_YESNO
    goto_if_eq VAR_RESULT, NO, PewterCity_Frlg_EventScript_LoreleiButter_Stay

    msgbox PewterCity_Frlg_Text_LoreleiWarp, MSGBOX_DEFAULT
    fadescreen FADE_TO_BLACK
    warp MAP_HARD_ROCK_CAFE, 9, 3
    waitstate
    end


PewterCity_Frlg_EventScript_LoreleiButter_NotReady:
    msgbox PewterCity_Frlg_Text_LoreleiFallback, MSGBOX_DEFAULT
    releaseall
    end


@ ============================================================================
@ MOVEMENTS
@ ============================================================================

PewterCity_Frlg_Movement_ReturnPlayerLooksAtRival:
    face_left
    step_end


PewterCity_Frlg_Movement_ReturnRivalLooksAtPlayer:
    face_right
    step_end


PewterCity_Frlg_Movement_PlayerFacesScreen:
    face_down
    step_end

PewterCity_Frlg_Movement_PlayerFacesLorelei:
    face_up
    step_end

PewterCity_Frlg_Movement_LoreleiFacesPlayer:
    face_down
    step_end

PewterCity_Frlg_Movement_LoreleiFacesLance:
    face_up
    step_end


PewterCity_Frlg_Movement_LanceFacesPlayer:
    face_down
    step_end


PewterCity_Frlg_Movement_CounterpartFacesPlayer:
    face_down
    step_end

PewterCity_Frlg_Movement_LoreleiFacesCounterpart:
    face_right
    step_end

PewterCity_Frlg_Movement_CounterpartFacesLorelei:
    face_left
    step_end


@ ============================================================================
@ TEXT - FLOWER LANDING
@ ============================================================================

PewterCity_Frlg_Text_ReturnFlowers:
    .string "{RIVAL}: ...Flowers.\p"
    .string "{PLAYER}: You okay?\p"
    .string "{RIVAL}: He put YOU on the road.\p"
    .string "{PLAYER}: ...\p"
    .string "{RIVAL}: He put ME in the flowers.\p"
    .string "{PLAYER}: Wow.\p"
    .string "Flowers?\p"
    .string "Okay, I guess, old guy.$"


PewterCity_Frlg_Text_ReturnCounterpartState9:
    .string "{RIVAL}: I'm fine.\p"
    .string "The flowers broke my fall.\p"
    .string "...I think.$"


PewterCity_Frlg_Text_ReturnCounterpartFallback:
    .string "{RIVAL}: We should probably\n"
    .string "keep moving.$"


@ ============================================================================
@ TEXT - THE BUTTER DEAL
@ ============================================================================

PewterCity_Frlg_Text_ButterDeal1:
    .string "LORELEI: Same as usual?\p"
    .string "LANCE: Two.\p"
    .string "LORELEI: Two?\p"
    .string "LANCE: Dragonite likes it.\p"
    .string "LORELEI: Lance.\p"
    .string "LANCE: ...They're both mine.$"


PewterCity_Frlg_Text_ButterDeal2:
    .string "LORELEI: I only made a few\n"
    .string "batches this week.\p"
    .string "LANCE: I know.\p"
    .string "LORELEI: That's why everyone\n"
    .string "keeps asking me for it.$"


PewterCity_Frlg_Text_ButterPlayerInterrupts:
    .string "{PLAYER}: ...Is that butter?\p"
    .string "LANCE: Yes.\p"
    .string "{PLAYER}: Why did that feel\n"
    .string "illegal?\p"
    .string "LANCE: I don't know what you\n"
    .string "mean.$"


PewterCity_Frlg_Text_ButterBrockReveal:
    .string "LORELEI: Wait.\p"
    .string "You're the two Brock sent,\n"
    .string "aren't you?\p"
    .string "{PLAYER}: Apparently.\p"
    .string "LORELEI: He sent you all this\n"
    .string "way for MY butter?\p"
    .string "{PLAYER}: ...Yes.\p"
    .string "LORELEI: He could've just asked.$"


PewterCity_Frlg_Text_ButterReceivedPlayer:
    .string "LORELEI: Here.\p"
    .string "This batch is fresh.\p"
    .string "Take it to Brock.$"

PewterCity_Frlg_Text_ButterFreshArgument:
    .string "LANCE: Wait.\p"
    .string "THAT one's fresh?\p"
    .string "LORELEI: Yours is fine.\p"
    .string "LANCE: Lorelei.\p"
    .string "LORELEI: It's fine.$"


PewterCity_Frlg_Text_LoreleiOffersRide:
    .string "LORELEI: You're heading back\n"
    .string "to Brock now, right?\p"
    .string "I can save you the walk.\p"
    .string "Want a ride?$"


PewterCity_Frlg_Text_LoreleiWarp:
    .string "{RIVAL}: Please don't say you\n"
    .string "know an old man.\p"
    .string "LORELEI: ...What?\p"
    .string "{RIVAL}: Never mind.\p"
    .string "LORELEI: Hold still.$"


PewterCity_Frlg_Text_LoreleiStay:
    .string "LORELEI: Fine.\p"
    .string "Just don't let that butter\n"
    .string "sit out too long.$"


PewterCity_Frlg_Text_LoreleiFallback:
    .string "LORELEI: Brock better appreciate\n"
    .string "that batch.$"


@ ============================================================================
@ PEWTER CITY SIGNS
@ ============================================================================

PewterCity_EventScript_MuseumSign::
    msgbox PewterCity_Text_MuseumSign, MSGBOX_SIGN
    end


PewterCity_EventScript_PoliceNotice::
    msgbox PewterCity_Text_PoliceNotice, MSGBOX_SIGN
    end


PewterCity_EventScript_GymSign::
    msgbox PewterCity_Text_ShrineSign, MSGBOX_SIGN
    end


PewterCity_EventScript_TrainerTips::
    msgbox PewterCity_Text_TrainerTips, MSGBOX_SIGN
    end


PewterCity_EventScript_CitySign::
    msgbox PewterCity_Text_CitySign, MSGBOX_SIGN
    end


PewterCity_Text_MuseumSign:
    .string "PEWTER MUSEUM OF SCIENCE$"


PewterCity_Text_PoliceNotice:
    .string "NOTICE\p"
    .string "Please respect PEWTER's\n"
    .string "historic sites and monuments.$"


PewterCity_Text_ShrineSign:
    .string "PEWTER SHRINE\p"
    .string "KEEPER: BROCK$"


PewterCity_Text_TrainerTips:
    .string "TRAINER TIPS\p"
    .string "Different POKéMON thrive in\n"
    .string "different situations.\p"
    .string "Build a team you can trust.$"


PewterCity_Text_CitySign:
    .string "PEWTER CITY\p"
    .string "A quiet city built among\n"
    .string "stone.$"


PewterCity_Frlg_Text_LoreleiRideAgain:
    .string "LORELEI: Change your mind?\p"
    .string "I can still get you back to\n"
    .string "Brock if you want.$"
