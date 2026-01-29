inherit "/d/Gondor/common/room";

#include <stdproperties.h>

#include "/d/Gondor/defs.h"

object  hermit,
        bug;

void reset_room();

void
create_room()
{
    set_short("a small dirty hut in the fens of the Entwash");
    set_long(BSN("The inside of this hut is a very pathetic sight."
      + " A makeshift mat comprised of dried cattails rests in one"
      + " corner opposite to an iron-oil lamp which is embedded in"
      + " the muddy floor. The walls and roof of this hut do very"
           + " little to provide adequate shelter."));

    add_item(({"hut","wall","walls","roof"}), BSN(
        "The walls of this hut are constructed from dried and binded"
      + " cattail reeds which have been strung to a number of branches"
      + " protruding from the muddy ground. Above, the roof of this"
      + " place is loosely attached to the top of the walls by patches"
      + " of dried mud. The roof seems to be constructed of willow"
      + " branches."));
    add_item(({"mat","bed","mats","beds"}), BSN(
        "This is certainly one of the least comfortable beds in the"
      + " entire region. No pillow or headrest is visible, and the"
      + " ground does not exactly look soft or dry in any way."));
    add_item(({"lamp","iron lamp","iron-oil lamp"}), BSN(
        "This lamp seems to act as a source of both light and heat for"
      + " this miserable home. It is currently lit, and looks to be"
      + " filled with some murkey oils."));
    add_item(({"oil","oils"}), BSN("The oil in the lamp looks very"
      + " much like some of the slime which covers the pools all"
      + " across the fens. Perhaps the owner has skimmed the oil for"
      + " his own purposes here."));
    add_item(({"ground","floor","mud"}), BSN(
        "The floor of this hut is nothing more than packed and"
      + " trampled earth. Nothing in this place looks clean or"
      + " cheerful. A dead fish lays heaped on the floor."));
    add_item(({"fish","fishes"}), BSN(
        "This fish looks like a trout!"));
    add_item(({"trout","trouts"}), BSN(
        "Ugh! What a disgusting sight!"));

    add_prop(ROOM_I_INSIDE, 1);
    add_prop(ROOM_I_LIGHT, 1);

    add_exit(ENTWASH_DIR + "ent4c", "out");

    reset_room();
}

void
clone_monsters()
{
    if (!objectp(hermit))
    {
        hermit = clone_object(ENTWASH_DIR + "npc/hermit");
        hermit->arm_me();
        hermit->move_living("from somewhere", TO);
    }

    if (!objectp(bug))
    {
        bug = clone_object(NPC_DIR + "mosquito");
        bug->set_poison_file(ENTWASH_DIR + "obj/mosquito_sting");
        bug->move_living("from somewhere", TO);
    }
}

void
reset_room()
{
    set_alarm(1.0, 0.0, clone_monsters);
}
