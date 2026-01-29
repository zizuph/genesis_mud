/*
 * monk_occtrain1.c
 *
 * This was once a part of the domain Roke.
 * Cleaned up and moved into Khalakhor by Glindor, Nov 2001.
 */

/* Ged */

#pragma save_binary
#pragma strict_types

inherit "/std/room";

#include "defs.h"
#include <macros.h>
#include <filter_funs.h>
#include <wa_types.h>

int torn, burned, debug;

varargs void
set_debug(int val = 1)
{
    debug = val;
}

void
reset_room()
{
    object *players;

    if (torn || burned)
    {
        players = FILTER_PLAYERS(all_inventory());
        if (sizeof(players) == 0)
        {
            torn = 0;
            burned = 0;
        }
    }
}

string
my_long()
{
    string str;

    str = "This is the largest room you have seen in the abandoned " +
          "building. Dust and cobwebs fill the room, like ragged " +
          "sheets on a hundred clotheslines.\n";
    if (torn)
    {
        str += "Someone has torn the cobwebs, making it possible to " +
               "pass through to the east.\n";
    }
    else if (burned)
    {
        str += "Someone has burned the cobwebs, making it possible to " +
               "pass through to the east.\n";
    }
    return str;
}

string
cobweb()
{
    if (torn)
    {
        return
            "The cobwebs, which are full of small spiders, fill the " +
            "room. A big rift through it lets you pass east.\n";
    }
    else if (burned)
    {
        return
            "The cobwebs are burned, leaving a passage to the east.\n";
    }
    else
    {
        return 
            "The cobwebs, which are full of small spiders, fill the room " +
            "completely covering the east wall. " +
            "You could try to cut your way through to the other side.\n";
    }
}

void
create_room()
{
    set_short("large room");
    set_long("@@my_long");

/*
    set_long("This is the largest training room in the monastery. You can see many\n" +
             "priests in training. They look very concentrated. In the far end of the room\n" +
             "you can see the chief-instructor. He is willing to teach you everything he\n" +
             "knows about unarmed combat and other skills.\n" +
             "You can see a big door behind him but you can't see into the next room.\n" +
             "There is a new sign on the wall.\n");

    add_prop(ROOM_M_NO_ATTACK,
             "You can not do that while on Sacred ground.\n");
    add_item(({"instructor", "chief-instructor"}),
             "He looks sturdy and you can see that he knows alot about all " +
             "fighting styles.\n");

    add_item(({"priest", "priests"}),
             "They are training very hard indeed.\n");
    add_item("sign", "You should read it.\n");
    add_cmd_item("sign", "read", "You can now choose " +
                 "between unarmed and armed combat. Simply pray for either: " +
                 "polearm skill or unarmed combat.\n");
*/

    add_item(({"web", "cobweb", "cobwebs"}), "@@cobweb");
    add_item(({"spider", "spiders"}),
             "Though small they look rather nasty and you are afraid to " +
             "disturb the web since you don't want them over you.\n");
    INSIDE;

    add_exit("monk_h2", "west");
    add_exit("monk_occtrain2", "east", "@@block", 1, 1);
    reset_room();
}

int
block()
{
    if (torn || burned)
        return 0;
    
    write("The cobwebs completely block your way east.\n");
    return 1;
}

void
init()
{
    ::init();

    add_action("cut", "cut");
    add_action("burn", "burn");
}

void
spider_rain_obj(object who, object cause)
{
    int t, n;
    object spider;
    string str;

    if (who != cause)
        n = random(2) + random(2);
    else
        n = 4 + random(5);
    
    if (n == 0) return;

    if (n == 1)
        str = "A small spider falls ";
    else if (n == 2)
        str = "Two small spiders fall ";
    else if (n < 5)
        str = "Some small spiders fall ";
    else
        str = "A lot of small spiders fall ";

    who->catch_msg(str + "down on you from the cobweb.\n");
    tell_room(environment(who), str + "down on " +
              QTNAME(who) + " from the cobweb.\n", who);

    for (t = 0; t < n; t++)
    {
        spider = clone_object(ROKEDIR + "npc/smallspider");
        spider->move(who, 1);
    }
}

void
spider_rain(object cause)
{
    object *players;
    
    if (!objectp(cause))
        cause = this_player();

    players = FILTER_PLAYERS(all_inventory(environment(cause)));
    map(players, &spider_rain_obj(,cause));
}

int
cut(string str)
{
    int slash, i;
    object *weapons;

    if (!str || !parse_command(str, ({}), "[through] 'web' / 'cobweb'"))
    {
        NF("Cut what?\n");
        return 0;
    }
    
    if (torn)
    {
        write("Someone has already cut down the cobweb.\n");
        return 1;
    }

    if (burned)
    {
        write("The cobweb has burned, leaving nothing much to cut.\n");
        return 1;
    }

    // You need something sharp
    slash = 0;
    weapons = this_player()->query_weapon(-1);
    for (i = 0 ; i < sizeof(weapons) ; i++)
        if (weapons[i]->query_dt() & W_SLASH)
        {
            slash = 1;
            break;
        }
    
    if (!slash)
    {
        write("You need something sharp to cut through the cobweb.\n");
        return 1;
    }

    if (!debug && random(5))
    {
        write("You make a clean cut through the cobweb, hardly disturbing " +
              "it at all. It looks like you can get through to the east " +
              "now.\n");
        say(QCTNAME(TP) + " makes a clean cut through the cobweb, revealing " +
            "a passage to the east.\n");
    }
    else
    {
        write("You cut through the cobweb and make an opening to the east. " +
              "Your cut has shook the cobweb a lot though, and you eye the " +
              "small spiders nervously.\n");
        say(QCTNAME(TP) + " cuts through the cobweb, revealing " +
            "a passage to the east.  The cobweb is shaking a lot though, " + 
            "and you eye the small spiders nervously.\n");
        set_alarm(0.0, 0.0, &spider_rain(this_player()));
    }
    torn = 1;
    return 1;
}

void
fire_rain_obj(object who)
{
    int dam, hp, rel;
    string str;

    dam = 50 + random(100);
    hp = who->query_hp();
    rel = (hp < dam) ? 100 : dam * 100 / hp;

    if (rel < 10)
        str = "slightly";
    else if (rel < 50)
        str = "badly";
    else
        str = "horribly";

    who->catch_msg("You are hit by some of the falling cobwebs and are " +
                   str + " burnt.\n");
    tell_room(environment(who), QCTNAME(who) + " is hit by some falling " +
              "cobwebs and is " + str + " burnt.\n", who);

    who->heal_hp(-dam);
    if (who->query_hp() <= 0)
        who->do_die(this_object());
}

void
fire_rain(object cause)
{
    object *players;
    
    players = FILTER_PLAYERS(all_inventory(environment(cause)));
    tell_room(this_object(),
              "Burning cobwebs start to fall down all over the room.\n");
    map(players, &fire_rain_obj());
}

int
burn(string str)
{
    object *torch;

    if (str != "web" && str != "cobweb")
    {
        NF("Burn what?\n");
        return 0;
    }

    torch = filter(all_inventory(TP), &->query_prop(OBJ_I_HAS_FIRE));

    if (sizeof(torch) == 0)
    {
        write("You don't have any fire!\n");
        return 1;
    }
    
    if (torn)
    {
        write("Someone has cut through the cobweb, so there is not much " +
              "point in burning it.\n");
        return 1;
    }

    if (burned)
    {
        write("The cobweb is already burned.\n");
        return 1;
    }

    // Burning is less likely to fail, but hurts more
    if (!debug && random(10))
    {
        write("You carefully set the cobwebs on fire. Large parts of the " +
              "cobwebs and spiders are slowly devoured, leaving an " +
              "opening to the east.\n");
        say(QCTNAME(TP) + " carefully burns the cobwebs, revealing " +
            "a passage to the east.\n");
    }
    else
    {
        write("As you put the flame to the cobwebs they ignite " +
              "instantly, and burn violently. Through the damaged " +
              "cobwebs you see an opening to the east.\n");
        say(QCTNAME(TP) + " puts a flame to the cobwebs, and they start " +
            "to burn violently. Through the damaged cobwebs you see an " +
            "opening to the east.\n");
        set_alarm(1.0, 0.0, &fire_rain(TP));
    }
    burned = 1;
    return 1;
}
