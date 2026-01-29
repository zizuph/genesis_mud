/*
    The clerk in the alchemist store of the Colleges of Elemental Magic.
    
    He trains alchemy skill in addition to peddling potions.
    
    Bishop, July 2003.
*/

#pragma strict_types

inherit "/std/creature";
inherit "/d/Calia/std/remember";

#include <stdproperties.h>
#include <ss_types.h>
#include "defs.h"

void
create_creature()
{
    set_name("Nagor");
    add_name("nagor");
    set_adj(({"bushy-eyebrowed","grumpy"}));
    set_race_name("dwarf");
    set_title("the Illuminate of Fire");
    set_long("This grumpy-looking dwarf manages the alchemist store" +
        " in the Marble Tower. In spite of his shoddy appearance, with" +
        " strange stains in his beard, he is known to be very knowledgeable" +
        " in matters of alchemy.\n");

    set_stats(({100,100,100,100,100,100}));
    set_alignment(0);
    set_skill(SS_AWARENESS, 80);
}


