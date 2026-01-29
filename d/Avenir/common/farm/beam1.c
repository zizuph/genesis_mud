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

void
create_room()
{
    set_short("Balancing on a wooden beam");
    set_long("@@desc_long");
    add_item(({"beams","light beams"}),"The source cast a few " +
        "beams of light through some invisible cracks " +
        "in the ceiling.\n");
    add_item(({"loft","hay loft","hay"}),"@@desc_loft");
    add_item("stable","@@desc_stable");
    add_item("ceiling","You reach out and touch the ceiling. Its a " +
        "rough surface and you feel cracks and its uneveness " +
        "under your hand. Dust flying around in the beams of light " +
        "from invisible cracks in the ceiling.\n");
    add_item("beam","@@desc_beam");
    add_item(({"dust","hay dust"}),"Dust from the hay is flying " +
        "around in the light coming from invisible cracks " +
        "in the ceiling.\n");
    add_item("ridge","@@desc_ridge");
    add_item(({"nest","wasp nest","shadow"}),"@@desc_nest");
    add_item(({"wall","walls"}),"You take a step closer to examine " +
        "the walls but find nothing sensational about them.\n");
    add_item("ladder","@@desc_ladder");
    add_exit("beam2","sound_connector", 1, 1, 1);
    add_exit("stable","sound_connector", 1, 1, 1);
    add_exit("loft","sound_connector", 1, 1, 1);
    set_terrain(TERRAIN_RESIDENCE);
    reset_room();
}

void
reset_room()
{
    object stable;
    int place_ladder;

    stable = find_object(THIS_DIR + "stable");
    place_ladder = stable->query_place_ladder();

}

void
init()
{

    ::init();
        add_action("balance_beam","balance");
        add_action("balance_beam","climb");
        add_action("jump_hay","jump");
        add_action("climb_ladder","climb");
        add_action("search_far_away_items","search");

}

int
balance_beam(string str)
{

    object obj;

    if (strlen(str) &&
           (
               (str == "beam") || (str == "on beam") || (str == "over")
           )
       )
    {
        if (!(CAN_SEE_IN_ROOM(TP)))
        {
            write("It is to dark to do any balance acts.\n");
            return 1;
        }
        write("You balance over to the other end of the " +
                  "beam.\n");
        say(({METNAME + " balances over to the other end of the " +
                  "beam.\n",
            TART_NONMETNAME + " balances over to the other " +
                "end of the beam.\n",
            "You hear something moving on the beam.\n"}), TP);
        tell_room(THIS_DIR + "beam2",
            ({METNAME + " comes balancing over from the other " +
                "end of the beam.\n",
            TART_NONMETNAME + " comes balancing over from the other " +
                "end of the beam.\n",
            "You hear something moving on the beam.\n"}), TP);
        tell_room(THIS_DIR + "stable",
            ({"You see " + METNAME + " balance on the beam high up " +
                "above.\n",
            "You see " + lower_case(ART_NONMETNAME) + " balance on the " +
                "beam high up above.\n",
            ""}), TP);
        tell_room(THIS_DIR + "loft",
            ({"You see " + METNAME + " balance on the beam high up " +
                "above.\n",
            "You see " + lower_case(ART_NONMETNAME) + " balance on the " +
                "beam high up above.\n",
            ""}), TP);
        TP->move_living("M", THIS_DIR + "beam2", 1);
        return 1;
    }
    write("Balance on what?\n");
    return 1;

}

void
drop_to_stable(string str, object ob)
{
    tell_room(THIS_DIR + "beam1", str +
        " falls down to the stable.\n");
    tell_room(THIS_DIR + "stable", str +
        " falls down from above.\n");
}

 

int
search_far_away_items(string str)
{
    if (str == "hay")
    {
        write("The " +str+ " is too far away to search.\n");
        return 1;
    }
    return 0;
}
 
void
enter_inv(object ob, object from)
{
   string str;

    ::enter_inv(ob, from);

    if(!living(ob))
    {
        str = ob->short();
        if (!function_exists("create_heap", ob))
        {
           str = (LANG_ART(str) + " " +str);
        }
    str = capitalize(str);
    set_alarm(1.0, 0.0, &drop_to_stable(str, ob));
    ob->move(THIS_DIR + "stable");
    }
}


string
desc_long()
{
    string text;
    int place_ladder = find_object("./stable")->query_place_ladder();


    text = "You are balancing on one end of a thick wooden " +
           "beam high up under the ceiling. ";
    if ((find_object(THIS_DIR + "stable")->query_place_ladder()) == 0)
    {
        text += "The ladder is leaning to the loft so you " +
                "cant climb down.\n";
        return text;
    }
    text += "The large wooden ladder is placed towards the " +
            "beam so you can climb down any moment " +
            "you wish.\n";
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
desc_loft()
{
    string text;
    object loft, *ob;

    text = "You look down at the loft a bit down from here. " +
        "There is a pile of hay down there, but thats about it. " +
        "To reach the loft you can not climb , but it seems " +
        "to be possible to jump down in the hay. ";

    loft = find_object(THIS_DIR + "loft");

        ob = FILTER_CAN_SEE(all_inventory(loft), TP);
        if (!sizeof(ob))
        {
            text += "\n";
            return text;
        }
        text += "Down in the loft you can see "
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
desc_ridge()
{

    string text;
    int nest;

    nest = find_object(THIS_DIR + "beam2")->query_nest();
    text = "Standing on the beam allows you to reach the " +
           "ridge of the celing.\n";

    if (nest)
    {
        text += "In the corner of the ridge and the wall is a large " +
                "wasp nest hanging.\n";
        return text;
    }
    text += "A wet shadow can be seen in the corner of the ridge " +
            "and the wall but there is nothing more to it.\n";
    return text;
}


string
desc_nest()
{
    string text;
    int nest;

    nest = find_object(THIS_DIR + "beam2")->query_nest();
    if (nest)
    {
        text = "Its big wasp nest and you can see a big wasp " +
           "crawl into the hole in the bottom it but you " +
           "need to balance over on the beam to get a better " +
            "look.\n";
        return text;
    }
    text = "In the corner of the ridge and the wall is a wet " +
           "spot. Looks like some kind of a insects nest have " +
           "hung here reasontly, but now its gone.\n";
    return text;

}

string
desc_ladder()
{

    int ladder;

    ladder = ((THIS_DIR + "stable")->query_place_ladder());
    if (!(ladder))
        return "Its a long wooden ladder which seems to " +
               "be in a good shape. Right now its leading " +
               "up to the hay loft.\n";
    else
    return "Its a long wooden ladder which seems to " +
               "be in a good shape. Right now its leading " +
               "up here.\n";
}

int
jump_hay(string str)
{
    if (strlen(str) && (str == "down"))
    {
        write("You take a big leap out into the air and " +
            "land safely in the heap of hay on the loft.\n");
        say(({METNAME + " takes a big leap out into the air and " +
                "land safely in the heap of hay on the loft.\n",
            TART_NONMETNAME + " take a big leap out into " +
                "the air and land safely in the heap of hay " +
                "on the loft.\n" ,
            "You hear a swishing sound and then it sounds " +
                "like someone landing in the hay far down " +
                "below.\n"}), TP);
        tell_room(THIS_DIR + "loft",
            ({METNAME + " jumps from " +
                "above and lands in the pile of hay.\n",
            TART_NONMETNAME + " jumps from above and lands in the " +
                "pile of hay.\n",
            "You hear the sound of someone moving in a " +
                "pile of hay.\n"}), TP);
        tell_room(THIS_DIR + "beam2",
            ({METNAME + " jumps from " +
                "the beam and lands in the pile of hay.\n",
            TART_NONMETNAME + " jumps from the beam and " +
                "lands in the pile of hay.\n",
            ""}), TP);
        TP->move_living("M", THIS_DIR + "loft", 1);
        return 1;
    }
    return 0;
}

int
climb_ladder(string str)
{
    if ((str != "down") && (str != "ladder"))
    {
        write("Climb where?\n");
        return 1;
    }
 
 
    int place_ladder = find_object("stable")->query_place_ladder();

    if ((find_object(THIS_DIR + "stable")->query_place_ladder()) == 1)
    {
        write("You climb down the ladder and soon you reach the " +
            "stable.\n");
        say(({METNAME + " climbs down the ladder.\n",
            TART_NONMETNAME + " climbs down the ladder.\n",
            "You hear something climbing down the ladder.\n"}), TP);
        tell_room(THIS_DIR + "stable",
            ({METNAME + " arrives from above.\n",
            TART_NONMETNAME + " arrives from above.\n",
            "You hear something arriving from above.\n"}), TP);
        tell_room(THIS_DIR + "beam2",
            ({METNAME + " climbs down to the stable on the ladder.\n",
            TART_NONMETNAME + " climbs down to the " +
                "on the ladder stable.\n",
            "You hear something moving on the ladder.\n"}), TP);
        tell_room(THIS_DIR + "loft",
            ({METNAME + " climbs down to the stable on the ladder.\n",
            TART_NONMETNAME + " climbs down to the " +
                "on the ladder stable.\n",
            ""}), TP);
        TP->move_living("M", THIS_DIR + "stable", 1);
    }
    else
        write("The ladder is leading to the hay loft. You " +
            "can not use it at this moment. Better try " +
            "another way to get down.\n");
    return 1;
}

string
desc_beam()
{
    string text;
    object *ob, beam1, beam2;

    text = "The wooden beam reaches from wall to wall " +
             "right below the ridge of the ceiling.";

    beam1 = find_object(THIS_DIR + "beam1");
    beam2 = find_object(THIS_DIR + "beam2");

    if (CAN_SEE_IN_ROOM(TP))
        ob = FILTER_OTHER_LIVE(FILTER_CAN_SEE(all_inventory(beam1), TP));
    if (CAN_SEE_IN_A_ROOM(TP, beam2))
        ob += FILTER_CAN_SEE(all_inventory(beam2), TP);

    if (!sizeof(ob))
    {
        text += "\n";
        return text;
    }

    text += " On the beam you can see "
         + COMPOSITE_WORDS(map(ob, "desc", TO)) + ".\n";
    return text;
}
