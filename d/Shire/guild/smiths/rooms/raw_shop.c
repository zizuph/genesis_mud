/*
 *    The raw material shop room for the smiths guild
 *    items needed for forging is bought here
 *    Made 1996 by Morinir for the Shire.
 *
 *    History:
 *    Removed shop abilities. Tobin now sells wooden poles 
 *    and limited leathers.
 *    -- Finwe, June 2001
 */

#pragma save_binary;

inherit "/d/Shire/room";

#include "smiths.h"
#include "/d/Shire/common/defs.h"
#include "/sys/macros.h"
#include "/sys/stdproperties.h"
#include <cmdparse.h>

#define SELLER         (SMITHSDIR_NPC+"seller")
#define SELLERSAY(s)   seller->command("say "+s)

void reset_room(); 

object seller;

void
create_room() {
    set_short("Raw material workshop in Smiths Guild");
    set_long("This room is used by Tobin Ironshoe, a known " +
        "member of the guild. Tobin has had this workshop for a " +
        "number of years. The only thing that doesn't quite fit " +
        "into this room is a large box with broken items placed " +
        "in a corner of the room. A sign on the wall has " +
        "instructions that Tobin expects people to read.\n");
   add_item(({"box","big box","scrap box"}),
        "This box is filled with broken rusted items to be used " +
        "as raw materials later.\n");
   add_item("sign", "Maybe you should read it.\n");
   add_cmd_item("sign", "read", "@@read_sign@@");


    add_exit(SMITHSDIR_ROOMS+"master_r","northeast",0);

    add_prop(ROOM_I_INSIDE,1);
// safe rooms
    add_prop(ROOM_I_NO_ATTACK, 1);
    add_prop(OBJ_M_NO_ATTACK,1);
    add_prop(ROOM_I_NO_MAGIC_ATTACK, 1); 


    reset_room();
}

init() {
    ::init();
}

void
reset_room()
{
    if (!objectp(seller))
    {
        seteuid(getuid(TO));

        seller = clone_object(SELLER);
        seller->move_living("X", TO);
    }
    else if (ENV(seller) != TO)
    {
        seller->move_living("X", TO);
    }
}

string
read_sign()
{
    return "\n      On the sign is painted the following:\n\n"+
            "       Tobin has available to him a limited number of\n"+
            "       leathers and wooden poles available for use in\n"+
            "       forging weapons and armours. To buy them, you\n"+
            "       <pay for leather> or <pay for wooden pole>.\n\n";
}
