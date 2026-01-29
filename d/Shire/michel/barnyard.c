inherit "/d/Shire/room";

#include "/d/Shire/common/defs.h"

#include <macros.h>
#include <stdproperties.h>
#include <ss_types.h>

void get_hay();

void
reset_room()
{
    object beam;

    if(!present("beam"))
    {
        beam = clone_object("/d/Shire/michel/obj/beam");
        beam->move(TO);

    }
}

create_room() 
{
    add_prop(ROOM_S_MAP_FILE, "michel_delving.txt");
    set_short("A barnyard");
    set_long("You have entered the barnyard of this farm, but "+
            "the barn-door seems securely shut, and you are pinned in "+
            "between some cattle pens, the barn, the farmhouse and "+
            "hay bales. The only way out is the way you came in.\n");

    add_item(({"barnyard","yard","farm","barn-door"}),
            "The barnyard is covered with bits of hay, and it "+
            "must have come from this farm.\n"+
            "The barn-door is securely closed.\n");

    add_item(({"pen","cattle pen","barn","farmhouse","hay","hay bales"}),
            "You are cut off by the barn on the south end, the farmhouse on the north, "+
            "the cattle pens on the east side and a high stack "+
            "of hay bales on the west.\n"+
            "You can see some hay scattered on the ground, ungathered.\n");
    add_exit(MICH_DIR + "farmhouse","in",0,1);

    reset_room();
}

init() {
    ::init();
    add_action("do_gath","gather",0);
    add_action("do_open","open",0);

}

int
do_gath(string str) 
{
    object thing;
    notify_fail(capitalize(query_verb()) + " what? \n");
    if (str!="hay")
        return 0;
    write("You start gathering some dry hay from the ground. \n");
    say(QCTNAME(this_player()) + " starts gathering some hay. \n");
    set_alarm(5.0,0.0, &get_hay());
    return 1;
}

void
get_hay() 
{
    object hayheap;
    hayheap = clone_object(MICH_DIR + "obj/hay");
    if (hayheap->move(this_player())) {
        write("You fail to carry the hay.\n");
        hayheap->remove_object();
    } else 
        write("You have gathered a big enough heap of hay. \n");
}

int
do_open(string str)
{

    if(str == "door")
    {
        write("The farmer wants his door closed, leave it be.\n");
        return 1;
    }
    else
    {
        NF("Open what?\n");
    }

    return 0;

}
