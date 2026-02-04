/*
 * Dining room in the vampire manor
 * Louie 2006
 */  
#pragma strict_types
#include "defs.h"

inherit ROOM_DIR + "vamp_room";

#include <stdproperties.h>
#include <composite.h>
#include <macros.h>
#include <filter_funs.h>

#define AT_TABLE "_at_table"
#define AT_HEAD "_at_head"
#define AT_FOOT "_at_food"

//proto
string candelabra_desc();
string chairs_desc();
string head_desc();
string foot_desc();
int do_sit(string str);
int do_stand(string str); 
int do_light(string str); 
int do_extinguish(string str);
mixed filter_the_blind(object ob);

object head_taken;
object foot_taken;
int lit = 0;

void
create_room()
{
    ::create_room();
    set_short("dining room");
    set_long("This long rectangular room is the dining room "+
        "of the manor.  " +
        "Four candelabra decorate the walls, two on the north "+
        "wall and two on the south wall.  "+
        "The room is dominated by an immense wooden table, "+
        "surrounded by plush high-backed chairs.  "+
        "The chairs are all identical, although the chair at the "+
        "head of the table has been crafted to be larger than "+
        "all of the others.  "+
        "\n");

    add_exit("kitchen.c", "east");
    add_exit("entry.c", "southwest");

    add_item(({"candelabra","candelabras"}),
        "@@candelabra_desc@@");

    add_item(({"flint"}),
        "The flint near the candelabras is used to strike a spark.\n");
    
    add_item(({"tinder"}),
        "The tinder is used to catch the spark created by the flint.\n");

    add_item(({"punk","punks"}),
        "The punks are thin sticks of dried wood which will burn "+
        "slowly, and can therefor be used to light many candles.  "+
        "The punks are usually lit with the tinder.\n");

    add_item(({"chairs","high-backed chairs","high-backed chair",
        "plush chairs","plush chair","plush high-backed chairs",
        "plush high-backed chair", "table","chair"}),
        "@@chairs_desc@@");

    add_item(({"largest chair","largest high-backed chair",
        "largest plush chair","largest plush high-backed chair",
        "head chair","large chair","head","head of table",
        "table head","head of the table","larger chair",
        "chair at head of table","chair at the head of the table",
        "chair at the head of table"}),
        "@@head_desc@@");

    add_item(({"foot","foot of table","foot of the table"}),
        "@@foot_desc@@");

    add_item(({"southwest","entry hall","hall"}),
        "To the southwest is the main entry hall of the manor.\n");

    add_item(({"east","kitchen"}),
        "The kitchen lies to the east.\n");


}

string chairs_desc()
{
    string s = "The table is an immense slab of wood, polished to a "+
        "high shine.  It is surrounded by plush high-backed chairs, "+
        "while the head of the table has the largest chair.  "+
        "Both the head and foot of the table have only one chair "+
        "each.  ";

    mixed *everything = all_inventory(this_object());
    everything -= ({ this_player() });
    int i = sizeof(everything);
    mixed *sitting = ({});

    while (i--)
    {
        if (interactive(everything[i]) &&
            (everything[i]->query_prop(AT_TABLE)
             || everything[i]->query_prop(AT_HEAD)
             || everything[i]->query_prop(AT_FOOT)))
        {
            sitting += ({ everything[i] });
        }
    }
    
    if (this_player()->query_prop(AT_TABLE)) {
        s += "You are sitting at the table.  ";
    } else if (this_player()->query_prop(AT_HEAD)) {
        s += "You are sitting at the head of the table.  ";
    } else if (this_player()->query_prop(AT_FOOT)) {
        s += "You are sitting at the foot of the table.  ";
    }

    if (sizeof(sitting)) 
    {
        s += "The table is occupied by "+COMPOSITE_LIVE(sitting)+".  ";
    }

    return s+"\n";
}


string head_desc()
{
    string s = "The largest high-backed chair is at the head of the table.  ";

    if (this_player()->query_prop(AT_HEAD)) {
        s += "You are current sitting at there.  ";
    } else if (head_taken 
        && environment(head_taken) == this_object()
        && head_taken->query_prop(AT_HEAD))
    {
        s += head_taken->query_The_name(this_player())+" is currently sitting there.  ";
    } else {
        s += "It is currently empty.  ";
    }

    return s+"\n";
}

string foot_desc()
{
    string s = "There is a lone, normal chair at the foot of the table.  ";
    
    if (this_player()->query_prop(AT_FOOT)) {
        s += "You are currently sitting there.  ";
    } else if (foot_taken 
        && environment(foot_taken) == this_object()
        && foot_taken->query_prop(AT_FOOT))
    {
        s += foot_taken->query_The_name(this_player())+" is currently sitting there.  ";
    } else {
        s += "It is currently empty.  ";
    }

    return s+"\n";
}

string candelabra_desc()
{
    string s = "The four candelabra in the room are all identical, "+
        "with flint, tinder, and punks nearby for lighting.  ";

    if (lit) {
        s += "The candelabra are currently lit, flooding the room "+
            "with light until they are extinguished.  ";
    } else {
        s += "The candelabra are currently extinguished, until "+
            "someone lights them.  ";
    }

    s += "\n";
    return s;
}

void 
init()
{    
    ::init();
    add_action(do_sit, "sit");
    add_action(do_stand, "stand");
    add_action(do_light, "light");
    add_action(do_extinguish, "extinguish");
}

int do_extinguish(string str)
{
    if (!strlen(str))
    {
        notify_fail("Extinguish the candelabra?\n");
        return 0;
    }

    if (str != "candelabra"
        && str != "the candelabra")
    {
        notify_fail("Extinguish the candelabra?\n");
        return 0;
    }

    if (!lit)
    {
        notify_fail("The candelabra are not lit.\n");
        return 0;
    }

    object tp = this_player();
    if (tp->query_prop(AT_TABLE)
        || tp->query_prop(AT_HEAD)
        || tp->query_prop(AT_FOOT))
    {
        notify_fail("You cannot extinguish the candelabra "+
            "while sitting down.\n");
        return 0;
    }

    write("You walk from candle to candle, snuffing out the flames "+
        "one by one until all of the candelabra are dark.\n");
    say(QCTNAME(tp)+" walks from candle to candle, snuffing out the "+
        "flames one by one until all of the candelabra are dark.\n");

    add_prop(ROOM_I_LIGHT,
        query_prop(ROOM_I_LIGHT) - 10);
    lit = 0;

    return 1;

}
int do_light(string str) 
{
    if (!strlen(str))
    {
        notify_fail("Light the candelabra?\n");
        return 0;
    }

    if (str != "candelabra"
        && str != "the candelabra")
    {
        notify_fail("Light the candelabra?\n");
        return 0;
    }
    
    if (lit)
    {
        notify_fail("The candelabra are already lit.\n");
        return 0;
    }

    object tp = this_player();
    if (tp->query_prop(AT_TABLE)
        || tp->query_prop(AT_HEAD)
        || tp->query_prop(AT_FOOT))
    {
        notify_fail("You cannot light the candelabra while sitting down.\n");
        return 0;
    }

    write("You take the flint and create a tiny spark, catching "+
        "it with the tinder and igniting the end of a punk.  "+
        "Slowly you travel from candle to candle, lighting the "+
        "candelabra in their entirety.\n");
    say(QCTNAME(tp)+" takes the flint and creates a tiny spark, "+
        "catching it with the tinder and igniting the end of a punk.  "+
        "Slowly "+tp->query_pronoun()+" travels from candle to "+
        "candle, lighting the candelabra in their entirety.  \n");

    add_prop(ROOM_I_LIGHT,
        query_prop(ROOM_I_LIGHT) + 10);
    lit = 1;

    return 1;
}

int 
do_sit(string str)
{
    object tp = this_player();
    if (tp->query_prop(AT_TABLE)){
        notify_fail("You are already sitting at the table.\n");
        return 0;
    }

    if (tp->query_prop(AT_HEAD)) {
        notify_fail("You are already sitting at the head of the table.\n");
        return 0;
    }

    if (tp->query_prop(AT_FOOT)) {
        notify_fail("You are already sitting at the foot of the table.\n");
        return 0;
    }

    switch (str) {
        case "table":
        case "at table":
        case "at the table":
        case "down":
        case "down at table":
        case "down at the table":
        case "in chair":
        case "in high-backed chair":
        case "in plush chair":
        case "in plush high-backed chair":
        case "chair":
        case "high-backed chair":
        case "plush chair":
        case "plush high-backed chair":
            tp->catch_msg("You sit down at the table.\n");
            tell_room(this_object(),QCTNAME(tp)+" sits down at the table.\n",
               filter_the_blind(tp), tp);
            tp->add_prop(AT_TABLE, 1);
            tp->add_prop(LIVE_S_EXTRA_SHORT," sitting at the table");
            break;
        case "at head of the table":
        case "at the head of the table":
        case "at the head of table":
        case "at head of table":
        case "at head":
        case "head":
        case "largest chair":
        case "largest high-backed chair":
        case "in largest chair":
        case "in largest high-backed chair":
        case "in the largest chair":
        case "in the largest high-backed chair":
            if (head_taken) {
                if (environment(head_taken) == this_object()
                    && head_taken->query_prop(AT_HEAD)) 
                {
                    if (CAN_SEE_IN_ROOM(tp) && CAN_SEE(tp, head_taken)) {
                        notify_fail(head_taken->query_The_name(tp) + 
                            " is already sitting at the head "+
                            "of the table.\n");
                    } else {
                        notify_fail("It appears someone is already "+
                            "sitting at the head of the table.\n");
                    }
                    return 0;
                }
                //Nobody is really there, reset it
                head_taken = 0;
            }
            tp->catch_msg("You sit down in the high-backed chair "+
                "at the head of the table.\n");
            tell_room(this_object(),QCTNAME(tp)+" sits down in the high-backed "+
                "chair at the head of the table.\n",
                filter_the_blind(tp), tp);
            tp->add_prop(AT_HEAD, 1);
            tp->add_prop(LIVE_S_EXTRA_SHORT," sitting at the head of the table");
            head_taken = tp;
            break;
        case "at foot of the table":
        case "at the foot of the table":
        case "at the foot of table":
        case "at foot of table":
        case "at foot":
        case "foot":
            if (foot_taken) {
                if (environment(foot_taken) == this_object()
                    && foot_taken->query_prop(AT_FOOT)) 
                {
                    if (CAN_SEE_IN_ROOM(tp) && CAN_SEE(tp, foot_taken))
                    {
                        notify_fail(foot_taken->query_The_name(tp)+ 
                            " is already sitting at the foot "+
                            "of the table.\n");
                    } else {
                        notify_fail("It appears someone is already "+
                            "sitting at the foot of the table.\n");
                    }
                    return 0;
                }
                //Nobody is really there, reset it
                foot_taken = 0;
            }

            tp->catch_msg("You sit down at the foot of the table.\n");
            tell_room(this_object(),QCTNAME(tp)+" sits down at the foot "+
                "of the table.\n",
                filter_the_blind(tp), tp);
            tp->add_prop(AT_FOOT, 1);
            tp->add_prop(LIVE_S_EXTRA_SHORT," sitting at the foot of the table");
            foot_taken = tp;
            break;
        default:
            notify_fail("Sit at the table, at the head of the table, "+
                "or at the foot of the table?\n");
            return 0;
    }

    return 1;

}

int 
do_stand(string str)
{
    if (strlen(str && str != "up"))
    {
        notify_fail("Stand up?\n");
        return 0;
    }

    object tp = this_player();

    if (tp->query_prop(AT_TABLE)) {
        tp->catch_msg("You stand up from the table.\n");
        tell_room(this_object(),QCTNAME(tp)+" stands up from the table.\n",
            filter_the_blind(tp), tp);
        tp->remove_prop(AT_TABLE);
        tp->remove_prop(LIVE_S_EXTRA_SHORT);
    } else if (tp->query_prop(AT_HEAD)) {
        tp->catch_msg("You stand up from the head of the table.\n");
        tell_room(this_object(),QCTNAME(tp)+" stands up from "+
            tp->query_possessive()+
            " place at the head of the table.\n",
            filter_the_blind(tp), tp);

        tp->remove_prop(AT_HEAD);
        tp->remove_prop(LIVE_S_EXTRA_SHORT);
        head_taken = 0;
    } else if (tp->query_prop(AT_FOOT)) {
        tp->catch_msg("You stand up from the foot of the table.\n");
        tell_room(this_object(),QCTNAME(tp)+" stands up from "+
            tp->query_possessive()+
            " place at the foot of the table.\n",
            filter_the_blind(tp), tp);
        tp->remove_prop(AT_FOOT);
        tp->remove_prop(LIVE_S_EXTRA_SHORT);
        foot_taken = 0;
    } else {
        notify_fail("You are not sitting at the table.\n");
        return 0;
    }

    return 1;
}


void leave_inv(object ob, object to)
{
    ::leave_inv(ob, to);    
    
    if(!objectp(to) || !objectp(ob))
            return;
            
    if (!interactive(ob))
        return;

    if (ob->query_prop(AT_TABLE)) {
        ob->catch_msg("You stand up from the table.\n");
        ob->remove_prop(AT_TABLE);
        ob->remove_prop(LIVE_S_EXTRA_SHORT);
    } else if (ob->query_prop(AT_HEAD)) {
        ob->catch_msg("You stand up from the head of the table.\n");
        ob->remove_prop(AT_HEAD);
        ob->remove_prop(LIVE_S_EXTRA_SHORT);
        head_taken = 0;
    } else if (ob->query_prop(AT_FOOT)) {
        ob->catch_msg("You stand up from the foot of the table.\n");
        ob->remove_prop(AT_FOOT);
        ob->remove_prop(LIVE_S_EXTRA_SHORT);
        foot_taken = 0;
    } 
}

mixed
filter_the_blind(object ob) {
    mixed all = all_inventory(this_object());
    mixed result = ({ ob });
    
    if (!all || !sizeof(all)) {
         return result;
    }

    mixed peeps = FILTER_LIVE(all);
    int i;
    if (!peeps || !(i = sizeof(peeps))) {
         return result;
    }

    while (i--) {
        if (!CAN_SEE_IN_ROOM(peeps[i]) || !CAN_SEE(peeps[i], ob)) {
            result += ({ peeps[i] });
        }
    }

    return result;

}