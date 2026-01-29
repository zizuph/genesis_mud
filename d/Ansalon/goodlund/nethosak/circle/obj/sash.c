/*
 * File Name        : sash.c
 * By               : Elmore.
 * Inspiration from : Occ_fighter Guild by Unknow.
 * Date             : Nov. 2000.
 * Description      : This is the guild item for the pirates.
 *                    It is possible to wear and remove this
 *                    object.
 *
 */

#pragma strict_types

inherit "/std/object";

#include "../local.h"
#include <macros.h>
#include <stdproperties.h>
#include <composite.h>
#include <language.h>
#include <filter_funs.h>
#include <cmdparse.h>
#include "/d/Krynn/common/defs.h"

private int worn = 0;

void
init_arg(string arg)
{ 
}

void
create_object()
{
    set_name("sash");
    add_name(GUILD_EMBLEM_ID);
    set_adj("black");
    add_adj("silver-lined");
    set_short("black silver-lined sash");
    set_long("@@my_long");

    add_prop(OBJ_M_NO_DROP, "You cannot drop the sash.\n");
    add_prop(OBJ_M_NO_GET,  1);
    add_prop(OBJ_M_NO_SELL, 1);
    add_prop(OBJ_M_NO_BUY,  1);
    add_prop(OBJ_I_WEIGHT,  2000);
    add_prop(OBJ_I_VOLUME,  500);

    remove_prop(OBJ_I_VALUE);
}

string
my_long()
{
    return "This is a black sash, worn only by the feared pirates of "+
           "the Bloodsea. Thin silverthreads has been weaved into the "+
           "fabric, it shimmers slightly as you move the sash in the "+
           "sunlight. The words 'help sash' has been printed on it.\n";
}

int
query_worn()
{
    return worn;
}

int
wear(string str)
{
    int i;
    mixed oblist;

    if (query_worn() || !strlen(str))
    {
        notify_fail("Wear what?\n");
        return 0;
    }

    i = parse_command(str,TP,"[the] %i",oblist);
    if (i != 1 || !oblist || member_array(TO,oblist) < 0 || oblist[0] == 0)
      return 0;

    write("You tie your black silver-lined sash around your hip.\n");
    say(QCTNAME(TP) + " ties a black silver-lined sash around " +
	POSSESSIVE(TP) + " hip.\n");
    set_no_show_composite(1);
    worn = 1;

    if (sizeof(oblist) > 2)
      return 0;

    return 1;
}

varargs int
remove(string str,object who = TP)
{
    int i;
    mixed oblist;
    object obj;

    if (!query_worn())
      return 0;
    
    i = parse_command(str,who,"[the] %i",oblist);
    if (i != 1 || !oblist || member_array(TO,oblist) < 0 || oblist[0] == 0)
      return 0;
    
    who->catch_msg("You remove the black silver-lined sash from your hip.\n");
    tell_room(E(who),QCTNAME(who) + " removes a black silver-lined sash from " +
	      POSSESSIVE(who) + " hip.\n",who);
    set_no_show_composite(0);
    worn = 0;

    if (sizeof(oblist) > 2)
      return 0;

    return 1;
}

string
show_subloc(string subloc, object me, object for_obj)
{
    if (me->query_prop(TEMP_SUBLOC_SHOW_ONLY_THINGS))
      return "You are wearing a black silver-lined sash.\n";
}

void
init()
{
    if (!interactive(TP))
      return;
    ADA("remove");
    ADA("wear");
}

