/* 
 * /d/Kalad/common/central/high-circle-north.c
 * Purpose    : Road connection between high and circlestreet
 * Located    : /d/Kalad/common/central/
 * Created By : Korat 1995
 * Modified By: Toby, 970919 (fixed typos)
 */ 

/* High street, north of plaza. */

inherit "/d/Kalad/room_std";  
#include "/d/Kalad/defs.h"  
object ob1;

void
reset_room()
{
    if (!objectp(ob1))
        {
        ob1 = clone_object("/d/Kalad/common/central/npc/patrol_watchman");
        ob1 -> move_living("xxx",TO);
    }
}

void
create_room()
{
    ::create_room();
    hear_bell = 3;
    set_short("High Street");
    set_long("You walk along the High Street, trying to avoid all the "+
        "small water pulps scattered around on the bricked road. You notice "+
        "that this crossroad also leads to the Circle street that circles the "+
        "grand plaza with its huge statue. Southwards you can see that "+
        "statue rising high among several buildings.\n");
    
    set_time_desc("Several people walk past you, all off to their "+
        "own doings.\n","The streets are deserted, except some figures "+
        "that silently walk the shadows.\n");
    
    add_exit(CENTRAL(high/s3), "north", 0);
    add_exit(CENTRAL(plaza/sq_north), "south", 0);
    add_exit(CENTRAL(circle/s1), "west");
    add_exit(CENTRAL(circle/s2), "east");
    
    add_item(({"pulps","pulp"}), 
        "Just small, wet pulps. Better try to avoid stepping into them!\n");
    add_item("statue", 
        "A large statue indeed. It has to be since you can "+
        "see it from this distance.\n");
    add_item("plaza",
        "The plaza lies south of you as an island surrounded with buildings, "+
        "just like all plaza's do.\n");

    reset_room();
}
