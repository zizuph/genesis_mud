inherit "/d/Krynn/std/boats/sailing_ensign";

#include "/d/Krynn/common/defs.h"


// ensign_short, ensign_long1, ensign_long2, ensign_names, allowed_guild

#define ENSIGN_DETAILS   "yellow maritime flag", \
     "Flying from the main mast is a simple yellow maritime flag " + \
     "of convenience, commonly flown by merchants and unaligned " + \
     "sailors of the High Seas. It is being flown by Captain ", \
     "Neatly folded is a simple yellow maritime flag " + \
     "of convenience, commonly flown by merchants and unaligned " + \
     "sailors of the High Seas. ", \
     ({ "yellow flag", "ensign", "maritime flag", "main mast" }), \
     " "

mixed * ensign_details = ({ ENSIGN_DETAILS });

void
create_object()
{
    add_name(({"flag","ensign","_krynn_sailing_ensign"}));
    set_ensign_details(ensign_details);
    create_the_ensign();
}
