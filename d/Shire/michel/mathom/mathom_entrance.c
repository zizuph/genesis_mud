inherit "/d/Shire/room";
#include "/d/Shire/common/defs.h"
#include "/sys/stdproperties.h"

void add_stuff();
void reset_room()
{
  set_alarm(0.8,0.0,"add_stuff");
}


void
create_room()
{
    add_prop(ROOM_S_MAP_FILE, "michel_delving.txt");

   set_short("The entrance hall to the Mathom-house of Michel Delving");
   set_long("This is the entrance hall to the Mathom-house of Michel Delving."+
   " It is a museum of sorts for items belonging to famous hobbits and not so famous hobbits "+
   "as well. Some parts of the museum are reserved for show, and "+
   "others are saved as a warehouse, where anyone can "+
   "leave or take anything from the Mathom-house. Very important "+
   "mathoms will not be allowed to be taken, however. "+
   "Please be on the best behavior, do not damage the artifacts!\n");

   add_item(({"artifact","artifacts","mathom","mathoms"}),
   "The artifacts are kept in the museum proper. This is merely "+
   "the entry-way.\n");
   add_item("hobbits","The hobbits are not kept here, but their "+
   "mathoms are.\n");
   add_item(({"warehouse","mathom-house","entrance"}),
   "The entrance-way in which you stand leads into the mathom-house "+
   "proper, where artifacts and mathoms are kept for show and "+
   "for storage.\n");

   add_prop(ROOM_I_INSIDE, 1);
   reset_room();
   add_exit(MICH_DIR + "mathom/mathom1","north");
   add_exit(MICH_DIR + "gamroad3","east",0,1);

}

void
add_stuff()
{
   object doorman, janitor;

   if(!find_living("_rosa_"))
   {
     doorman = clone_object(MICH_DIR + "npc/doorman");
     doorman->move(TO);
   }

   if(!find_living("_alva_"))
   {
    janitor = clone_object(MICH_DIR + "npc/janitor");
    janitor->move(TO);
   }

}
