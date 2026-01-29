// 2003/12/25 Last update
// 2011/08/05 Lavellan - Removed bad duplicate hobbit spawn to void

#pragma save_binary
#pragma strict_types

#include "local.h"
#include H_MAKER

inherit EAST_ROAD;

#define MAX_RAB 1
#define MAX_CITIZENS 3

//   Prototypes
void make_rab();
void add_stuff();

int alarm_id;
object *rab;
int no_of_rab;
static object *hobbits = allocate(MAX_CITIZENS);

void
create_er_room()
{
   area = "not far from";
   areaname = "Grey Havens";
   land = "the Shire";
   areatype = 1;
   areadesc = "field";
   grass = "green";

   extraline = "Above you tower the Tower Hills, upon which stand "+
   "the three White Towers. The sides of the hills are covered in green "+
   "and only a few bushes dot them. "+
   "To the east and west stretch more fields and south runs the Eastroad.";
   
   add_item(({"white towers","towers","tower"}),
   "These towers are the White Towers built by the elves of "+
   "Mithlond. They were made to look over the sea to the Forbidden "+
   "Land, Tol Eressea.\n");

   add_item(({"surroundings","expanse","fields","shire"}),
   "They stretch out in all directions north, south, east and west. "+
   "In the middle, to your south, runs the Eastroad, a brown strip "+
   "in the middle of all this green.\n");

   add_item(({"hills","hill","bushes","bush"}),
   "The hills themselves, while steep, look very rich and full of life.\n");

   add_exit(EAST_R_DIR + "er1n","west",0,2,1);
   add_exit(EAST_R_DIR + "er3n","east",0,2,1);
   add_exit(EAST_R_DIR + "er2","south");
//   add_exit("/d/Shire/blue/road/rd01","north");

//   set_noshow_obvious(1);
   rab = allocate(MAX_RAB);
   add_stuff();
}

void
add_stuff()
{

    int index;
 
    setuid();
    seteuid(getuid());
 
    /* Loop over all elements in the array. */
    for(index = 0; index < MAX_CITIZENS; index++)
    {
        if (!objectp(hobbits[index]))
        {
//            hobbits[index] = clone_object(HOBBITMAKER);
            hobbits[index] = clone_object(HOBBITMAKER);
            hobbits[index]->set_type(CITIZEN);
            hobbits[index]->set_power(100);
            hobbits[index]->set_restrain_path(({"/d/Shire/eastroad/western", 
                "/d/Shire/eastroad/village/whit",
                "/d/Shire/common/hobbiton",
                "/d/Shire/michel" }));
            hobbits[index]->set_random_move(3);
            hobbits[index]->set_monster_home(EAST_R_DIR + "er2n");
            hobbits[index]->move(TO);
 
        }
    }

//  alarm_id = set_alarm(4.0,0.0,&make_rab());
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
         rab[no_of_rab]->set_restrain_path(EAST_R_DIR);
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
