inherit "/d/Gondor/minas/houses/citizens/house.c";

#include <stdproperties.h>
#include <macros.h>
#include "/d/Gondor/defs.h"

void
create_room()
{
    set_short("small kitchen");
    set_long(BSN(
        "This small room is the kitchen of this house. There are " +
        "cupboards on the walls and a table in the middle of the " +
        "room. A basin sits in one corner and a stove in another."));
    add_item(({"cupboards","cupboard","cabinets","cabinet"}), BSN(
        "These cupboards are rough and made of unfinished wood. " +
        "Looking inside them, you see that some contain pots, " +
        "pans, and utensils, while others contain foodstuffs."));
    add_item(({"pots","pans","utensils"}), BSN(
        "The pots, pans and utensils which are inside the cupboards " +
        "are of low quality. They are battered and bent, and in " +
        "some cases they have been but poorly cleaned."));
    add_item(({"food","foodstuffs"}), BSN(
        "These foodstuffs include flour, a small portion of salt, " +
        "dried fruits, nuts, several loaves of hard bread, and a " +
        "very little dried and salted meat."));
    add_item(({"table","wooden table","worn table"}), BSN(
        "This worn wooden table is used as a preparation surface " +
        "for food. The table has been scarred by the constant " +
        "actions of knives upon its surface. It is a well crafted " +
        "table, however."));
    add_item(({"basin","waterbasin"}), BSN(
        "This basin holds water collected from the common well. " +
        "It is dented in many places and looks as if it is about " +
        "to spring a leak."));
    add_item(({"water"}), BSN(
        "The water in the basin is cool despite its proximity to " +
        "the stove."));
    add_item(({"stove"}), BSN(
        "This stove burns wood and coal, and serves to cook the " +
        "food that this family eats. It is a cylindrical stove with " +
        "a flat top to hold pots and pans. There is a stack of wood " +
        "sitting next to the stove."));
    add_item(({"wood","firewood"}), BSN(
        "This wood is stacked neatly, ready for the stove. You " +
        "notice a small spider crawling on one of the pieces " +
        "of wood."));
    add_item(({"spider","arachnid"}), BSN(
        "It's a small brown spider. Seems harmless enough."));
    add_item(({"moisture","condensation"}), BSN(
        "This condensation is apparently leftover from some boiling " +
        "water in the recent past, for it has not yet completely " +
        "evaporated."));

    add_prop(ROOM_I_INSIDE, 1);

    set_wealth(0);
    set_side("south");
    set_circle("Second Circle");

    add_window("There is some moisture on the inside of the window.");
    add_walls("Cupboards line the walls.");
    add_ceiling("The tops of the cupboards meet the ceiling.");
    add_floor("A waterbasin stands upon the floor.");

    add_exit(MINAS_DIR + "houses/citizens/h4r1salleycrc2","north",0,0);
}
