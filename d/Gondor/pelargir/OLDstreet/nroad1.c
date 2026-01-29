inherit "/d/Gondor/common/room";
inherit "/d/Gondor/pelargir/city_items.c";

#include "/sys/stdproperties.h"

#include "/d/Gondor/defs.h"

object  citizen;

void
reset_room()
{
    if (objectp(citizen))
        return;

    citizen = clone_object(PELAR_DIR + "npc/citizen");
    citizen->arm_me();
    citizen->move_living("down", TO);
}

void
create_room()
{
    set_short("on an east-west road");
    set_long(BSN("You are travelling one of the northern east-west "+
       "streets of Pelargir. A few townspeople scurry about, but most "+
       "don't pay any attention to you. Various buildings line the "+
       "street, though most are simply houses of the commonfolk. "+
       "In the distance to the east you see the lighthouse, to the west "+
       "is a bridge over the Sirith River which runs through the city, "+
       "and to the north behind the buildings, looms the city wall."));
    add_cobble();
    add_northside();
    add_lighthouse();
    add_item("townspeople",BSN("Most of them won't even "+
       "look in your direction. Not too trusting of "+
       "outsiders you guess."));
    add_exit(PELAR_DIR + "street/ngbcross","west",0);
    add_exit(PELAR_DIR + "street/nroad2","east",0);

    reset_room();
}

