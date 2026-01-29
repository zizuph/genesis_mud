inherit "/std/room";
#include "/sys/macros.h"
#include "/sys/stdproperties.h"
#include "defs.h"
#include "/d/Cirath/common/defs.h"


void
create_room()
 {
  set_short("Steam Bath");
  set_long("Strangely enough, this room has been converted into a "
  	+"strange sort of steam bath.  Smooth marble seats line the "
  	+"walls, while in the middle of the room is a large black "
  	+"stone box which pours forth steam.  You see other men and "
  	+"women lounging about here, either cleaning themselves, or "
  	+"just enjoying the relaxing power of the steam.  You see a "
  	+"granite plaque hanging from the wall.\n");
  add_item(({"plaque","granite plaque"}),
  	"It is hanging from the wall and looks to have some readable "
  	+"instructions upon it.\n");
  add_item(({"seats","marble seats"}),"Large pieces of flawed marble "
  	+"has been thankfully donated by the generous nobles of Tyr "
  	+"for this steam bath.  It was probably done less out of "
  	+"charity and more so that the militia would not be filthy "
  	+"and stinky when entering noble houses.\n");
  add_item(({"box","black box","stone box","large box"}),
  	"This box apparently is what creates all of the steam in here.  "
  	+"It is made of perfectly smooth black rock of some sort and is "
  	+"warm to the touch.  There are hinges on it and it looks "
  	+"openable.\n");
  add_item("hinges","They look like regular hinges on a door.\n");
  add_cmd_item("box","open","As you open the box, a huge cloud of "
  	+"steam billows forth.  When it clears, you see a small 8 "
  	+"inch tall fire elemental and an equal size water elemental "
  	+"sitting on the ground and staring at each other coldly.  "
  	+"They both turn their soulless eyes to you, and you "
  	+"quickly close the lid on the box.\n");	
    add_cmd_item("plaque","read","Since some of the places in the "
	+"realms leave an unpleasant stain and filth upon us, "
	+"the noblemen of Tyr hereby give unto out faithful "
	+"protectors this wonderful steam bath.  By using "
	+"<wash me> you will be able to rid yourself of the "
	+"stench of these other big cities.\n");
  add_exit(MILITIA_ROOM + "startroom","south");
  add_exit(MILITIA_ROOM + "m10","west");
  set_alarm(1.0,0.0,"reset_room");
}

init()
{
         ::init();
	 add_action("wash", "wash");

}
int
wash(string str)
{
    if(str == "me")
    write("Already moist from the steam in the air, you utilize a "
    	+"rough edged piece of cloth provided by the bath to wash the "
    	+"grime and grit from your body.\n");
    set_alarm(1.0,0.0,"remove_dirt");
    return 1;
}
remove_dirt()
{
    object *ob;
    int i;
    ob = deep_inventory(TP);
    for (i = 0; i < sizeof(ob); i++)
        if (ob[i]->id("dirty"))
            ob[i]->remove_object();
    return 1;
}

