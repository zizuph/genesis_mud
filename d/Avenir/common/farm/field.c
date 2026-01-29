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

inherit "/std/room";

int scare_bull();

int pole = 0;

void
create_room()
{
    set_short("The small grass field");
    set_long("You stand in a small grass field surrounded by " +
        "a wooden fence. Outside the fence you see some trees " +
        "and the backside of the tool shed. In one corner of " +
        "the field there is a junk heap.\n");
    add_item(({"tree","trees"}), "The trees are just some ordinary trees " +
        "typical for the surrounding.\n");
    add_item(({"shed","tool shed","backside"}),"You walk back to " +
        "the fence close to the shed to get a better look, but " +
        "there is nothing intresting about the backside.\n");
    add_item(({"junk heap","junk","heap"}),"Something, probably " +
        "the bull, has been poking around in the heap spreading " +
        "out some of the junk around the field. Looking closer you " +
        "see that the heap mainly consists of soil overgrown with " +
        "weed and some other junk such as old clothes and boxes " +
        "that are of no use anymore.\n");
    add_item(({"clothes","boxes"}),"@@desc_clothes");
    add_item(({"soil","weed"}), "The junk heap consists mainly " +
        "of soil and junk. You can tell it was a long time anyone " +
        "threw things here because the whole heap is overgown with " +
        "weed.\n");
    add_item("field", "@@long");
    add_item("grass", "There isnt much left of the grass. Animals " +
        "have eaten most of it and the little that is left doesnt " +
        "look very nice at all.\n");
    add_item("fence","@@desc_fence");
    add_item("yard","@@desc_yard");
    add_item("bolt","Its a wooden bolt, hit deep down into the " +
        "ground, with brute force.\n");
    add_item("ring","@@desc_ring");
    add_item("chain","@@desc_chain");
    add_prop(OBJ_S_SEARCH_FUN, "search_heap");
    set_terrain(TERRAIN_OPENSPACE);
    set_terrain(TERRAIN_OUTSIDE);

    setuid();
    seteuid(getuid());
    reset_room();
}

void
reset_room()
{
    object bull, yard;

    if (sizeof(FILTER_PLAYERS(all_inventory(TO))))
        return;

    yard = find_object(THIS_DIR + "yard");
    if (objectp(yard) && sizeof(FILTER_PLAYERS(all_inventory(yard))))
        return;

        bull = (present("bull", this_object()));
        if (bull)
            bull->remove_object();
        bull = clone_object(THIS_DIR + "npc/bull");
        bull->move(this_object());
        add_item("chain","@@desc_chain");
        pole = 0;
}

void
init()
{
    ::init();
        add_action("climb_fence","climb");
        add_action("pull_bolt","pull");
        add_action("pull_bolt","get");
        add_action("give_nest","give");


}

string
desc_chain()
{
    string text;

    if (present("_bull", TO))
    {
        string text ="Its a long chain that secures the bull to a wooden " +
            "bolt in the ground.\n";
        return text;
    }
    return "What?";
}

string
desc_ring()
{
    string text;

    if (present("_bull", TO))
    {
        string text = "A massive gold colored brass ring that is stuck " +
            "in the nose of the huge bull.\n";
        return text;
     }
    return "What?";
}

int
climb_fence(string str)
{
    if ((str == "") || (!(str == "fence")))
        return 0;
    write("You climb over the fence.\n");
    say(({METNAME + " climbs over the fence into the " +
        "stable yard.\n",
        TART_NONMETNAME + " climbs over the fence into the " +
        "stable yard.\n",
        ""}), TP);
    tell_room(THIS_DIR + "yard", ({METNAME + " arrives over " +
        "the fence.\n",
        TART_NONMETNAME + " arrives over " +
        "the fence.\n",
        ""}), TP);
    TP->move_living("M", THIS_DIR + "yard", 1);
    return 1;

}

int
pull_bolt(string str)
{
    if ((str == "") || (!(str == "bolt")))
        return 0;
    write("You take a steady grip of the bolt and try to pull it up. Alas, " +
        "its stuck too hard into the ground.\n");
    say(({METNAME + " tries to pull up a wooden bolt from " +
        "the ground, but its stuck to hard.\n",
        TART_NONMETNAME + " tries to pull up a wooden bolt from " +
        "the ground, but its stuck to hard.\n",
        ""}), TP);
    return 1;
}

string
search_heap(object player, string str)

{
    object ob;

    switch (str)
    {
        case ("heap"):
        case ("junk"):
        case ("junk heap"):
            if (present("_bull"))
            {
                write("Suddenly your sixth sense tells you " +
                    "that the bull doesnt like you poking " +
                    "around in his junk heap.\nYou stop " +
                    "your search and move away from the bull.\n");
                return "";
                break;
            }
            if (pole == 0)
            {
                ob = clone_object(THIS_DIR + "obj/pole");
                ob->move(TP);
                pole = 1;
                return "You find "+LANG_ASHORT(ob)+".\n";
                break;
            }

        default:
            return "";
    }
}


string
desc_fence()
{
    string text, name;
    object yard;
    object *ob;

    text = " Its a wooden fence about 6 feet high that surrounds " +
        "a small grass field behind the tool shed. ";

    yard = find_object(THIS_DIR + "yard");

    ob = FILTER_CAN_SEE(all_inventory(yard), TP);
    if (!sizeof(ob))
    {
        text += "\n";
        return text;
    }
    text += "On the other side you can see "
         + COMPOSITE_WORDS(map(ob, "desc", TO)) + ".\n";
    return text;
}


string
desc_yard()
{
    string text, name;
    object yard;
    object *ob;

    text = " You can see the yard from here with the stable " +
        "and the shed. ";

    yard = find_object(THIS_DIR + "yard");
    ob = FILTER_CAN_SEE(all_inventory(yard), TP);
        if (!sizeof(ob))
        {
            text += "\n";
            return text;
        }
    text += "You can see " + COMPOSITE_WORDS(map(ob, "desc", TO)) + " in " +
        "the yard.\n";
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
desc_clothes()
{
    string text;

    if (present("_bull", TO))
    {
        text = "You try to get closer to the heap to get a " +
            "better look, but the bull stops you from coming " +
            "closer.\n";
        return text;
    }
    text = "You take some of the junk from the heap to get " +
        "a better look at it.\nIts just junk though, so you " +
        "drop it back again where it belongs.\n";
    return text;

}

int
query_pole()
{
    return pole;
}

void
enter_inv(object ob, object old)
{
    object bull;

    ::enter_inv(ob, old);
        if (ob->query_prop("_wasp_nest"))
        {
            bull = (present("_bull"));
            if (bull)
                set_alarm(2.0, 0.0, &scare_bull());
                return;
        }
        return;

}

int
scare_bull()
{
    object bull;

    bull = (present("_bull"));
    if (bull)
    {
        bull->scared_bull();
        return 1;
    }
    return 0;
}
 
int
give_nest(string str)
{
    if ((str == "") || (!(str == "nest to bull")))
        return 0;
    if (present(!("_bull")))
        return 0;
    if (!(present("wasp nest", TP)))
        return 0;
    write("You walk towards the bull with the nest in " +
        "your hand. The bull stares at you with wide " +
        "open eyes and then lowers his head in your " +
        "direction. Maybe this wasnt such a good idea " +
        "after all.\n");
    say(({METNAME + " walks towards the bull with a " +
        "wasp nest in " + TP->query_possessive()+ " hand.\n",
        TART_NONMETNAME + " walks towards the bull with a " +
        "wasp nest in " + TP->query_possessive()+ " hand .\n",
        ""}), TP);
    return 1;
}
