#pragma save_binary
#pragma strict_types

#include "local.h"

inherit EAST_ROAD;

#define MAX_RAB 1

void make_rab();
void add_stuff();

int alarm_id;
object *rab;
int no_of_rab;

void
create_er_room()
{
   area = "not far from";
   areaname = "Grey Havens";
   land = "the Shire";
   areatype = 1;
   areadesc = "field";
   grass = "green";
   
   extraline = "Nearby is Mithlond, or Grey Havens as most "+
   "people in these parts call it, and yet the surroundings are still wide open and the true "+
   "expanse of the fields of the Shire are apparent. Signs of animal life "+
   "abound, and what appear to be the walls of Mithlond appear on the "+
   "horizon to the west. South is the Great Eastroad and east finds "+
   "more fields.";
   
   add_item(({"walls","wall","mithlond","horizon"}),
      "Directly to your west you see the White Walls of Mithlond towering high "+
      "over the plains of Eriador.\n");
   
   add_item(({"signs","sign","animal life","animal"}),
      "You see many footprints across the fields here- some does you think, or "+
      "maybe even a bear.\n");
   
   add_item(({"surroundings","expanse","fields","shire"}),
      "They stretch out in all directions north, south, east and west. "+
      "In the middle, to your south, runs the Eastroad, a brown strip "+
      "in the middle of all this green.\n");
   
   add_exit(EAST_R_DIR + "er1","south");
   add_exit(EAST_R_DIR + "er2n","east");
   set_noshow_obvious(1);
   
   rab = allocate(MAX_RAB);
   add_stuff();
   
}

void
add_stuff()
{
   
   object hook;
   alarm_id = set_alarm(4.0,0.0,&make_rab());
   if(!present("hook"))
      {
      hook = clone_object(ER_OBJ + "hook");
      hook->move(TO);
   }
}
void
reset_shire_room()
{
   add_stuff();
}

void
make_rab()
{
   remove_alarm(alarm_id);
   alarm_id = 0;
   if(!rab[no_of_rab])
      {
      rab[no_of_rab] = clone_object(NPC_DIR + "squirrel");
      if(!random(MAX_RAB))
         {
         rab[no_of_rab]->set_random_move(5);
         rab[no_of_rab]->set_restrain_path("/d/Shire/eastroad/");
      }
      rab[no_of_rab]->move(TO);
      tell_room(TO,CAP(LANG_ADDART(rab[no_of_rab]->query_nonmet_name()))+" crawls into view.\n");
   }
   no_of_rab++;
   if(no_of_rab == MAX_RAB)
      {
      no_of_rab = 0;
      return;
   }
   if (alarm_id)
      alarm_id = set_alarm(itof(200 + random(200)),0.0,&make_rab());
   
}





