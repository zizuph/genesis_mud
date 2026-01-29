// This is the standard lake room.
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

inherit "/std/room";
string query_action();
int drift_boat(object ob);
float time_to_drift;
int query_time_to_drift();
int drift_alarm;
int time_init;
int start_drift(object ob);



string
long_description()
{
    string long_desc = "You are " + query_action() + " a small lake. " +
        "The lake is surrounded by high growing reeds which prevents " +
        "closer examination of the shores. You see various trees that looks like " +
        "large oaks, but its hard to tell what kind they are from here. " +
        "You can also look in any direction to get a better view " +
        "of that part of the shore.\n";

    return long_desc;
}


void
enter_inv(object ob, object old)
{

    ::enter_inv(ob, old);
    if (ob->id("_boat"))
    {
        start_drift(ob);
    }
    if (this_object()->query_prop(X))
        tell_room(environment(this_player()), "The wind dies out and " +
            "the water is very calm around you.\n");

}

void
leave_inv(object ob, object to)
{
::leave_inv(ob, to);
if (ob->id("_boat") && (drift_alarm))
    remove_alarm(drift_alarm);
}

int
start_drift(object ob)
{
    time_init = time();

    // Quicker drift if the boat is empty
    if (sizeof(FILTER_PLAYERS(all_inventory(ob))))
        time_to_drift = ((rnd() * 400.0) + 300.0);
    else
        time_to_drift = ((rnd() * 60.0) + 5.0);

    if (this_object()->query_prop(X))
         time_to_drift = ((rnd() * 60.0) + 9.0);

    drift_alarm = set_alarm(time_to_drift, 0.0, &drift_boat(ob));
    return 1;
}

int
query_time_to_drift()
{
    if (time_to_drift)
        return ((ftoi(time_to_drift) + time_init) - time());
    else
    return 0;
}

int
query_drift_alarm()
{
    return drift_alarm;
}

int
drift_boat(object ob)
{
    if (present(ob, TO))
        ob->drift();
    if (drift_alarm)
        remove_alarm(drift_alarm);
}

string
query_action()
{
    if (ENV(TP)->id("boat"))
        return "rowing on";
    return "swiming in";
}


void
make_the_room()
{
    set_long(&long_description());
    set_short("A small lake");
}

string
desc_east()
{
    string text;

    text = "Looking at the east shore you can see the thick " +
        "reed growing close to the brink making it impossible " +
        "to row there. On the slope behind are some large trees " +
        "growing. ";

    if (query_prop(ROCK))
        text += "Behind the trees you see a glimpse of a " +
            "huge rock.\n";
    else
        text += "\n";
    return text;
}

string
desc_north()
{
    string text;

    text = "Looking north you see some hills. " +
        "The slopes are rather steep, but do not look " +
        "to hard to climb. ";

    if (query_prop(MILL))
        text += "Behind the hill ridge you can see a " +
            "weather mill, or at least a part of it. A " +
            "roof and two of its vanes are clearly " +
            "visible from here.\n";
    else
        text += "\n";
    return text;
}

string
desc_south()
{
    string text;

    text = "The land to the south is open areas stretching out " +
        "far away. They rise slowly above the lake until the " +
        "ridge of a hill which is as far you can see. ";

    if (query_prop(HOUSE))
        text += "Close to the lake is a small house.\n";
    else
        text += "\n";
    return text;

}

string
desc_west()
{
    string text;

    text = "The view to the west is blocked by trees growing " +
        "close to the lake. The reed is also spreading out " +
        "quite a bit into the lake in that direction. ";

    if (query_prop(TOWER))
        text += "Above the tree tops you can see the upper parts " +
        "of the mansion. The tower windows reflects some light " +
        "and it looks almost like a lighthouse from down here. \n";
    else
    if (random(1))
        text += "There is nothing else to see from here.\n";
    else
        text += "You are too close to the west side of the lake " +
            "to see anything of the mansion as the trees are " +
            "blocking your view.\n";
    return text;
}

int
reed(string str)
{
    write("The thick reed " +
        "growing close to the brink prevents you from " +
        "coming closer.\n");
    return 1;
}


string
desc_oaks()
{
        return "You try to study the oaks that grows on the east " +
            "shore but you are to far to see any details. They " +
            "look very old and beautiful but that's all there is " +
            "to be seen from here. Looking in the other directions " +
            "isnt better, except from that you get a better grip " +
            "of the surroundings. There are no oaks to be seen " +
            "on those shores.\n";
}


string
desc_rock()
{
    return "You cant see much of the rock from " +
            "this distance. But its quite obvious " +
            "that it is a very big and tall rock.\n";
}

string
desc_tower()
{
        return "You stretch up and look up at the " +
            "mansion tower. The sun reflects in its " +
            "windows and it looks very beautiful from " +
            "down here. You cant see any other part " +
            "of the mansion from this location.\n";
}

string
desc_mill()
{

        say(QCTNAME(TP) + " stands up in the boat and looks " +
            "north. As the sudden movement rocks the boat a bit " +
            (TP->query_possessive()) + " sits down " +
            "quickly again.\n");
        return "You stand up in the rickety boat to get a " +
            "better look. A bit behind the hill ridge you " +
            "can see a bit of the roof and two of the vanes " +
            "of the mill. The vanes stand in a ten to two " +
            "position but thats about it.\nYou sit down " +
            "again before the boat should capsize of you " +
            "loosing your balance.\n";
}

string
desc_house()
{

        return "The house looks abandoned from what you can " +
            "see from here. Broken windows, a broken " +
            "door hanging on only one hinge and a garden " +
            "that no one have touched for many years. The " +
            "building stands in a small grove of birches " +
            "making it hard to see from another angle than " +
            "this one.\n";
}

string
desc_shores()
{
    return "The reed is preventing a closer examination " +
        "of the shores around the lake.\n";
}

string
desc_water()
{
    int i = random(4);

    if (this_object()->query_prop(X))
        return "You look down into the water and see some fish " +
            "pass by.\nThen suddenly you see it. First its " +
            "only a shadow, but when you look carefully you see " +
            "the contures of a sunken boat down there.\n";

    switch(i)
    {
        case 0:
            return "You look out over the water and feel a cool " +
                "breeze in your face.\n";
            break;
        case 1:
            say(QCTNAME(TP)+ " sticks " +TP->query_possessive()+
                " hand into the water. From the looks of "
                +TP->query_possessive()+ " face, it must be " +
                "very cold in the water.\n");
            return "You stick your right hand into the water. Brr, " +
                "its very cold and you are happy you do not have " +
                "to take a swim in it.\n";
            break;
        case 2:
            return "Sunlight is glittering on the surface and " +
                "you feel the boat rock slightly in the waves.\n";
            break;
        case 3:
            return "You try to get a glimpse of the bottom of the " +
            "lake, but its all dark down there.\n";
        break;
    }
}

string
desc_bottom()
{
if (this_object()->query_prop(X))
        return "You look down into the water and see some fish " +
            "pass by.\nThen suddenly you see it. First its " +
            "only a shadow, but when you look carefully you see " +
                "the contures of a wreck or a sunken boat down " +
                "there.\n";

return "You try to get a glimpse of the bottom of the " +
            "lake, but its all dark down there.\n";
}

string
desc_sunken_boat()
{
    string text;

if (this_object()->query_prop(X))
{
    text = "Now that you know about it, you can clearly see " +
        "the sunken boat down there. It looks very much the " +
        "same as the boat you sit in yourself. ";
    if (this_object()->query_sack())
        text += "In its stern you can see some kind of an " +
            "oilskin sack.";
    text += "\n";
    return text;
    }

    return "What?\n";
}

string
desc_sack()
{
    string text;

    if ((TO->query_prop(X)) && (TO->query_sack()))
    {
        text = "You can not see much of the sack from " +
            "up here. But it seems to be lying free from " +
            "other objects so it might be possible to " +
            "get it, if only you had something to get " +
            "it with.\n";
        return text;
    }
    return "What?\n";
}
