#include "global.h"
#include "battle_main.h"
#include "battle.h"
#include "battle_gfx_sfx_util.h"
#include "berry.h"
#include "caps.h"
#include "data.h"
#include "daycare.h"
#include "decompress.h"
#include "event_data.h"
#include "international_string_util.h"
#include "item.h"
#include "link.h"
#include "link_rfu.h"
#include "main.h"
#include "menu.h"
#include "overworld.h"
#include "ow_abilities.h"
#include "palette.h"
#include "party_menu.h"
#include "pokedex.h"
#include "pokemon.h"
#include "evolution_scene.h"
#include "pokemon_storage_system.h"
#include "random.h"
#include "random_mon_generation.h"
#include "script.h"
#include "sprite.h"
#include "string_util.h"
#include "tv.h"
#include "wild_encounter.h"
#include "constants/pokeball.h"
#include "constants/abilities.h"
#include "constants/items.h"
#include "constants/battle_frontier.h"

static void CB2_ReturnFromChooseHalfParty(void);
static void CB2_ReturnFromChooseBattleFrontierParty(void);
static void HealPlayerBoxes(void);

void HealPlayerParty(void)
{
    u32 i;
    for (i = 0; i < gPartiesCount[B_TRAINER_PLAYER]; i++)
        HealPokemon(&gParties[B_TRAINER_PLAYER][i]);
    if (OW_PC_HEAL >= GEN_8)
        HealPlayerBoxes();

    // Recharge Tera Orb, if possible.
    if (B_FLAG_TERA_ORB_CHARGED != 0 && CheckBagHasItem(ITEM_TERA_ORB, 1))
        FlagSet(B_FLAG_TERA_ORB_CHARGED);
}

static void HealPlayerBoxes(void)
{
    int boxId, boxPosition;
    struct BoxPokemon *boxMon;

    for (boxId = 0; boxId < TOTAL_BOXES_COUNT; boxId++)
    {
        for (boxPosition = 0; boxPosition < IN_BOX_COUNT; boxPosition++)
        {
            boxMon = &gPokemonStoragePtr->boxes[boxId][boxPosition];
            if (GetBoxMonData(boxMon, MON_DATA_SANITY_HAS_SPECIES))
                HealBoxPokemon(boxMon);
        }
    }
}

u8 ScriptGiveEgg(enum Species species)
{
    struct Pokemon mon;
    u8 isEgg;

    CreateEgg(&mon, species, TRUE);
    isEgg = TRUE;
    SetMonData(&mon, MON_DATA_IS_EGG, &isEgg);

    return GiveCapturedMonToPlayer(&mon);
}

void HasEnoughMonsForDoubleBattle(void)
{
    switch (GetMonsStateToDoubles())
    {
    case PLAYER_HAS_TWO_USABLE_MONS:
        gSpecialVar_Result = PLAYER_HAS_TWO_USABLE_MONS;
        break;
    case PLAYER_HAS_ONE_MON:
        gSpecialVar_Result = PLAYER_HAS_ONE_MON;
        break;
    case PLAYER_HAS_ONE_USABLE_MON:
        gSpecialVar_Result = PLAYER_HAS_ONE_USABLE_MON;
        break;
    }
}

static bool32 CheckPartyMonHasHeldItem(enum Item item)
{
    int i;

    for (i = 0; i < PARTY_SIZE; i++)
    {
        enum Species species = GetMonData(&gParties[B_TRAINER_PLAYER][i], MON_DATA_SPECIES_OR_EGG);
        if (species != SPECIES_NONE && species != SPECIES_EGG && GetMonData(&gParties[B_TRAINER_PLAYER][i], MON_DATA_HELD_ITEM) == item)
            return TRUE;
    }
    return FALSE;
}

bool8 DoesPartyHaveEnigmaBerry(void)
{
    bool8 hasItem = CheckPartyMonHasHeldItem(ITEM_ENIGMA_BERRY_E_READER);
    if (hasItem == TRUE)
        GetBerryNameByBerryType(BERRY_ID_ENGIMA_E_READER, gStringVar1);

    return hasItem;
}

void CreateScriptedWildMon(enum Species species, u8 level, enum Item item)
{
    u8 heldItem[2];

    ZeroEnemyPartyMons();
    u32 personality = GetMonPersonality(species,
        GetSynchronizedGender(STATIC_WILDMON_ORIGIN, species),
        GetSynchronizedNature(STATIC_WILDMON_ORIGIN, species),
        RANDOM_UNOWN_LETTER);
    CreateMonWithIVs(&gParties[B_TRAINER_OPPONENT_A][0], species, level, personality, OTID_STRUCT_PLAYER_ID, USE_RANDOM_IVS);
    GiveMonInitialMoveset(&gParties[B_TRAINER_OPPONENT_A][0]);
    if (item)
    {
        heldItem[0] = item;
        heldItem[1] = item >> 8;
        SetMonData(&gParties[B_TRAINER_OPPONENT_A][0], MON_DATA_HELD_ITEM, heldItem);
    }
}
void CreateScriptedDoubleWildMon(enum Species species1, u8 level1, enum Item item1, enum Species species2, u8 level2, enum Item item2)
{
    u8 heldItem1[2];
    u8 heldItem2[2];

    ZeroEnemyPartyMons();
    u32 personality = GetMonPersonality(species1,
        GetSynchronizedGender(STATIC_WILDMON_ORIGIN, species1),
        GetSynchronizedNature(STATIC_WILDMON_ORIGIN, species1),
        RANDOM_UNOWN_LETTER);
    CreateMonWithIVs(&gParties[B_TRAINER_OPPONENT_A][0], species1, level1, personality, OTID_STRUCT_PLAYER_ID, USE_RANDOM_IVS);
    GiveMonInitialMoveset(&gParties[B_TRAINER_OPPONENT_A][0]);
    if (item1)
    {
        heldItem1[0] = item1;
        heldItem1[1] = item1 >> 8;
        SetMonData(&gParties[B_TRAINER_OPPONENT_A][0], MON_DATA_HELD_ITEM, heldItem1);
    }

    personality = GetMonPersonality(species2,
        GetSynchronizedGender(STATIC_WILDMON_ORIGIN, species2),
        GetSynchronizedNature(STATIC_WILDMON_ORIGIN, species2),
        RANDOM_UNOWN_LETTER);
    CreateMonWithIVs(&gParties[B_TRAINER_OPPONENT_A][1], species2, level2, personality, OTID_STRUCT_PLAYER_ID, USE_RANDOM_IVS);
    GiveMonInitialMoveset(&gParties[B_TRAINER_OPPONENT_A][1]);
    if (item2)
    {
        heldItem2[0] = item2;
        heldItem2[1] = item2 >> 8;
        SetMonData(&gParties[B_TRAINER_OPPONENT_A][1], MON_DATA_HELD_ITEM, heldItem2);
    }
}

void ScriptSetMonMoveSlot(u8 monIndex, enum Move move, u8 slot)
{
// Allows monIndex to go out of bounds of gParties[B_TRAINER_PLAYER]. Doesn't occur in vanilla
#ifdef BUGFIX
    if (monIndex >= PARTY_SIZE)
#else
    if (monIndex > PARTY_SIZE)
#endif
        monIndex = gPartiesCount[B_TRAINER_PLAYER] - 1;

    SetMonMoveSlot(&gParties[B_TRAINER_PLAYER][monIndex], move, slot);
}

// Note: When control returns to the event script, gSpecialVar_Result will be
// TRUE if the party selection was successful.
void ChooseHalfPartyForBattle(void)
{
    gMain.savedCallback = CB2_ReturnFromChooseHalfParty;
    VarSet(VAR_FRONTIER_FACILITY, FACILITY_MULTI_OR_EREADER);
    InitChooseHalfPartyForBattle(0);
}

static void CB2_ReturnFromChooseHalfParty(void)
{
    switch (gSelectedOrderFromParty[0])
    {
    case 0:
        gSpecialVar_Result = FALSE;
        break;
    default:
        gSpecialVar_Result = TRUE;
        break;
    }

    SetMainCallback2(CB2_ReturnToFieldContinueScriptPlayMapMusic);
}

void ChoosePartyForBattleFrontier(void)
{
    gMain.savedCallback = CB2_ReturnFromChooseBattleFrontierParty;
    InitChooseHalfPartyForBattle(gSpecialVar_0x8004 + 1);
}

static void CB2_ReturnFromChooseBattleFrontierParty(void)
{
    switch (gSelectedOrderFromParty[0])
    {
    case 0:
        gSpecialVar_Result = FALSE;
        break;
    default:
        gSpecialVar_Result = TRUE;
        break;
    }

    SetMainCallback2(CB2_ReturnToFieldContinueScriptPlayMapMusic);
}

void ReducePlayerPartyToSelectedMons(void)
{
    struct Pokemon party[MAX_FRONTIER_PARTY_SIZE];
    int i;

    CpuFill32(0, party, sizeof party);

    // copy the selected Pokémon according to the order.
    for (i = 0; i < MAX_FRONTIER_PARTY_SIZE; i++)
        if (gSelectedOrderFromParty[i]) // as long as the order keeps going (did the player select 1 mon? 2? 3?), do not stop
            party[i] = gParties[B_TRAINER_PLAYER][gSelectedOrderFromParty[i] - 1]; // index is 0 based, not literal

    CpuFill32(0, gParties[B_TRAINER_PLAYER], sizeof gParties[B_TRAINER_PLAYER]);

    // overwrite the first 4 with the order copied to.
    for (i = 0; i < MAX_FRONTIER_PARTY_SIZE; i++)
        gParties[B_TRAINER_PLAYER][i] = party[i];

    CalculatePlayerPartyCount();
}

void CanHyperTrain(struct ScriptContext *ctx)
{
    u32 stat = ScriptReadByte(ctx);
    u32 partyIndex = VarGet(ScriptReadHalfword(ctx));

    Script_RequestEffects(SCREFF_V1);

    assertf(stat < NUM_STATS, "invalid stat: %d", stat)
    {
        gSpecialVar_Result = FALSE;
        return;
    }

    CalculatePlayerPartyCount();
    assertf(partyIndex < gPartiesCount[B_TRAINER_PLAYER], "invalid party index: %d", partyIndex)
    {
        gSpecialVar_Result = FALSE;
        return;
    }

    if (!GetMonData(&gParties[B_TRAINER_PLAYER][partyIndex], MON_DATA_HYPER_TRAINED_HP + stat)
     && GetMonData(&gParties[B_TRAINER_PLAYER][partyIndex], MON_DATA_HP_IV + stat) < MAX_PER_STAT_IVS)
    {
        gSpecialVar_Result = TRUE;
    }
    else
    {
        gSpecialVar_Result = FALSE;
    }
}

void HyperTrain(struct ScriptContext *ctx)
{
    u32 stat = ScriptReadByte(ctx);
    u32 partyIndex = VarGet(ScriptReadHalfword(ctx));

    Script_RequestEffects(SCREFF_V1 | SCREFF_SAVE);

    assertf(stat < NUM_STATS, "invalid stat: %d", stat)
    {
        return;
    }

    CalculatePlayerPartyCount();
    assertf(partyIndex < gPartiesCount[B_TRAINER_PLAYER], "invalid party index: %d", partyIndex)
    {
        return;
    }

    bool32 data = TRUE;
    SetMonData(&gParties[B_TRAINER_PLAYER][partyIndex], MON_DATA_HYPER_TRAINED_HP + stat, &data);
    CalculateMonStats(&gParties[B_TRAINER_PLAYER][partyIndex]);
}

void HasGigantamaxFactor(struct ScriptContext *ctx)
{
    u32 partyIndex = VarGet(ScriptReadHalfword(ctx));

    Script_RequestEffects(SCREFF_V1);

    if (partyIndex < PARTY_SIZE)
        gSpecialVar_Result = GetMonData(&gParties[B_TRAINER_PLAYER][partyIndex], MON_DATA_GIGANTAMAX_FACTOR);
    else
        gSpecialVar_Result = FALSE;
}

void ToggleGigantamaxFactor(struct ScriptContext *ctx)
{
    u32 partyIndex = VarGet(ScriptReadHalfword(ctx));

    Script_RequestEffects(SCREFF_V1 | SCREFF_SAVE);

    gSpecialVar_Result = FALSE;

    if (partyIndex < PARTY_SIZE)
    {
        bool32 gigantamaxFactor;

        if (gSpeciesInfo[SanitizeSpeciesId(GetMonData(&gParties[B_TRAINER_PLAYER][partyIndex], MON_DATA_SPECIES))].isMythical)
            return;

        gigantamaxFactor = GetMonData(&gParties[B_TRAINER_PLAYER][partyIndex], MON_DATA_GIGANTAMAX_FACTOR);
        gigantamaxFactor = !gigantamaxFactor;
        SetMonData(&gParties[B_TRAINER_PLAYER][partyIndex], MON_DATA_GIGANTAMAX_FACTOR, &gigantamaxFactor);
        gSpecialVar_Result = TRUE;
    }
}

void CheckTeraType(struct ScriptContext *ctx)
{
    u32 partyIndex = VarGet(ScriptReadHalfword(ctx));

    Script_RequestEffects(SCREFF_V1);

    gSpecialVar_Result = TYPE_NONE;

    if (partyIndex < PARTY_SIZE)
        gSpecialVar_Result = GetMonData(&gParties[B_TRAINER_PLAYER][partyIndex], MON_DATA_TERA_TYPE);
}

void SetTeraType(struct ScriptContext *ctx)
{
    enum Type type = ScriptReadByte(ctx);
    u32 partyIndex = VarGet(ScriptReadHalfword(ctx));

    Script_RequestEffects(SCREFF_V1 | SCREFF_SAVE);

    if (type < NUMBER_OF_MON_TYPES && partyIndex < PARTY_SIZE)
        SetMonData(&gParties[B_TRAINER_PLAYER][partyIndex], MON_DATA_TERA_TYPE, &type);
}

/* Creates a Pokemon via script
 * if side/slot are assigned, it will create the mon at the assigned party location
 * if slot == PARTY_SIZE, it will give the mon to first available party or storage slot
 */
static u32 ScriptGiveMonParameterized(u8 side, u8 slot, enum Species species, u8 level, enum Item item, enum PokeBall ball, u8 nature, u8 abilityNum, u8 gender, u16 *evs, u16 *ivs, enum Move *moves, enum ShinyMode shinyMode, bool8 gmaxFactor, enum Type teraType, u8 dmaxLevel)
{
    struct Pokemon mon;
    u32 i;
    bool32 isShiny;

    ResolveRandomMonGeneration(species, &ball, moves);

    u32 personality = GetMonPersonality(species, gender, nature, RANDOM_UNOWN_LETTER);
    CreateMon(&mon, species, level, personality, OTID_STRUCT_PLAYER_ID);

    // shininess
    if (shinyMode == SHINY_MODE_ALWAYS || (P_FLAG_FORCE_SHINY != 0 && FlagGet(P_FLAG_FORCE_SHINY)))
        isShiny = TRUE;
    else if (shinyMode == SHINY_MODE_NEVER || (P_FLAG_FORCE_NO_SHINY != 0 && FlagGet(P_FLAG_FORCE_NO_SHINY)))
        isShiny = FALSE;
    else
        isShiny = GetMonData(&mon, MON_DATA_IS_SHINY);

    SetMonData(&mon, MON_DATA_IS_SHINY, &isShiny);

    // gigantamax factor
    SetMonData(&mon, MON_DATA_GIGANTAMAX_FACTOR, &gmaxFactor);

    // Dynamax Level
    SetMonData(&mon, MON_DATA_DYNAMAX_LEVEL, &dmaxLevel);

    // tera type
    if (teraType == TYPE_NONE || teraType == TYPE_MYSTERY || teraType >= NUMBER_OF_MON_TYPES)
        teraType = GetTeraTypeFromPersonality(&mon);
    SetMonData(&mon, MON_DATA_TERA_TYPE, &teraType);

    // EV and IV
    for (i = 0; i < NUM_STATS; i++)
    {
        // EV
        if (evs[i] <= MAX_PER_STAT_EVS)
            SetMonData(&mon, MON_DATA_HP_EV + i, &evs[i]);

        // IV
        if (ivs[i] <= MAX_PER_STAT_IVS)
            SetMonData(&mon, MON_DATA_HP_IV + i, &ivs[i]);
    }
    CalculateMonStats(&mon);

    // moves
    bool32 all_default_flag = TRUE;
    for (i = 0; i < MAX_MON_MOVES; i++)
    {
        if (moves[i] != MOVE_DEFAULT)
        {
            all_default_flag = FALSE;
            break;
        }
    }
    if (all_default_flag)
    {
        GiveMonInitialMoveset(&mon);
    }
    else
    {
        for (i = 0; i < MAX_MON_MOVES; i++)
        {
            if (moves[i] == MOVE_NONE)
                break;
            if (moves[i] < MOVES_COUNT)
            {
                SetMonMoveSlot(&mon, moves[i], i);
            }
            else if (moves[i] == MOVE_DEFAULT)
            {
                GiveMonDefaultMove(&mon, i);
                continue;
            }
            else
            {
                assertf(FALSE, "invalid move: %d", moves[i]) {}
            }
        }
    }

    // ability
    if (abilityNum != NUM_ABILITY_PERSONALITY)
    {
        assertf(abilityNum < NUM_ABILITY_SLOTS && GetAbilityBySpecies(species, abilityNum) != ABILITY_NONE,
                "invalid ability num %d for species %d", abilityNum, species)
        {
            // If the ability num is invalid, we loop to find a valid one
            do {
                abilityNum = Random() % NUM_ABILITY_SLOTS; // includes hidden abilities
            } while (GetAbilityBySpecies(species, abilityNum) == ABILITY_NONE);
        }
        SetMonData(&mon, MON_DATA_ABILITY_NUM, &abilityNum);
    }

    // ball
    if (ball > POKEBALL_COUNT)
        ball = BALL_POKE;
    SetMonData(&mon, MON_DATA_POKEBALL, &ball);

    // held item
    SetMonData(&mon, MON_DATA_HELD_ITEM, &item);

    // In case a mon with a form changing item is given. Eg: SPECIES_ARCEUS_NORMAL with ITEM_SPLASH_PLATE will transform into SPECIES_ARCEUS_WATER upon gifted.
    TryFormChange(&mon, FORM_CHANGE_ITEM_HOLD, B_TRAINER_PLAYER);

    if (side == B_SIDE_PLAYER)
        return GiveScriptedMonToPlayer(&mon, slot);

    assertf(slot < PARTY_SIZE, "invalid slot: %d", slot)
    {
        return MON_CANT_GIVE;
    }
    CopyMon(&gParties[B_TRAINER_OPPONENT_A][slot], &mon, sizeof(struct Pokemon));
    return MON_GIVEN_TO_PARTY;
}

u32 ScriptGiveMon(enum Species species, u8 level, enum Item item)
{
    struct Pokemon mon;
    u8 heldItem[2];

    CreateRandomMon(&mon, species, level);
    if (item)
    {
        heldItem[0] = item;
        heldItem[1] = item >> 8;
        SetMonData(&mon, MON_DATA_HELD_ITEM, heldItem);
    }

    return GiveScriptedMonToPlayer(&mon, PARTY_SIZE);
}

#define PARSE_FLAG(n, default_) (flags & (1 << (n))) ? VarGet(ScriptReadHalfword(ctx)) : (default_)

/* Give or create a mon to either player or opponent
 */


void ScrCmd_createmon(struct ScriptContext *ctx)
{
    u8 side            = ScriptReadByte(ctx);
    u8 slot            = ScriptReadByte(ctx);
    enum Species species = VarGet(ScriptReadHalfword(ctx));
    u8 level           = VarGet(ScriptReadHalfword(ctx));

    u32 flags          = ScriptReadWord(ctx);
    enum Item item     = PARSE_FLAG(0, ITEM_NONE);
    enum PokeBall ball = PARSE_FLAG(1, BALL_POKE);
    u8 nature          = PARSE_FLAG(2, NATURE_RANDOM);
    u8 abilityNum      = PARSE_FLAG(3, NUM_ABILITY_PERSONALITY);
    u8 gender          = PARSE_FLAG(4, MON_GENDER_RANDOM);

    u32 i;
    u16 evs[NUM_STATS];
    for (i = 0; i < NUM_STATS; i++)
    {
        evs[i] = PARSE_FLAG(5 + i, 0);
        assertf(evs[i] <= MAX_PER_STAT_EVS, "invalid ev value of %d above maximum of %d", evs[i], MAX_PER_STAT_EVS)
        {
            evs[i] = MAX_PER_STAT_EVS;
        }
    }

    u16 ivs[NUM_STATS];
    u32 nonFixedIvCount = 0;
    enum Stat availableIVs[NUM_STATS];
    enum Stat selectedIvs[NUM_STATS];
    for (i = 0; i < NUM_STATS; i++)
    {
        ivs[i] = PARSE_FLAG(11 + i, USE_RANDOM_IVS);
        assertf(ivs[i] <= USE_RANDOM_IVS, "invalid iv value of %d above maximum of %d", ivs[i], MAX_PER_STAT_IVS)
        {
            ivs[i] = MAX_PER_STAT_IVS;
        }
        if (ivs[i] == USE_RANDOM_IVS)
        {
            availableIVs[nonFixedIvCount] = i;
            ivs[i] = Random() % (MAX_PER_STAT_IVS + 1);
            nonFixedIvCount++;
        }
    }

    // Perfect IV calculation
    if (gSpeciesInfo[species].perfectIVCount != 0)
    {
        // Select the IVs that will be perfected.
        for (i = 0; i < nonFixedIvCount && i < gSpeciesInfo[species].perfectIVCount; i++)
        {
            u8 index = Random() % (nonFixedIvCount - i);
            selectedIvs[i] = availableIVs[index];
            RemoveIVIndexFromList(availableIVs, index);
        }
        for (i = 0; i < nonFixedIvCount && i < gSpeciesInfo[species].perfectIVCount; i++)
        {
            ivs[selectedIvs[i]] = MAX_PER_STAT_IVS;
        }
    }

    enum Move moves[MAX_MON_MOVES];
    for (i = 0; i < MAX_MON_MOVES; i++)
        moves[i] = PARSE_FLAG(17 + i, MOVE_DEFAULT);

    enum ShinyMode shinyMode = PARSE_FLAG(21, SHINY_MODE_RANDOM);
    bool8 gmaxFactor         = PARSE_FLAG(22, FALSE);
    enum Type teraType       = PARSE_FLAG(23, NUMBER_OF_MON_TYPES);
    u8 dmaxLevel             = PARSE_FLAG(24, 0);

    enum GeneratedMonOrigin origin;
    if (side == 0)
    {
        Script_RequestEffects(SCREFF_V1 | SCREFF_SAVE);
        origin = GIFTMON_ORIGIN;
    }
    else
    {
        Script_RequestEffects(SCREFF_V1);
        origin = STATIC_WILDMON_ORIGIN;
    }

    if (gender == MON_GENDER_MAY_CUTE_CHARM)
        gender = GetSynchronizedGender(origin, species);
    if (nature == NATURE_MAY_SYNCHRONIZE)
        nature = GetSynchronizedNature(origin, species);

    gSpecialVar_Result = ScriptGiveMonParameterized(side, slot, species, level, item, ball, nature, abilityNum, gender, evs, ivs, moves, shinyMode, gmaxFactor, teraType, dmaxLevel);
}

#undef PARSE_FLAG

void Script_GetChosenMonOffensiveEVs(void)
{
    ConvertIntToDecimalStringN(gStringVar1, GetMonData(&gParties[B_TRAINER_PLAYER][gSpecialVar_0x8004], MON_DATA_ATK_EV), STR_CONV_MODE_LEFT_ALIGN, 3);
    ConvertIntToDecimalStringN(gStringVar2, GetMonData(&gParties[B_TRAINER_PLAYER][gSpecialVar_0x8004], MON_DATA_SPATK_EV), STR_CONV_MODE_LEFT_ALIGN, 3);
    ConvertIntToDecimalStringN(gStringVar3, GetMonData(&gParties[B_TRAINER_PLAYER][gSpecialVar_0x8004], MON_DATA_SPEED_EV), STR_CONV_MODE_LEFT_ALIGN, 3);
}

void Script_GetChosenMonDefensiveEVs(void)
{
    ConvertIntToDecimalStringN(gStringVar1, GetMonData(&gParties[B_TRAINER_PLAYER][gSpecialVar_0x8004], MON_DATA_HP_EV), STR_CONV_MODE_LEFT_ALIGN, 3);
    ConvertIntToDecimalStringN(gStringVar2, GetMonData(&gParties[B_TRAINER_PLAYER][gSpecialVar_0x8004], MON_DATA_DEF_EV), STR_CONV_MODE_LEFT_ALIGN, 3);
    ConvertIntToDecimalStringN(gStringVar3, GetMonData(&gParties[B_TRAINER_PLAYER][gSpecialVar_0x8004], MON_DATA_SPDEF_EV), STR_CONV_MODE_LEFT_ALIGN, 3);
}

void Script_GetChosenMonOffensiveIVs(void)
{
    ConvertIntToDecimalStringN(gStringVar1, GetMonData(&gParties[B_TRAINER_PLAYER][gSpecialVar_0x8004], MON_DATA_ATK_IV), STR_CONV_MODE_LEFT_ALIGN, 3);
    ConvertIntToDecimalStringN(gStringVar2, GetMonData(&gParties[B_TRAINER_PLAYER][gSpecialVar_0x8004], MON_DATA_SPATK_IV), STR_CONV_MODE_LEFT_ALIGN, 3);
    ConvertIntToDecimalStringN(gStringVar3, GetMonData(&gParties[B_TRAINER_PLAYER][gSpecialVar_0x8004], MON_DATA_SPEED_IV), STR_CONV_MODE_LEFT_ALIGN, 3);
}

void Script_GetChosenMonDefensiveIVs(void)
{
    ConvertIntToDecimalStringN(gStringVar1, GetMonData(&gParties[B_TRAINER_PLAYER][gSpecialVar_0x8004], MON_DATA_HP_IV), STR_CONV_MODE_LEFT_ALIGN, 3);
    ConvertIntToDecimalStringN(gStringVar2, GetMonData(&gParties[B_TRAINER_PLAYER][gSpecialVar_0x8004], MON_DATA_DEF_IV), STR_CONV_MODE_LEFT_ALIGN, 3);
    ConvertIntToDecimalStringN(gStringVar3, GetMonData(&gParties[B_TRAINER_PLAYER][gSpecialVar_0x8004], MON_DATA_SPDEF_IV), STR_CONV_MODE_LEFT_ALIGN, 3);
}



static u32 GetTrainingEVField(u16 choice)
{
    switch (choice)
    {
    case 0:
        return MON_DATA_HP_EV;
    case 1:
        return MON_DATA_ATK_EV;
    case 2:
        return MON_DATA_DEF_EV;
    case 3:
        return MON_DATA_SPATK_EV;
    case 4:
        return MON_DATA_SPDEF_EV;
    case 5:
        return MON_DATA_SPEED_EV;
    default:
        return MON_DATA_HP_EV;
    }
}

static u32 GetTrainingIVField(u16 choice)
{
    switch (choice)
    {
    case 0:
        return MON_DATA_HP_IV;
    case 1:
        return MON_DATA_ATK_IV;
    case 2:
        return MON_DATA_DEF_IV;
    case 3:
        return MON_DATA_SPATK_IV;
    case 4:
        return MON_DATA_SPDEF_IV;
    case 5:
        return MON_DATA_SPEED_IV;
    default:
        return MON_DATA_HP_IV;
    }
}

static u32 GetMonTotalEVsForTraining(struct Pokemon *mon)
{
    return GetMonData(mon, MON_DATA_HP_EV)
         + GetMonData(mon, MON_DATA_ATK_EV)
         + GetMonData(mon, MON_DATA_DEF_EV)
         + GetMonData(mon, MON_DATA_SPATK_EV)
         + GetMonData(mon, MON_DATA_SPDEF_EV)
         + GetMonData(mon, MON_DATA_SPEED_EV);
}

void Script_CheckSelectedMonEVTraining(void)
{
    struct Pokemon *mon;
    u32 field;
    u32 current;
    u32 total;

    if (gSpecialVar_0x8004 >= PARTY_SIZE || gSpecialVar_0x8005 > 5)
    {
        gSpecialVar_Result = 3;
        return;
    }

    mon = &gParties[B_TRAINER_PLAYER][gSpecialVar_0x8004];
    field = GetTrainingEVField(gSpecialVar_0x8005);
    current = GetMonData(mon, field);
    total = GetMonTotalEVsForTraining(mon);

    if (current >= 252)
        gSpecialVar_Result = 1;
    else if (total >= 510)
        gSpecialVar_Result = 2;
    else
        gSpecialVar_Result = 0;
}

void Script_TrainSelectedMonEV(void)
{
    struct Pokemon *mon;
    u32 field;
    u32 current;
    u32 total;
    u32 available;
    u32 needed;
    u32 newValue;

    if (gSpecialVar_0x8004 >= PARTY_SIZE || gSpecialVar_0x8005 > 5)
    {
        gSpecialVar_Result = FALSE;
        return;
    }

    mon = &gParties[B_TRAINER_PLAYER][gSpecialVar_0x8004];
    field = GetTrainingEVField(gSpecialVar_0x8005);

    current = GetMonData(mon, field);
    total = GetMonTotalEVsForTraining(mon);

    if (current >= 252 || total >= 510)
    {
        gSpecialVar_Result = FALSE;
        return;
    }

    available = 510 - total;
    needed = 252 - current;

    if (needed > available)
        needed = available;

    newValue = current + needed;

    Script_RequestEffects(SCREFF_V1 | SCREFF_SAVE);
    SetMonData(mon, field, &newValue);
    CalculateMonStats(mon);

    gSpecialVar_Result = TRUE;
}

void Script_CheckSelectedMonIVTraining(void)
{
    struct Pokemon *mon;
    u32 field;

    if (gSpecialVar_0x8004 >= PARTY_SIZE || gSpecialVar_0x8005 > 5)
    {
        gSpecialVar_Result = FALSE;
        return;
    }

    mon = &gParties[B_TRAINER_PLAYER][gSpecialVar_0x8004];
    field = GetTrainingIVField(gSpecialVar_0x8005);

    gSpecialVar_Result = GetMonData(mon, field) < 31;
}

void Script_TrainSelectedMonIV(void)
{
    struct Pokemon *mon;
    u32 field;
    u32 value = 31;

    if (gSpecialVar_0x8004 >= PARTY_SIZE || gSpecialVar_0x8005 > 5)
    {
        gSpecialVar_Result = FALSE;
        return;
    }

    mon = &gParties[B_TRAINER_PLAYER][gSpecialVar_0x8004];
    field = GetTrainingIVField(gSpecialVar_0x8005);

    Script_RequestEffects(SCREFF_V1 | SCREFF_SAVE);
    SetMonData(mon, field, &value);
    CalculateMonStats(mon);

    gSpecialVar_Result = TRUE;
}

void Script_IsSelectedMonShiny(void)
{
    if (gSpecialVar_0x8004 >= PARTY_SIZE)
    {
        gSpecialVar_Result = FALSE;
        return;
    }

    gSpecialVar_Result = GetMonData(
        &gParties[B_TRAINER_PLAYER][gSpecialVar_0x8004],
        MON_DATA_IS_SHINY
    );
}

void Script_IsSelectedMonMimikyu(void)
{
    if (gSpecialVar_0x8004 >= PARTY_SIZE)
    {
        gSpecialVar_Result = FALSE;
        return;
    }

    gSpecialVar_Result =
        GetMonData(
            &gParties[B_TRAINER_PLAYER][gSpecialVar_0x8004],
            MON_DATA_SPECIES
        ) == SPECIES_MIMIKYU;
}


void Script_MakeSelectedMonShiny(void)
{
    u32 isShiny = TRUE;

    if (gSpecialVar_0x8004 >= PARTY_SIZE)
    {
        gSpecialVar_Result = FALSE;
        return;
    }

    Script_RequestEffects(SCREFF_V1 | SCREFF_SAVE);

    SetMonData(
        &gParties[B_TRAINER_PLAYER][gSpecialVar_0x8004],
        MON_DATA_IS_SHINY,
        &isShiny
    );

    gSpecialVar_Result = TRUE;
}


static struct BoxPokemon *GetSelectedEggForCustomization(void)
{
    struct BoxPokemon *boxMon = GetSelectedBoxMonFromPcOrParty();

    if (boxMon == NULL)
        return NULL;

    if (!GetBoxMonData(boxMon, MON_DATA_IS_EGG))
        return NULL;

    return boxMon;
}

void Script_CanCustomizeSelectedEggGender(struct ScriptContext *ctx)
{
    gSpecialVar_Result = (GetSelectedEggForCustomization() != NULL);
}

void Script_SetSelectedMonNature(struct ScriptContext *ctx)
{
    struct Pokemon *mon;
    struct BoxPokemon *boxMon;
    enum Species species;
    u32 nature = gSpecialVar_0x8005;
    u32 gender;
    u32 personality;

    if (gSpecialVar_0x8004 >= PARTY_SIZE || nature >= NUM_NATURES)
    {
        gSpecialVar_Result = FALSE;
        return;
    }

    mon = &gParties[B_TRAINER_PLAYER][gSpecialVar_0x8004];

    if (GetMonData(mon, MON_DATA_IS_EGG))
    {
        gSpecialVar_Result = FALSE;
        return;
    }

    species = GetMonData(mon, MON_DATA_SPECIES);
    gender = GetMonGender(mon);

    personality = GetMonPersonality(
        species,
        gender,
        nature,
        RANDOM_UNOWN_LETTER
    );

    Script_RequestEffects(SCREFF_V1 | SCREFF_SAVE);

    boxMon = &mon->box;
    UpdateMonPersonality(boxMon, personality);

    // Make the effective Nature agree with the new personality Nature.
    SetMonData(mon, MON_DATA_HIDDEN_NATURE, &nature);

    CalculateMonStats(mon);

    gSpecialVar_Result = TRUE;
}


void Script_SetSelectedEggNature(struct ScriptContext *ctx)
{
    struct BoxPokemon *boxMon = GetSelectedEggForCustomization();
    u32 nature = gSpecialVar_0x8005;

    if (boxMon == NULL || nature >= NUM_NATURES)
    {
        gSpecialVar_Result = FALSE;
        return;
    }

    Script_RequestEffects(SCREFF_V1 | SCREFF_SAVE);

    SetBoxMonData(boxMon, MON_DATA_HIDDEN_NATURE, &nature);

    gSpecialVar_Result = TRUE;
}

void Script_SetSelectedEggGender(struct ScriptContext *ctx)
{
    struct BoxPokemon *boxMon = GetSelectedEggForCustomization();
    enum Species species;
    u32 personality;
    u32 requestedGender;
    u32 hiddenNature;

    if (boxMon == NULL)
    {
        gSpecialVar_Result = FALSE;
        return;
    }

    if (gSpecialVar_0x8005 == 0)
        requestedGender = MON_MALE;
    else if (gSpecialVar_0x8005 == 1)
        requestedGender = MON_FEMALE;
    else
    {
        gSpecialVar_Result = FALSE;
        return;
    }

    species = GetBoxMonData(boxMon, MON_DATA_SPECIES);

    if (gSpeciesInfo[species].genderRatio == MON_MALE
     || gSpeciesInfo[species].genderRatio == MON_FEMALE
     || gSpeciesInfo[species].genderRatio == MON_GENDERLESS)
    {
        gSpecialVar_Result = FALSE;
        return;
    }

    // Preserve the effective Nature across the personality change.
    hiddenNature = GetBoxMonData(boxMon, MON_DATA_HIDDEN_NATURE);

    personality = GetMonPersonality(
        species,
        requestedGender,
        NATURE_RANDOM,
        RANDOM_UNOWN_LETTER
    );

    Script_RequestEffects(SCREFF_V1 | SCREFF_SAVE);

    UpdateMonPersonality(boxMon, personality);

    // The hidden Nature modifier depends on personality, so rebuild it
    // against the new personality while preserving the chosen Nature.
    SetBoxMonData(boxMon, MON_DATA_HIDDEN_NATURE, &hiddenNature);

    gSpecialVar_Result = TRUE;
}


void Script_SetSelectedEggAbility(struct ScriptContext *ctx)
{
    struct BoxPokemon *boxMon = GetSelectedEggForCustomization();
    enum Species species;
    u32 requestedMode = gSpecialVar_0x8005;
    u32 abilityNum;
    u32 i;

    if (boxMon == NULL)
    {
        gSpecialVar_Result = FALSE;
        return;
    }

    species = GetBoxMonData(boxMon, MON_DATA_SPECIES);

    if (requestedMode == 0)
    {
        // Innate Ability.
        // Preserve an existing valid normal slot when possible.
        abilityNum = GetBoxMonData(boxMon, MON_DATA_ABILITY_NUM);

        if (abilityNum >= NUM_NORMAL_ABILITY_SLOTS
         || GetAbilityBySpecies(species, abilityNum) == ABILITY_NONE)
        {
            for (i = 0; i < NUM_NORMAL_ABILITY_SLOTS; i++)
            {
                if (GetAbilityBySpecies(species, i) != ABILITY_NONE)
                {
                    abilityNum = i;
                    break;
                }
            }

            if (i == NUM_NORMAL_ABILITY_SLOTS)
            {
                gSpecialVar_Result = FALSE;
                return;
            }
        }
    }
    else if (requestedMode == 1)
    {
        // Hidden Ability slot begins immediately after the normal slots.
        abilityNum = NUM_NORMAL_ABILITY_SLOTS;

        if (GetAbilityBySpecies(species, abilityNum) == ABILITY_NONE)
        {
            gSpecialVar_Result = FALSE;
            return;
        }
    }
    else
    {
        gSpecialVar_Result = FALSE;
        return;
    }

    Script_RequestEffects(SCREFF_V1 | SCREFF_SAVE);
    SetBoxMonData(boxMon, MON_DATA_ABILITY_NUM, &abilityNum);

    gSpecialVar_Result = TRUE;
}

void Script_SetSelectedEggBall(struct ScriptContext *ctx)
{
    struct BoxPokemon *boxMon = GetSelectedEggForCustomization();
    u32 ball = gSpecialVar_0x8005;

    if (boxMon == NULL)
    {
        gSpecialVar_Result = FALSE;
        return;
    }

    if (ball < BALL_POKE
     || ball >= POKEBALL_COUNT
     || ball == BALL_MASTER
     || ball == BALL_CHERISH
     || ball == BALL_STRANGE)
    {
        gSpecialVar_Result = FALSE;
        return;
    }

    Script_RequestEffects(SCREFF_V1 | SCREFF_SAVE);

    SetBoxMonData(boxMon, MON_DATA_POKEBALL, &ball);

    gSpecialVar_Result = TRUE;
}

void Script_SetStatus1(struct ScriptContext *ctx)
{
    u32 status1 = VarGet(ScriptReadHalfword(ctx));
    u32 slot = VarGet(ScriptReadHalfword(ctx));

    Script_RequestEffects(SCREFF_V1 | SCREFF_SAVE);

    if (slot >= PARTY_SIZE)
    {
        enum Species species;

        for (slot = 0; slot < PARTY_SIZE; slot++)
        {
            species = GetMonData(&gParties[B_TRAINER_PLAYER][slot], MON_DATA_SPECIES);
            if (species != SPECIES_NONE
             && species != SPECIES_EGG
             && GetMonData(&gParties[B_TRAINER_PLAYER][slot], MON_DATA_HP) != 0)
                SetMonData(&gParties[B_TRAINER_PLAYER][slot], MON_DATA_STATUS, &status1);
        }
    }
    else
    {
        SetMonData(&gParties[B_TRAINER_PLAYER][slot], MON_DATA_STATUS, &status1);
    }
}

void Script_SetKO(struct ScriptContext *ctx)
{
    u32 slot = VarGet(ScriptReadHalfword(ctx));

    Script_RequestEffects(SCREFF_V1 | SCREFF_SAVE);

    if (slot < PARTY_SIZE)
    {
        u32 hp = 0;
        SetMonData(&gParties[B_TRAINER_PLAYER][slot], MON_DATA_HP, &hp);
    }
}

void Script_GiveRandomBerry(struct ScriptContext *ctx)
{
    enum BerryId loBerry = ScriptReadByte(ctx);
    enum BerryId hiBerry = ScriptReadByte(ctx);

    gSpecialVar_Result = BerryTypeToItemId(RandomUniform(RNG_RANDOM_BERRY, loBerry, hiBerry));
}

/*
 * Fallarbor Evolution Specialist
 *
 * Allows a selected party Pokemon to undergo an evolution whose
 * primary evolution method is EVO_TRADE.
 */

void Script_CheckSelectedMonTradeEvolution(void)
{
    u32 partyIndex = gSpecialVar_0x8004;
    struct Pokemon *mon;
    enum Species targetSpecies;

    if (partyIndex >= gPartiesCount[B_TRAINER_PLAYER])
    {
        gSpecialVar_Result = FALSE;
        return;
    }

    mon = &gParties[B_TRAINER_PLAYER][partyIndex];

    if (GetMonData(mon, MON_DATA_IS_EGG))
    {
        gSpecialVar_Result = FALSE;
        return;
    }

    targetSpecies = GetEvolutionTargetSpecies(
        mon,
        EVO_MODE_TRADE,
        ITEM_NONE,
        NULL,
        NULL,
        CHECK_EVO
    );

    gSpecialVar_Result = (targetSpecies != SPECIES_NONE);
}

void Script_EvolveSelectedMonByTrade(void)
{
    u32 partyIndex = gSpecialVar_0x8004;
    struct Pokemon *mon;
    enum Species targetSpecies;
    bool32 canStopEvo = TRUE;

    if (partyIndex >= gPartiesCount[B_TRAINER_PLAYER])
    {
        gSpecialVar_Result = FALSE;
        return;
    }

    mon = &gParties[B_TRAINER_PLAYER][partyIndex];

    targetSpecies = GetEvolutionTargetSpecies(
        mon,
        EVO_MODE_TRADE,
        ITEM_NONE,
        NULL,
        &canStopEvo,
        CHECK_EVO
    );

    if (targetSpecies == SPECIES_NONE)
    {
        gSpecialVar_Result = FALSE;
        return;
    }

    GetEvolutionTargetSpecies(
        mon,
        EVO_MODE_TRADE,
        ITEM_NONE,
        NULL,
        &canStopEvo,
        DO_EVO
    );

    gSpecialVar_Result = TRUE;
    gCB2_AfterEvolution = CB2_ReturnToFieldContinueScript;
    BeginEvolutionScene(mon, targetSpecies, canStopEvo, partyIndex);
    ScriptContext_Stop();
}


void Script_GetLavaridgeVirtueEggSpecies(void)
{
    enum Species species = SPECIES_WYNAUT;
    u16 best = 0;
    u16 value;

    value = VarGet(VAR_COMPASSION);
    if (value > best)
    {
        best = value;
        species = SPECIES_TOGEPI;
    }

    value = VarGet(VAR_CURIOSITY);
    if (value > best)
    {
        best = value;
        species = SPECIES_EEVEE;
    }

    value = VarGet(VAR_RESOLVE);
    if (value > best)
    {
        best = value;
        species = SPECIES_RIOLU;
    }

    value = VarGet(VAR_INDEPENDENCE);
    if (value > best)
    {
        best = value;
        species = SPECIES_ABSOL;
    }

    value = VarGet(VAR_WISDOM);
    if (value > best)
    {
        best = value;
        species = SPECIES_RALTS;
    }

    value = VarGet(VAR_PERSPECTIVE);
    if (value > best)
    {
        best = value;
        species = SPECIES_ZORUA;
    }

    gSpecialVar_Result = species;
}

void Script_LavaridgeHotSpringsWarmEggs(void)
{
    u32 i;
    u32 eggCycles;
    u32 warmed = 0;

    for (i = 0; i < gPartiesCount[B_TRAINER_PLAYER]; i++)
    {
        if (!GetMonData(&gParties[B_TRAINER_PLAYER][i], MON_DATA_IS_EGG))
            continue;

        if (GetMonData(&gParties[B_TRAINER_PLAYER][i], MON_DATA_SANITY_IS_BAD_EGG))
            continue;

        eggCycles = GetMonData(
            &gParties[B_TRAINER_PLAYER][i],
            MON_DATA_FRIENDSHIP
        );

        if (eggCycles <= 1)
            continue;

        if (eggCycles > 5)
            eggCycles -= 5;
        else
            eggCycles = 1;

        SetMonData(
            &gParties[B_TRAINER_PLAYER][i],
            MON_DATA_FRIENDSHIP,
            &eggCycles
        );

        warmed++;
    }

    gSpecialVar_Result = warmed;
}


void Script_RepairCorruptedLavaridgeTogepi(void)
{
    u32 i;
    u32 personality;
    u32 ball = ITEM_POKE_BALL;
    struct Pokemon *mon;

    for (i = 0; i < gPartiesCount[B_TRAINER_PLAYER]; i++)
    {
        mon = &gParties[B_TRAINER_PLAYER][i];

        if (GetMonData(mon, MON_DATA_SPECIES) != SPECIES_TOGEPI)
            continue;

        personality = GetMonPersonality(
            SPECIES_TOGEPI,
            MON_FEMALE,
            NATURE_MODEST,
            RANDOM_UNOWN_LETTER
        );

        CreateMonWithIVs(
            mon,
            SPECIES_TOGEPI,
            1,
            personality,
            OTID_STRUCT_PLAYER_ID,
            USE_RANDOM_IVS
        );

        GiveMonInitialMoveset(mon);
        SetMonData(mon, MON_DATA_POKEBALL, &ball);
        CalculateMonStats(mon);

        CalculatePlayerPartyCount();

        gSpecialVar_Result = TRUE;
        return;
    }

    gSpecialVar_Result = FALSE;
}
