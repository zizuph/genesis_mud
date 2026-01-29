inherit "/std/room";

#include "/d/Roke/common/defs.h"

create_room()
{
	set_short("Hotel room in the Elfstone Tavern and Inn");
	set_long(BSS("You have entered small bedroom at the Elfstone "+
		"Tavern and Inn. There is a large comfortable bed here "+
		"where you can sleep. You notice a small sign hanging "+
		"just above the bed.\n"));

	add_item(({"sign","small sign"}), BSS(
		"It is a small sign made of steel. There is some "+
		"kind of writing on it.\n"));

	add_cmd_item(({"sign","small sign"}), "read", BSS(
		"When you want to sleep for some time, just type "+
		"<sleep in bed>, and you will go to sleep.\n"));

	add_item(({"bed","large bed","comfortable bed",
		"large comfortable bed"}), BSS(
		"This bed looks really comfortable, and you start "+
		"to dream about sleeping in it.\n"));


  add_exit(INNS_D+"inn1a","down",0);

  INSIDE;
}
init()
{
  ::init();

    add_action("start","sleep");
}
int start(string s)
{
  object ob;

  if(!(ob=present("tjop_dej_rom",TP)))
     {
	write(BSS("You don't dare sleep in this bed, since the room "+
		"is not yours.\n"));
       return 1;
     }
  NF("Sleep where ??\n");
  if(s!="in bed") return 0;

     ob->remove_object();

     TP->set_temp_start_location(INNS_D+"inn1c");

     write("You will start here the next time you enter the game.\n");
  TP->command("quit");
  return 1;
   }
