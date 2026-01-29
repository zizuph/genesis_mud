//      Igneous'   Laughing gas container.

//      The object which distributes the laugh gas
//      effect to all living things in the environment
//      of this object.

//      Copyright (C)   Chad Richardson     March/96

#pragma save_binary

inherit "/std/object";

#include <filter_funs.h>
#include <macros.h>
#include <stdproperties.h>
#include "/d/Shire/common/defs.h"

#define GIGGLY_OBJ "/d/Shire/trickster/obj/giggly"

//  Prototypes
void timeout();
void start_gas();

int      delay_time, gas_release;

void
create_object()
{
   set_name("vial");
   set_long("This is what remains of a glass vial, which is now " +
      "broken and shattered.  Little bits of glass lie everywhere " +
      "so you best leave it alone, or you might cut yourself.\n");
   set_short("broken vial");
   set_adj(({"glass","broken"}));
   
   add_prop(OBJ_I_VALUE, 0);
   add_prop(OBJ_I_WEIGHT, 0);
   add_prop(OBJ_I_VOLUME, 0);
   add_prop(OBJ_M_NO_GET, "You don't dare pick up the sharp broken glass!\n");
   
   delay_time = set_alarm(0.5,0.0,&start_gas());
}

void
start_gas()
{
   remove_alarm(delay_time);
   tell_room(ENV(TO), "The glass vial breaks on impact on the ground, " +
      "releasing a strange gas.\n");
   gas_release = set_alarm(itof(1 + random(5)),0.0,&timeout());
}

void
timeout()
{
   object *people,
   giggles;
   int    i;
   
   remove_alarm(gas_release);
   
   people = FILTER_LIVE(all_inventory(ENV(TO)));
   
   if (!sizeof(people))
   {
      remove_object();
      return;
   }
   for (i = 0; i < sizeof(people); i++)
   {
      setuid(); seteuid(getuid());
      giggles = clone_object(GIGGLY_OBJ);
      giggles->move(people[i]);
      giggles->start_laughing(people[i]);
   }
   remove_object();
   return;
}
