/*

  This ring is a guild item for the College of Fire Magic. It acts as
  their spell object.
  
  Bishop of Calia, July 2003.

*/

inherit "/std/object";
inherit "/lib/wearable_item";
inherit "/d/Genesis/newmagic/spellcasting.c";

#include <stdproperties.h>
#include <macros.h>
#include "defs.h"

void
create_object()
{
    if (!IS_CLONE)
    {
        return;
    }

    set_name("ring");
    add_name("college_ring");
    add_adj("plain");
    add_adj("onyx");
    set_short("plain onyx ring");
    
    set_long("This unadorned onyx ring feels slightly warm. There is an" +
        " engraving on the inside. In flowing letters, it reads: 'Fire will" +
        " be your guide'.\n");
        
    add_prop(OBJ_M_NO_INS, 1);
    add_prop(OBJ_I_NO_DROP, 1);
    add_prop(OBJ_M_NO_STEAL, 1);
    add_prop(OBJ_M_NO_SELL, 1);
    add_prop(OBJ_I_NO_STEAL,1);
 
}


string
query_auto_load()
{
    return MASTER; 
}

string
query_recover()
{
    return 0;
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

void
init()
{
    ::init();
}