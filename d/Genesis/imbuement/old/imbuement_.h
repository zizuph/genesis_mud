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

#define        IMBUE_SHORT   "_obj_s_imbue_short"
#define        IMBUE_TRY     "_obj_i_imbue_try"

#define        IMBUE_M_ID    "There is a hidden power lurking in this item.\n"

#define        POWER_DESC   ([ 1 : "faint",        \
                               2 : "pronounced",   \
                               3 : "intense" ])

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


#define TELL_G(x) find_living("gorboth")->catch_msg("DEBUG: " + x + "\n")