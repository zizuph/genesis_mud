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
int place_ladder = 0;
int bucket = 1;
object beam1;
object loft;
object beam2;

void
create_room()
{
    set_short("The stable");
    set_long("@@desc_long");
    add_item(({"beams","light beams"}),"The sun cast a few " +
               "beams of light through some invisible cracks " +
               "in the ceiling.\n");
    add_item(({"loft","hay loft","hay"}),"You cant see much of the " +
               "loft from down here. There seems to be a pile " +
               "of hay up there, but thats about it. To reach " +
               "the loft you must use the ladder.\n");
    add_item("ceiling","You look up at the ceiling and see the " +
             "hay dust flying around in the beams of light from " +
             "invisible cracks. Right below the ceiling is a " +
             "large wooden beam fastened right below the ridge. " +
             "Probably there to stabilise the structure of the " +
             "stable.\n");
    add_item("beam","@@desc_beam");
    add_item(({"dust","hay dust"}),"Dust from the hay is flying " +
             "around in the light coming from invisible cracks " +
             "in the ceiling.\n");
    add_item(({"box","boxes","horse boxes"}),"The are two boxes " +
             "in here for horses. Both are empty and when you take " +
             "a closer look inside you realise there was a long " +
             "time since there were any horses in here.\n");
    add_item("ridge","Far up, right where the ridge ends in the wall, " +
             "you notice a big shadow.\n");
    add_item(({"shadow","big shadow","nest"}),"You cant see what " +
               "it is from down here, but when you try to focus " +
               "you notice some flying insects around it so probably " +
               "its some kind of a nest or such.\n");
    add_item(({"wall","walls"}),"You take a step closer to examine " +
               "the walls but find nothing sensational about them. " +
               "A few hooks to hang up things on, a black board to " +
               "write messages on and close to the wall a water " +
               "trough for the horses.\n");
    add_item("black board","There seems to have been something " +
             "written here, but its impossible to see what it was. " +
             "There is no chalk in sight so even if you wanted to, " +
             "writing is impossible on the board.\n");
    add_item(({"trough","water trough"}),"When you lean over you " +
        "see that the trough is completely empty. A big rust hole " +
        "in the bottom tells you why.\n");
    add_item("hooks","@@desc_hooks");
    add_item("stable","@@desc_long");
    add_item("ladder","@@desc_ladder");
    add_exit("yard","out");
    add_exit("beam1","sound_connector", 1, 1, 1);
    add_exit("beam2","sound_connector", 1, 1, 1);
    add_exit("loft","sound_connector", 1, 1, 1);
    set_terrain(TERRAIN_RESIDENCE);
    reset_room();
}

void
reset_room()
{

    (THIS_DIR + "beam1")->teleledningsanka();
    (THIS_DIR + "beam2")->teleledningsanka();
    (THIS_DIR + "loft")->teleledningsanka();
    loft = find_object(THIS_DIR + "loft");
    beam1 = find_object(THIS_DIR + "beam1");
    beam2 = find_object(THIS_DIR + "beam2");

    if (sizeof(FILTER_PLAYERS(all_inventory(TO))))
        return;
    if (sizeof(FILTER_PLAYERS(all_inventory(loft))))
        return;
    if (sizeof(FILTER_PLAYERS(all_inventory(beam1))))
        return;
    if (sizeof(FILTER_PLAYERS(all_inventory(beam2))))
        return;

    place_ladder = 0;
    bucket = 1;
    add_item("bucket","@@desc_bucket");
}

void
init()
{
    ::init();
        add_action("move_ladder","move");
        add_action("climb_ladder","use");
        add_action("move_ladder","push");
        add_action("lift_ladder","lift");
        add_action("lift_ladder","get");
        add_action("get_bucket","get");
        add_action("climb_ladder","climb");
        add_action("search_far_away_items","search");
}

string
desc_long()
{
    string text;

    text = "This is a rather small stable. Right now its " +
           "pretty empty and the two horse boxes looks " +
           "like it was a long time since they saw a horse. " +
           "Up above you can see the hay loft and a few " +
           "light beams find their way through the ceiling. ";

    if (place_ladder == 0)
    {
        text += "Leading up to the loft is a long wooden " +
            "ladder.\n";
        return text;
    }

    text += "A large wooden ladder is placed towards a " +
        "wooden beam right under the ridge of the " +
        "ceiling.\n";
    return text;
}

string
desc_ladder()
{

    if (place_ladder == 0)
    {
        say(({METNAME + " steps forward to the ladder and looks " +
                "up to see where it leads.\n",
            TART_NONMETNAME + " steps forward to the ladder and looks " +
                "up to see where it leads.\n",
            ""}), TP);
        return "Its a long wooden ladder which seems to " +
           "be in a good shape. Right now its leading " +
           "up to the hay loft.\n";
    }
    say(({METNAME + " steps forward to the ladder and looks " +
            "up to see where it leads.\n",
        TART_NONMETNAME + " steps forward to the ladder and looks " +
            "up to see where it leads.\n",
        ""}), TP);
    return "Its a long wooden ladder which seems to " +
       "be in a good shape. Right now its leading " +
       "up the the wooden beam under the ridge of " +
       "the ceiling.\n";
}


string
desc_bucket()
{
    mixed  *target = FILTER_PLAYERS(all_inventory(this_object()));
    int i, n;
    string name;

    if (bucket)
    {
        for (i = 0, n = sizeof(target); i < n; i++)
        {
            if(target[i] == this_player())
                target[i]->catch_tell("Its a metal bucket hanging on a " +
                    "hook. When you tip it over and look inside " +
                    "you find that its completely empty.\n");
            else if (!(CAN_SEE_IN_ROOM(target[i])))
                    target[i]->catch_tell("You hear someone moving " +
                        "around, but its too dark to see what is going " +
                        "on.\n");
            else
            {
                if (CAN_SEE(target[i], this_player()))
                {
                    name = TP->query_The_name(target[i]);
                    target[i]->catch_tell(name + " takes a step" +
                       " forward and looks closely inside a " +
                       "bucket that is hanging on a hook.\n");
                }
                else
                    target[i]->catch_tell("You suddenly see the " +
                        "bucket wobble on its hook as if something " +
                        "was moving it.\n");
            }

        }
        return "";
    }
    return "";
}


string
desc_hooks()
{

    string text;

    text = "The hooks have been used to hang things on. " +
           "Most likely ropes, reins and such but also " +
           "saddles and buckets on some particularly " +
           "big hooks. ";

    if (bucket)
        text += "An old bucket is still hanging " +
                "here.\n";
    text += "\n";
    return text;
}

string
desc_beam()
{
    string text;
    object *ob, beam1, beam2;

    text = "The wooden beam reaches from wall to wall " +
             "right below the ridge of the ceiling. You cant reach " +
             "it from down here which might be a good thing as " +
             "its pretty high to the ridge. ";

    beam1 = find_object(THIS_DIR + "beam1");
    beam2 = find_object(THIS_DIR + "beam2");

    ob = FILTER_CAN_SEE(all_inventory(beam1), TP);
    ob += FILTER_CAN_SEE(all_inventory(beam2), TP);
    if (!sizeof(ob))
    {
        text += "\n";
        return text;
    }
    text += "Up on the beam you can see "
         + COMPOSITE_WORDS(map(ob, "desc", TO)) + " trying a " +
             "balance act.\n";
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

int
search_far_away_items(string str)
{
    if ((str == "shadow") || (str == "beam") || (str == "ridge")
        || (str == "loft") || (str == "beams") || (str == "ceiling"))
    {
        write("The " +str+ " is too far away to search.\n");
        return 1;
    }
    return 0;
}

int
lift_ladder(string str)
{
    if (strlen(str) && (str == "ladder"))
    {
        write("The ladder is way to heavy for you " +
             "to get. Maybe it is possible to push it.\n");
        say(({METNAME + " tries to lift the ladder but " +
            "it is too heavy for " +TP->query_possessive()+
            ".\n", TART_NONMETNAME + " tries to lift the ladder " +
            "but it is too heavy for " +TP->query_possessive()+
            ".\n", "You hear someone take a deep breath and " +
            "then a scraping sound, but it is impossible to " +
            "see what happened.\n"}), TP);
        return 1;
    }
    return 0;
}

int
climb_ladder(string str)
{

    if ((str != "up") && (str != "ladder"))
    {
        write("Climb where?\n");
        return 1;
    }
 
    if (place_ladder)
    {
        write("You climb up the ladder and soon you reach the " +
            "wooden beam.\n");
        say(({METNAME + " climbs up the ladder to the beam.\n",
            TART_NONMETNAME + " climbs up the ladder to the beam.\n",
            "You hear something climbing up the ladder.\n"}), TP);
        tell_room(THIS_DIR + "beam1",
            ({METNAME + " arrives from below.\n",
            TART_NONMETNAME + " arrives from below.\n",
            "You hear something arriving from the stable.\n"}), TP);
        tell_room(THIS_DIR + "beam2",
            ({METNAME + " arrives from below to the beam.\n",
            TART_NONMETNAME + " arrives from below " +
        "to the beam.\n",
            "You hear something arriving from below on the " +
                "ladder.\n"}), TP);
        tell_room(THIS_DIR + "loft",
            ({METNAME + " climbs up to the beam on the " +
                "ladder.\n",
            TART_NONMETNAME + " climbs up to the beam on the " +
                "ladder.\n",
            ""}), TP);
        TP->move_living("M", THIS_DIR + "beam1", 1);
    }
    else
    {
        write("You climb up the ladder and soon you reach the " +
            "hay loft.\n");
        say(({METNAME + " climbs up the ladder to the loft.\n",
            TART_NONMETNAME + " climbs up the ladder to the loft.\n",
            "You hear someone climbing up the ladder.\n"}), TP);
        tell_room(THIS_DIR + "loft",
            ({METNAME + " arrives from the stable on the ladder.\n",
            TART_NONMETNAME + " arrives from the stable on " +
        "the ladder.\n",
            "You hear something arriving from below on the ladder.\n"}), TP);
        tell_room(THIS_DIR + "beam1",
            ({METNAME + " climbs up to the loft on the " +
                "ladder.\n",
            TART_NONMETNAME + " climbs up to the loft on the " +
                "ladder.\n",
            ""}), TP);
        tell_room(THIS_DIR + "beam2",
            ({METNAME + " climbs up to the loft on the " +
                "ladder.\n",
TART_NONMETNAME + " climbs up to the loft on the " +
                "ladder.\n",
            ""}), TP);
        TP->move_living("M", THIS_DIR + "loft", 1);
    }
    return 1;
}

int
get_bucket(string str)
{

    object obj;

    mixed  *target = FILTER_PLAYERS(all_inventory(this_object()));
    int i, n;
    string name;

    if (strlen(str) && (str == "bucket"))
    {
        if (bucket)
        {
            for (i = 0, n = sizeof(target); i < n; i++)
            {
                if(target[i] == this_player())
                    target[i]->catch_tell(" You take a step " +
                        "forward and get a bucket that is " +
                        "hanging on its hook.\n");
                else if (!(CAN_SEE_IN_ROOM(target[i])))
                    target[i]->catch_tell("You hear something moving" +
                        "around, but its too dark to see what is going " +
                        "on.\n");
                else
                {
                    if (CAN_SEE(target[i], this_player()))
                    {
                        name = TP->query_The_name(target[i]);
                        target[i]->catch_tell(name + " takes a step " +
                            "forward and gets a bucket that is " +
                            "from a hook.\n");
                    }
                    else
                        target[i]->catch_tell("You suddenly see the " +
                            "bucket wobble on its hook and then " +
                            "it suddenly disappears!\n");
                }
            }
            obj = clone_object(THIS_DIR + "obj/bucket");
            obj->move(this_player());
            bucket = 0;
            remove_item("bucket");
            return 1;
        }
        return 0;
    }
    return 0;
}

int
query_place_ladder()
{
    return place_ladder;
}

int
move_ladder(string str)
{
    object beam1;
    mixed  *target = FILTER_PLAYERS(all_inventory(this_object()));
    int i, n;
    string name;

    if (strlen(str) && (str == "ladder"))
    {
        if (place_ladder == 0)
        {
            for (i = 0, n = sizeof(target); i < n; i++)
            {
                if(target[i] == this_player())
                    target[i]->catch_tell("You take a step " +
                        "forward and push the ladder towards " +
                        "the wooden beam. Now it is possible " +
                        "to climb up there.\n");
                else if (!(CAN_SEE_IN_ROOM(target[i])))
                    target[i]->catch_tell("You hear something moving" +
                        "around, but its too dark to see what is going " +
                        "on.\n");
                else
                {
                    if (CAN_SEE(target[i], this_player()))
                    {
                        name = TP->query_The_name(target[i]);
                        target[i]->catch_tell(name + " takes a step " +
                            "forward and push the ladder towards " +
                            "the wooden beam. Now it is possible " +
                            "to climb up there.\n");
                    }
                    else
                        target[i]->catch_tell("You suddenly see the " +
                            "ladder move towards the wooden beam " +
                            "up under the ceiling as if beeing " +
                            "moved by an invisible force!\n");
                }
            }
            place_ladder = 1;
            return 1;
        }

        for (i = 0, n = sizeof(target); i < n; i++)
        {
            if(target[i] == this_player())
                target[i]->catch_tell("You take a step " +
                    "forward and push the ladder towards " +
                    "the hay loft. Now it is possible " +
                    "to climb up there.\n");
            else if (!(CAN_SEE_IN_ROOM(target[i])))
                target[i]->catch_tell("You hear something moving" +
                    "around, but its too dark to see what is going " +
                    "on.\n");
            else
            {
                if (CAN_SEE(target[i], this_player()))
                {
                    name = TP->query_The_name(target[i]);
                    target[i]->catch_tell(name + " takes a step " +
                        "forward and push the ladder towards " +
                        "the hay loft. Now it is possible " +
                        "to climb up there.\n");
                }
                else
                    target[i]->catch_tell("You suddenly see the " +
                        "ladder move towards the hay loft " +
                        "as if beeing moved by an invisible " +
                        "force!\n");
            }
        }
        place_ladder = 0;
        return 1;
    }
    return 0;
}
