/*
 *      /w/vencar/caravan/obj/fire_wand.c
 *
 *      A wand that fire with fireballs.
 *      Created by Vencar 09/09/2003
 *
 *      Copyright by Peter Bech Lund (Vencar)
 *      09/2003
 *
 * Based on Ansalon fermammon wand.
 */

inherit "/std/object";
inherit "/lib/holdable_item";

#include <macros.h>
#include <wa_types.h>
#include <ss_types.h>
#include <stdproperties.h>
#include "/d/Krynn/common/defs.h"

#define DEBUG_WIZ       "vencar"
#define DEBUG_MSG(x)   find_player(DEBUG_WIZ)->catch_msg("Debug msg: " + x + ".\n");

string
short_descr()
{
    return "red steel-tipped wand";
}


int
point_wand(string str)
{
    object sh;
    object who;
    who = find_living(str);

    DEBUG_MSG(who->short());

//    sh = clone_object("/d/Ansalon/guild/pot/shadow/occ_shadow.c");


}


void
leave_env(object env, object to)
{
    ::leave_env(env, to);
    holdable_item_leave_env(env, to);
}

void
create_object()
{
    set_name("wand");
    set_short("@@short_descr");
    add_name("@@short_descr");
    set_long("This " + "@@short_descr@@" + " is made of " +
      "some rare sort of red wood. the steely tip is covered " +
      "slightly with soot.\n");

    add_prop(OBJ_I_WEIGHT,30);
    add_prop(OBJ_I_VOLUME,30);
    add_prop(OBJ_I_VALUE, 7500);
    add_prop(MAGIC_AM_MAGIC,({25,"enchantment"}));
    add_prop(OBJ_I_IS_MAGIC_WEAPON, 1);
    add_prop(MAGIC_AM_ID_INFO,
      ({"This is a wand of firebals. Its  " +
    "type generally has a few charges, and can be hard to " +
    "use correctly if one is not skilled in magic. " +
    "It may be recharged, but recharging of such powerful magic " +
    "may be hazardeous for the unskilled.\n",10}));

    set_slots(W_ANYH);

}


public void
init()
{
    ::init();

    add_action (point_wand, "fnuggle");


}