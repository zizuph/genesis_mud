/*
  This is a testing spell object, used to test the
  Fire College spells as we code them.
  
  Bishop of Calia, July 2003.

*/

inherit "/std/object";
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

    set_name("rod");
    add_name("fire_college_test");
    set_short("red pulsating rod");
    
    set_long("This short rod is warm and light red in color," +
        " growing darker and hotter at regular intervals. This" +
        " object is used by wizards to test the Fire College spells"+
        " as they are being developed.\n");
        
    add_prop(OBJ_M_NO_INS, 1);
    add_prop(OBJ_I_NO_DROP, 1);
    add_prop(OBJ_M_NO_STEAL, 1);
    add_prop(OBJ_M_NO_SELL, 1);
    add_prop(OBJ_I_NO_STEAL,1);
    
    add_spell(FIRE_SPELLS + "blindness");
    add_spell(FIRE_SPELLS + "steadyflame");
    add_spell(FIRE_SPELLS + "efreetsumm");
    add_spell(FIRE_SPELLS + "firemites");
    add_spell(FIRE_SPELLS + "firebolt");
    add_spell(FIRE_SPELLS + "fireball");
    add_spell(FIRE_SPELLS + "bloodlust");
    add_spell(clone_object(FIRE_SPELLS + "firetell"));

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

