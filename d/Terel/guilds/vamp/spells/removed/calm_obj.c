
#include "../../guild.h"

inherit SPELLOBJ_DIR+"spell_obj";
inherit "/std/object";

#include <stdproperties.h>
#include <macros.h>

public void create_object()
{
    set_name("_calm_obj");
    
    add_prop(OBJ_I_NO_DROP, 1);
    add_prop(OBJ_S_WIZINFO, "Spell object for the calm spell\n");

    set_spell_effect_desc("control your fears");
    set_no_show();

}

varargs public int
dispel_spell_effect(object dispeller)
{
	
	query_effect_target()->set_calm(0);
	
    query_effect_target()->catch_tell("Your body's natural state presses "+
    "hard against your psyche, forcing an inner conflict between man and "+ 
    "beast.  The beast wins, for now, and your inner calm is broken.\n");

    remove_spell_effect_object();
    return 1;
}

public void warn_fading()
{
    query_effect_caster()->catch_tell("Your inner instincts press "+
    "against your mask of calm, pushing your feral self to the "+
    "forefront.\n");
}


public int
start()
{

    if (!::start())
    {
        remove_spell_effect_object();
        return 0;
    }
    

    query_effect_target()->catch_tell("You focus deeply on controlling "+
    "the natural tendencies of your undead body.  The choice of fight "+
    "or flight lives deep within the your being, but another of your "+
    "preternatural gifts is the inner control of this instinct. "+
    "You find a place of calm, so that your dominant mind may control "+
    "when you flee.\n");

    move(query_effect_target(),1);
    
    query_effect_target()->set_calm(1);

    int delay=max(300,query_effect_target()->query_vamp_stat()*15);
    
    //Lasts 5-45 minutes
    delay=min(delay,60*45);
    
    set_dispel_time(delay);

    query_effect_target()->add_panic(
        -query_effect_target()->query_panic()/2);

    return 1;
}

public void init()
{
    ::init();
    add_action(stop,"stop");
}
