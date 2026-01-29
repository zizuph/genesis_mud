// a home in the villager
#include "defs.h"
inherit  ROOM+"home";
#define  EXIT_DIR "south"
 
void reset_room()
{
   make_npcs();
   set_all_random_move(60);
}
 
void create_khalakhor_room()
{
   create_home(EXIT_DIR);
   add_exit("court4",EXIT_DIR);
   setup_villagers(1+random(2));
   name[0]="brid"; // brid is first (only?) villager
   reset_room();
}
