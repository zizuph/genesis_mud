/* This comment tells emacs to use c++-mode  -*- C++ -*- */

/*
 * ew_gloves.c
 *
 * Mergula's gloves.
 */

#include "/d/Terel/include/Terel.h"
inherit STDARMOUR;

#include <wa_types.h>
#include <ss_types.h>

#define MAX_TIMES     10

static int no_times;

void
create_armour()
{
    set_name(({"gloves", "pair of gloves"}));
    set_pname("pairs of gloves");
    set_short("pair of black gloves");
    set_pshort("pairs of black gloves");
    set_long("It's a pair of black gloves. They are made of leather.\n");
    set_adj(({"black", "leather"}));

    set_default_armour(20, A_HANDS, 0, 0);

    set_af(this_object());

    add_prop(OBJ_I_WEIGHT, 1200);
    add_prop(OBJ_I_VOLUME,  600);
    add_prop(OBJ_M_NO_BUY, 1);
    add_prop(OBJ_I_IS_MAGIC_ARMOUR, 1);
    add_prop(MAGIC_AM_MAGIC, ({40, "conjuration"}));
    add_prop(MAGIC_AM_ID_INFO,
	({"This is Mergula's pair of magical gloves. If worn they " +
	  "will increase your swiftness in combat.\n", 30,
	  "However, their magical strength will " +
	  "diminish everytime you remove them.\n", 60}));
    add_prop(OBJ_I_VALUE, 578);
}

int
wear()
{
    no_times++;
    if (no_times <= MAX_TIMES) {
	this_player()->set_stat_extra(SS_DEX, MAX_TIMES + 1 - no_times);
        set_alarmv(2.0, -1.0, "wmsg", ({this_player(), "You feel quicker " +
	       "as you wear the " + short() + ".\n"}));
    }
    if (interactive(this_player())) set_likely_cond(12);
    return 0;
}

int
remove()
{
    if (no_times <= MAX_TIMES) {
        this_player()->set_stat_extra(SS_DEX, 0);
        set_alarmv(2.0, -1.0, "wmsg", ({this_player(), "You feel normal " +
	       "again as you remove the " + short() + ".\n"}));
    }
    return 0;
}

void
wmsg(object who, string msg)
{
    if (who) who->catch_msg(msg);
}

string
query_recover()
{
    return MASTER + ":" + query_arm_recover() + "#nt#" + no_times + "##";
}

void
init_recover(string arg)
{
    string foobar;

    init_arm_recover(arg);
    if (sscanf(arg, "%s#nt#%d##", foobar, no_times) != 2) {
	no_times = MAX_TIMES + 1;
    }
}
