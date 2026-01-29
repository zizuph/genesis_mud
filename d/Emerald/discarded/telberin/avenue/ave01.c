/* 
 * Outer road of Telberin
 * By Finwe, January 1997
 */
 
#include "default.h"
 
inherit AVENUE;
 
 
void
create_avenue()
{
    add_my_desc("You stand awed at the beauty and workmanship of " +
        "the gleaming white buildings around you. Bright pennants " +
        "fly atop of the gleaming towers. As you look up at the " +
        "surrounding walls, the bright sun glints off the " +
        "shining armour of the Royal Guard. A grand arch " +
        "stands here, marking the entrance to the city, guarding " +
        "it from the enemies of the city.\n\n");
 
    add_item( ({"arch", "Arch", "grand arch", "grand Arch"}), 
        "The Arch dominates this part of town. Made of polished " +
        "white marble, it stands as a sentinal, protecting the " +
        "elves of Telberin. You notice reliefs carved onto " +
        "the Arch.\n");
 
    add_item( ( {"relief", "reliefs"}),"@@random_relief_desc@@"); 

    add_exit(AVENUE_DIR + "ave33", "south");
    add_exit(CASTLE_DIR + "1k1",  "east");
    add_exit(THIS_DIR +   "arch",  "west");
    add_exit(THIS_DIR + "eagle_landing", "up");
    add_exit("ave02", "northeast");
    set_alarm(1.0,0.0,"reset_room");
}
 
void
reset_room()
{
}
string random_relief_desc()
{
    return ( {"You see elven heros across the top of the Arch.\n",
              "You see a depiction of the King crushing his " +
                  "foes under his heel.\n",
              "You see the Keepers of Telberin defending " +
                  "the city during a decisive battle.\n",
              "Inside the Arch, you see relief carvings of " +
                "roses growing up and over the walls.\n",
              "You see the coronation of the King depicted.\n",
        })[random(4)];
}
