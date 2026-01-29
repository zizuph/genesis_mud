/* chapel/obj/ring.c is cloned by chapel/jewelers.c 
 * Modified a lot by Rohim. A sunny day this will work
 * emotes will lie in the soul. Hopefully that is.
 */

#pragma strict_types
#pragma save_binary

inherit "/std/armour";
#include <stdproperties.h>
#include <wa_types.h>
#include <macros.h>
#include <std.h>
#include "chapel.h"

string material, person;
 
void
create_armour()
{
    set_name("ring");
    set_pname("rings");
    add_name(RING_ID);
    add_adj( ({ "marriage", "wedding" }) );
    set_long("@@long_desc@@");
 
    set_ac(0);
 
    set_at(A_L_FINGER);
    
    set_likely_break(0);

    add_prop(OBJ_I_WEIGHT, 15);
    add_prop(OBJ_I_VOLUME, 3);
    seteuid(getuid());
}
 
string
long_desc()
{
    if (!material || !person)
       return "This is a beautifully engraved marriage ring.\n";
    return "It is a uniquely crafted marriage ring. "+
     "It is made of " + material + ", and is inscribed on the band. "+
     "The inscription reads:  'With all my love, "+
     capitalize(person) + "'.\n";
}

string
material_desc()
{
    return material;
}

int
query_value()
{
    return (member_array(material, MATERIALS) + 1) * 86400;
}

string
query_auto_load()
{
    if (material && person)
         return MASTER + ":" + material + "!" + person;
    return 0;
}

string
query_material()
{
    return material;
}

void
set_material(string m)
{
    material = m; /* Used when you choose type of ring. */

    set_adj(material);
    set_short(material + " marriage ring");
    set_pshort(material + " marriage rings");
}
 
void
set_person(string p)
{
    person = p;  /* Used to set the spouse. */
}
 
string
query_person()
{
    return person;
}

void
init_arg(string arg)
{
    sscanf(arg, "%s!%s", material, person);

    set_adj(material);
    set_short(material + " marriage ring");
    set_pshort(material + " marriage rings");
}

void
add_soul(object env)
{
    if(env->add_cmdsoul(SOUL_PATH))
    {
        env->update_hooks();
    }
}

void
enter_env(object env, object from)
{
    ::enter_env(env, from);
    if (env && living(env))
    {
        if (M_MANAGER->query_married(env->query_real_name()) == 0)
        {
        set_alarm(0.0, 0.0, remove_object);
        return ;
        }
        env->add_prop(PLAYER_S_SPOUSE, person);
        add_prop(OBJ_M_NO_DROP, 1);
        set_alarm(2.0, 0.0, &add_soul(env));
        return;
    }   
}

void
leave_env(object from, object to)
{
    ::leave_env(from, to);
    if (from && living(from))
        from->remove_prop(PLAYER_S_SPOUSE);
}

string
stat_object()
{
    string str;
 
    str = ::stat_object();
 
    if (person)
      str += "Spouse: " + person + "\n";
    if (material)
      str += "Material: " + material + "\n";
    return str;
}

int query_recover()
{
  return 0;
}

/* Too many armour breaking routines fail to check for likely_break == 0 */
varargs void
remove_broken(int silent)
{
}
