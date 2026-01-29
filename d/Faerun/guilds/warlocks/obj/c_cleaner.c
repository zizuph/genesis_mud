/*
 *  A corpse cleaner based on the pentacled silver ingot from
 *  Calia. 
 *
 *  Finwe, August 2017
 */
 
#include "/d/Faerun/defs.h"
#include "../guild.h";
#include <stdproperties.h>
#include <macros.h>

inherit "/d/Calia/sea/objects/corpse_cleaner";

void create_object()
{
    set_name("amulet");
    set_adj(({"round", "black" }));
    
    set_short("round black amulet");
    set_long("This is a round black amulet. It feels heavy in your hand " +
        "and thrums with a dark power. The amulet is about the size of " +
        "your hand. A likeness of a human skull is engraved in the center " +
        "of the object.\n");

    add_prop(MAGIC_AM_ID_INFO,({"This powerful amulet has been cursed with " +
        "dark powers and sorcery. It will speed up the decay time of " +
        "corpses, reducing them to nothing in mere seconds. What will be " +
        "left behind are things you can pick over. To invoke this dark " +
        "magic, you need to \"clean corpse\".", 10 }));

    add_prop(OBJ_I_WEIGHT, 80);
    add_prop(OBJ_I_VOLUME, 10);
    add_prop(OBJ_I_VALUE,5000);
    add_prop(OBJ_M_NO_SELL, 1);
}


/*
 * Function:    hook_clean_corpse
 * Description: Displays the messages when someone successfully cleans
 *              the corpse. The corpse is passed in so one can do
 *              queries on it before it gets destroyed.
 */
public void
hook_clean_corpse(object corpse)
{
    write("You hold the amulet over the " + corpse->short() + ". The " +
        "skull glows a blood red and envelopes the corpse with a dark " +
        "light. The light dissapates and the corpse is no more. Some " +
        "items fall to the ground. \n");
    say(QCTNAME(this_player()) + " holds something over the " + 
        corpse->short() + ". A dark light envelopes it. A moment later " +
        "the light is gone and the corpse is gone. Some items fall to " +
        "the ground.\n");
}