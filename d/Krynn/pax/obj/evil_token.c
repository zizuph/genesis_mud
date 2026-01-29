/*
 *    This is the token Verminaard gives to the players
 *    attempting to try the evil version of the disks of
 *    Mishakal quest.
 *
 *    Jeremiah, March 96.
 */

inherit "std/object";

#include "/d/Krynn/common/defs.h"
#include "/d/Krynn/pax/local.h"

void
create_object()
{
    set_name(({"token", "_krynn_evil_disks_token_"}));
    set_name(({"medallion", "token", "_krynn_evil_disks_token_"}));
    set_long("This is a medallion of blackened steel. A dragon "
      + "with its wings spread wide is embossed into the metal. "
      + "This medallion might have been worn around the neck, "
      + "but the chain is missing.\n");
    set_adj("blackened");
    add_adj("steel");

    add_prop(OBJ_I_VALUE, 50);
    add_prop(OBJ_I_WEIGHT, 200);
    add_prop(OBJ_I_VOLUME, 200);
}
