/*
 *	/d/Gondor/ithilien/emyn-arnen/obj/scabbard
 *
 *	Copyright (c) 1997 by Christian Markus
 *
 * 	Part of the reward for solving the Battlestandard quest.
 *
 *	Olorin
 *
 *	Modification log:
 *	22-Feb-97, Olorin:	Added logging.
 *	13-Apr-98, Gnadnar:	Mask enter_env(), similar to current
 *				mask of leave_env().
 */
#pragma save_binary
#pragma strict_types

inherit "/std/container.c";
inherit "/lib/keep.c";

#include <cmdparse.h>
#include <macros.h>
#include <stdproperties.h>
#include <wa_types.h>

#include "/d/Gondor/defs.h"

#define SCABBARD_SUBLOC		"_scabbard_subloc"
#define SCABBARD_MASTER		(ITH_DIR + "emyn-arnen/obj/scabbard_master")

static object  Worn = 0;

public void
create_container()
{
    set_name("scabbard");
    add_name("_emyn_arnen_scabbard");
    set_short("golden scabbard");
    set_adj(({"golden", "ancient"}));
    set_long(BSN("A valuable scabbard, probably very ancient. "
	+ "It is made from wood plated with pure gold. In the "
	+ "scabbard you can sheathe a sword, and from it you "
	+ "can draw it again when you have to fight. You can "
	+ "also wear it, and later remove it again."));

    add_prop(OBJ_M_NO_SELL, 1);
    add_prop(OBJ_I_NO_STEAL, 1);
    add_prop(CONT_I_WEIGHT,  2000);
    add_prop(CONT_I_VOLUME,  2000);
    add_prop(CONT_I_MAX_WEIGHT, 50000);
    add_prop(CONT_I_MAX_VOLUME, 25000);
    add_prop(CONT_I_TRANSP, 1);
    add_prop(CONT_I_RIGID,  0);
    add_prop(CONT_M_NO_INS, "If you want to insert a sword into the "
      + "scabbard, then try to 'sheathe' it!\n");
    add_prop(OBJ_S_WIZINFO, BSN(
	"This scabbard is part of the quest reward for retrieving the "
	+ "battlestandard of the Witchking of Angmar. It can be used "
	+ "to sheathe a sword. The scabbard will auto_load and it can "
	+ "not be sold in shops, but it can be lost, dropped, given away."));
}

static int
filter_weapon(object x)
{
    return (function_exists("create_object", x) == "/std/weapon");
}

static int
filter_sword(object x)
{
    return (x->query_wt() == W_SWORD);
}

public int
do_sheathe(string str)
{
    int     result;
    object *sword,
    tp = TP;

    if (!str)
	sword = tp->query_weapon(-1);
    else
	sword = filter(FIND_STR_IN_OBJECT(str, tp),
	  "filter_weapon", TO);

    sword = filter(sword, "filter_sword", TO);

    if (sizeof(sword) != 1)
    {
	NF("Sheathe which sword?\n");
	return 0;
    }

    if (sizeof(all_inventory(TO)))
    {
	NF("You cannot sheathe your "+sword[0]->short()
	  + ", there is already "+LANG_ASHORT(all_inventory(TO)[0])
	  + " in the "+TO->short()+".\n");
	return 0;
    }

    if ( sword[0]->query_wielded() == TP )
    {
	sword[0]->unwield_me();
	if ( sword[0]->query_wielded() == TP )
	{
	    NF("You cannot unwield your "+sword[0]->short()+".\n");
	    return 0;
	}
    }

    remove_prop(CONT_M_NO_INS);
    if (result = sword[0]->move(TO))
    {
	switch(result)
	{
	case 1:
	    NF("Your "+sword[0]->short()+" is too heavy for the "
	      + TO->short()+".\n");
	    break;
	case 8:
	    NF("Your "+sword[0]->short()+" is too large for the "
	      + TO->short()+".\n");
	    break;
	default:
	    NF("Strangely, you cannot sheathe your "+sword[0]->short()
	      + " in the "+ TO->short()+".\n");
	    break;
	}
	return 0;
    }
    if(objectp(environment(tp)))
	environment(tp)->update_light(1);
    tp->catch_msg("You sheathe your "+sword[0]->short()+".\n");
    tell_room(ENV(tp), QCTNAME(tp)+" sheathes "+POSSESSIVE(tp)+" "
      + sword[0]->short()+".\n", tp);
    add_prop(CONT_M_NO_INS, 1);

    return 1;
}

public int
do_draw(string str)
{
    object *sword,
    tp = TP;
    mixed res;



    if (!str)
	sword = all_inventory(TO);
    else
	sword = FIND_STR_IN_OBJECT(str, TO);

    if (!sizeof(sword))
    {
	if (!str)
	    NF("Your "+TO->short()+" is empty!\n");
	else
	    NF("There is no "+str+" in your "+TO->short()+"!\n");
	return 0;
    }
    tp->catch_msg("You draw your "+sword[0]->short()+"!\n");
    tell_room(ENV(tp), QCTNAME(tp)+" draws "+POSSESSIVE(tp)+ " "
      + sword[0]->short()+".\n", tp);
    if (sword[0]->move(tp))
	sword[0]->move(tp, 1);

    if (stringp(res = sword[0]->command_wield()))
    {
        write(res);
    }

    return 1;
}

public string
query_auto_load()
{
    setuid();
    seteuid(getuid());
    SCABBARD_MASTER->check_owner(ENV(TO));
    return MASTER + ":";
}

public int
do_wear(string str)
{
    object *sc,
    tp = TP;

    if (!str)
	return 0;

    sc = FIND_STR_IN_OBJECT(str, tp);

    if (member_array(TO, sc) == -1)
    {
	NF("Do you want to wear the scabbard?\n");
	return 0;
    }

    if (objectp(Worn))
    {
	NF("You are already wearing it!\n");
	return 0;
    }

    if (member_array(SCABBARD_SUBLOC, tp->query_sublocs()) > -1)
    { 
	write("You already wear another scabbard!\n");
	return 1;
    } 

    tp->add_subloc(SCABBARD_SUBLOC, TO);
    write("You wear the "+TO->short()+" around your hips.\n");
    say(QCTNAME(TP) + " wears the "+TO->short()+" around "
      + tp->query_possessive() + " hips.\n");
    add_prop(OBJ_M_NO_DROP, "Remove the scabbard first!\n");
    Worn = tp;
    TO->set_no_show_composite(1); /* do not display in inventory */
    return 1;
}

public int
do_remove(string str)
{
    object *sc,
    tp = TP;

    if (!str)
	return 0;

    sc = FIND_STR_IN_OBJECT(str, tp);

    if (member_array(TO, sc) == -1)
    {
	NF("Do you want to remove the scabbard?\n");
	return 0;
    }

    if (!objectp(Worn))
    {
	NF("You are not wearing it!\n");
	return 0;
    }

    tp->remove_subloc(SCABBARD_SUBLOC);
    write("You remove the "+TO->short()+".\n");
    say(QCTNAME(TP) + " removes the "+TO->short()+".\n");
    remove_prop(OBJ_M_NO_DROP);
    Worn = 0;
    TO->set_no_show_composite(0);  /* display in inventory again */
    return 1;
}

public void
enter_env(object dest, object old)
{
    string  msg;

    ::enter_env(dest, old);

    if (!objectp(old) || !objectp(dest) || !interactive(dest))
	return;

    FIX_EUID;
    SCABBARD_MASTER->check_owner(dest);
    msg = dest->query_name();
    if (!living(old))
	msg += " picked up the scabbard from " + file_name(old);
    else if (interactive(old))
	msg += " got the scabbard from " + old->query_name();
    else
	msg += " got the scabbard from " + old->query_name() + " (" +
	file_name(old) + ")";
    msg += ". " + ctime(time()) + ".\n";
    log_file("scabbard", msg);
}

public void
leave_env(object old, object dest)
{
    string  msg;

    TP->remove_subloc(SCABBARD_SUBLOC);
    TO->unset_no_show_composite();
    remove_prop(OBJ_M_NO_DROP);

    ::leave_env(old, dest);

    if (!objectp(dest) || !objectp(old) || !interactive(old))
	return;

    FIX_EUID;
    SCABBARD_MASTER->remove_owner(old);
    msg = old->query_name();
    if (!living(dest))
	msg += " dropped the scabbard in " + file_name(dest);
    else if (interactive(dest))
	msg += " gave the scabbard to " + dest->query_name();
    else
	msg += " gave the scabbard to " + dest->query_name() + " (" +
	file_name(dest) + ")";
    msg += ". " + ctime(time()) + ".\n";
    log_file("scabbard", msg);
}

public string
show_subloc(string subloc, object on, object for_obj)
{
    string data;

    if(subloc == SCABBARD_SUBLOC)
    {
	if (for_obj != on)
	    data = capitalize(on->query_pronoun()) + 
	    " is wearing "+LANG_ASHORT(TO)+".\n";
	else
	    data = "You are wearing "+LANG_ASHORT(TO)+".\n";
	return data;
    }
    return 0;
}

public int query_recover() { return 0; }

void
init()
{
    ::init();

    add_action(do_sheathe, "sheathe");
    add_action(do_draw,    "draw");
    add_action(do_wear,    "wear");
    add_action(do_remove,  "remove");
}

public object
query_worn()
{
    return Worn;
}
