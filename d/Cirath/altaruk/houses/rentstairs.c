#include "../defs.h"
inherit "/d/Cirath/std/room.c";

int block();

void
create_room()
{
    set_short("in a dark alley in Altaruk.");
    set_long("The town is built up on the commerce that follows the" +
        " caravans that pass trough here. Sandstone and clay walls" +
        " makes up most of your view. Your standing at the top of" +
        " some stairs. You can hear the shouts of pedlers and guards" +
        " shouting orders about. Your outside a door.\n");

    add_item("stairs", "Stone steps going down to the street.\n");

    add_exit(ALT_ALL + "01.c", "down", 0, 1);
    add_exit("rentroom.c", "east", &block(), 1);

}

int
block()
{
    if(!(present("_altaruk_room_key_",TP)))
    {
        write("You fumble with the door for a second before you realize" +
            " you don't have the key. \n");
        say(QCTNAME(TP)+" fails to open the door and mumbles something" +
            " about a key.\n");
        return 1;
    }
    return 0;
}
