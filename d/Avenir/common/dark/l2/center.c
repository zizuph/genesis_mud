// file name: ~Avenir/common/dark/l2/center.c
// creator(s): Tepisch, longtimeago
// last update: Tepisch, Dec 94
// purpose:
// note: General clean up of code; modernizing to modern standards
// bug(s):
// to-do:

inherit "/std/room";
inherit "/d/Avenir/inherit/sair_wall";
#include "/d/Avenir/common/dark/dark.h"

void
create_room()   
{

  set_short("Tunnel");
  set_long(
 	"Shadows flicker all around this high-vaulted cavern. This room" +
	" is cut out of solid stone. Scratches and scrapes line the" +
	" walls as high as the available light carries. Tunnels branch"+
	" from this room in three directions.\n");


  AI(({"shadow", "shadows"}),
	"They seem to swallow up what light is avalable.\n");
  AI(({"scratch","scratches","scrape","scrapes"}),
	"They cover the walls completely. No pattern can be made out" +
	" of them.\n");
  AI(({"wall","walls"}),
	"They are completely covered in scratches and scrapes.\n");
  AI(({"tunnel","tunnels"}),
	"Nothing can be seen inside the tunnels. But that doesn't mean"+
	" that there's nothing there...\n");
	
  set_sair_dest(({L2+"add/t36", L1+"center", L4+"center"}));  
  add_sair_wall();
 
  BLACK
  IN	

	AE(L2 + "n1","north",0);
	AE(L2 + "e1","east",0);
	AE(L2 + "s1","south",0);

}

public void
init()
{
    ::init();
    sair_init();  
}