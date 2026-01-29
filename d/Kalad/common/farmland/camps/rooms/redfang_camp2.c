/*
 *  /d/Kalad/common/farmland/camps/rooms/redfang_camp2
 *
 *  One of the rooms in the red fang camp in Kalad
 *
 *  Created October 2015, by Andreas Bergstrom (Zignur)
 */
#pragma strict_types
#include "../defs.h"

inherit ROOMS_DIR + "std_redfang_camp";


/* Prototypes */
public void         create_redfang_camp_room();
public int          burn_redfang_camp(string str);


/*
 * Function name:        create_redfang_camp_room
 * Description  :        constructor for the room
 */
public void
create_redfang_camp_room()
{
    set_short("at a path southeast of a camp");
    set_long("A sparse forest surrounds the area, broken crates,"
      + " barrels and refuse piles lie scattered on the ground."
      + " The path leads northwest towards the main camp"
      + " and east towards the farmlands.\n\n");       

    add_redfang_camp_items();
    /* special items for this room */
    add_item( ({ "path" }),
        "The path leads in and out of the camp.\n");
    add_item( ({ "forest", "sparse forest"}),
        "You see a sparse forest surrounding the camp.\n");
    add_item( ({ "farmland", "farmlands"}),
        "The farmlands of Kalad lies to the southeast.\n");	
    int totalMobs = 0;
    int mobs = 0;
    mobs = random(6)+2;
    totalMobs = totalMobs + mobs;
    
    add_npc(NPC_DIR + "goblin_warrior", mobs, &->arm_me());
 
    /* Add the mobs to the counter */
    RF_WAR_ROOM->add_goblin_warriors(totalMobs);

    add_exit("redfang_camp1", "east");
    add_exit("redfang_camp3", "northwest");
   
} /* create_redfang_camp_room */

/*
 * Function name:        burn_redfang_camp
 * Description  :        Attemps to burn the redfang camp
 * Arguments    :        string str 
 * Returns      :        0 - failure
 */
public int
burn_redfang_camp(string str)
{
    
    if(!strlen(str))
    {
        notify_fail("Burn what? <burn camp>, perhaps?\n");
        return 0;
    }
   
    if (!parse_command(str, ({}),
        "[the] 'camp'"))
    {
        return 0;
    }
    
    /* This room is outside the main camp so we dont want
    to burn it. */
    notify_fail("You need to move further into the camp.\n");
    return 0;
    
   
} /* burn_redfang_camp */


/*
 * Function name: init
 * Description  : Override the burn function from the std room.
 */
public void
init()
{
    ::init();
    add_action(burn_redfang_camp, "burn");
} /* init */

