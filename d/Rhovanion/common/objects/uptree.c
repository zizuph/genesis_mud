inherit "/d/Rhovanion/lib/room";

#include "/d/Rhovanion/defs.h"

void
reset_room()
{}

void
create_room()
{
    set_short("Up a tree");
    set_long("You are in the top of a large tree.  You see the ground " +
        "far below you through branches which spread out here to form a " +
        "platform which you can easily stand on, but the leaves block your " +
        "view of the area surrounding the tree.  You can go back down " +
        "from here.  There doesn't seem to be much to see from here.\n");

    add_item(({ "branch", "branches" }),
        "These large branches easily support your weight.  They are " +
        "covered with large green leaves which block anything outside of " +
        "the tree from your view.\n");

    add_item(({ "leaves", "green leaves", "leaf", "green leaf" }),
        "These beautiful leaves block your view, it seems like they do it " +
        "almost intentionally.\n");

    add_item(({ "area", "surrounding area" }),
        "You can't see much of the surrounding area because of all the " +
        "leaves in your way.\n");

     reset_room();
}
