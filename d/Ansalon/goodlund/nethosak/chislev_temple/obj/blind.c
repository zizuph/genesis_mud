/*
 *  blind.c
 *
 *  This is the object which is moved to cause
 *  the target to become stunned when using the
 *  'chislev_staff.c'
 * 
 *  Created by Carnak, January 2016
 */
#pragma save_binary

#include "/d/Ansalon/common/defs.h"
#include <stdproperties.h>
#include <macros.h>
#include <filter_funs.h>
#include <formulas.h>

inherit "/std/object";

#define BLIND_SUBLOC "firefly_blind_subloc"

int alarm;
object enemy;

void
create_object()
{
    add_name("_firefly_blindness");
    add_prop(OBJ_I_NO_DROP, 1);
    add_prop(OBJ_S_WIZINFO, "Chislev Firefly blind effect.\n");
    set_no_show();
}

public int
dispel_blind_effect()
{
    enemy->catch_tell("You recover from the eerie green light, "+
    "regaining your sight.\n");
    
    object *obs;
    obs = all_inventory(environment(enemy));
    obs -= FILTER_IS_SEEN(enemy, obs);
    obs += ({ enemy });
    tell_room(environment(enemy), QCTNAME(enemy)+ " "+
    "appears to have recovered from the eerie green light, recovering "+
    HIS(enemy)+" eyesight.\n", obs, enemy);

    enemy->add_prop(LIVE_I_BLIND, enemy->query_prop(LIVE_I_BLIND) + 1);
    enemy->remove_subloc(BLIND_SUBLOC);

    this_object()->remove_object();
    return 1;
}

public void
set_blind_time(int t)
{
    remove_alarm(alarm);
    alarm = set_alarm(itof(t), 0.0, dispel_blind_effect);
}

public int
do_start()
{
    enemy = environment(this_object());
    enemy->catch_msg("The eerie light irritates your sensitive eyes, "+
    "blinding you.\n");
    
    object *obs;
    obs = all_inventory(environment(enemy));
    obs -= FILTER_IS_SEEN(enemy, obs);
    obs += ({ enemy });
    tell_room(environment(enemy), QCTNAME(enemy)+ " "+
    "appears affected by the eerie green light, loosing "+
    HIS(enemy)+" eyesight.\n", obs, enemy);
    
    enemy->add_prop(LIVE_I_BLIND, enemy->query_prop(LIVE_I_BLIND) - 1);
    enemy->add_subloc(BLIND_SUBLOC, TO);
    
    return 1;
}

public string
show_subloc(string subloc, object me, object for_obj)
{
    if (me->query_prop(TEMP_SUBLOC_SHOW_ONLY_THINGS))
        return "";

    if (for_obj == me)
        return "You squint your eyes, blinded by the eerie green light.\n";

    return capitalize(HIS(me)) + " eyes are squinting, blinded by the "+
    "eerie green light.\n";
}