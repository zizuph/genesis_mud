//-*-C++-*-
// file name:    /d/Avenir/union/obj/band.c
// creator(s):   Cirion
// purpose:      To hold throwing knives
/*
 * Revisions:
 *	 Lilith, Jun 2004: Split out from band.c and fixed recovery bug.
 *                         Fixed other bugs, re-created a generic inheritable
 *                         rather then have several copies of the same thing.
 *       Lucius, Jul 2017: Re-Code.
 */
#pragma strict_types

inherit "/d/Genesis/std/wearable_pack";
inherit "/lib/keep";

#include <macros.h>
#include <language.h>
#include <wa_types.h>
#include <composite.h>
#include <stdproperties.h>

#include "../defs.h";

#define PACK_SUBLOC "_bandeleria_subloc"

public int knives;

private mixed check_ins(void);

public nomask int
union_bandeleria(void)	{ return 1; }

static void 
init_band(void)
{
    add_adj("union");
    set_short("bandeleria");
    set_long("It is a belt that can be worn over the shoulder "+
	"and down to the hips.\n");
}

static nomask void 
create_wearable_pack(void)
{
    set_adj("union");
    add_adj("unworn");
    set_name(({"bandeleria", BAND_ID, "belt", "bandolier"}));

    set_mass_storage(1);
    set_looseness(15);
    set_layers(2);
    set_cf(TO);
    set_slots(A_L_SHOULDER | A_CHEST);
    set_keep(1); 

    init_band();

    add_prop(CONT_M_NO_INS, check_ins);
    add_prop(CONT_I_TRANSP, 1);
    add_prop(CONT_I_WEIGHT, 3000); 
    add_prop(CONT_I_VOLUME, 3000); 
    add_prop(CONT_I_MAX_WEIGHT, 100000); 
    add_prop(CONT_I_MAX_VOLUME, 100000); 
    add_prop(CONT_I_REDUCE_VOLUME, 500);
    add_prop(CONT_I_REDUCE_WEIGHT, 500);

    add_prop(OBJ_I_VALUE, random(200) + (knives * 10));
    set_alarm(1.0, 0.0, &remove_name("pack"));

    if (IS_CLONE)
      set_item_expiration(); 
}

private string 
num_daggers(void)
{
    int num = sizeof(all_inventory(TO));

    if (num <= 1)
	return "";

    if (num >= knives)
    {
	return "All " + LANG_WNUM(knives) +
	    " pockets are full.";
    }
    else
    {
	return CAP(LANG_WNUM(num)) + " of the pockets have "+
	    "knives sheathed in them.";
    }
}

private mixed 
check_ins(void)
{
    if (sizeof(all_inventory(TO)) >= knives)
    {
	return "All " + LANG_WNUM(knives) + " pockets on the " +
	    short() + " are full.\n";
    }

    string verb = query_verb();

    if ((verb != "sheathe") && (verb != "fill"))
    {
	return "You can only fill the " + short() +
	    " with knives or daggers.\n";
    }

    return 0;
}

/* 
 * Display the pack sublocation 
 */
public string
show_subloc(string subloc, object on, object viewer)
{
    if (subloc != PACK_SUBLOC)
	return "";

    if (viewer != on)
    {
	return CAP(on->query_pronoun()) + " is wearing " +
	    LANG_ADDART(short()) + " across " +
	    on->query_possessive() + " shoulder and chest.\n";
    }
    else
    {
	return "You are wearing " + LANG_ADDART(short()) +
	    " across your shoulder and chest.\n";
    }
}

/* 
 * item_filter, used to filter out certain objects when shifting stuff 
 * in or out of pack, like non-sellables, non-droppables, 
 * containers etc. 
 */
public int
item_filter(object ob)
{
    if (ob->query_wt() != W_KNIFE)
	return 0;

    if (ob->query_prop(UNION_FLINGING))
	return 0;

    if (ob->query_prop(OBJ_I_BROKEN))
	return 0;

    if (ob->query_wielded())
	return 0;

    return 1;
}

public void
pack_fill_hook(object *moved)
{
    if (!sizeof(moved))
    {
	::pack_fill_hook(moved);
	return;
    }

    write("You sheathe " + COMPOSITE_DEAD(moved) +
	" in your " + short() + ".\n");
    tell_room(ENV(this_player()), QCTNAME(this_player()) +
	" sheathes " + COMPOSITE_DEAD(moved) + " in the " +
	short() + ".\n", this_player());
}

public int
pack_fill_fail(void)
{
    if (::pack_fill_fail())
	return 1;

    if (sizeof(all_inventory(TO)) >= knives)
    {
	write("All the pockets on the "+ short() +" are full.\n");
	return 1;
    }

    return 0;
}

public void
pack_empty_hook(object *moved)
{
    if (!sizeof(moved))
    {
	::pack_empty_hook(moved);
	return;
    }

    write("You draw out " + COMPOSITE_DEAD(moved) +
	" from the " + short() + ".\n");
    tell_room(ENV(this_player()), QCTNAME(this_player()) +
	" draws out " + COMPOSITE_DEAD(moved) + " from the " +
	short() + ".\n", this_player());
}

/* Can't open or close it */
public nomask varargs  int
close(object what)	{ return 2; }

public nomask varargs int
open(object what)	{ return 2; }

public nomask int
sheathe(string str)
{
    object *obs, knife;

    if (!strlen(str))
	return NF("Sheathe what where?\n");

    obs = filter(all_inventory(TP), &operator(==)(W_KNIFE) @ &->query_wt());

    if (!parse_command(str, obs, "[a] / [the] %o", knife))
	return NF("Sheathe what into your "+ real_short() +"?\n");

    if (knife->move(TO))
    {
	write(CAP(LANG_THESHORT(TO)) + " is already full.\n");
	return 1;
    }

    write("You sheathe "+ LANG_THESHORT(knife) +
	" in the highest pocket of your " + real_short() + ".\n");
    say(QCTNAME(TP) + " sheathes " + LANG_ASHORT(knife) +
	" in the highest pocket of " + HIS(TP) +
	" " + real_short() + ".\n");

    return 1;
}

public void
init(void)
{
    ::init();
    add_action(sheathe, "sheathe");
}

public varargs string
long(string str, object viewer)
{
    string desc = container::long(str, viewer);

    if (strlen(str))
	return desc;

    return desc + " It contains " + LANG_WNUM(knives) +
	" pockets, in which knives or daggers can be sheathed. "+
	num_daggers() + "\n";
}

public varargs string
short(object viewer)
{
    return real_short(viewer);
}

string
query_recover()
{
     return MASTER + ":" + query_container_recover() + query_item_expiration_recover();
}

void
init_recover(string arg)
{
    init_container_recover(arg);
    init_item_expiration_recover(arg);
}