/* Created by ?
 *
 * Revised by Stralle @ Genesis: 000921
 *   Easily configured weapon and armour selection
 *   Doing things when encountering people of certain occ guilds
 *   Removed silly emotes, added additional through having added
 *    the dragonarmy command soul in them.
 *
 * #define MOVED_TO_KRYNN when all files have been copied where they
 *                        are supposed to be.
 */

#ifndef _KRYNN_DRACONIAN_H_
#define _KRYNN_DRACONIAN_H_

#define SPLAINS "/d/Krynn/solamn/splains/obj/"
#define NERAKA  "/d/Krynn/neraka/obj/"
#define LAKE    "/d/Krynn/solace/lake/obj/"
#define AWEP    "/d/Ansalon/common/wep/"

#define ROUNDS_INBETWEEN_SMART_FIGHTING 4

#ifndef UNIQUE
#define UNIQUE(filen,num,alternatefile) ((!((filen)->load_file()) && \
      sizeof(filter(object_clones(find_object(filen)), \
      (&operator(==)(0) @ &->query_prop("_obj_i_broken")))) \
      < num) ? filen : alternatefile)
#endif                        


#define DSOUL(x) ("/d/Ansalon/guild/dragonarmy/soul/dragonarmy_" + (x) + \
    "_soul")

#define DRACONIAN "/d/Krynn/std/draconian"

#define DRAC_ADJS ({ "snarling", "alarming", "raging", "vigourous", \
    "unnerving", "swaying", "flexing", "intimidating", "calculating", \
    "hypnotizing", "frowning", "hissing", "dangerous", "teeth-bearing", \
    "sniffing" })

#define DRAC_ADJS2 ({ "sinewy", "lithe", "vicious", "energetic", "bulky", \
    "eager", "cautious", "sleek", "canny", "defiant", "fearless", \
    "lethargic", "razor-taloned",  "hideous", "blunt-nosed", "astute" })

#define GET_DRAC_ADJ(x) (x[random(sizeof(x))])

/* All strings within the arrays are commands to be made by us.
 * %s is substituted with the name of the player we encounter
 * '*' are everyone else. Only occupational guilds are checked.
 */
#define DRAC_MEET ([ "Dragonarmy" : ({ "dsalute %s" }), \
                     "Priests of Takhisis" : ({ "dnod %s" }), \
                     "Solamnian Knights" : ({ "dponder %s" }), \
                     "*" : ({ "dlook %s" }) ])

#define DRAC_ACTS ({ /* "emote shows you its claws.", \ */ \
    "emote snarls: What are you doing here?", \
/*    "emote snarls: You are not supposed to be here, get lost!",*/ \
/*    "emote shows you the finger, or rather, its middle claw.",*/ \
    "frown", \
    "grin", \
    "dshield", \
    "dburp", \
/*    "emote snarls: Do you want me to spill out your guts?",*/ \
    "snicker", \
    "laugh evilly all", \
    "scream", \
/*    ({"say Get lost you peasant!", "laugh evilly"}), */ \
/*    "glare evilly all", */ \
/*    "kick all", */ \
/*    "emote grunts: Hey you fool, get out of here.", */ \
    "emote snarls: Knights think they can fight? Ha!", \
    "growl", \
    "emote gruffs: I would like to have some elven meat for lunch today.", \
    "emote snarls: Are you supposed to be here or should I sound the alarm?", \
})

#define MOVETYPES   ({ "feints deceptively", "dances around", \
    "lunges quickly", "ducks low", "moves fast", "strikes rapidly" })

#define WEPDEGREE   ({ ({ /* Slash weapons */ \
    ({ "pricks", "lightly", "superficially", "just barely" }), \
    ({ "scratches", "mildly", "barely" }), \
    ({ "jabs", "quickly", "meanly" }), \
    ({ "cuts", "painfully" }), \
    ({ "slices", "deeply" }), \
    ({ "pierces", "wickedly" }), \
    ({ "slashes", "expertly" }), \
    ({ "stabs", "fiercely" }), \
    ({ "carves", "to pieces" }), \
    ({ "cleaves", "cruelly" }), \
    ({ "wounds", "greviously" }), \
    ({ "devastates", "completely" }), \
    ({ "destroys", "utterly" }) }), \
   ({ /* Impale weapons */ \
    ({ "pricks", "lightly", "superficially", "just barely" }), \
    ({ "scratches", "mildly", "barely" }), \
    ({ "grazes", "sharply" }), \
    ({ "gashes", "deeply" }), \
    ({ "tears", "painfully" }), \
    ({ "pierces", "wickedly" }), \
    ({ "shears", "to ribbons" }), \
    ({ "punctures", "deeply", "with a quick thrust" }), \
    ({ "rips", "to pieces" }), \
    ({ "impales", "without mercy" }), \
    ({ "wounds", "greviously" }), \
    ({ "devastates", "completely" }), \
    ({ "destroys", "utterly" }) }), \
   ({ /* Bludgeon weapons */ \
    ({ "brushes", "lightly", "softly", "with little force", }), \
    ({ "bruises", "mildly" }), \
    ({ "hits", "hard" }), \
    ({ "pounds", "solidly" }), \
    ({ "hammers", "painfully" }), \
    ({ "pummels", "soundly" }), \
    ({ "trashes", "viciously" }), \
    ({ "smashes", "forcefully" }), \
    ({ "crushes", "violently" }), \
    ({ "slams", "powerfully" }), \
    ({ "wounds", "greviously" }), \
    ({ "devastates", "completely" }), \
    ({ "destroys", "utterly" }) }) })

/* Weapons and armours are chosen in this fashion:
 *
 * In a decrementive loop, check level of monster.
 * When level > WEAPONS[x * 2] (0, 2, 4, ..) take that array and
 * examine it. Each number is a percentual possobility for the
 * string|array|array of array to be chosen.
 *
 * string - pick that weapon/armour
 * array - pick all of the weapons/armours
 *
 * This can be recursive so doing
 *  ({ ({ "a", 50, "b", 50 }), ({ "c", 100 }) })
 * would always pick c and either of a and b
 *
 *
 * An empty string is indicated by a chance of not picking anything at all.
 */
#define WEAPONS ({ \
    0, \
      ({ SPLAINS + "bflance", 17, SPLAINS + "bdagger", 17, \
         SPLAINS + "bhandaxe", 17, NERAKA + "dr_knife", 16, \
         NERAKA + "dr_spear", 16, SPLAINS + "bshortsword", 17 \
      }), \
    3, \
      ({ NERAKA + "dr_stsword", 33, SPLAINS + "bmace", 33, \
         NERAKA + "dr_sword", 34 \
      }), \
    5, \
      ({ SPLAINS + "bsabre", 33, NERAKA + "dr_axe", 33, \
         NERAKA + "dr_sword", 34 \
      }), \
    7, \
      ({ SPLAINS + "bsword", 50, LAKE + "drac_sword", 50 }), \
    9, \
      ({ SPLAINS + "bbattleaxe", 66, \
        ({ ({ SPLAINS + "bsword", 50, SPLAINS + "bsabre", 50 }), \
           ({ SPLAINS + "bsword", 33, SPLAINS + "bsabre", 33, \
              SPLAINS + "bmace", 34 }) \
        }), 33 \
      }), \
    11, \
      ({ AWEP + "pole/aurak_halberd", 11, \
         SPLAINS + "bbattleaxe", 11, \
         SPLAINS + "bknife", 9, \
         ({ LAKE + "st_scimitar", SPLAINS + "bsword" }), 33, \
         ({ ({ SPLAINS + "bsword", 50, SPLAINS + "bsabre", 50 }), \
            ({ SPLAINS + "bsword", 33, SPLAINS + "bsabre", 33, \
               SPLAINS + "bmace", 34 }) \
         }), 66 \
      }), \
    14, \
      ({ AWEP + "pole/aurak_halberd", 33, \
	 SPLAINS + "bclaymore", 33, \
         ({ SPLAINS + "bsword", SPLAINS + "bknife" }), 34 \
      }), \
   })

#define ARMOURS ({ \
    0, \
    ({ ({ SPLAINS + "brobe", 100 }), \
       ({ SPLAINS + "bhelmet", 20, SPLAINS + "bboots", 20, \
	  SPLAINS + "bshield", 20, "", 40 }) \
    }), \
    3, \
      ({ ({ SPLAINS + "barmour3", 100 }), \
         ({ SPLAINS + "bhelmet", 20, SPLAINS + "bshield", 20, \
	    SPLAINS + "bboots", 20, "", 40 }) \
      }), \
    5, \
      ({ ({ SPLAINS + "barmour3", 100 }), \
         ({ SPLAINS + "bshield", 25, SPLAINS + "bheavyboots", 25, \
		SPLAINS + "blargeshield", 25, "", 25 }) \
      }), \
    7, \
      ({ ({ SPLAINS + "barmour2", 100 }), \
       ({ SPLAINS + "bshield", 25, SPLAINS + "bleggings", 25, \
	      SPLAINS + "bheavyboots", 25, SPLAINS + "blargeshield", 25 }) \
      }), \
    11, \
      ({ ({ SPLAINS + "barmour1", 100 }), \
	 ({ SPLAINS + "blargeshield", 25, SPLAINS + "bleggings", 25, \
            SPLAINS + "bshinguard", 25, SPLAINS + "bheavyboots", 25 }) \
      }), \
    13, \
      ({ ({ SPLAINS + "barmour1", 100 }), \
         ({ SPLAINS + "blargeshield", 50, "", 50 }), \
         ({ SPLAINS + "bleggings", 50, SPLAINS + "bshinguard", 50 }), \
         ({ SPLAINS + "bdragonhelm", 50, SPLAINS + "bheavyboots", 50 }) \
      }), \
    14, \
      ({ SPLAINS + "bdragonarm", \
         SPLAINS + "bshinguard", \
	 SPLAINS + "bheavyboots", \
         SPLAINS + "bdragonhelm" \
      }), \
    15, \
      ({ \
	  SPLAINS + "bdragonarm", \
          SPLAINS + "bshinguard", \
          SPLAINS + "bheavyboots", \
          SPLAINS + "bdragonhelm" \
      }) \
    })

/* The item limits had to be moved here since otherwise 
 * They would be evaluted for all weapons when the item arrays where 
 * assigned to a variable. 
 */
#define LIMITS ([ \
        SPLAINS + "bbattleaxe" : ({ 3, SPLAINS + "bmace" }), \
        SPLAINS + "bdragonarm" : ({ 3, SPLAINS + "barmour1" }), \
   AWEP + "pole/aurak_halberd" : ({ 5, SPLAINS + "bknife" }), \
            SPLAINS + "bknife" : ({ 6, SPLAINS + "bsword" }), \
         SPLAINS + "bclaymore" : ({ 8, SPLAINS + "bknife" }), \
               ])

#define SPELLCASTING "/d/Genesis/magic/spellcasting"

/* Death objects */
#define LIGHTNING   "/d/Krynn/common/monster/lightning"
#define FLAMES      "/d/Krynn/common/monster/flame_remains"
#define ACID        "/d/Krynn/common/monster/acid_remains"
#define STATUE      "/d/Krynn/common/monster/stonecorpse"
#define KAPAK_POISON_SH "/d/Krynn/common/monster/kapak_poisoneffect"

/* Valid draconian types */
#define BAAZ  0
#define KAPAK 1
#define BOZAK 2
#define SIVAK 3
#define AURAK 4

#define DRAC_RACE ({"baaz", "kapak", "bozak", "sivak", "aurak"})

#endif _KRYNN_DRACONIAN_H_
