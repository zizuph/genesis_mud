/*
 * Copyright notice, please read.
 *
 * Copyright Chalmers Datorf|rening, 1992
 *
 * You are welcome to read this file for information & education purposes.
 * However, you are expressly forbidden to copy this code for use in any
 * other mud. This code is part of Genesis and we want Genesis to remain
 * unique. You must invent your own world on your own mud.
 *
 */

#pragma save_binary
#pragma strict_types

inherit "/std/creature.c";
inherit "/std/combat/unarmed";   /* This gets us standard unarmed routines */

#include <stdproperties.h>
#include <macros.h>
#include <cmdparse.h>
#include <money.h>
#include <ss_types.h>
#include <wa_types.h>

#include "../defs.h"

static void give_note(string who);

void
create_creature()
{
    set_name("ratty");
    add_name(({"rat", "rattus", "domesticus"}));
    set_adj(({"furry", "black"}));
    set_living_name("_ratty_");
    set_short("furry black rattus domesticus");
    set_race_name("rattus domesticus");
 
              /* str dex con int wis dis */
    set_stats(({   5, 10,  5, 10, 20,  5 }));
    set_hp(10000); /* Heal fully */

    set_skill(SS_DEFENCE, 20);
    set_skill(SS_UNARM_COMBAT, 10);
    
    set_attack_unarmed(0, 8, 8, W_IMPALE, 30, "teeth");

    set_hitloc_unarmed(0, ({ 1, 1, 1 }), 20, "head");
    set_hitloc_unarmed(1, ({ 1, 1, 1 }), 80, "body");

    add_prop(CONT_I_WEIGHT, 100);
    add_prop(CONT_I_HEIGHT, 50);
    add_prop(CONT_I_VOLUME, 100);

    /* Triggers */
    trig_new("%w 'drops' %s", "react_drop");
    trig_new("%w 'gives' 'you' %s", "react_give");
}

void
deposit_coins()
{
    object *inv;
    int i, num;
    string kind;

    inv = all_inventory(TO);

    for (i = 0 ; i < sizeof(inv) ; i++)
    {
	if (file_name(inv[i])[0..9] == "/std/coins")
	{
	    num = inv[i]->num_heap();
	    kind = inv[i]->query_adj() + " " + inv[i]->query_name();
	    command("deposit " + num + " " + kind);
	}
	else
	    command("drop " + inv[i]->query_name());
    }
}

void
delay_drop(string who)
{
    if (!present("coin", ETO))
	return;

    command("take 10 coins");
    command("snicker");
    set_alarm(1.0, 0.0, deposit_coins);

    give_note(who);
}

void
delay_give(string who)
{
    if (!present("coin", TO))
	return;

    command("smile");
    set_alarm(1.0, 0.0, deposit_coins);

    give_note(who);
}

void
react_drop(string dropper, string what)
{
    set_alarm(1.0, 0.0, &delay_drop(dropper));
}

void
react_give(string giver, string what)
{
    set_alarm(1.0, 0.0, &delay_give(giver));
}

static void
give_note(string who)
{
    object note, *pls, *inv;
    int num, i;

    if (parse_command(lower_case(who), ETO, "%l", pls))
        pls = VISIBLE_ACCESS(pls, "show_allow", TO);

    if (!sizeof(pls))
	return;

    inv = all_inventory(TO);
    if (file_name(inv[i])[0..9] == "/std/coins")
	num = inv[i]->num_heap();
    else
	num = 0;
    
    if (pls[0]->query_race() == "elf" && num >= 5)
    {
	pls[0]->catch_msg(QCTNAME(TO) + " scurries up your leg,\nputs something in your hand and promptly jumps back to the ground again.\n");

	tell_room(ETO, QCTNAME(TO) + " scurries up " + QTNAME(pls[0]) + "'s leg\nonly to jump back to the ground again. Amazing!\n", ({ TO, pls[0] }));

	note = clone_object(D_OBJ + "ratty_note.c");
	note->set_owner(pls[0]->query_real_name());
	note->move(pls[0], 0);
    }
}

public int
show_allow(object pl)
{
    if (environment(pl) == environment(this_player()) && TO != pl)
        return 1;
    return 0;
}
