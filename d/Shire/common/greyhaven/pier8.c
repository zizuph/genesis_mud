inherit "/d/Shire/std/room";
/*
 * Sets flag in players from calling dragons into ME.
 * Disabled by request of Admin, June 2001
#include "/d/Gondor/common/lib/gs_include.c"
*/
#include "/d/Shire/common/defs.h"

void add_ship();

object ship;

void
create_shire_room()
{

    set_short("A pier in the Gulf of Lhun");
    set_long("This pier stretches out into the gulf of Lhun. It wide and " +
        "made of stone. North you see the city of Mithlond. White city " +
        "walls surround it, from which tall towers rise from them. Seagulls " +
        "circle above you. A sign has been posted where the pier meets the " +
        "road.\n");

    add_item(({"seagull","seagulls","cries of seagulls"}),"The cries of "+
      "the seagulls are unrelenting, seeming to take on a "+
      "hauntingly eerie tone. You wish you too could sail over the seas to "+
      "Eressea.\n");
    add_item(({"city","walls","city walls","lighthouse"}),"The city, "+
      "while not so far away is still somewhat blurry as you try to pick "+
      "out features. You wonder if this is an elven magic or if the city "+
      "is just a good distance from here. The lighthouse is the nearest "+
      "feature, and you cannot make out its top.\n");

    add_item(({"pier","road","dock","east road","eastroad"}),"Here you "+
      "are standing on a pier in the Gulf of Lhun, waiting for a ship, "+
      "apparently. The path to the Eastroad is to your east, and the pier "+
      "seems firm beneath you.\n");
    add_item(({"sign"}),"The sign reads: Ship to Harlond.\n");

    add_exit("/d/Shire/common/greyhaven/path8","east",0,1);
    add_prop(ROOM_I_NO_CLEANUP,1);
    
    reset_shire_room();
}

void reset_shire_room()
{
	add_ship();
}

init()
{
    ::init();
    add_action("do_read","read");
}

int
do_read(string str)
{
    if(!str) { NF("Read what?\n"); return 0; }
    if(str != "sign") { NF("Read what?\n"); return 0; }
    write("The sign reads: Ship to Harlond for 6 gold coins.\n");
    return 1;
}

void
add_ship() 
{
    if(!objectp(ship)) 
    {
        ship = clone_object("/d/Shire/common/ship/har_ship");
	ship->move(TO);
        ship->start_ship();
    }
}
