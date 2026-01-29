/*
 * A pan that can contain water (or anything else)
 *
 * modified from bucket.c by Dust
 *
 * Olorin, Apr 1993
 */
inherit "/std/container";
#include "/d/Gondor/defs.h"
#include <stdproperties.h>
#include <ss_types.h>
#include <macros.h>

int	filled;	/* true if filled with water */
int     spill_alarm;
object	water;	/* The actual water in the pan */

void test_spill();

void
create_container() {

    if (!IS_CLONE) return;

    filled = 0;

    set_name("pan");
    set_short("battered old pan");
    set_pshort("battered old pans");
    set_long("This battered old pan might hold some stuff.\n");
    set_adj(({"battered","old"}));
    add_prop(CONT_I_WEIGHT,1000);
    add_prop(CONT_I_MAX_WEIGHT, 5000);
    add_prop(CONT_I_VOLUME,400);
    add_prop(CONT_I_MAX_VOLUME, 5000);
    add_prop(CONT_I_TRANSP,1);
    add_prop(CONT_I_RIGID,1);
    add_prop(OBJ_I_VALUE,100);
}

void
test_spill()
{
    object player;

    player = environment(this_object());
    if (living(player) && filled)
    {
	if (random(player->query_stat(SS_DEX)) < 5)
	{
	    tell_object(player,
		"Oops, clumsy as you are, you spill the water...\n" +
		"It vanishes in the ground immediately.\n");
	    tell_room(environment(player),
		QCTNAME(player) + " spills water on the floor.\n" +
		"It vanishes in the ground immediately.\n",player);
	    water->remove_object();
       this_object()->remove_prop(OBJ_I_CONTAIN_WATER);
	    filled = 0;
	}
    }

    if (filled)
        spill_alarm = set_alarm(10.0, 0.0, test_spill);
}

void
init()
{
    ::init();
    add_action("do_fill","fill",0); /* filling the pan */
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
			"'pan' [with] 'water'") ||
	parse_command(str,environment(this_player()),
			"'water' [in] 'pan'"))
    {
	if (volume_left() < 1893 || weight() > 1000) {
	    notify_fail("But the pan isn't empty...\n");
	    return 0;
	}
	if (environment(this_player())->query_prop(OBJ_I_CONTAIN_WATER) ||
       environment(this_player())->query_prop(ROOM_I_TYPE) == ROOM_BEACH)
	{
	    filled = 1;
	    write("You fill the pan with water.\n");
	    water = clone_object(OBJ_DIR + "water");
	    water->move(this_object());
	    this_object()->add_prop(OBJ_I_CONTAIN_WATER,1);
            if (!get_alarm(spill_alarm))
                spill_alarm = set_alarm(10.0, 0.0, &test_spill());
 
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
	    notify_fail("But the pan doesn't contain any water.\n");
	    return 0;
	}
	if (!(fire = present(/* DUSTDIR + */ "fire",
		environment(this_player()))))
	{
	    notify_fail("But there is no fire in this room.\n");
	    return 0;
	}
	filled = 0;
        remove_alarm(spill_alarm);

	write("You pour water on the fire.\n");
	water->remove_object();
   this_object()->remove_prop(OBJ_I_CONTAIN_WATER);
	fire->extinguish();
	return 1;
    }
    notify_fail("What do you want to pour on what?\n");
    return 0;
}

query_recover()
{
  string rec;

  rec = MASTER +  ":";
  rec += filled; 
  return rec;
}

init_recover(string arg)
{
  int i;

  if (sscanf(arg, "%d", i) != 1)
    write("Something went wrong with recovering the pot.\n");
  else
  {
    filled = i;
    if (filled) {
        spill_alarm = set_alarm(10.0, 0.0, &test_spill());
        this_object()->add_prop(OBJ_I_CONTAIN_WATER,1);
    }
  }
  return;
}
