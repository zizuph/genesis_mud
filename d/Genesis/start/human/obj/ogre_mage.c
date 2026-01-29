/*
 *	ogre_mage.c		Styles.   Mar 1993
 *
 *	This is the ogre mage that starts in the old ruin
 *	(ruin.c) north of Sparkle. 
 *
 *
 *	The ogre is cloned from the reset_room() function in
 *	ruin.c as seen below.
 *
 *  void
 *  reset_room()
 *  {
 *    int n;
 *  
 *    get_gem();
 *
 *    if (ogre)
 *        return;
 *
 *    ogre = clone_object(OBJ_DIR + "ogre_mage");
 *    ogre->arm_me();
 *    ogre->move_living("foobar", TO);
 *  }
 *
 *       Updated to possibly spawn an enchanted staff for
 *       newbies. Arman, January 2021.
 */

#pragma save_binary
#pragma strict_types

inherit "/std/monster";
inherit "/lib/unique";

#include <ss_types.h>
#include <macros.h>
#include <money.h>
#include <stdproperties.h>

#include "../defs.h"

string face();

#define MAGIC_STAFF   "/d/Genesis/start/human/obj/ogre_magi_staff"
#define HALBERD       "/d/Genesis/start/human/obj/halberd"

void
create_monster()
{
    if (!IS_CLONE)
	return;

    seteuid(getuid(this_object()));

    set_race_name("ogre mage"); 
    set_name("maharuk");
    set_living_name("maharuk");
    add_name("ogre");
    add_name("mage");
    set_adj(face());

    set_long("He eyes you suspiciously, looking for valuables.\n"+
	     "He looks quite determined and very strong.\n");

    set_base_stat(SS_STR, random(19)+13);
    set_base_stat(SS_DEX, 15);
    set_base_stat(SS_CON, 17);
    set_base_stat(SS_INT, 9);
    set_base_stat(SS_WIS, 12);
    set_base_stat(SS_DIS, 12);
    set_hp(10000); /* reduced to correct level according to con. */

    add_prop(CONT_I_WEIGHT, 140000);
    add_prop(CONT_I_HEIGHT, 2100);
    add_prop(CONT_I_VOLUME, 110000);

    set_random_move(20);
    set_aggressive(0);
    set_attack_chance(1);
    set_alignment(-300 - random(200));

    set_cact_time(1);
    add_cact("petrify");

    set_skill(SS_WEP_POLEARM, 29);
    set_skill(SS_WEP_SWORD, 22);
    set_skill(SS_WEP_KNIFE, 14);
    set_skill(SS_WEP_CLUB, 8);
    set_skill(SS_SPELLCRAFT, 20);
    set_skill(SS_ELEMENT_EARTH, 20);
}

string
face()
{
    string *faces;
    faces = ({"veteran", "grim", "grumpy", "experienced", "sturdy", "massive",
	      "big", "nasty", "angry", "mean", "dirty", "ugly", "foul",
	      "brutal", "battered", "savage", "ugly", "ugly"});
    return faces[random(sizeof(faces))];
}

void
arm_me()
{
    MONEY_MAKE(random(210)+180,"copper")->move(TO);
    MONEY_MAKE(random(50)+45, "silver")->move(TO);

    clone_unique(MAGIC_STAFF, 30, HALBERD)->move(TO);
    clone_object("/d/Genesis/start/human/obj/knife")->move(TO);
    command("wield staff");
    command("wield halberd");
}
