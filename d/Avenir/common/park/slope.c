// file name:   slope.c
// creator(s):  Farlong
// last update: Lilith Feb 2002, removed aglyna landing here.
//              Lilith: updated typing and indentation.
//              Ilyian (8 March, 1995)
// purpose:
// note:        
// bug(s):
// to-do:

inherit "/std/room";
#include "/sys/stdproperties.h"
#include "/d/Avenir/include/relation.h"
#include "park.h"

void 
create_room()
{
    set_short("Downward slope");
    set_long("You stand on a narrow path which splits"
        +" here, leading away to the northeast, east and south."
        +" Low stone walls, now heavily eroded and crumbling slowly away"
        +" into dust, line the way, while heavy vines hang from overhead and"
        +" viscious plants and various undergrowth seem to grasp at your"
        +" ankles, almost as if possessing a will of their own."
        +" Little light is able to penetrate the thick canopy of growth"
        +" above and all around you. The way which once led northward has"
        +" been replaced by a sharp slope heading downward into"
        +" darkness.\n");

    add_exit(PK+"ne_path1","northeast",0);
    add_exit(PK+"square_rm","east",0);
    add_exit(PK+"s_path1","south",0);
    add_exit(PK+"dlord","down",0);

    add_prop(ROOM_I_LIGHT,1);
    IN

    add_item("path","The path leads away to"
        +" the northeast, east and south. It is narrow and overgrown with"
        +" weeds and other growth. The path was apparently made by"
        +" humanoid hands, though in a time long past.\n");
    add_item(({"stone","walls","wall","dust","stones"}),"The"
        +" narrow path is lined by low stone walls that have begun to crumble"
        +" away under time's great influence.\n");
    add_item(({"vines","vine","growth","plants","undergrowth",
        "canopy"}),"The vines, brush and other plant life"
        +" are all around you, constantly impeding your progress. They"
        +" seem almost driven to the task by some dark power.\n");

}

/*
void
summon()
{
    int num_players, num_steeds, how_many, i;
    object *steeds = ({});

    num_players = sizeof(FILTER_PLAYERS(all_inventory(TO)));
    num_steeds = sizeof(filter(all_inventory(TO), &->id("aglyna")));

    how_many = num_players - num_steeds;

    if(how_many <= 0)
    {
         return;
    }

    for(i = 0; i < how_many; i++)
        steeds += ({ clone_object("/d/Avenir/common/outpost/mon/aglyna") });

    steeds->move_living("M", TO);

    tell_room(TO, "Flying down from great heights, "
        + COMPOSITE_LIVE(steeds) + " descend" + (sizeof(steeds) == 1 ? "s" : "")
        + ".\n");

}

void
enter_inv(object to, object from)
{
    ::enter_inv(to, from);

    if(IS_SYBARITE(to))
       set_alarm(30.0, 0.0, summon);
}

*/