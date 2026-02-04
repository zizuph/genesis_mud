/* This comment tells emacs to use c++-mode  -*- C++ -*- */

/*
 * cave11.c
 *
 * Red Dragon Lair
 * Tomas  -- Dec. 1999
 */

#include "/d/Terel/include/Terel.h"
inherit MOUNTAIN_DIR + "redlair/cave_room";
#include <macros.h>
#include <formulas.h>
#include <wa_types.h>
#include <ss_types.h>
#include <cmdparse.h>
#include <composite.h>
#include <filter_funs.h>
#define DRAGONFIRE "_terel_dragonfire"


/*
 * Function name: create_room
 * Description:   Default constructor
 */
public void
create_room()
{
    ::create_room();
    set_long("The main path ends here. To the north and south are " +
           "smaller caverns. Towards the east the cavern widens and a light " +
           "can be seen. " +
           "You feel a sense of extreme dread. The temperature here " +
           "is extremely hot. Perhaps, it isn't too late to turn back now.\n");
    
    DARK;
    
    add_exit(MOUNTAIN_DIR + "redlair/cave10", "west");
    add_exit(MOUNTAIN_DIR + "redlair/cave12", "east");
    add_exit(MOUNTAIN_DIR + "redlair/cave13", "north");
    add_exit(MOUNTAIN_DIR + "redlair/cave14", "south");

    

    reset_room();
}

/*
 * Function name: smell_desc
 * Description:   What does the air smell like here?
 * Returns:       The description of the smell
 */ 
public string
smell_desc()
{
    return "It smells like a sulfur furnace from hell in here!\n";
}


public string
touch_desc()
{
    return "The walls are very hot! Its extremely warm here.\n";
}


int 
bake(object me)
{
    object *room_list;
    mixed* hitresult;
    int  hurt, i;
    string how;
    me = find_object(MOUNTAIN_DIR + "redlair/monster/dragon");

    room_list=FILTER_LIVE ( all_inventory(TO) );

    for (i=0; i<sizeof(room_list); i++) 
    {
        hurt = F_PENMOD(200, 150 + random(50));
        hurt -= hurt * room_list[i]->query_magic_res(MAGIC_I_RES_FIRE) / 100;
        if(room_list[i]->query_prop(DRAGONFIRE))
            hurt = 0;
     
        hitresult = room_list[i]->hit_me(hurt, MAGIC_DT, me, -1);

        how = "miss";
        if (hitresult[0] > 0)
            how = "singe";
        if (hitresult[0] > 20)
            how = "burn";
        if (hitresult[0] > 50)
            how = "ignite";
        if (hitresult[0] > 100)
            how = "incinerate";
        room_list[i]->catch_msg("Flames erupt from the west engulfing the room!\n");
        room_list[i]->catch_msg("The flames " + how + " you.\n");
        if(room_list[i]->query_hp() <= 0)
            room_list[i]->do_die(me);
    }
    return 0;
}


