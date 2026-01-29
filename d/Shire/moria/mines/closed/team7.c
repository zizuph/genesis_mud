inherit "/d/Shire/room";
#include "/d/Shire/greenfields/camp/tent.h"
#include "/d/Shire/orcmaker/orcmaker.h"
#define MAX_ORCS 4

object leader, *orcs = ({});

void add_stuff();
void reset_room();

create_room()
{
   set_short("Inside an orc tent");
   set_long("This tent is a bit neater than the camp outside, with sacks "+
   "directions, and some pots are piled up in a corner.\n");

   
   add_prop(ROOM_I_INSIDE,1);
   
   add_exit("/d/Shire/moria/mines/slime","east",0,1);

reset_room();
}
void
reset_room()
{
   set_alarm(55.0,0.0,"add_stuff");
}

void
add_stuff()
{
   int i;

    if(!leader)
     {
       leader = clone_object(ORCMAKER_DIR + "orcmaker");
       leader->set_type(9);
       leader->set_power(145 + random(100));
       leader->move(TO);
       leader->set_random_move(5);
      }


     if(!sizeof(orcs))
     orcs = allocate(MAX_ORCS);
     for(i = 0; i < MAX_ORCS; i++)
     if(!orcs[i])
     {
       orcs[i] = clone_object(ORCMAKER_DIR + "orcmaker");
       orcs[i]->set_type(9);
       orcs[i]->set_power(150 + random(75));
//       leader->team_join(orcs[i]);
       orcs[i]->set_random_move(5);
       orcs[i]->move(TO);

     }
/*
   else
       if(orcs[i]->query_leader() != leader)
       leader->team_join(orcs[i]);
*/
}
