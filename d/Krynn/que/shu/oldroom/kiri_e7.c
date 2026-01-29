/* Created by Gorret 07/07/94 */

#include "../local.h"
inherit ATTACKROOM;
#include "/d/Krynn/common/random_meet.h"
#define "/d/Krynn/common/rndtables/tblwarkiri"

object monster;

void
create_attack_room()
{
    set_short("In front of the Que Kiri village");
    set_long("You stand before the entrance of a large village. " +
       "People here are entering and exiting the village through " +
       "two large open gates, which look as if they could swing " +
       "shut at a moments notice. The gates are hinged to a " +
       "tall stone wall which bends away from you appearing to " +
       "surround the entire village. You doubt that any marauding " +
       "band of attackers would test themselves against such a " +
       "formidable fortress.\n"); 
    set_change_msg(0, ATTACK);
    set_change_short(1, SMOK_ENTRANCE);
    set_change_long(1, BURN_ENTRANCE);
    set_change_msg(1, FIRES_DIEOUT);
    set_change_short(2, EMPTY_ENTRANCE);
    set_change_long(2, DESTED_VILLAGE);
    set_change_msg(2, STRANGE_WIND);
    set_change_short(3, EMPTY_VILLAGE);
    set_change_long(3, DRIFT_ENTRANCE);
    set_change_msg(3, REBUILD_ENTRANCE);
    set_change_short(4, BUSY_ENTRANCE);
    set_change_long(4, RETURN_ENTRANCE);
    set_change_msg(4, PEACE);

    OUTSIDE;

    add_exit(ROOM + "kiri_d7","north");

    add_item(({"gate","gates"}),"@@gate_desc");
    add_item(({"wall"}),"@@wall_desc");
    add_item(({"people","entrance"}),"@@people_desc");
    add_item(({"smoke","column"}),"@@smoke_desc");

}

string
gate_desc()
{
   switch (state_of_room)
    {
     case 2: return "The gates show signs of neglect. The great metal" +
         " pins on which the gates hinge have come loose from the" +
         " walls, making them look as if drunken craftsmen had built them.\n";
     case 3: return "These old gates show signs of rot and termites." +
         " Hanging at decrepit angles, they swing and flap in the" +
         " breeze creating a horrible screeching noise.\n";
     case 4: return "The gates are currently being repaired and" +
         " properly rehung by the village work crews.\n";
     default: return "The gates are made of strong timber and look" +
         " to be quite thick. They're currently open, allowing" +
         " for passage into and out of the village.\n";
    }
}

string
wall_desc()
{
   switch (state_of_room)
   {
    default: return OUTER_WALL;
   }
}

string
people_desc()
{
  switch (state_of_room)
  {
   case 1: return "Women and men are running out of the village like" +
         " rats. The screaming is awful. As people shove and push" +
         " their way out of the village and old man is knocked to" +
         " the ground. Helping him up, you can see the fear and" +
         " hopelessness in his facial expression before he pushes" +
         " you away and runs off.\n";
   case 2: return "Funny, you don't see a single soul.\n";
   case 3: return "These people look poor and homeless, they've" +
         " probably come here to search the rubble for valuables.\n"; 
   case 4: return "You see large groups or people arriving, bringing" +
         " their belongings, and hoping to start a new life here.\n";
   default: return "The activity here is brisk. People seem to be" +
         " arriving and departing the village in large numbers." +
         " Most of the traffic comes from the road leading to Solace." +
         " While some better equipped villagers look as if they had" +
         " just traversed the plains from the east.\n";
  }
}

string
smoke_desc()
{
  switch (state_of_room)
  {
   case 0: return "The only smoke you can see comes from the" +
      " village camp fires, rising into the sky as small white" +
      " streams against a blue background.\n";
   case 1: return "The black billowy smoke rises from the village" +
      " blocking out the sunlight, and casting the landside into" +
      " a sinister and evil darkness.\n";
   default: return "The smoke has long since died out from the village" +
      " fires. Nothing but blue sky and open plains here.\n";
  }
}

int
hook_change_room(int which)
{
    if (which == 0)
      {
   if (monster)
     return 0;
   monster = RANDOM_MEET(TABLE);
   monster->move_living("xx",TO);
   return 1;
      }
    if (which == 1)
      if (monster)
 return 0;
    return 1;
}

