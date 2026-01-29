/*
 * This is the room that allows the player to get himself a steed.
 * It will decide the maximum age of the steed and check that the
 * name has not been used before.
 */

inherit "/std/room";
inherit "/lib/trade";

#include <std.h>
#include <macros.h>
#include <stdproperties.h>
#include "steed.h"

#define NUM             sizeof(MONEY_TYPES)
#define STEED_PRICE         26000
/*
 * List of names previously used
 */
string *used_names;

/*
 * Mapping with an array for each horse in existance.  Format is:
 *
 *  "owner" : ({ time_of_purchase, "name", time_of_death, number_of_steeds })
 *
 */
mapping horses;

/*
 * Function name: create_room
 * Description:   Set up the room description and restore any saved
 *                list of names etc.
 */
void
create_room()
{
    set_short("Rhun Transportation Merchants");
    set_long(break_string("You are standing in a large dark and shabby"+
			  " office with pictures placed around the walls and"+
			  " a large counter made of ironwood.  Behind the desk"+ 
			  " is an officious looking person staring at you"+
			  " impatiently.  Directly behind him is a large sign\n", 76));

    add_item("sign", "There seems to be some form of writing on it!\n");

    add_cmd_item( ({ "sign", "writing" }),
		  "read",
		  "                       Tuor's Horse Yards.\n"+
		  "                      We provide the finest\n"+
		  "                       horses in Rhovanion\n"+
		  "                           Instructions.\n"+
		  "1)..To get a horse type buy steed.  To own a horse you must\n"+
		  "    be an elf or human.  Wargs and Ponies are available at other\n"+
		  "    locations in Rhovanion and Middle Earth\n"+
		  "2)..Enter the name of your mount as asked.  Please note\n"+
		  "    the steed cannot be the name of a player on the game.\n"+
		  "3)..Type in the long description of your horse including its\n"+
		  "    colour and notable features.  Do not put in offensive\n"+
		  "    descriptions or I will make a standard long description\n"+
		  "4)..Input an adjective to describe your steed\n"+
		  "5)..Insert a second adjective to describe your steed\n" +
		  "6)..Horses currently cost " + text(split_values(STEED_PRICE)) +
		  " to purchase\n");

    add_prop(ROOM_I_INSIDE, 1);

    config_default_trade();

    /*
     * Set our effective uid so we can read the save file
     */
    seteuid(getuid());

    /*
     * If the save file does not exist, put in empty arrays
     */
    if (!restore_object(REGISTRY)) {
	used_names = ({});
	horses = ([]);
    }
}

/*
 * Function name: init
 * Description:   Set up commands we need to handle the purchase of horses
 */
void
init()
{
    ::init();

    add_action("do_purchase", "purchase");
    add_action("do_purchase", "buy");
}

/*
 * Function name: do_purchase
 * Description:   Let the player purchase a steed for himself.
 * Arguments:     arg - the rest of the command given
 * Returns:       1 - command successful
 *                0 - command not successful
 */
int
do_purchase(string arg)
{
    mixed what;

    notify_fail(capitalize(query_verb()) + " what?\n");
    if (arg != "steed")
	return 0;
    what = horses[this_player()->query_real_name()];
    if (!pointerp(what))
	what = 0;
    if (what && !what[2]) {
	write("You already have a steed.\n");
	return 1;
    }
    write("By which name wouldst your steed be named?\n");
    input_to("get_name");
    return 1;
}

/*
 * Function name: get_name
 * Description:   Get the wished-for name of the steed
 * Arguments:     name - name the player wants to use
 */
void
get_name(string name)
{
    int i;

    if (!name)
	return;
    name = lower_case(name);
    for (i=0 ; i<sizeof(used_names) ; i++)
	if (name == used_names[i]) {
	    write("That name has already been used.\n");
	    return;
	}
    if (SECURITY->exist_player(name)) {
	write("That is not an allowed name!\n");
	return;
    }
    write("How wouldst you describe your steed?\n");
    input_to("get_long", 0, name);
}

void
get_long(string long, string name)
{
    if (!long)
	return;

    write("Give an adjective describing the steed:\n");
    input_to("get_adj", 0, ({ name, long }));
}

void
get_adj(string adj, string *other)
{
    int age;
    mixed what;
    object ob;
    string long, name;

    if (!adj)
	return;
    name = other[0];
    long = other[1];
    if (sizeof(other) == 2) {
	write("Give another adjective describing the steed:\n");
	input_to("get_adj", 0, ({ name, long, adj }));
	return;
    }

    age = BASE_AGE;
    if (this_player()->query_guild_name_occ() == RIDER_OCC)
	age += OCCUP_BONUS;
    else if (this_player()->query_guild_name_lay() == RIDER_LAY)
	age += LAYMAN_BONUS;

    if (this_player()->query_prop(STEED_I_QUEST))
	age += QUEST_BONUS;

    age *= 86400;

    ob = clone_object(PEDIGREE);
    ob->set_owner_name(this_player()->query_real_name());
    ob->set_horse_name(name);
    ob->set_long_desc(long);
    ob->set_steed_adj(adj);
    ob->set_steed_adj(other[2]);
    ob->set_horse_max_age(age);
    ob->init_stats();

    if (ob->move(this_player())) {
	ob->move(this_player(), 1);
	ob->move(this_player());
    }

    what = horses[this_player()->query_real_name()];
    if (what) {
	what[0] = time();
	what[1] = name;
	what[2] = 0;
	what[3] = what[3] + 1;
    }
    else
	what = ({ time(), name, 0, 1 });
    used_names += ({ name });
    horses[this_player()->query_real_name()] = what;

    seteuid(getuid());
    save_object(REGISTRY);

    write(break_string("You are given a pedigree showing the name of your new "+
		       "steed. The steed can be found in the stables.\n", 76));
}

/*
 * Function name: horse_died
 * Description:   Called when a horse dies so we can update the mapping
 *                holding all horses
 * Arguments:     name - name of the horse' owner
 */
void
horse_died(string name)
{
    mixed what;

    what = horses[name];
    if (!what)
	return;
    what[2] = time();
    horses[name] = what;
}
