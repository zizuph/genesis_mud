/* This comment tells emacs to use c++-mode  -*- C++ -*- */

/*
 * goblic.c
 *
 * A small goblin. Mortricia 921027 
 * modified by Sorgum 941226
 */

#include "/d/Terel/include/Terel.h"

inherit STDMONSTER;

inherit "/std/act/action";
inherit "/std/act/seqaction";
inherit "/std/act/domove";

#include <ss_types.h>
#include <wa_types.h>
#include <money.h>

#define ALIGN           50

object check_sh_pr(string sh_desc, string prop, object ob);

object last_obj;

/*
 * Function name: init_living
 * Description:   Add the 'command items' of this object. 
 */
public void
init_living()
{
    ::init_living();
    add_action("do_show", "show");
}

/*
 * Function name: create_monster
 * Description:   Create the monster. (standard)
 */
public void
create_monster()
{
    if (!IS_CLONE)
        return;

    ::create_monster();
    set_name("goblin");
    set_short("small goblin");
    set_long("It's a small goblin. You wonder what he is doing here?\n");
    set_adj("small");
    set_gender(MALE);
    set_race_name("goblin");

    add_prop(LIVE_I_NEVERKNOWN, 1);

    set_stats(({15, 15, 15, 30, 30, 30}));
    SET_MAX_HP;
    SET_MAX_MANA;
    set_alignment(random(ALIGN) - ALIGN / 2);
 
    set_skill(SS_UNARM_COMBAT, 15);
    set_skill(SS_AWARENESS,    15);

    set_all_hitloc_unarmed(15);
    set_all_attack_unarmed(50, 15);

    set_act_time(10);
    add_act("smile");

    set_alarm(1.0, -1.0, "dress_me");
}

dress_me()
{
    object cloak, knife;

    FIX_EUID;
    knife = clone_object(ENCHANT_DIR + "weapon/knife");
    knife -> move(TO);
    cloak = clone_object(ENCHANT_DIR + "armour/cloak");
    cloak -> set_short("red cloak");
    cloak -> set_adj("red");
    cloak -> set_long("It's a red cloak.\n");
    cloak -> move(TO);
    command("wield knife");
    command("wear cloak");
}

object
check_sh_pr(string sh_desc, string prop, object ob)
{
    int i;
    object *ob_arr, r_ob;

    r_ob = 0;
    ob_arr = all_inventory(ob);
    for(i=0; i<sizeof(ob_arr); i++) {
	if (ob_arr[i]->query_short() == sh_desc &&
	    ob_arr[i]->query_prop(prop) == ob->query_name()) {
	    r_ob = ob_arr[i];
	}
    }
    return r_ob;
}

do_show(string what)
{
    object ring, key, ob1, ob2;
    string who, whom;

    NF("Show what?\n");
    if (!what) return 0;

    if (!parse_command(what, environment(), "%o 'to' %o", ob1, ob2)) {
	if (!parse_command(what, environment(), "%o", ob1)) return 0;
	ob2 = TO;
    }
    if (!ob1) return 0;
    NF("Show "+ob1->short()+" to whom?\n");
    if (!ob2) return 0;
    if (!living(ob2)) return 0;
    NF("You show the "+ob1->short()+" to yourself!?\n");
    if (ob2 == TP) return 0;

    ring = check_sh_pr("gold ring", "q_solver", TP);
    who = lower_case(TP -> query_name());
    TP->catch_msg("You show the "+ob1->short()+" to "+QTNAME(ob2)+".\n");
    ob2->catch_msg(QCTNAME(TP) + " shows you the " +
		     ob1->short()+".\n");
    tell_room(environment(TP), QCTNAME(TP) +
			       " shows something to " +
                               QTNAME(ob2) +
			       ".\n", ({TP, ob2}));
    if (ring == ob1 && ob2 == TO && TP != last_obj) {
	key = clone_object(ENCHANT_DIR + "obj/key");
	key -> add_prop("key_owner", TP->query_name());
	TO -> command("whisper " + who + " Here is a key.\n");
    last_obj = TP;
	if(key -> move(TP)) {
	    write("Oops! You cannot carry it!\n");
	    key -> move(environment(TP));
	}
        TO -> command("smile " + who);
    } else {
        TO -> command("stare " + who);
    }
    return 1;
}

