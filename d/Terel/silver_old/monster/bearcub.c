/* This comment tells emacs to use c++-mode  -*- C++ -*- */

/*
 * bearcub.c
 *
 * Janus 920620
 * modified by Sorgum 941002
 */

#include "/d/Terel/include/Terel.h"

inherit STDCREATURE;

inherit "/std/combat/unarmed";
inherit "/std/act/domove";
inherit "/std/act/action";
inherit "/std/act/attack";

#include "../local.h"
#include <wa_types.h>
#include <ss_types.h>
#include <filter_funs.h>

/*
 * Function name: create_creature
 * Description:   Create the creature.
 */
public void
create_creature()
{
    ::create_creature();
    set_name(({"bear","bearcub"}));
    set_short("dark brown bearcub");
    set_long("A small dark brown bearcub, running around in the " +
	     "snow. It doesnt seem to be afraid of you.  Perhaps it knows " +
	     "that it's mother will protect it.\n");
    set_adj(({"small", "brown", "furry"}));
    set_race_name("bear");
    set_alignment(0);
    set_stats(({5, 4, 7, 3, 3, 10}));
    PASSIVE;
    set_act_time(11);

    add_act(({"sniff", "flip", "growl", "@@do_tackle"}));
    SET_MAX_HP;
    set_gender(random(2));
    set_skill(SS_CLIMB, random(25));
    set_skill(SS_DEFENCE, random(5));
    add_prop(OBJ_I_WEIGHT, 7500);
    add_prop(OBJ_I_VOLUME, 8000);
    set_whimpy(1);
    ADDSKIN;
    ADDMEAT(2);
}

/*
 * Function name: do_tackle
 * Description:   Act to tackle a random player in the room.
 */
public void
do_tackle()
{
    int i;
    object *oblist;

    oblist = FILTER_PLAYERS(all_inventory(ETO));
    if (sizeof(oblist) == 0)
	return;
    
    command("tackle " + oblist[ random(sizeof(oblist)) ]->query_race_name());
}
    
#define A_BITE  0
#define A_LPAW  1
#define A_RPAW  2
#define A_BHUG  3

#define H_HEAD 0
#define H_BODY 1
#define H_LEGS 2

public void
cr_configure()
{
    add_attack(3, 6, W_SLASH,   20, A_BITE);
    add_attack(5, 5, W_BLUDGEON,35, A_RPAW);
    add_attack(5,5,W_BLUDGEON,  35, A_LPAW);
    add_attack(10,8,W_BLUDGEON, 10, A_BHUG);

    add_hitloc( ({ 2, 2, 2 }), 15, "head", H_HEAD);
    add_hitloc( ({ 3, 3, 3 }), 60, "body", H_BODY);
    add_hitloc( ({ 3, 3, 3 }), 25, "legs", H_LEGS);
}

public string
cr_attack_desc(int aid)
{
    switch(aid) {
    case A_BITE: return "bite";
    case A_RPAW: return "right front paw";
    case A_LPAW: return "left front paw";
    case A_BHUG: return "bearhug";
    }
    return "mind"; /* should never occur */
}
