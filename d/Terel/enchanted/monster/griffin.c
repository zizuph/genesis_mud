/* This comment tells emacs to use c++-mode  -*- C++ -*- */

/*
 * griffin.c
 *
 * A griffin. Mortricia 920917 
 * modified by Sorgum 941226
 */

#include "/d/Terel/include/Terel.h"

inherit STDCREATURE;

inherit "/std/combat/unarmed";
inherit "/std/act/action";
inherit "/std/act/domove";


#include <language.h>
#include <wa_types.h>
#include <ss_types.h>
#include <cmdparse.h>

#define TEREL_MEAT "Terel_meat"

//object check_na(string name, string adj, object ob);
object check_na(string name, string prop, object ob);


/*
 * Function name: init_living
 * Description:   Add the 'command items' of this object. 
 */
public void
init_living()
{
    ::init_living();
    add_action("do_offer", "offer");
    add_action("do_give",  "give");
}

/*
 * Function name: create_monster
 * Description:   Create the monster. (standard)
 */
public void
create_creature()
{
    if (!IS_CLONE)
        return;
    ::create_creature();
    set_name("griffin");
    set_short("silent griffin");
    set_long("It's a silent griffin. It stands here almost like a "+
	"statue. Its body is that of a lion while the head is that " +
	"of an eagle. Its eagle wings are folded along the body.\n");
    set_adj("silent");
    set_race_name("griffin");
    set_stats(({80, 80, 80, 80, 80, 80}));
    SET_MAX_HP;
    set_alignment(50);
    set_gender(NEUTER);

    set_skill(SS_DEFENCE,   77 + random(5));
    set_skill(SS_AWARENESS, 77 + random(5));

    add_prop(LIVE_I_NEVERKNOWN, 1);
    add_prop(LIVE_I_QUICKNESS,  100);
    
    add_prop(OBJ_I_WEIGHT, 300000);
    add_prop(OBJ_I_VOLUME, 290000);
    
    add_prop(CONT_I_MAX_WEIGHT, 380000);
    add_prop(CONT_I_MAX_VOLUME, 330000);

    add_item(({"body"}), "The body is that of a lion.\n");
    add_item(({"head"}), "The beak looks sharp.\n");
    add_item(({"wings"}), "The wings are folded along the body.\n");
}

#define A_BEAK  0
#define A_CLAW  1

#define H_HEAD 0
#define H_BODY 1
#define H_LEGS 2
#define H_LWING 3
#define H_RWING 4

public void
cr_configure()
{
    add_attack(80, 60, W_IMPALE, 40, A_BEAK);
    add_attack(60, 80, W_SLASH,  60, A_CLAW);

    add_hitloc( ({ 40, 30, 30 }), 20, "eagle head", H_HEAD);
    add_hitloc( ({ 50, 50, 60 }), 40, "lion body",  H_BODY);
    add_hitloc( ({ 40, 40, 40 }), 20, "legs",       H_LEGS);
    add_hitloc( ({ 20, 15, 20 }), 10, "left wing",  H_LWING);
    add_hitloc( ({ 20, 15, 20 }), 10, "right wing", H_RWING);
}

public string
cr_attack_desc(int aid)
{
    switch(aid)
    {
     case A_BEAK:return "beak";
     case A_CLAW:return "claws";
    }
}

do_offer(string what)
{
    object meat;

    NF("Offer what?\n");
    if (!what) return 0;

    if(what != "meat") return 0;

//    meat = check_na("meat","badger",TP);
    meat = check_na("meat",TEREL_MEAT,TP);
    TO -> command("sniff interest");
    if (!meat) {
	write("You don't have the proper meat.\n");
    } else {
	write("You offer the bloody meat to the griffin.\n");
	say(QCTNAME(TP) + " offers some meat to the griffin.\n");
	meat -> move(TO);
	TO -> command("eat meat");
	stop_quarrel(TP);
	write("The griffin pushes you eastwards.\n");
	TP -> move_living("east", ENCHANT_DIR + "ugnd4");
    }
    return 1;
}

object
//check_na(string name, string adj, object ob)
check_na(string name, string prop, object ob)
{
    int i;
    object *ob_arr, r_ob;

    r_ob = 0;
    ob_arr = all_inventory(ob);
    for(i = 0; i < sizeof(ob_arr); i++) {
	if (ob_arr[i]->query_name() == name &&
	    ob_arr[i]->query_prop(TEREL_MEAT)) {
	    r_ob = ob_arr[i];
	}
    }
    return r_ob;
}

do_give(string str)
{
    string s1, s2;
    object *obs;
    object ob1, ob2, meat;

    if(!str) return 0;
    if(sscanf(str, "%s to %s", s1, s2) != 2) return 0;

    obs = FIND_STR_IN_OBJECT(s1, TP);
    if (sizeof(obs)==0) return 0;
    ob1 = obs[0];
    if (ob1->query_name() != "meat") return 0;

    obs = FIND_STR_IN_OBJECT(s2, environment(TO));
    if (sizeof(obs)==0) return 0;
    ob2 = obs[0];
    if (ob2 != TO) return 0;

    ob1 -> move(ob2);
    write("You give "+LANG_ASHORT(ob1)+" to the "+ob2->short()+".\n");
    say(QCTNAME(TP) + " gives " + LANG_ASHORT(ob1) + " to the " +
		      ob2->short()+".\n");

    meat = check_na("meat", "bloody", TO);
    TO -> command("sniff interest");
    if (!meat) {
	TO->command("stare " + lower_case(TP->query_name()));
	write("It didn't like the "+ob1->short()+".\n");
    } else {
	TO -> command("eat meat");
	stop_quarrel(TP);
	write("The griffin pushes you eastwards.\n");
	TP -> move_living("east", ENCHANT_DIR + "ugnd4");
    }
    return 1;
}

void
stop_quarrel(object tp)
{
    int i;
    object *enemies;

    enemies = TO->query_enemy(-1);
    for (i=0; i<sizeof(enemies); i++) {
        if (enemies[i] == tp) {
            TO->stop_fight(tp);
            tp->stop_fight(TO);
            break;
        }
    }
}
