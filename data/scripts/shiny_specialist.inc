@ Global Shiny Specialist service
@ Available from Fallarbor onward

@ ============================================================
@ SHINY SPECIALIST
@ ============================================================

ShinySpecialist_EventScript::
        lock
        faceplayer
        showmoneybox 0, 0
        msgbox ShinySpecialist_TextIntro, MSGBOX_YESNO
        goto_if_eq VAR_RESULT, NO, ShinySpecialist_EventScriptDecline
        msgbox ShinySpecialist_TextChoose, MSGBOX_DEFAULT
        chooseboxmon SELECT_PC_MON_NORMAL
        waitstate
        goto_if_eq VAR_0x8004, PARTY_NOTHING_CHOSEN, ShinySpecialist_EventScriptDecline
        special IsSelectedMonEgg
        goto_if_eq VAR_RESULT, TRUE, ShinySpecialist_EventScriptEgg
        special Script_IsSelectedMonShiny
        goto_if_eq VAR_RESULT, TRUE, ShinySpecialist_EventScriptAlreadyShiny
        msgbox ShinySpecialist_TextConfirm, MSGBOX_YESNO
        goto_if_eq VAR_RESULT, NO, ShinySpecialist_EventScriptDecline
        checkmoney 30000
        goto_if_eq VAR_RESULT, FALSE, ShinySpecialist_EventScriptNoMoney
        playse SE_SHOP
        removemoney 30000
        updatemoneybox
        waitse
        special Script_MakeSelectedMonShiny
        msgbox ShinySpecialist_TextSuccess, MSGBOX_DEFAULT
        hidemoneybox
        release
        end

ShinySpecialist_EventScriptEgg::
        msgbox ShinySpecialist_TextEgg, MSGBOX_DEFAULT
        hidemoneybox
        release
        end

ShinySpecialist_EventScriptAlreadyShiny::
        msgbox ShinySpecialist_TextAlreadyShiny, MSGBOX_DEFAULT
        hidemoneybox
        release
        end

ShinySpecialist_EventScriptNoMoney::
        msgbox ShinySpecialist_TextNoMoney, MSGBOX_DEFAULT
        hidemoneybox
        release
        end

ShinySpecialist_EventScriptDecline::
        msgbox ShinySpecialist_TextDecline, MSGBOX_DEFAULT
        hidemoneybox
        release
        end

ShinySpecialist_TextIntro:
        .string "I provide a very rare treatment for\n"
        .string "POKéMON.\p"
        .string "It can bring out a brilliant radiance\n"
        .string "that lasts forever.\p"
        .string "The treatment costs 30,000.\n"
        .string "Interested?$"

ShinySpecialist_TextChoose:
        .string "Wonderful.\p"
        .string "Which POKéMON would you like me to\n"
        .string "treat?$"

ShinySpecialist_TextConfirm:
        .string "Once the treatment is complete,\n"
        .string "the change is permanent.\p"
        .string "Proceed for 30,000?$"

ShinySpecialist_TextEgg:
        .string "Oh, no.\p"
        .string "I won't perform the treatment on an\n"
        .string "EGG.\p"
        .string "Come back after it hatches.$"

ShinySpecialist_TextAlreadyShiny:
        .string "This POKéMON already has a brilliant\n"
        .string "radiance.\p"
        .string "There's nothing more for me to do.$"

ShinySpecialist_TextNoMoney:
        .string "I'm afraid you don't have enough.\p"
        .string "The treatment costs 30,000.$"

ShinySpecialist_TextSuccess:
        .string "There we are.\p"
        .string "The treatment was a complete success.\p"
        .string "Your POKéMON's radiance is now\n"
        .string "permanent.$"

ShinySpecialist_TextDecline:
        .string "Of course.\p"
        .string "Come back if you decide you want a\n"
        .string "little more sparkle.$"
