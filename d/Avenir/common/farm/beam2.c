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

int nest = 1;

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
    add_item(({"wasp","wasps"}),"@@desc_wasp");
    add_item("ridge","@@desc_ridge");
    add_item("ladder","@@desc_ladder");
    add_item(({"nest","wasp nest","shadow"}),"@@desc_nest");
    add_item(({"hole","bottom"}),"@@desc_bottom");
    add_item("spot", "@@desc_spot");
    add_exit("beam1","sound_connector", 1, 1, 1);
    add_exit("stable","sound_connector", 1, 1, 1);
    add_exit("loft","sound_connector", 1, 1, 1);
    set_terrain(TERRAIN_RESIDENCE);
    reset_room();
}

void
reset_room()
{
    nest = 1;
}

int
query_nest()
{
    return nest;
}


void
init()
{
    ::init();
        add_action("balance_beam","balance");
        add_action("balance_beam","climb");
        add_action("catch_nest","catch");
        add_action("catch_nest","get");
        add_action("search_far_away_items","search");
}

void
drop_to_stable(string str, object ob)
{

    tell_room(THIS_DIR + "beam2", str +
        " falls down to the stable.\n");
    tell_room(THIS_DIR + "stable", str +
        " falls down from above.\n");
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

int
balance_beam(string str)
{

    object obj, bucket;

    if (strlen(str) &&
           (
               (str == "beam") || (str == "on beam") || (str == "over")
           )
       )
    {
        if (!(CAN_SEE_IN_ROOM(TP)))
        {
            write("It is too dark to do any balance acts.\n");
            return 1;
        }


        bucket = present("_stable_bucket", TP);

        if (bucket)
        {
            write("Suddenly you loose balance! By waving your arms " +
                "like a madman you recover balance, but you drop " +
                "your bucket.\n");
            bucket->move(TO);
            return 1;
        }
        write("You balance over to the other end of the " +
                  "beam.\n");
        say(({METNAME + " balances over to the other end of the " +
                  "beam.\n",
            TART_NONMETNAME + " balances over to the other " +
                "end of the beam.\n",
            "You hear something moving on the beam.\n"}), TP);
        tell_room(THIS_DIR + "beam1",
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
        TP->move_living("M", THIS_DIR + "beam1", 1);
        return 1;
    }
    write("Balance on what?\n");
    return 1;

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
desc_wasp()
{
    string text;

    if (nest)
        text = "From the wasp nest comes a buzzing sound. " +
            "Around the hole in the bottom of the nest you " +
            "can see wasps crawl in and out.\n";
    else
    text = "You can see a lonesome wasp fly around in the " +
        "light from the cracks in the ceiling. Angrily it " +
        "buzzes around as if searching for something.\n";
    return text;
}

string
desc_loft()
{
    string text;
    object loft, *ob;

    text = "You look down at the loft a bit down from here. " +
        "There is a pile of hay down there, but thats about it. " +
        "To reach the loft you can not climb , but it seems " +
        "to be possible to jump down in the hay from the other end " +
        "of this beam, but from here it is too far. ";

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
desc_bottom()
{
    string text;

    if (nest)
    {
        text = "You bend down and look at the hole in the " +
               "bottom of the nest. Its too dark to see " +
               "anything up in there.\n";
        return text;
    }
    return "Examine what?";

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
               "up to the other end of the beam.\n";
}


string
desc_long()
{
    string text;

    text = "You are balancing on a thick wooden beam " +
           "high up under the ceiling. ";

    if (nest)
        text += "Close to you, hanging in the corner, is a large " +
            "wasp nest.";
    text += "\n";
    return text;
}

string
desc_nest()
{
    string text;

    if (nest)
    {
        text = "Its a big wasp nest and you can see a big wasp " +
            "crawl into the hole in the bottom of the nest.\n";
        return text;
    }
    text = "In the corner of the ridge and the wall is a wet " +
        "spot. Looks like some kind of a insects nest have " +
        "hung here lately, but now its gone.\n";
    return text;

}

int
catch_nest(string str)
{
    object bucket, wasp_nest;

    if (strlen(str) && (str == "nest") && (nest == 1))
    {
        write("Slowly and with great care you remove the " +
            "nest from the ceiling. You do not want to " +
            "be attacked up here by some furious killer " +
            "wasps and to your relief nothing dangerous " +
            "seems to happen.\n");
        say(({METNAME + " slowly removes the giant insect " +
               "nest from its place.\n",
            TART_NONMETNAME + " slowly removes the giant insect " +
               "nest from its place.\n",
            "You hear a buzzing sound close to you.\n"}), TP);
        tell_room(THIS_DIR + "beam1",
            ({METNAME + " slowly removes a giant insect " +
               "nest from its place.\n",
            TART_NONMETNAME + " slowly removes a giant insect " +
               "nest from its place.\n",
            ""}), TP);
        nest = 0;
        wasp_nest = clone_object(THIS_DIR + "/obj/wasp_nest");
        wasp_nest->move(TP);
        return 1;
    }
    return 0;
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
        ob = FILTER_OTHER_LIVE(FILTER_CAN_SEE(all_inventory(beam2), TP));
    if (CAN_SEE_IN_A_ROOM(TP, beam1))
        ob += FILTER_CAN_SEE(all_inventory(beam1), TP);

    if (!sizeof(ob))
    {
        text += "\n";
        return text;
    }

    text += " On the beam you can see "
         + COMPOSITE_WORDS(map(ob, "desc", TO)) + ".\n";
    return text;
}

string
desc_spot()
{
    string text;
    if (nest)
        text = "What spot?\n";
    else
        text = "The spot is nothing but a dark shadow on the wall.\n";
    return text;
}
