/*
 * guru_quest.h
 * This file contains all the defines used in the calian
 * sup. guru quest. It's 'isolated' so that it may be included
 * in the npc's external to Eldoral (Krom, Raspatoon, and Lobar)
 * with minimal impact of extraneous defines.
 */

/* 'Trigger' define for opening the guru quest. Define */
/* GURU_OPEN to have the npcs outside of Eldoral start */
/* compiling the necessary extras. Note you'll have */
/* to reload each of them after defining this, so its */
/* almost as easy to wait until just before arma. */
#define GURU_OPEN

/* Path to the guru quest brain object. */
#ifndef GURU_BRAIN
#define GURU_BRAIN             "/d/Calia/eldoral/special/guru_brain"
#endif

/* Properties */
#define LIVE_I_GURU_QUESTING   "_live_i_guru_questing"
#define DRAGON_S_WAS_RELEASED  "_dragon_s_was_released"

/* Flags for the GURU_QUESTING property. */
#define C_GURU_DRAGON          1
#define C_GURU_KROM            2
#define C_GURU_RASPATOON       4
#define C_GURU_LOBAR           8

/* Names for special objects for the quest. */
#define C_GURU_GAUNTLET_NAME   "_c_guru_gauntlet"
#define C_GURU_MOSS_NAME       "_c_guru_moss"
#define C_GURU_CHAIN_NAME      "_c_guru_chain"
#define C_GURU_GUILD_NAME      "Calian warrior's guild"

/* The guru quest group and bit. */
#define GURU_QUEST_GROUP       4
#define GURU_QUEST_BIT         4

/* Simple IS_GURU_CALIAN(x) macro. */
#define IS_GURU_CALIAN(x) \
     ((x->query_guild_name_occ()) == C_GURU_GUILD_NAME)
