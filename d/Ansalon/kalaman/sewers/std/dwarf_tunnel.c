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
   set_short("Down in the sewers of Kalaman");
   set_long("@@look_desc");
    
   add_item(({"tunnel", "tunnels", "ceiling"}), "@@tunnel_desc");
    
   INSIDE;
}

void
reset_sewer_room()
{
    
}

string
get_ceiling_string()
{
    string temp, temp2, race;
    
    race = QRACE(TP);
    temp = "The ceilings are very low";
    
    temp2 = " and you have to duck your head a little to fit in these tunnels";
    
    if(race == "gnome" || race == "hobbit" || race == "kender" || race == "dwarf")
    {
        temp2 = ", but you are able to stand up straight without bumping your head to the ceiling";
    }
    else if(race == "human" || race == "elf")
    {
        temp2 = " and you have to duck your head in, avoiding bumping into the ceiling. You wonder if this will cause back troubles later on";
    }
    
    temp += temp2 + ".\n";
    return temp;
}

string
tunnel_desc()
{
    string temp;
    temp = "The craftmanship of these tunnels are very poor. " + get_ceiling_string();
    return temp;
}


string
look_desc()
{
    string temp;
    temp = "You are under the tunnels of the sewers of Kalaman. These tunnels were not made by the builders of Kalaman, for these tunnel system here are not like the craftmanship of the tunnels above. The tunnels are wet and damp, and rather filthy as well. " + get_ceiling_string();
    return temp;
}
