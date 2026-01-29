inherit "/d/Gondor/common/room";
#include "/sys/stdproperties.h"
#include "/d/Gondor/defs.h"


void
create_room()
{
    set_short("the bedroom");
    set_long(BSN("You have entered the bedroom of the house. "
        + "It is a small chamber with few furnitures. You can see a bed, "
        + "a nightstand and a closet."));
    add_item(({"bed"}),BSN("The bed is large enough for two people and "
        + "is currently empty."));
    add_item(({"nightstand"}),BSN("The nightstand is made in some kind "
        + "of black wood."));
    add_item(({"closet"}),BSN("The closet is made in some kind of "
        + "polished wood. In the closet you see some farmers clothes."));
    add_item(({"cloth","clothes","farmers"}),BSN("The clothes are of poor "
        + "quality not worth taking."));
add_exit(EDORAS_DIR + "houses/house1r1","south",0);

    add_prop(ROOM_I_INSIDE,1);

}
