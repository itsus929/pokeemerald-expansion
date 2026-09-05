#ifndef GUARD_SCRIPT_POKEMON_UTIL_H
#define GUARD_SCRIPT_POKEMON_UTIL_H

struct ScriptContext;

u32 ScriptGiveMon(enum Species species, u8 level, enum Item item);
u8 ScriptGiveEgg(enum Species species);
void CreateScriptedWildMon(enum Species species, u8 level, enum Item item);
void CreateScriptedDoubleWildMon(enum Species species, u8 level, enum Item item, enum Species species2, u8 level2, enum Item item2);
void ScriptSetMonMoveSlot(u8 monIndex, enum Move move, u8 slot);
void ReducePlayerPartyToSelectedMons(void);
void HealPlayerParty(void);
void Script_GetChosenMonOffensiveEVs(void);
void Script_GetChosenMonDefensiveEVs(void);
void Script_GetChosenMonOffensiveIVs(void);
void Script_GetChosenMonDefensiveIVs(void);

void Script_IsSelectedMonShiny(void);
void Script_MakeSelectedMonShiny(void);
void Script_IsSelectedMonMimikyu(void);

void Script_CheckSelectedMonEVTraining(void);
void Script_TrainSelectedMonEV(void);
void Script_CheckSelectedMonIVTraining(void);
void Script_TrainSelectedMonIV(void);


void Script_CanCustomizeSelectedEggGender(struct ScriptContext *ctx);
void Script_SetSelectedMonNature(struct ScriptContext *ctx);
void Script_SetSelectedEggNature(struct ScriptContext *ctx);
void Script_SetSelectedEggGender(struct ScriptContext *ctx);
void Script_SetSelectedEggAbility(struct ScriptContext *ctx);
void Script_SetSelectedEggBall(struct ScriptContext *ctx);


void Script_CheckSelectedMonTradeEvolution(void);
void Script_EvolveSelectedMonByTrade(void);

void Script_GetLavaridgeVirtueEggSpecies(void);
void Script_LavaridgeHotSpringsWarmEggs(void);

void Script_RepairCorruptedLavaridgeTogepi(void);
#endif // GUARD_SCRIPT_POKEMON_UTIL_H
