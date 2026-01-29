// a home in the villager
#include "defs.h"
inherit  ROOM+"home";
#define  EXIT_DIR "west"
 
void reset_room()
{
   make_npcs();
   set_all_random_move(60);
}
 
void create_khalakhor_room()
{
   create_home(EXIT_DIR);
   add_exit("court5",EXIT_DIR);
   setup_villagers(random(3));
   reset_room();
}
