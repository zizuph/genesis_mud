/* This comment tells emacs to use c++-mode  -*- C++ -*- */

/*
 * unicorn.c
 *
 * A rare unicorn. Mortricia 920917 
 * modified by Sorgum 941226
 */

#include "/d/Terel/include/Terel.h"

inherit STDCREATURE;

inherit "/std/combat/unarmed";
inherit "/std/act/action";
inherit "/std/act/domove";
inherit "/std/act/seqaction";

#include <wa_types.h>
#include <ss_types.h>

/*
 * Function name: create_monster
 * Description:   Create the monster. (standard)
 */
public void
create_creature()
{
    ::create_creature();
    set_name("unicorn");
    set_short("rare unicorn");
    set_long("It's a rare unicorn. " +
	     "It looks like a horse but has a horn on its head. " +
	     "There aren't many enchanted creatures like this " +
	     "left in the world today.\n");

    set_adj("rare");
    set_race_name("unicorn");
    set_stats(({65, 65, 65, 65, 65, 65}));
    SET_MAX_HP;
    set_alignment(231);
    set_gender(NEUTER);

    set_skill(SS_DEFENCE,   60 + random(5));
    set_skill(SS_AWARENESS, 80 + random(5));

    add_prop(LIVE_I_NEVERKNOWN, 1);
    add_prop(LIVE_I_QUICKNESS,  100);
    
    add_prop(OBJ_I_WEIGHT, 150000);
    add_prop(OBJ_I_VOLUME,  90000);
    
    add_prop(CONT_I_MAX_WEIGHT, 180000);
    add_prop(CONT_I_MAX_VOLUME, 140000);

    add_item(({"horn"}), "The horn is very pointed.\n");
    add_item(({"hoofs"}), "The hoofs are sharp.\n");
}

/*
 * Function name: query_object_list
 * Description:   return list of equipment
 */
public string*
query_object_list()
{
    return ({
            ENCHANT_DIR + "obj/meat",
            ENCHANT_DIR + "obj/meat",
            ENCHANT_DIR + "obj/meat",
            ENCHANT_DIR + "obj/meat"		
		});
}

#define A_HORN  0
#define A_CLAW  1

#define H_HEAD 0
#define H_BODY 1
#define H_LEGS 2

public void
cr_configure()
{
    add_attack(75, 75, W_IMPALE, 50, A_HORN);
    add_attack(30, 30, W_SLASH,  50, A_CLAW);

    add_hitloc( ({ 30, 30, 20 }), 30, "head", H_HEAD);
    add_hitloc( ({ 35, 35, 45 }), 40, "body", H_BODY);
    add_hitloc( ({ 20, 20, 20 }), 30, "legs", H_LEGS);
}

public string
cr_attack_desc(int aid)
{
    switch(aid)
    {
     case A_HORN:return "horn";
     case A_CLAW:return "hoofs";
    }
}
