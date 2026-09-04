SafariZone_SecretHouse_Frlg_MapScripts::
    .byte 0


SafariZone_SecretHouse_Frlg_EventScript_Attendant::
    lock
    faceplayer

    goto_if_set FLAG_RECEIVED_SAFARI_SECRET_HOUSE_REWARD, SafariZone_SecretHouse_Frlg_EventScript_AlreadyReceived

    msgbox SafariZone_SecretHouse_Frlg_Text_Congratulations, MSGBOX_DEFAULT

    giveitem ITEM_ABILITY_CAPSULE
    goto_if_eq VAR_RESULT, FALSE, SafariZone_SecretHouse_Frlg_EventScript_BagFull

    setflag FLAG_RECEIVED_SAFARI_SECRET_HOUSE_REWARD

    msgbox SafariZone_SecretHouse_Frlg_Text_ExplainCapsule, MSGBOX_DEFAULT
    release
    end


SafariZone_SecretHouse_Frlg_EventScript_BagFull::
    msgbox SafariZone_SecretHouse_Frlg_Text_BagFull, MSGBOX_DEFAULT
    release
    end


SafariZone_SecretHouse_Frlg_EventScript_AlreadyReceived::
    msgbox SafariZone_SecretHouse_Frlg_Text_AlreadyReceived, MSGBOX_DEFAULT
    release
    end


SafariZone_SecretHouse_Frlg_Text_Congratulations:
    .string "You actually made it!\p"
    .string "Most people turn around long\n"
    .string "before they find this place.\p"
    .string "You earned something special.$"


SafariZone_SecretHouse_Frlg_Text_ExplainCapsule:
    .string "That's an Ability Capsule.\p"
    .string "It can change a Pokemon's\n"
    .string "Ability.\p"
    .string "Use it wisely!$"


SafariZone_SecretHouse_Frlg_Text_BagFull:
    .string "Oh! Your Bag is full.\p"
    .string "Make some room and come back.\n"
    .string "I'll hold onto your prize.$"


SafariZone_SecretHouse_Frlg_Text_AlreadyReceived:
    .string "Enjoy that Ability Capsule!\p"
    .string "And hey...\n"
    .string "you found the Secret House.$"
