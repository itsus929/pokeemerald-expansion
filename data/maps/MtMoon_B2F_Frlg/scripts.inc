MtMoon_B2F_Frlg_MapScripts::
    map_script MAP_SCRIPT_ON_LOAD, MtMoon_B2F_Frlg_SetTwinGraphics
    .byte 0


MtMoon_B2F_Frlg_SetTwinGraphics:
    @ Dad-raised path -> Xie.
    @ Mom-raised path -> Sol.
    goto_if_set FLAG_HIDE_HOME_MOM, MtMoon_B2F_Frlg_SetXieGraphics

    setvar VAR_OBJ_GFX_ID_1, OBJ_EVENT_GFX_SOL
    return


MtMoon_B2F_Frlg_SetXieGraphics:
    setvar VAR_OBJ_GFX_ID_1, OBJ_EVENT_GFX_XIE
    return


MtMoon_B2F_Frlg_EventScript_BeliefBook::
    lock
    faceplayer

    goto_if_set FLAG_MT_MOON_BELIEF_BOOK_USED, MtMoon_B2F_Frlg_EventScript_BeliefBookAfter

    msgbox MtMoon_B2F_Frlg_Text_BeliefBookOpening, MSGBOX_DEFAULT

    dynmultichoice 0, 0, FALSE, 3, 0, DYN_MULTICHOICE_CB_NONE, MtMoon_B2F_Frlg_Text_ChoiceSee, MtMoon_B2F_Frlg_Text_ChoiceFeel, MtMoon_B2F_Frlg_Text_ChoiceRemember, MtMoon_B2F_Frlg_Text_ChoiceUnderstand

    goto_if_eq VAR_RESULT, MULTI_B_PRESSED, MtMoon_B2F_Frlg_EventScript_BeliefBookCancel
    goto_if_eq VAR_RESULT, 0, MtMoon_B2F_Frlg_EventScript_GiveMimikyu
    goto_if_eq VAR_RESULT, 1, MtMoon_B2F_Frlg_EventScript_GiveAnnihilape
    goto_if_eq VAR_RESULT, 2, MtMoon_B2F_Frlg_EventScript_GiveTypeNull
    goto_if_eq VAR_RESULT, 3, MtMoon_B2F_Frlg_EventScript_GiveZoroark

    goto MtMoon_B2F_Frlg_EventScript_BeliefBookCancel


MtMoon_B2F_Frlg_EventScript_GiveMimikyu:
    setvar VAR_0x8005, 0
    msgbox MtMoon_B2F_Frlg_Text_ThenBelieveIt, MSGBOX_DEFAULT
    givemon SPECIES_MIMIKYU, 30, , , , , , , , , , , , , , , , , , , , , , SHINY_MODE_ALWAYS
    goto MtMoon_B2F_Frlg_EventScript_CheckGift


MtMoon_B2F_Frlg_EventScript_GiveAnnihilape:
    setvar VAR_0x8005, 1
    msgbox MtMoon_B2F_Frlg_Text_ThenBelieveIt, MSGBOX_DEFAULT
    givemon SPECIES_ANNIHILAPE, 30, , , , , , , , , , , , , , , , , , , , , , SHINY_MODE_ALWAYS
    goto MtMoon_B2F_Frlg_EventScript_CheckGift


MtMoon_B2F_Frlg_EventScript_GiveTypeNull:
    setvar VAR_0x8005, 2
    msgbox MtMoon_B2F_Frlg_Text_ThenBelieveIt, MSGBOX_DEFAULT
    givemon SPECIES_TYPE_NULL, 30, , , , , , , , , , , , , , , , , , , , , , SHINY_MODE_ALWAYS
    goto MtMoon_B2F_Frlg_EventScript_CheckGift


MtMoon_B2F_Frlg_EventScript_GiveZoroark:
    setvar VAR_0x8005, 3
    msgbox MtMoon_B2F_Frlg_Text_ThenBelieveIt, MSGBOX_DEFAULT
    givemon SPECIES_ZOROARK_HISUI, 30, , , , , , , , , , , , , , , , , , , , , , SHINY_MODE_ALWAYS
    goto MtMoon_B2F_Frlg_EventScript_CheckGift


MtMoon_B2F_Frlg_EventScript_CheckGift:
    goto_if_eq VAR_RESULT, MON_GIVEN_TO_PARTY, MtMoon_B2F_Frlg_EventScript_BeliefBookSuccess
    goto_if_eq VAR_RESULT, MON_GIVEN_TO_PC, MtMoon_B2F_Frlg_EventScript_BeliefBookSuccess

    msgbox MtMoon_B2F_Frlg_Text_NoRoom, MSGBOX_DEFAULT
    release
    end


MtMoon_B2F_Frlg_EventScript_BeliefBookSuccess:
    setflag FLAG_MT_MOON_BELIEF_BOOK_USED

    goto_if_eq VAR_0x8005, 0, MtMoon_B2F_Frlg_EventScript_SaveBeliefSee
    goto_if_eq VAR_0x8005, 1, MtMoon_B2F_Frlg_EventScript_SaveBeliefFeel
    goto_if_eq VAR_0x8005, 2, MtMoon_B2F_Frlg_EventScript_SaveBeliefRemember
    goto_if_eq VAR_0x8005, 3, MtMoon_B2F_Frlg_EventScript_SaveBeliefUnderstand

    goto MtMoon_B2F_Frlg_EventScript_BeliefBookFinish


MtMoon_B2F_Frlg_EventScript_SaveBeliefSee:
    setvar VAR_MT_MOON_BELIEF, 1
    goto MtMoon_B2F_Frlg_EventScript_ConfirmMimikyu


MtMoon_B2F_Frlg_EventScript_SaveBeliefFeel:
    setvar VAR_MT_MOON_BELIEF, 2
    goto MtMoon_B2F_Frlg_EventScript_ConfirmAnnihilape


MtMoon_B2F_Frlg_EventScript_SaveBeliefRemember:
    setvar VAR_MT_MOON_BELIEF, 3
    goto MtMoon_B2F_Frlg_EventScript_ConfirmTypeNull


MtMoon_B2F_Frlg_EventScript_SaveBeliefUnderstand:
    setvar VAR_MT_MOON_BELIEF, 4
    goto MtMoon_B2F_Frlg_EventScript_ConfirmZoroark

    goto MtMoon_B2F_Frlg_EventScript_BeliefBookFinish


MtMoon_B2F_Frlg_EventScript_ConfirmMimikyu:
    msgbox MtMoon_B2F_Frlg_Text_ReceivedMimikyu, MSGBOX_DEFAULT
    goto MtMoon_B2F_Frlg_EventScript_BeliefBookFinish


MtMoon_B2F_Frlg_EventScript_ConfirmAnnihilape:
    msgbox MtMoon_B2F_Frlg_Text_ReceivedAnnihilape, MSGBOX_DEFAULT
    goto MtMoon_B2F_Frlg_EventScript_BeliefBookFinish


MtMoon_B2F_Frlg_EventScript_ConfirmTypeNull:
    msgbox MtMoon_B2F_Frlg_Text_ReceivedTypeNull, MSGBOX_DEFAULT
    goto MtMoon_B2F_Frlg_EventScript_BeliefBookFinish


MtMoon_B2F_Frlg_EventScript_ConfirmZoroark:
    msgbox MtMoon_B2F_Frlg_Text_ReceivedZoroark, MSGBOX_DEFAULT
    goto MtMoon_B2F_Frlg_EventScript_BeliefBookFinish


MtMoon_B2F_Frlg_EventScript_BeliefBookFinish:
    msgbox MtMoon_B2F_Frlg_Text_BeliefBookSuccess, MSGBOX_DEFAULT
    release
    end


MtMoon_B2F_Frlg_EventScript_BeliefBookCancel:
    msgbox MtMoon_B2F_Frlg_Text_BeliefBookCancel, MSGBOX_DEFAULT
    release
    end


MtMoon_B2F_Frlg_EventScript_BeliefBookAfter:
    goto_if_set FLAG_MT_MOON_BELIEF_SHINY_FIXED, MtMoon_B2F_Frlg_EventScript_BeliefBookAfterNormal

    msgbox MtMoon_B2F_Frlg_Text_BeliefShinyFix, MSGBOX_DEFAULT

    chooseboxmon SELECT_PC_MON_NORMAL
    waitstate

    goto_if_eq VAR_0x8004, PARTY_NOTHING_CHOSEN, MtMoon_B2F_Frlg_EventScript_BeliefBookAfterNormal

    special Script_IsSelectedMonMimikyu
    goto_if_eq VAR_RESULT, FALSE, MtMoon_B2F_Frlg_EventScript_BeliefShinyWrongMon

    special Script_IsSelectedMonShiny
    goto_if_eq VAR_RESULT, TRUE, MtMoon_B2F_Frlg_EventScript_BeliefShinyAlreadyDone

    special Script_MakeSelectedMonShiny
    setflag FLAG_MT_MOON_BELIEF_SHINY_FIXED

    msgbox MtMoon_B2F_Frlg_Text_BeliefShinySuccess, MSGBOX_DEFAULT
    release
    end

MtMoon_B2F_Frlg_EventScript_BeliefShinyAlreadyDone:
    setflag FLAG_MT_MOON_BELIEF_SHINY_FIXED
    msgbox MtMoon_B2F_Frlg_Text_BeliefShinyAlready, MSGBOX_DEFAULT
    release
    end

MtMoon_B2F_Frlg_EventScript_BeliefShinyWrongMon:
    msgbox MtMoon_B2F_Frlg_Text_BeliefShinyWrongMon, MSGBOX_DEFAULT
    release
    end

MtMoon_B2F_Frlg_EventScript_BeliefBookAfterNormal:
    msgbox MtMoon_B2F_Frlg_Text_BeliefBookAfter, MSGBOX_DEFAULT
    release
    end


MtMoon_B2F_Frlg_Text_BeliefBookOpening:
    .string "The pages are covered in faded\n"
    .string "writing...\p"
    .string "What you believe defines who\n"
    .string "you are.\p"
    .string "...Or does it?\p"
    .string "When what you know fails you...\p"
    .string "When what you trust is tested...\p"
    .string "In the face of adversity...\p"
    .string "What do you believe?$"


MtMoon_B2F_Frlg_Text_ChoiceSee:
    .string "What I can see$"


MtMoon_B2F_Frlg_Text_ChoiceFeel:
    .string "What I can feel$"


MtMoon_B2F_Frlg_Text_ChoiceRemember:
    .string "What I remember$"


MtMoon_B2F_Frlg_Text_ChoiceUnderstand:
    .string "What I don't understand$"


MtMoon_B2F_Frlg_Text_ThenBelieveIt:
    .string "The words on the page begin to\n"
    .string "fade...\p"
    .string "Then believe it.$"


MtMoon_B2F_Frlg_Text_NoRoom:
    .string "For a moment, the pages tremble.\p"
    .string "Then everything becomes still.\p"
    .string "Whatever was supposed to happen...\n"
    .string "didn't.$"


MtMoon_B2F_Frlg_Text_ReceivedMimikyu:
    .string "Something small shifts at your\n"
    .string "side.\p"
    .string "MIMIKYU joined you.$"


MtMoon_B2F_Frlg_Text_ReceivedAnnihilape:
    .string "A violent presence surges nearby.\p"
    .string "ANNIHILAPE joined you.$"


MtMoon_B2F_Frlg_Text_ReceivedTypeNull:
    .string "Something restrained stirs beside\n"
    .string "you.\p"
    .string "TYPE: NULL joined you.$"


MtMoon_B2F_Frlg_Text_ReceivedZoroark:
    .string "A pale shape flickers into view.\p"
    .string "HISUIAN ZOROARK joined you.$"


MtMoon_B2F_Frlg_Text_BeliefBookSuccess:
    .string "The final words disappear from\n"
    .string "the page.$"


MtMoon_B2F_Frlg_Text_BeliefBookCancel:
    .string "The question remains on the page.$"


MtMoon_B2F_Frlg_Text_BeliefShinyFix:
    .string "For a moment, something glimmers\n"
    .string "across the blank page...\p"
    .string "A familiar presence comes to mind.$"

MtMoon_B2F_Frlg_Text_BeliefShinySuccess:
    .string "The page gives off a faint light.\p"
    .string "Then it becomes blank again.$"

MtMoon_B2F_Frlg_Text_BeliefShinyAlready:
    .string "Nothing changes.\p"
    .string "It seems this has already happened.$"

MtMoon_B2F_Frlg_Text_BeliefShinyWrongMon:
    .string "Nothing happens.\p"
    .string "That isn't the presence the book\n"
    .string "remembers.$"

MtMoon_B2F_Frlg_Text_BeliefBookAfter:
    .string "The pages are blank.\p"
    .string "Every single one.$"

@ ============================================================
@ Professor Oak
@ ============================================================

MtMoon_B2F_Frlg_EventScript_Oak::
    lock
    faceplayer
    goto_if_set FLAG_MT_MOON_OAK_TALKED, MtMoon_B2F_Frlg_EventScript_OakCircleback

    msgbox MtMoon_B2F_Frlg_Text_Oak, MSGBOX_DEFAULT
    setflag FLAG_MT_MOON_OAK_TALKED
    release
    end

MtMoon_B2F_Frlg_EventScript_OakCircleback:
    msgbox MtMoon_B2F_Frlg_Text_OakCircleback, MSGBOX_DEFAULT
    release
    end


MtMoon_B2F_Frlg_Text_Oak:
    .string "{PLAYER}: Professor Oak?\p"
    .string "OAK: Ah, {PLAYER}.\p"
    .string "I wondered when you'd find your\n"
    .string "way down here.\p"
    .string "{PLAYER}: ...You did?\p"
    .string "OAK: Hm?\p"
    .string "{PLAYER}: You said you wondered\n"
    .string "when I'd get here.\p"
    .string "OAK: Did I?\p"
    .string "{PLAYER}: ...Yes.\p"
    .string "OAK: Interesting.\p"
    .string "{PLAYER}: What's interesting?!\p"
    .string "OAK: Clefairy.\p"
    .string "{PLAYER}: ...\p"
    .string "OAK: I've been studying their\n"
    .string "behavior in this area.\p"
    .string "{PLAYER}: You changed the subject.\p"
    .string "OAK: Did I?$"

@ ============================================================
@ Mt. Moon Twin Altar
@ ============================================================

MtMoon_B2F_Frlg_EventScript_Twin::
    setvar VAR_0x8004, LOCALID_MT_MOON_TWIN
    lock
    faceplayer

    call MtMoon_B2F_Frlg_EventScript_BufferTwinName

    goto_if_set FLAG_MT_MOON_TWIN_BOOK_READ, MtMoon_B2F_Frlg_EventScript_TwinAfterReading
    goto_if_set FLAG_MT_MOON_TWIN_BOOK_INTRO_DONE, MtMoon_B2F_Frlg_EventScript_TwinWaitingForBook

    msgbox MtMoon_B2F_Frlg_Text_TwinOpening, MSGBOX_DEFAULT

    applymovement VAR_0x8004, Common_Movement_WalkInPlaceFasterUp
    waitmovement 0

    msgbox MtMoon_B2F_Frlg_Text_TwinBookPrompt, MSGBOX_DEFAULT

    setflag FLAG_MT_MOON_TWIN_BOOK_INTRO_DONE

    release
    end


MtMoon_B2F_Frlg_EventScript_TwinWaitingForBook:
    msgbox MtMoon_B2F_Frlg_Text_TwinWaitingForBook, MSGBOX_DEFAULT
    release
    end


MtMoon_B2F_Frlg_EventScript_TwinAfterReading:
    msgbox MtMoon_B2F_Frlg_Text_TwinAfterBook, MSGBOX_DEFAULT

    applymovement VAR_0x8004, Common_Movement_FacePlayer
    waitmovement 0

    msgbox MtMoon_B2F_Frlg_Text_TwinSaffronOak, MSGBOX_DEFAULT
    msgbox MtMoon_B2F_Frlg_Text_TwinBattleIntro, MSGBOX_DEFAULT

    goto_if_set FLAG_HIDE_HOME_MOM, MtMoon_B2F_Frlg_EventScript_XieBattle

MtMoon_B2F_Frlg_EventScript_SolBattle:
    trainerbattle_no_intro TRAINER_SOL_MT_MOON, MtMoon_B2F_Frlg_Text_TwinDefeat
    goto MtMoon_B2F_Frlg_EventScript_TwinAfterBattle

MtMoon_B2F_Frlg_EventScript_XieBattle:
    trainerbattle_no_intro TRAINER_XIE_MT_MOON, MtMoon_B2F_Frlg_Text_TwinDefeat
    goto MtMoon_B2F_Frlg_EventScript_TwinAfterBattle

MtMoon_B2F_Frlg_EventScript_TwinAfterBattle:
    call MtMoon_B2F_Frlg_EventScript_BufferTwinName
    msgbox MtMoon_B2F_Frlg_Text_TwinAfterBattle, MSGBOX_DEFAULT

    setflag FLAG_HIDE_MT_MOON_TWIN
    removeobject LOCALID_MT_MOON_TWIN

    delay 30
    msgbox MtMoon_B2F_Frlg_Text_TwinDisappeared, MSGBOX_DEFAULT

    release
    end


@ ============================================================
@ Dynamic Sol / Xie Name
@ ============================================================

MtMoon_B2F_Frlg_EventScript_BufferTwinName:
    goto_if_set FLAG_HIDE_HOME_MOM, MtMoon_B2F_Frlg_EventScript_BufferXieName

    bufferstring STR_VAR_1, MtMoon_B2F_Frlg_Text_NameSol
    return


MtMoon_B2F_Frlg_EventScript_BufferXieName:
    bufferstring STR_VAR_1, MtMoon_B2F_Frlg_Text_NameXie
    return


@ ============================================================
@ Second Book
@ ============================================================

MtMoon_B2F_Frlg_EventScript_TwinBook::
    lock

    goto_if_set FLAG_MT_MOON_TWIN_BOOK_READ, MtMoon_B2F_Frlg_EventScript_TwinBookBlank

    msgbox MtMoon_B2F_Frlg_Text_TwinBook, MSGBOX_DEFAULT

    setflag FLAG_MT_MOON_TWIN_BOOK_INTRO_DONE
    setflag FLAG_MT_MOON_TWIN_BOOK_READ

    release
    end


MtMoon_B2F_Frlg_EventScript_TwinBookBlank:
    msgbox MtMoon_B2F_Frlg_Text_TwinBookBlank, MSGBOX_DEFAULT
    release
    end


@ ============================================================
@ Twin Altar Text
@ ============================================================

MtMoon_B2F_Frlg_Text_NameSol:
    .string "SOL$"

MtMoon_B2F_Frlg_Text_NameXie:
    .string "XIE$"


MtMoon_B2F_Frlg_Text_TwinOpening:
    .string "{PLAYER}: ...What are you doing?\p"
    .string "{STR_VAR_1}: Reading.\p"
    .string "{PLAYER}: I can see that.\p"
    .string "{STR_VAR_1}: Then why'd you ask?\p"
    .string "{PLAYER}: How'd you even get here?\p"
    .string "{STR_VAR_1}: Walked.\p"
    .string "{PLAYER}: From Saffron?!\p"
    .string "{STR_VAR_1}: Eventually.\p"
    .string "{PLAYER}: What happened with\n"
    .string "Sabrina?\p"
    .string "{STR_VAR_1}: A lot.\p"
    .string "{PLAYER}: ...That's it?\p"
    .string "{STR_VAR_1}: For now.$"


MtMoon_B2F_Frlg_Text_TwinBookPrompt:
    .string "{PLAYER}: What's so interesting\n"
    .string "about that book?\p"
    .string "{STR_VAR_1}: Read it.$"


MtMoon_B2F_Frlg_Text_TwinWaitingForBook:
    .string "{STR_VAR_1}: Read it.$"


MtMoon_B2F_Frlg_Text_TwinBook:
    .string "The pages are covered in faded\n"
    .string "writing...\p"
    .string "What you believe defines who\n"
    .string "you are.\p"
    .string "...But what defines what you\n"
    .string "believe?\p"
    .string "Sight can deceive.\p"
    .string "Feeling can betray.\p"
    .string "Memory can change.\p"
    .string "Understanding can fail.\p"
    .string "When none can be trusted...\p"
    .string "What remains?\p"
    .string "...\p"
    .string "The words disappear from the\n"
    .string "page.$"


MtMoon_B2F_Frlg_Text_TwinBookBlank:
    .string "The pages are blank.$"


MtMoon_B2F_Frlg_Text_TwinAfterBook:
    .string "{PLAYER}: ...\p"
    .string "{STR_VAR_1}: Yeah.\p"
    .string "{PLAYER}: You already read that?\p"
    .string "{STR_VAR_1}: It wasn't blank when I\n"
    .string "found it.\p"
    .string "{PLAYER}: Mine wasn't like that.\p"
    .string "{STR_VAR_1}: Mine?\p"
    .string "{PLAYER}: I found another one.\p"
    .string "{STR_VAR_1}: What did yours ask?\p"
    .string "{PLAYER}: What I believed.\p"
    .string "{STR_VAR_1}: Did you answer?\p"
    .string "{PLAYER}: ...Yeah.\p"
    .string "{STR_VAR_1}: Interesting.\p"
    .string "{PLAYER}: Don't.\p"
    .string "{STR_VAR_1}: What?$"


MtMoon_B2F_Frlg_Text_TwinSaffronOak:
    .string "{PLAYER}: Oak said the same thing.\p"
    .string "{STR_VAR_1}: Gramps is here?\p"
    .string "{PLAYER}: HOW DOES EVERYONE KNOW\n"
    .string "HIM?!\p"
    .string "{STR_VAR_1}: ...Know who?\p"
    .string "{PLAYER}: Never mind.\p"
    .string "{STR_VAR_1}: You seem tense.\p"
    .string "{PLAYER}: I wonder why.$"


MtMoon_B2F_Frlg_Text_TwinBattleIntro:
    .string "{STR_VAR_1}: Speaking of interesting...\p"
    .string "{PLAYER}: No.\p"
    .string "{STR_VAR_1}: You don't even know what\n"
    .string "I was going to say.\p"
    .string "{PLAYER}: You want to battle.\p"
    .string "{STR_VAR_1}: See? You do know me.$"

MtMoon_B2F_Frlg_Text_TwinDefeat:
    .string "...Interesting.$"

MtMoon_B2F_Frlg_Text_TwinDisappeared:
    .string "{PLAYER}: ...Did they just disappear?\p"
    .string "{PLAYER}: Did they learn that from\n"
    .string "Sabrina?\p"
    .string "{PLAYER}: I thought we didn't like\n"
    .string "her.\p"
    .string "{PLAYER}: ...Hm.$"

MtMoon_B2F_Frlg_Text_TwinAfterBattle:
    .string "{PLAYER}: Don't say it.\p"
    .string "{STR_VAR_1}: I wasn't going to.\p"
    .string "{PLAYER}: Yes, you were.\p"
    .string "{STR_VAR_1}: Maybe.\p"
    .string "{PLAYER}: Where are you going?\p"
    .string "{STR_VAR_1}: Out.\p"
    .string "{PLAYER}: That's not an answer.\p"
    .string "{STR_VAR_1}: It answered the question.$"

MtMoon_B2F_Frlg_EventScript_Lorelei::
    lock
    faceplayer
    goto_if_set FLAG_MT_MOON_LORELEI_TALKED, MtMoon_B2F_Frlg_EventScript_LoreleiCircleback

    msgbox MtMoon_B2F_Frlg_Text_Lorelei, MSGBOX_DEFAULT
    setflag FLAG_MT_MOON_LORELEI_TALKED
    release
    end

MtMoon_B2F_Frlg_EventScript_LoreleiCircleback:
    msgbox MtMoon_B2F_Frlg_Text_LoreleiCircleback, MSGBOX_DEFAULT
    release
    end


MtMoon_B2F_Frlg_Text_Lorelei:
    .string "{PLAYER}: ...Lorelei?\p"
    .string "LORELEI: Hm?\p"
    .string "{PLAYER}: What are you doing?\p"
    .string "LORELEI: Looking around.\p"
    .string "{PLAYER}: At Professor Oak?\p"
    .string "LORELEI: Among other things.\p"
    .string "{PLAYER}: You're watching him.\p"
    .string "LORELEI: Observing.\p"
    .string "{PLAYER}: That's the same thing.\p"
    .string "LORELEI: It sounds less suspicious.\p"
    .string "{PLAYER}: Why are you observing him?\p"
    .string "LORELEI: Because he's lying.\p"
    .string "{PLAYER}: About what?\p"
    .string "LORELEI: How familiar he is with\n"
    .string "this place.\p"
    .string "{PLAYER}: ...He knew I was coming.\p"
    .string "LORELEI: Did he?\p"
    .string "{PLAYER}: Then pretended he didn't\n"
    .string "say it.\p"
    .string "LORELEI: That sounds like Oak.\p"
    .string "{PLAYER}: You know him?\p"
    .string "LORELEI: Everyone knows Oak.\p"
    .string "{PLAYER}: That's not what I meant.\p"
    .string "LORELEI: I know.\p"
    .string "{PLAYER}: ...\p"
    .string "LORELEI: You should ask him about\n"
    .string "Giovanni sometime.\p"
    .string "{PLAYER}: Giovanni?!\p"
    .string "LORELEI: Or don't.\p"
    .string "{PLAYER}: LORELEI.\p"
    .string "LORELEI: I'm observing.$"

MtMoon_B2F_Frlg_EventScript_KogaRando::
    lock
    faceplayer
    msgbox MtMoon_B2F_Frlg_Text_KogaRando, MSGBOX_DEFAULT
    release
    end


MtMoon_B2F_Frlg_EventScript_CardioGirl::
    lock
    faceplayer
    msgbox MtMoon_B2F_Frlg_Text_CardioGirl, MSGBOX_DEFAULT
    release
    end


MtMoon_B2F_Frlg_EventScript_GiovanniRando::
    lock
    faceplayer
    msgbox MtMoon_B2F_Frlg_Text_GiovanniRando, MSGBOX_DEFAULT
    release
    end


MtMoon_B2F_Frlg_EventScript_ConfusedClefairy::
    lock
    faceplayer
    msgbox MtMoon_B2F_Frlg_Text_ConfusedClefairy, MSGBOX_DEFAULT
    release
    end


MtMoon_B2F_Frlg_Text_KogaRando:
    .string "Koga told me not to wander too\n"
    .string "deep into Mt. Moon.\p"
    .string "Naturally, I took that as a\n"
    .string "recommendation.$"


MtMoon_B2F_Frlg_Text_CardioGirl:
    .string "I've been doing laps around this\n"
    .string "Clefairy for exercise.\p"
    .string "It hasn't moved once.\p"
    .string "I think it's judging my form.$"


MtMoon_B2F_Frlg_Text_GiovanniRando:
    .string "I used to hike through here years\n"
    .string "ago.\p"
    .string "Saw Professor Oak arguing with\n"
    .string "Giovanni once.\p"
    .string "Didn't seem like my business.\p"
    .string "Still doesn't.$"


MtMoon_B2F_Frlg_Text_ConfusedClefairy:
    .string "CLEFAIRY: ...Clefairy?$"

MtMoon_B2F_Frlg_EventScript_MoonWoman::
    lock
    faceplayer
    msgbox MtMoon_B2F_Frlg_Text_MoonWoman, MSGBOX_DEFAULT
    release
    end


MtMoon_B2F_Frlg_Text_MoonWoman:
    .string "People come here looking for\n"
    .string "Moon Stones.\p"
    .string "I think half of them just like\n"
    .string "having a reason to explore.$"


MtMoon_B2F_Frlg_Text_OakCircleback:
    .string "{PLAYER}: Giovanni.\p"
    .string "OAK: Clefairy.\p"
    .string "{PLAYER}: You can't keep doing\n"
    .string "that.\p"
    .string "OAK: Hm?$"


MtMoon_B2F_Frlg_Text_LoreleiCircleback:
    .string "{PLAYER}: Still observing?\p"
    .string "LORELEI: Very interesting wall.\p"
    .string "{PLAYER}: Right.$"

