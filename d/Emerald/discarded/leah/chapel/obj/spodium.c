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
   add_adj("stone");
   set_short("Stone podium");
   set_long("This podium is constructed from a very large stone. It has "+
      "been chiseled and cut into it's current shape. The stone "+
      "has been polished until it gleams like cut glass.\n");
   
   add_prop(OBJ_I_WEIGHT, 100000);
   add_prop(OBJ_I_VOLUME, 50000);
   add_prop(OBJ_I_NO_GET, 1);
   add_prop(OBJ_I_LIGHT, 1);
   
   on_podium = ({ });
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
