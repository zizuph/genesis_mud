inherit "/d/Gondor/rohan/horn/helmsdeep.c";

#include "/d/Gondor/defs.h"
#include "/sys/stdproperties.h"
#include "/sys/macros.h"
#include "/sys/filter_funs.h"
#include "/d/Gondor/rohan/horn/hd_defs.h"
#include "/d/Gondor/common/mordor/sys/clock.h"

#define CLONK1 ROH_DIR + "horn/on_walls/i_wall1"
#define CLONK3 ROH_DIR + "horn/on_walls/i_wall6"
#define CLONK2 ROH_DIR + "horn/on_walls/o_wall6"
#define CLONK4 ROH_DIR + "horn/on_walls/o_wall7"

object orc;

void
reset_room()
{
    orc = clone_npc(orc, (ROH_DIR + "horn/npc/spy_orc"));
    orc->add_prop(OBJ_I_HIDE, 16);
}

int sunset();

void
create_helmsdeep_room()
{
    set_short("Inside the orc hide out");
    set_extra_long("This is the orc hide out. If you as mortal manage to "+
    "get to this room, please make a bug report.");
    add_prop(ROOM_I_INSIDE, 1);
    add_exit(WALL_ROOM, "northeast", 0);
    reset_room();
    CLOCK->notify_dusk(sunset);
}


int sunset()
{
    CLOCK->notify_dusk(sunset);
    if (orc->query_prop(SCARED_ORC))
    {
        return 0;
    }
    set_alarm(8.0, 0.0, "do_clonk");
    return 1;
}

int sunrise()
{
    return 1;
} 

int do_clonk()
{
    tell_room(CLONK1, "You hear a distant and somewhat muffled 'clonk'.\n");
    tell_room(CLONK2, "You hear a distant and somewhat muffled 'clonk'.\n");
    tell_room(CLONK3, "You hear a distant and somewhat muffled 'clonk'.\n");
    tell_room(CLONK4, "You hear a distant and somewhat muffled 'clonk'.\n");
    set_alarm(2.0, 0.0, "move_orc");
    return 1;
}

/*
 *  I need to make the quest a bit easier :(
 *
int check_people()
{   
    object *inv, *people, room;

    inv = ({});
    if ((room = find_object(WALL_ROOM)) != 0)
         inv += all_inventory(room);
 
    people = FILTER_LIVE(inv);
    if(sizeof(people) > 0)
    {
        return 0;
    }
    return 1;
}
 */
    
int move_orc()
{
    object *people;
    int i;

/*
    if (!check_people())
        return 0;
 */
    people = FILTER_LIVE(all_inventory(TO));
    for (i = 0; i < sizeof(people); i++)
    {
        if (people[i]->id("_spy_orc"))
        {
             people[i]->command("hide");
             people[i]->command("sneak northeast");
             return 1;
        }
    }
    return 1;
}

int brave_orc()
{
    object *people;
    int i;

    people = FILTER_LIVE(all_inventory(TO));
    for (i = 0; i < sizeof(people); i++)
    {
        if (people[i]->id("_spy_orc"))
        {
             people[i]->remove_prop(SCARED_ORC);
             return 1;
        }
    }
    return 0;
}
