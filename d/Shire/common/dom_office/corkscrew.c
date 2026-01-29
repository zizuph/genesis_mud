/*
 * Corkscrew
 * Knick knack for domain office
 * Thanks to Abeni for the idea.
 * Finwe, March 2004
 */

#include "/d/Shire/sys/defs.h" 
#include <macros.h>
#include <stdproperties.h>
#include <ss_types.h>

inherit "/std/object";

void
create_object()
{
    seteuid(getuid());

    set_name("corkscrew");
    set_pname("corkscrews");
    set_adj("ornate");
    set_short("ornate corkscrew");
    set_long("This is an ornate corkscrew. It is a device used to remove " +
        "corks from bottles. It consists of a pointed metal spiral attached " +
        "to an ornate handle of a chubby hobbit.\n");
    add_item(({"spiral", "pointed metal spiral", "metal spiral"}),
        "This is a thin piece of metal that spirals downward. On the " +
        "end is a sharp point that is twisted into a cork. The metal is " +
        "smooth and doesn't look dangerous.\n");
    add_item(({"handle", "corkscrew handle"}),
        "The handle has been made from metal. It fits in the palm of " +
        "your hand comfortably and is the shape of a chubby hobbit. In " +
        "small letters you read: Drink to your health, From Hobbiton.\n");
    add_item(({"hobbit", "chubby man"}),
        "The hobbit has a big, broad forehead and chubby rosy cheeks. He " +
        "is wearing a loose fitting shirt and pants, and is sitting down with " +
        "crossed legs. He looks very happy, grinning from ear to ear.\n");

    add_prop(OBJ_I_WEIGHT, 1);
    add_prop(OBJ_I_VOLUME, 3);
    add_prop(OBJ_I_VALUE, 100);
}
