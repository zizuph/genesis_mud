inherit "/std/room";

#include "default.h"

/* Prototypes */
void reset_room();

object paladin;
object guard1;
object guard2;
object guard3;
object guard4;

void
create_room()
{
   set_short("Guardroom");
   set_long(break_string("This is a communal guardroom where the elven "+
         "guards laze around in the nice cool atmosphere. There is a "+
         "fireplace here, presumably for the winter evenings.\n",76));

   add_exit(CASTLE_DIR + "1k11", "north", 0);
   
   add_item(({"fireplace","fire"}),"The fireplace is large and ornate "+
      "to say the least. It has many\ncarvings all over it, and a beautiful "+
      "crest on the top.\n");
   add_item(({"crest","carvings"}), "The crest and carvings are all one "+
      "really since they run into each other.\nThe crest is of the Royal "+
      "House of Telberin, whereas the carvings \nare of royalty "+
      "desplaying their affection for their rulers.\n");
   add_item("gate","You can just see the gate to the east.\n");

   add_prop(ROOM_I_INSIDE, 1);
   add_prop(ROOM_I_LIGHT, 1);
   reset_room();
}

void
reset_room()
{
   /* any member of the guard that is killed, will be restored */
   if (!paladin)
      {
      paladin = clone_object(NPC_DIR + "pal2");
      paladin->move_living("into the room", this_object());
   }
   if (!guard1)
      {
          //guard1 = clone_object(NPC_DIR + "humanoids/e_gua");
          //guard1->move_living("into the room", this_object());
   }
   if (!guard2)
      {
          //guard2 = clone_object(NPC_DIR + "humanoids/e_gua");
          //guard2->move_living("into the room", this_object());
   }
   if (!guard3)
      {
          //guard3 = clone_object(NPC_DIR + "humanoids/e_gua");
          //guard3->move_living("into the room", this_object());
   }
   if (!guard4)
      {
          //guard4 = clone_object(NPC_DIR + "humanoids/e_gua");
          //guard4->move_living("into the room", this_object());
   }
   
   /* make the guards join the team of the paladin
   if (guard1) paladin->team_join(guard1);
   if (guard2) paladin->team_join(guard2);
   if (guard3) paladin->team_join(guard3);
   if (guard4) paladin->team_join(guard4);
   */
}
