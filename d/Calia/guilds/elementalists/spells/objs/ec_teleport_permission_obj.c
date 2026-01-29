
/*
 * ec_teleport_permission_obj.c
 *
 * An object for the Elemental Clerics teleport spells
 *
 * This object requests permission from the player to allow EC
 * members to teleport to them.
 *
 * Copyright (C): Jaacar, December 1st, 2017
 *
 */


#pragma save_binary
#pragma strict_types

inherit "/std/object";

#include <stdproperties.h>
#include <macros.h>
#include <tasks.h>
#include <ss_types.h>
#include "defs.h"

public string caster_name;
public mixed caster;

void
set_caster_name(mixed name)
{
    caster = name;
    caster_name = capitalize(caster->query_real_name());
}

string
describe_long()
{
    return "It is a small glowing sphere that has to come you from "+
        caster_name + ". As you roll it around in your fingers, two "+
        "visions enter your mind.\nThe first is you crushing the sphere, "+
        "not allowing " + caster_name + " permission to teleport to you.\n"+
        "The second is you swallowing the sphere, allowing " + caster_name +
        " permission to teleport you.\n";
}

void
create_object()
{
    set_name("small glowing sphere");
    add_name("sphere");
    add_adj(({"small","glowing"}));
    add_name("_ec_teleport_permission_");
    set_short("small glowing sphere");
    set_long("@@describe_long@@");

    add_prop(OBJ_I_VOLUME,0);
    add_prop(OBJ_I_WEIGHT,0);
    add_prop(OBJ_I_VALUE,0);
    add_prop(OBJ_M_NO_SELL,1);
    add_prop(OBJ_M_NO_DROP,1);
    add_prop(OBJ_M_NO_GIVE,1);
    add_prop(OBJ_M_NO_STEAL,1);  
}

public void
remove_ec_teleport_denial(string prop)
{
	TP->remove_prop(prop);
	TO->remove_object();
}

public int
do_crush(string str)
{
    if (!str)
    {
        notify_fail("Crush what?\n");
        return 0;
    }
    
    if (!parse_command(str, TP, " [the] [small] [glowing] 'sphere'"))
    {
        notify_fail("Crush what?\n");
        return 0;
    }
    
    write("You crush the small glowing sphere between your fingers and it "+
        "disappears into thin air.\n");
    string TELEPORT_PROP = "_live_i_allow_ec_teleport_"+
        lower_case(caster_name);
    TP->add_prop(TELEPORT_PROP,"no");
    caster->catch_msg(QCTNAME(TP)+" has NOT permitted you to teleport "+
        "to them.\n");
    TO->set_no_show();
    set_alarm(1800.0,0.0,&remove_ec_teleport_denial(TELEPORT_PROP));
    return 1;
}

public int
do_swallow(string str)
{
    if (!str)
    {
        notify_fail("Swallow what?\n");
        return 0;
    }
    
    if (!parse_command(str, TP, " [the] [small] [glowing] 'sphere'"))
    {
        notify_fail("Swallow what?\n");
        return 0;
    }
    
    write("You swallow the small glowing sphere.\n");
    string TELEPORT_PROP = "_live_i_allow_ec_teleport_"+
        lower_case(caster_name);
    TP->add_prop(TELEPORT_PROP,"yes");
    caster->catch_msg(QCTNAME(TP)+" has permitted you to teleport "+
        "to them.\n");
    TO->remove_object();
    return 1;
}

void
init()
{
    ::init();
    add_action(do_crush, "crush");
    add_action(do_swallow, "swallow");
}


