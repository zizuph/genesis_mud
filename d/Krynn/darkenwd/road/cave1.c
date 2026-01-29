/* Cave1 coded by Teth
 * Last updated Oct 25, 1996
 */

#include "local.h"
#include <macros.h>

inherit INCAVE;
inherit HERBSEARCHNEW

string *herbs = HERB_MASTER->query_herbs( ({ "cave", }) );

void
reset_darkenwd_room()
{
    set_searched(random(2));
}

void
create_darkenwd_room() 
{
    set_short("A large cave");
    set_long("This large cave is essentially a hole in the cliff. This cave "+
             "is large enough for several people to stretch out and spend " +
             "time comfortably resting. The floor of the cave is covered "+
             "with a soft warm sand. The walls of the cave are made of "+
             "granite, and are quite a dark grey. Fresh air appears to " +
             "circulate in the cave, so perhaps there is a small passageway "+
             "for air in the somewhat cracked rock ceiling. A large crack "+
             "is the only exit from the cave.\n"); 
    AI(({"cave", "large cave"}), "You are standing in it. It is essentially "+
        "a hole in the cliff.\n");
    AI("floor", "The floor of the cave is covered with a soft warm sand. " +
        "It looks like a suitable place to rest, being not too "+
        "uncomfortable.\n");
    AI(({"soft sand", "warm sand", "sand","soft warm sand"}),"This soft warm "+
        "sand appears to be the eroded product of years of water washing "+
        "upon rock. Perhaps it was deposited here when Crystalmir Lake had "+
        "high water levels one year.\n");
    AI(({"walls","wall","granite","rock","grey walls","dark grey walls"}),
        "These walls are covered with soot. Apparently, other adventurers "+
        "have built campfires in here in the past.\n");
    AI("soot", "The soot is black, but dry. It covers the walls with a " +
        "blanketing film.\n");
    AI(({"ceiling","rock ceiling","cracked rock ceiling","cracked ceiling"}),
        "The ceiling has several cracks in it, some of which seem to lead "+
        "for quite some distance upwards. However, none of the cracks are "+
        "bigger than a few centimetres across. It is possible that air can "+
        "find a passageway upwards, but certainly not you.\n"); 
    AI("cracks","The cracks in the ceiling are numerous and "+
        "many, the effect of time upon the rock.\n");
    AI(({"air","fresh air"}),"This air circulates in the cave, bringing in "+
        "a crisp smell, unlike most caves.\n");
    AI(({"crack","large crack"}),"This large crack is the only exit out of "+
        "the cave. It is wide enough for a large-shouldered human to fit "+
        "through with some discomfort.\n");
    add_search(({"walls","wall","granite","rock","grey walls",
        "dark grey walls","soot"}),3,KROBJECT + "black_soot", -20);
    add_search(({"sand","soft sand","soft warm sand","warm sand","floor"}),
        2,KROBJECT + "sand_grain",-20);
    add_exit(TDIR + "shore2", "out");

    seteuid(getuid(TO));
    set_up_herbs( ({ ONE_OF(herbs), ONE_OF(herbs), ONE_OF(herbs) }),
        ({"floor", "cave",}), 6);
    reset_room();

    DARK;
    
}



