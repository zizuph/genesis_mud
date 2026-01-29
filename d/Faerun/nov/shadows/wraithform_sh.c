#pragma save_binary
#pragma strict_types

#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>
#include "../nov.h";

inherit "/std/shadow";

#ifndef OBJ_ADJS
#define OBJ_ADJS ({"black", "wraithlike"})
#endif

private mixed
query_list(mixed list, int arg)
{
    if (!pointerp(list))
        return 0;

    if (!arg && sizeof(list))
        return list[0];
    else
        return list + ({});
}

varargs public mixed
query_adj(int arg) 
{
    return query_list(OBJ_ADJS, arg);
}

public string *
query_adjs() 
{ 
    return query_list(OBJ_ADJS, 1);
}

public int
adjectiv_id(string str)
{
    return (member_array(str, OBJ_ADJS) >= 0);
}

public string *
parse_command_adjectiv_id_list()
{
    return OBJ_ADJS + ({ query_shadow_who()->query_gender_string() });
}




string
query_race_name()
{
    return "shadow";
}

string
query_gender_string()
{
    return "misty";
}


void
remove_wraithform_shadow()
{
    shadow_who->tell_watcher(QCTNAME(shadow_who)+" returns to normal from the wraithform.\n");
    shadow_who->remove_prop(IAMINWRAITHFORM);
    tell_object(shadow_who, "Your body returns to normal from the wraithform!\n");
    
    remove_shadow();
}


varargs public mixed
hit_me(int wcpen, int dt, object attacker, int attack_id, int hitloc)
{
    //if(wcpen > 0 && random(100) > 50)
    if(random(100) < 25)
    {
        tell_object(shadow_who,"You harmlessly pass through an incoming blow.\n");
        tell_room(environment(shadow_who),QTNAME(shadow_who)+" passes harmlessly through " +
        "a blow.\n",shadow_who);
        return;
    }
    return shadow_who->hit_me(wcpen,dt,attacker,attack_id,hitloc);
}

int
query_wraithform_shadow()
{
    return 1;
}


void
init_wraithform_shadow(int i)
{
      tell_object(shadow_who,"Your body becomes black and misty!\n");
      shadow_who->tell_watcher(QCTNAME(shadow_who)+"'s body transforms into a black wraithlike " +
      "misty shadow.\n");
      shadow_who->add_prop(IAMINWRAITHFORM, 1);
    
      set_alarm(itof(i),0.0,&remove_wraithform_shadow());
}