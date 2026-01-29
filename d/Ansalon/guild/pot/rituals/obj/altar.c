/* Stralle @ Genesis 040226
 */

#pragma strict_types

inherit "/std/container";

#include <stdproperties.h>
#include <composite.h>

void
create_container()
{
    set_name("altar");
    set_adj(({"black", "stone"}));
    set_long("A black stone altar rests at the feet of a statue. " +
        "Consisting of a pillar with intricate patterns upon which " +
        "a circular stone slab rests. Wear and tear have " +
        "made the surface irregular, which has dried traces of " +
        "heavy use. ");
    
    add_item(({"pillar"}), "It raises from the floor like a dragons " +
        "neck. Intricate patterns and runes adorns it where upon it, " +
        "rests a circular stone slab.\n");
    add_item(({"slab", "stone slab", "circular slab", "circular stone slab",
        "surface"}),
        "It rests upon the pillar and is circular in shape. At regular " +
        "intervals along it, a dragon head is set at its edge, overlooking " +
        "the entire abbey. Dried blood and other signs upon it tells " +
        "of heavy use.\n");
    add_item(({"traces", "dried traces"}), "Dried blood and other " +
        "marks tells of heavy use.\n");
    add_item(({"runes", "patterns", "intricate patterns"}), "@@exa_runes");
    
    add_prop(OBJ_I_NO_GET, 1);
    add_prop(OBJ_I_WEIGHT, 200000);
    add_prop(OBJ_I_VOLUME, 10000);
    add_prop(CONT_I_ATTACH, 1);
    add_prop(CONT_I_MAX_VOLUME, 50000);
    add_prop(CONT_I_MAX_WEIGHT, 50000);
    set_no_show_composite(1);
}

void
describe_contents(object for_obj, object *obarr)
{
    for_obj->catch_tell(show_sublocs(for_obj));
    
    if (sizeof(obarr) > 0)
    {
        for_obj->catch_tell("Upon the altar rests " + COMPOSITE_DEAD(obarr) +
            ".\n");
    }
    else
    {
        for_obj->catch_tell("\n");
    }
}
