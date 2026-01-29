/*
 *  /d/Genesis/imbuement/imbuement.h
 *
 *  This header file supplies the imbuement code with various definitions.
 *
 *  Created October 2009, by Cooper Sherry (Gorboth)
 */

#define        IMBUE_DIR     "/d/Genesis/imbuement/"
#define        SHADOW_DIR    IMBUE_DIR + "shadows/"

#define        IMBUE_MASTER  (IMBUE_DIR + "imbuement_generator")
#define        STONE_MASTER  (IMBUE_DIR + "stone_master")
#define        LAPID_MASTER  (IMBUE_DIR + "lapidarium_master")

#define        IMBUE_SHORT   "_obj_s_imbue_short"
#define        IMBUE_TRY     "_obj_i_imbue_try"

#define        STONE_NAME    "_imbuement_container_stone"

#define        QUEST_WEAPON  "_imbuement_quest_dagger"
#define        QUEST_JOURNAL "_imbuement_quest_read_journal"
#define        QUEST_FLUTE   "_imbuement_quest_bone_flute"
#define        QUEST_DEMON   "_imbuement_quest_demon_object"
#define        QUEST_TEAR    "_imbuement_quest_tear"

#define        ORC_TEMPLE_QUEST_PROP  "_enchanter_orc_temple_instructions"

#define        IMBUE_M_ID    "There is a hidden power lurking in this item.\n"

#define        POWER_DESC   ([ 1 : "faint",        \
                               2 : "pronounced",   \
                               3 : "intense" ])

#define        A_POWER_DESC   ([ 1 : "a faint",        \
                               2 : "a pronounced",   \
                               3 : "an intense" ])

#define        CA_POWER_DESC   ([ 1 : "A faint",        \
                               2 : "A pronounced",   \
                               3 : "An intense" ])

#define        POWER_LEVEL_DESC  ([ 1: "low",      \
                                    2: "medium",   \
                                    3: "high" ])

#define        NULL_IMBUE                "None"

#define        IMBUE_SPECIAL_STRIKE_RATE  5

#define        IMBUE_HIT_CHANCE_LOW      10
#define        IMBUE_HIT_CHANCE_MEDIUM   20
#define        IMBUE_HIT_CHANCE_HIGH     33

#define        IMBUE_ELEMENTAL_PEN_LOW   10
#define        IMBUE_ELEMENTAL_PEN_MED   25
#define        IMBUE_ELEMENTAL_PEN_HIGH  50

#define        IMBUE_BANE_PEN_EXTRA      16

#define TELL_G(x) find_living("gorboth")->catch_msg("DEBUG: " + x + "\n");
