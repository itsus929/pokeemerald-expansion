FallarborTown_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, FallarborTown_OnTransition
	.byte 0

FallarborTown_OnTransition:
	setflag FLAG_VISITED_FALLARBOR_TOWN
	setvar VAR_CONTEST_HALL_STATE, 0
	clearflag FLAG_CONTEST_SKETCH_CREATED
	end

FallarborTown_EventScript_ExpertM::
	lock
	faceplayer
	goto_if_set FLAG_DEFEATED_EVIL_TEAM_MT_CHIMNEY, FallarborTown_EventScript_ExpertMNormal
	msgbox FallarborTown_Text_ShadyCharactersCozmosHome, MSGBOX_DEFAULT
	release
	end

FallarborTown_EventScript_ExpertMNormal::
	msgbox FallarborTown_Text_RegionKnownForMeteors, MSGBOX_DEFAULT
	release
	end

FallarborTown_EventScript_Girl::
	msgbox FallarborTown_Text_MyPreciousAzurill, MSGBOX_NPC
	end

FallarborTown_EventScript_Gentleman::
	msgbox FallarborTown_Text_HaveYouChallengedFlannery, MSGBOX_NPC
	end

FallarborTown_EventScript_Azurill::
	lock
	faceplayer
	waitse
	playmoncry SPECIES_AZURILL, CRY_MODE_NORMAL
	msgbox FallarborTown_Text_Azurill, MSGBOX_DEFAULT
	waitmoncry
	release
	end

FallarborTown_EventScript_BattleTentSign::
	msgbox FallarborTown_Text_BattleTentSign, MSGBOX_SIGN
	end

FallarborTown_EventScript_TownSign::
	msgbox FallarborTown_Text_TownSign, MSGBOX_SIGN
	end

FallarborTown_EventScript_MoveTutorSign::
	msgbox FallarborTown_Text_MoveTutorSign, MSGBOX_SIGN
	end

FallarborTown_Text_ShadyCharactersCozmosHome:
	.string "Something's happening,\n"
	.string "and I don't like it!\p"
	.string "I've seen shady characters wandering\n"
	.string "in and out of PROF. COZMO's home…$"

FallarborTown_Text_RegionKnownForMeteors:
	.string "This region's been known for meteors\n"
	.string "since the olden days.\p"
	.string "They say METEOR FALLS was gouged out\n"
	.string "by a falling meteorite long ago.$"

FallarborTown_Text_MyPreciousAzurill:
	.string "See! Take a look!\n"
	.string "This is my precious AZURILL!\p"
	.string "It's slick and smooth and plushy, too!$"

FallarborTown_Text_Azurill:
	.string "AZURILL: Rooreelooo.$"

FallarborTown_Text_HaveYouChallengedFlannery:
	.string "Have you already challenged FLANNERY,\n"
	.string "the KEEPER of LAVARIDGE SHRINE?\p"
	.string "The girl's grandfather was famous.\n"
	.string "He was one of the ELITE FOUR in the\l"
	.string "POKéMON LEAGUE at one point.\p"
	.string "It wouldn't surprise me to see FLANNERY\n"
	.string "become a great TRAINER in her own\l"
	.string "right.$"

FallarborTown_Text_BattleTentSign:
	.string "BATTLE TENT FALLARBOR SITE\n"
	.string "“May the Greatest Teams Gather!”$"

FallarborTown_Text_TownSign:
	.string "FALLARBOR TOWN\n"
	.string "“A farm community with small gardens.”$"

FallarborTown_Text_MoveTutorSign:
	.string "EVOLUTION SPECIALIST\n"
	.string "“Solutions for unusual evolutions.”$"


@ =============================================================================
@ BREEDER GRACE - REPEATABLE TRAINING
@ =============================================================================

FallarborTown_EventScript_BreederGrace::
    lock
    faceplayer

    msgbox FallarborTown_Text_BreederGraceOffer, MSGBOX_YESNO
    goto_if_eq VAR_RESULT, NO, FallarborTown_EventScript_BreederGraceDecline

    trainerbattle_single TRAINER_BREEDER_GRACE_FALLARBOR, FallarborTown_Text_BreederGraceIntro, FallarborTown_Text_BreederGraceDefeat

    cleartrainerflag TRAINER_BREEDER_GRACE_FALLARBOR

    @ Normal Lv.29 Breeder payout = ₽1,160.
    @ Training bonus brings each victory to ₽1,500 total.
    addmoney 340

    msgbox FallarborTown_Text_BreederGraceAfterBattle, MSGBOX_DEFAULT
    release
    end

FallarborTown_EventScript_BreederGraceDecline::
    msgbox FallarborTown_Text_BreederGraceDecline, MSGBOX_DEFAULT
    release
    end

FallarborTown_Text_BreederGraceOffer:
    .string "GRACE: You must be the TRAINER I've\n"
    .string "been hearing about.\p"
    .string "{PLAYER}: Please don't say Faith told you.\p"
    .string "GRACE: Faith told me.\p"
    .string "{PLAYER}: Of course she did.\p"
    .string "GRACE: I'm Grace.\p"
    .string "My AUDINO are a little stronger than\n"
    .string "hers.\p"
    .string "Want to train?$"

FallarborTown_Text_BreederGraceIntro:
    .string "GRACE: Let's see how you're coming\n"
    .string "along!$"

FallarborTown_Text_BreederGraceDefeat:
    .string "GRACE: Faith wasn't exaggerating.$"

FallarborTown_Text_BreederGraceAfterBattle:
    .string "GRACE: Nice work.\p"
    .string "My AUDINO will be ready whenever you\n"
    .string "want to train again.$"

FallarborTown_Text_BreederGraceDecline:
    .string "GRACE: No problem.\p"
    .string "I'll be right here when you're ready.$"
