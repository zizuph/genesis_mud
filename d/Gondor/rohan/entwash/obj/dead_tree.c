inherit "/std/object";

#include <macros.h>
#include <stdproperties.h>
#include "/d/Gondor/defs.h"

string  tree = ONE_OF_LIST( ({"willow","alder","oak"}) );

void
create_object()
{
    set_name("entwash_dead_tree");
    add_name(({"tree",tree+" tree",tree}));
    set_short("ash-grey " + tree);
    set_pshort("ash-grey " + tree +"s");
    set_long(BSN("Though still standing, and without any visible signs"
               + " of decay, this "+tree+" is clearly dead. It is"
               + " completely devoid of any leaves, and its vine tangled"
               + " branches look brittle and stiff. The bark of the tree"
               + " has taken on a pallid grey colour, as if something has"
               + " sapped it of the pigment which gave it life."));

    add_item(({"branch","branches"}), BSN(
        "The branches look very dry and brittle. They spread to the sky"
      + " as a silent formation of fingers."));
    add_item(({"bark"}), BSN("The bark of this " +tree+ " is grey and ashen."
      + " Rot and holes riddle the tree."));
    add_item(({"hole","holes","rot"}), BSN(
        "These holes do not seem natural. It looks as if some parasite has"
      + " bored into the base."));
    add_prop(OBJ_M_NO_GET, "Don't be absurd!\n");
    add_prop(OBJ_I_WEIGHT, 800000);
    add_prop(OBJ_I_VOLUME, 200000);
}

int
smooch_tree(string str)
{
    if (!str)
    {
        NFN("Well, what do you want to smooch?");
        return 0;
    }

    if (str != "tree" && str != tree)
    {
        NFN("Thats just not worth smooching.");
        return 0;
    }

    write(BSN("You approach the tree, bashfully at first, and quite"
      + " suddenly smooch it deftly upon the bark. Ack! You seem to"
      + " have gotten bits of wood and dirt all over your lips!"));
    say(BSN(QCTNAME(TP) + " approaches the tree cautiously, and moves"
      + " in suddenly, delivering a swift smooch to its bark!"));
    TP->command("ack");
    TP->command("spit");

    return 1;
}

int
climb_tree(string str)
{
    if (!str)
    {
        NF("Climb what?\n");
        return 0;
    }

    if (str != "tree" && str != tree)
    {
        NF("Trying to climb that is not useful.\n");
        return 0;
    }

    write(BSN("Most of the branches are out of reach, and those that"
      + " are not do not look capable of supporting you."));
    return 1;
}

void
init()
{
    ::init();
    add_action(climb_tree, "climb");
    add_action(smooch_tree, "smooch");
}
