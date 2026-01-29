// Sarr,
// Fysix, recoded, March 1998

#include "default.h"

inherit NOBLE_ROOM;

void
create_noble_room()
{
    set_short("In the castle courtyard");
    set_long("You stand in a grassy courtyard right before "+
        "the large castle that dominates the Noble district. "+
        "The castle walls rise directly to your south. All around "+
        "you, flowers and bushes dot the area. The only way back out "+
        "of here is to the northwest.  There is a fountain here.\n");
    add_item(({"walls","castle"}),"The castle walls are made of grey stone "+
        "brick and mortar. As you gaze up, you see that they don't "+
        "reach very high up, but the towers do. You see many little "+
        "windows facing out of the walls.\n");
    add_item("bushes","Neat trimmed bushes.\n");
    add_item("flowers","There are all sorts of colors and patterns.\n");
    add_item("fountain","A large stone fountain of an eagle in a "+
        "pool stands here. There is no water in it, however.\n");
    
    add_exit(NOBLE + "castle/g4", "northwest", 0, 0);

    set_noshow_obvious(1);
}

