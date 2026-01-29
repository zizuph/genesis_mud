#include "/d/Krynn/common/defs.h"
#include "../local.h"

/* Inherit the Krynn room */
inherit R_FILE

/*
 * Change these two XXX to the proper name
 */
#define CREATE "create_sewer_room"
#define RESET  "reset_sewer_room"

/*
 * IN NORMAL CASES YOU SHOULDN'T NEED TO CHANGE ANYTHING BELOW
 */

object dwarf1, dwarf2, dwarf3;

/*
 * This function is called from the main Krynn room. It checks
 * weather or not the room should be reseted.
 * The function returns TRUE if there should be a reset.
 */
nomask public int
query_reset()
{
    if (function_exists(RESET, TO))
        return 1;
    return 0;
}

/*
 * This function is called from the main Krynn room.
 */
nomask public void
create_krynn_room()
{
    call_other(TO, CREATE);
}

/*
 * This function is called from the main Krynn room.
 */
nomask public void
reset_krynn_room()
{
    call_other(TO, RESET);
}

void
create_sewer_room()
{
   set_short("Cottage in the sewers of Kalaman");
   set_long("@@look_desc");
    
   add_item(({"tunnel", "tunnels", "ceiling"}), "@@tunnel_desc");
   add_item(({"rubbish", "heap"}), 
                "There are a lot of rubbish stacked on the heap. " + 
                "You see a lot of items which are probably thrown " + 
                "into the sewers by the citizen of Kalaman. Most of " +
                "the stuff you see is considered junk to you.\n");
    
   INSIDE;
   reset_room();
}

void
reset_sewer_room()
{
    if (!objectp(dwarf1))
    {
        if(random(2))
        {
            dwarf1 = clone_object(SNPC + "dwarf");
            dwarf1->move_living("xxx", TO);
        }
    }
    if(!objectp(dwarf2))
    {
        if(random(2))
        {
            dwarf2 = clone_object(SNPC + "dwarf");
            dwarf2->move_living("xxx", TO);
        }
    }
    if(!objectp(dwarf3))
    {
        if(random(2))
        {
            dwarf3 = clone_object(SNPC + "dwarf");
            dwarf3->move_living("xxx", TO);
        }
    }
    

}

string
get_race_string()
{
    string temp, temp2, temp3, race;
    
    race = QRACE(TP);
    temp = "The ceilings are very low";
    
    temp2 = " and you have to duck your head a little to fit in these tunnels";
    temp3 = ". You find it hard to believe that these dwarves are somehow related to the hill dwarves in the south";
    
    if(race == "gnome" || race == "hobbit" || race == "kender" || race == "dwarf")
    {
        temp2 = ", but you are able to stand up straight without bumping your head to the ceiling";
        
        if(race == "dwarf")
        {
            temp3 = ". The thought that these dwarves are somehow related to you disgusts you";
        }
    }
    else if(race == "human" || race == "elf")
    {
        temp2 = " and you have to duck your head in, avoiding bumping into the ceiling. You wonder if this will cause back troubles later on";
    }
    
    temp += temp2 + temp3 + ".\n";
    return temp;
}

string
tunnel_desc()
{
    string temp;
    temp = "The craftmanship of these cottages are very poor. " + get_race_string();
    return temp;
}


string
look_desc()
{
    string temp;
    temp = "You are standing in a small cottage in the village of the gully dwarves. " + 
           "The entire cottage is made of mud and feces which the dwarves probably found " +
           "in the first floor of the sewers. The cottage is small, damp and messy. " +
           "There is a big heap of rubbish in the corner of the cottage. " + 
           tunnel_desc();

    return temp;
}
