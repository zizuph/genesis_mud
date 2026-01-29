/*
    The clerk in the herb store of the Colleges of Elemental Magic.
    
    He trains herbalism skill in addition to peddling herbs.
    
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
    set_name("Belos");
    add_name("belos");
    set_adj(({"ancient", "tall"}));
    set_race_name("human");
    set_title("the Loremaster of Water");
    set_long("This elderly man manages the herb store in the Marble" +
        " Tower. He appears a neat and orderly man, without a" +
        " blemish on his clothes. His knowledge about the finding and" +
        " keeping of herbs is unsurpassed.\n");

    set_stats(({100,100,100,100,100,100}));
    set_alignment(0);
    set_skill(SS_AWARENESS, 80);
}


