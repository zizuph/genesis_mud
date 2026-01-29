
 /* Spirit Circle of Psuchae Defs */

#ifndef SPIRIT_GUILD_NAME
#define SPIRIT_GUILD_NAME      "Spirit Circle of Psuchae"
#endif
#define SPIRIT_GUILD_TYPE      "occupational"
#define SPIRIT_GUILD_STYLE     "cleric"
#define SPIRIT_GUILD_TYPE_LAY  "layman"
#define SPIRIT_GUILD_STYLE_LAY "cleric"
#define SPIRIT_GUILD_POST       "/d/Calia/guilds/scop/temple/post_office"

#define SCOP_GURU_GROUP       2
#define SCOP_GURU_BIT        11
#define SCOP_GURU_EXP       250

#define SPIRIT_GUILD_BASE_TAX  13
#define SPIRIT_GUILD_TAX_LAY    7

#define SPELL_TAX_LEVEL_ONE   1
#define SPELL_TAX_LEVEL_TWO   2
#define SPELL_TAX_LEVEL_THREE 1
#define SPELL_TAX_LEVEL_FOUR  5
#define SPELL_TAX_LEVEL_FIVE  2
#define SPELL_TAX_LEVEL_SIX   3
#define SPELL_TAX_LEVEL_SEVEN 3
#define SPELL_TAX_LEVEL_EIGHT 2

#define SPELLS_ONE_FLAG       1
#define SPELLS_TWO_FLAG       2
#define SPELLS_THREE_FLAG     4
#define SPELLS_FOUR_FLAG      8
#define SPELLS_FIVE_FLAG     16
#define SPELLS_SIX_FLAG      32
#define SPELLS_SEVEN_FLAG    64
#define SPELLS_EIGHT_FLAG   128

#define ALL_SPELL_LEVELS (SPELLS_ONE_FLAG | SPELLS_TWO_FLAG | SPELLS_THREE_FLAG | SPELLS_FOUR_FLAG | SPELLS_FIVE_FLAG | SPELLS_SIX_FLAG | SPELLS_SEVEN_FLAG | SPELLS_EIGHT_FLAG)

#define SPIRIT_GUILD_TAX(chosen) \
        (SPIRIT_GUILD_BASE_TAX + \
        ((chosen & SPELLS_ONE_FLAG) ? SPELL_TAX_LEVEL_ONE : 0) + \
        ((chosen & SPELLS_TWO_FLAG) ? SPELL_TAX_LEVEL_TWO : 0) + \
        ((chosen & SPELLS_THREE_FLAG) ? SPELL_TAX_LEVEL_THREE : 0) + \
        ((chosen & SPELLS_FOUR_FLAG) ? SPELL_TAX_LEVEL_FOUR : 0) + \
        ((chosen & SPELLS_FIVE_FLAG) ? SPELL_TAX_LEVEL_FIVE : 0) + \
        ((chosen & SPELLS_SIX_FLAG) ? SPELL_TAX_LEVEL_SIX : 0) + \
        ((chosen & SPELLS_SEVEN_FLAG) ? SPELL_TAX_LEVEL_SEVEN : 0) + \
        ((chosen & SPELLS_EIGHT_FLAG) ? SPELL_TAX_LEVEL_EIGHT : 0))
        
#define FIRST_LEVEL_SPELL_LIST   ({"spazopetra", "exevrisko","fos","magikos"})
#define SECOND_LEVEL_SPELL_LIST  ({"siopi","vekpos"})
#define THIRD_LEVEL_SPELL_LIST   ({"skiamorfi", "niktamati"})
// removed eirini
#define FOURTH_LEVEL_SPELL_LIST  ({"giatreou","therapeaou","sfyri", "syskotisi"})
#define FIFTH_LEVEL_SPELL_LIST   ({"skiamati", "tharos"})
// removed bdella
#define SIXTH_LEVEL_SPELL_LIST   ({"anakalo","apergo", "elefrinisi"})
#define SEVENTH_LEVEL_SPELL_LIST ({"anagnorizo","metaballo"})
#define EIGHTH_LEVEL_SPELL_LIST  ({"tihosskias", "oneiro"})

#ifndef SS_CARVED
#define SS_CARVED             114050
#endif

#ifndef SS_PUNISHMENT
#define SS_PUNISHMENT         114051
#endif

#ifndef SS_PATRON_ELEMENTAL
#define SS_PATRON_ELEMENTAL   114052
#endif

#define SS_SPIRIT_TITLE       114020
#define SS_ELEMENT_SPIRIT     114021
#define SS_SPIRIT_PUNISHMENT  114022
#define SS_SPIRIT_CHOSEN      114023
#define SS_SPELLS_CASTED      114024

#define CASTED_LIMIT    250000

#define FIRE_FLAG 1
#define EARTH_FLAG 2
#define AIR_FLAG 4
#define WATER_FLAG 8

#define NO_PUNISHMENT      0
#define SPELL_BANNED       1
#define TRAIN_BANNED       2
#define EXPELLED           3
#define REMOVE_PUNISHMENTS 4
#define A_PROMOTED         5
#define M_PROMOTED         6
#define E_DEMOTED          7
#define M_DEMOTED          8
#define TEMPLE_RESTRICTED  9

#define SPEECH_HP_COST     25
#define SPEECH_MANA_COST   10
#define SPIRIT_FAMILIAR_SUMMONED  "_spirit_familiar_summoned"

#define KNEELING_OBJECT           "_kneeling_object"
#define ANOINTED_OBJECT           "_anointed_object"
#define CEREMONIAL_GARB           "_ceremonial_garb"
#define CEREMONIAL_ROBE           "_ceremonial_robe"
#define INCENSE_CLOUD             "_incense_cloud"
#define INCENSE_QTY               "_incense_qty"
#define CEREMONIAL_LAYOBJ         "_ceremonial_layobj"
#define CEREMONIAL_LAYOBJ_FNPROP  "_ceremonial_layobj_fname_prop"
#define CEREMONIAL_LAYOBJ_SPROP   "_ceremonial_layobj_second_prop"
#define CEREMONIAL_LAYOBJ_FILE    SPIRIT_OBJECTS+"layobj.c"
#define SPIRIT_CUTTING_KNIFE      "_ceremonial_dagger"
#define HIDE_LAYMAN_TITLE         "_hide_layman_title"

#define OBJ_I_ELEMENTAL_STAFF         "_obj_i_elemental_staff"
#define LIVE_I_PURIFIED_SPIRIT_ITEMS  "_live_i_purified_spirit_items"
#define LIVE_I_PLACED_SPIRIT_CYLINDER "_live_i_placed_spirit_cylinder"
#define LIVE_I_PLACED_SPIRIT_TRIANGLE "_live_i_placed_spirit_triangle"
#define LIVE_I_PLACED_SPIRIT_SYMBOL   "_live_i_placed_spirit_symbol"
#define LIVE_I_ON_SPIRIT_GURU_QUEST   "_live_i_on_spirit_guru_quest"

#ifndef IS_MEMBER
#define IS_MEMBER(x)  ((x)->query_guild_name_occ() == SPIRIT_GUILD_NAME || (x)->query_guild_name_occ() == "Elemental Clerics of Calia")
#endif
                    
#define WORSTART       "/d/Calia/worshippers/temple/startroom"
#define WORSHIPSOUL    "/d/Calia/worshippers/specials/worshipsoul"
#define WORSHIPSHADOW  "/d/Calia/worshippers/specials/worshipshadow"

#define SPIRIT_TRAINER "/d/Calia/guilds/scop/temple/training_room"
#define SPIRIT_START "/d/Calia/guilds/scop/temple/startroom"

#define MEMBER_LIST_UTILITY "/d/Calia/guilds/scop/specials/member_list_utility"
