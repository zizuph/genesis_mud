/*
 * This is a horse' pedigree.  It is autoloading and undroppable.
 * It is used to hold neccecary information about the horse, like
 * it's name, age, max. age and owner.
 */

inherit "/std/object";

/*
 * We use some stuff from here
 */
#include <macros.h>
#include <stdproperties.h>
#include <ss_types.h>
#include "steed.h"

/*
 * The loaded horse object in the game
 */
static object horse;

/*
 * Information we need about the horse
 */
string horse_name;
string owner_name;
string long_desc, *adj_list;
int age, max_age;
int str, dex, con, intx, wis, dis, defence, unarmed, awareness;
int hp, stuffed, fatigue;

/*
 * Prototypes
 */
int query_horse_age();
void update_values();

/*
 * Function name: create_object
 * Description:   Set up the basic pedigree object.
 */
void
create_object()
{
    set_name( ({ "pedigree", "_steed_controller_" }) );
    set_adj("horse'");
    /*
     * VBFC so we can give some information about the specific horse
     */
    set_long("@@pedigree_desc@@");

    /*
     * Make sure it isn't sold or dropped by accident
     */
    add_prop(OBJ_M_NO_DROP, "You wouldn't really want to do that.\n");

    long_desc = "This is a rather big battle horse. It looks like it might "+
		"hold you.";

    adj_list = ({ "magnificent", "proud" });
}

/*
 * Function name: init
 * Description:   Set up special commands for the pedigree
 */
void
init()
{
    ::init();
    if (environment() == this_player()) {
	add_action("do_call", "call");
	add_action("do_call", "summon");
	add_action("do_read", "read");
    }
}

/*
 * Function name: do_call
 * Description:   Call the steed to you
 * Arguments:     arg - the rest of the command string
 * Returns:       0 - failure
 *                1 - success
 */
int
do_call(string arg)
{
    notify_fail("Call what?\n");
    if (!arg || arg != horse_name)
	return 0;
    if (environment(this_player())->query_prop(ROOM_I_INSIDE) &&
	!environment(this_player())->query_prop(ROOM_I_IS_STABLE))
	write("You emit a shrill whistle, but stop immediately as the sound "+
	      "echos back from the walls, hurting your ears.\n");
    else if (horse) {
	write("You emit a shrill whistle, and sense your horse responding.\n");
	call_out("trans_horse", 15, this_player());
    }
    else if (environment(this_player())->query_call_horse()) {
	write("You emit a shrill whistle, and sense your horse responding.\n");
	call_out("load_horse", 15, this_player());
    }
    else
	write("You emit a shrill whistle, but can't sense any response.\n");
    say(QCTNAME(this_player()) + " emits a shrill whistle.\n");
    return 1;
}

/*
 * Function name: do_read
 * Description:   Read the pedigree
 * Arguments:     arg - the rest of the command string
 * Returns:       0 - failure
 *                1 - success
 */
int
do_read(string arg)
{
    notify_fail("Read what?\n");
    if (!arg || !id(arg))
	return 0;
    write("You read the pedigree, not finding much of interest.\n");
    return 1;
}

/*
 * Function name: pedigree_desc
 * Description:   Give out the long description of the horse' pedigree
 * Returns:       String holding the long description of the pedigree
 */
string
pedigree_desc()
{
    return break_string("This is the pedigree of the grand horse "+
			capitalize(horse_name) + ", now in the possession of "+
			capitalize(owner_name) + ".\n", 76);
}

/*
 * Function name: query_auto_load
 * Description:   Make the pedigree autoloading
 * Returns:       String holding the pathname of the pedigree as well
 *                as the value of some variables we will need
 */
string
query_auto_load()
{
    /*
     * Make sure the values we store are up to date
     */
    update_values();
    /*
     * Calculate and return the autoload string
     */
    return MASTER + ":" + horse_name + "##" + owner_name + "##" +
	   long_desc + "##" + adj_list[0] + "," + adj_list[1] + "##" +
	   age + "," + max_age + "," + str + "," + dex + "," +
	   con + "," + intx + "," + wis + "," + dis + "," +
	   hp + "," + stuffed + "," + fatigue + "," + defence + "," +
	   unarmed + "," + awareness + "##";
}

/*
 * Function name: init_arg
 * Descriotion:   Initialize variables from autoload string when a
 *                player logs in
 * Arguments:     str - holds the parts of the autoload string following
 *                      the ":".
 */
void
init_arg(string arg)
{
    if (sscanf(arg, "%s##%s##%s##%s,%s##%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d##",
	       horse_name, owner_name, long_desc, adj_list[0], adj_list[1],
	       age, max_age, 
	       str, dex, con, intx, wis, dis,
	       hp, stuffed, fatigue,
	       defence, unarmed, awareness) < 19)
	call_out("remove_object", 1);
    else
	call_out("introduce_steed", 1);
}

/*
 * Function name: introduce_steed
 * Description:   Make sure the player knows the name of the steed
 */
void
introduce_steed()
{
    environment()->add_introduced(horse_name);
}

/*
 * Function name: query_horse_name
 * Description:   Get the name of the steed
 * Returns:       String holding the name of the horse
 */
string
query_horse_name()
{
    return horse_name;
}

/*
 * Function name: query_owner_name
 * Description:   Get the name of the owner
 * Returns:       String holding the name of the owner
 */
string
query_owner_name()
{
    return owner_name;
}

/*
 * Function name: query_horse_age
 * Description:   Get the current age of the horse
 * Returns:       The age of the horse in seconds
 */
int
query_horse_age()
{
    if (horse)
	age = horse->query_age();
#ifdef AGE_IN_STABLE
    else
	age += time() - environment()->query_login_time();
#endif
    return age;
}

/*
 * Function name: set_horse_name
 * Description:   Define the name of the steed
 * Arguments:     str - the new name of the horse
 */
void
set_horse_name(string str)
{
    horse_name = str;
}

/*
 * Function name: set_owner_name
 * Description:   Define the name of the steed's owner
 * Arguments:     str - the name of the owner
 */
void
set_owner_name(string str)
{
    owner_name = str;
}

/*
 * Function name: set_long_desc
 * Description:   Set up the long desc of the steed
 * Arguments:     str - the new long desc for the steed
 */
void
set_long_desc(string str)
{
    long_desc = str;
}

/*
 * Function name: set_steed_adj
 * Description:   Set up the adjectives of the steed
 * Arguments:     str - the new adjective for the steed
 */
void
set_steed_adj(string str)
{
    adj_list = ({ str }) + adj_list;
    adj_list = adj_list[0..1];
}

/*
 * Function name: set_horse_max_age
 * Description:   Limit the maximum age of a horse
 * Arguments:     i - the maximum age of the steed in seconds
 */
void
set_horse_max_age(int i)
{
    max_age = i;
}

/*
 * Function name: init_stats
 * Description:   Set up initial, random stats for the steed
 */
void
init_stats()
{
    str = 50 + random(20);
    dex = 50 + random(20);
    con = 50 + random(20);
    intx = 50 + random(20);
    wis = 50 + random(20);
    dis = 50 + random(20);
    hp = (con + 20) * (con + 20) / 5 - 80;
    stuffed = (500 + con * 25) / 3;
    fatigue = (con + 50);
    defence = 20 + random(10);
    unarmed = 20 + random(10);
    awareness = 20 + random(10);
}

/*
 * Function name: load_horse
 * Description:   Load the horse into the game
 */
void
load_horse(object player)
{
    int i;

    if (horse || !player || (environment(player)->query_prop(ROOM_I_INSIDE) &&
			     !environment(player)->query_prop(ROOM_I_IS_STABLE)))
	return;
    seteuid(getuid());
    horse = clone_object(HORSE);
    horse->set_name(horse_name);
    horse->set_owner(owner_name);
    horse->set_long(long_desc);
    horse->remove_adj(horse->query_adjs());
    horse->set_adj(adj_list);
    horse->set_age(age);
    horse->set_max_age(max_age);
    horse->set_stats( ({ str, dex, con, intx, wis, dis }) );
    horse->set_hp(hp);
    for (i = 0 ; i < 5 ; i++)
	 horse->eat_food(stuffed / 5, 0);
    horse->eat_food(stuffed % 5, 0);
    horse->set_fatigue(fatigue);
    horse->set_skill(SS_DEFENCE, defence);
    horse->set_skill(SS_UNARM_COMBAT, unarmed);
    horse->set_skill(SS_AWARENESS, awareness);
    horse->move_living("into a room", environment(player));
}

/*
 * Function name: trans_horse
 * Description:   Transport the horse to the player
 */
void
trans_horse(object player)
{
    if (!horse || !player || (environment(player)->query_prop(ROOM_I_INSIDE) &&
			      !environment(player)->query_prop(ROOM_I_IS_STABLE)))
	return;
    horse->move_living("in search of " + horse->query_possessive() +
		       " owner", environment(player));
}

/*
 * Function name: remove_object
 * Description:   Override so we can remove the steed when the player
 *                logs out etc.
 */
void
remove_object()
{
    if (horse)
	horse->start_remove();
    ::remove_object();
}

void 
update_values() 
{ 
     if (!horse)
         return;
     age = query_horse_age();
     str = horse->query_base_stat(SS_STR);
     dex = horse->query_base_stat(SS_DEX);
     con = horse->query_base_stat(SS_CON);
     intx = horse->query_base_stat(SS_INT);
     wis = horse->query_base_stat(SS_WIS);
     dis = horse->query_base_stat(SS_DIS);
     hp = horse->query_hp();
     stuffed = horse->query_stuffed();
     fatigue = horse->query_fatigue();
     defence = horse->query_base_skill(SS_DEFENCE);
     unarmed = horse->query_base_skill(SS_UNARM_COMBAT);
     awareness = horse->query_base_skill(SS_AWARENESS);
} 
