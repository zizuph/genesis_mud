/* created by Aridor 06/19/93 */

#include "../local.h"
#include "/d/Krynn/common/clock/clock.h"
#include <macros.h>

inherit ROOM_BASE


string
get_long()
{
    string ret_str = "The Vingaard Mountains seem less significant up close, though "
                   + "you realize the road a head is still significant. ";
    int season;

    season = GET_SEASON;

    switch (season)
    {
        case WINTER:
            ret_str += "However, the deeper chill of the winter is in the air, "
                    +  "and the southern track is blocked by a wall of snow, making "
                    +  "the the northern track the only possible route.\n";
            add_item(({"snow", "wall of snow", "wall"}), "The wall of snow is blocking the southern track.\n");
            break;
        case SPRING:
           ret_str += "The wind blowing past you is mild. ";
            break;
        case SUMMER:
            ret_str += "The wind blow up the mountainside is warm and kind. ";
            break;
        case AUTUMN:
            ret_str += "The wind here is rough as if it bids the darker days to come welcome. ";
            break;
    }

    if (season != WINTER)
    {
        ret_str += "The winding road continues northeast and east,"
                + " winding itself up the steep mountainside. "
                + "Rocks and cliffs make travel in other directions "
                + "impossible. ";
        remove_item("snow");
        remove_item("wall of snow");
        remove_item("wall");
    }

    return ret_str;
}

int
check_southern()
{
   if (GET_SEASON != WINTER)
   {
       TP->catch_msg("You continue down the southern track...\n");
       return 0;
   }

   TP->catch_msg("The road is blocked by a wall of snow...\n");
   say(QCTNAME(TP) + " stops and looks at the wall of snow blocking " +
       "the way to the east.\n");
       
   return 1;
}

void
create_vin_mount_room()
{

    set_short("In the Vingaard Mountains");
    set_long(get_long()+"\n");

    OUTSIDE;

    add_exit(ROOM + "road5", "east", check_southern, 15);
    add_exit(ROOM + "road3","northeast",0,15);

    add_item(({"track","ground","road","gravel","mountain track"}),
         "The track itself is simply " +
        "laid out with small stones and gravel.\n");
    add_item(({"mountains","mountain","mountainside"}),
         "These are high mountains indeed, rocks and occasional " +
        "shrubs are scattered everywhere, it is definitely " +
        "a very hostile area.\n");
    add_item(({"cliffs","cliff"}),
         "Steep, almost vertical cliffs offer no chance for travel " +
        "in other directions but along the road.\n");
    add_item(({"shrubs","rocks"}),
         "The mountainsides are covered with rocks with a few " +
        "shrubs making their living in between.\n");


}

