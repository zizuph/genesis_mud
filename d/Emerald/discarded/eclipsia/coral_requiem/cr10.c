/* Created by Lucas */
/* Modified by Kieryn */
   

#include "/d/Emerald/eclipsia/edefs.h"
#include <stdproperties.h>
#include "/d/Emerald/defs.h"

inherit WATER_ROOM;

object kraken;

void reset_room()
{
   if (!kraken)
      {
      (kraken = clone_object(ECLIPSIA_NPC + "he_kraken"))->move(this_object(), 1);
      tell_room(this_object(), "returns to his lair.\n");
   }
}

void gate(object ob);


create_room()
{
   ::create_room();
   set_short("Caves around Coral Requiem");
   set_long("    You quickly realize what the great iron gate is for. " +
      "This is the lair of the great beast, the kraken. You see skulls " +
      "on the floor, along with the remains of unfortunate merfolk who " +
      "ventured too far into the depths of the cave. The merfolk " +
      "imprisoned the kraken here ages ago so it would no longer be a " +
      "threat to their community. Many a valiant soul have died in an " +
      "attempt to display their bravery by killing the ancient "+
      "beast.\n\n");
   
   add_item("gate", "The gate is to the northeast. You can still " +
      "squeeze through the bars.\n");
   add_item(({"skull", "skulls", "bones", "remains", "merfolk"}),
      "Sad remains of merfolk and other beings that have " +
      "fallen victim to the kraken litter the room.\n");
   
   add_prop(ROOM_I_TYPE, ROOM_UNDER_WATER);
   
   add_exit(CRDIR + "cr9", "northeast");
   reset_room();
}

enter_inv(object ob, object from)
{
   ::enter_inv(ob, from);
   
   gate(ob);
}

leave_inv(object ob, object to)
{
   ::leave_inv(ob, to);
   
   gate(ob);
}

void
gate(object ob)
{
   tell_object(ob, "\nYou manage to squeeze your body through the " +
      "iron bars.\n\n");
}
