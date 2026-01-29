/*
   Wayreth.

   laboratory.c
   ------------

   Coded ........: 970508
   By ...........: Karath

   Latest update : 
   By ...........: 

*/

#include "/d/Krynn/wayreth/local.h"
inherit TOWERROOM;

void
create_tower_room()
{
   set_short("Magic Research Laboratory");
   set_long("This is an extension of the laboratory above. This is used "+
      "by the mortal leaders of the guild in experiments to rediscover "+
      "lost spells. The room is bare except for a board, and some "+
      "rather strange looking scorch marks on the walls.\n");
   AI(({ "marks", "scorch marks"}), "The walls are covered in blackened " +
      "scorch marks, probably the result of magical experimentation. You  " +
      "have no idea if these particular experiments were successful or "+
      "not, but either way, it appears to be dangerous to be here when "+
      "someone is experimenting.\n");

   set_tell_time(180);
   add_tell("An acrid smell of smoke still hangs in the air.\n");
   add_tell("You hear the echos of strange arcane words go through "+
	"the tower.\n");

   add_exit(WTOWER + "laboratory", "up", 0);

   clone_object(WOBJ + "wohs_magic_board")->move(this_object());
}

public void
enter_inv (object ob, object from)
{
   ::enter_inv(ob, from);
   if (interactive(ob))
      start_room_tells();
    reset();
}
