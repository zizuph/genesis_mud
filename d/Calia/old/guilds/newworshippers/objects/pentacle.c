
/* 
   This is the object for earth spells in the Elemental Worshippers
   guild.

   Coded by Jaacar

   Modifications by Maniac 27/9/96.

   Revised by Bishop, June 2000.
*/
 

#pragma save_binary

#include "defs.h"

inherit "/std/object";
inherit "/d/Genesis/newmagic/spellcasting.c";

#include <stdproperties.h>
#include <macros.h>
#include <tasks.h>
#include <ss_types.h>
#include <wa_types.h>
#include "defs.h"

int count = 0;

int dest_tool();


string
query_auto_load()
{
    return MASTER + ":" + count;
}


int
dest_tool()
{
    object e;

    e = environment(this_object());

    if (interactive(e))
        e->catch_msg("The Earth Pentacle shatters into thousands of " +
                     "tiny pieces.\n");
    else
        tell_room(e, "The Earth Pentacle shatters into thousands of " +
                     "tiny pieces.\n");

    remove_object();
    return 1;
}


void
init_arg(string arg)
{
    if (!(this_player()->is_worship()))
    {
        count = atoi(arg) + 1;
        if (count >= 50)
            set_alarm(5.0, 0.0, dest_tool);
    }
}



void
create_object()
{
    set_name("pentacle");
    add_name("worshipper_pentacle");
    set_short("platinum earth pentacle");
    set_long("This is an Earth Pentacle, roughly shaped like "+
        "a shallow bowl, sheathed in platinum. A pentagram "+
        "has been engraved upon the inner surface, and the inner "+
        "rim bears strange runes.\n");

    add_prop(OBJ_M_NO_INS, 1);
    add_prop(OBJ_I_NO_DROP, 1);
    add_prop(OBJ_M_NO_STEAL, 1);
    add_prop(OBJ_M_NO_SELL, 1);
    add_prop(OBJ_I_NO_GIVE, 1);
    add_prop(OBJ_I_NO_STEAL,1);

}


void
enter_env(object env, object from)
{ 
   ::enter_env(env, from);
    add_spell_object(env);
}


void
leave_env(object env, object to)
{
    ::leave_env(env, to);
    remove_spell_object(env);
}