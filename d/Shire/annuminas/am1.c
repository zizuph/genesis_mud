inherit "/d/Shire/room";
#include "/d/Shire/common/defs.h"
object ob;

create_room() 
{

set_short("Broken Road");
set_long("The grassy fields give way to an old broken stone road leading "
        +"north. In that direction seem to be some ruins in the "
        +"distance, but a thick mist covers the ground. All around "
        +"lies grassy plains, lush and green, indicating a nearby "
	   +"water source. Dotting the plains are small piles "
	   +"of rubble, rocky rubble of some sort.\n");
add_item(({"road"}),"This is an old stone leading northwards. The "
		   +"broken marble slabs are laying astray of a "
		   +"normal path, and grass has sprouted between the slabs.\n");
add_item(({"ruins"}),"Not much is visible, but it seems to be "
		    +"the ruins of a rather large town. A small "
		    +"stream of smoke is trailing into the air, "
		    +"the only sign of life in the area.\n");
add_item(({"grass","plains"}),"A large grassy plain, with tall "
			     +"thick, green grass sprouting "
			     +"everywhere, covering the ground "
			     +"like a blanket.\n");
add_item(({"rubble","piles"}),"These small piles of rubble look "
		    +"like the remnants of a small wall that was "
		    +"overrun and destroyed.\n");
add_item(({"mist"}),"This is a thick, moist mist that floats just "
		   +"above the grass. It obscures your vision "
		   +"just enough so you can't make out the ruins "
		   +"in the distance.\n");

    add_exit(ANNUM_DIR + "am2","north",0,1);
     add_exit(EVENDIM_DIR + "ev9","south",0,1);

//   "/d/Shire/annuminas/orcroom1"->teleledningsanka();
  
}

void
init()
{
    ::init();
    if (interactive(this_player()))
        catch(call_other("/d/Shire/annuminas/monsters/clone_handler.c", "??"));
}
