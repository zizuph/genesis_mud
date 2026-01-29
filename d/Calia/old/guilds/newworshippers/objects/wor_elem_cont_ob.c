/*
    Control object cloned in a player, to enable them to issue commands
    to their summoned elemental.

    Coded by Bishop of Calia, 02/07/03.

*/

#pragma strict_types

inherit "/std/object";

#include <defs.h>
#include <macros.h>
#include <stdproperties.h>

void set_caster(object ob);

object elemental, caster;

void
create_object()
{
    set_name("wor_elem_cont_ob");
        
    add_prop(OBJ_I_VALUE,0);
    add_prop(OBJ_I_WEIGHT,0);
    add_prop(OBJ_I_VOLUME,0);
    set_no_show();
    add_prop(OBJ_M_NO_STEAL,1);
    add_prop(OBJ_M_NO_DROP,1);
    add_prop(OBJ_S_WIZINFO, "This is an object cloned in an Elemental" +
        " Worshipper of Calia, to give them commands and facilitate their" +
        " control over summoned elementals.\n");
}

void
set_caster(object ob)
{
    caster = ob;
}

int
warmor(string str)
{
    if (!present(elemental, environment(caster)))
    {
        notify_fail("Your elemental must be present in order" +
            " to become an armor!\n");
        return 0;
    }
        
    if (present("wor_elem_arm", caster))
    {
        notify_fail("You're already wearing elemental armor!\n");
        return 0;
    }

    elemental->become_armor();
    return 1;
}    

int
wdispel(string str)
{
    write("You wave your arms and the creature is dispelled.\n");
    say(QCTNAME(caster) + " waves " + 
        caster->query_possessive() + " arms momentarily.\n", caster);
    elemental->dispel_spell_effect(caster);
    return 1;
}

int
wcs(string str)
{
    write("You send your message silently to your creature.\n");
    elemental->catch_question(str);
    return 1;
}

int 
wrecall(string str)
{
    if (present(elemental, environment(caster)))
    {
        notify_fail("The elemental is already here!\n");
        return 0;
    }
    else if (environment(elemental)->query_prop(ROOM_M_NO_TELEPORT) ||
        environment(elemental)->query_prop(ROOM_M_NO_TELEPORT_FROM) ||
        environment(caster)->query_prop(ROOM_M_NO_TELEPORT) ||
        environment(caster)->query_prop(ROOM_M_NO_TELEPORT_TO))
    {
        notify_fail("Some force prevents the elemental from returning!\n");
        return 0;
    }
    
    elemental->move_living("X", environment(caster));
    
    if (!present(elemental, environment(caster)))
    {
        write("The creature is prevented from coming here by some force.\n");
    }
    
    return 1;

}

int
ehelp(string str)
{
    write("You can issue the following commands for your elemental:\n" +
        "eldispel - returns your elemental to where it came from\n" +
        "elcs <message> - silently speak a message to your elemental\n" +
        "elrecall - return your elemental to you, if you become separated\n" +
        "elarmor - your elemental engulfs you and becomes an armor\n");
    return 1;
}

void
enter_env(object env, object from)
{
    ::enter_env(env, from);

    elemental = caster->query_prop(WOR_CREATURE_SUMMONED);
}

void
init()
{
    ::init();
    
    add_action(wdispel, "eldispel");
    add_action(wcs, "elcs");
    add_action(wrecall, "elrecall");
    add_action(ehelp, "ehelp");
    add_action(warmor, "elarmor");
}