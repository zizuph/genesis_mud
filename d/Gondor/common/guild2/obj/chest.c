#pragma strict_types

inherit "/std/receptacle.c";

#include <stdproperties.h>
#include "/d/Gondor/defs.h"

void
create_receptacle()
{
    set_short("wooden chest");
    set_pshort("wooden chests");
    set_name("chest");
    set_adj("wooden");
    set_long(BSN("The large chest is made from a most peculiar type "
      + "of wood: Its colour is a deep crimson, and the wood is "
      + "almost glowing. Heavy iron fittings run around the body "
      + "of the chest and across the lid. The lid and the four "
      + "corner posts are decorated with carvings."));

    add_item(({"wood", }), BSN(
        "The wood of the chest is of a deep crimson colour, and it "
      + "almost seems to be glowing. Examining the wood closely, you "
      + "notice that it has not been painted. Suddenly you realize "
      + "that it must have been impregnated with blood, thus giving "
      + "it its most peculiar colour."));

    add_item(({"corner posts", "posts", "carvings", }), BSN(
        "The carvings on the four corner posts show elven captives, "
      + "tortured in the dungeons beneath Thangorodrim. Each "
      + "post shows a member of a different elf kindred: "
      + "the two front posts show a Noldo on the right and "
      + "a Sindarin elf on the left, the two back posts show "
      + "one of the Avari on the right, and a Nando of "
      + "Ossiriand on the right."));

    add_item(({"lid", }), BSN(
        "The lid is decorated with purely ornamental carvings. "
      + "It is made of the same wood as the body of the "
      + "chest, and beset with the same heavy iron fittings."));

    set_no_show_composite(1);

    add_prop(OBJ_M_NO_GET, "The chest is fixed to the floor, you cannot take it.\n");
    add_prop(CONT_I_MAX_VOLUME, 50000);
    add_prop(CONT_I_MAX_WEIGHT, 75000);
    add_prop(CONT_I_VOLUME,  4500);
    add_prop(CONT_I_WEIGHT,  5000);
    add_prop(CONT_I_RIGID,      1);
    add_prop(CONT_I_TRANSP,     0);

}
