inherit "/d/Gondor/common/room";

#include "/sys/stdproperties.h"

#include "/d/Gondor/defs.h"
#include "/d/Gondor/pelargir/citdefs.h"

string read_sign();

void
create_room()
{
    set_short("on an east-west road");
    set_long(BSN("This is a nice stretch of city road. "+
       "The buildings here are kept in decent repair, and you do not see a "+
       "lot of riff-raff about. The lighthouse looms tall in the "+
       "distance and you can hear the Sirith River coursing along "+
       "its narrow channel through the city to the west and south. "+
       "There is a finely carved wooden sign on the wall of the old "+
       "building to the north."));
    add_item(({"sirith", "river","sirith river"}),BSN("The Sirith River "+
       "is constricted by the stone levee and city stonework, "+
       "creating a fast current as the Sirith courses past."));
    add_item("lighthouse",BSN("The lighthouse stands tall in "+
       "the east."));
    add_item(({"sign", "wooden sign", "carved sign", "carved wooden sign"}),
        read_sign);
    add_cmd_item(({"sign", "wooden sign", "carved sign", "carved wooden sign"}),
        "read", read_sign);
    COBBLE;
    add_exit(PELAR_DIR + "street/nroad3","east",0);
    add_exit(PELAR_DIR + "street/nroad1","west",0);
    clone_object(STORYT_DIR + "obj/foyer_door_out")->move(TO);
}

string
read_sign()
{
    write(read_file(STORYT_DIR + "misc/sign.txt"));
    return "";
}

