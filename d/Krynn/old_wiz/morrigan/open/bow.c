/*
 * Prototype bow by Morrigan
 * To do: add failure possibilities to stringing and notching
 *        chance to break string when shooting (string strength)
 */

#include "/d/Krynn/common/defs.h"
#include <macros.h>
#include <wa_types.h>
#include <ss_types.h>

inherit "/std/weapon";

#define SS_FLETCHERY E(TO)->query_skill(SS_WEP_MISSILE)
#define STRING_DIFF 10
#define NOTCH_DIFF 3

int gStrung = 0;
object gNotched = 0;

int query_strung()
{
    return gStrung;
}

set_strung(int strung)
{
    gStrung = strung;
}

object query_notched()
{
    return gNotched;
}

set_notched(object notched)
{
    gNotched = notched;
}

void create_weapon()
{
    set_name("bow");
    set_short("longbow");
    set_long("@@long_desc");
    set_default_weapon(1, 1, W_CLUB, W_BLUDGEON, W_BOTH);
}

string long_desc()
{
    return (query_strung() ? "A strung" : "An unstrung")+
    " longbow"+(query_notched() ? ", notched with an "+
      query_notched()->short()+".\n" : ".\n");
}

void init()
{
    add_action("notch_arrow", "notch");
    add_action("shoot", "shoot");
    add_action("string_bow", "string");
    ::init();
}

int string_bow(string str)
{
    object me = E(TO), bowstring, *inv;
    int i, try;


    NF("String what?\n");
    if (!TO->id(str))
	return 0;

    inv = all_inventory(E(TO));

    for (i = 0; i < sizeof(inv); i++)
	if (inv[i]->id("bowstring"))
	    bowstring = inv[i];

    NF("You have no bowstring to string your "+short()+" with.\n");
    if (!bowstring)
	return 0;

    if (STRING_DIFF > (try = random(SS_FLETCHERY)))
    {
	if (try <= 1)
	{
	    bowstring->remove_object();
	    write("You try, but fail to properly string your bow, breaking the "+
	      "bowstring in the process.\n");
	    say(QCTNAME(E(TO))+" tries, but fails to properly string "+
	      POSSESSIVE(E(TO))+" "+short()+", breaking a bowstring in the "+
	      "process.\n");
	    return 1;
	}

	write("You try, but fail to properly string your bow.\n");
	say(QCTNAME(E(TO))+" tries, but fails to properly string "+
	  POSSESSIVE(E(TO))+" "+short()+".\n");
	return 1;
    }  

    set_strung(1);
    bowstring->remove_object();
    write("You string your "+short()+".\n");
    say(QCTNAME(E(TO))+" strings "+POSSESSIVE(E(TO))+" "+short()+".\n");
    return 1;
}

int notch_arrow(string str)
{
    object me = E(TO), *inv, arrow;
    int i, try;

    NF("Notch what?\n");
    if (str != "arrow")
	return 0;

    NF("Your "+short()+" already has an arrow notched.\n");
    if (query_notched())
	return 0;

    NF("Your "+short()+" is not strung.\n");
    if (!query_strung())
	return 0;

    inv = all_inventory(E(TO));

    for (i = 0; i < sizeof(inv); i++)
	if (inv[i]->id("arrow"))
	    arrow = inv[i];

    NF("You have no arrow to notch.\n");
    if (!arrow)
	return 0;

    if (NOTCH_DIFF > (try = random(SS_WEP_MISSILE)))
    {
	if (try == 0)
	{
	    arrow->move(E(E(TO)));
	    write("You try to notch your "+arrow->short()+", but manage to drop it "+
	      "in the failed attempt.\n");
	    say(QCTNAME(E(TO))+" tries to notch a "+arrow->short()+", but drops it.\n");
	    return 1;
	}

	write("You try to notch your "+arrow->short()+", but fail to do so.\n");
	say(QCTNAME(E(TO))+" tries to notch a "+arrow->short()+", but fails.\n");
	return 1;
    }

    arrow->set_no_show();
    set_notched(arrow);
    write("You notch an arrow on your "+short()+".\n");
    say(QCTNAME(E(TO))+" notches a "+arrow->short()+" on "+POSSESSIVE(E(TO))+
      " "+short()+".\n");
    return 1;
}

/* VERY TEMPORARY */
int shoot(string str)
{
    object tar = find_living(str), arrow;

    NF("You do not find a "+C(str)+" to shoot.\n");
    if (!tar)
	return 0;

    NF("Your "+short()+" is not strung.\n");
    if (!query_strung())
	return 0;

    NF("You have no arrow notched on your "+short()+".\n");
    if (!query_notched())
	return 0;

    if (!random(10)) /* LOWER CHANCE, TESTING */
    {
	set_strung(0);
	arrow = query_notched();
	set_notched(0);
	arrow->unset_no_show();
	arrow->unset_no_show_composite();
	arrow->move(E(E(TO)));
	write("As you try to shoot, your bowstring breaks! The arrow notched "+
	  "falls to the ground.\n");
	say("As "+QTNAME(E(TO))+" tries to shoot "+POSSESSIVE(E(TO))+" "+short()+
	  ", the bowstring breaks!\n");
	return 1;
    }

    arrow = query_notched();
    set_notched(0);
    arrow->unset_no_show();
    arrow->unset_no_show_composite();
    arrow->move(tar);
    write("You shoot "+tar->query_the_name(E(TO))+".\n");
    say(QCTNAME(E(TO))+" shoots "+QTNAME(tar)+".\n", tar);
    tar->catch_msg(E(TO)->query_The_name(tar)+" shoots you.\n");
    return 1;
}

