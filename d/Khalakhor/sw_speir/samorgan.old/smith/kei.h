
/*
 * /d/Cirath/tyr/bonesmith/kei.h
 *
 * Definitions for the blacksmith in SaMorgan.
 *
 * Contains defines for the armours, weapons, and 
 * functions of the smith (Kei) NPC
 *
 * Fylo, Feb 2000
 *
 * Modification log: Added shields Damaris 9/2002
 */
/* Misc defines */

#include "defs.h"

#define BS(x)            break_string((x), 75)
#define BSN(x)           (BS(x) + "\n")
#define RESPOND(x) if (present(this_player(), environment())) \
                   command("say to " + this_player()->query_real_name() + " " + x)

/* Armour defines */

#define TENT_ARM_FILE TYR_BONESMITH + "kei_arm.c"
#define TENT_STD_WEP_FILE TYR_BONESMITH + "kei_std_wep.c"
#define TENT_OBS_WEP_FILE TYR_BONESMITH + "kei_obs_wep.c"

#define MAT_AC    0
#define MAT_SLA   1
#define MAT_IMP   2
#define MAT_WGT   3
#define MAT_PRI   4
#define MAT_CON   5
#define MAT_BRK   6
#define MAT_VRB   7
#define MAT_LNG   8

#define CON_AC    0
#define CON_WGT   1
#define CON_LNG   2

#define ARM_TYPE 0
#define ARM_WGT  1

#define ARM_MAP ([\
"chestplate":  ({A_TORSO, 100}),\
"helm":        ({A_HEAD, 35}),\
"greaves":     ({A_LEGS, 45}),\
"bracers":     ({A_ARMS, 45}),\
"gauntlets":   ({A_HANDS, 15}),\
"boots":       ({A_FEET, 20}),\
"shield":      ({A_SHIELD, 100})\
])

#define MAT_MAP ([\
"tempered iron": ({27, 1, 1, 75, 500, 8, 9, "pounded",                        \
                  "Made of iron taken from the legendary iron mines "        +\
                  "of SaMorgan, it is a rare site outside the armouries of "      +\
                  "the King. The iron is well known for its high quality "   +\
                  "and the blacksmiths of SaMorgan are experts in its use. When " +\
                  "crafted into armour it is first blackened, and then "     +\
                  "tempered to increase its strength. It is shaped using "   +\
                  "special creases and bends requiring much less metal, "    +\
                  "making it lighter without sacrificing protection."}),      \
"braxat shell": ({25,  -1, 2, 70, 300, 5, 7, "carved",                        \
                  "Made from the rock hard plates that cover the "           +\
                  "back of a braxat. The plates are thick and "              +\
                  "can be worked much like bone. The material is "           +\
                  "light but extremely hard to penetrate. When made "        +\
                  "into armour the plates are carved and hollowed to "       +\
                  "fit different parts of the body."}),                       \
"jozhal hide": ({20, 1, 1, 65, 200, 3, 4, "worked",                           \
                  "Crafted from the tough hide of an Athasian jozhal, "     +\
                  "the leather like material is very light and protective. " +\
                  "Large sheets of hide are repeatedly soaked and dried "    +\
                  "to stiffen and harden the leather, it is then cut and "   +\
                  "and oil is rubbed into the skin to make it workable."})    \
])

#define CON_MAP ([\
"thin": ({3, 3, " extra thin, making it lighter and trapping less heat, "    +\
                "but also a little less protective and durable."}),           \
"thick": ({3, 5, " for fit and form, but left as thick as possible to "      +\
                 "provide the greatest protection and strength, it also "    +\
                 "makes it a little heavier."})                               \
])
 
#define MAX_BOUGHT_AC 35
#define VOL_STAND 50
#define WGT_STAND 50


/* Smith & Wep defines */
                   
#define LIVE_I_GAVE_TENTAVVAR_MATERIALS "_live_i_gave_kei_materials"

#define WAX_COST     20    /* Waxing costs 20% per point */
#define SHARPEN_COST 20    /* Sharpening as well */
#define MEND_COST    30    /* Mending is a little more */

#define MONEY_TYPE ({ "cc", "sc", "gc", "pc" })

#define F_RANGE_RANDOM(orig, max, min, value)                              \
        ((orig) - (orig)*((min)*100 + ((max)-(min)) * (100-(value)))/10000 \
        + random(2*(orig)*((min)*100 + ((max)-(min)) * (100-(value))) / 10000))
        
#define WEP_MATERIAL ({"obsidian", "bone", "black steel"})

#define WEP_HANDS ({"one-handed", "two-handed"})

#define OBS_TYPES ({"brown", "mahogany", "lizard-skin", "flame-red",         \
                    "jet-black", "deep-green", "midnight-lace",              \
                    "snowflake", "rainbow", "gold-sheen", "silver-sheen"})
                    
#define FINISH_TYPES ({ "shiny", "dull", "gleaming", "polished", "glassy",   \
                        "glossy", "rough", "cold" })

#define WEP_TYPE (["sword":   W_SWORD,    \
                   "axe":     W_AXE,      \
                   "halberd": W_POLEARM,  \
                   "club":    W_CLUB,     \
                   "knife":   W_KNIFE     \
])

#define STD_DAMAGE_TYPE ([\
   "sword":    W_SLASH|W_IMPALE,\
   "halberd":  W_SLASH|W_BLUDGEON|W_IMPALE,\
   "club":     W_BLUDGEON,\
   "axe":      W_SLASH,\
   "knife":    W_SLASH|W_IMPALE\
])

#define OBS_DAMAGE_TYPE ([\
   "sword":    W_SLASH|W_IMPALE,\
   "halberd":  W_SLASH|W_BLUDGEON|W_IMPALE,\
   "club":     W_SLASH|W_BLUDGEON,\
   "axe":      W_SLASH|W_BLUDGEON,\
   "knife":    W_SLASH|W_IMPALE\
])

#define WEP_NAME ([\
   "sword":    ({"sword"}),\
   "halberd":  ({"halberd"}),\
   "club":     ({"club"}),\
   "axe":      ({"battleaxe", "axe"}),\
   "knife":    ({"knife"})\
])

