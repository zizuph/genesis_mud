/*
 * A bucket that can contain 1 gal of water (or anything else)
 */
inherit "/std/container";
#include "/d/Terel/common/terel_defs.h"
#include <stdproperties.h>
#include <ss_types.h>
#include <macros.h>

#define TO   this_object()
#define ETO  environment(TO)
#define TP   this_player()
#define ETP  environment(TP)

int     aid=0;    /* Alarm id */
int	filled;	/* true if filled with water */
object	water;	/* The actual water in the bucket */


public void
create_container()
{
    filled = 0;
    set_name("bucket");
    set_short("battered old bucket");
    set_pshort("battered old buckets");
    set_long("This battered old bucket might hold some stuff.\n");
    set_adj(({"battered", "old"}));
    add_prop(CONT_I_WEIGHT, 1000);
    add_prop(CONT_I_MAX_WEIGHT, 4785);
    add_prop(CONT_I_VOLUME, 0);
    add_prop(CONT_I_MAX_VOLUME, 3785);
    add_prop(CONT_I_TRANSP,1);
    add_prop(CONT_I_RIGID,1);
}

public void
test_spill()
{
    if (!filled || !ETO) return;
    
    if (living(ETO))
    {
	/* dex = 30: you can carry the water for about 5 minutes
	 * dex =100: you can carry the water for about 15 minutes
	 * dex = 10: you can carry the water for about 1.5 minutes
	 */
	if (random(ETO->query_stat(SS_DEX)) < 3)
	{
	    tell_object(ETO,
		"Oops, clumsy as you are, you spill the water...\n" +
		"It vanishes in the ground immediately.\n");
	    tell_room(environment(ETO),
		QCTNAME(ETO) + " spills water on the floor.\n" +
		"It vanishes in the ground immediately.\n", ETO);
	    water->remove_object();
	    filled = 0;
	}
    }
}

public void
enter_env(object to, object from)
{
    ::enter_env(to, from);
    
    if (from && living(from)) return;
    
    if (to && living(to)) {
        if (!aid) {
            aid = set_alarm(30.0, 30.0, test_spill);
        }
    }
}

public void
leave_env(object from, object to)
{
    ::leave_inv(from, to);
    
    if (to && living(to)) return;
    
    if (from && living(from)) {
        if (aid) {
            remove_alarm(aid);
            aid = 0;
        }
    }
}

public int
do_fill(string str)
{

    seteuid(getuid());
    if (!str)
    {
	notify_fail("Fill what?\n");
	return 0;
    }
    if (parse_command(str, ETP,
			"'bucket' [with] 'water'") ||
	parse_command(str, ETP,
			"'water' [in] 'bucket'"))
    {
	if (volume_left() < 3785 || weight() > 1000) {
	    notify_fail("But the bucket isn't empty...\n");
	    return 0;
	}
	if (ETP->query_prop(ROOM_HAS_WATER))
	{
	    filled = 1;
	    write("You fill the bucket with water.\n");
	    water = clone_object(DUSTDIR + "water");
	    water->move(TO);
	    return 1;
	}
	notify_fail("But there is no water available in this room.\n");
	return 0;
    }
    notify_fail("What do you want to fill with what?\n");
    return 0;
}

public int
do_pour(string str)
{
    object fire;

    seteuid(getuid());
    if (str == 0)
    {
	notify_fail("Pour what?\n");
	return 0;
    }
    if (parse_command(str, ETP,
			"'water' [on] 'fire'") ||
	parse_command(str, ETP,
			"'water' [at] 'fire'") ||
	parse_command(str, ETP,
			"'fire' [with] 'water'"))
    {
	if (!filled) {
	    notify_fail("But the bucket doesn't contain any water.\n");
	    return 0;
	}
	if (!(fire = present("fire", ETP)))
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

public void
init()
{
    ::init();
    add_action(do_fill, "fill"); /* filling the bucket */
    add_action(do_pour, "pour"); /* pour water out */
}
