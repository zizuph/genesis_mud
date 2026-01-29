inherit "/std/object";
#include <macros.h>
#include <stdproperties.h>
#include <language.h>
#include <filter_funs.h>

void
create_object()
{
    set_name("bouquet");
	set_short("bouquet of flowers");
	set_long(break_string("A beautiful bouquet of pink roses, white " +
	"lily of the valley. Intermixed with the flowers are sprigs of " +
	"baby's breath and feathery greens. The flowers look as if they " +
	"have been specially cultivated for this day. There is a note " +
	"attached.\n",75));
    add_prop(OBJ_I_VOLUME, 40);
    add_prop(OBJ_I_WEIGHT, 37);
    add_prop(OBJ_I_VALUE, 0);
    add_item(({"note"}),("Good luck on your wedding day and with your married " +
    "life.\n" + 
	"Love, Tri.\n"));

}
void
init()
{
    ::init();
    add_action("do_throw", "throw");
}

int
do_throw(string arg)
{
    object ob, *obs;
    mixed exits, exit, target;
    int i;

    notify_fail("Throw what?\n");
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
    notify_fail("Throw what at whom?\n");
    if (!parse_command(arg, obs + all_inventory(this_player()),
		       "%o 'at' %l", ob, target))
	return 0;
    if (ob != this_object())
	return 0;
    notify_fail("Throw " + LANG_THESHORT(this_object()) + " at whom?\n");
    if (sizeof(target) != 2 || !objectp(target[1]))
	return 0;
    this_player()->catch_msg("You throw " + LANG_ASHORT(this_object()) +
			     " at " + QTNAME(target[1]) + ".\n");
    say(QCTNAME(this_player()) + " throws a bouquet of flowers in the air, and it is caught by " + QCTNAME(target[1]) +
	".\n", ({ target[1], this_player() }));
    target[1]->catch_msg("You catch the bride's bouquet in your hands.\n");
    tell_room(environment(target[1]), QCTNAME(target[1]) + " catches the " +
	      LANG_ASHORT(this_object()) + ".\n", target[1]);
    seteuid(getuid());
    if (ob->move(environment(target[1]), 0))
	ob->remove_object();
    remove_object();
    return 1;
}
