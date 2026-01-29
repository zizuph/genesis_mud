/*     Created by:     Sir Toby, 97-07-22
 *     Purpose:        The great hall of the Lizards lair.
 *     Location:       /d/Kalad/common/sewers/ll36.c
 *     Modified:       
 */


#pragma strict_types

inherit "/d/Kalad/room_std";
#include "/d/Kalad/defs.h"
#include "/d/Kalad/common/sewers/lizards_lair/path.h"


object king;
object guard1;
object guard2;
object guard3;
object guard4;
object guard5;
object guard6;
object king;

void
reset_room()
{

  if (!king)
      {
      king = clone_object("/d/Kalad/common/sewers/npc/lizard_king.c");
      king -> move_living("M",TO);
      }

   if (!guard1)
      {
      guard1 = clone_object("/d/Kalad/common/sewers/npc/king_guard.c");
      guard1 -> arm_me();
      guard1 -> move_living("M",TO);      
      }

   if (!guard2)
      {
      guard2 = clone_object("/d/Kalad/common/sewers/npc/king_guard.c");
      guard2 -> arm_me();
      guard2 -> move_living("M",TO);      
      }

   if (!guard3)
      {
      guard3 = clone_object("/d/Kalad/common/sewers/npc/king_guard.c");
      guard3 -> arm_me();
      guard3 -> move_living("M",TO);      
      }

   if (!guard4)
      {
      guard4 = clone_object("/d/Kalad/common/sewers/npc/king_guard.c");
      guard4 -> arm_me();
      guard4 -> move_living("M",TO);      
      }

   if (!guard5)
      {
      guard5 = clone_object("/d/Kalad/common/sewers/npc/king_guard.c");
      guard5 -> arm_me();
      guard5 -> move_living("M",TO);      
      }

   if (!guard6)
      {
      guard6 = clone_object("/d/Kalad/common/sewers/npc/king_guard.c");
      guard6 -> arm_me();
      guard6 -> move_living("M",TO);      
      guard1 -> team_join(guard2);
      guard1 -> team_join(guard3);
      guard1 -> team_join(guard4);
      guard1 -> team_join(guard5);
      guard1 -> team_join(guard6);

      tell_room(TO,"The lizardking arrives, accompanied " +
	   	"by six of his elite guards.\n");
      }
}



void
create_room()
{
::create_room();

    set_short("In a great hall");
    set_long("This is the east end of the great hall. " +
	     "The ceiling is a huge dome and it radiates a " +
	     "strange strong light. The floor is so smooth " +
	     "and polished that you can almost see your own " +
	     "reflection. You stand before the lizardkings " +
	     "huge throne. It is a few steps to get up to the " +
	     "throne. " + "@@dwarf_check");

    add_item("ceiling","The ceiling is huge and vaulted, creating " +
	     "a huge dome. It radiates a strange strong light.\n");
    add_item("floor","The floor is so smooth and polished that " +
		     "you can almost see your own reflection.\n");
    add_item("wall","On the wall is a great tapestry.\n");
    add_item("tapestry","The tapestry pictures two suns, one yellow " +
	     "and one red, over a deserted desert landscape.\n");
    add_item("throne","It is carved out of finest dark wood. It has " +
	     "carvings on the sides that pictures glorious battles " +
	     "between lizardmen and different creatures of the " +
	     "known world. \n" + "@@present_king_check");

    add_exit(PATH + "ll34.c","west",0,1);
    add_exit(PATH + "ll33.c","northwest",0,1);
    add_exit(PATH + "ll35.c","southwest",0,1);
    set_noshow_obvious(1);

    add_prop(ROOM_I_INSIDE,1);
    add_prop(ROOM_I_LIGHT,50);  // It is a magical light...

reset_room();

return;
}

string
dwarf_check()
{

    if(TP->query_race() == "dwarf")
        return"You sence that the ground " +
              "is totally flat and that you are deep under " +
              "the surface of Kabal.\n"; 

       return"\n";

}


string
present_king_check()
{

    if(king)
	return"The proud lizardking sits in his throne" +
	({".\n",
	  " studying you with piercing eyes.\n",
	  " appearing very thoughtful.\n",
	  " staring into nothingness.\n",
	  " thinking of his latest kill.\n",
	  " murmuring orders to his guards.\n"})[random(6)];

    return "\n";

}


