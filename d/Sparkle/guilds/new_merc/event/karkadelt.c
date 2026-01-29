/*
 *  /d/Genesis/imbuement/npc/enchanter.c
 *
 *  This is Karkadelt the Enchanter. He is two important things:
 *
 *    - The main quest npc for the Orc Temple quests in Sparkle.
 *    - The interface for players who wish to learn about and participate
 *      in the imbuement system.
 *
 *  Created October 2010, by Cooper Sherry (Gorboth)
 */
#pragma strict_types

inherit "/std/monster";

#include <cmdparse.h>
#include <composite.h>
#include <filter_funs.h>
#include <formulas.h>
#include <macros.h>
#include <money.h>
#include <ss_types.h>
#include <stdproperties.h>
#include <time.h>
#include "/d/Sparkle/sys/quests.h"


/* Definitions */
#define            ENCHANTER_DIARY_CHECK "_imbue_diary_check"
#define            ALREADY_SEEN          "_imbue_already_seen"
#define            NULLSTONE_ADVICE      "_imbue_nullstone_advice"
#define            ID_CONFIRMATION       "_imbue_confirmed_id_payment"
#define            IMBUE_CONFIRMATION    "_imbue_confirmed_imbue_payment"
#define            STONE_CONFIRMATION    "_imbue confirmed_nullstone"
#define            AMULET_CONFIRMATION   "_imbue_confirmed_amulet"
#define            DIS_CONFIRMATION      "_imbue_confirmed_disenchant"
#define            TRANS_CONFIRMATION    "_imbue_confirmed_transmogrify"
#define            DISENCHANT_VETERAN    "_imbue_veteran_disenchanting"
#define            TRANS_VETERAN         "_imbue_veteran_transmogrifying"
#define            DATA_OBJ    ("/d/Sparkle/area/city/obj/vendor_master")

#define            IMBUE_COST          1000
#define            STONE_COST          25
#define            LAPIDARIUM_COST     10
#define            IDENTIFY_COST       100
#define            DISENCHANT_REWARD   5
#define            IMBUE_FILE(n)       (extract((n), 0, 0) + "/" + (n))
#define            DIARY_NUM_FILE      "enchanter_diary"

/* Prototypes */
public void        create_monster();


/* 
 * Function name:       create_sparkle_npc
 * Description  :       This function overrides the one in the base class
 * Arguments    :       none
 * Returns      :       void/nothing
 */
public void
create_monster()
{
    set_living_name("karkadelt");
    set_name("karkadelt");
    add_name( ({ "enchanter", "_imbuement_enchanter_npc" }) );
    set_race_name("half-elf");
    add_adj( ({ "dressed", "ornately", }) );

    set_title("the Enchanter, Master of the Arcane");

    set_short("ornately dressed enchanter");
    set_long("Robes of magenta with many rings of rare stones stitched"
      + " around a tight-fitting cowl adorn this imposing individual."
      + " His every movement is quiet, and yet utterly decisive, with"
      + " a poise and dignity that might suggest noble upbringing. Though"
      + " unmistakably elven, the features of his sharply-lined face are"
      + " clearly mixed with something other, as a darker and harder"
      + " bloodline also struggles to make itself known.\n");

    set_stats( ({ 130, 190, 90, 300, 500, 500 }) ); /* He is impressive. */
    set_alignment(0); /* He serves his own loyalties, and none other. */

    remove_prop(LIVE_I_NEVERKNOWN);
    add_prop(OBJ_M_NO_ATTACK, "Just as you begin to make your move,"
      + " the enchanter touches one of the brightly coloured stones"
      + " on his robes, and a shockwave jolts your body. After a moment"
      + " of painful tingling, you find that your violent impulse has"
      + " been replaced by a respect for this person's power.\n");

    set_skill(SS_UNARM_COMBAT, 20);      /* Just a bit here ... */
    set_skill(SS_ALCHEMY, 100);          /* A grandmaster.      */
    set_skill(SS_AWARENESS, 100);        /* He sees much.       */
    set_skill(SS_SPELLCRAFT, 100);       /* Master of magic.    */
    set_skill(SS_FORM_ENCHANTMENT, 100); /* THE grandmaster.    */
    set_skill(SS_FORM_DIVINATION, 100);  /* Utterly proficient  */
    set_skill(SS_APPR_OBJ, 100);         /* He sees deeply.     */

    remove_prop(LIVE_M_NO_ACCEPT_GIVE);

    setuid();
    seteuid(getuid());
} /* create_sparkle_npc */   


