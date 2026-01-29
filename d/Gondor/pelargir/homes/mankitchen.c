inherit "/d/Gondor/common/room";

#include <stdproperties.h>

#include "/d/Gondor/defs.h"

void
create_room()
{
    set_short("in the mansion's kitchen");
    set_long(BSN("This is the spacious kitchen of the mansion. "+
       "There is a fireplace here used strictly for heating water "+
       "and a wood stove in the corner near the pantry. "+
       "Everywhere you look you can see pots, pans, and kettles "+
       "hung on the wall or balanced on various cabinets."));
    add_prop(ROOM_I_INSIDE,1);
    add_item(({"cabinet", "cabinets"}), "The cabinets look well " + 
        "used and old. They are stuck shut.\n");
    add_item("fireplace",BSN("The fireplace looks well used, "+
       "though there currently is not any wood in it. It is possible "+
       "to see various food stains from spilled kettles all around it."));
    add_item(({"food stains","stains"}),BSN("These stains range from "+
       "pea soup, to egg, to burnt coney grease. Not only are they "+
       "by the fireplace, but also on the cabinets, floor, and most "+
       "of the kettles and pots."));
    add_item(({"pots","pans","kettles"}),BSN(
       "These mostly need to be cleaned, it probably would not be "+
       "sanitary to carry one around. Interesting food stains though."));
    add_item(({"wood stove","stove"}), "OUCH!! that sure is hot!\n");
    add_cmd_item(({"cabinet", "cabinets"}), "open", "The cabinets " + 
        "are stuck shut.\n");

    add_exit(PELAR_DIR +"homes/mandinhall","south",0);
}

