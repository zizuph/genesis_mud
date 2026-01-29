inherit "/std/room";

#include <language.h>
#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>
#include "/d/Gondor/defs.h"

#define MIN_AWARENESS		25
#define ITEM_ARRAY		({ (WEP_DIR + "knife"), \
                        	   (WEP_DIR + "hatchet"), \
                        	   (WEP_DIR + "qstaff"), \
				   (ARM_DIR + "fjacket"), \
				   (EDORAS_DIR + "obj/leather"), \
				   (EDORAS_DIR + "obj/robe"), \
				   (EDORAS_DIR + "obj/leathcoat"), \
				   (EDORAS_DIR + "obj/diamond"), \
                                   (OBJ_DIR + "pan"), \
                                   (OBJ_DIR + "oilflask"), \
                                   (OBJ_DIR + "oilflask"), \
                                   (OBJ_DIR + "torch"), \
                                   (OBJ_DIR + "torch"), \
				})
#define DIRS	({"north", "northeast", "east", "southeast", \
		  "south", "southwest", "west", "northwest", })
#define HIDDEN_CELLAR		(ITH_DIR+"emyn-arnen/hid_cellar")

void    reset_room();

int     c;

void
create_room()
{
    set_short("damp cellar");
    set_long(BSN("This is a cellar under the hut. It is almost circular, "
      + "so that you cannot make out a corner anywhere. Halfway to the "
      + "northern end stands a rickety ladder leading up. In the middle "
      + "of the room lies a large heap of broken boards, shards, dirt, "
      + "and other unrecognizable items."));

    add_item(({"ladder", "rickety ladder"}), BSN(
        "The ladder is leading up back to the ground floor of the "
      + "hut. It does not look very strong but since it carried you "
      + "when you climbed down on it, it will probably be strong "
      + "enough to let you leave again."));
    add_item(({"roof", "ceiling", }), BSN(
        "The roof is made from stones forming a circular vault with its "
      + "highest point at the center. Halfway between the center and "
      + "the northern wall there is a hole in the roof, with a ladder "
      + "underneath leading up through the hole to the ground floor."));
    add_item(({"ground", "floor", }), BSN(
        "The floor is just earth that was stamped to make it level. "
      + "In the middle of the room, a large heap of refuse is lying "
      + "on the ground."));
    add_item(({"wall", "walls", "north wall", "northeast wall",
        "east wall", "southeast wall", "south wall", "southwest wall",
        "west wall", "northwest wall", }), BSN(
        "The walls are made of rough stone which was hewn into large "
      + "uneven blocks of different colours."));
    add_item(({"stone", "stones", "blocks", }), VBFC_ME("stone_colour"));
    add_item(({"pile", "heap", "shards", "dirt", "garbage", "refuse"}), BSN(
        "The pile of refuse is made up from broken boards, plain dirt, "
      + "shards from bottles and earthenware, and other unrecognizable "
      + "items. And that is just what is visible on the top of the "
      + "pile. Who knows what might be hidden below?"));
    add_item(({"slab", "stone slab", "boulder", }),
        "Perhaps you should try to push the wall in which you found the "
      + "stone slab?\n");

    add_prop(ROOM_I_LIGHT, 0);
    add_prop(ROOM_I_INSIDE, 1);
    add_prop(OBJ_S_SEARCH_FUN, "do_search");

    FIX_EUID
    clone_object(ITH_DIR + "emyn-arnen/obj/h4down_door")->move(TO);

    add_exit(ITH_DIR + "emyn-arnen/house4", "up", 0, 4);
    reset_room();
}

varargs int
query_seed(string name)
{
    int     i,
            seed = 0;

    if (!strlen(name))
        name = TP->query_name();

    for (i = 0; i < strlen(name); i++)
        seed += name[i];

    return seed;
}

string
query_seed_dir(string name)
{
    int     seed;

    if (!strlen(name))
        name = TP->query_name();

    seed = query_seed(name);

    return DIRS[random(sizeof(DIRS), seed)];
}

string
do_search(object pl, string str)
{
    int     as;
    object  ob;
    string  dir,
            xdir;

    if (!strlen(str))
        return 0;

    if (str == "wall" || str == "walls")
        return BSN("You search the walls, but you do not find "
          + "anything. Perhaps you would be more successful " 
          + "if you decided to search one wall at a time.");
    if (sscanf(str, "%s wall", dir) == 1)
    {
        xdir = query_seed_dir(TP->query_name());
        if (dir != xdir)
            return "You search the "+str+
                ", but you cannot find anything interesting.\n";
        else
        {
            return BSN("When you examine the "+str+" closely, "
              + "you notice that in its center there is single "
              + "large stone slab looking almost like a door.");
        }
    }
    else if (member_array(str,
        ({"refuse", "pile", "heap", "dirt", "garbage", })) == -1)
        return 0;

    if ((((as = pl->query_skill(SS_AWARENESS)) < MIN_AWARENESS) && 
        random((100 - as + MIN_AWARENESS)/MIN_AWARENESS*2)) || (c == 0))
        return "You search through the pile of refuse, " +
               "but you don't find anything interesting.\n";

    ob = clone_object(ONE_OF_LIST(ITEM_ARRAY));
    if (ob->move(TO))
        ob->move(TO, 1);
    c--;
    return "You search through the pile of refuse and find "+LANG_ASHORT(ob)+".\n";
}

string
stone_colour()
{
    string  dir;

    dir = query_seed_dir(TP->query_name());

    return BSN("The walls are made from stone blocks roughly hewn from "
      + "rock of different colours. The "+dir+" wall looks somehow "
      + "different from the other walls, but you cannot say what "
      + "it is that makes it different.");
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
    int     n;
    string  vb = query_verb(),
            dir,
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

    if (member_array(dir, DIRS) == -1)
    {
        NFN0("There is no such thing as "
          + LANG_ADDART(dir) + " wall to " + vb + ".");
    }
    xdir = query_seed_dir(TP->query_name());
    if ((dir != xdir) ||
        (member_array(HIDDEN_CELLAR, query_exit()) > -1))
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
        add_exit(HIDDEN_CELLAR, xdir, "@@pass_door|"+xdir+"@@", 1);
        n = member_array(xdir, DIRS);
        HIDDEN_CELLAR->add_exit(file_name(TO), DIRS[(n+4)%8], 
            "@@pass_door|"+xdir+"@@", 1);
    }
    return 1;
}

void
remove_cellar_exit(string xdir)
{
    int     n;
    string  odir;

    if (member_array(HIDDEN_CELLAR, query_exit()) == -1)
        return;
    tell_room(TO, BSN("The stone block in the "+xdir+" wall moves "
      + "back into its old position, closing the doorway leading "
      + xdir +"."));
    remove_exit(xdir);
    n = member_array(xdir, DIRS);
    odir = DIRS[(n+4)%8];
    HIDDEN_CELLAR->remove_exit(odir);
    tell_room(HIDDEN_CELLAR, BSN("The stone block in the "
      + odir +" wall moves back into its old position, "
      + "closing the doorway leading " + odir +"."));
}

int
pass_door(string xdir)
{
    write("You pass through the doorway into the hidden cellar.\n");
    set_alarm(5.0, 0.0, "remove_cellar_exit", xdir);
    return 0;
}

void
reset_room()
{
    int     i;
    mixed   exits = query_exit();

    c = random(3) + 1;

    if ((i = member_array(HIDDEN_CELLAR, exits)) >= 0)
        remove_cellar_exit(exits[i+1]);
}

