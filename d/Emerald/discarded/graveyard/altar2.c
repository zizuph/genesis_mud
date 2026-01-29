inherit "/std/room";
 
#include "/d/Emerald/defs.h"
 
void
create_room()
{
   add_prop(ROOM_I_INSIDE, 1);
   set_short("Behind altar");
   set_long("There is only just enough space to move here "+
         "behind the altar. There is only one exit and that is "+
         "back out into the church. The back of the altar is "+
         "digging into your back.\n");
   add_exit(GRAVEYARD_DIR + "church", "out", 0);
   add_item("altar", "The altar is made of finely crafted "+
         "stone blocks that fit together perfectly. Their "+
         "craftwork is from an age long forgotten in this "+
         "world.\n");
   add_item("blocks", "The blocks are remarkably carved, without "+
      "the need for mortar to bind them together. One "+
      "of the blocks seems to be slightly worn, however.\n");
}
 
query_no_snoop()
{
   return 1;
}
 
init()
{
   add_action("press_stone", "press");
   add_action("press_stone", "push");
   add_action("press_stone", "depress");
   ::init();
}
 
int
press_stone(string str)
{
   if(!strlen(str))
      {
      write("Do what?\n");
      return 1;
   }
   if((str == "worn stone") || (str == "stone") || (str == "block"))
      {
      tell_room( GRAVEYARD_DIR + "church", "A strange "+
         "noise echoes around the room, then suddenly all is quiet "+
         "again.\n");
      write("You press the worn stone and it moves with a barely "+
         "audible 'click'.\nYou feel the world tilt underneath you "+
         "and you fall down until\nyou hit hard earth.\n");
      tell_room( OCHURCH_DIR + "entry", QCTNAME(this_player())+
         " falls from the opening above.\n");
      this_player()->move_living("M",OCHURCH_DIR + "entry");
      return 1;
   }
}
 
