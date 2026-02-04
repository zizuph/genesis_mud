/* This comment tells emacs to use c++-mode  -*- C++ -*- */

/*
 * ew_helmet.c
 *
 * Mergula's helmet.
 */

#include "/d/Terel/include/Terel.h"
inherit STDARMOUR;

#include <wa_types.h>
#include <ss_types.h>

#define MAX_TIMES    10

static int no_times;

void
create_armour()
{
    set_name("helmet");
    set_short("visored helmet of blackened steel");
    set_long(break_string(
      "It is a visored helmet covering not only the head but also a " +
      "large part of the face, neck and shoulders. It is a bit " +
      "ungainly but will provide a lot of protection. It is made " +
      "of blackened steel.\n", 72));
    set_adj("visored");
    add_adj("blackened");

    set_default_armour(29, A_HEAD, 0, 0);
    set_am(({ 2, 2, -4}));

    set_af(this_object());

    add_prop(OBJ_I_WEIGHT, 7700);
    add_prop(OBJ_I_VOLUME, 3000);
    add_prop(OBJ_M_NO_BUY, 1);
    add_prop(OBJ_I_IS_MAGIC_ARMOUR, 1);
    add_prop(MAGIC_AM_MAGIC, ({ 40, "conjuration" }));
    add_prop(MAGIC_AM_ID_INFO,
	({"This is Mergula's magical helmet. If worn it will increase " +
	  "your mental capacity.\n", 30,
	  "However, its magical strength will " +
	  "diminish everytime you remove them.\n", 60}));
    add_prop(OBJ_I_VALUE, 600);
}

int
wear()
{
    no_times++;
    if (no_times <= MAX_TIMES) {
        this_player()->set_stat_extra(SS_INT, MAX_TIMES + 1 - no_times);
        set_alarmv(2.0, -1.0, "wmsg", ({this_player(), "You feel more " +
	       "intelligent as you wear the " + short() + ".\n"}));
    }
    if (interactive(this_player())) set_likely_break(6);
    return 0;
}

int
remove()
{
    if (no_times <= MAX_TIMES) {
        this_player()->set_stat_extra(SS_INT, 0);
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
