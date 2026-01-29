/*
 * /d/Gondor/anorien/cairandros/obj/dicecup.c
 *
 * Dice in a cup, presumably soldiers gamble with them
 *
 * Varian - March, 2020
 *
 */

#pragma strict_types

#include "../../defs.h"
#include <stdproperties.h>
#include <macros.h>

inherit "/std/object";
inherit "/lib/keep";

int do_read(string str);
int do_toss(string str);

#define DIE1    one_of_list(markings)
#define DIE2    one_of_list(markings)
#define DIE3    one_of_list(markings)
#define DIE4    one_of_list(markings)
#define DIE5    one_of_list(markings)

public void
create_object()
{
    set_name("_dice_cup_");
    add_name( ({"dice cup", "cup", "cup of dice", "dice"}) );

    set_adj("leather");

    set_short("leather cup of dice");
    set_pshort("leather cups of dice");

    set_long("This is a leather cup with five dice tucked inside. " +
    	"The dice themselves are small bone cubes with markings " +
    	"on each face. You could <toss dice> to toss the dice " +
    	"and see what rolls out.\nThere appear to be some rules " +
    	"printed on the bottom of the cup.\n");

    add_item( ({"dice", "bone dice"}),
    	"There are five dice inside your leather cup here. Each die " +
    	"is made from bone and has been cut into cubes. The six " +
    	"faces of the cube each have a unique marking carved into " +
    	"it; the markings are as follows: Tree, Star, Crown, Sword, " +
    	"Coin and Rod. The dice are from Gondor and the common folk " +
    	"there have their own rules for playing, often using them " +
    	"to gamble with.\n");
    add_item( ({"rules", "dice rules"}),
    	"@@rules@@");

    add_prop(OBJ_I_VALUE,     1);
    add_prop(OBJ_I_VOLUME,  100);
    add_prop(OBJ_I_WEIGHT,  100);
}

string
rules()
{
    write("The Gondorian rules of the dice in your leather cup are " +
    	"fairly simple, every person playing will toss the dice from " +
    	"the cup once. The highest ranking roll would be a five of " +
    	"a kind, followed by four of a kind, followed by three of a " +
    	"kind plus a pair, followed by two pairs, followed by a " +
    	"single pair and lastly a single high die. The markings are " +
    	"ranked from highest to lowest as follows: Tree, Star, " +
    	"Crown, Sword, Coin and Rod. The marking ranks are only used " +
    	"if two or more people playing have tied in their roll. Any " +
    	"players tied with identical throws will re-roll amongst " +
    	"themselves (omitting any players who rolled lower) to see " +
    	"who has won that round.\n");
}

/*
* Function name: query_auto_load()
* Description  : Checks if this object should be loaded at login
* Arguments    : None
*/

public string
query_auto_load()
{
return MASTER;
}

public int
do_read(string str)
{
    if(!strlen(str))
    {
        notify_fail("What did you want to read?\n");
        return 0;
    }

    if((str != "the rules") && (str != "rules") &&
        (str != "dice rules") && (str != "the dice rules"))
    {
        notify_fail("Read what, the dice rules?\n");
        return 0;
    }

    write("The Gondorian rules of the dice in your leather cup are " +
    	"fairly simple, every person playing will toss the dice from " +
    	"the cup once. The highest ranking roll would be a five of " +
    	"a kind, followed by four of a kind, followed by three of a " +
    	"kind plus a pair, followed by two pairs, followed by a " +
    	"single pair and lastly a single high die. The markings are " +
    	"ranked from highest to lowest as follows: Trees, Stars, " +
    	"Crowns, Swords, Coins and Rods. The marking ranks are only " +
    	"used if two or more people playing have tied in their roll. " +
    	"Any players tied with identical throws will re-roll amongst " +
    	"themselves (omitting any players who rolled lower) to see " +
    	"who has won that round.\n");

    return 1;
}

public int
do_toss(string str)
{
	object die1, die2, die3, die4, die5;
    if(!strlen(str))
    {
        notify_fail("What did you want to toss?\n");
        return 0;
    }

    if((str != "the dice") && (str != "bone dice") &&
    	(str != "the cup") && (str != "cup of dice") &&
    	(str != "the cup of dice") && (str != "cup") &&
    	(str != "the leather cup") && (str != "leather cup of dice") &&
    	(str != "the leather cup of dice") && (str != "leather cup") &&
        (str != "dice") && (str != "the bone dice"))
    {
        notify_fail("Toss what, the cup of dice?\n");
        return 0;
    }

    write("You toss the dice!\n");
    SAYBB(" tosses some dice from a leather cup!");

    setuid();
    seteuid(getuid());
    die1 = clone_object(AN_OBJ_DIR + "die1");
    die2 = clone_object(AN_OBJ_DIR + "die2");
    die3 = clone_object(AN_OBJ_DIR + "die3");
    die4 = clone_object(AN_OBJ_DIR + "die4");
    die5 = clone_object(AN_OBJ_DIR + "die5");
    die1->move(environment(this_player()), 1);
    die2->move(environment(this_player()), 1);
    die3->move(environment(this_player()), 1);
    die4->move(environment(this_player()), 1);
    die5->move(environment(this_player()), 1);
    this_player()->command("gatem _mark");
    this_player()->command("getem _mark");
    this_player()->command("gitem _mark");
    this_player()->command("gotem _mark");
    this_player()->command("gutem _mark");
    /*die1 = remove_object(AN_OBJ_DIR + "die1");
    die2 = remove_object(AN_OBJ_DIR + "die2");*/

    return 1;
}

public void
init()
{   
    ::init();
    add_action(do_read, "read");
    add_action(do_toss, "toss");
}