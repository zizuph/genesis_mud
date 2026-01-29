/* chapel/obj/ring.c is cloned by chapel/jewelers.c 
 * Modified a lot by Rohim. A sunny day this will work
 * emotes will lie in the soul. Hopefully that is.
 */

inherit "/std/armour";

#include <stdproperties.h>
#include <wa_types.h>
#include <macros.h>
#include <std.h>
#include "/d/Emerald/leah/chapel/chapel.h"

void add_soul();

string material, person;
 
void
create_armour()
{
    set_name("ring");
    add_name(RING_ID);
    add_adj("@@material_desc@@");
    add_adj("marriage");
    set_long("@@long_desc@@");
 
    set_ac(0);
 
    set_at(A_L_FINGER);
    
    add_prop(OBJ_I_WEIGHT, 15);
    add_prop(OBJ_I_VOLUME, 3);
    seteuid(getuid());
}
 
string
long_desc()
{
    if (!material || !person)
       return "This is a beautiful marriage ring.\n";
    return "It is a beautifully made marriage ring. "+
     "It is made of " + material + ", and on the inside "+
     "it is engraved:  'With all my love, "+
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
    int v, i;
 
    v = 1744;
    for (i=0 ; i<member_array(material, MATERIALS) ; i++)
              v *= 2;
    return v;
}
 
string
query_auto_load()
{
    if (material && person)
         return "/d/Emerald/common/marriage/ring" + ":" + material + "!" + person;
    return 0;
}

void
set_material(string m)
{
         material = m; /* Used when you choose type of ring. */
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
}

void
enter_env(object env, object from)
{
    ::enter_env(env, from);
    if (env && living(env))
    {
        env->add_subloc(RING_SUBLOC, TO);
        env->add_prop(PLAYER_S_SPOUSE, person);
        add_prop(OBJ_M_NO_DROP, 1);
        set_alarm(2.0, 0.0, add_soul);
    }   
}

void
leave_env(object from, object to)
{
    ::leave_env(from, to);
    if (from && living(from))
    {
        from->remove_subloc(RING_SUBLOC);
        from->remove_prop(PLAYER_S_SPOUSE);   
    }
}

void
add_soul()
{
    if(TP->add_cmdsoul(SOUL_PATH))
    {
        TP->update_hooks();
    }
    return;
}

string
show_subloc(string subloc, object carrier, object for_obj)
{
    object ob;
    string str;
 
    if (subloc != RING_SUBLOC)
      return "";
    if (carrier->query_prop(TEMP_SUBLOC_SHOW_ONLY_THINGS) || !person)
      return "";
    setuid();
    seteuid(getuid());
    if (ob = find_player(person))
       str = ob->query_the_name(for_obj);
    else if (ob = SECURITY->finger_player(person))
    {
        str = ob->query_the_name(for_obj);
        ob->remove_object();
    }
    else
      return "";
    if (for_obj == carrier)
      return "You are married to " + str + ".\n";
    return capitalize(carrier->query_pronoun()) + " is married " +
	   "to " + str + ".\n";
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
