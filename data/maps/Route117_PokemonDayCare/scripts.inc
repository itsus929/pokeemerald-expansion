Route117_PokemonDayCare_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, Route117_PokemonDayCare_OnTransition
	.byte 0

Route117_PokemonDayCare_OnTransition:
	setflag FLAG_LANDMARK_POKEMON_DAYCARE
	end


@ ============================================================
@ EGG MOVE SPECIALIST
@ ============================================================

Route117_PokemonDayCare_EventScript_EggMoveSpecialist::
        lockall
        faceplayer
        goto_if_set FLAG_RECEIVED_ROUTE117_MIRROR_HERB, Route117_PokemonDayCare_EventScript_EggMoveServices
        msgbox Route117_PokemonDayCare_Text_EggMoveIntro, MSGBOX_DEFAULT
        giveitem ITEM_MIRROR_HERB, 1
        goto_if_eq VAR_RESULT, FALSE, Route117_PokemonDayCare_EventScript_MirrorHerbBagFull
        setflag FLAG_RECEIVED_ROUTE117_MIRROR_HERB
        msgbox Route117_PokemonDayCare_Text_FirstMirrorHerb, MSGBOX_DEFAULT
        goto Route117_PokemonDayCare_EventScript_EggMoveServices
        end

Route117_PokemonDayCare_EventScript_MirrorHerbBagFull::
        msgbox Route117_PokemonDayCare_Text_MirrorHerbBagFull, MSGBOX_DEFAULT
        releaseall
        end

Route117_PokemonDayCare_EventScript_EggMoveServices::
        msgbox Route117_PokemonDayCare_Text_ServiceMenuPrompt, MSGBOX_DEFAULT
        dynmultichoice 0, 0, FALSE, 3, 0, DYN_MULTICHOICE_CB_NONE, Route117_PokemonDayCare_Text_ServiceDeleteMove, Route117_PokemonDayCare_Text_ServiceMirrorHerb, Route117_PokemonDayCare_Text_ServiceCustomizeEgg, Route117_PokemonDayCare_Text_ServiceCancel
        goto_if_eq VAR_RESULT, 0, Route117_PokemonDayCare_EventScript_ChooseMonAndMoveToForget
        goto_if_eq VAR_RESULT, 1, Route117_PokemonDayCare_EventScript_MirrorHerbShop
        goto_if_eq VAR_RESULT, 2, Route117_PokemonDayCare_EventScript_ChooseEggToCustomize
        goto Route117_PokemonDayCare_EventScript_ServiceBye
        end

Route117_PokemonDayCare_EventScript_ServiceBye::
        msgbox Route117_PokemonDayCare_Text_ComeBackAnytime, MSGBOX_DEFAULT
        releaseall
        end

Route117_PokemonDayCare_EventScript_MirrorHerbShop::
        message Route117_PokemonDayCare_Text_MirrorHerbShop
        waitmessage
        pokemart Route117_PokemonDayCare_MirrorHerbMart
        msgbox Route117_PokemonDayCare_Text_ComeBackAnytime, MSGBOX_DEFAULT
        releaseall
        end

        .align 2
Route117_PokemonDayCare_MirrorHerbMart:
        .2byte ITEM_MIRROR_HERB
        pokemartlistend

@ ============================================================
@ MOVE DELETER
@ ============================================================

Route117_PokemonDayCare_EventScript_ChooseMonAndMoveToForget::
        msgbox Route117_PokemonDayCare_Text_WhichMonShouldForget, MSGBOX_DEFAULT
        chooseboxmon SELECT_PC_MON_MOVE_DELETER
        waitstate
        goto_if_eq VAR_0x8004, PARTY_NOTHING_CHOSEN, Route117_PokemonDayCare_EventScript_EggMoveServices
        special IsSelectedMonEgg
        goto_if_eq VAR_RESULT, TRUE, Route117_PokemonDayCare_EventScript_EggCantForgetMoves
        special GetNumMovesSelectedMonHas
        goto_if_eq VAR_RESULT, 1, Route117_PokemonDayCare_EventScript_MonOnlyKnowsOneMove
        msgbox Route117_PokemonDayCare_Text_WhichMoveShouldBeForgotten, MSGBOX_DEFAULT
        fadescreen FADE_TO_BLACK
        special MoveDeleterChooseMoveToForget
        fadescreen FADE_FROM_BLACK
        goto_if_eq VAR_0x8005, MAX_MON_MOVES, Route117_PokemonDayCare_EventScript_ChooseMonAndMoveToForget
        special BufferMoveDeleterNicknameAndMove
        msgbox Route117_PokemonDayCare_Text_MonsMoveShouldBeForgotten, MSGBOX_YESNO
        goto_if_eq VAR_RESULT, YES, Route117_PokemonDayCare_EventScript_TryForgetMove
        goto Route117_PokemonDayCare_EventScript_EggMoveServices
        end

Route117_PokemonDayCare_EventScript_TryForgetMove::
        special IsLastMonThatKnowsSurf
        goto_if_eq VAR_RESULT, TRUE, Route117_PokemonDayCare_EventScript_LastMonWithSurf
        special MoveDeleterForgetMove
        playfanfare MUS_MOVE_DELETED
        waitfanfare
        msgbox Route117_PokemonDayCare_Text_MonHasForgottenMove, MSGBOX_DEFAULT
        goto Route117_PokemonDayCare_EventScript_EggMoveServices
        end

Route117_PokemonDayCare_EventScript_MonOnlyKnowsOneMove::
        special BufferMoveDeleterNicknameAndMove
        msgbox Route117_PokemonDayCare_Text_MonOnlyKnowsOneMove, MSGBOX_DEFAULT
        goto Route117_PokemonDayCare_EventScript_EggMoveServices
        end

Route117_PokemonDayCare_EventScript_EggCantForgetMoves::
        msgbox Route117_PokemonDayCare_Text_EggCantForgetMoves, MSGBOX_DEFAULT
        goto Route117_PokemonDayCare_EventScript_EggMoveServices
        end

Route117_PokemonDayCare_EventScript_LastMonWithSurf::
        special BufferMoveDeleterNicknameAndMove
        msgbox Route117_PokemonDayCare_Text_CantForgetSurf, MSGBOX_DEFAULT
        goto Route117_PokemonDayCare_EventScript_EggMoveServices
        end


@ ============================================================
@ EGG CUSTOMIZATION
@ ============================================================

Route117_PokemonDayCare_EventScript_ChooseEggToCustomize::
        msgbox Route117_PokemonDayCare_Text_ChooseEgg, MSGBOX_DEFAULT
        chooseboxmon SELECT_PC_MON_NORMAL
        waitstate
        goto_if_eq VAR_0x8004, PARTY_NOTHING_CHOSEN, Route117_PokemonDayCare_EventScript_EggMoveServices
        special IsSelectedMonEgg
        goto_if_eq VAR_RESULT, FALSE, Route117_PokemonDayCare_EventScript_NotAnEgg
        goto Route117_PokemonDayCare_EventScript_EggCustomizeMenu
        end

Route117_PokemonDayCare_EventScript_NotAnEgg::
        msgbox Route117_PokemonDayCare_Text_NotAnEgg, MSGBOX_DEFAULT
        goto Route117_PokemonDayCare_EventScript_ChooseEggToCustomize
        end

Route117_PokemonDayCare_EventScript_EggCustomizeMenu::
        msgbox Route117_PokemonDayCare_Text_CustomizeWhat, MSGBOX_DEFAULT
        dynmultichoice 0, 0, FALSE, 3, 0, DYN_MULTICHOICE_CB_NONE, Route117_PokemonDayCare_Text_CustomGender, Route117_PokemonDayCare_Text_CustomBall, Route117_PokemonDayCare_Text_CustomAbility, Route117_PokemonDayCare_Text_CustomBack
        goto_if_eq VAR_RESULT, 0, Route117_PokemonDayCare_EventScript_GenderMenu
        goto_if_eq VAR_RESULT, 1, Route117_PokemonDayCare_EventScript_BallMenu
        goto_if_eq VAR_RESULT, 2, Route117_PokemonDayCare_EventScript_AbilityMenu
        goto_if_eq VAR_TEMP_2, 1, Route117_PokemonDayCare_EventScript_LavaridgeEggSisterExit
        goto Route117_PokemonDayCare_EventScript_EggMoveServices
        end

@ ------------------------------------------------------------
@ NATURE
@ ------------------------------------------------------------

Route117_PokemonDayCare_EventScript_NatureMenu::
        msgbox Route117_PokemonDayCare_Text_ChooseNature, MSGBOX_DEFAULT

        dynmultipush Route117_PokemonDayCare_Text_NatureHardy, NATURE_HARDY
        dynmultipush Route117_PokemonDayCare_Text_NatureLonely, NATURE_LONELY
        dynmultipush Route117_PokemonDayCare_Text_NatureBrave, NATURE_BRAVE
        dynmultipush Route117_PokemonDayCare_Text_NatureAdamant, NATURE_ADAMANT
        dynmultipush Route117_PokemonDayCare_Text_NatureNaughty, NATURE_NAUGHTY
        dynmultipush Route117_PokemonDayCare_Text_NatureBold, NATURE_BOLD
        dynmultipush Route117_PokemonDayCare_Text_NatureDocile, NATURE_DOCILE
        dynmultipush Route117_PokemonDayCare_Text_NatureRelaxed, NATURE_RELAXED
        dynmultipush Route117_PokemonDayCare_Text_NatureImpish, NATURE_IMPISH
        dynmultipush Route117_PokemonDayCare_Text_NatureLax, NATURE_LAX
        dynmultipush Route117_PokemonDayCare_Text_NatureTimid, NATURE_TIMID
        dynmultipush Route117_PokemonDayCare_Text_NatureHasty, NATURE_HASTY
        dynmultipush Route117_PokemonDayCare_Text_NatureSerious, NATURE_SERIOUS
        dynmultipush Route117_PokemonDayCare_Text_NatureJolly, NATURE_JOLLY
        dynmultipush Route117_PokemonDayCare_Text_NatureNaive, NATURE_NAIVE
        dynmultipush Route117_PokemonDayCare_Text_NatureModest, NATURE_MODEST
        dynmultipush Route117_PokemonDayCare_Text_NatureMild, NATURE_MILD
        dynmultipush Route117_PokemonDayCare_Text_NatureQuiet, NATURE_QUIET
        dynmultipush Route117_PokemonDayCare_Text_NatureBashful, NATURE_BASHFUL
        dynmultipush Route117_PokemonDayCare_Text_NatureRash, NATURE_RASH
        dynmultipush Route117_PokemonDayCare_Text_NatureCalm, NATURE_CALM
        dynmultipush Route117_PokemonDayCare_Text_NatureGentle, NATURE_GENTLE
        dynmultipush Route117_PokemonDayCare_Text_NatureSassy, NATURE_SASSY
        dynmultipush Route117_PokemonDayCare_Text_NatureCareful, NATURE_CAREFUL
        dynmultipush Route117_PokemonDayCare_Text_NatureQuirky, NATURE_QUIRKY
        dynmultipush Route117_PokemonDayCare_Text_CustomBack, 255
        dynmultistack 0, 0, FALSE, 6, 0, 0, DYN_MULTICHOICE_CB_NONE

        goto_if_eq VAR_RESULT, MULTI_B_PRESSED, Route117_PokemonDayCare_EventScript_EggCustomizeMenu
        goto_if_eq VAR_RESULT, 255, Route117_PokemonDayCare_EventScript_EggCustomizeMenu
        copyvar VAR_0x8005, VAR_RESULT
        goto Route117_PokemonDayCare_EventScript_BuyNature
        end

Route117_PokemonDayCare_EventScript_BuyNature::
        showmoneybox 0, 0
        msgbox Route117_PokemonDayCare_Text_NaturePrice, MSGBOX_YESNO
        goto_if_eq VAR_RESULT, NO, Route117_PokemonDayCare_EventScript_CancelPaidCustomization
        checkmoney 5000
        goto_if_eq VAR_RESULT, FALSE, Route117_PokemonDayCare_EventScript_CustomizationNoMoney
        callnative Script_SetSelectedEggNature
        goto_if_eq VAR_RESULT, FALSE, Route117_PokemonDayCare_EventScript_CustomizationFailed
        playse SE_SHOP
        removemoney 5000
        updatemoneybox
        waitse
        hidemoneybox
        msgbox Route117_PokemonDayCare_Text_NatureDone, MSGBOX_DEFAULT
        goto Route117_PokemonDayCare_EventScript_EggCustomizeMenu
        end

@ ------------------------------------------------------------
@ ABILITY
@ ------------------------------------------------------------

Route117_PokemonDayCare_EventScript_AbilityMenu::
        msgbox Route117_PokemonDayCare_Text_ChooseAbility, MSGBOX_DEFAULT
        dynmultichoice 0, 0, FALSE, 2, 0, DYN_MULTICHOICE_CB_NONE, Route117_PokemonDayCare_Text_AbilityInnate, Route117_PokemonDayCare_Text_AbilityHidden, Route117_PokemonDayCare_Text_CustomBack
        goto_if_eq VAR_RESULT, MULTI_B_PRESSED, Route117_PokemonDayCare_EventScript_EggCustomizeMenu
        goto_if_eq VAR_RESULT, 2, Route117_PokemonDayCare_EventScript_EggCustomizeMenu
        copyvar VAR_0x8005, VAR_RESULT

        showmoneybox 0, 0
        msgbox Route117_PokemonDayCare_Text_AbilityPrice, MSGBOX_YESNO
        goto_if_eq VAR_RESULT, NO, Route117_PokemonDayCare_EventScript_CancelPaidCustomization
        checkmoney 5000
        goto_if_eq VAR_RESULT, FALSE, Route117_PokemonDayCare_EventScript_CustomizationNoMoney
        callnative Script_SetSelectedEggAbility
        goto_if_eq VAR_RESULT, FALSE, Route117_PokemonDayCare_EventScript_AbilityUnavailable
        playse SE_SHOP
        removemoney 5000
        updatemoneybox
        waitse
        hidemoneybox
        msgbox Route117_PokemonDayCare_Text_AbilityDone, MSGBOX_DEFAULT
        goto Route117_PokemonDayCare_EventScript_EggCustomizeMenu
        end

Route117_PokemonDayCare_EventScript_AbilityUnavailable::
        hidemoneybox
        msgbox Route117_PokemonDayCare_Text_AbilityUnavailable, MSGBOX_DEFAULT
        goto Route117_PokemonDayCare_EventScript_EggCustomizeMenu
        end

@ ------------------------------------------------------------
@ GENDER
@ ------------------------------------------------------------

Route117_PokemonDayCare_EventScript_GenderMenu::
        callnative Script_CanCustomizeSelectedEggGender
        goto_if_eq VAR_RESULT, FALSE, Route117_PokemonDayCare_EventScript_GenderLocked

        msgbox Route117_PokemonDayCare_Text_ChooseGender, MSGBOX_DEFAULT
        dynmultichoice 0, 0, FALSE, 2, 0, DYN_MULTICHOICE_CB_NONE, Route117_PokemonDayCare_Text_GenderMale, Route117_PokemonDayCare_Text_GenderFemale, Route117_PokemonDayCare_Text_CustomBack
        goto_if_eq VAR_RESULT, MULTI_B_PRESSED, Route117_PokemonDayCare_EventScript_EggCustomizeMenu
        goto_if_eq VAR_RESULT, 2, Route117_PokemonDayCare_EventScript_EggCustomizeMenu
        copyvar VAR_0x8005, VAR_RESULT

        showmoneybox 0, 0
        msgbox Route117_PokemonDayCare_Text_GenderPrice, MSGBOX_YESNO
        goto_if_eq VAR_RESULT, NO, Route117_PokemonDayCare_EventScript_CancelPaidCustomization
        checkmoney 5000
        goto_if_eq VAR_RESULT, FALSE, Route117_PokemonDayCare_EventScript_CustomizationNoMoney
        callnative Script_SetSelectedEggGender
        goto_if_eq VAR_RESULT, FALSE, Route117_PokemonDayCare_EventScript_CustomizationFailed
        playse SE_SHOP
        removemoney 5000
        updatemoneybox
        waitse
        hidemoneybox
        msgbox Route117_PokemonDayCare_Text_GenderDone, MSGBOX_DEFAULT
        goto Route117_PokemonDayCare_EventScript_EggCustomizeMenu
        end

Route117_PokemonDayCare_EventScript_GenderLocked::
        msgbox Route117_PokemonDayCare_Text_GenderLocked, MSGBOX_DEFAULT
        goto Route117_PokemonDayCare_EventScript_EggCustomizeMenu
        end

@ ------------------------------------------------------------
@ POKE BALL
@ ------------------------------------------------------------

Route117_PokemonDayCare_EventScript_BallMenu::
        msgbox Route117_PokemonDayCare_Text_ChooseBall, MSGBOX_DEFAULT

        dynmultipush Route117_PokemonDayCare_Text_BallPoke, BALL_POKE
        dynmultipush Route117_PokemonDayCare_Text_BallGreat, BALL_GREAT
        dynmultipush Route117_PokemonDayCare_Text_BallUltra, BALL_ULTRA
        dynmultipush Route117_PokemonDayCare_Text_BallPremier, BALL_PREMIER
        dynmultipush Route117_PokemonDayCare_Text_BallHeal, BALL_HEAL
        dynmultipush Route117_PokemonDayCare_Text_BallNet, BALL_NET
        dynmultipush Route117_PokemonDayCare_Text_BallNest, BALL_NEST
        dynmultipush Route117_PokemonDayCare_Text_BallDive, BALL_DIVE
        dynmultipush Route117_PokemonDayCare_Text_BallDusk, BALL_DUSK
        dynmultipush Route117_PokemonDayCare_Text_BallTimer, BALL_TIMER
        dynmultipush Route117_PokemonDayCare_Text_BallQuick, BALL_QUICK
        dynmultipush Route117_PokemonDayCare_Text_BallRepeat, BALL_REPEAT
        dynmultipush Route117_PokemonDayCare_Text_BallLuxury, BALL_LUXURY
        dynmultipush Route117_PokemonDayCare_Text_BallLevel, BALL_LEVEL
        dynmultipush Route117_PokemonDayCare_Text_BallLure, BALL_LURE
        dynmultipush Route117_PokemonDayCare_Text_BallMoon, BALL_MOON
        dynmultipush Route117_PokemonDayCare_Text_BallFriend, BALL_FRIEND
        dynmultipush Route117_PokemonDayCare_Text_BallLove, BALL_LOVE
        dynmultipush Route117_PokemonDayCare_Text_BallFast, BALL_FAST
        dynmultipush Route117_PokemonDayCare_Text_BallHeavy, BALL_HEAVY
        dynmultipush Route117_PokemonDayCare_Text_BallDream, BALL_DREAM
        dynmultipush Route117_PokemonDayCare_Text_BallSafari, BALL_SAFARI
        dynmultipush Route117_PokemonDayCare_Text_BallSport, BALL_SPORT
        dynmultipush Route117_PokemonDayCare_Text_BallPark, BALL_PARK
        dynmultipush Route117_PokemonDayCare_Text_BallBeast, BALL_BEAST
        dynmultipush Route117_PokemonDayCare_Text_CustomBack, 255
        dynmultistack 0, 0, FALSE, 6, 0, 0, DYN_MULTICHOICE_CB_NONE

        goto_if_eq VAR_RESULT, MULTI_B_PRESSED, Route117_PokemonDayCare_EventScript_EggCustomizeMenu
        goto_if_eq VAR_RESULT, 255, Route117_PokemonDayCare_EventScript_EggCustomizeMenu
        copyvar VAR_0x8005, VAR_RESULT

        showmoneybox 0, 0
        msgbox Route117_PokemonDayCare_Text_BallPrice, MSGBOX_YESNO
        goto_if_eq VAR_RESULT, NO, Route117_PokemonDayCare_EventScript_CancelPaidCustomization
        checkmoney 2500
        goto_if_eq VAR_RESULT, FALSE, Route117_PokemonDayCare_EventScript_CustomizationNoMoney
        playse SE_SHOP
        removemoney 2500
        updatemoneybox
        waitse
        callnative Script_SetSelectedEggBall
        goto_if_eq VAR_RESULT, FALSE, Route117_PokemonDayCare_EventScript_CustomizationFailed
        hidemoneybox
        msgbox Route117_PokemonDayCare_Text_BallDone, MSGBOX_DEFAULT
        goto Route117_PokemonDayCare_EventScript_EggCustomizeMenu
        end

@ ------------------------------------------------------------
@ SHARED PURCHASE RESULTS
@ ------------------------------------------------------------

Route117_PokemonDayCare_EventScript_LavaridgeEggSisterExit::
        setvar VAR_TEMP_2, 0
        msgbox Route117_PokemonDayCare_Text_LavaridgeEggSisterBye, MSGBOX_DEFAULT
        releaseall
        end

Route117_PokemonDayCare_EventScript_CancelPaidCustomization::
        hidemoneybox
        goto Route117_PokemonDayCare_EventScript_EggCustomizeMenu
        end

Route117_PokemonDayCare_EventScript_CustomizationNoMoney::
        hidemoneybox
        msgbox Route117_PokemonDayCare_Text_CustomizationNoMoney, MSGBOX_DEFAULT
        goto Route117_PokemonDayCare_EventScript_EggCustomizeMenu
        end

Route117_PokemonDayCare_EventScript_CustomizationFailed::
        hidemoneybox
        msgbox Route117_PokemonDayCare_Text_CustomizationFailed, MSGBOX_DEFAULT
        goto Route117_PokemonDayCare_EventScript_EggCustomizeMenu
        end

@ ============================================================
@ TEXT
@ ============================================================

Route117_PokemonDayCare_Text_LavaridgeEggSisterBye:
        .string "All right.\p"
        .string "Come see me anytime before your\n"
        .string "EGG hatches.$"

Route117_PokemonDayCare_Text_EggMoveIntro:
        .string "I study how POKéMON learn moves\n"
        .string "from one another.\p"
        .string "Some techniques are called\n"
        .string "EGG MOVES.\p"
        .string "A POKéMON normally cannot learn\n"
        .string "them just by leveling up.\p"
        .string "But a MIRROR HERB can help.\p"
        .string "Give the HERB to the POKéMON\n"
        .string "you want to teach.\p"
        .string "Make sure it has an empty move\n"
        .string "slot, then leave it here with a\l"
        .string "POKéMON that knows one of its\l"
        .string "EGG MOVES.\p"
        .string "They will handle the rest.\p"
        .string "Here. Try it yourself.$"

Route117_PokemonDayCare_Text_FirstMirrorHerb:
        .string "That first MIRROR HERB is free.\p"
        .string "If you need another one later,\n"
        .string "I keep extras here.$"

Route117_PokemonDayCare_Text_MirrorHerbBagFull:
        .string "Your BAG is full.\p"
        .string "Make some room and come back.\n"
        .string "I'll keep your MIRROR HERB here.$"

Route117_PokemonDayCare_Text_DeleteMoveOffer:
        .string "Need to make room for an\n"
        .string "EGG MOVE?$"

Route117_PokemonDayCare_Text_BuyMirrorHerbOffer:
        .string "Need another MIRROR HERB?$"

Route117_PokemonDayCare_Text_MirrorHerbShop:
        .string "They're ¥1,500 each.$"

Route117_PokemonDayCare_Text_ComeBackAnytime:
        .string "Come back anytime you want to\n"
        .string "work on EGG MOVES.$"

Route117_PokemonDayCare_Text_WhichMonShouldForget:
        .string "Which POKéMON needs some room?$"

Route117_PokemonDayCare_Text_WhichMoveShouldBeForgotten:
        .string "Which move should it forget?$"

Route117_PokemonDayCare_Text_MonOnlyKnowsOneMove:
        .string "{STR_VAR_1} only knows one move.\p"
        .string "I can't leave it with nothing.$"

Route117_PokemonDayCare_Text_MonsMoveShouldBeForgotten:
        .string "Forget {STR_VAR_1}'s\n"
        .string "{STR_VAR_2}?$"

Route117_PokemonDayCare_Text_MonHasForgottenMove:
        .string "Done.\p"
        .string "{STR_VAR_1} forgot\n"
        .string "{STR_VAR_2}.$"

Route117_PokemonDayCare_Text_EggCantForgetMoves:
        .string "That's an EGG.\p"
        .string "Let's wait until it hatches.$"

Route117_PokemonDayCare_Text_CantForgetSurf:
        .string "{STR_VAR_1} can't forget\n"
        .string "SURF right now.$"


@ ============================================================
@ SPECIALIST SERVICE MENU
@ ============================================================

Route117_PokemonDayCare_Text_ServiceMenuPrompt:
        .string "What can I help you with?$"

Route117_PokemonDayCare_Text_ServiceDeleteMove:
        .string "Delete a Move$"

Route117_PokemonDayCare_Text_ServiceMirrorHerb:
        .string "Mirror Herb$"

Route117_PokemonDayCare_Text_ServiceCustomizeEgg:
        .string "Customize an Egg$"

Route117_PokemonDayCare_Text_ServiceCancel:
        .string "Never mind$"

Route117_PokemonDayCare_Text_ChooseEgg:
        .string "Choose the EGG you want me to\n"
        .string "work with.$"

Route117_PokemonDayCare_Text_NotAnEgg:
        .string "That is not an EGG.\p"
        .string "I can only customize a POKéMON\n"
        .string "before it hatches.$"

Route117_PokemonDayCare_Text_CustomizeWhat:
        .string "What would you like to customize?$"

Route117_PokemonDayCare_Text_CustomAbility:
        .string "Ability$"

Route117_PokemonDayCare_Text_CustomGender:
        .string "Gender$"

Route117_PokemonDayCare_Text_CustomBall:
        .string "Poké Ball$"

Route117_PokemonDayCare_Text_CustomBack:
        .string "Back$"

Route117_PokemonDayCare_Text_ChooseNature:
        .string "Choose the Nature you want.\p"
        .string "I will keep its gender the same.$"

Route117_PokemonDayCare_Text_NaturePrice:
        .string "Nature customization costs\n"
        .string "5,000. Is that okay?$"

Route117_PokemonDayCare_Text_NatureDone:
        .string "Done.\p"
        .string "Its Nature is all set.$"

Route117_PokemonDayCare_Text_ChooseAbility:
        .string "Choose the Ability type you want.$"

Route117_PokemonDayCare_Text_AbilityInnate:
        .string "Innate Ability$"

Route117_PokemonDayCare_Text_AbilityHidden:
        .string "Hidden Ability$"

Route117_PokemonDayCare_Text_AbilityPrice:
        .string "Ability customization costs\n"
        .string "5,000. Is that okay?$"

Route117_PokemonDayCare_Text_AbilityDone:
        .string "Done.\p"
        .string "Its Ability is all set.$"

Route117_PokemonDayCare_Text_AbilityUnavailable:
        .string "That Ability type is not available\n"
        .string "for this species.$"

Route117_PokemonDayCare_Text_ChooseGender:
        .string "Choose the gender you want.\p"
        .string "I will keep its Nature the same.$"

Route117_PokemonDayCare_Text_GenderPrice:
        .string "Gender customization costs\n"
        .string "5,000. Is that okay?$"

Route117_PokemonDayCare_Text_GenderDone:
        .string "Done.\p"
        .string "Its gender is all set.$"

Route117_PokemonDayCare_Text_GenderLocked:
        .string "This species cannot switch between\n"
        .string "male and female.$"

Route117_PokemonDayCare_Text_ChooseBall:
        .string "Choose the Poké Ball you want it\n"
        .string "to hatch from.$"

Route117_PokemonDayCare_Text_BallPrice:
        .string "Poké Ball customization costs\n"
        .string "2,500. Is that okay?$"

Route117_PokemonDayCare_Text_BallDone:
        .string "Done.\p"
        .string "That will be its Poké Ball.$"

Route117_PokemonDayCare_Text_CustomizationNoMoney:
        .string "You do not have enough money for\n"
        .string "that service.$"

Route117_PokemonDayCare_Text_CustomizationFailed:
        .string "Hmm... I cannot make that change\n"
        .string "to this EGG.$"

@ Nature names

Route117_PokemonDayCare_Text_NatureHardy:
        .string "Hardy$"
Route117_PokemonDayCare_Text_NatureLonely:
        .string "Lonely$"
Route117_PokemonDayCare_Text_NatureBrave:
        .string "Brave$"
Route117_PokemonDayCare_Text_NatureAdamant:
        .string "Adamant$"
Route117_PokemonDayCare_Text_NatureNaughty:
        .string "Naughty$"
Route117_PokemonDayCare_Text_NatureBold:
        .string "Bold$"
Route117_PokemonDayCare_Text_NatureDocile:
        .string "Docile$"
Route117_PokemonDayCare_Text_NatureRelaxed:
        .string "Relaxed$"
Route117_PokemonDayCare_Text_NatureImpish:
        .string "Impish$"
Route117_PokemonDayCare_Text_NatureLax:
        .string "Lax$"
Route117_PokemonDayCare_Text_NatureTimid:
        .string "Timid$"
Route117_PokemonDayCare_Text_NatureHasty:
        .string "Hasty$"
Route117_PokemonDayCare_Text_NatureSerious:
        .string "Serious$"
Route117_PokemonDayCare_Text_NatureJolly:
        .string "Jolly$"
Route117_PokemonDayCare_Text_NatureNaive:
        .string "Naive$"
Route117_PokemonDayCare_Text_NatureModest:
        .string "Modest$"
Route117_PokemonDayCare_Text_NatureMild:
        .string "Mild$"
Route117_PokemonDayCare_Text_NatureQuiet:
        .string "Quiet$"
Route117_PokemonDayCare_Text_NatureBashful:
        .string "Bashful$"
Route117_PokemonDayCare_Text_NatureRash:
        .string "Rash$"
Route117_PokemonDayCare_Text_NatureCalm:
        .string "Calm$"
Route117_PokemonDayCare_Text_NatureGentle:
        .string "Gentle$"
Route117_PokemonDayCare_Text_NatureSassy:
        .string "Sassy$"
Route117_PokemonDayCare_Text_NatureCareful:
        .string "Careful$"
Route117_PokemonDayCare_Text_NatureQuirky:
        .string "Quirky$"

@ Gender names

Route117_PokemonDayCare_Text_GenderMale:
        .string "Male$"

Route117_PokemonDayCare_Text_GenderFemale:
        .string "Female$"

@ Ball names

Route117_PokemonDayCare_Text_BallPoke:
        .string "Poké Ball$"
Route117_PokemonDayCare_Text_BallGreat:
        .string "Great Ball$"
Route117_PokemonDayCare_Text_BallUltra:
        .string "Ultra Ball$"
Route117_PokemonDayCare_Text_BallPremier:
        .string "Premier Ball$"
Route117_PokemonDayCare_Text_BallHeal:
        .string "Heal Ball$"
Route117_PokemonDayCare_Text_BallNet:
        .string "Net Ball$"
Route117_PokemonDayCare_Text_BallNest:
        .string "Nest Ball$"
Route117_PokemonDayCare_Text_BallDive:
        .string "Dive Ball$"
Route117_PokemonDayCare_Text_BallDusk:
        .string "Dusk Ball$"
Route117_PokemonDayCare_Text_BallTimer:
        .string "Timer Ball$"
Route117_PokemonDayCare_Text_BallQuick:
        .string "Quick Ball$"
Route117_PokemonDayCare_Text_BallRepeat:
        .string "Repeat Ball$"
Route117_PokemonDayCare_Text_BallLuxury:
        .string "Luxury Ball$"
Route117_PokemonDayCare_Text_BallLevel:
        .string "Level Ball$"
Route117_PokemonDayCare_Text_BallLure:
        .string "Lure Ball$"
Route117_PokemonDayCare_Text_BallMoon:
        .string "Moon Ball$"
Route117_PokemonDayCare_Text_BallFriend:
        .string "Friend Ball$"
Route117_PokemonDayCare_Text_BallLove:
        .string "Love Ball$"
Route117_PokemonDayCare_Text_BallFast:
        .string "Fast Ball$"
Route117_PokemonDayCare_Text_BallHeavy:
        .string "Heavy Ball$"
Route117_PokemonDayCare_Text_BallDream:
        .string "Dream Ball$"
Route117_PokemonDayCare_Text_BallSafari:
        .string "Safari Ball$"
Route117_PokemonDayCare_Text_BallSport:
        .string "Sport Ball$"
Route117_PokemonDayCare_Text_BallPark:
        .string "Park Ball$"
Route117_PokemonDayCare_Text_BallBeast:
        .string "Beast Ball$"

