inherit "/std/object";
#include <macros.h>
#include <stdproperties.h>
#include <language.h>
#include <filter_funs.h>
#include "/d/Avenir/common/common.h"

void
create_object()
{
	set_name("whip");
	set_short("whip");
	set_pshort("whips");
	set_long("A large black whip.  What do you think it is for? (To use crack whip at <name>\n");
    add_prop(OBJ_I_VOLUME, 40);
    add_prop(OBJ_I_WEIGHT, 37);
    add_prop(OBJ_I_VALUE, 0);
}

void
init()
{
    ::init();
	add_action("do_crack", "crack");
}

int
	do_crack(string arg)
{
    object ob, *obs;
    mixed exits, exit, target;
    int i;

	NF("use what?\n");
    if (!arg)
	return 0;
    obs = FILTER_LIVE(all_inventory(environment(this_player())));
    exits = environment(this_player())->query_exit();
    if (pointerp(exits))
	for (i=0 ; i<sizeof(exits) ; i+=3) {
	    exit = environment(this_player())->check_call(exits[i]);
	    if (stringp(exit))
		exit = find_object(exit);
	    if (objectp(exit))
		obs += FILTER_LIVE(all_inventory(exit));
	}
	NF("Use waht on whom?\n");
    if (!parse_command(arg, obs + all_inventory(this_player()),
		       "%o 'at' %l", ob, target))
	return 0;
    if (ob != this_object())
	return 0;
	NF("Use the whip on whom?\n");
    if (sizeof(target) != 2 || !objectp(target[1]))
	return 0;
TP->catch_msg("You aim the whip at " + QCTNAME(target[1]) + "'s buttocks.\n");
	say(QCTNAME(TP) + " aims the tip of the whip at " + 
QCTNAME(target[1]) + "'s buttocks.\n", ({ target [1], this_player() }));
tell_room(environment(target[1]), QCTNAME(target[1]) + " is hit in the buttocks by a whip.\n", target[1]);
	target[1]->catch_msg("You feel a stinging sensation in your buttocks.  OWWW! You realize you have been struck by a whip!\n");
    return 1;
}
string query_auto_load()
{
	return MASTER;
}
