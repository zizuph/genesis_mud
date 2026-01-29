/*
 * GRAVEYARD3.c
 * Re-described and updated by Alaron July 26, 1996
 */

inherit "/std/room";
 
#include "/d/Emerald/defs.h"
 
void
reset_room()
{
   object bat;
   int    i;
 
   bat=present("bat");
   if (bat)
      return;
   i = random(5);
   while (i-- > 0) {
      bat=clone_object( GRAVEYARD_DIR + "npc/bat");
      bat->move_living("into a room", this_object());
   }
}
 
void create_room()
{
   object door;
 
   set_short("Graveyard");
   
   set_long("  You stand atop a small plateau at the high end of "+
	    "of a dark green, wet field. The field is covered with "+
	    "hundreds of broken, worn, and neglected grave stones. A "+
	    "heavy cloud of thick, gray fog hovers in the air above "+
	    "the grave site. The small, flat clearing here at the top "+
	    "of the graveyard contains several small, broken headstones "+
	    "and one large grave stone in the middle of the wet grass.\n\n");

   add_item( ({"fog", "thick fog", "thick heavy fog"}),
	    "It is a thick cloud of eerie, dark fog which looms over "+
	    "the gravesite like a hungry vulture waiting for the prey "+
	    "to die. As you peer into the darkness of the fog you "+
	    "begin to feel lonely and start to despair ... You barely "+
	    "manage to shake the feeling off.\n");
 
   add_exit(GRAVEYARD_DIR + "graveyard2", "east", 0);
 
   add_item("note", "It says 'Out for lunch!'.  Strange that.\n");
 
 
   reset_room();
}
 
void
init()
{
   ::init();
   add_action("read", "read");
   add_action("do_move","move");
}
 
int
do_move(string str)
{
   NF("Move what?\n");
   if(!strlen(str))
      return 0;
 
   NF("You try to move it but it just won't budge.\n");
   if(str == "gravestone")
      return 0;
 
   else
      NF("You try to move the "+str+", but fail.\n");
   return 0;
}
 
int
read(string arg)
{
   if (arg != "note")
      return 0;
   write("It says 'Out for lunch!'. Strange that.\n");
   return 1;
}
