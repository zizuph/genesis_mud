// file name:        /d/Avenir/common/holm/jungle/lf20.c
// creator(s):       Lilith, Nov 97
// revisions:
// purpose:
// note:
// bug(s):
// to-do

/* Inherit the room that is the base for the area. */
inherit "/d/Avenir/common/holm/jungle/jungle_base";

/* Include the local area defines, etc */
#include "/d/Avenir/common/holm/holm.h"
#include <composite.h>
#include <filter_funs.h>

/*
 * Function name: reset_domain_room
 * Description:   This function should be used for for reseting herbs
 */
void reset_domain_room()
{
    set_searched(0);
    ::reset_domain_room();
}


/* Now create the room.  */
void
create_jungle_room()
{
    set_short("knoll overlooking the shoreline");
    set_long("You stand upon a little knoll overlooking the shoreline. "+
        "A fine layer of black sand grinds underfoot, providing little "+
        "relief from the hard glossy stone of the obsidian seawall. "+
        "A narrow path cuts into the thorn bushes east of here, and "+
        "toward the humid embrace of the jungle in the northeast. Below, "+
        "your view of the shore is limited, but looking northwest you "+
        "can see @@shore_view@@.\n"); 

    add_exit("lf19", "northeast", 0);
    add_exit(SHORE +"sh27", "down", "@@jump");
    add_exit("lf21", "east", 0);

    add_item(({"thicket", "thorn bushes", "bushes"}),
        "Stubborn bushes with thick gnarled trunks and viscious "+
        "hooked thorns.\n");
    add_item(({"shore", "shoreline"}), "Your view of the shore is limited, "+
        "but looking northwest you can see @@shore_view@@.\n");
    add_item(({"sand"}), "It is very fine and black.\n");
    add_cliff();
    add_seawall();
    add_atrack();
    reset_domain_room(); 
}

int 
jump()
{
    write("\nYou jump off the obsidian seawall and land with a roll on the "+
        "soft, black sand.\n");
    return 0;
}

string 
shore_view()
{
    object *inv, *live, *dead, room;
    int i;
 
    inv = ({ });
    for (i = 0; i < sizeof(SROOMS); i++)
        if ((room = find_object(SROOMS[i])))
            inv += all_inventory(room);
 
    if (inv && sizeof(inv) > 0) 
    {
        live = FILTER_LIVE(inv);
        live = FILTER_CAN_SEE(live, TP);
        dead = FILTER_DEAD(inv);
        dead = FILTER_CAN_SEE(dead, TP);

        if (sizeof(live) > 0 && sizeof(dead) > 0)
            return COMPOSITE_LIVE(live);
        else if (sizeof(live))
            return COMPOSITE_LIVE(live);
        else if (sizeof(dead))
            return COMPOSITE_DEAD(dead);
    }
    return "little more than stranded humps of seaweed and hungry shorebirds";
}

  
