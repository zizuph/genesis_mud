/*
 * /d/Gondor/ithilien/emyn-arnen/hid_cellar.c
 * Contains hidden ranger heal spell scroll
 * Modifications:
 *    Tigerlily, 4-22-2004: updated scroll reference for recode
 */

inherit "/std/room";

#include <language.h>
#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>
#include "/d/Gondor/defs.h"

#define MIN_AWARENESS      35
#define ENTRANCE          (ITH_DIR+"emyn-arnen/cellar4")
#define DIRS              ({"north", "northeast", "east", "southeast", \
                           "south", "southwest", "west", "northwest", })

#ifndef NEW_RANGERS_OPEN
#define RANGER_SCROLL     (RANGER_DIR + "spells/obj/heal_scroll")
#endif
//else
#ifdef NEW_RANGERS_OPEN
#define RANGER_SCROLL  "/d/Gondor/guilds/rangers/spells/obj/heal_scroll"
#endif

void    reset_room();

int     scroll_found;

void
create_room()
{
    set_short("damp cellar");
    set_long(BSN("This is a hidden cellar, almost a small dungeon. "
      + "The owner of the hut hid his most valuable possessions "
      + "here, but even this hiding place did not escape sacking. "
      + "The ground is covered with old scrolls and books which "
      + "someone tried to burn here."));
    add_item(({"roof", "ceiling", }), BSN(
        "The roof is made from stones forming a circular vault with its "
      + "highest point at the center."));
    add_item(({"ground", "floor", }), BSN(
        "The floor is just earth that was stamped to make it level. "
      + "The ground is covered with old scrolls and books which someone "
      + "tried to burn here."));
    add_item(({"wall", "walls", "north wall", "northeast wall",
        "east wall", "southeast wall", "south wall", "southwest wall",
        "west wall", "northwest wall", }), BSN(
        "The walls are made of rough stone which was hewn into large "
      + "uneven blocks of different colours."));
    add_item(({"stone", "stones", "blocks", }), VBFC_ME("stone_colour"));
    add_item(({"scrolls", "books", "papers", "ashes", "heap", }), BSN(
        "A large heap of old scroll and the sad remains of many books "
      + "is lying on the ground. Obviously, someone put them all onto "
      + "the heap to burn them, and it looks as if he was quite "
      + "successful. Most of the scrolls and books on the top of the "
      + "heap are torn to shreds or burnt to ashes and it does not "
      + "look as if anything could have survived deeper inside the heap."));
    add_item(({"slab", "stone slab", "boulder", "door", }),
        "Perhaps you should try to push the wall in which you found "
      + "the stone slab?\n");

    add_prop(ROOM_I_LIGHT, 0);
    add_prop(ROOM_I_INSIDE, 1);
    add_prop(OBJ_S_SEARCH_FUN, "do_search");

    FIX_EUID
    reset_room();
}

void
reset_room()
{
    scroll_found = 0;
}

string
do_search(object pl, string str)
{
    object  ob;

    if (!strlen(str) || (member_array(str,
        ({"scrolls", "books", "papers", "heap", "ashes",})) == -1))
        return 0;

    if ((scroll_found) || 
        (MIN_AWARENESS > TP->query_skill(SS_AWARENESS)))
        return "You search through the heap of papers and ashes, " +
               "but you don't find anything interesting.\n";

    ob = clone_object(RANGER_SCROLL);
    if (ob->move(pl))
        if (ob->move(TO))
            ob->move(TO, 1);
    scroll_found = 1;
    tell_room(TO, QCTNAME(pl)+" finds "+LANG_ASHORT(ob)+" in the heap "
      + "of papers and ashes.\n", pl);
    return "You search through the heap of papers and ashes and find "
      + LANG_ASHORT(ob)+".\n";
}

string
query_seed_dir(string name)
{
    int     n;
    string  dir;

    dir = ENTRANCE->query_seed_dir(TP->query_name());
    n = member_array(dir, DIRS);
    return DIRS[(n+4)%8];
}

string
stone_colour()
{
    int     n;
    string  dir;
    mixed   exits = query_exit();

    if ((n = member_array(ENTRANCE, exits)) >= 0)
        return BSN("The walls are made from stone blocks roughly "
          + "hewn from rock of different colours. In the "
          + exits[n+1] + " wall, there is a doorway leading "
          + "out.");

    dir = query_seed_dir(TP->query_name());

    return BSN("The walls are made from stone blocks roughly hewn from "
      + "rock of different colours. The "+dir+" wall looks somehow "
      + "different from the other walls, and when you examine it "
      + "closely, you notice that in its center there is single "
      + "large stone slab looking almost like a door.");
}

void
init()
{
    ::init();

    add_action("do_push", "push");
    add_action("do_push", "press");
}

int
do_push(string str)
{
    string  vb = query_verb(),
            dir,
            odir,
            xdir;

    if (!strlen(str))
        NFN0(CAP(vb)+" what?");

    if (str == "slab" || str == "stone slab")
        NFN0("If you want to "+vb+" the stone slab, "+vb+
            " the wall in which you found it.");

    if (str == "wall" || str == "walls")
        NFN0(CAP(vb)+" which wall?");

    if (sscanf(str, "%s wall", dir) != 1)
        NFN0(CAP(vb)+" what?");

    xdir = query_seed_dir(TP->query_name());
    if ((dir != xdir) ||
        (member_array(ENTRANCE, query_exit()) > -1))
    {
        write("You "+vb+" against the "+dir
            +" wall, but nothing happens.\n");
        say(QCTNAME(TP)+" "+vb+"es against the "+dir
            +" wall, but nothing happens.\n");
    }
    else
    {
        write(BSN("As you "+vb+" against the "+xdir+" wall, the "
          + "stone block suddenly recedes into the wall revealing "
          + "a hidden doorway."));
        say("As "+QTNAME(TP)+" "+vb+"es against the "+xdir
          + " wall, the stone block suddenly recedes into the "
          + "wall revealing a hidden doorway.\n");
        odir = ENTRANCE->query_seed_dir(TP->query_name());
        add_exit(ENTRANCE, xdir, "@@pass_door|"+odir+"@@", 1);
        ENTRANCE->add_exit(file_name(TO), odir, 
            "@@pass_door|"+odir+"@@", 1);
    }
    return 1;
}

void
remove_cellar_exit(string dir)
{
    ENTRANCE->remove_cellar_exit(dir);
}

int
pass_door(string xdir)
{
    write("You pass through the doorway out of the hidden cellar.\n");
    set_alarm(5.0, 0.0, "remove_cellar_exit", xdir);
    return 0;
}

