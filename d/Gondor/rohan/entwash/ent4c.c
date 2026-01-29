inherit "/d/Gondor/rohan/entwash/entwash";
#include "/d/Gondor/defs.h"

void reset_room();

object  bug;

void
create_swamp()
{
    set_short("Near to a hut among the Mouths of the Entwash in northern"
      + " Anorien");

    set_extra_long("This place seems to have been hollowed out some."
      + " The ground is well trodden, and rubbish is strewn about in"
      + " a very haphazard way. A dirty looking hut has been erected"
      + " a few yards away from the bank of the nearby stream.");

    add_item(({"rubbish", "bones","bone"}), BSN(
        "Bones and half eaten animals litter the ground here. There is"
      + " a rather unpleasant smell which accompanies the rubbish."));
    add_item(({"hut","huts","dirty looking hut"}), BSN(
        "This hut has been built on a slight rise in the otherwise"
      + " flat terrain which comprises the bulk of these fens. In no"
      + " way is this hut impressive, but it does look as if it may"
      + " have taken a bit of doing to construct, for it seems to be"
      + " built entirely of swamp reeds, and other locally growing"
      + " vegetation. A small opening seems to lead into the hut."));
    add_item(({"opening","small opening"}), BSN(
        "Using this opening is very likely indeed to bring one into"
      + " the hut proper."));
    add_item(({"rise"}), BSN("This rise looks artificially constructed."
      + " and probably serves to save the hut from the flooding which"
      + " occurs regularly in this region."));
    add_item(({"ground","terrain"}), BSN("Pools and weeds rest here as"
      + " everywhere else, yet the ground that does peek through the"
      + " water is well trodden."));
    add_item(({"stream"}), BSN("A swift stream flows by south of here"
      + " and runs in off to the northeast where it disappears into"
      + " the mist."));

    add_exit(ENTWASH_DIR + "ent4a", "northwest");

    reset_room();
}

int
enter_hut(string str)
{
    if(!strlen(str))
    {
        NFN("Enter what?");
        return 0;
    }

    if (str == "hut" || str == "opening")
    {
        set_dircmd("hut");
        TP->move_living("into the hut", ENTWASH_DIR + "hut.c");
        return 1;
    }

    NFN("Enter what?");
    return 0;
}

void
init()
{
    ::init();
    add_action(enter_hut, "enter");
}

void
add_monsters()
{
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
    set_alarm(1.0, 0.0, add_monsters);
}
