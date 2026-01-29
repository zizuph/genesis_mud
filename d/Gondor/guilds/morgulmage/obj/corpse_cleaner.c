/*
 *  A corpse cleaner based on the pentacled silver ingot from
 *  Calia. Added as replacement for removing the Orekir spell.
 *
 *  Eowul, Oktober 2009
 */
 
#include "../morgulmage.h"
#include <stdproperties.h>
#include <macros.h>

inherit "/d/Calia/sea/objects/corpse_cleaner";

void create_object()
{
    set_name("talisman");
    set_adj(({ "small", "palm-sized" }));
    
    set_short("small palm-sized talisman");
    set_long("A small, palm-sized talisman in the shape of an Eye, wreathed "
        + "in flame. Strange shadowy powers radiate from the very center of "
        + "the Eye urging you to pass it over nearby corpses.\n");

    add_prop(MAGIC_AM_ID_INFO,({ "This talisman has been infused with the "
        + "power of the Dark Lord. Passing it over a nearby corpse will "
        + "cause it to decay into nothingness, leaving but the remains for "
        + "use by His servants. To use the talisman, you need only <clean "
        + "corpse>.\n", 10 }));

    add_prop(OBJ_I_WEIGHT, 80);
    add_prop(OBJ_I_VOLUME, 10);
    add_prop(OBJ_I_VALUE, 4000);
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
    write("You pass the talisman over the " + corpse->short() 
        + " causing it to decay into nothingness, save a few paltry "
        + "remains.\n");
    say(QCTNAME(this_player()) + " waves a visage of the Eye over the " 
        + corpse->short() + ". Nothing remains save a few pieces.\n");
}

string
query_recover()
{
    return MASTER; 
}
