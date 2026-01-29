/*
 * Modification History:
 *     October 2010 - Added saving rack functionality (Gorboth)
 *     October 2020 - increased capacity x10 (Arman)
 */

#pragma strict_types

inherit "/std/receptacle.c";
inherit "/d/Genesis/specials/lib/item_recovery_lib"; 

#include <macros.h>
#include <stdproperties.h>
#include "/d/Gondor/defs.h"

void
create_receptacle()
{
    set_short("wooden chest");
    set_pshort("wooden chests");
    set_name("chest");
    set_adj("wooden");
    set_long("The large chest is made from a most peculiar type "
      + "of wood: Its colour is a deep crimson, and the wood is "
      + "almost glowing. Heavy iron fittings run around the body "
      + "of the chest and across the lid. The lid and the four "
      + "corner posts are decorated with carvings.");

    add_item(({"wood", }), 
        "The wood of the chest is of a deep crimson colour, and it "
      + "almost seems to be glowing. Examining the wood closely, you "
      + "notice that it has not been painted. Suddenly you realize "
      + "that it must have been impregnated with blood, thus giving "
      + "it its most peculiar colour.");

    add_item(({"corner posts", "posts", "carvings", }), 
        "The carvings on the four corner posts show elven captives, "
      + "tortured in the dungeons beneath Thangorodrim. Each "
      + "post shows a member of a different elf kindred: "
      + "the two front posts show a Noldo on the right and "
      + "a Sindarin elf on the left, the two back posts show "
      + "one of the Avari on the right, and a Nando of "
      + "Ossiriand on the right.");

    add_item(({"lid", }), 
        "The lid is decorated with purely ornamental carvings. "
      + "It is made of the same wood as the body of the "
      + "chest, and beset with the same heavy iron fittings.");

    set_no_show_composite(1);

    add_prop(OBJ_M_NO_GET, "The chest is fixed to the floor, you cannot take it.\n");
    add_prop(CONT_I_MAX_VOLUME, 500000);
    add_prop(CONT_I_MAX_WEIGHT, 750000);
    add_prop(CONT_I_VOLUME,  4500);
    add_prop(CONT_I_WEIGHT,  5000);
    add_prop(CONT_I_RIGID,      1);
    add_prop(CONT_I_TRANSP,     0);

    if (!IS_CLONE)
    {
        return;
    }
    
    set_enable_logging(0);
    set_enable_recovery(1);
    
    init_database();    
    set_alarm(0.0, 0.0, &recover_objects_from_database());
}

/* 
 * Function name: enter_inv
 * Description:   Called when objects enter this container or when an
 *                object has just changed its weight/volume/light status.
 * Arguments:     ob: The object that just entered this inventory
 *                from: The object from which it came.
 */
public void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);
    
    if (from == this_object())
    {
        return;
    }
    
    add_rack_entry(ob);
}


/* 
 * Function name: leave_inv
 * Description:   Called when objects leave this container or when an
 *                object is about to change its weight/volume/light status.
 * Arguments:     ob: The object that just left this inventory.
 *                to: Where it went.
 */
public void
leave_inv(object ob, object to)
{
    ::leave_inv(ob, to);
    
    if (to == this_object() || !objectp(to))
    {
        return;
    }

    remove_rack_entry(ob);
}
