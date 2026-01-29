/*
 *  /d/Gondor/minas/citadel/tower2.c
 *
 *  Hall of the White Tower of Ecthelion: Center
 *
 *  Alto, 20 April 2001
 *
 */

#pragma strict_types

inherit "/d/Gondor/std/room.c";

#include <macros.h>
#include <stdproperties.h>
#include "/d/Gondor/defs.h"

#define INNER_MINAS "/d/Gondor/minas"

public void
create_gondor()
{
    set_short("Inside the hall of the White Tower");
    set_long("You are halfway between the dais to the west and "
        + "the great doors to the east. There are deep windows in the "
        + "wide aisles at either side, beyond rows of tall pillars "
        + "that uphold the roof. No hangings nor storied webs, nor "
        + "any things of woven stuff or of wood, are to be seen in "
        + "this long solemn hall; but between the pillars there stands "
        + "a silent company of tall images graven in cold stone.\n");

    add_exit(INNER_MINAS + "/citadel/tower3", "west", 0, 0);
    add_exit(INNER_MINAS + "/citadel/tower1", "east", 0, 0);

    add_item(({"hall", "great hall", "tower", "white tower"}), "This is "
        + "a vast hall made entirely of native stone. Your footsteps ring "
        + "upon the stone floor and echo off the stone walls. The tall "
        + "statues between the pillars seem to stare down upon you in "
        + "disapproval of the noise.\n");
    add_item(({"stone", "native stone", "marble", "rock"}), "There are "
        + "two primary kinds "
        + "of stone from which the objects in the great hall are made. One "
        + "is the kind of gleaming white rock such as the seven walls of "
        + "the city are made from. The other is a shiny black marble. "
        + "Both are quarried from the foothills of Mount Mindolluin.\n");
    add_item(({"stone floor", "floor"}), "The floor is made from the "
        + "same black marble as the great monolithic pillars. "
        + "It is so highly polished that it reflects back the light of "
        + "the hall.\n");
    add_item(({"statue", "statues", "images", "company", "image"}), "The "
        + "statues between the "
        + "great pillars comprise an avenue of kings long dead. Near the "
        + "dais are three statues you recognize as Elendil, Anarion and "
        + "Isildur, the first kings of Gondor.\n");
    add_item(({"elendil", "statue of elendil"}), "This is a likeness "
        + "of Elendil son of "
        + "Amandil, first High King of Arnor and Gondor. A great "
        + "mariner, he gathered his sons Isildur and Anarion from "
        + "Numenor and was blown to Middle Earth in the wake of "
        + "tempest. There is a mighty longsword at his side.\n");
    add_item(({"longsword", "longsword on statue", "elendil's longsword"}),
        "A stone likeness of the famous blade Narsil hangs from "
        + "the side of the statue of Elendil. It broke long ago beneath its "
        + "master when he fell with the elf king Gil-galad "
        + "in combat with Sauron on the slopes of Orodruin. Legend "
        + "speaks that it will one day be forged anew and an heir of the "
        + "House of Elendil will come forth to contest the Black Lord "
        + "of Mordor once again.\n");
    add_item(({"anarion", "statue of anarion"}), "Opposite the statue of "
        + "Elendil is the sculpted image of King Anarion, who with his "
        + "brother Isildur was the second king of Gondor. He died in "
        + "Mordor during the Last Alliance of Elves and Men when struck "
        + "by a stone hurled from the Barad-dur.\n");
    add_item(({"isildur", "statue of isildur"}), "Beside the statue "
        + "of Anarion is the sculpted image of his brother, King Isildur. "
        + "It was Isildur who recovered a sapling of Nimloth the Fair, "
        + "later planting a seedling in "
        + "memory of his brother. Following the defeat of Sauron, Isildur "
        + "ruled Gondor for two years, but later died under mysterious "
        + "circumstances as he travelled north to assume the rule of "
        + "Arnor.\n");
    add_item(({"windows", "walls", "north wall", "south wall"}), "The "
        + "windows are forty feet tall "
        + "and ten feet wide. They are set into the north and south walls "
        + "in such a way that every two pillars have a window between "
        + "them. They are cut deep, and ascend at such a steep angle that "
        + "you are unable to see outside through them.\n");
    add_item(({"aisles"}), "Beyond the great pillars, two wide aisles "
        + "line the north and south facing walls of the great hall.\n");
    add_item(({"rows", "pillars", "tall pillars", "monoliths", "pillar"}), 
        "Mighty pillars stand in two rows running the length of "
        + "the hall from west "
        + "to east. Monoliths of black marble, they rise to great capitals "
        + "carved in many strange figures of beasts and leaves. Between "
        + "each two pillars is a tall image carved in stone.\n");
    add_item(({"capital", "capitals", "figures", "beasts", "leaves"}), 
        "Great capitals can be seen at the top of each pillar where it "
        + "meets the roof. Each is elegantly sculpted with images of "
        + "beasts and leaves.\n");
    add_item(({"roof", "vaulting", "traceries"}), "Far above in shadow, "
        + "the wide vaulting "
        + "gleams with dull gold, inset with flowing traceries of many "
        + "colours.\n");
    add_item(({"dais", "steps"}), "At the far end of the hall, upon a "
        + "dais of many steps, is set a high throne under a canopy of "
        + "marble shaped like a crowned helm; behind it is carved upon "
        + "the west wall, and set with gems, an image of a tree in flower. "
        + "At the foot of the dais, upon the lowest step, which is broad "
        + "and deep, there is a stone chair, black and unadorned.\n");
    add_item(({"throne", "high throne"}), "This is where the King of "
        + "Gondor sat as he held court in the days after the fall of "
        + "Osgiliath. The throne has been vacant for many years, however. "
        + "Its empty grandeur paints a dash of sadness and loss against "
        + "the otherwise regal splendour of the great hall.\n");
    add_item(({"canopy", "crowned helm", "helm"}), "A great canopy "
        + "of marble arches over the empty throne. It is fashioned after "
        + "the winged helm of the House of Elendil. Only the tower guard "
        + "wear such livery now.\n");
    add_item(({"tree", "gems", "west wall"}), "A great carving of a tree "
        + "in flower adorns the west wall. Its leaves are made of glittering "
        + "gems. It strikes you that this must be what the dead tree in the "
        + "Court of the Fountain must have looked like in its living years.\n");
    add_item(({"chair", "lowest step", "stone chair", "black chair", "step"}), 
        "On the lowest step of the dais rests a small stone chair. Upon this "
        + "chair sat the Steward of the city whilst the King held court. "
        + "Although no King has walked this hall for many a year, the ruling "
        + "Steward remains here, at the foot of the dais, until the return "
        + "of the King.\n");
    add_item(({"doors", "timbers", "plates", "doors"}), "Two "
        + "massive doors made of wood "
        + "banded in great plates of iron. These doors have never been "
        + "broken, and gazing upon their might you wonder at the "
        + "kind of strength that would be required to even scratch "
        + "the huge timbers.\n");



    add_prop(ROOM_I_INSIDE, 1);
    add_prop(ROOM_I_HIDE, -1);

    reset_room();
}


