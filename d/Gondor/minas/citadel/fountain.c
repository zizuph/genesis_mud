/*
 *  /d/Gondor/minas/citadel/fountain.c
 *
 *  Court of the Fountain
 *
 *  Last modified by Alto, 06 April 2001
 *
 */

#pragma strict_types

inherit "/d/Gondor/std/room.c";
inherit "/d/Gondor/common/lib/drink_water.c";


#include <macros.h>
#include <stdproperties.h>
#include "/d/Gondor/defs.h"
#include "/d/Gondor/std/tell.c"

#define INNER_MINAS "/d/Gondor/minas"

static object *Guard = allocate(2);

object tree, door;

public void
create_gondor()
{
    set_short("The Court of the Fountain");
    set_long("This is a large white-paved courtyard. To the west "
        + "stand the doors of a majestic white tower. In the center "
        + "of the court there is a wide sward of bright green grass "
        + "surrounding a sweet fountain. Despite the peace and "
        + "grandeur of the courtyard, there is something mournful about "
        + "this place. The impression of ancient sadness is underscored "
        + "by the dead tree drooping over the pool.\n");

    add_item(({"courtyard", "plaza"}), "This place is grand, and yet "
        + "sad in a distant way. Despite the deep feeling of loss "
        + "emanating from the dead tree, there is also an "
        + "elusive wisp of hope.\n");
    add_item(({"fountain", "sweet fountain"}), "From somewhere deep "
        + "within the roots of Mount Mindolluin, ice-clear water "
        + "finds its way to this beautiful fountain. Water streams "
        + "into the air from a tall statue slightly west of the center "
        + "of the large circular pool. In its center stands a dead "
        + "tree.\n");
    add_item(({"doors", "timbers", "plates"}), "Two massive doors made of wood "
        + "banded in great plates of iron. These doors have never been "
        + "broken, and gazing upon their might you wonder at the "
        + "kind of strength that would be required to even scratch "
        + "the huge timbers.\n");
    add_item(({"tower", "tower of ecthelion", "white tower"}), "The White "
        + "Tower of Ecthelion spikes fifty fathoms high into the sky at the "
        + "west end of the plaza. It looks as though it is made "
        + "of pearl and silver, and its pinnacle glitters as if "
        + "wrought of crystals.\n");
    add_item(({"pinnacle"}), "With a sense of vertigo, your eyes rise "
        + "to the heights of the White Tower. Just before you look "
        + "away, you think you notice a strange flash of light from "
        + "inside its highest east-facing window.\n");
    add_item(({"window"}), "There are many windows about the courtyard. "
        + "The only one that catches your interest is the highest window "
        + "in the Tower of Ecthelion.\n");
    add_item(({"highest window"}), "There it is again, a strange flash "
        + "of bright light. Who knows what secrets are to be found in "
        + "the ancient rooms above?\n");
    add_item(({"ground", "pavement"}), "Large octagonal paving-stones "
        + "of argent sheetrock surround the lawn and fountain.\n");
    add_item(({"paving-stones", "stones"}), "There certainly are "
        + "many of them. Counting them all would be thirsty work. Good thing "
        + "there is a fountain here.\n");
    add_item(({"grass", "green grass", "sward", "lawn"}), "A well-"
        + "manicured lawn of the greenest grass. The sward is "
        + "shaped like a star with seven rays and a sweet fountain "
        + "plays in its center.\n");
    add_item(({"pool", "large pool", "circular pool"}), "The water is "
        + "very cold and clean to the touch. The pool is continually "
        + "filled by the water streaming from the fountain at its "
        + "west end. Some of the water drips sadly into the pool "
        + "from the barren "
        + "and broken branches of the dead tree in its center.\n");
    add_item(({"mountain", "mount mindolluin"}), "Rising behind the "
        + "tower is the dark mass of Mount Mindolluin. The deep "
        + "purple shadows of its high glens and its tall face "
        + "are so large that you cannot take it all in at a single "
        + "glance.\n");
    add_item(({"glens", "face"}), "The mountain towers so huge about "
        + "the courtyard that you get dizzy looking up at it.\n");
    add_item(({"water"}), "Do you mean the water spraying from the "
        + "statue or the water resting in the pool?\n");
    add_item(({"water spraying from the statue", "streams", "wheel",
        "ships-wheel"}),
        "From several small jets within the spokes of the great "
        + "ships-wheel, crystal clear water arcs over the pool in thin "
        + "glistening streams.\n");
    add_item(({"jets"}), "You would need to climb into the pool to "
        + "inspect them closely. That would be rather rude, don't "
        + "you think?\n");
    add_item(({"water in the pool", "water resting in the pool", "drops"}), 
        "Long ago, this must have fed the tree in the center of the "
        + "pool. For many long years, however, the dead tree "
        + "has lifted no water up from its roots into its branches.\n");
    add_item(({"statue", "tall statue"}), "This statue must have been "
        + "created long ago. The craft of its making is lost in the "
        + "deeps of time. It depicts a tall mariner behind a giant "
        + "ships-wheel. The statue faces east, and for some reason "
        + "it would appear unseemly were it to face any other "
        + "direction. Though weathered by the ages, the mariner "
        + "retains a potent and regal disposition.\n");
    add_item(({"mariner", "elendil"}), "Upon closer inspection, you "
        + "realize that this is a statue of Elendil son of "
        + "Amandil, first High King of Arnor and Gondor. A great "
        + "mariner, he gathered his sons Isildur and Anarion from "
        + "Numenor and was blown to Middle Earth in the wake of "
        + "tempest. There is a mighty longsword at his side.\n");
    add_item(({"longsword", "longsword on statue", "elendil's longsword",
        "blade"}),
        "A stone likeness of the famous blade Narsil hangs from "
        + "the side of the statue. It broke long ago beneath its "
        + "master when he fell with the elf king Gil-galad "
        + "in combat with Sauron on the slopes of Orodruin. Legend "
        + "speaks that it will one day be forged anew and an heir of the "
        + "House of Elendil will come forth to contest the Black Lord "
        + "of Mordor once again.\n");
    add_item(({"sky"}), "The sky is dominated by the tower rising before "
        + "you and the massive mountain behind and above it.\n");
    add_item(({"dove", "doves"}), "Blue-grey mourning doves can be seen "
        + "fluttering about the plaza. Now and then a dove will settle "
        + "on the great ships-wheel of the statue and coo sadly to its "
        + "fellows.\n");
    add_item(({"fish", "goldfish"}), "When you look into the pool, you spy "
        + "a large school of colourful goldfish. Although they are lovely, "
        + "you decide it would be better to drink from the fountain than "
        + "the pool.\n");
    add_item(({"banner", "banner of the stewards"}), "Far above you "
        + "the great banner of the Stewards is raised atop the pinnacle "
        + "of the tower. It floats a thousand feet above the plain "
        + "before the city.\n");
    add_item(({"plain"}), "The large open land before the city cannot "
        + "be seen over the encircling walls. A better view might be "
        + "gained on the battlement to the northeast.\n");
    add_item(({"wall", "walls"}), "This wall completely encloses the "
        + "Citadel. The dull murmer of city life rises from the six circles "
        + "descending beyond it.\n");
    add_item(({"gates", "seventh gate", "gate"}), "The two doors look "
        + "well-made and very strong. Although they can be pushed open "
        + "with almost no effort from this side, they are closely guarded "
        + "on the other. Only those with the password are permitted to "
        + "pass to this side.\n");
    add_item(({"battlement", "bastion", "stairs"}), "Partly from the primeval "
        + "shaping of the hill, partly from the mighty craft and labour of "
        + "old, a towering bastion of stone stands up from the First Gate, "
        + "rising up even to the level of this, the Seventh Circle. It is "
        + "crowned with a battlement that can be reached by climbing the "
        + "stairs to the northeast.\n");
    add_item(({"sky", "clouds"}), "The western sky is dominated by "
        + "Mount Mindolluin. The eastern sky seems filled with black "
        + "clouds.\n");
    add_item(({"western sky"}), "It is dominated by Mount Mindolluin.\n");
    add_item(({"eastern sky"}), "It is filled with black clouds.\n");


    set_drink_from("fountain");

    add_prop(OBJ_I_CONTAIN_WATER, -1);
    add_prop(ROOM_I_INSIDE, 0);

    tree = clone_object(INNER_MINAS + "/obj/white_tree.c");
    tree->move(TO);

    add_exit(INNER_MINAS + "/citadel/battlement1", "northeast", 0, 1);
    add_exit(INNER_MINAS + "/citadel/tower_entrance", "west", 0, 1);
    add_exit(INNER_MINAS + "/citadel/north_lane1", "north", 0, 1);
    add_exit(INNER_MINAS + "/citadel/south_lane1", "south", 0, 1);

    door = clone_object(INNER_MINAS + "/obj/gate_seven_in.c");
    door->move(TO);


    set_tell_time(120);
    add_tell("Water drips gently from the broken branches into "
        + "the pool.\n");
    add_tell("A dove flutters up from the paving-stones and comes "
        + "to rest on the statue.\n");
    add_tell("A refreshing mist from the fountain blows across the "
        + "courtyard.\n");
    add_tell("Dark clouds drift across the sky from the east.\n");
    add_tell("Crisp mountain wind whispers through the plaza.\n");
    add_tell("Thunder rumbles in the distance.\n");
    add_tell("Splash! A goldfish leaps from the water in the pool "
        + "only the plunge beneath the surface once again.\n");
    add_tell("The low sounds of Minas Tirith rise from below the "
        + "encircling walls.\n");
    add_tell("The banner of the Stewards snaps in the wind high "
        + "above.\n");

    reset_room();
}

public void
reset_room()
{
    clone_npcs(Guard, INNER_MINAS + "/npc/g7_guard_in", -1.0);
}


public void
init()
{
    ::init();
    init_drink();
}

/*
 * This function enables the random room tells.
 */

public void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);

    if(interactive(ob))
        start_room_tells();
}


