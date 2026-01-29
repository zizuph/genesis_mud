inherit "/d/Gondor/common/room";

#include <stdproperties.h>

#include "/d/Gondor/defs.h"

void
create_room()
{
    set_short("the entry of the Dragon's Claw");
    set_long(BSN("This is the common room of the Dragon's Claw Inn in "
      + "Pelargir. It seems that thieves have raided the inn "
      + "storeroom so no drinks or meals are being served today. In "
      + "fact, the innkeeper is so upset he is not even around for "
      + "comment. The inn itself seems fairly comfortable. There are "
      + "quite a few dark stains on the floor and stairs, but the "
      + "tables are clean."));
    add_prop(ROOM_I_INSIDE,1);
    add_item("stairs",BSN("The stairs look a little bit worn and "+
       "splintery, though you would not want to tread them barefoot "+
       "they look sturdy enough."));
    add_item("tables",BSN("The tables are the cleanest part of the "+
       "entire room. You might hope that they are clean because someone "+
       "cleans them regularly, though it is probably because "+
       "no one has eaten on them for awhile."));
    add_item(({"dark stains","floor","stains"}),BSN("The stains on the "+
       "wood floor look to be mostly ale, though you might "+
       "guess that there is "+
       "vomit here and there also. Other than that it looks nice."));
    add_exit(PELAR_DIR + "homes/inn/innhall1","up",0);
    add_exit(PELAR_DIR + "streets/plaza","east",0);
}

