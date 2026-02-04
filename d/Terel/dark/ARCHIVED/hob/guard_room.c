
#include "/d/Terel/guilds/vamp/guild.h";
inherit "/d/Terel/guilds/vamp/room/vamp_room";
#include <stdproperties.h>

#define PATH "/d/Terel/dark/"

object *dark_arr;

reset_room()
{
   object mon;
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
try_south()
{   
    if (!IS_VAMP(TP) && !IS_BG(TP))
    {
        write("The way south is blocked by a door.\n");
        return 1;
    }
    write("You pass through the door as if it is not there.\n");
    return 0;
    
}

void
create_room()
{
   object door;
   set_short("Center of the lair");
   set_long("Darkness and stench are all-pervasive. "+
      "The stones themselves seem to belch foul "+
      "odors so intense your eyes water.\n"+
      "A massive wooden door is set into the south wall.\n");
   add_item("door", "A large iron-banded wood door. The emblem of\n"
      +"a skull has been burned into it. There is a large slot for\n"
      +"a key.\n");
/*
   door=clone_object(PATH + "hob/door2");
   door->move(this_object());
*/
   add_exit(PATH + "hob/entrance", "south", "@@try_south", 1, 1); //invis exit
   add_exit(PATH + "hob/n1", "north", 0);
   reset_room();
}
