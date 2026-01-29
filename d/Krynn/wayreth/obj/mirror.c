/* Magic teleportation mirror - Arman 2017     */
/* Based on mirror in VK, by Teth, Jan 15 1997 */

inherit "/std/object";
#include "../../local.h"
#include "/d/Krynn/common/defs.h"
#include <macros.h>

int mirror_activated = 0;

#define WOHS_MIRROR_PORTAL_PROP "_wohs_mirror_portal_prop"
#define MIRROR_DESTINATION "/d/Krynn/solace/poolbottom/room/landing.c"

string
long_desc()
{
   if(mirror_activated)
     return ", and glowing with a magical light";
   else
     return "";
}

public void
create_object()
{
    set_name("mirror");
    add_name("_wohs_mirror_portal");
    set_short("@@short_desc");
    set_adj(({"framed","silvered"}));
    set_long("This silvered mirror is elegantly framed, with sweeping " +
        "scrolls of bronze surrounding it. It is leaning against the wall. " +
        "This mirror is frequently stared into, by those wishing to " +
        "inspect themselves. It is about two meters high@@long_desc@@.\n");
    add_item(({"frame","elegant frame"}),"The elegant frame is made of bronze, " +
        "with a scrolled pattern.\n");
    add_item(({"sweeping scrolls","scrolls","scrolled pattern","pattern"}),
        "Bronze and elegant, the scrolls surround the mirror.\n");
    add_item("silver","The silver is flawless on the surface of the mirror.\n");
    add_item(({"surface","mirror surface","silvered surface"}),"The surface " +
        "of the mirror reflects all light that enters it.\n");

    add_prop(OBJ_I_VOLUME, 8000);
    add_prop(OBJ_I_WEIGHT, 3200);
    add_prop(OBJ_I_VALUE, 500);
    add_prop(OBJ_M_NO_GET, "It is attached to the wall at the top, and the " +
       "floor at the bottom.\n");
    add_prop(OBJ_M_NO_STEAL, 1);

    add_prop(MAGIC_AM_ID_INFO, ({ "This mirror radiates traces of magic, " +
				  "and is capable of being used by experienced magic " +
                                  "users as a portal between locations.\n", 25,
                                  "In days long ago these mirror portals were " +
                                  "common, however have since become rare and " +
                                  "fallen out of use.\n", 45, "Lore states that " +
                                  "some mirror portals have at times teleported " +
                                  "wizards to the Abyss, where they have become " +
                                  "play things of demons!\n", 75 }));
    add_prop(MAGIC_AM_MAGIC, ({ 10, "enchantment" }));

}

string
short_desc()
{
   if(mirror_activated)
     return "glowing silvered mirror";
   else
     return "framed, silvered mirror";
}

public void
deactivate_magic_mirror()
{
   if(!mirror_activated)
     return;

   tell_room(E(TO), "The framed, silvered mirror ceases to glow.\n", ({  }) );
   mirror_activated = 0;
   return;
}

public void
activate_magic_mirror()
{
   if(mirror_activated)
     return;

   tell_room(E(TO), "The framed, silvered mirror suddenly begins to glow... " +
         "its reflection blurring and changing.\n", ({  }) );
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
stare(string str)
{
    if ((str=="mirror")||(str=="into mirror")) 
    {

     if(mirror_activated)
     {
         write("Staring into the mirror, you no longer see a reflection of yourself! " +
            "You see a room somewhere else... the top of a landing overlooking the great " +
            "hall within the school of High Magic in Poolbottom. The vision looks so real, " +
            "you feel you could enter the mirror to go to that location.\n");
         say(QCTNAME(TP)+ " stares into the mirror, seeing a vision of somewhere else!\n");
         return 1;
      }
      else
      {
         write("Staring into the mirror, you see a reflection of yourself.\n");
         say(QCTNAME(TP)+ " stares into the mirror, seeing a reflection of " +
              HIM(TP)+ "self.\n");
         return 1;
       }
    }
    notify_fail("Stare where?\n");
   return 0;
}

int 
enter(string str)
{
    if ((str=="mirror")||(str=="into mirror")) 
    {

     if(mirror_activated && TP->query_prop(WOHS_MIRROR_PORTAL_PROP))
     {
         write("You step through the mirror and in to another room...\n");
         say(QCTNAME(TP)+ " walks into the mirror and vanishes! " +C(HIS(TP))+
             " image appears in the reflection of the mirror briefly, before " +
             "returning to normal.\n");
         TP->move_living("M", MIRROR_DESTINATION, 1, 0);
         tell_room(E(TP), "The framed, silvered mirror suddenly glows.\n" +
            "The mirror's reflection blurs as " +
            QTNAME(TP)+ " steps out of it and into the room!\n" +
            "The framed, silvered mirror ceases to glow.\n", ({ TP }) );
         deactivate_magic_mirror();
         return 1;
      }
      else if(mirror_activated)
      {
         write("You try and walk through the mirror, but you find yourself " +
            "unable to pass through.\n");
         say(QCTNAME(TP)+ " tries to walk through the glowing mirror, but " +
            "fails.\n");
         return 1;
      }
      else
      {
         write("You walk into the mirror. You find it solid. Ouch.\n");
         say(QCTNAME(TP)+ " walks into the mirror, wincing slightly when " +
            "finding it as solid as it looks.\n");
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
   add_action(stare, "stare");
   add_action(enter, "enter");

}
