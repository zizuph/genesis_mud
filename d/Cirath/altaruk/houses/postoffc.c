#pragma save_binary

inherit "/d/Cirath/std/room";
inherit "/d/Genesis/lib/post";
#include "../defs.h"
 
void create_room()
{
    set_short("the message center");
    set_long("The Altaruk Post Office is little more than a single clay "+
             "room with some fast erdlus out back to deliver messages. "+
             "A stone counter with writing carved into it serves the "+
             "almost equally stony clerk as a place to rest his head, "+
             "and a window looks outside.\n");
 
    add_item("clerk", "It is not wise to disturb a sleeping dwarf.\n");
    add_item(({"counter", "writing"}), "The counter looks uncomfortable, "+
             "but the carved writing is quite readable.\n");
             
    add_cmd_item(({"counter", "writing"}), "read", "It seems to be "+
             "instructions for the use of the Center:\n"+
                "   read #           Read your mail.\n"+
                "   mail <player>    Mail to another player by 'name'.\n"+
                "   from             List all incoming mail by header.\n");

    add_exit(ALT_STR+"19", "east", 0, 1);
    INSIDE

}
 
init()
{
  ::init();
  post_init();
}
 
leave_inv(ob,to)
{
  ::leave_inv(ob,to);
  post_leave_inv(ob,to);
}
