// updated by Lilith Dec 2021: moved from Sorgum's dir to Terel/common
//    updated to Terel std room, etc

#include "/d/Terel/include/Terel.h"
inherit STDROOM;


int ribbon_gone_flag; 

void
reset_room()
{
     ribbon_gone_flag = 0;
}

string 
do_search(object searcher, string str)
{
    object ribbon;

	if (str != "mattress" && str != "straw")
      return "Your search reveals nothing special.\n";

    if (!ribbon_gone_flag) 
    {
        ribbon_gone_flag = 1;
	    ribbon = clone_object("/d/Terel/common/moor/obj/ribbon");
	    ribbon->move(searcher, 1);
	    say(QCTNAME(TP) + " finds something in the bed.\n");
        return "You find a metal ribbon.\n";
	}
    else
	  return "It looks like the mattress was recently searched "+
             "by another. There isn't anything here.\n";
}


void
create_room()
{
    set_short("cottage bedroom");
    set_long(
	"A small bedroom off of the kitchen.  The flagstone floor only " +
	"reaches part way into the room and the rest of the floor is " +
	"covered with shale tiles. There is a small bed along one wall, "+
    "and not much else. It looks like whoever lived here took everything "+
    "with them.\n"
    );

    add_item(({"bed", "small bed"}), 
	"The small bed is a straw-stuffed mattress on a wooden frame.  "+
    "The headboard is inscribed with the initials T.A.\n"
    );

    add_item(({"mattress", "straw" }),
    "It is lumpy and moldy.\n");

    add_item(({"floor", "flagstone", "shale", "tiles", "shale tiles"}),
    "The flagstone floor from the kitchen extends a few steps into the room. "+
    "The majority of the bedroom is floored in shale tiles.\n");	
	
    add_item(({"wall", "walls", "mold", "cobwebs" }),
    "The walls are decorated with mold and cobwebs.\n");
	
    add_prop(ROOM_I_INSIDE, 1);
    add_prop(OBJ_S_SEARCH_FUN, "do_search");
    add_prop(OBJ_I_SEARCH_TIME, 2);

    add_exit("cottage_kitchen", "east", 0);
    
}


