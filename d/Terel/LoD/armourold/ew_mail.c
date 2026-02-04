/* This comment tells emacs to use c++-mode  -*- C++ -*- */

/*
 * ew_mail.c
 *
 * Mergula's sword.
 */

#include "/d/Terel/include/Terel.h"

inherit STDARMOUR;
#include <wa_types.h>

#define EVIL_LIM -100

void
create_armour()
{
    set_name("ringmail");
    set_short("blackened steel ringmail");
    set_long("It's a blackened steel ringmail of superb "+
	     "dwarfish quality.\n");
    set_adj("steel");
    add_adj("blackened");

    set_default_armour(42, A_BODY, 0, 0);
    set_am(({ 0, 8, -8}));

    set_af(this_object());

    add_prop(OBJ_I_WEIGHT, 11000);
    add_prop(OBJ_I_VOLUME,  6000);
    add_prop(OBJ_M_NO_BUY, 1);

    add_prop(OBJ_I_IS_MAGIC_ARMOUR, 1);
    add_prop(MAGIC_I_RES_FIRE, ({3, 1}));
    add_prop(MAGIC_AM_MAGIC, ({20, "enchantment"}));
    add_prop(MAGIC_AM_ID_INFO,
	({"This ringmail has been made by the dwarf Realin when he " +
	  "was captured by the legion of darkness. Mergula forced " +
	  "Realin to make it somewhat resistant against fire by " +
	  "using black magic.\n", 10,
	  "The wearer must be evil to fully make use of it.\n", 50}));
}

string
query_recover()
{
    return MASTER + ":" + query_arm_recover();
}

void
init_recover(string arg)
{
    init_arm_recover(arg);
}

int
wear()
{
    int fire;

    fire = TP->query_prop(MAGIC_I_RES_FIRE);
    TP->add_prop(MAGIC_I_RES_FIRE, fire+1);
    if (TP->query_alignment() < EVIL_LIM) {
        set_alarm(1.0, -1.0, "delay_msg", TP,
                  "You feel comfortable in this " + short() + ".");
        change_prop(MAGIC_I_RES_FIRE, ({15, 1}));
    }
}

int
remove()
{
    int fire;

    fire = TP->query_prop(MAGIC_I_RES_FIRE);
    TP->add_prop(MAGIC_I_RES_FIRE, fire-1);
    change_prop(MAGIC_I_RES_FIRE, ({3, 1}));
}

void
delay_msg(object ob, string msg)
{
    if (ob) ob->catch_msg(msg + "\n");
}
