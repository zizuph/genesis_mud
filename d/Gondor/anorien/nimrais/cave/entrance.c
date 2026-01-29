/*
 *	/d/Gondor/anorien/nimrais/cave/entrance.c
 *
 *	December 1995, Olorin
 */
#pragma strict_types

inherit "/d/Gondor/common/room.c";

#include <language.h>
#include <macros.h>
#include <stdproperties.h>

#include "/d/Gondor/defs.h"

#define RANDOM_OBJECT	({WEP_DIR+"knife",WEP_DIR+"stick",WEP_DIR+"fssword",\
                  WEP_DIR+"qstaff",WEP_DIR+"hatchet",EDORAS_DIR+"obj/fknife",})

public void   reset_room();

object *wolf = allocate(2 + random(3));

public void
create_room()
{
    set_short("a damp cave");
    set_long(BSN("The floor of this cave is covered with damp hay and leaves. "
      + "The roof slopes down towards the back of the cave. An almost circular "
      + "hole is leading outside."));

    add_item(({"ground", "floor", }), BSN("The ground is covered by damp hay "
      + "and leaves. The rock floor is visible only just in front of the hole "
      + "leading out."));
    add_item(({"roof", "ceiling", }), BSN("The roof just barely allows you to "
      + "stand upright here. Towards the back of the cave, it slopes down, "
      + "casting the parts of the cave farther from the hole into dark and "
      + "impenetrable shadows."));
    add_item(({"hole", "exit", }), BSN("The hole leading outside is in the "
      + "southeast wall of the cave. It is shaped almost as a circle, so "
      + "that you will have to stoop low if you want to leave through it."));
    add_item(({"leaves", "hay", }), BSN("The leaves and the hay look as "
      + "if they have been carried into this cave by someone to build a "
      + "nest or lair."));
    add_item(({"back", "shadows", "back part", "farther parts", }), BSN(
        "The parts of the cave farther away from the entrance are in "
      + "dark shadows. It is impossible to determine how far the cave "
      + "continues deeper into the mountain. And the low-hanging roof "
      + "makes it impossible to walk further into the cave."));
    add_item(({"cave", }), BSN(
        "The cave is high enough to stand here. It extends further back "
      + "towards the north, but the roof slopes down and the back of the "
      + "cave is cast into deep and impenetrable shadows."));

    add_exit(ANO_DIR + "nimrais/rimvalley6", "southeast", "@@exit_msg@@", 1);
    add_prop(ROOM_I_INSIDE, 1);
    add_prop(OBJ_S_SEARCH_FUN, "do_search");
    add_prop(OBJ_I_SEARCH_TIME, 5);

    reset_room();
}

public string
do_search(object tp, string str)
{
    object  obj;

    if (!objectp(tp) || !present(tp, TO))
        return 0;
    if (!strlen(str))
        return 0;

    str = LOW(str);
    switch (str)
    {
        case "leaves":
        case "hay":
            if (query_searched())
                return "You search through the "+str+" covering "
                  + "the ground, but you do not find anything noteworthy.\n";
            set_searched(1);
            obj = ONE_OF_LIST(RANDOM_OBJECT);
            if (obj->move(tp))
            {
                if (obj->move(TO))
                    obj->move(TO, 1);
            }
            return "Hidden among the pile of damp leaves and hay, you find "
              + LANG_ASHORT(obj) + ".\n";
            break;
        default:
            return 0;
            break;
    }
}

public int
exit_msg()
{
    write("Stooping low, you leave the damp cave.\n");
    return 0;
}

public int
do_crawl(string str)
{
    NFN("Crawl where?");
    if (!strlen(str))
        return 0;

    str = LOW(str);

    if (!parse_command(str, ({}),
        "[further] [in] [into] [the] [back] 'cave' / 'north' / 'part' / 'shadows'"))
        return 0;

    switch ((ANO_DIR + "nimrais/cave/tunnel2")->query_heap_state())
    {
    case 0:
        write("You crawl north into the back part of the cave.\n");
        TP->move_living("crawling north into the back of the cave",
            ANO_DIR + "nimrais/cave/back");
        break;
    case 1:
    case 2:
        write("Due to the tremendous roar and dust coming from the back "
          + "of the cave, you decide that it would be in the best interest "
          + "of your continues existence not to enter that part of the cave.\n");
        say(QCTNAME(TP)+" crawls around on the ground.\n");
        break;
    case 3:
    default:
        write("You try to crawl north further into the cave, but you find "
          + "that the back of the cave is completely filled by a heap "
          + "of rocks and stones.\n");
        say(QCTNAME(TP)+" crawls around on the ground.\n");
        break;
    }
    return 1;
}

public void
init()
{
    ::init();

    add_action(do_crawl, "crawl");
}

public void
reset_room()
{
    int     i, s;
    object  wolf_leader = present("wolf", TO),
            dummy;

    if (objectp(wolf_leader) && 
        objectp(dummy = wolf_leader->query_leader()))
        wolf_leader = dummy;

    for (i = 0, s = sizeof(wolf); i < s; i++)
        if (!objectp(wolf[i]))
        {
            wolf[i] = clone_object(NPC_DIR + "wolf");
            wolf[i]->set_restrain_path(ANO_DIR + "nimrais");
            wolf[i]->move_living("down", TO);
            if (objectp(wolf_leader))
                wolf_leader->team_join(wolf[i]);
            else
                wolf_leader = wolf[i];
        }
}

