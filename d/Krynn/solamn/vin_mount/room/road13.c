/* created by Aridor 06/19/93 */

#include "../local.h"

inherit ROOM_BASE

#include RND_MEET

object* monster = ({ });

void
init()
{
    object mon;

    ::init();
    if (random(50) > 1)
        return;
    mon = RANDOM_MEET(TABLE);
    mon->move_living("xx",TO);
    monster += ({ mon });
}

void
reset_vin_mount_room()
{
    monster -= ({ 0 });
    if (monster && sizeof(monster))
    {
    monster->command("emote leaves.");
    monster->remove_object();
    monster = ({});
    }
}

void
create_vin_mount_room()
{

    set_short("End of the Vale");
    set_long("You are in the northern end of the Vale "
        +    "with a mountain track leading up into the rocks "
        +    "to the north and to the southwest a cozy vale "
        +    "spreads out before your eyes. Another track is leading " +
         "south into the mountains.\n");

    OUTSIDE;

    add_exit(ROOM + "road10","north",0,20);
    add_exit(ROOM + "road14","southwest",0,10);
    add_exit(DRAGON,"south","@@no_go@@",20);

    add_item("vale",
         "It is a lovely vale, no noise can be heard except " +
        "the singing of birds and the occasional rustle of " +
        "some small animal.\n");
    add_item(({"bird","birds","animal","animals"}),
         "You can hear sounds but you " +
        "cannot see anything.\n");
    add_item(({"track","ground","road","gravel","mountain track"}),
         "The road into the vale is covered with " +
        "grass, the track leading up into the mountains is simply " +
        "laid out with small stones and gravel.\n");
    add_item(({"mountains","mountain"}),
         "These are high mountains indeed, rocks and occasional " +
        "shrubs are scattered everywhere, it is definitely " +
        "a very hostile area.\n");
    add_item(({"shrubs","rocks"}),
         "The mountainsides are covered with rocks with a few " +
        "shrubs making their living in between.\n");

}

//Hack
//Tibbit, 22 April 1998
int
no_go()
{
    write("You decide not to pursue the southbound track "+
        "at this time, as it looks rather "+
        "slippery.\n");

    return 1;
}


