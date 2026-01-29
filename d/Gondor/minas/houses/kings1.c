/*
 *  /d/Gondor/minas/houses/kings1.c
 *
 *  The House of Kings: Porch
 *
 *  Alto, 18 April 2001
 *
 */

#pragma strict_types

inherit "/d/Gondor/std/room.c";

#include <macros.h>
#include <stdproperties.h>
#include "/d/Gondor/defs.h"
#include "/d/Gondor/std/tell.c"


#define INNER_MINAS "/d/Gondor/minas"


public void
create_gondor()
{
    set_short("On the porch of the House of Kings");
    set_long("This is the porch of the House of Kings. "
        + "You feel insignificant and small standing within the "
        + "towering architecture of this place. The porch is formed "
        + "by a long level expanse before the building, upon which rest "
        + "fifty massive columns. Between the columns are numerous "
        + "statues of tall stern-looking men. In the center of the "
        + "building a great arch opens into the empty halls of the Tomb. The "
        + "prospect of passing through the arch becomes even less "
        + "appealing as you discover how very dark it looks inside.\n");


    add_exit(INNER_MINAS + "/houses/hallows1", "north", 0, 0);
    add_exit(INNER_MINAS + "/houses/kings2", "enter", 0, 0);

    add_item(({"porch", "expanse"}), "It is beneath your feet and "
        + "seems to be holding up some very large columns.\n");
    add_item(({"building", "tomb", "halls"}), "The House of Kings is "
        + "made entirely of "
        + "native stone. Its sheer size is enough to intimidate even the "
        + "bravest of hearts, and its sweeping arches are so beautiful "
        + "as to leave one breathless. Despite its grand elegance, however, "
        + "you hesitate to enter its silent halls.\n");
    add_item(({"stone", "native stone", "blocks"}), "Tough stone quarried from "
        + "the foothills of Mount Mindolluin. You wonder how the huge "
        + "blocks could have possibly been transported to this place.\n");
    add_item(({"arches", "arch"}), "The entrance to the Tomb is framed by a "
        + "great arch. Although it is dark inside, you can make out "
        + "other arches within, rising toward a ceiling lost in the "
        + "shadows. Above the great arch of entry is carved a large symbol.\n");
    add_item(({"symbol", "tree", "stars"}), "The symbol carved atop the arch "
        + "is the image of a tall stone tree beneath seven stars.\n");
    add_item(({"column", "columns"}), "The columns reach far upward, "
        + "and support the roof of the porch. They are made of the same "
        + "white stone as the rest of the building, and each is so broad "
        + "that twenty men with arms outstretched could not encircle it.\n");
    add_item(({"roof"}), "The roof of the Tomb slopes up toward the "
        + "pale dome at the apex of the building.\n");
    add_item(({"dome", "pale dome"}), "From here you can only see the "
        + "lower curve of the dome. To see it in full, you would need "
        + "to return to the street.\n");
    add_item(({"street", "rath dinen"}), "Looking down the stairs to "
        + "the north you see the Silent Street, the Rath Dinen. Beyond "
        + "the street stands the House of Stewards, where the successors "
        + "of Steward Hurin forever sleep.\n");
    add_item(({"house of stewards"}), "It stands on the other side of the "
        + "Rath Dinen and appears to be the architectural twin of the "
        + "House of Kings.\n");
    add_item(({"flight", "stairs"}), "There must be one hundred large "
        + "rectangular stairs leading down from each Tomb.\n");
    add_item(({"statues", "men"}), "There are many statues of grim-faced "
        + "men standing among the great columns. These are the carven "
        + "images of long-dead Kings. Some are weathered beyond "
        + "recognition, but six of them seem to have been "
        + "especially tended and remain true to their original form.\n");
    add_item(({"statue"}), "Which one? Six of them retain enough detail to "
        + "be recognizable.\n");
    add_item(({"first statue", "wheel"}), "This statue stands to the right of "
        + "the great arch, and is a replica of "
        + "the statue in the Court of the Fountain. The craft of its "
        + "making is lost in the "
        + "deeps of time. It depicts a tall mariner behind a giant "
        + "ships-wheel. Unlike the other statues, which face north, this "
        + "statue faces east. The mariner retains a potent and regal "
        + "disposition.\n");
    add_item(({"mariner", "elendil"}), "Upon closer inspection, you "
        + "realize that this is a statue of Elendil son of "
        + "Amandil, first High King of Arnor and Gondor. A great "
        + "mariner, he gathered his sons Isildur and Anarion from "
        + "Numenor and was blown to Middle Earth in the wake of "
        + "tempest. There is a mighty longsword at his side.\n");
    add_item(({"longsword", "longsword on statue", "elendil's longsword"}),
        "A stone likeness of the famous blade Narsil hangs from "
        + "the side of the statue. It broke long ago beneath its "
        + "master when he fell with the elf king Gil-galad "
        + "in combat with Sauron on the slopes of Orodruin. Legend "
        + "speaks that it will one day be forged anew and an heir of the "
        + "House of Elendil will come forth to contest the Black Lord "
        + "of Mordor once again.\n");
    add_item(({"second statue", "anarion"}), "Opposite the statue of "
        + "Elendil is the sculpted image of King Anarion, who with his "
        + "brother Isildur was the second king of Gondor. He died in "
        + "Mordor during the Last Alliance of Elves and Men when struck "
        + "by a stone hurled from the Barad-dur.\n");
    add_item(({"third statue", "isildur"}), "Directly beside the statue "
        + "of Anarion is the sculpted image of his brother, King Isildur. "
        + "It was Isildur who recovered a sapling of Nimloth the Fair, "
        + "later planting a seedling in "
        + "memory of his brother. Following the defeat of Sauron, Isildur "
        + "ruled Gondor for two years, but later died under mysterious "
        + "circumstances as he travelled north to assume the rule of "
        + "Arnor.\n");
    add_item(({"fourth statue", "minardil"}), "Near the middle of the "
        + "right side of the Tomb is the sculpted image of King "
        + "Minardil. His steward was Hurin of Emyn Arnen, who founded "
        + "the House of Stewards. Minardil was slain in battle with the "
        + "Corsairs of Umbar.\n");
    add_item(({"fifth statue", "tarondor"}), "Near the end of the left "
        + "side of the Tomb is the sculpted image of King Tarondor. "
        + "He assumed the throne when King Telemnar and all his children "
        + "perished in the Great Plague. Following the death of the "
        + "White Tree of Isildur, he planted one of its seedlings in "
        + "the Court of the Fountain. Tarondor ruled longer than any "
        + "other king of Gondor.\n");
    add_item(({"sixth statue", "earnur"}),
        "Furthest from the great arch on the right side of the Tomb "
        + "is the sculpted image of King Earnur, last King of Gondor. "
        + "In the battle of Fornost he was shamed when his horse bolted "
        + "from the presence of the Lord of the Nazgul. In later years, "
        + "after he had assumed the throne of Gondor, the Lord of the "
        + "Nine taunted him with a challenge of personal combat. At "
        + "first restrained by his steward Mardil, he later entered into "
        + "Minas Morgul and never returned. He had no heir, and thus "
        + "ended the line of Anarion. It was during his reign that the "
        + "name of the city was changed from Minas Anor, the Tower of "
        + "the Sun, to Minas Tirith, the Tower of the Guard.\n");
 


    reset_room();

}   
   

    











