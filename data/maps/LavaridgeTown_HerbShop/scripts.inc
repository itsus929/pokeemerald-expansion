LavaridgeTown_HerbShop_MapScripts::
	.byte 0

LavaridgeTown_HerbShop_EventScript_Clerk::
	lock
	faceplayer
	message LavaridgeTown_HerbShop_Text_WelcomeToHerbShop
	waitmessage
	pokemart LavaridgeTown_HerbShop_Pokemart
	msgbox gText_PleaseComeAgain, MSGBOX_DEFAULT
	release
	end

	.align 2
LavaridgeTown_HerbShop_Pokemart:
	.2byte ITEM_ENERGY_POWDER
	.2byte ITEM_ENERGY_ROOT
	.2byte ITEM_HEAL_POWDER
	.2byte ITEM_REVIVAL_HERB
        .2byte ITEM_ABILITY_CAPSULE
        .2byte ITEM_ABILITY_PATCH
	pokemartlistend

LavaridgeTown_HerbShop_EventScript_NatureSpecialist::
        lock
        faceplayer
        msgbox LavaridgeTown_HerbShop_Text_NatureIntro, MSGBOX_YESNO
        goto_if_eq VAR_RESULT, NO, LavaridgeTown_HerbShop_EventScript_NatureDecline

        getpartysize
        goto_if_eq VAR_RESULT, 0, LavaridgeTown_HerbShop_EventScript_NatureNoPokemon
        msgbox LavaridgeTown_HerbShop_Text_ChoosePokemon, MSGBOX_DEFAULT
        chooseboxmon SELECT_PC_MON_NORMAL
        waitstate
        goto_if_eq VAR_0x8004, PARTY_NOTHING_CHOSEN, LavaridgeTown_HerbShop_EventScript_NatureDecline
        special IsSelectedMonEgg
        goto_if_eq VAR_RESULT, TRUE, LavaridgeTown_HerbShop_EventScript_NatureEgg

LavaridgeTown_HerbShop_EventScript_NatureMenu::
        msgbox LavaridgeTown_HerbShop_Text_ChooseNature, MSGBOX_DEFAULT

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

        goto_if_eq VAR_RESULT, MULTI_B_PRESSED, LavaridgeTown_HerbShop_EventScript_NatureDecline
        goto_if_eq VAR_RESULT, 255, LavaridgeTown_HerbShop_EventScript_NatureDecline
        copyvar VAR_0x8005, VAR_RESULT

        showmoneybox 0, 0
        msgbox LavaridgeTown_HerbShop_Text_NaturePrice, MSGBOX_YESNO
        goto_if_eq VAR_RESULT, NO, LavaridgeTown_HerbShop_EventScript_NatureCancelPurchase
        checkmoney 5000
        goto_if_eq VAR_RESULT, FALSE, LavaridgeTown_HerbShop_EventScript_NatureNoMoney

        callnative Script_SetSelectedMonNature
        goto_if_eq VAR_RESULT, FALSE, LavaridgeTown_HerbShop_EventScript_NatureFailed

        playse SE_SHOP
        removemoney 5000
        updatemoneybox
        waitse
        hidemoneybox
        msgbox LavaridgeTown_HerbShop_Text_NatureDone, MSGBOX_DEFAULT
        release
        end

LavaridgeTown_HerbShop_EventScript_NatureCancelPurchase::
        hidemoneybox
        goto LavaridgeTown_HerbShop_EventScript_NatureMenu
        end

LavaridgeTown_HerbShop_EventScript_NatureNoMoney::
        hidemoneybox
        msgbox LavaridgeTown_HerbShop_Text_NatureNoMoney, MSGBOX_DEFAULT
        release
        end

LavaridgeTown_HerbShop_EventScript_NatureFailed::
        hidemoneybox
        msgbox LavaridgeTown_HerbShop_Text_NatureFailed, MSGBOX_DEFAULT
        release
        end

LavaridgeTown_HerbShop_EventScript_NatureEgg::
        msgbox LavaridgeTown_HerbShop_Text_NatureEgg, MSGBOX_DEFAULT
        release
        end

LavaridgeTown_HerbShop_EventScript_NatureNoPokemon::
        msgbox LavaridgeTown_HerbShop_Text_NatureNoPokemon, MSGBOX_DEFAULT
        release
        end

LavaridgeTown_HerbShop_EventScript_NatureDecline::
        msgbox LavaridgeTown_HerbShop_Text_NatureComeBack, MSGBOX_DEFAULT
        release
        end

LavaridgeTown_HerbShop_EventScript_ExpertM::
	msgbox LavaridgeTown_HerbShop_Text_HerbalMedicineWorksButMonWillDislike, MSGBOX_NPC
	end

LavaridgeTown_HerbShop_EventScript_OldMan::
	lock
	faceplayer
	goto_if_set FLAG_RECEIVED_CHARCOAL, LavaridgeTown_HerbShop_EventScript_ExplainCharcoal
	msgbox LavaridgeTown_HerbShop_Text_YouveComeToLookAtHerbalMedicine, MSGBOX_DEFAULT
	giveitem ITEM_CHARCOAL
	goto_if_eq VAR_RESULT, FALSE, Common_EventScript_ShowBagIsFull
	setflag FLAG_RECEIVED_CHARCOAL
	release
	end

LavaridgeTown_HerbShop_EventScript_ExplainCharcoal::
	msgbox LavaridgeTown_HerbShop_Text_ExplainCharcoal, MSGBOX_DEFAULT
	release
	end

LavaridgeTown_HerbShop_Text_WelcomeToHerbShop:
	.string "Welcome to the HERB SHOP, home of\n"
	.string "effective and inexpensive medicine!$"

LavaridgeTown_HerbShop_Text_YouveComeToLookAtHerbalMedicine:
	.string "You've come to look at herbal medicine\n"
	.string "in LAVARIDGE?\p"
	.string "That's rather commendable.\p"
	.string "I like you! Take this!$"

LavaridgeTown_HerbShop_Text_ExplainCharcoal:
	.string "That CHARCOAL I gave you, it's used\n"
	.string "for making herbal medicine.\p"
	.string "It also does wonders when held by\n"
	.string "a POKéMON.\p"
	.string "It intensifies the power of FIRE-type\n"
	.string "moves.$"

LavaridgeTown_HerbShop_Text_HerbalMedicineWorksButMonWillDislike:
	.string "Herbal medicine works impressively well.\n"
	.string "But your POKéMON will dislike you for it.\l"
	.string "It must be horribly bitter!$"


LavaridgeTown_HerbShop_Text_NatureIntro:
        .string "A POKéMON's NATURE can shape how\n"
        .string "its strengths develop.\p"
        .string "For ¥5,000, I can help change the\n"
        .string "NATURE of one of your POKéMON.\p"
        .string "Would you like me to?$"

LavaridgeTown_HerbShop_Text_ChoosePokemon:
        .string "Which POKéMON would you like me to\n"
        .string "work with?$"

LavaridgeTown_HerbShop_Text_ChooseNature:
        .string "Which NATURE would you like?$"

LavaridgeTown_HerbShop_Text_NaturePrice:
        .string "That will be ¥5,000.\p"
        .string "Is that all right?$"

LavaridgeTown_HerbShop_Text_NatureDone:
        .string "There we are.\p"
        .string "Your POKéMON's NATURE has changed.$"

LavaridgeTown_HerbShop_Text_NatureNoMoney:
        .string "You don't have enough money.\p"
        .string "Come back whenever you're ready.$"

LavaridgeTown_HerbShop_Text_NatureFailed:
        .string "I'm afraid I can't change the\n"
        .string "NATURE of that POKéMON.$"

LavaridgeTown_HerbShop_Text_NatureComeBack:
        .string "Of course.\p"
        .string "Come see me if you change your mind.$"

LavaridgeTown_HerbShop_Text_NatureEgg:
        .string "That POKéMON hasn't hatched yet.\p"
        .string "Come see me after it does.$"

LavaridgeTown_HerbShop_Text_NatureNoPokemon:
        .string "You don't have any POKéMON with you.\p"
        .string "Come back when you do.$"

