/*
* Modified from /d/Krynn/common/potions/quenta_object.c
* By Arman 16/10/97
 *
 * Teth, Feb 1997, modified from Olorin's old invis_object.
 *
 * Navarre July 1st 2006: Lowered the resistance
 *
 * Arman August 25 2016: Changed from add_prop to add_magic_effect
 */
#pragma strict_types

inherit "/std/object";

#include <macros.h>
#include <poison_types.h>
#include <ss_types.h>

#include "/d/Ansalon/common/defs.h"

static int     time = 1;

void
create_object()
{
    set_name("Ansalon_Resistance_Object");

    add_prop(OBJ_I_VOLUME, 0);
    add_prop(OBJ_I_WEIGHT, 0);
    add_prop(OBJ_I_NO_DROP, 1);
    add_prop(OBJ_I_NO_GIVE, 1);

    set_no_show();
}

varargs mixed
query_magic_protection(string prop, object protectee = previous_object())
{
    object  ob = E(TO);
    int res_lvl;

    if(ob->query_race_name() == "dwarf")
    {
	res_lvl = 20;
    }
    else
	res_lvl = 18;
    
    if (protectee == ob)
      {
	  if (prop == MAGIC_I_RES_POISON)
	    return ({ res_lvl, 1}); /* additive */
      } 
    else 
      return ::query_magic_protection(prop, protectee);
}

void
set_duration(int i)
{
    time = i;
}

void
end_effect()
{
    object  ob = E(TO);

    ob->remove_magic_effect(TO);
    ob->catch_msg("You feel the effects of the dwarven brew " +
      "wearing off.\n");
    set_alarm(0.0, 0.0, remove_object);

}

void
enter_env(object to, object from)
{
    ::enter_env(to, from);

    if (!objectp(to) || !living(to))
    {
	set_alarm(0.0, 0.0, remove_object);
	return;
    }

    to->add_magic_effect(TO);
    to->catch_msg("Aaaerg! This brew is strong! For a moment you see double " +
      "of everything...\n");
    set_alarm(itof(time), 0.0, end_effect);
}

void
leave_env(object old, object dest)
{
    ::leave_env(old, dest);
}

