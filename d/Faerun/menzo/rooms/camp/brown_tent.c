/*
* Clyptas - August, 2017
*/

#pragma strict_types
#include "/d/Faerun/defs.h"
#include "defs.h"
#include <stdproperties.h>
inherit "std/room";
#define OBJ "/d/Faerun/menzo/obj/"
object azure_wine;
#define MIN_AWARENESS   10

int items_count = 0;
object item_found;

public void
create_room()
{
    
    //0 means outdoors, and 1 means indoors for this prop
    add_prop(ROOM_I_INSIDE, 1);
    
    set_short ("Inside a small brown tent.");

    set_long("The tent is clean and maintained. Herbs hang from the beams above " +
         "you. There are crates, boxes, and sacks stacked and placed neatly " +
         "in the center of the tent. There are wide, squat barrels lining " +
         "right side.\n");
         
    add_item(({"crates"}),
         "The crates are clean. The writing on the sides tells you they are " +
         "filed with a number of different things. Mostly goods and " +
         "non-perishables.\n");
         
    add_item(({"writing"}),
         "The writing is blocked, solid letters, written in the common " +
         "tongue. Mostly labels sorting flour, grains, sugar, and dried " +
         "meat.\n");
    
    add_item(({"sacks"}),
        "The sacks are full of bolts of brightly colored cloth, spidersilk, " +
        "cotton, satin, elfwyr and webcloth.\n");
    
    add_item(({"boxes"}),
        "The boxes are sealed and taped shut. They are unmarked.\n");
    
    add_item(({"herbs"}),
        "Herbs are strung from the beams, drying from the rafters. The " +
        "faint scents of the herbs greet your nose.\n");
        
    add_item(({"beams"}),
        "Fresh herbs and flowers hang from the beams of the tent.\n");
        
    add_item(({"flowers"}),
        "The flowers are hanging upside down, and you realize that they are " +
        "drying. Many of the flowers are familiar to you, while some are " +
        "unknown.\n");
        
    add_item(({"casks","barrels","containers"}),
         "There are casks of what seems to be wine lining the right side " +
         "of the tent. There are a few skins lying on top of the barrels.\n");
    
     add_exit(CAMP_DIR + "camp1", "out");
    
    add_prop(OBJ_S_SEARCH_FUN,"my_search");
    add_prop(OBJ_I_SEARCH_TIME, -2);
}

void
reset_room()
{
    ::reset_room();
    items_count = 0;
}

mixed
my_search(object searcher, string str)
{
    int awareness;
    int max_item_count = 2;

    awareness = searcher->query_skill(SS_AWARENESS);
    if(awareness < MIN_AWARENESS)
    {
        return 0;
    }

    if(str=="crates" || str=="barrels")
    {
        if(items_count > max_item_count)
        {
            return "You found nothing.\n";
        }
        else
        {
            seteuid(getuid(TO));
            item_found = clone_object(OBJ + "azure_wine");
            item_found->move(searcher,1);
            say(QCTNAME(searcher)+ " found something.\n");
            items_count = items_count + 1;
            return "You find a " + item_found->short() + " behind the " + 
                str + ".\n";
        }

      return "You found nothing here!\n";
    }
    else
    {
        return 0;
    }
}

public void
hook_smelled(string str)
{
    switch(str)
    {
    case "herbs":
    write("The tangy, sharp scent of herbs drying permeates your nostrils.\n");
    break;

    case "flowers":
    write("You smell the heady, sweet aroma of flowers drying as they hang.\n");
    break;

    default:
    write("The scent of flowers and herbs wafts around you.\n");
    break;
    }
}
