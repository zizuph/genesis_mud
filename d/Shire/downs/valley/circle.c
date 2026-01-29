/*
 * The valley of the Barrow Downs
 * By Finwe, December 2001
 */
 
//#pragma strict_types
 
#include "local.h"
#include "/d/Shire/sys/defs.h"
//#include "/d/Shire/scav_hunt/scav_hunt.h"

#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>

inherit ROAD_BASE;

#define MIN_AWARE 10
static object coronet;
//int coronet_check=0;
//string scav_hunt_item();

 
void
create_road_room()
{
    set_areadesc("hollow");
    set_area("circle in");
    set_areaname("the Barrow Downs");
    set_land("Eriador");

    set_extraline("This is an excavated hill in the valley of the " +
        "Downs. It is bowl shaped and looks like it was used for " +
        "cremating bodies or something. A tall stone rises from the " +
        "center of the valley. This hollow circle has an uneasy feeling " +
//        "about it. " + scav_hunt_item() + " " + coronet_check);
        "about it.");
    add_item(({"tall rock", "rock", "tall stone", "stone"}),
        "The tall stone stands in the center of the hollow. It " +
        "looks featureless yet somehow significant, as if it was " +
        "a landmark of some sort.\n");
    add_item(({"circle", "hollow circle"}),
        "The hollow circle is bowl shaped and looks like it was " +
        "excavated by someone ages ago. It is covered with green " +
        "grass with only a single tall rock rising from its center.\n");
    add_item(({"excavated hill"}),
        "The excavated hill is bowl shaped, and sunk into the " +
        "earth. The inside of the hill is covered with green grass. " +
        "A tall rock stands in the center and points to the sky.\n");

    add_exit(VAL_DIR + "val06", "north");
    add_exit(VAL_DIR + "val05", "southwest");

}

public void reset_shire_room()
{
    coronet = 0;
//    coronet_check = 0;
}
/*
string scav_hunt_item()
{
write(coronet_check);

    if (SCAV_HUNT == 0)
    {
        if (coronet_check != 0) 
        {
            return "A cold wind blows down through the hollow.";
        }
        else
        {
            return "Something glints under the tall stone.";
        }
    }
}

public string
herb_search(object searcher, string str)
{
   int     awareness;
   string  dummy;

   seteuid(getuid());
   
   if (sscanf(str, "%s for %s", dummy, dummy) == 2)
       return ::herb_search(searcher, str);

   awareness = searcher->query_skill(SS_AWARENESS);
   if (awareness < (MIN_AWARE ))
       return 0;
   if (!str || (str!= "stone" && str != "tall stone")) 
       return 0;
   if (coronet) 
       return 0;

   coronet = clone_object("/d/Shire/scav_hunt/coronet");
   coronet_check = 1;
   if (coronet->move(searcher))
       if (coronet->move(TO))
       {
           coronet->move(TO, 1);
           coronet_check = 1;
        }
   say(QCTNAME(searcher)+ " digs under the tall rock and finds something.\n");
   return "You dig under the tall rock and find an ancient battered coronet.\n";
}

*/