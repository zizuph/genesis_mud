#include "/d/Kalad/defs.h"
#include "/d/Kalad/common/raum/std/jewelry.h"

inherit RAUM(std/jewelry);

/*
 * /d/Kalad/common/guilds/khiraa/temple/obj/demon_beads.
 * Purpose    : This is a magical ward used in rites of the Khiraa
 * Located    : Can be taken from sacrifice room.
 * Created By : Sarr  24.Apr.97
 * Modified By: 
 */



void
create_jewelry()
{
    set_name("fingers");
    add_name("_khiraa_chain2_");
    add_name("chain");
    add_adj("ghastly");
    add_adj("dismembered");
    set_short("chain of ghastly dismembered fingers");
    set_ok_jewelry_slots(({ANSALON_JEWELRY_NECK}));
    set_long("A silver chain that is strung through several dismembered "+
    "fingers. The blood is dried, and the fingers are old and shrivling, "+
    "but magical protection keeps them from rotting away completely. "+
    "This piece of magic is used in very powerful rites of the Khiraa.\n");

    set_jewelry_value(0);
}
