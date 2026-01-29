/*   Thanks to Vladimir for his help with all of the Hobbit project
 *   This file is based on Varl's traveller insignia, which has
 *   passed through many changes, mostly Vladimir's.
 *   Used for the Adventuresome Hobbits guild
 *   Dunstable, Oct 1994
 * 
 *  Made the pipe actually somekable!
 *  Igneous, August 1996 
 *
 *  General Update and Improvements 
 *  Igneous, Feb 1998
 */
#pragma save_binary
#pragma strict_types

inherit "/std/object";

#include <macros.h>
#include <stdproperties.h>
#include <composite.h>
#include "/d/Shire/sys/defs.h"
#include "/d/Shire/hobbit/hobbit.h"

// Global Vars
int  Puff_time, Smoke_time, Smoking;
string Flavour;

void
create_object()
{
    set_name("pipe");
    add_adj(({"large","brown"}));
    add_name("_hobbit_race_guild_pipe_");
    set_short("large brown pipe");
    set_long("This is a large brown pipe, the Adventuresome Hobbits' "+
      "guild item.\nUse 'help hobbit' for more "+
      "information.\n");

    add_prop(OBJ_I_WEIGHT,  20);
    add_prop(OBJ_I_VOLUME,   5);
    remove_prop(OBJ_I_VALUE);
    add_prop(OBJ_M_NO_DROP,  1);
    add_prop(OBJ_M_NO_STEAL, 1);
    Smoking = 0;
}

void
puff(object player)
{
    player->catch_tell("You take a puff from your pipe, savouring "+
      "the wonderful "+ Flavour +" smoke.\n");
    say(QCTNAME(player)+" takes a puff from "+HIS_HER(player)+" pipe, "+ 
      "savouring the "+Flavour+" smoke.\n", ({player}));
}

void
timeout(object player)
{
    remove_alarm(Puff_time);
    remove_alarm(Smoke_time);
    Puff_time = 0;
    Smoke_time = 0;
    Smoking = 0;
    player->catch_tell("Your pipe has run out of tobacco!!\n");
    say(QCTNAME(player)+"'s pipe has run out of tobacco and "+
      HE_SHE(player) +" ceases to smoke.\n", ({player}));
    return;
}

int
hsmoke(string str)
{
    string tob_type;
    int duration;
    object tobacco;

    if (Smoking)
    {
	notify_fail("But you haven't finished your last batch of pipe-weed.\n");
	return 0;
    }
    if (!str)
	str = "tobacco";
    tobacco = present(str, TP);
    //       Wizards always get to smoke!!!
    if (!tobacco && !tobacco->query_is_tobacco())
    {
	notify_fail("You have no tobacco to put in your pipe!\n");
	return 0;
    }
    if (function_exists("create_herb", tobacco))
    {
	if (!tobacco->query_dried())
	{
	    NF("Your "+tobacco->short()+" needs to be dried first before you can "+
	      "smoke it!\n");
	    return 0;
	}
    }
    if (tobacco && tobacco->query_is_tobacco())
    {
	duration = tobacco->query_prop(OBJ_I_VALUE) * 10;
	if (!duration)
	    duration = tobacco->query_herb_value();
	tob_type = tobacco->query_short();
	Flavour = tobacco->query_flavour();
	tobacco->remove_object();
    }
    else
    {
	duration = 6000;
	tob_type = "longbottom leaf tobacco";
	Flavour = "longbottom leaf";
    }
    Puff_time = set_alarm(1.0, itof(random(15)+15), &puff(TP));
    Smoke_time = set_alarm(itof(duration), 0.0, &timeout(TP));
    Smoking = 1;
    write("You quickly fill your pipe with some "+tob_type+" and immediately "+
      "light it.  As you start to inhale the wonderful pipe-weed "+
      "smoke, you smile happily, thoroughly enjoying it.\n");
    say(QCTNAME(TP)+" stuffs some "+tob_type+" into "+HIS_HER(TP)+" pipe "+
      "and then proceeds to light it.  "+CAP(HE_SHE(TP))+" smiles happily "+
      "as "+HE_SHE(TP)+" exhales the wonderful pipe-weed smoke.\n");
    return 1;
}

int
extinguish(string str)
{
    if (!str || str != "pipe")
    {
	notify_fail("Extinguish what?\n");
	return 0;
    }
    if (!Smoking)
    {
	notify_fail("Extinguishing a non-lit pipe??  How foolish of you.\n");
	return 0;
    }
    remove_alarm(Puff_time);
    remove_alarm(Smoke_time);
    Puff_time = 0;
    Smoke_time = 0;
    Smoking = 0;
    write("You decide to cease smoking, by extinguishing your pipe.\n");
    say(QCTNAME(TP)+" ceases to smoke "+HIS_HER(TP)+" pipe by "+
      "extinguishing it.\n");
    return 1;
}

int
query_pipe_is_smoking()
{
    return Smoking;
}

string
query_pipe_smoke_flavour()
{
    return Flavour;
}

void
init()
{
    ::init();
    add_action(hsmoke,     "hsmoke");
    add_action(extinguish, "extinguish");
}
