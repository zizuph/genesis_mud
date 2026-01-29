// Ziggurat Makeup-shop (ZIG_RL3 + "makeup.c")
// creator(s):   Zielia 2006
// last update:
// purpose:      Ziggurat shop where players can buy various cosmetics.
// note:
// bug(s):
// to-do:
#pragma strict_types

#include "zigg.h"
#include <macros.h>

inherit ZIG_ROOM;
inherit "/d/Avenir/inherit/shop";

#define STORE_ROOM   (ZIG_RL3 + "store_makeup")

public void
reset_room(void)
{
    fix_keeper();
}

public void
zig_room(void)
{
    set_short("cosmetics shop");
    set_long("Pale, dazzling light bounces off mirror-lined walls. "+
        "In front of the back wall, stands a simple, marble counter. "+
        "On top of the counter, several cherry-wood baskets elegantly "+
        "display the goods for sale and a carved wooden sign is propped up "+
        "next to a small silver bell.\n");

    set_store_room(STORE_ROOM);
    set_keeper_file(ZIG_MON + "lyrelle");
    set_favoured_race(({"elf", "gnome"}));
    set_suspected_race(({"hobbit"}));    // 'cause there aren't any in Avenir
    set_money_greed_buy(50);

    add_exit("room7", "east", 0);
    add_exit(STORE_ROOM, "store", wiz_check, 0, 1);

    add_cmd_item("bell", "ring", "@@do_ring");

    add_item("sign", "@@read_me");
    add_item("mirror", "@@see_mirror");
    add_item(({"mirrors", "walls", "wall"}), break_string(
        "All around the room, full length mirrors line the black stone "+
        "walls, reflecting the room from all angles. The mirrors are "+
        "lit by Source-crystals set into the walls all around them and "+
        "are angled slightly to avoid facing each other straight on.\n", 70));
    add_item("reflection", "@@reflect_me");
    add_item("reflections", "@@reflect_room");
    add_item(({"niche", "niches", "crystal", "crystals",}), break_string(
        "Set into the black stone wall all around the mirrors, small "+
        "source crystals are firmly set into niches carved to direct the "+
        "pale light toward the subject of the mirror's reflection.\n", 70));
    add_item(({"floor", "ground", "tiles"}), "@@see_floor");
    add_item(({"ceiling", "roof", "ceiling tiles"}), "@@see_ceiling");
    add_item(({"counter", "marble counter", "simple counter"}),
        "It seems to be made out of a solid slab of white marble swirled "+
        "with faint, dark lines.\n");
    add_item(({"bell", "small bell"}), "A shiny silver bell. It looks like "+
        "it would ring with a lovely, clear tone.\n");
    add_item(({"basket", "cherry-wood basket"}), "Which basket?\n");
    add_item(({"baskets", "cherry-wood baskets"}), break_string(
        "Glossy strips of cherry bark are woven into five tasteful baskets "+
        "and placed atop the counter. Each basket contains different items "+
        "for sale.\n", 70));

    /* special listing add_items */
    add_item(({"soaps", "soap basket", "first basket"}), "@@view_soap");
    add_item(({"pots", "mesdemets", "pots basket", "mesdemet basket",
        "second basket"}), "@@view_pots");
    add_item(({"brushes", "brush basket", "third basket"}), "@@view_brush");
    add_item(({"lotions", "lotion basket", "fourth basket"}), "@@view_lotion");
    add_item(({"pomades", "pomade basket", "fifth basket"}), "@@view_pomade");

    fix_keeper();
    config_shop();
}

/* Functions for listing what is for sale in each basket. */

public string
view_soap(void)
{
    write("You peer into the first cherry-wood basket to examine "+
        "its contents.\n\n");
    say(QCTNAME(TP) + " peers into the first cherry-wood basket to examine "+
        "its contents.\n");
    do_list("soaps");
    return "";
}

public string
view_pots(void)
{
    write("You peer into the second cherry-wood basket to examine "+
        "its contents.\n\n");
    say(QCTNAME(TP) + " peers into the second cherry-wood basket to examine "+
        "its contents.\n");
    do_list("pots");
    return "";
}

public string
view_brush(void)
{
    write("You peer into the third cherry-wood basket to examine "+
        "its contents.\n\n");
    say(QCTNAME(TP) + " peers into the third cherry-wood basket to examine "+
        "its contents.\n");
    do_list("brushes");
    return "";
}

public string
view_lotion(void)
{
    write("You peer into the fourth cherry-wood basket to examine "+
        "its contents.\n\n");
    say(QCTNAME(TP) + " peers into the fourth cherry-wood basket to examine "+
        "its contents.\n");
    do_list("lotions");
    return "";
}

public string
view_pomade(void)
{
    write("You peer into the fifth cherry-wood basket to examine "+
        "its contents.\n\n");
    say(QCTNAME(TP) + " peers into the fifth cherry-wood basket to examine "+
        "its contents.\n");
    do_list("pomades");
    return "";
}

/*
* Function name: do_sell
* Description:   Try to let the player sell the_item
* Returns:       1 on sucess, 0 fail; should always fail.
* Arguments:     str - string holding name of item, hopefully
*/
public int
do_sell(string str)
{
    if (keeper_speak("I only sell things, not buy them."))
    return 1;

    notify_fail("This shop only sells items, it doesn't buy them.\n");
    return 0;
}

/*
* Function name: do_buy
* Description:   Try to let the player buy the_item if not an infidel.
* Returns:       1 on sucess, 0 fail.
* Arguments:     str - string holding name of item, hopefully
*/
public int
do_buy(string str)
{
    if (!check_keeper())
    return 0;

    if (IS_INFIDEL(this_player()))
    {
    if (keeper_speak("I don't do business with criminals."))
        return 1;

    notify_fail("This shop does not conduct business with criminals.\n");
    return 0;
    }

    return ::do_buy(str);
}

/* Functions to describe the add_items as the player examines them */
string
reflect_me()
{
    write("You stand before one of the mirrors and examine your reflection:\n\n"+
        TP->long() +"\n");
    say(QCTNAME(TP) +" stands before one of the full length mirrors and examines "+
        HIS(TP) +" reflection.\n");

    return "";
}

string
reflect_room()
{
    write("All around the room, tall, lighted mirrors surround you, "+
        "reflecting the room back at you again and again:\n\n"+
        long() +"\n");

    return "";
}

string
see_mirror()
{
    write("You approach one of the mirrors and examine it more closely:\n\n"+
        "It is a full length mirror set into the black stone of the walls. "+
        "All around the mirror, tiny niches are carved into the stone, "+
        "each holding a glowing source-crystal, illuminating the reflections "+
        "for further examination.\n");

    say(QCTNAME(TP) +" approaches one of the full length mirrors, examining "+
        "it closely.\n");

    return "";
}

string
see_floor()
{
    write("You look down to carefully examine the floor:\n\n"+
        "The floor is covered with many heavy-looking marble tiles. "+
        "Set into every tile is a black, onyx triangle whose top point meets "+
        "the bottom point of a red, carnelian triangle. The pattern repeats "+
        "hundreds of times across the breadth of the floor, each hour-glass "+
        "figure standing out distinctly from the white marble surrounding "+
        "it.\n");

    say(QCTNAME(TP) +" looks down to carefully examine the floor.\n");

    return "";
}

string
see_ceiling()
{
    write("You look up to carefully examine the ceiling:\n\n"+
        "Set into every ceiling tile is a black triangle whose top point "+
        "meets the bottom point of a red triangle, each hour-glass figure "+
        "standing out distinctly from the white marble surrounding it. "+
        "The ceiling is tiled to precisely match the floor, furthering "+
        "the mirrored effect of the room and giving you the odd notion that "+
        "if you stayed in this mirrored room long enough, you'd lose track "+
        "of up and down, left and right.\n");

    say(QCTNAME(TP) +" looks up to carefully examine the ceiling.\n");

    return "";
}

/* Ring bell to summon shop keeper for service if missing. */
int
do_ring()
{

    write("You ring the bell, the sound resonating throughout the room.\n");
    say(QCTNAME(TP) +" rings the bell on the counter, and the ringing "+
        "resonates throughout the room.\n");

    if (!keeper)
    {
    fix_keeper();
    tell_room(TO, QCTNAME(keeper) +" glides towards you with "+
        "a polite smile on "+ HIS(keeper) +" face.\n");
    }
    else
    {
    keeper->command("emote breathes: Ta'haveth. How may I help you?");
    }

    return 1;
}

/* Functions for reading and examining the shop sign. */
string
read_me()
{
    write("              Cosmetics by Lyrelle\n"+
          "            ^^^^^^^^^^^^^^^^^^^^^^^^\n"+
          "  Lyrelle celebrates beauty with her finest, most luxurious\n"+
          "  line of beauty enhancements and indulgences.\n"+
          "\n"+
          "  This shop operates like any other. To see what items are\n"+
          "  for sale at this time, please use <list>.\n"+
          "\n"+
          "  Thank you for your patronage of Cosmetics by Lyrelle.\n");

    return "";
}

int
do_read(string str)
{
    notify_fail("Read what?\n");
    if (str != "sign")
        return 0;

    read_me();
    return 1;
}

/*
* Function name: do_get
* Description:   If the player attempts to get certain items in the room
*                gives a unique message about why they can't get them.
* Returns:       1 on sucess, 0 fail; should always fail.
* Arguments:     str - string anything the player tries to get or take.
*/
int
do_get(string str)
{
    string a;
    string b;

    parse_command(str, ({}), "%s 'from' [the] %s", a, b);

    if (item_id(b) && ( b == "basket" || b == "baskets" || b == "first basket"
    || b == "second basket" || b == "third basket" || b == "fourth basket"
    || b == "fifth basket" || b == "cherry-wood basket"
    || b == "cherry-wood baskets"))
    {
        write(keeper->query_The_name(TP) +" blocks your hand as "+
            "you reach toward the basket.\n");

        say(QCTNAME(TP) +" reaches toward one of the baskets, but "+
            keeper->query_the_name(TP) +" blocks "+ HIS(TP) +" hand.\n");

        keeper->command("say to "+ OB_NAME(TP) +" Please do not touch the "+
            "merchandise. If you'd like to see something I can <show> "+
            "it to you.");

        return 1;
    }

    if (item_id(b) && ( a == "crystal" || a == "source crystal"
    || a == "crystals" || a == "source crystals" ))
    {

        write("You try to pull a source crystal from one of the niches "+
            "but you find it firmly set into the stone wall.\n");

        say(QCTNAME(TP) +" tries to pull a source crystal from one of "+
            "the niches but seems unable to free it from the stone wall.\n");

        return 1;
    }

    else return 0;
}

/*
 * Function name:   init
 * Description:     Is called for each living that enters this room
 * Returns:
*/
public void
init(void)
{
    ::init();

    add_action(  do_get, "get"  );
    add_action(  do_get, "take" );

    init_shop();
}

/* Shop List customizations. */

public string
category(object ob)
{
    if (ob->id("soap"))
	return "Lather";

    if (ob->id("lotion"))
	return "Lotion";

    if (ob->id("pomade"))
	return "Pomade";
}
