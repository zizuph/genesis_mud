inherit "/d/Kalad/room_std";
#include "/d/Kalad/defs.h"

void 
create_room()
{
    ::create_room();
    set_short("City Gates");
    set_long(
"The clearing ends in a tall white-washed wall that runs from north to\n"+
"south. To the west, the well worn path rolls across a small field and\n"+
"then up a forested hill into the hills again. No path leads south, but\n"+
"a faint trail heads of north along the wall.\n");
    add_prop(ROOM_NO_TIME_DESC,1);
    add_exit(WILD(trail1),"north","@@block",0,0);
    add_exit(WILD(path10),"west","@@block",0,0);
    clone_object(NOBLE(obj/fgdoor1))->move(TO);
}

int
block()
{
    write("The way is not open yet.\nSpazm.\n");
    return 1;
}
