/* Final teleportation device fo WoHS Test - Arman 2017     */


inherit "/std/object";
#include "/d/Krynn/common/defs.h"
#include "/d/Krynn/guilds/wohs/defs.h"
#include <macros.h>

int mirror_activated = 0;

#define WOHS_MIRROR_PORTAL_PROP "_wohs_mirror_portal_prop"
#define MIRROR_DESTINATION      "/d/Krynn/guilds/wohs/test/room/void1.c"
#define HEARTROOM_ACTIVATED     "_wohs_test_heartroom_activated"
#define COMPLETED_TEST          "_wohs_test_completed_test"

public void
create_object()
{
    set_name("pool");
    set_adj("large");
    add_adj("shallow");
    set_short("large shallow pool");
    add_name("_wohs_mirror_portal");
    set_long("This is the magical pool in the Tower of Daltigoth.\n");

    add_prop(OBJ_I_VOLUME, 200000);
    add_prop(OBJ_I_WEIGHT, 13200);
    add_prop(OBJ_I_VALUE, 0);
    add_prop(OBJ_M_NO_GET, "How do you plan on picking up the shallow " +
        "pool?\n");
    add_prop(OBJ_M_NO_STEAL, 1);

    set_no_show();

    add_prop(MAGIC_AM_ID_INFO, ({ "This is a magical pool that is part " +
        "of the Test of High Sorcery, the final gate to complete the " +
        "test!\n", 75 }));
    add_prop(MAGIC_AM_MAGIC, ({ 10, "enchantment" }));

}

public void
deactivate_magic_mirror()
{
   if(!mirror_activated)
     return;

   tell_room(E(TO), "The large shallow pool ceases to glow.\n", ({  }) );
   mirror_activated = 0;
   return;
}

public void
activate_magic_mirror(object caster)
{
   if(mirror_activated)
     return;

   if(!caster->query_prop(HEARTROOM_ACTIVATED))
   {
       caster->catch_msg("Nothing seems to happen.\n");
       return;
   }

   tell_room(E(TO), "The large shallow pool suddenly begins to glow " +
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
    if ((str=="pool") || (str=="shallow pool")) 
    {

     if(mirror_activated && TP->query_prop(WOHS_MIRROR_PORTAL_PROP))
     {
         write("You step into the shallow pool, teleporting away from " +
             "the Tower as it explodes!\n\n\n\n");
         say(QCTNAME(TP)+ " steps into the shallow pool and vanishes! " +
             C(HIS(TP))+ " image appears in the reflection of the pool " +
             "briefly.\n");
         TP->add_prop(COMPLETED_TEST, 1);
         WOHS_MANAGER->add_wohs_test_props(TP, COMPLETED_TEST, 1);
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
         if(TP->query_prop(HEARTROOM_ACTIVATED))
            write("You step into the pool. Radiant energies swirl " +
                "around your feet like those of the Rivers of Time in " +
                "the well at Wayreth, however nothing happens. " +
                "It feels like you are missing something?\n");
         else
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
