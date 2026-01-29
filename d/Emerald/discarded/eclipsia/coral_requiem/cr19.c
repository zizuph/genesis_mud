/* Created by Lucas */
/* Modified by Kieryn */
// Modified by Rohim.    

#include "/d/Emerald/eclipsia/edefs.h"
#include <stdproperties.h>
#include "/d/Emerald/defs.h"

inherit WATER_ROOM;
object she_kraken;

void reset_room()
{
   if (!she_kraken)
   {
       (she_kraken = clone_object(ECLIPSIA_NPC + "shekraken"))->move(this_object(), 1);
   tell_room(this_object(), "returns to her lair.\n");
    }
}

create_room()
{
   ::create_room();
   clone_object("/d/Emerald/eclipsia/obj/doorb")->move(this_object());
   set_short("Caves around Coral Requiem");
   set_long("    This great, high-walled room has no ceiling. It is " +
      "covered only by the open water. This is the lair of a great " +
      "kraken. Ahead to the southeast, you spot a shipwreck. These " +
      "waters must be in the open sea. The kraken has guarded " +
      "the shipwreck for years, hoarding whatever treasures it must " +
      "hold.\n\n");
   
   add_item(({"skulls", "bones", "bone", "skull"}), "Skulls and bones of " +
      "many victims lie across the floor.\n");
   add_item("shipwreck", "A great ship must have fallen victim to " +
      "the kraken who lives here. Who knows what it may hold?\n");
   
   add_prop(ROOM_I_TYPE, ROOM_UNDER_WATER);
   
   add_exit(CRDIR + "cr18", "northwest");
   add_exit(CRDIR + "cr20", "southeast");
   reset_room();
}

