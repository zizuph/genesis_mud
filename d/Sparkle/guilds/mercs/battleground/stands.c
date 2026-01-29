inherit "/std/room";
inherit "/cmd/std/command_driver";

#include "../merc.h"
#include <living_desc.h>
#include <state_desc.h>

#define GLANCEARENA (MBATTLE + "battlegrounds")
 
void
reset_room()
{
}
 
create_room()
{
    set_short("The stands overlooking the arena");
    set_long("You are in the stands that overlook the arena from the northern "+
	"side. To the south, beyond the arena, you spot the entrance to the "+
	"mercenary halls. To the west, you see a fenced off area. Behind the "+
	"stands, to the north, a river forms a natural boundary, beyond which "+
	"are plains to which no end can be seen from here. "+
        "You may 'watch' the arena, even specific things that "+
        "are there.\n");
 
    add_item(({"area", "west", "fenced off area", "fence"}), "You see a "+
	"large fenced off area, in which there are many dogs. There are "+
	"several humans tending to them.\n");
    add_item(({"river", "north", "plains"}), "The river curves around the back "+
	"side of the stands, extending to the east and west for as far as you "+
	"can see. Beyond the river, there are plains.\n"); 

    add_prop(ROOM_M_NO_ATTACK,"Combat belongs in the arena, not the stands!\n");
    add_prop(ROOM_M_NO_MAGIC_ATTACK,"Combat belongs in the arena, not the "+
	"stands!\n");

    add_exit(MBATTLE + "battlegrounds.c", "arena", 0, 1);
    reset_room();
}

void
init()
{
    ::init();
    add_action("glance", "watch");
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

    if (!strlen(str) || str == "arena" || str == "below" || str == "stadium")
    {
        write(GLANCEARENA->long());
        inv = (GLANCEARENA->return_obj_in_arena());
	obs = FILTER_SHOWN(FILTER_DEAD(inv));
        ppl = FILTER_LIVE(inv);
 
        if (strlen(desc = (string) COMPOSITE_FILE->desc_dead(obs, 1)))
        write(capitalize(desc) + ".\n");
 
        if (strlen(desc = (string) COMPOSITE_FILE->desc_live(ppl, 1)))
        write(capitalize(desc) + ".\n");
 
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
    write("Watch what in the arena?\n");
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
