inherit "/d/Gondor/common/room";

#include "/d/Gondor/defs.h"
#include "/sys/stdproperties.h"
#include "/sys/macros.h"
#include "/sys/ss_types.h"

object funohad;
 
void add_stuff();
void reset_room();

create_room() {
   set_short("The secret room");
   set_long(BSN("This is a secret room of a kind. " +
   "It seems to be the study of the owner. You can see " +
   "a large desk with some papers on it. "+
   "When you look around even more, you discover a weird exit " +
   "in the south wall."));
  
   add_item(({ "desk","large desk" }),
   BSN("The desk is large with some old papers spread out " +
       "all over it. Unfortunately you cannot read the papers " +
       "so you decide to let them be."));

   add_item(({ "exit","weird exit" }),
   BSN("When you examine the exit closely, you can see that " +
       "it is actually the back of the mirror in the bathroom. " +
       "It seems like a trick, but you think you can walk through " +
       "the mirror from this way whithout breaking it. Very strange " +
       "indeed."));
 
  
   add_exit(EDORAS_DIR + "rooms/uproom2","south", 0, 1);
  
   add_prop(ROOM_I_INSIDE,1);  /* This is a real room */
   add_stuff();
    reset_room();
}

 
add_stuff()
{
// funohad is broken. commented out for now. Finwe, May 2020
/*
  if (!funohad)
  {
log_file("runtime", ctime(time()) + ": "+this_interactive()->query_name() + " tried to load " + file_name(this_object()) + ".\n\n");
  funohad = clone_object(EDORAS_DIR + "npc/funohad");
  funohad->move(TO);
  }
*/
}
  
void
reset_room()
{
add_stuff();
}
