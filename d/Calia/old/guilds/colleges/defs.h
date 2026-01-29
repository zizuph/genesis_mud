#include "/d/Calia/domain.h"

#define COLLEGE_DIR "/d/Calia/guilds/colleges/"
#define COLLEGE_LOGS "/d/Calia/guilds/colleges/logs/"
#define COLLEGE_SPECIALS "/d/Calia/guilds/colleges/specials/"

#define TOWER "/d/Calia/guilds/colleges/tower/"
#define TOWER_NPCS "/d/Calia/guilds/colleges/tower/npcs/"
#define TOWER_OBJECTS "/d/Calia/guilds/colleges/tower/objects/"

#define TEMP_ROOM "/d/Calia/guilds/colleges/specials/temp_spell_room"

#define COUNCIL_OB "/d/Calia/guilds/colleges/specials/council_control"

#define FIRE_DIR "/d/Calia/guilds/colleges/fire/"
#define WATER_DIR "/d/Calia/guilds/colleges/water/"
#define AIR_DIR "/d/Calia/guilds/colleges/air/"
#define EARTH_DIR "/d/Calia/guilds/colleges/earth/"

 /* Fire College */

#define FIRE_OBJECTS "/d/Calia/guilds/colleges/fire/objects/"
#define FIRE_SPELLS "/d/Calia/guilds/colleges/fire/spells/"
#define FIRE_SPECIALS "/d/Calia/guilds/colleges/fire/specials/"
#define FIRE_TAX 0

 /* Air College */

#define AIR_OBJECTS "/d/Calia/guilds/colleges/air/objects/"
#define AIR_SPELLS "/d/Calia/guilds/colleges/air/spells/"
#define AIR_SPECIALS "/d/Calia/guilds/colleges/air/specials/"
#define AIR_TAX 0

 /* Water College */

#define WATER_OBJECTS "/d/Calia/guilds/colleges/water/objects/"
#define WATER_SPELLS "/d/Calia/guilds/colleges/water/spells/"
#define WATER_SPECIALS "/d/Calia/guilds/colleges/water/specials/"
#define WATER_TAX 0

 /* Earth College */

#define EARTH_OBJECTS "/d/Calia/guilds/colleges/earth/objects/"
#define EARTH_SPELLS "/d/Calia/guilds/colleges/earth/spells/"
#define EARTH_SPECIALS "/d/Calia/guilds/colleges/earth/specials/"
#define EARTH_TAX 0

/* Guild skills */

// This skill contains guild levels and punishments, odds and ends.
#define SS_COLLEGE_BITS  114053

// This skill contains spell bits, used to determine what the caster can cast.
#define SS_COLLEGE_SPELL_STATUS 114054

// This skill is a visible skill, training in ritual magic.
#define SS_RITUAL_MAGIC 114055

/* Bits for SS_COLLEGE_BITS */

#define APPRENTICE_LVL_BIT 1
#define MAGE_LVL_BIT 2
#define SCHOLAR_LVL_BIT 4
#define SPELL_BANNED_BIT 8
#define TOWER_CONFINED_BIT 16
#define EXPELLED_BIT 32
#define TITLE_SIMPLE_BIT 64
#define HERBALISM_CHOSEN_BIT 128
#define ALCHEMY_CHOSEN_BIT 256
#define LANGUAGE_CHOSEN_BIT 512

/* Bits for SS_COLLEGE_SPELL_STATUS */

#define SPELL_1_BIT 1
#define SPELL_2_BIT 2
#define SPELL_3_BIT 4
#define SPELL_4_BIT 8
#define SPELL_5_BIT 16
#define SPELL_6_BIT 32
#define SPELL_7_BIT 64
#define SPELL_8_BIT 128
#define SPELL_9_BIT 256
#define SPELL_10_BIT 512
#define SPELL_11_BIT 1024
#define SPELL_12_BIT 2048
#define SPELL_13_BIT 4096
#define SPELL_14_BIT 8192
#define COOP_1_BIT 16384
#define COOP_2_BIT 32768
#define COOP_3_BIT 65536

//Prop set in players when entering a training room, how far they
//can train.
#define COLLEGE_I_MAXTRAIN "_college_i_maxtrain"


