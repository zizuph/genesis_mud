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
int do_drop();
int place_ladder;
int needle = 1;

void
create_room()
{
    set_short("The hay loft");
    set_long("@@desc_long");
    add_item(({"beams","light beams"}),"The source cast a few " +
        "beams of light through some invisible cracks " +
        "in the ceiling.\n");
    add_item("ceiling","You look up at the ceiling and see the " +
        "hay dust flying around in the beams of light from " +
        "invisible cracks. Below the ceiling is a " +
        "large wooden beam fastened right below the ridge. " +
        "Probably there to stabilise the stucture of the " +
        "stable.\n");
    add_item("beam","@@desc_beam");
    add_item("loft","You look around the loft. Apart from the " +
        "huge heap of hay there is not much to see up here. But " +
        "you have a nice view of the stable from up here.\n");
    add_item(({"dust","hay dust"}),"Dust from the hay is flying " +
        "around in the light coming from invisible cracks " +
        "in the ceiling.\n");
    add_item(({"wall","walls"}),"The walls are the standard " +
        "wooden planks of a country stable.\n");
    add_item(({"hay","heap","pile"}),"The huge heap of old hay is " +
        "big enough for many people to hide or play in. " +
        "Perhaps you recall some good old memories from childhood " +
        "doing just that in another pile of hay.\n");
    add_item("ridge","Far up, right where the ridge ends in the wall, " +
        "you notice a big shadow.\n");
    add_item(({"shadow","big shadow","nest"}),"You cant see what " +
        "it is from down here, but when you try to focus " +
        "you notice some flying insects around it so probably " +
        "its some kind of a nest or such.\n");
    add_item("floor","It's a wooden floor covered by straw from " +
        "the huge pile of hay.\n");
    add_item("ladder","@@desc_ladder");
    add_item(({"stable","wiev",}),"@@desc_stable");
    add_exit("beam1","sound_connector", 1, 1, 1);
    add_exit("beam2","sound_connector", 1, 1, 1);
    add_exit("stable","sound_connector", 1, 1, 1);
    add_prop(OBJ_S_SEARCH_FUN, "search_hay");
    set_terrain(TERRAIN_RESIDENCE);
    reset_room();
}

void
reset_room()
{


}

void
init()
{
    ::init();
        add_action("climb_ladder","climb");
        add_action("search_far_away_items","search");
        add_action("jump_down","jump");
        add_action("play_in_hay","play");
        add_action("play_in_hay", "hide");
}

int
play_in_hay(string str)
{
    if ((str) && (str == "in hay"))
    {
        write("You " +query_verb()+ " in the hay for a while. But it isn't " +
            "as fun as you hoped it would be so you stop.\n");
        say(QCTNAME(TP) + " " +query_verb()+ "s in the hay.\n");
        return 1;
    }
    return 0;
}

int
search_far_away_items(string str)
{
    if ((str == "shadow") || (str == "beam") || (str == "ridge")
        || (str == "stable") || (str == "beams") || (str == "ceiling"))
    {
        write("The " +str+ " is to far away to search.\n");
        return 1;
    }
    return 0;
}

string
desc_long()
{
    string text;

    text = "This is the hay loft. On the floor is a huge heap of " +
           "old and dry hay but apart from that there isn't much " +
           "to see up here. ";

    place_ladder = find_object(THIS_DIR + "stable")->query_place_ladder();

    if (place_ladder == 0)
    {
        text += "Leading up to the loft is a long wooden " +
            "ladder.\n";
        return text;
    }
    text += "A large wooden ladder is placed towards a " +
        "wooden beam right under the ridge of the " +
        "ceiling so you cant climb down from the loft " +
        "at the moment.\n";
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
         + COMPOSITE_WORDS(map(ob, "desc", TO)) + ".\n";
    return text;
}

string
desc_stable()
{
    string text;
    object stable, *ob;

    text = "You look down in the stable. Its a long drop " +
        "and you dont want to experience such a fall. From " +
        "up here everything looks a lot different but you decide " +
        "this is not the time to watch the view. ";

    stable = find_object(THIS_DIR + "stable");

        ob = FILTER_CAN_SEE(all_inventory(stable), TP);
        if (!sizeof(ob))
        {
            text += "\n";
            return text;
        }
        text += "Far down in the stable you can see "
             + COMPOSITE_WORDS(map(ob, "desc", TO)) + ".\n";
    return text;
}

string
desc(object ob)
{
    if (living(ob))
        return COMPOSITE_LIVE(ob);
    if (function_exists("create_heap", ob))
        return (ob->short());
    else
        return LANG_ADDART(ob->short());
}

string
desc_ladder()
{

    place_ladder = find_object(THIS_DIR + "stable")->query_place_ladder();

    if (place_ladder == 0)
        return "Its a long wooden ladder which seems to " +
               "be in a good shape. Right now its leading " +
               "up here.\n";
    return "Its a long wooden ladder which seems to " +
               "be in a good shape. Right now its leading " +
               "up the the wooden beam under the ridge of " +
               "the ceiling so the only way down is to " +
               "jump.\n";
}

int
jump_down(string str)
{
    if (strlen(str) && (str == "down"))
    {
        write("You take a big leap out into the air and " +
            "land safely in the stable.\n");
        say(({METNAME + " jumps down to the stable.\n",
            TART_NONMETNAME + " jumps down to the stable.\n",
            "You hear a thud from below.\n"}), TP);
        tell_room(THIS_DIR + "stable",
            ({METNAME + " jumps down from the loft and " +
                "lands right beside you.\n",
            TART_NONMETNAME + " jumps down from the loft and " +
                "lands right beside you.\n",
            "You hear a 'thudding' sound right beside you as " +
                "something fell down from above.\n"}), TP);
        tell_room(THIS_DIR + "beam1",
            ({METNAME + " jumps down from the loft and " +
                "lands in the stable.\n",
            TART_NONMETNAME + " jumps down from the loft and " +
                "lands in the stable.\n",
            ""}), TP);
        tell_room(THIS_DIR + "beam2",
            ({METNAME + " jumps down from the loft and " +
                "lands in the stable.\n",
            TART_NONMETNAME + " jumps down from the loft and " +
                "lands in the stable.\n",
            ""}), TP);
        TP->move_living("M", THIS_DIR + "stable", 1);
        return 1;
    }
    return 0;
}

string
search_hay(object player, string str)
{
    object ob;


    switch (str)
    {
        case ("hay"):
        case ("heap"):
        case ("pile"):
        {
            if (needle)
            {
                set_alarm(3.0, 0.0, &do_drop());
                needle = 0;
                return "After a short time you see something glimmering " +
                    "in the hay.\nThe needle in the hay stack!!\n";
                say(QCTNAME(TP)+ " starts to search the hay stack and " +
                    "suddenly " +TP->query_pronoun()+ " finds something!\n");
                break;
            }
        }
        default:
            return "";
    }
}

int
do_drop()
{
    write("You fumble and drop the needle back into the hay.\n");
    say(QCTNAME(TP)+ " drops something in the hay!\n");
    return 1;
}

int
climb_ladder(string str)
{
    if ((str != "down") && (str != "ladder"))
    {
        write("Climb where?\n");
        return 1;
    }

    place_ladder = find_object(THIS_DIR + "stable")->query_place_ladder();
    if (place_ladder == 0)
    {
        write("You climb down the ladder and soon you reach the " +
            "stable.\n");
        say(({METNAME + " climbs down the ladder.\n",
            TART_NONMETNAME + " climbs down the ladder.\n",
            "You hear something climbing down on the ladder.\n"}), TP);
        tell_room(THIS_DIR + "stable",
            ({METNAME + " arrives from above.\n",
            TART_NONMETNAME + " arrives from above.\n",
            "You hear something arriving from above on the " +
                "ladder.\n"}), TP);
        tell_room(THIS_DIR + "beam1",
            ({METNAME + " climbs down to the stable on " +
                "the ladder.\n",
            TART_NONMETNAME + " climbs down to the stable on " +
                "the ladder.\n",
            ""}), TP);
        tell_room(THIS_DIR + "beam2",
            ({METNAME + " climbs down to the stable on " +
                "the ladder.\n",
            TART_NONMETNAME + " climbs down to the stable on " +
                "the ladder.\n",
            ""}), TP);
        TP->move_living("M", THIS_DIR + "stable", 1);
    }
    else
        write("The ladder is not leading to the hay loft. You " +
            "can not use it at this moment. Better try " +
            "another way to get down.\n");
    return 1;
}
