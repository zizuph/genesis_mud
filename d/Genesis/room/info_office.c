
/* 
   This is the Genesis domain office. 
   It's here as an example of how to code a domain 
   office for the tower of realms. 

   Coded by Maniac 7/1/97
 */ 

#include <stdproperties.h>
#include "/d/Genesis/start/human/town/tower.h"
#include <std.h>

inherit TOWER_OFFICE;

void
create_tower_office()
{
    set_long("You're standing on the rounded surface of a huge " +
             "sugar-frosted donut. In the donut's hole is a beaming " +
             "light that illuminates the inner surface of the " +  
             "toroid, while the outer surface is eternally dark. " +  
             "Taking a closer look at the donut's surface you blink " + 
             "in disbelief as you begin to see " +
             "mountain ranges, seas, forests and cities all over " +
             "the place. But that's probably just your over-active " +
             "imagination at work. " +
             "Planted nearby is a sign on a spike, with a small " +
             "pool of jam at its base.\n" +
             "Clearly visible is a player graph, on which the creators " +
             "keep track of the amount of visitors to the realm. From " +
             "time to time the graph refreshes itself.\n");

    add_item(({"donut", "sugar", "hole", "light", 
               "toroid", "jam", "pool"}), 
            "Genesis is a big jam donut with a light at its centre. " +
            "This model is _not_ to scale.\n"); 

    add_item(({"mountain ranges", "seas", "forests", "cities"}), 
             "Nah, it must be your imagination.\n"); 
    add_item("sign", OFFICE_SIGN_TEXT); 
    add_cmd_item("sign", "read", OFFICE_SIGN_TEXT); 
    add_item( ({ "graph", "player graph" }), "@@graph@@");
    disable_logged_in_display(); 
    set_project_dir("/d/Genesis/open/projects/"); 
    add_tower_link("tower"); 

    add_prop(ROOM_I_INSIDE, 1);
    add_prop(ROOM_S_MAP_FILE, "tower_map.txt");
}

string
graph()
{
    WIZ_CMD_APPRENTICE->graph("all");
    return "";
}
