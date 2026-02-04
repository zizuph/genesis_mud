inherit "/std/room";
#include "/d/Terel/include/Terel.h"
#include <living_desc.h>
#include <composite.h>
#include <filter_funs.h>



#define GLANCEARENA (CALATHIN_DIR+"obj/stadium")
 
public void
create_room()
{
    set_short("Wooden stands");
    set_long("You're sitting on strong wooden benches that surround "+
                   "the field. The benches are well worn and rather "+
                   "comfortable. From here you can view the action on "+
                   "the field.\n");
 
 
    add_item(({"bench", "benches"}), "They look pretty uncomfortable.\n");
 
   add_prop(ROOM_M_NO_ATTACK,"Start a fight here? Are you nuts???\n");
    add_prop(ROOM_M_NO_MAGIC_ATTACK,"Start a fight here? "+
    "Are you nuts???\n");

    add_exit(CALATHIN_DIR+"obj/stadium","arena",0,1);
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
