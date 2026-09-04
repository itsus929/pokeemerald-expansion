EmberSpa_Frlg_MapScripts::
        map_script MAP_SCRIPT_ON_LOAD, EmberSpa_SetCounterpartGraphics
        .byte 0

EmberSpa_SetCounterpartGraphics:
        @ Counterpart only appears when the Mt. Chimney Spa branch is pending.
        goto_if_set FLAG_EMBER_SPA_COUNTERPART_PENDING, EmberSpa_ShowCounterpart
        setflag FLAG_HIDE_EMBER_SPA_COUNTERPART
        goto EmberSpa_SetCounterpartGraphics_Select

EmberSpa_ShowCounterpart:
        clearflag FLAG_HIDE_EMBER_SPA_COUNTERPART

EmberSpa_SetCounterpartGraphics_Select:
        goto_if_eq VAR_COUNTERPART_ID, COUNTERPART_BRENDAN, EmberSpa_SetBrendan
        goto_if_eq VAR_COUNTERPART_ID, COUNTERPART_MAY, EmberSpa_SetMay
        goto_if_eq VAR_COUNTERPART_ID, COUNTERPART_LEXY, EmberSpa_SetLexy
        goto_if_eq VAR_COUNTERPART_ID, COUNTERPART_JUSTIN, EmberSpa_SetJustin
        goto_if_eq VAR_COUNTERPART_ID, COUNTERPART_MAAM, EmberSpa_SetMaam
        goto_if_eq VAR_COUNTERPART_ID, COUNTERPART_SIR, EmberSpa_SetSir
        goto EmberSpa_FinishCounterpartLoad

EmberSpa_SetBrendan:
        setvar VAR_OBJ_GFX_ID_0, OBJ_EVENT_GFX_BRENDAN_NORMAL
        goto EmberSpa_FinishCounterpartLoad

EmberSpa_SetMay:
        setvar VAR_OBJ_GFX_ID_0, OBJ_EVENT_GFX_MAY_NORMAL
        goto EmberSpa_FinishCounterpartLoad

EmberSpa_SetLexy:
        setvar VAR_OBJ_GFX_ID_0, OBJ_EVENT_GFX_LEXY_NORMAL
        goto EmberSpa_FinishCounterpartLoad

EmberSpa_SetJustin:
        setvar VAR_OBJ_GFX_ID_0, OBJ_EVENT_GFX_JUSTIN_NORMAL
        goto EmberSpa_FinishCounterpartLoad

EmberSpa_SetMaam:
        setvar VAR_OBJ_GFX_ID_0, OBJ_EVENT_GFX_MAAM_NORMAL
        goto EmberSpa_FinishCounterpartLoad

EmberSpa_SetSir:
        setvar VAR_OBJ_GFX_ID_0, OBJ_EVENT_GFX_SIR_NORMAL

EmberSpa_FinishCounterpartLoad:
        end

EmberSpa_EventScript_SpaHeal::
        lockall
        fadescreen FADE_TO_WHITE
        special HealPlayerParty
        fadescreen FADE_FROM_WHITE
        msgbox EmberSpa_Text_FullyRefreshed
        setvar VAR_TEMP_1, 1
        releaseall
        end

EmberSpa_EventScript_OldMan::
        msgbox EmberSpa_Text_OldMan, MSGBOX_NPC
        end

EmberSpa_EventScript_BaldingMan::
        msgbox EmberSpa_Text_BaldingMan, MSGBOX_NPC
        end

EmberSpa_EventScript_BlackBelt::
        msgbox EmberSpa_Text_BlackBelt, MSGBOX_NPC
        end

EmberSpa_EventScript_OldWoman::
        msgbox EmberSpa_Text_OldWoman, MSGBOX_NPC
        end

EmberSpa_EventScript_SpaHistorian::
        msgbox EmberSpa_Text_SpaHistorian, MSGBOX_NPC
        end

EmberSpa_EventScript_ReviveSeller::
        lock
        faceplayer
        showmoneybox 0, 0
        msgbox EmberSpa_Text_ReviveSellerIntro, MSGBOX_DEFAULT
        dynmultichoice 0, 0, FALSE, 4, 0, DYN_MULTICHOICE_CB_NONE, EmberSpa_Text_ReviveOne, EmberSpa_Text_ReviveThree, EmberSpa_Text_ReviveFive, EmberSpa_Text_ReviveCancel
        switch VAR_RESULT
        case 0, EmberSpa_EventScript_BuyOneRevive
        case 1, EmberSpa_EventScript_BuyThreeRevives
        case 2, EmberSpa_EventScript_BuyFiveRevives
        case 3, EmberSpa_EventScript_ReviveSellerDecline
        case MULTI_B_PRESSED, EmberSpa_EventScript_ReviveSellerDecline
        goto EmberSpa_EventScript_ReviveSellerDecline

EmberSpa_EventScript_BuyOneRevive::
        checkmoney 1000
        goto_if_eq VAR_RESULT, FALSE, EmberSpa_EventScript_NotEnoughMoney
        checkitemspace ITEM_REVIVE, 1
        goto_if_eq VAR_RESULT, FALSE, EmberSpa_EventScript_BagFull
        removemoney 1000
        updatemoneybox
        hidemoneybox
        giveitem ITEM_REVIVE, 1
        msgbox EmberSpa_Text_ReviveSellerThanks, MSGBOX_DEFAULT
        release
        end

EmberSpa_EventScript_BuyThreeRevives::
        checkmoney 3000
        goto_if_eq VAR_RESULT, FALSE, EmberSpa_EventScript_NotEnoughMoney
        checkitemspace ITEM_REVIVE, 3
        goto_if_eq VAR_RESULT, FALSE, EmberSpa_EventScript_BagFull
        removemoney 3000
        updatemoneybox
        hidemoneybox
        giveitem ITEM_REVIVE, 3
        msgbox EmberSpa_Text_ReviveSellerThanks, MSGBOX_DEFAULT
        release
        end

EmberSpa_EventScript_BuyFiveRevives::
        checkmoney 5000
        goto_if_eq VAR_RESULT, FALSE, EmberSpa_EventScript_NotEnoughMoney
        checkitemspace ITEM_REVIVE, 5
        goto_if_eq VAR_RESULT, FALSE, EmberSpa_EventScript_BagFull
        removemoney 5000
        updatemoneybox
        hidemoneybox
        giveitem ITEM_REVIVE, 5
        msgbox EmberSpa_Text_ReviveSellerThanks, MSGBOX_DEFAULT
        release
        end

EmberSpa_EventScript_NotEnoughMoney::
        msgbox EmberSpa_Text_NotEnoughMoney, MSGBOX_DEFAULT
        hidemoneybox
        release
        end

EmberSpa_EventScript_BagFull::
        msgbox EmberSpa_Text_BagFull, MSGBOX_DEFAULT
        hidemoneybox
        release
        end

EmberSpa_EventScript_ReviveSellerDecline::
        msgbox EmberSpa_Text_ReviveSellerDecline, MSGBOX_DEFAULT
        hidemoneybox
        release
        end

EmberSpa_Text_FullyRefreshed:
        .string "The water is perfectly warm.\n"
        .string "It feels exquisite...\p"
        .string "{PLAYER} and the POKéMON were\n"
        .string "fully refreshed!$"

EmberSpa_Text_OldMan:
        .string "Nothing clears the head like a\n"
        .string "good soak.\p"
        .string "Stay as long as you need.$"

EmberSpa_Text_BaldingMan:
        .string "If you're heading back up the\n"
        .string "mountain, take your time.\p"
        .string "It'll still be there.$"

EmberSpa_Text_BlackBelt:
        .string "Hot water after training.\p"
        .string "Best recovery there is.$"

EmberSpa_Text_OldWoman:
        .string "Oh, honey...\p"
        .string "You look like you've had a day.\p"
        .string "Get in the water.$"

EmberSpa_Text_SpaHistorian:
        .string "Trainers have stopped here for\n"
        .string "years before climbing higher.\p"
        .string "The smart ones stop again on\n"
        .string "the way back.$"

EmberSpa_Text_ReviveSellerIntro:
        .string "Heading back up the mountain?\p"
        .string "I keep REVIVES for trainers.\p"
        .string "Spa price. 1,000 each.$"

EmberSpa_Text_ReviveSellerThanks:
        .string "There you go.\p"
        .string "Try not to need them.$"

EmberSpa_Text_NotEnoughMoney:
        .string "Looks like you're a little short.\p"
        .string "The spring is still free.$"

EmberSpa_Text_BagFull:
        .string "Your BAG is too full.\p"
        .string "Make some room and come back.$"

EmberSpa_Text_ReviveSellerDecline:
        .string "Suit yourself.\p"
        .string "Just be careful up there.$"

EmberSpa_Text_ReviveOne:
        .string "1 REVIVE$"

EmberSpa_Text_ReviveThree:
        .string "3 REVIVES$"

EmberSpa_Text_ReviveFive:
        .string "5 REVIVES$"

EmberSpa_Text_ReviveCancel:
        .string "Never mind$"


EmberSpa_EventScript_Counterpart::
        lock
        faceplayer
        msgbox EmberSpa_Text_CounterpartSoak, MSGBOX_DEFAULT
        closemessage

        @ Their part in the Mt. Chimney arc is complete.
        clearflag FLAG_EMBER_SPA_COUNTERPART_PENDING
        setflag FLAG_HIDE_EMBER_SPA_COUNTERPART

        @ Small fade lets them get out and leave without
        @ needing fragile water-path choreography.
        fadescreen FADE_TO_BLACK
        removeobject LOCALID_EMBER_SPA_COUNTERPART
        delay 12
        fadescreen FADE_FROM_BLACK

        release
        end

EmberSpa_Text_CounterpartSoak:
        .string "{RIVAL}: Okay.\p"
        .string "This was a good idea.\p"
        .string "{PLAYER}: I know.\p"
        .string "{RIVAL}: Don't make it weird.\p"
        .string "{PLAYER}: You just admitted I was\n"
        .string "right.\p"
        .string "{RIVAL}: And now I regret speaking.\p"
        .string "{PLAYER}: You good though?\p"
        .string "{RIVAL}: ...Yeah.\p"
        .string "I think so.\p"
        .string "Today was just a lot.\p"
        .string "{PLAYER}: That's one way to put it.\p"
        .string "{RIVAL}: Giovanni showing up again.\p"
        .string "Sabrina somehow being involved.\p"
        .string "And whatever's going on with\n"
        .string "Mt. Moon...\p"
        .string "{PLAYER}: You said you weren't\n"
        .string "summarizing anymore.\p"
        .string "{RIVAL}: I'm not.\p"
        .string "I'm saying it's weird.\p"
        .string "{PLAYER}: Fair.\p"
        .string "Okay, well...\p"
        .string "I'll see you around.\p"
        .string "Whenever, I guess.\p"
        .string "{RIVAL}: Yeah. Sure.\p"
        .string "But some seriously weird stuff\n"
        .string "is going on, man.\p"
        .string "I'm telling you.$"
