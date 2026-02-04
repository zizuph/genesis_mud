/*
 * cave_room.c
 *
 * A generic troll cave room.  All the troll caves rooms should inherit this
 * file.
 *
 * Lucius - Jan 2021
 *    Cleanup and modernized.
 *    Moved guarded() function here.
 *    Added a time delay to prevent mass spamming to
 *      avoid blocking.
 *    Mask add_npc to do auto-troll-teaming
 */
#include "/d/Terel/include/Terel.h"
inherit STDROOM;
#include <ss_types.h>

#define DELAY    3
#define BLOCK_T  "_troll_block_time"

public void
hook_smelled(string str)
{
    if (!strlen(str))
        write("A damp, fetid stench permeates the air.\n");
}

/*
 * Function name: create_room
 * Description:   Default constructor
 */
public void
create_terel_room()
{
    set_short("a dark cave above the moors of northern Terel");
    set_long("You are in a cave high above the moors of northern Terel. "+
      "These caves seem to belong to trolls that wander the "+
      "moors below. The fetid stench of the beasts can be smelled "+
      "well before even entering the caves. ");

    add_item(({"stalagmites", "stalagmite"}),
      "They vary in size and are a bit lighter in colour than the " +
      "ground from which they come.\n");

    add_item(({"stalagtites", "stalagtite"}),
      "Hanging down from the ceiling, they have a rough texture. " +
      "Some of them drip water onto the cavern floor.\n");

    add_item(({"wall", "walls"}),
      "The walls have the same rough texture as " +
      "the stalagmites, but are darker in colour.\n");

    DARK;
    INSIDE;
}

public int
guarded()
{
    if (TP->query_prop(OBJ_I_INVIS))
        return 0;

    object troll = present("_terel_cave_troll");
    if (!objectp(troll))
    {
        TP->add_prop(BLOCK_T, 0);
        return 0;
    }

    int last = TP->query_prop(BLOCK_T);
    if ((last + DELAY) > time())
    {
        write(troll->query_The_name(TP) +" is standing in your way.\n");
        say(QCTNAME(troll) +" stands in " + QTNAME(TP) +"'s way.\n");
        return 1;
    }

    if ((TP->query_stat(SS_INT) + TP->query_stat(SS_WIS)) >
        (troll->query_stat(SS_STR) + troll->query_stat(SS_DEX) -
            random(100)))
    {
        return 0;
    }

    TP->add_prop(BLOCK_T, time());
    write(troll->query_The_name(TP) +" is standing in your way.\n");
    say(QCTNAME(troll) +" stands in " + QTNAME(TP) +"'s way.\n");
    return 1;
}

public void
team_up(object ob)
{
    if (!objectp(ob))
        return;

    object troll = present("_terel_cave_troll");

    if (!objectp(troll))
        return;

    object leader = troll->query_leader();
    if (objectp(leader))
        leader->team_join(ob);
    else
        troll->team_join(ob);
}

public varargs void
add_npc(string file, int count = 1, function init_call = 0)
{
    if (!functionp(init_call))
        init_call = TO->team_up;

    ::add_npc(file, count, init_call);
}
