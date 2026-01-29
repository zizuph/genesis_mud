/*
 *  /d/Genesis/imbuement/imbuement.h
 *
 *  This header file supplies the imbuement code with various definitions.
 *
 *  Created October 2009, by Cooper Sherry (Gorboth)
 */

#define        IMBUE_DIR     "/d/Genesis/imbuement/"
#define        SHADOW_DIR    IMBUE_DIR + "shadows/"
#define        IMBUE_LOG_DIR IMBUE_DIR + "log/"
#define        IMBUE_OBJ_DIR IMBUE_DIR + "obj/"

#define        IMBUE_MASTER  (IMBUE_DIR + "imbuement_master")
#define        IMBUE_GENERATOR  (IMBUE_DIR + "imbuement_generator")
#define        STONE_MASTER  (IMBUE_DIR + "stone_master")
#define        LAPID_MASTER  (IMBUE_DIR + "lapidarium_master")
#define        RECOVER_OBJ   IMBUE_DIR + "obj/recoverer"

#define        IMBUE_SHORT   "_obj_s_imbue_short"
#define        IMBUE_TRY     "_obj_i_imbue_try"

#define        CRAFT_STATUS  "_imbuement_crafting_status"

#define        IMBUE_M_ID    "There is a hidden power lurking in this item.\n"

#define        STONE_NAME    "_imbuement_container_stone"
#define        LAPIDARIUM    "_imbuement_lapidarium"

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

#define        POWER_SHORT  ([ 1 : "unusual",        \
                               2 : "peculiar",   \
                               3 : "exotic" ])

#define        NULL_IMBUE                "None"

#define        IMBUE_SPECIAL_STRIKE_RATE 20

#define        IMBUE_HIT_CHANCE_LOW      10
#define        IMBUE_HIT_CHANCE_MEDIUM   20
#define        IMBUE_HIT_CHANCE_HIGH     33

#define        IMBUE_ELEMENTAL_PEN_LOW   10
#define        IMBUE_ELEMENTAL_PEN_MED   25
#define        IMBUE_ELEMENTAL_PEN_HIGH  50

#define        IMBUE_BANE_PEN_EXTRA      16

#define         COL_OBJ     0
#define         COL_TY1     1
#define         COL_LV1     2
#define         COL_TY2     3
#define         COL_LV2     4
#define         COL_TY3     5
#define         COL_LV3     6
#define         COL_STA     7
#define         COL_REC     8

#define         send_debug_message(tag, input)    \
                    "/d/Genesis/imbuement/debugger_tell"->  \
                    send_debug_message2(tag, input, 0); \
                    find_living("gorboth")->catch_msg("DEBUG: " + input + "\n")

#define TELL_G(x) find_living("gorboth")->catch_msg("DEBUG: " + x + "\n");find_living("lavellan")->catch_msg("DEBUG: " + x + "\n")

