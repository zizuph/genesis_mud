/*
 * Invisible Object controlling the NO ATTACK prop of a 
 * recently rescued enemy.
 */
inherit "/std/object";

#include <stdproperties.h>
#include "../guild.h"

mapping guards;

void
create_object()
{
    set_name(RESCUE_OBJECT);
    set_short("a rescue object");
    set_no_show();

    add_prop(OBJ_I_NO_DROP, 1);
    add_prop(OBJ_I_WEIGHT, 0);
    add_prop(OBJ_I_VOLUME, 0);                                                 
    add_prop(OBJ_I_VALUE, 0);

    guards = ([ ]);
}

string
no_attack()
{
    int k;
    object *g;

    if (!guards[this_player()])
	return 0;
    
    g = guards[this_player()];
    g = filter(g, &operator(==)(environment(environment())) @ 
	environment);
    
    if (!(k = sizeof(g)))
	return 0;
    
    return "You attempt to attack " + 
	environment()->query_the_name(this_player()) + 
	", but " + g[random(k)]->query_the_name(this_player()) + 
	" stands firmly in your way.\n";
}


void
remove_guard(object guardian, object foe)
{
    if (guards[foe])
	guards[foe] -= ({ guardian });
    
    if (!sizeof(filter(m_values(guards), sizeof)))
    {
	/* No guards left */
	remove_object();
    }
}

void
add_guard(object guardian, object foe)
{
    object who;

    who = environment();
    
    if (!guards[foe])
	guards[foe] = ({ });

    guards[foe] += ({ guardian });
    
    if (who->query_prop(OBJ_M_NO_ATTACK))
    {
	/* We might be the ones who added it */
	return;
    }
    
    who->add_prop(OBJ_M_NO_ATTACK, &no_attack());
    set_alarm(who->query_speed(RESCUE_PROTECT_TIME), 0.0, &remove_guard(guardian, foe));
}

void
enter_env(object ob, object from)
{
    ::enter_env(ob, from);

    if (!living(ob) || 
	ob->query_prop(OBJ_M_NO_ATTACK))
    {
	return;
    }
    ob->add_prop(OBJ_M_NO_ATTACK, no_attack);
}

void
leave_env(object ob, object to)
{
    ::leave_env(ob, to);
    
    if (!living(ob))
	return;

    if (functionp(ob->query_prop_setting(OBJ_M_NO_ATTACK)) &&
	function_name(ob->query_prop_setting(OBJ_M_NO_ATTACK)) == "no_attack");
    {
	ob->remove_prop(OBJ_M_NO_ATTACK);
    }
}
