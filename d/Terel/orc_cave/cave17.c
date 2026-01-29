/* This comment tells emacs to use c++-mode  -*- C++ -*- */

/*
 * cave10.c
 *
 * A cave room that is home to a large wolf.
 */

#include "/d/Terel/include/Terel.h"
inherit ORC_CAVE_DIR + "cave_room";
#include <macros.h>
#include <formulas.h>
#include <wa_types.h>
#include <ss_types.h>
#include <cmdparse.h>
#include <composite.h>
#include <filter_funs.h>
#define DRAGONFIRE "_terel_dragonfire"


public void
create_room()
{
    ::create_room();
    set_long(query_long() + 
        "The ground here is burnt and charred beyond belief. "+
        "A larger cave is to your east or you can follow the "+
        "tunnel back to the west.\n");

    add_item("fireflies",
	     "You stop to look at the dazzling dance of the fireflies.\n");
    
    add_item(({"window","glass","glass window"}),
	     "It is securely embedded in the wall.\n");

    add_exit(ORC_CAVE_DIR + "cave11", "west");
    add_exit(ORC_CAVE_DIR + "cave16", "east");
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
    return "There is a faint smell foul creatures and an overpowering " +
	"smell of fire and sulfur.\n";
}
int 
bake(object me)
{
    object *room_list;
    mixed* hitresult;
    int  hurt, i;
    string how;
    me = find_object(ORC_CAVE_DIR + "monster/dragon");

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


