inherit "/std/room";

#include <stdproperties.h>
#include <macros.h>
#include "/d/Terel/common/terel_defs.h"     
#include "volcano.h"
#define TOMBDIR SORGUMDIR + "tomb/"

create_room()
{
    set_short("Graveyard.");
    set_long(BSN(
	 "Plunging hideously downward through an inconcievable abyss " +
	 "in whirling, giddying, sickening tomb-like air you end up " +
         "on a dim plane strewn with singular relics of old grave stones, " +
	 "broken urns and grotesque fragments of monuments.  Strange black " +
	 "gravestones can be seen in the section of the graveyard to " +
	 "the west"
    ));

    add_prop(ROOM_I_INSIDE, 0);
     
    add_item(({"grave", "graves", "gravestones", "relic", "relics"}), BSN(
       "The grotesque gravestones may have once been majestic but now " +
       "are crumbling travesties of their original forms."
    ));

    add_item(({"urn", "urns", "broken urn", "broken urns"}), BSN(
       "The large urns lie about here all dented and broken."
    ));								
    
    add_exit(TOMBDIR + "cottage_graveyard", "west", 0);
}

