/*
 *  /d/Gondor/minas/houses/stewards1.c
 *
 *  The House of Stewards: Porch
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
    set_short("On the porch of the House of Stewards");
    set_long("This is the porch of the House of Stewards. "
        + "You feel insignificant and small standing within the "
        + "towering architecture of this place. The porch is formed "
        + "by a long level expanse before the building, upon which rest "
        + "fifty massive columns. Between the columns are numerous "
        + "statues of tall stern-looking men. In the center of the "
        + "building a great arch opens into the empty halls of the Tomb. The "
        + "prospect of passing through the arch becomes even less "
        + "appealing as you discover how very dark it looks inside.\n");


    add_exit(INNER_MINAS + "/houses/hallows1", "south", 0, 0);
    add_exit(INNER_MINAS + "/houses/stewards2", "enter", 0, 0);


    add_item(({"porch", "expanse"}), "It is beneath your feet and "
        + "seems to be holding up some very large columns.\n");
    add_item(({"building", "tomb", "halls"}), "The House of Stewards is "
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
        + "shadows. Above the great arch of entry is engraved a bold "
        + "inscription.\n");
    add_item(({"inscription"}), "The inscription reads: To Hold Rod And "
        + "Rule In The Name Of The King, Until He Shall Return.\n");
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
        + "the south you see the Silent Street, the Rath Dinen. Beyond "
        + "the street stands the House of Kings, where the successors "
        + "of King Anarion forever sleep.\n");
    add_item(({"house of kings"}), "It stands on the other side of the "
        + "Rath Dinen and appears to be the architectural twin of the "
        + "House of Stewards.\n");
    add_item(({"flight", "stairs"}), "There must be one hundred large "
        + "rectangular stairs leading down from each Tomb.\n");
    add_item(({"statues", "men"}), "There are many statues of grim-faced "
        + "men standing among the great columns. These are the carven "
        + "images of long-dead Stewards. Some are weathered beyond "
        + "recognition, but six of them seem to have been "
        + "especially tended and remain true to their original form.\n");
    add_item(({"statue"}), "Which one? Six of them retain enough detail to "
        + "be recognizable.\n");
    add_item(({"first statue", "hurin"}), "Nearest the great arch is "
        + "the image of Hurin of Emyn-Arnen, sculpted from native stone. "
        + "Hurin was the steward of King Minardil and was the founder of "
        + "the House of Stewards. The Stewards of Gondor were ever after "
        + "chosen from his descendants. "
        + "He looks down upon all those seeking to enter the Tomb with "
        + "stern reproach.\n");
    add_item(({"second statue", "mardil"}), "Opposite the statue of "
        + "Hurin is the sculpted image of Mardil Voronwe, the Steadfast. "
        + "Mardil was the steward of King Earnil and then the last King "
        + "Earnur. When Earnur was lost, Mardil became the first Ruling "
        + "Steward of Gondor, charged with safeguarding the kingdom until "
        + "the return of the King. His face is the image of faithfulness.\n");
    add_item(({"third statue", "pelendur"}), "Near the middle of the "
        + "left side of the Tomb is the sculpted image of Steward Pelendur. "
        + "Although not one of the Ruling Stewards, Pelendur did rule "
        + "for a single year after the fall of King Ondoher and his sons. "
        + "Pelendur was instrumental in rejecting the claim of the last "
        + "northern king, Arvedui, for the vacant throne of Gondor.\n");
    add_item(({"fourth statue", "vorondil"}), "Near the middle of the "
        + "right side of the Tomb is the sculpted image of Steward "
        + "Vorondil the Hunter. Vorondil was the steward of King Earnil II "
        + "and made the Great Horn of the House of Stewards from the "
        + "horn of a Kine of Araw he slew during a hunt.\n");
    add_item(({"fifth statue", "boromir"}), "Near the end of the left "
        + "side of the Tomb is the sculpted image of Steward Boromir. "
        + "His image is strong of body, just as he was strong of will in "
        + "life. During the rule of his father, Denethor I, Boromir "
        + "captained a great battle in which Ithilien was regained "
        + "from the uruks of Mordor. In combat, he suffered a Morgul-wound that "
        + "left him increasingly shrunken with pain. He died only "
        + "twelve years after his father.\n");
    add_item(({"sixth statue", "belecthor ii", "belecthor II", "tree"}),
        "Near the end of the right side of the Tomb is the sculpted "
        + "image of Steward Belecthor II. At his feet stands a stone tree. "
        + "Upon his death, the white tree in the Court of the Fountain "
        + "also died. No sapling has ever been found to replace it, and the "
        + "dead tree can yet be seen in the fountain where it stands sadly "
        + "awaiting the return of the King.\n");
 


    reset_room();

}   
   

    











