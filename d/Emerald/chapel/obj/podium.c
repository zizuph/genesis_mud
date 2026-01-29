/* chapel/obj/podium.c is cloned by chapel/chapel.c */
inherit "/std/object";

#include <stdproperties.h>
#include <composite.h>
#include "../chapel.h"

object *on_podium;

void
create_object()
{
   set_name("podium");
   add_adj("sturdy");
   set_short("@@short_desc@@");
   set_long("@@long_desc@@");
   
   add_item(({"panel","panels"}), "Rainbows dance across the panels as the light reflects off them.\n");
   add_item("wood","This is a highly polished wood from one of the many trees growing in the forest around the chapel.\n");
   
   add_prop(OBJ_I_WEIGHT, 100000);
   add_prop(OBJ_I_VOLUME, 50000);
   add_prop(OBJ_I_NO_GET, 1);
   add_prop(OBJ_I_LIGHT, 1);
   
   on_podium = ({ });
}

string
short_desc()
{
   string str;
   int    i;
   
   for (i=0 ; i<sizeof(on_podium) ; i++)
   if (on_podium[i])
      on_podium[i]->set_no_show_composite(0);
   str = "sturdy podium";
   if (sizeof(on_podium))
      str += " with " + COMPOSITE_LIVE(on_podium) + " standing on it";
   for (i=0 ; i<sizeof(on_podium) ; i++)
   if (on_podium[i])
      on_podium[i]->set_no_show_composite(1);
   return str;
}

string
long_desc()
{
   string str;
   int    i;
   
   for (i=0 ; i<sizeof(on_podium) ; i++)
   if (on_podium[i])
      on_podium[i]->set_no_show_composite(0);
   str = "The sturdy podium is made from a highly polished wood, with "+
   "two long crystal panels in the front.";
   if (sizeof(on_podium)) {
      str += " " + capitalize(COMPOSITE_LIVE(on_podium)) + " ";
      if (sizeof(on_podium) > 1)
         str += "are";
      else
         str += "is";
      str += " standing on it.";
   }
   for (i=0 ; i<sizeof(on_podium) ; i++)
   if (on_podium[i])
      on_podium[i]->set_no_show_composite(1);
   str += "\n";
   return str;
}

void
living_entered(object ob)
{
   if (present("wand", ob) && !ob->query_prop(IS_BRIDE)
         && !ob->query_prop(IS_GROOM)) {
      ob->set_no_show_composite(1);
      if (member_array(ob, on_podium) < 0)
         on_podium += ({ ob });
   }
}

void
living_left(object ob)
{
   if (!ob->query_prop(IS_BRIDE) && !ob->query_prop(IS_GROOM)) {
      ob->set_no_show_composite(0);
      on_podium -= ({ ob });
   }
}
