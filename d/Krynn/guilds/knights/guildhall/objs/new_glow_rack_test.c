/*
 * Filename:    new_glow_rack
 * Description: Equipment rack for knights, made to hold lasting items.
 *
 * Creator:     Carnak, 2017-09-21
 */
inherit "/d/Krynn/guilds/knights/guildhall/objs/new_rack";

#include <stdproperties.h>

/*
 * Function:    create_rack
 * Description: Mask this to initialize your own variables
 */
public void
create_rack()
{
    ::create_rack();
    set_recover_rack(1);
} /* create_rack */
