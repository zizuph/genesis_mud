/*    Teleportation pool fo WoHS spell quest 
 *    Found in the temple of Huerzyd.
 *
 *    - Arman, June 2020 
 */


inherit "/std/object";
#include "/d/Krynn/common/defs.h"
#include "/d/Krynn/guilds/wohs/defs.h"
#include <macros.h>

int mirror_activated = 0;

#define WOHS_MIRROR_PORTAL_PROP "_wohs_mirror_portal_prop"
#define MIRROR_DESTINATION      "/d/Ansalon/taman_busuk/sanction/room/city/volcano_side"

public void
create_object()
{
    set_name("pool");
    set_adj("large");
    add_adj("shallow");
    set_short("shallow pool");
    add_name("_wohs_mirror_portal");
    set_long("This is the magical pool in the Temple of Huerzyd.\n");

    add_prop(OBJ_I_VOLUME, 200000);
    add_prop(OBJ_I_WEIGHT, 13200);
    add_prop(OBJ_I_VALUE, 0);
    add_prop(OBJ_M_NO_GET, "How do you plan on picking up the shallow " +
        "pool?\n");
    add_prop(OBJ_M_NO_STEAL, 1);

    set_no_show();

    add_prop(MAGIC_AM_ID_INFO, ({ "This is a magical pool dedicated to the " +
        "God of Magic, Solinari. Those learned in High Sorcery are familiar " +
        "with such magical pools as devices of teleportation.\n", 35 }));
    add_prop(MAGIC_AM_MAGIC, ({ 10, "enchantment" }));

}

public void
deactivate_magic_mirror()
{
   if(!mirror_activated)
     return;

   tell_room(E(TO), "The shallow reflection pool ceases to glow.\n", ({  }) );
   mirror_activated = 0;
   return;
}

public void
activate_magic_mirror(object caster)
{
   if(mirror_activated)
     return;

   tell_room(E(TO), "The shallow reflection pool suddenly begins to glow " +
        "with a radiant light!\n", ({  }) );
   mirror_activated = 1;
   set_alarm(30.0, 0.0, &deactivate_magic_mirror());
   return;
}

public int
query_magic_mirror()
{
   return mirror_activated;
}

int 
enter(string str)
{
    if ((str=="pool") || (str=="shallow pool") || (str=="reflection pool")) 
    {

     if(mirror_activated && TP->query_prop(WOHS_MIRROR_PORTAL_PROP))
     {
         write("You step into the shallow pool, teleporting away from " +
             "the Temple!\n\n\n\n");
         say(QCTNAME(TP)+ " steps into the shallow pool and vanishes! " +
             C(HIS(TP))+ " image appears in the reflection of the pool " +
             "briefly.\n");
         TP->move_living("M", MIRROR_DESTINATION, 1, 0);
         tell_room(E(TP), QCTNAME(TP)+ " appears into the room!\n", ({ TP }) );
         deactivate_magic_mirror();
         return 1;
      }
      else if(mirror_activated)
      {
         write("You enter the pool, however nothing happens.\n");
         say(QCTNAME(TP)+ " splashes around in the pool briefly.\n");
         return 1;
      }
      else
      {
        write("You step into the pool. Its waters are neither " +
            "warm nor cold.\n");

         say(QCTNAME(TP)+ " steps into the pool briefly.\n");
         return 1;
      }
    }
    notify_fail("Enter what?\n");
   return 0;
}

void
init()
{
   ::init();
   add_action(enter, "enter");

}
