FuchsiaCity_Mart_Frlg_MapScripts::
    .byte 0


FuchsiaCity_Mart_Frlg_EventScript_Clerk::
    lock
    faceplayer
    message gText_HowMayIServeYou
    waitmessage
    pokemart FuchsiaCity_Mart_Frlg_Pokemart
    msgbox gText_PleaseComeAgain, MSGBOX_DEFAULT
    release
    end


    .align 2
FuchsiaCity_Mart_Frlg_Pokemart:
    .2byte ITEM_ULTRA_BALL
    .2byte ITEM_GREAT_BALL
    .2byte ITEM_HYPER_POTION
    .2byte ITEM_SUPER_POTION
    .2byte ITEM_FULL_HEAL
    .2byte ITEM_REVIVE
    .2byte ITEM_SUPER_REPEL
    pokemartlistend


FuchsiaCity_Mart_Frlg_EventScript_Gentleman::
    msgbox FuchsiaCity_Mart_Frlg_Text_Gentleman, MSGBOX_NPC
    end


FuchsiaCity_Mart_Frlg_EventScript_Cooltrainer::
    msgbox FuchsiaCity_Mart_Frlg_Text_Cooltrainer, MSGBOX_NPC
    end


FuchsiaCity_Mart_Frlg_Text_Gentleman:
    .string "One should always prepare before\n"
    .string "wandering into tall grass.\p"
    .string "I say this from experience.$"


FuchsiaCity_Mart_Frlg_Text_Cooltrainer:
    .string "I came in for one thing.\p"
    .string "My Bag says I bought seven.$"
