/*
 *  /d/Gondor/clubs/nisse/obj/basketpack.c
 *
 *  A backpack to carry stuff in. It has sell-protection.
 *
 *  Deagol, April 2003
 */

inherit "/d/Gondor/common/guild/obj/backpack";

#include <stdproperties.h>

#include "/d/Gondor/defs.h"
#include "../nisse_defs.h"

void
create_backpack()
{
    ::create_backpack();

    set_name("backpack");
    add_name(({"pack", "basket", "basketpack"}));
    set_pname("backpacks");
    add_pname(({"packs", "baskets", "basketpacks"}));
    set_adj("woven");
    add_adj("hand");
    set_short("hand woven basket pack");
    set_pshort("hand woven basket packs");

    set_backpack_long("This is a hand woven basket pack with a lid you can " +
        "open or close. There are leather straps which fit perfectly over " +
        "your shoulders to hold the pack in place. It has a reinforced " +
        "bottom, wood runners and an oak handle for carrying when the pack " +
        "is not being worn.");

    add_item(({"runners", "wooden runners", "runners"}),
        "The wooden runners are hand carved from oak and run the length of " +
        "the pack to offer support and stability.\n");
    add_item(({"handle", "oak handle"}),
        "The oak handle is attached to the top of the pack lid allowing " +
        "you to carry it until you are ready to wear it.\n");
    add_item(({"lid"}),
        "The lid is constructed in the same way as the pack itself and has " +
        "a wooden handle attached to the center allowing it to be " +
        "carried.\n");
    add_item(({"straps", "leather straps"}),
        "The pair of leather straps fit perfectly over your shoulders.\n");

    add_prop(OBJ_I_VALUE, 490);
    add_prop(CONT_I_HOLDS_COMPONENTS, 1);
}
