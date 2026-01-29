#pragma save_binary
#pragma strict_types

#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>
#include "../nov.h";

inherit "/std/shadow";

void
remove_deathshield_shadow()
{
    shadow_who->tell_watcher("The black aura of negative energy " +
    "around "+QCTNAME(shadow_who)+" fades away.\n");
    shadow_who->remove_prop(IHAVEDEATHSHIELD);
    tell_object(shadow_who, "Your deathshield wears off!\n");
    
    remove_shadow();
}


varargs public mixed
hit_me(int wcpen, int dt, object attacker, int attack_id, int hitloc)
{
    //if(wcpen > 0 && random(100) > 50)
    if(random(100) > 25)
    {
        tell_object(shadow_who,"The black aura of negative energy absorbs a blow " +
        "against you!\n");
        tell_room(environment(shadow_who),"The black aura of negative energy around "+QTNAME(shadow_who)+
        " absorbs the blow!\n",shadow_who);
        return;
    }
    return shadow_who->hit_me(wcpen,dt,attacker,attack_id,hitloc);
}

int
query_deathshield_shadow()
{
    return 1;
}


void
init_deathshield_shadow(int i)
{
      tell_object(shadow_who,"An aura of black negative energy envelops you!\n");
      shadow_who->tell_watcher(QCTNAME(shadow_who)+"'s body is engulfed by an aura of black negative energy.\n");
      shadow_who->add_prop(IHAVEDEATHSHIELD, 1);
    
      set_alarm(itof(i),0.0,&remove_deathshield_shadow());
}