
/* File name: store_base.c
 * 
 * Blizzard, 12.11.2003.
 */

inherit "/std/room";
inherit "/lib/store_support";

#include "/sys/stdproperties.h"
#include "/d/Krynn/qualinesti/local.h"
#include "../guild.h"

#define  TORCH      "qualinesti_oil_and_flasks"

public void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);
    store_update(ob);
}

public void
reset_room()
{
    reset_store();
}

public void
create_room()
{
    set_short("inside the store tent");
    set_long("This is the store room for the shop.\n");

    add_exit(GUILD_ROOM + "general_store", "out");

    INSIDE;  /* This is an inside room */

    set_max_values(20, 8);
    set_default_stock( ({ (OBJ + "quiver.c"), 2,
                          (WEP + "elven_arrow"), 2,
                          (WEP + "elven_arrow"), 2, 
                          (WEP + "elven_bow"), 3,
                          (ARM + "cloak"), 2
                       }) );  
    reset_room();
    
}

