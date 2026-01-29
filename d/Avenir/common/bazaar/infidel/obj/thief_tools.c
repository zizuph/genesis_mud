// file name:    Thieves_tools
// creator(s):   Cirion, August 1996
// last update:  
// purpose:      Thieves tools that aid in the picking of
//               locks and such. They add 10 to the SS_OPEN_LOCK
//               of any player carrying them.
// note:         
// bug(s):       
// to-do:        
#pragma strict_types

inherit "/std/object";
inherit "/lib/keep";

#include "/d/Avenir/common/common.h"
#include <cmdparse.h>

#define MY_ID  "_Avenir_thief_tools"

void create_object()
{
    set_name("tools");
    set_short("set of tiny tools");
    set_pshort("sets of tiny tools");
    add_name(({"set", "tool", MY_ID}));
    set_long("It is a bunch of tiny lock picks, all hanging "
     + "together on a long wire. They would probably aid "
     + "in the picking of locks.\n");

    add_item("wire","It is a thin steel wire on which "
     + "the tools are all attached to.\n");
    add_item(({"pick","picks"}),"They are tiny lock picks, "
     + "all of varying shapes and sizes.\n"); 

    set_keep(1);
  
    add_prop(OBJ_I_WEIGHT, 100);
    add_prop(OBJ_I_VOLUME, 200);
    add_prop(OBJ_I_VALUE, 670);
    add_prop(OBJ_S_WIZINFO, "These tools add 10 to the "
     + "SS_OPEN_LOCK of any player carrying them, to aid "
     + "in picking locks on doors and chests. Only one set "
     + "of tools will add the extra stats (ie, player's can't "
     + "carry around 10 of them and have a skill of 100).\n"
     + "Coded by Cirion, Aug 1996.\n");
}

int query_is_thieves_tools()
{
    return 1;
}

int has_tools(object who)
{
    object *stuff = all_inventory(who) - ({ TO });

    if(member_array(1, stuff->query_is_thieves_tools()) != -1)
      return 1;
    else
      return 0;
}    

/* Add 10 to the SS_OPEN_LOCK of any player holding the tools,
 * unless we already have these tools. */
void enter_env(object to, object from)
{
    ::enter_env(to, from);

    if(!interactive(to) || has_tools(to))
      return;

    to->set_skill_extra(SS_OPEN_LOCK, 
      to->query_skill_extra(SS_OPEN_LOCK) + 10);
}

/* Remove the added skills when the player drops the tools */
void leave_env(object inv, object to)
{
    ::leave_env(inv, to);
    if(!interactive(inv) || has_tools(inv))
      return;

    inv->set_skill_extra(SS_OPEN_LOCK, 
       inv->query_skill_extra(SS_OPEN_LOCK) - 10);
}
