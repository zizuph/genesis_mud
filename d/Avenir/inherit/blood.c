/* Some blood ... just for effect */
#pragma strict_types
#pragma no_inherit

inherit "/std/object";
#include <stdproperties.h>
#include <composite.h>
#include <macros.h>

#define BLOOD   "avenir_blood"

string *hits = ({ });
int     heal_alarm;

void create_object()
{
    set_name("wounds");
    add_name(({ BLOOD, "wound" }));

    remove_prop(OBJ_I_WEIGHT);
    remove_prop(OBJ_I_VOLUME);
    add_prop(OBJ_M_NO_DROP, "Drop what?\n");
    
    set_no_show_composite(1);

    set_long("It is a gash on your "
     + VBFC_ME("query_hits") + ", caused by being struck with a "
     + "bladed weapon.\n");
}

void avenir_weapon_damage() { /* Empty function. Do not remove. */ }

string query_hits()
{
  if(sizeof(hits) > 7)
   return COMPOSITE_WORDS(hits[0..6]);
  else
   return COMPOSITE_WORDS(hits);
}

void enter_env(object to, object from)
{
   ::enter_env(to, from);

   if(!living(to))
   {
     set_alarm(0.0, 0.0, remove_object);
     return;
   }

   to->add_subloc(BLOOD, this_object());
}

void leave_env(object to, object from)
{
   ::leave_env(to, from);

   from->remove_subloc(BLOOD);
}

public string
show_subloc(mixed subloc, object on, object for_obj)
{
  string str;

  if(!objectp(environment(this_object())) || !living(environment(this_object())))
  {
    set_alarm(0.0, 0.0, remove_object);
    return "";
  }

  if(for_obj->query_prop(TEMP_SUBLOC_SHOW_ONLY_THINGS) ||
     subloc != BLOOD || !sizeof(hits))
     return "";

  if(for_obj != on)
    str = (sizeof(hits) > 1 ? "Wounds" : "A wound") 
         + " on " + on->query_possessive() + " " + query_hits()
         + " " + (sizeof(hits) > 1 ? "are" : "is")
         + " bleeding.\n";
  else
    str = (sizeof(hits) > 1 ? "Wounds" : "A wound") 
         + " on your " + query_hits()
         + " " + (sizeof(hits) > 1 ? "are" : "is")
         + " bleeding.\n";

  return str;
}

void heal()
{
  string where;

  if(!sizeof(hits))
  {
    set_alarm(0.0, 0.0, remove_object);
    return;
  }

  hits -= ({ hits[0] });

  if(!sizeof(hits))
  {
    set_alarm(0.0, 0.0, remove_object);
    return;
  }
}

void add_hurt(string where)
{
  if(member_array(where, hits) == -1)
   hits += ({ where });

  if(!heal_alarm || !sizeof(get_alarm(heal_alarm)))
    heal_alarm = set_alarm(200.0, 500.0, heal);
}
