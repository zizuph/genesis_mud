/*
    This is a test spell object. Used to test SCoP spells as they
    are recoded, before adding them to the guild.

    Bishop of Calia, April 2004.
 
*/


inherit "/std/object";
inherit "/d/Genesis/newmagic/spellcasting.c";

#include <stdproperties.h>
#include <macros.h>

#include "defs.h"
#include SPIRIT_HEADER


void
create_object()
{
    if (!IS_CLONE)
    {
        return;
    }

    set_name("sphere");
    add_name("scop_college_test");
    set_short("shimmering sphere");
    
    set_long("This sphere brims with energy. It is a spell object, "+
        " used to test spirit circle spells as they are coded.\n");
        
    add_prop(OBJ_M_NO_INS, 1);
    add_prop(OBJ_I_NO_DROP, 1);
    add_prop(OBJ_M_NO_STEAL, 1);
    add_prop(OBJ_M_NO_SELL, 1);
    add_prop(OBJ_I_NO_STEAL,1);
    
    add_spell(SPIRIT_SPELLS + "anakalo");    
}


public void
remove_object()
{
    /* Remove any cloned instances of spells that are registered with this
     * spellcasting object so that they aren't sitting around just taking up
     * memory.  You can either call remove_object() in the spells yourself,
     * or use the utility function cleanup_spells() to do it.
     */
    cleanup_spells();
    ::remove_object();
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