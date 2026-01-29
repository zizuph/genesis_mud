/*
 * Standard Spell Object
 *
 * This spell object base uses the spell_obj_lib.c file. Please see that
 * file for more details on available hooks. The purpose of this file
 * is to add standard properties onto an object. Each spell effect object
 * when removed will automatically call dispel by including auto_remove.h
 *
 * Created by Petros, September 2009
 */
 
#include <stdproperties.h>
#include <macros.h>
#include "defs.h"

inherit "/std/object";
inherit SPELL_OBJ_DIR + "spell_obj_lib";

#include "auto_remove.h"

/* 
 * Function:    create_object
 * Description: Standard object creation function. Set to nomask, but
 *              can override defaults using create_spell_object
 */
public nomask void
create_object()
{
    set_name("_base_spell_obj");
    add_name( ({"base_spell_obj" }) );
    set_short("hidden base spell object");    
    set_long("A basic spell object. One should not be able to see it "
           + "in their inventory.\n");
    // Don't allow this to be sold.
    add_prop(OBJ_M_NO_DROP, 1);
    add_prop(OBJ_M_NO_STEAL, 1);                          
    add_prop(OBJ_M_NO_SELL, 1); 
    remove_prop(OBJ_I_VALUE);
    remove_prop(OBJ_I_VOLUME);
    remove_prop(OBJ_I_WEIGHT);
    
    // By setting this, players should not know that this is in their
    // inventory.
    set_no_show();
    
    setuid();
    seteuid(getuid());
    
    create_spell_object();
}

public int
setup_spell_effect()
{
    int result = ::setup_spell_effect();
    if (!result)
        return result;
    if (query_spell_effect_name())
    {
        set_short(query_spell_effect_name() + " spell effect");
    }
    if (query_spell_effect_desc())
    {
        set_long(query_spell_effect_desc());
    }
    return result;
}

