inherit "/d/Shire/std/room";
#include "/d/Shire/common/defs.h"

void
create_shire_room()
{
    set_short("A path along the Gulf of Lhun");
    set_long("This path juts southwest, following the shoreline. The piers " +
        "look well used. Ships from all over land here dropping off and " +
        "picking up passengers. North is the city of Mithlond.\n");

    add_exit("/d/Shire/common/greyhaven/path7","northeast",0,1);
    add_exit("/d/Shire/common/greyhaven/path9","southwest",0,1);
    add_exit("/d/Shire/common/greyhaven/pier8","west",0,1);

   
}
