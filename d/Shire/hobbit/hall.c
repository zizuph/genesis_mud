#pragma save_binary

inherit "/d/Shire/room";
#include "/d/Shire/common/defs.h"
#include <stdproperties.h>
#include "hobbit.h"

int do_step(string str);
void
create_room()
{
    set_short("Hallway in the Adventuresome Hobbits guild");
    set_long("This small hallway connects the entrance with the "+
    "guild's living quarters.  To the southeast, you see a pub and "+
    "southwest is a quiet room.  A plaque adorns the south wall. "+
    "A thick, finely woven rug comforts any feet who step on it.\n");

   add_item("rug","It is made of wool and dyed a lovely forest green.\n");
   add_item("plaque","It has very important writing on it, please read it.\n");

   add_cmd_item("plaque","read","The plaque reads:\n"+
   "This guild is founded on the principles of good and adventuresomeness. "+
   "Should you shy away from the path of good, you will no longer be worthy "+
   "of your furry feet, and will be expelled.\n");

    add_prop(ROOM_I_INSIDE,1);
    add_prop(ROOM_M_NO_ATTACK,"No fighting, please!\n");
    
    add_exit(HOBGLD_DIR +"join","north",0,1);
    add_exit(HOBGLD_DIR + "inn_new","southeast",0,1);
    add_exit(HOBGLD_DIR + "start","southwest",0,1);
      

}

void
init()
{
    ::init();
    add_action("do_step","step");

}

int
do_step(string str)
{
   if(!str)
   {
    write("Step on what? The rug?\n");
   return 1;
     }

   if(str = "on rug")
   {
   write("You step carefully on the rug, inspecting the quality with your feet.\n");
   say(QCTNAME(TP)+ " steps carefully on the rug, inspecting its quality "+
   "with "+HIS_HER(TP)+ " bare feet.\n");
   return 1;
   }

}
