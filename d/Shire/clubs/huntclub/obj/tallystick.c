/* /d/Shire/club/huntclub/obj/tallystick.c

 Tally Stick
 By Tomas,  November 2017
 

*/

#pragma save_binary;


inherit "/cmd/std/command_driver";
inherit "/std/object";

#include <adverbs.h>
#include <cmdparse.h>
#include <ss_types.h>
#include <filter_funs.h>
#include "../huntclub.h"
#include <macros.h>
#include <stdproperties.h>
#include <composite.h>
#include "/d/Shire/common/defs.h"
#include <formulas.h>

void
create_object()
{
    set_name("tally stick");
    add_name("_huntclub_tallystick_");
    add_adj(({"white","bone"}));
    set_short("tallystick");
    set_long("The tallystick is a piece of elongated white bone. The word, "+
      "'hchelp' etched into the side.\n");
    add_item(("tally","tallystick"), "The tally stick is an elongated piece of bone, " +
       "that can be marked with a system of notches for recording your kills. The word " +
       "'hchelp' has been etched into the side.\n");
    add_prop(OBJ_I_WEIGHT, 1);
    add_prop(OBJ_I_VOLUME, 100);
    add_prop(OBJ_I_VALUE, 0);
    add_prop(OBJ_M_NO_DROP,"The tallystick refuses to leave your side, and won't drop.\n");
}
/*
string
query_auto_load() { return MASTER + ":"; }


public string
query_recover() { return 0; }
*/