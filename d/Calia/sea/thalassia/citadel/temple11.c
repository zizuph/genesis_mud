
/*  Diabrecho Temple in Thalassia

    coder(s):   Jaacar

    history:    15. 7.03    room coded                      Jaacar
                12. 5.16    typo fixed                      Jaacar

*/

#pragma save_binary
#pragma strict_types

inherit "/d/Calia/std/water_room";
#include <stdproperties.h>
#include <macros.h>
#include "/d/Calia/sys/water.h"
#include "defs.h"

void
create_water_room()
{
    set_short("Swimming in the Temple of Diabrecho");
    set_long("You are swimming in the magnificent Temple of Diabrecho. "+
        "This structure was built originally to house statues of the "+
        "leaders of the city, but was later changed to show thanks "+
        "to Lord Diabrecho for the gift of life in the sea. Rising "+
        "up before you is a gigantic golden statue of Lord Diabrecho "+
        "riding in a chariot drawn by six massive sea-horses. "+
        "Surrounding the chariot and sea-horses are one hundred golden "+
        "statues of tritons riding dolphins. The statue of Lord "+
        "Diabrecho is so large that its head touches the top of the "+
        "domed roof. To the north you see a large altar, directly "+
        "in front of the statues. Surrounding the outside walls of the "+
        "temple are statues of the past leaders of this city, also made "+
        "of gold. There are many pillars rising up to hold the ceiling "+
        "in place above you. There is a pathway leading north and west "+
        "from here.\n");

    add_item(({"altar","large altar"}),"The large altar appears to "+
        "be made of the fiery metal orichalcum and decorated with "+
        "marble and silver. It is directly north from here.\n");

    add_item("pathway","The pathway leads off to the north and west.\n");

    add_item(({"wall","walls","outside wall","outside walls"}),
        "The walls are made entirely of gold blocks placed one on "+
        "top of the other. The seams between the blocks are so "+
        "small that it is almost impossible to see them, giving "+
        "the illusion that the wall is one solid mass of gold.\n");

    add_item(({"pillar","pillars"}),"These silver coated pillars rise "+
        "up two hundred feet to hold the golden ceiling above you.  "+
        "Each one is perfectly round and smooth.\n");

    add_item(({"roof","ceiling","dome","domed roof"}),"The roof is "+
        "made entirely of gold except for the dome which rises "+
        "another one hundred feet above the rest of the roof. The "+
        "inside of the dome is coated in white ivory slabs between "+
        "which run veins of orichalcum, silver and gold. The head "+
        "of the statue of Lord Diabrecho touches the middle of the "+
        "the dome.\n");

    add_item(({"triton","tritons","triton statue","triton statues"}),
        "The golden triton statues each depict a muscular creature "+
        "with a human-like torso and arms but from the waist down "+
        "they have tails like that of a fish which are wrapped "+
        "around the bottom of the dolphin statues they are riding. "+
        "Each one is wielding a trident in both hands.\n");

    add_item(({"sea-horse","sea-horses","sea horse","sea-horses",
        "sea-horse statue","sea-horse statues","sea horse statue",
        "sea horse statues"}),"These massive golden sea-horses dwarf "+
        "all but the largest of their land-based cousins. They are "+
        "so muscular in fact that you think that just one of these "+
        "beasts could pull this entire chariot on its own.\n");

    add_item(({"chariot","chariot statue"}),"This gigantic golden "+
        "statue is a beautifully decorated chariot. Riding inside of the "+
        "chariot is Lord Diabrecho. There are six massive sea-horses "+
        "pulling this chariot.\n");

    add_item(({"leader","leaders","leader statue","leader statues"}),
        "These marvelous golden statues of the past leaders of "+
        "Thalassia were carved by the hands of the finest sculptors "+
        "in the entire city and then carefully coated in gold. There "+
        "are ten statues in all.\n");

    add_item(({"statue","statues","gold statue","gold statues"}),
        "Which statue(s) do you want to look at? The statue of "+
        "Lord Diabrecho, the dolphin statue(s), the triton statue(s), "+
        "the sea-horse statue(s), the chariot statue, or the leader "+
        "statue(s)?\n");

    add_item(({"dolphin","dolphins","dolphin statue","dolphin statues"}),
        "These golden dolphin statues seem to float magically around "+
        "the statue of Lord Diabrecho, each with a triton rider on its "+
        "back.\n");

    add_item(({"Lord Diabrecho","lord diabrecho","diabrecho",
        "Diabrecho","statue of Lord Diabrecho",
        "statue of lord diabrecho"}),"This massive golden statue of "+
        "Lord Diabrecho must be over one hundred and fifty feet in "+
        "length and three hundred feet high at its highest point. "+
        "He is very handsome, with rich and flowing hair and a sleek "+
        "yet muscular body. He stands in a chariot of gold wielding "+
        "a giant trident in one hand and holding the reins to the "+
        "sea-horses in the other.\n");

    IN;

    add_swim_exit(THALC+"temple10","north",0,1);
    add_swim_exit(THALC+"temple12","west",0,1);
}
