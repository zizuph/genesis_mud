inherit "/d/Gondor/minas/houses/citizens/suspect_home";

#include <stdproperties.h>
#include <macros.h>
#include "/d/Gondor/defs.h"

void
create_suspect_room()
{
    add_exit(MINAS_DIR + "houses/citizens/h7r2","south",0,0);
    add_exit(MINAS_DIR + "houses/citizens/h7r3","north",0,0);

    set_door_id("MT_h7_s3crc3");
    set_door_command(({"e","east"}));
    set_door_name(({"door","wooden door"}));
    set_other_room(MINAS_DIR + "s3crc3");
    set_door_desc(BSN(
        "This door seems very dark from afar. However, when you near it " +
        "you notice in a scratched place that it is much lighter " +
        "beneath the surface, and you realize that it simply has not " +
        "been cleaned in a very long time."));

    set_suspect(6);
    set_wealth(1); /* A necessity due to the way the houses were coded */
    set_side("south");
    set_circle("Third Circle");

    set_short("messy room");
    set_long(BSN(
        "This entry room is marked by a great deal of uncleanliness. The " +
        "place is not poor, it is merely ill-maintained. There is a " +
        "small pile of dirty boots and shoes by the door, and a " +
        "discarded cloak is draped over the couch. There is a desk " +
        "here which is covered with all manner of clutter. A shelf " +
        "stands against the west wall."));
    add_item(({"boots","shoes","pile"}), BSN(
        "This footgear is in an ugly heap. Mud is crusted on many of " +
        "the boots, and wet shoes sit here to dry, regardless of " +
        "the effect this has upon the carpet. There is a distinct " +
        "and unpleasant odour arising from the pile."));
    add_item(({"mud","dirt"}), BSN(
        "The dirt and drying mud are encrusted on some of the boots " +
        "here. Apparently the person who last wore them did not bother " +
        "to cleanse them before discarding them."));
    add_item(({"carpet","rug"}), BSN(
        "This carpet is quite dirty. It looks as if it once was of " +
        "good quality, but those days have long since passed. There " +
        "are stains of food and tracked mud all about the carpet."));
    add_item(({"stain","stains"}), BSN(
        "These stains mar almost everything in this room, from the " +
        "carpet to the couch and including the desk."));
    add_item(({"cloak","cape"}), BSN(
        "This dirty cloak was probably once white, but lack of cleaning " +
        "and ill care have stained it to a dull grey colour. It has " +
        "been cast carelessly over the couch."));
    add_item(({"couch","long chair"}), BSN(
        "This couch bears many stains. It has not been cleaned for a " +
        "long time, but it appears very comfortable. There are bits " +
        "of food behind the cushions and various miscellany clutters " +
        "the seats."));
    add_item(({"food","bits","miscellany"}), BSN(
        "The food and other common items which have collected here " +
        "seem typical of the whole house. You cannot see a clean " +
        "item in the place."));
    add_item(({"desk","writing desk"}), BSN(
        "This writing desk is covered with clutter. It seems to " +
        "have withstood the rigours of existence in this house much " +
        "better than most of the furniture here. The wood is free " +
        "from nicks and scratches, though it is stained with what " +
        "appears to be wine."));
    add_item(({"clutter"}), BSN(
        "The clutter on this desk consists mainly of writing implements " +
        "and surfaces, but scattered about without order. Chaos seems " +
        "to be the order here."));
    add_item(({"shelf","bookshelf"}), BSN(
        "This shelf holds many books in no particular order. The thin " +
        "layer of dust which covers each shelf indicates that the " +
        "books do not receive much use."));
    add_item(({"book","books"}), BSN(
        "These books are rather nondescript. They seem to be concerned " +
        "principally with law and civil codes of Gondor and the old " +
        "Kingdom of Arnor. You can see why they have not been much " +
        "read."));

    add_window("The glass is filthy.");
    add_walls("You touch the wall and find that a layer of grime " +
        "comes off on your hand.");
    add_ceiling("The ceiling has a few dusty cobwebs.");
    add_floor("What parts of the floor that aren't covered by the rug " +
        "are covered in dust.");

    add_lamp();
}
