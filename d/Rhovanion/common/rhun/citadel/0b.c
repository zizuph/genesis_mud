
inherit "/d/Rhovanion/lib/room";

#include <stdproperties.h>
#include "/d/Rhovanion/farlong.h"

create_room()
{
    set_short("At the door");
    set_long("You stand in the darkened cellar of this citadel.  "+
        "The cobwebs hang heavily here. A low archway leads back to the east, "+
        "and a large iron door stands just to the west.\n");

AE(RHUN+"citadel/0a","east");

    IN;

    add_item("door","The iron door is not yet ready to be opened. Perhaps "+
        "you ought to return at a later date.\n");
    add_item(({"web","webs","cobweb","cobwebs"}),
        "The cobwebs hang thick here, dangling from ceiling and walls and "+
        "constantly in your face.\n");
    add_item(({"wall","walls"}),"The walls here are still made "+
        "from that same black stone as the citadel above.  Cobwebs "+
        "are strewn all about them.\n");
    add_item("floor","The floor here is simple "+
        "dirt, cold and hard-packed.\n");
    add_item(({"arch","east"}),"A low-hanging arch, covered in "+
        "cobwebs, stands just east of here.  Beyond it lies "+
        "another dark part of this cellar.\n");

    reset_euid();
/*
    clone_object(RHUN+"citadel/citadel_door")->move(TO);
*/

}

