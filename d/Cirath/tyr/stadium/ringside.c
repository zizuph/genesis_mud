inherit "/std/room";
inherit "/cmd/std/command_driver";

#include "defs.h"
#include <living_desc.h>
#include <state_desc.h>
#include <composite.h>
#include <filter_funs.h>

#include "/d/Cirath/common/mobber.h"

#define GLANCEARENA (TYR_STADIUM+"stadium")
 
void
reset_room()
{
    bring_room_mob("audience", TYR_NPC+"aren_mob.c", 1);
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
   add_prop(ROOM_M_NO_ATTACK,"Start a fight here? Are you nuts???\n");
    add_prop(ROOM_M_NO_MAGIC_ATTACK,"Start a fight here? "+
    "Are you nuts???\n");

    add_exit(TYR_STADIUM+"stadium.c", "arena", 0, 1);
    reset_room();

}

void
init()
{
    ::init();
    add_action("glance", "glance");
	add_action("health", "health");
}
 
mixed
return_obj_in_seats()
{
    return (all_inventory(TO));
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

/* get_proc_text and show_subloc_health copied from /cmd/live/state.c  */

private varargs string
get_proc_text(int num, mixed maindesc, int turnpoint, mixed subdesc)
{
    int a, b, c, d,j;
    mixed subs;

    if (!sizeof(maindesc))
	return ">normal<";

    if (num < 0)
	num = 0;
    if (num > 99)
	num = 99;

    j = sizeof(maindesc) * num / 100;    
    
    if (!pointerp(subdesc))
	subs = SD_STAT_DENOM;
    else if (sizeof(subdesc))
	subs = subdesc;
    else
	return maindesc[j];

    a = num - (j * 100 / sizeof(maindesc));

    b = (sizeof(subs) * a * sizeof(maindesc)) / 100;

    if (j < turnpoint)
	b = (sizeof(subs) - 1) - b;

    return subs[b] + maindesc[j];
}

private string
show_subloc_health(object on, object for_obj)
{
    int hp, mhp;

    hp = on->query_hp();
    mhp = on->query_max_hp();
    if (mhp == 0)
	mhp = 1;

    return get_proc_text((hp * 100) / mhp, SD_HEALTH, 0, ({}) );
}


private int
health_arena()
{
 object *obs, *people;
 int i, size;

 obs = FILTER_LIVE(GLANCEARENA->return_obj_in_arena());
 people = FILTER_CAN_SEE(obs,this_player());

 size = sizeof(people);

 if(size < 1)
 {
  write("You cannot see anyone in the arena!\n");
 }
 else
 {
  for(i = 0; i < size; i++)
  {
   write(people[i]->query_The_name(this_player()) + " is " +
         show_subloc_health(people[i], this_player()) + ".\n");
  }
 }

 return 1;
}

public int
health(string str)
{
 if(str == "arena") return health_arena();
 return 0;
}

