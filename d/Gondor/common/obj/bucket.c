/*
 * A bucket that can contain 1 gal of water (or anything else)
 */
inherit "/std/container";
#include <stdproperties.h>
#include <ss_types.h>
#include <macros.h>
#include "/d/Gondor/defs.h"

int	filled;	/* true if filled with water */
object	water;	/* The actual water in the bucket */

void test_spill();

void
create_container() {

    filled = 0;

    set_name("bucket");
    set_short("battered old bucket");
    set_pshort("battered old buckets");
    set_long("This battered old bucket might hold some stuff.\n");
    set_adj(({"battered","old"}));
    add_prop(CONT_I_WEIGHT,1000);
    add_prop(CONT_I_MAX_WEIGHT,4785);
    add_prop(CONT_I_VOLUME,0);
    add_prop(CONT_I_MAX_VOLUME,3785);
    add_prop(CONT_I_TRANSP,1);
    add_prop(CONT_I_RIGID,1);
    set_alarm(30.0, 0.0, test_spill);
}

void
test_spill()
{
    object player;

    player = environment(this_object());
    if (living(player) && filled)
    {
	/* dex = 30: you can carry the water for about 5 minutes
	 * dex =100: you can carry the water for about 15 minutes
	 * dex = 10: you can carry the water for about 1.5 minutes
	 */
	if (random(player->query_stat(SS_DEX)) < 3)
	{
	    tell_object(player,
		"Oops, clumsy as you are, you spill the water...\n" +
		"It vanishes in the ground immediately.\n");
	    tell_room(environment(player),
		QCTNAME(player) + " spills water on the floor.\n" +
		"It vanishes in the ground immediately.\n",player);
	    water->remove_object();
	    filled = 0;
	}
    }
    set_alarm(20.0, 0.0, test_spill);
}

void
init()
{
    ::init();
    add_action("do_fill","fill",0); /* filling the bucket */
    add_action("do_pour","pour",0); /* pour water out */
}

int
do_fill(string str)
{

    seteuid(getuid());
    if (str == 0)
    {
	notify_fail("Fill what?\n");
	return 0;
    }
    if (parse_command(str,environment(this_player()),
			"'bucket' [with] 'water'") ||
	parse_command(str,environment(this_player()),
			"'water' [in] 'bucket'"))
    {
	if (volume_left() < 3785 || weight() > 1000) {
	    notify_fail("But the bucket isn't empty...\n");
	    return 0;
	}
	if (environment(this_player())->query_prop(OBJ_I_CONTAIN_WATER))
	{
	    filled = 1;
	    write("You fill the bucket with water.\n");
            water = clone_object(OBJ_DIR + "water");
	    water->move(this_object());
	    return 1;
	}
	notify_fail("But there is no water available in this room.\n");
	return 0;
    }
    notify_fail("What do you want to fill with what?\n");
    return 0;
}

int
do_pour(string str)
{
    object fire;

    seteuid(getuid());
    if (str == 0)
    {
	notify_fail("Pour what?\n");
	return 0;
    }
    if (parse_command(str,environment(this_player()),
			"'water' [on] 'fire'") ||
	parse_command(str,environment(this_player()),
			"'water' [at] 'fire'") ||
	parse_command(str,environment(this_player()),
			"'fire' [with] 'water'"))
    {
	if (!filled) {
	    notify_fail("But the bucket doesn't contain any water.\n");
	    return 0;
	}
	if (!(fire = present(/* DUSTDIR + */ "fire",
		environment(this_player()))))
	{
	    notify_fail("But there is no fire in this room.\n");
	    return 0;
	}
	filled = 0;
	write("You pour water on the fire.\n");
	water->remove_object();
	fire->extinguish();
	return 1;
    }
    notify_fail("What do you want to pour on what?\n");
    return 0;
}
