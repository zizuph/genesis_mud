inherit "/std/room";
#include "defs.h"
#include <living_desc.h>
#include <composite.h>
#include <filter_funs.h>

#include "/d/Cirath/common/mobber.h"

#define GLANCEARENA (STADIUM+"stadium")
 
void
reset_room()
{
    bring_room_mob("audience", ATH_PERSON+"aren_mob.c", 1);
}
 
create_room()
{
    set_short("the sun seats");
    set_long("Sitting as they do as close to the blistering sun and as "+
             "far from the arena as any of the seats, these have earned "+
             "a reputation of attracting the rowdiest arena denizens "+
             "and being a good place to suffer heat stroke. Long stone "+
             "benches are supported by squat ionic columns, though most "+
             "of the audience here prefers to stand. The entrance to the "+
             "stands southeast has been temporarily blocked off, but a "+
             "makeshift connection down to the arena has been built.\n"+
             "You may 'glance' into the arena, even at specific things that "+
             "are there.\n");
 
    add_item(({"bench", "benches"}), "They look pretty uncomfortable.\n");
 
    ADD_SUN_ITEM

    add_exit(STADIUM+"stadium.c", "arena", 0, 1);
    reset_room();

}

void
init()
{
    ::init();
    add_action("glance", "glance");
}
 

int
glance(string str)
{
    object glancee, *inv, *obs, *ppl;
    string desc, *ctants;
    int i;

    if (!strlen(str))
    {
        write(GLANCEARENA->long());
        inv = (GLANCEARENA->return_obj_in_arena());
	obs = FILTER_SHOWN(FILTER_DEAD(inv));
        ppl = FILTER_LIVE(inv);
 
        if (strlen(desc = (string) COMPOSITE_FILE->desc_dead(obs, 1)))
        write(desc + ".\n");
 
        if (strlen(desc = (string) COMPOSITE_FILE->desc_live(ppl, 1)))
        write(desc + ".\n");
 
        for (i = 0; i < sizeof(ppl); i++)
        {
            ctants = map(ppl[i]->query_enemy(-1), "fights", this_object(),
            ppl[i]);
 
            if (sizeof(ctants))
            ctants -= ({ 0 });
 
            if (sizeof(ctants) == 1)
              desc = LD_FIGHT1(ctants[0]);
            else if (sizeof(ctants) > 1)
              desc = LD_FIGHT_MANY(ctants);
            else
              desc = 0;
 
            if (desc)
              write(LD_FIGHT_DESC(desc, ppl[i]));
         }
         return 1;
    }
 
    if(glancee = (GLANCEARENA->return_in_arena(str)))
    {
        write(glancee->long());
        return 1;
    }
    write("Glance at what in the arena?\n");
    return 1;
}
