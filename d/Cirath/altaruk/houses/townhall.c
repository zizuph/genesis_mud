#include "../defs.h"
inherit "/d/Cirath/std/room.c";
#include "/d/Cirath/common/mobber.h"

void
reset_room()
{
   bring_room_mob("norad",ALT_NPC+"norad.c",1,0);
}

void
create_room()
{
    set_short("the town hall of Altaruk.");
    set_long("This is the town hall of altaruk. The hall" +
        " is narrow with a high ceiling. In the middle of" +
        " of the room a female dwarf sits behind a desk." +
        " There is a sign here.\n");
    
    add_item("sign", "The sign says:\n" +
        " Information desk.\n");

    add_item(({"wall", "walls"}), "The walls are sandstone." +
        " Thay look a bit worn down.\n");
       
    add_prop(ROOM_I_INSIDE,1);
    add_exit(ALT_STR + "12.c","south",0,1,0);

    reset_room();
}