
#include "/d/Terel/guilds/vamp/guild.h";
inherit "/d/Terel/guilds/vamp/room/vamp_room";
#include <stdproperties.h>

#define PATH "/d/Terel/dark/"

object *dark_arr, door;

reset_room()
{
   object mon;
   door->reset_object();
   if (!dark_arr)
      dark_arr = ({ 0, 0, 0, 0, 0, 0 });
   call_out("delay_reset_room", 1, 0);
   if(present("lizard")) return;
   mon=clone_object(PATH + "mon/lizard");
   mon->move(this_object());
}

delay_reset_room(which_dark) {
   if (!dark_arr[which_dark])
      darks(which_dark);
   if (which_dark < 5) 
      call_out("delay_reset_room", 1, which_dark + 1);
}

darks(which_dark)
{
   object ob;
   ob = clone_object("/d/Terel/dark/mon/hobgoblin");
   ob->move_living("xx", this_object());
   
   dark_arr[which_dark] = ob;
}

int
try_north()
{   
    if (!IS_VAMP(TP) && !IS_BG(TP))
    {
        write("The way north is blocked by a door.\n");
        return 1;
    }
    write("You pass through the door as if it is not there.\n");
    return 0;
    
}

void
create_room()
{
   set_short("Lair Entrance");
   set_long(
      "This blackened cavern echoes sounds of grief coming from\n"
      +"the deeper parts of the world. The cavern area has been\n"
      +"crudely carved from the stone. A corridor leads up.\n"
      +"A massive wooden door is set into the north wall.\n");
   add_item("door", "A large iron-banded wood door. The emblem of\n"
      +"a skull has been burned into it. There is a large slot for\n"
      +"a key.\n");
/* 
   door=clone_object(PATH + "hob/door1");
   door->move(this_object());
   door->set_key(6056);
*/
   add_exit(PATH + "hob/guard_room", "north", "@@try_north", 1, 1); //invis exit
   add_exit(PATH + "s3c", "up", 0);
   reset_room();
}
