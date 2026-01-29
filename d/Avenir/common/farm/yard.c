#pragma strict_types
#include "/d/Avenir/common/common.h"
#include "./defs.h"
#include <stdproperties.h>
#include <filter_funs.h>
#include <composite.h>
#include <language.h>
#include <ss_types.h>
#include <macros.h>
#include <tasks.h>
#include <terrain.h>

#define LABAL "_friendly_status_labal"
#define RING_BITS 2, 0
#define FARM_BITS 2, 1
#define TROUT_BITS 2, 2

inherit "/std/room";

int maggots = 5;
int query_maggots();
int bug_off(object obj);

void
create_room()
{
    set_short("The stable yard");
    set_long("You stand on a small stable yard right in front " +
        "of what looks like a small stable. Opposite the " +
        "stable is a smaller building, which looks like " +
        "some kind of a tool shed. Behind the tool shed you " +
        "can see a small field surrounded by a fence.\n");
    add_item("stable","The stable looks exactly how a stable " +
        "usually looks like. It looks easy to enter through the door. " +
        "Behind it, you catch a glimpse of the dung heap.\n");
    add_item(({"dung heap","heap","dung"}),"@@exa_dung_heap");
    add_item(({"shed","tool shed","toolshed","building"}),"This " +
        "little building is much smaller than the stable which " +
        "is the main reason it looks like a tool shed. " +
        "Behind the shed is a small field surrounded by " +
        "a fence. The door to the shed has no lock so entering looks easy.\n");
    add_item("fence","@@desc_fence");
    add_item("field","@@desc_field");
    add_item("bull","@@desc_bull");
    add_prop(OBJ_S_SEARCH_FUN, "search_heap");
    set_terrain(TERRAIN_OPENSPACE);
    set_terrain(TERRAIN_OUTSIDE);
    add_exit("gate","north");
    add_exit("road1","south");
    set_terrain(TERRAIN_OPENSPACE);
    set_terrain(TERRAIN_OUTSIDE);

    reset_room();
}

void
reset_room()
{
    object labal;

    if (!present("_labal", this_object()))
    {
        labal = clone_object(THIS_DIR + "npc/servant");
        labal->move(this_object());
    }

    (THIS_DIR + "field")->teleledningsanka();
    maggots = 7;
}

void
init()
{
    ::init();
        add_action("climb_fence","climb");
        add_action("enter_stable","enter");
        add_action("enter_shed","enter");
        add_action("enter_field","enter");
        add_action("do_poke","poke");
        add_action("do_poke","dig");
        add_action("do_poke","stir");
        add_action("do_poke","turn");
        add_action("do_shake", "shake");
    add_action("do_shake","kick");
    add_action("do_use", "use");

}

int
climb_fence(string str)
{
if (!(str))
    return 0;

    if ((str == "fence") || (str == "over the fence") ||
        (str == "over fence"))
    {
        write("You climb over the fence.\n");
        say(({METNAME + " climbs over the fence into the small " +
            "field.\n",
            TART_NONMETNAME + " climbs over the fence into the small " +
            "field.\n",
            ""}), TP);
        tell_room(THIS_DIR + "field", ({METNAME + " arrives over " +
            "the fence.\n",
            TART_NONMETNAME + " arrives over " +
            "the fence.\n",
            ""}), TP);
        TP->move_living("M", THIS_DIR + "field", 1);
        return 1;
    }
    return 0;
}

int
enter_stable(string str)
{
    if ((str) && (str == "stable"))
    {
        write("You go into the stable.\n");
        say(({METNAME + " leaves into the stable.\n",
            TART_NONMETNAME + " leaves into the stable.\n",
            ""}), TP);

        tell_room(THIS_DIR + "stable",
            ({METNAME + " arrives through the door.\n",
            TART_NONMETNAME + " arrives through " +
            "the door.\n", ""}), TP);

        TP->move_living("M", THIS_DIR + "stable", 1);
        return 1;
    }
    return 0;

}

string
exa_dung_heap()
{
    string text;

    say(({METNAME + " takes a step towards the dung heap and " +
        "takes a closer look.\n",
        TART_NONMETNAME + " takes a step towards the dung heap and " +
        "takes a closer look.\n",
        ""}), TP);
    text = "The dung heap seems to have been untouched for a " +
        "long time. You catch the dry smell even from this " +
        "distance and the sight of it isn't very pretty.\n";
    return text;
}

int
enter_shed(string str)
{
    if ((str) && ((str == "tool shed") || (str == "shed")))
    {
        write("You enter the tool shed.\n");
        say(({METNAME + " leaves into the shed.\n",
            TART_NONMETNAME + " leaves into the shed.\n",
            ""}), TP);
        tell_room(THIS_DIR + "shed",
            ({METNAME + " arrives through the door.\n",
            TART_NONMETNAME + " arrives through " +
            "the door.\n", ""}), TP);
        TP->move_living("M", THIS_DIR + "shed", 1);
        return 1;
    }
    return 0;

}

int
enter_field(string str)
{

    if ((str) && ((str == "field")))
    {
        write("You think about entering the field but " +
            "there is no gate. The only way to get to " +
            "it, is to climb over the fence.\n");
        return 1;
    }
    if ((str) && (str == "field"))
        return 1;
    return 0;
}

string
desc_fence()
{
    string text, name;
    object field;
    object *ob;

    text = "Its a wooden fence about 6 feet high that surrounds " +
        "a small grass field behind the tool shed. You wonder if " +
        "it is as sturdy as it looks like.";

    field = find_object(THIS_DIR + "field");

    ob = FILTER_CAN_SEE(all_inventory(field), TP);
    if (!sizeof(ob))
    {
        text += "\n";
        return text;
    }
    text += " On the other side you can see "
         + COMPOSITE_WORDS(map(ob, "desc", TO)) + ".\n";
    say(({METNAME + " walks up to the wooden fence surrounding " +
        "the small grass field behind the tool shed.\n",
        TART_NONMETNAME + " walks up to the wooden fence surrounding " +
        "the small grass field behind the tool shed.\n",
        ""}), TP);
    return text;
}

string
desc_bull()
{
    string text;

    object field = find_object(THIS_DIR + "field");
    if (present("_bull", field))
    {
        say(({METNAME + " walks up to the fence and takes " +
            "a closer look of the field and the bull.\n",
            TART_NONMETNAME + " walks up to the fence and takes " +
            "a closer look of the field and the bull.\n",
            ""}), TP);
        text = "You walk closer up to the fence to catch " +
            "a glimpse of the bull in the field. He looks " +
            "huge and no one to mess with.\n";
        return text;
    }
    text = "What?\n";
    return text;
}

string
desc_field()
{
    string text, name;
    object field;
    object *ob;

    text = "You see a small grass field surrounded by the fence. ";

    field = find_object(THIS_DIR + "field");
    ob = FILTER_CAN_SEE(all_inventory(field), TP);
        if (!sizeof(ob))
        {
            text += "\n";
            return text;
        }
    text += "You can see " + COMPOSITE_WORDS(map(ob, "desc", TO)) + " in " +
        "the field.\n";
    say(({METNAME + " looks out over the field behind the " +
        "small tool shed.\n",
        TART_NONMETNAME + " looks out over the field behind the " +
        "small tool shed.\n",
        ""}), TP);
    return text;
}


string
desc(object ob)
{
    if (living(ob))
        return COMPOSITE_LIVE(ob);
    else
        return LANG_ADDART(ob->short());
}

string
search_heap(object player, string str)
{
    object maggot, can, maggot1;
    string text;

    switch(str)
    {
        case "heap":
        case "dung":
        case "dung heap":
        {
            if (TO->query_maggots())
            {
                maggot = clone_object(THIS_DIR + "obj/maggot");
                can = (present("_can", TP));
                if (can)
                {
                    maggot->move(can);
                    maggots--;
                    text = "You find "+LANG_ASHORT(maggot)+" and put " +
                        "it inside your metal can to prevent it from " +
                        "dying as it most likely would have, had you " +
                        "not been so clever.";
                    say(({METNAME + " picks up a small maggot and puts " +
                        "it inside a metal can.\n",
                        TART_NONMETNAME + " picks up a small maggot and puts " +
                        "it inside a metal can.\n",
                        ""}), TP);
                    if (!can->query_dung())
{
                        text+= " After putting the maggot in the can " +
                            "you take a handful of dung and fill " +
                            "the can to protect the maggot inside.";
                        can->add_dung();
                    }

                    text+= "\n";
                    return text;
                    break;
                }
                maggot->move(TP);
                maggot->kill_maggot();  // It will soon die without a can
                maggots --;
                text = "You find "+LANG_ASHORT(maggot)+".\n";
                say(({METNAME + " searches through the dung heap and " +
                    "finds a small maggot.\n",
                    TART_NONMETNAME + " searches through the dung heap and " +
                    "finds a small maggot.\n",
                    ""}), TP);
                return text;
                break;
            }

            else
            {
                maggot1 = (present("_maggot", TP));
                if (maggot1)
                {
                    text = "You poke around in the " +str+ " for a " +
                        "while, but it seems there are no maggots " +
                        "to find. Use of a tool could perhaps change " +
                        "this state of matters if you really need to " +
                        "search in the lower parts of the heap.\n";
                    say(({METNAME + " pokes around in the dung heap, but seems " +
                        "to find nothing of interest.\n",
                        TART_NONMETNAME + " pokes around in the dung heap, but seems " +
                        "to find nothing of interest.\n",
                        ""}), TP);
                    return text;
                    break;
}
                text = "You search the heap but find nothing of interest. Maybe " +
                    "there could be something hidden deeper in the dung but most " +
                    "likely its only a place for dung maggots to hide.\n";
                say(({METNAME + " pokes around in the dung heap, but seems " +
                    "to find nothing of interest.\n",
                    TART_NONMETNAME + " pokes around in the dung heap, but seems " +
                    "to find nothing of interest.\n",
                    ""}), TP);
                return text;
                break;
            }
        }

        default:
             return "";
     }
}

int
query_maggots()
{
    return maggots;
}

int
do_poke(string str)
{
    object fork;

    if (!(str))
        return 0;
    if ((str == "heap") || (str == "dung") || (str == "dung heap")
        || (str == "in heap") || (str == "in dung heap")
        || (str == "in dung"))
    {

       fork = (present("_pitch_fork", TP));
       if (fork)
       {
           write("You poke around in the dung heap for a while " +
            "with your pitch fork. Now you might find what you " +
            "are looking for in there.\n");
           maggots = 5;
           return 1;
       }
       write("You start to poke around in the heap with your hands " +
        "but after a while you stop. Its really no use without the " +
        "proper tool.\n");
       return 1;
    }
    return 0;
}

int
do_use(string str)
{
    object fork;

    if (!(str))
        return 0;
    if ((str == "pitch fork") || (str == "fork"))
    {

       fork = (present("_pitch_fork", TP));
       if (fork)
       {
           write("You poke around in the dung heap for a while " +
            "with your pitch fork. Now you might find what you " +
            "are looking for in there.\n");
           maggots = 5;
           return 1;
       }
       return 0;
    }
    return 0;
}

int
do_shake(string str)
{

    if (!(str))
        return 0;
    if ((str == "fence") || (str == "wooden fence"))
    {
       write("You take a steady grip of the fence and " +query_verb()+ " it hard. " +
           "It is very solid. The planks doesnt give in the slightest.\n");
       say(({METNAME + " walks up to the wooden fence and " +query_verb()+ "s it " +
           "violently.\n",
           TART_NONMETNAME + " walks up to the wooden fence and " +query_verb()+ "s it " +
           "violently.\n",
           ""}), TP);
       return 1;
    }
    return 0;
}

void
enter_inv(object ob, object old)
{
    object elf, player;

    ::enter_inv(ob, old);

    if (!(query_interactive(ob)))
        return;

    player = find_player("ibun");
    if (player)
    {
        player->catch_msg("Someone at the yard.\n");
    }

    if (!(ob->query_prop(LIVE_S_LAST_MOVE) == "north"))
        return;

    if (ob->query_prop(LABAL) < 0)
        return;


    if ((ob->test_bit("Avenir", FARM_BITS))
        && (ob->query_prop(LABAL) < 4))
        {
            ob->add_prop(LABAL, 4);
            return;
        }


    if ((ob->test_bit("Avenir", TROUT_BITS))
        && (ob->query_prop(LABAL) < 3))
        {
            ob->add_prop(LABAL, 3);
            return;
        }

   if ((ob->test_bit("Avenir", RING_BITS))
&& (ob->query_prop(LABAL) < 2))
{
ob->add_prop(LABAL, 2);

            return;

        }

    if (!(ob->query_prop(LABAL)))
    {
        elf = present("_labal", TO);
        if (elf)
        {
            set_alarm(1.0, 0.0, &bug_off(elf));
            return;
        }
    }
    return;
}

int
bug_off(object elf)
{
    elf->bug_off(TP);
}
