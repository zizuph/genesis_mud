/* Include this file in a room to add a seat. ~mucalytic/std/seat */

/* To use this, you'll have to add these two lines somewhere in create_room()
 *
 * set_seat_name(string seat_name);
 * add_item(string seat_name, "@@query_seated");
 * 
 * In your room's init(), you need to put the following line:
 *
 * init_seat();
 *
 */

#include "/sys/macros.h"
#include "/sys/language.h"
#include "../master_defs.h"
#include "/sys/stdproperties.h"

object rest;
int rest_alarm;
string seat_name = "none";

#define NOT_DO	({ "bounce", "bow", "caress", "cower", "cringe", "cuddle", \
                   "curtsey", "dance", "fawn", "flip", "grovel", "hug", \
                   "kick", "knee", "nibble", "pat", "poke", "ruffle", "slap", \
                   "spank", "stomp", "strut", "tackle", "tickle", "wiggle", \
                   "worship", "n", "s", "e", "w", "u", "d", "ne", "nw", "se", \
                   "sw", "north", "south", "east", "west", "up", "down", \
                   "northeast", "northwest", "southeast", "southwest", "vis", \
                   "invis", "invisible", "kill", "do", "sweep", "search", \
                   "backstab", "hide", "sneak", "steal", "track", "fireball", \
                   "quit" })

void init_seat()
{
    add_action("sit", "sit");
    add_action("sit", "rest");
    add_action("stand", "stand");
}

void set_seat_name(string str)
{
    seat_name = str;
}

string query_seat_name()
{
    return seat_name;
}

string query_seated()
{
    if(!rest)
        return "";
    else if(rest == TP)
        return("You are sitting on it.");
    else
        return(TP->check_call(QCTNAME(rest))+" is sitting on it.");
}

int sit(string str)
{
    if(rest == TP)
    {
        write("You are already resting. (To stop resting, type: 'stand').\n");
        return 1;
    }
    else if(rest)
    {
        write(break_string("You try to sit on the "+seat_name+", but cannot "+
            "because "+TP->check_call(QTNAME(rest))+" is already sitting on "+
            "it.\n", 75));

        say(break_string(QCTNAME(TP)+" tries to sit on the "+seat_name+", "+
            "but finds that "+TP->check_call(QTNAME(rest))+" is already "+
            "sitting on it.\n", 75));
        return 1;
    }

    rest = TP;

    say(QCTNAME(TP)+" sits down on the "+seat_name+".\n");
    write(break_string("You feel deeply relaxed and the aches from your "+
        "body seem to be soothing themselves away almost as soon as you "+
        "sit down.\n", 75));

    TP->add_fatigue(2);
    TP->add_prop(LIVE_S_SOULEXTRA, "sitting on "+LANG_ADDART(seat_name));

    if(!TP->query_prop(LIVE_S_EXTRA_SHORT))
        TP->add_prop(LIVE_S_EXTRA_SHORT, " (sitting on "+
            LANG_ADDART(seat_name)+")");

    TP->add_prop(OBJ_M_NO_ATTACK, "You cannot attack someone while "+
                                  "they are resting!\n");

    rest_alarm = set_alarm(10.0, 10.0, "rest_traveller");

    add_action("catch_all", "", 1);
    return 1;
}

int stand()
{
    if(rest != TP)
    {
        write("You are already standing!\n");
        return 1;
    }

    write("Ok.\n");
    say(QCTNAME(rest)+" stands up from the "+seat_name+".\n");

    TP->remove_prop(OBJ_M_NO_ATTACK);
    TP->remove_prop(LIVE_S_SOULEXTRA);
    TP->remove_prop(LIVE_S_EXTRA_SHORT);

    remove_alarm(rest_alarm);

    rest = 0;
    return 1;
}

void rest_traveller()
{
    TP->add_fatigue(2 + random(2));
}

int catch_all(string arg)
{
    string action;

    if (!rest || rest != TP)
        return 0;

    action = query_verb();

    if(action == "sit")
    {
        sit("");
        return 1;
    }
    else if(action == "stand")
    {
        stand();
        return 1;
    }
    else if(member_array(action, NOT_DO) != -1)
    {
        write("You must 'stand' before you can do that!\n");
        return 1;
    }
    else
        return 0;
}
