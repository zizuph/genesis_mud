// updated by Lilith Dec 2021: moved from Sorgum's dir to Terel/common
//    updated to Terel std room, etc

#include "/d/Terel/include/Terel.h"
inherit STDROOM;

void
init()
{
     ::init();
     add_action("do_sit", "sit");
}

void	  
create_room()
{
    set_short("cottage sideroom");
    set_long(
        "This side room is mostly bare. There is nothing in the room " +
	"other than a table with low stone benches. Windows run most of "+
    "the length of the room.\n"
    );

    add_item(({"bench", "benches"}), 
	"The low stone benches are made of the same flagstone as the " +
	"floor.  They look like they would hurt your butt if you sat in " +
	"them too long.\n"
    );

    add_item(({"table"}),
    "The table is covered in dust, but looks like it was once a nice "+
    "place to take a meal or snack while looking out the windows.\n");
	
    add_item(({"window", "windows"}),
    "The windows are mostly covered in grime, but you can see the "+
	"hills and forest surrounding the cottage.\n");
	
    add_prop(ROOM_I_INSIDE, 1);
    add_exit("cottage_in", "west", 0);
}

int
do_sit(string what)
{
     write("The cold stone makes your rear end sore so you stand back up.\n");
     return 1;
}

