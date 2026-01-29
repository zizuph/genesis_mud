/*
 * /d/Gondor/lebennin/road/ghop3.c
 *
 *
 * Revision history:
 * Updated code - 05/06/96 - By Arren
 */
inherit "/d/Gondor/common/lib/field";

#include <stdproperties.h>
#include <macros.h>

#include "/d/Gondor/defs.h"
#include "/d/Gondor/common/lib/herbsearch.h"
#include "/d/Gondor/common/lib/herb_list.h"

#define MAX_GHOP 7

void    add_stuff();

object *ghop;
int     no_of_ghop,
        alarm_id;

void
create_room()
{
   
   area = "northeast";
   areaname = "Lebennin";
   land = "Gondor";
   areatype = 2;
   areadesc = "field";
   grass = "green";
   add_exit(LEB_DIR + "road/nr4","north",0,1);
   
   add_item("mound","This large mound fills your view to the south.\n"+
      "You think it is quite old.\n");
   add_item(({"bush","bushes"}),"These bushes are crawling with insects.\n");
   ghop = allocate(MAX_GHOP);
   add_stuff();
   set_up_herbs(({ONE_OF_LIST(HERBS), ONE_OF_LIST(HERBS), ONE_OF_LIST(HERBS), }),
                ({"bush", "bushes", "ground","grass"}), 6);
   
   make_the_room();
}

void
make_ghop()
{
   remove_alarm(alarm_id);
   alarm_id = 0;

   if(!objectp(ghop[no_of_ghop]))
   {
      ghop[no_of_ghop] = clone_object(NPC_DIR + "grasshopper.c");
      if(!random(MAX_GHOP))
      {
        ghop[no_of_ghop]->set_random_move(1);
        ghop[no_of_ghop]->set_restrain_path("/d/Gondor/lebennin/");
      }
      ghop[no_of_ghop]->move(TO);
      tell_room(TO,CAP(LANG_ADDART(ghop[no_of_ghop]->query_nonmet_name()))+" jumps from the bushes.\n");
   }
   no_of_ghop++;
   if(no_of_ghop == MAX_GHOP)
   {
      no_of_ghop = 0;
      return;
   }
    if (!alarm_id)
        alarm_id = set_alarm(itof(200 + random(200)), 0.0, make_ghop);

   extraline = "You have strolled off the main road and now all around "+
   "you are bushes. You see a large mound directly to your south.";
   
}

void
add_stuff()
{
    alarm_id = set_alarm(7.0, 0.0, make_ghop);
}

void
reset_room()
{
   ::reset_room();
   add_stuff();
}
