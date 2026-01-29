/* /d/Shire/club/huntclub/obj/tallystick.c

 Tally Stick
 By Tomas,  November 2017
 
 Stolen for the Allies of Rohan
 /d/Gondor/clubs/ally_rohan/obj/signet.c
 Raymundo, Summer 2021
 

*/

#pragma save_binary;


inherit "/cmd/std/command_driver";
inherit "/std/object";

#include <adverbs.h>
#include <cmdparse.h>
#include <ss_types.h>
#include <filter_funs.h>
#include "../ally_rohan.h"
#include <macros.h>
#include <stdproperties.h>
#include <composite.h>
#include "/d/Gondor/defs.h"
#include <formulas.h>

void
create_object()
{
    set_name("signet");
    add_name("_rohan_signet_");
    add_adj(({"rohan"}));
    set_short("signet of Rohan");
    set_long("The signet bears the official seal of Rohan, marking its bearer as an ally of the kingdom.\n");
    add_item(("seal"), "The seal is of a Rohirrim horse.\n");
    add_prop(OBJ_I_WEIGHT, 1);
    add_prop(OBJ_I_VOLUME, 100);
    add_prop(OBJ_I_VALUE, 0);
    add_prop(OBJ_M_NO_DROP,"You can't just drop the signet. You need to relinquish it in front of the king!\n");
}
/*
string
query_auto_load() { return MASTER + ":"; }


public string
query_recover() { return 0; }
*/