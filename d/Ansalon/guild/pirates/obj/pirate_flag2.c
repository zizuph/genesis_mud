inherit "/d/Krynn/std/boats/sailing_ensign";

#include "/d/Krynn/common/defs.h"

// ensign_short, ensign_long1, ensign_long2, ensign_names, allowed_guild

#define ENSIGN_DETAILS   "Blood Flag", \
     "Flying from the main mast is a deep red ensign - the " + \
     "Bloody Red, a flag raised when no mercy would be " + \
     "shown and no life spared! It is being flown by Captain ", \
     "Neatly folded is a deep red ensign - the Bloody Red, " + \
     "a flag raised by pirates when no mercy would be shown! ", \
     ({ "blood flag", "ensign", "bloody red", "main mast" }), \
     "Pirate of the Bloodsea"

mixed * ensign_details = ({ ENSIGN_DETAILS });

void
create_object()
{
    add_name(({"flag","ensign","_krynn_sailing_ensign"}));
    set_ensign_details(ensign_details);
    create_the_ensign();
}
