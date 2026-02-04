/*

 Crate in caravan wagon

 by Udana, 03/06

 Restricted the spawn rate of the unusual stick.
 Arman - October 2018

*/


#pragma strict_types

inherit "/std/container.c";
inherit "/lib/unique";

#include "/d/Terel/include/Terel.h"
#include "../include/defs.h"
#include <filter_funs.h>
#include <macros.h>
#include <stdproperties.h>
#include <cmdparse.h>
#include <ss_types.h>
#include <tasks.h>

#define SOUTH_GOODS ({\
  "/d/Terel/calathin/obj/torch", \
  "/d/Gondor/common/obj/oilflask", \
  "/d/Terel/common/town/mansion/obj/chisel", \
  "/d/Terel/common/town/mansion/obj/mining_boots"})

#define NORTH_GOODS ({\
  "/d/Terel/common/town/mansion/obj/silver_nugget", \
  "/d/Terel/common/town/mansion/obj/gold_nugget", \
  OBJ + "deerskin", \
  OBJ + "foxskin", \
  OBJ + "hareskin"})

/* It's 0 when the it holds north_goods and 1 when south_goods */
int contents = 0;
int crate_status = 0;

/* for add action purpose */
int break_crate(string a);

/* it merely sets the contents variable, if it's called with anything but 1 it will set it to 0 */
public void set_contents(int direction);

/* fills the crate with north or south goods */
void fill_crate();

public void create_container()
{
    set_name("crate");
    add_name("box");
    set_adj("large");
    add_adj("heavy");
    set_short("@@my_short");
    set_long("@@my_long");

    add_prop(CONT_I_WEIGHT, 100000);
    add_prop(CONT_I_VOLUME, 50000);
    add_prop(CONT_I_MAX_WEIGHT, 200000);
    add_prop(CONT_I_MAX_VOLUME, 100000);
    add_prop(CONT_I_CLOSED, 1);
}

string my_short()
{
    return (crate_status ? "broken" : "large") + " crate";
}

string my_long()
{
    return "A large crate, used for storing all sorts of goods. "
    + (crate_status ? "It has been broken and looted.\n" : "Maybe it contains something valuable?\n");
}

public int is_caravan_crate()
{
    return 1;
}

public void set_contents(int direction)
{
    contents = (direction == 1 ? direction : 0);
}

void fill_crate()
{
    string *goods = (contents == 1 ? SOUTH_GOODS : NORTH_GOODS);
    FIX_EUID;
    for(int i = 0; i < sizeof(goods); ++i)
    {
	int j = random(3) + 1;
	while(j--)
	    clone_object(goods[i])->move(TO);
    }

    clone_unique(OBJ + "stick", 3, "/d/Terel/calathin/obj/torch")->move(TO);
}

public void enter_env(object dest, object old)
{
    ::enter_env(dest, old);
    if(interactive(dest))
	E(dest)->picked_chest(dest);
}

public void init()
{
    ::init();
    add_action(break_crate, "break");
}

public int
break_crate(string a)
{
    object *crates, *tmp;

    notify_fail("Break what?\n");
    if (!strlen(a))
	return 0;

    tmp = filter(all_inventory(environment(this_player())), &->is_caravan_crate());
    crates = PARSE_COMMAND(a, tmp, "[a] / [the] %i");

    if (!sizeof(crates))
	return 0;

    if (sizeof(crates) > 1)
        return notify_fail("Break which crate?\n");

    if (crates[0] != TO)
	return 0;

    if (crate_status)
    {
	write("The crate is already broken!\n");
	return 1;
    }

    if (E(TP)->is_manned())
    {
	write("Guards are looking at you, it wouldn't be the best idea.\n");
	return 1;
    }

    tmp = TP->query_weapon(-1);
    int wpen = sizeof(tmp) ? tmp[0]->query_pen() : 10;
    string wdesc = sizeof(tmp) ? tmp[0]->short() : "fist";

    if (TP->resolve_task((100 - wpen) * 15, ({TS_STR})) > 0)
    {
	write("You hit the crate with your " + wdesc +
            " using all your might, and break the lid into shreds.\n");
	say(QCTNAME(TP) + " hits the crate with his " + wdesc +
            ", breaking the lid into shreds.\n");

	crate_status = 1;
	add_adj("broken");
	add_prop(CONT_I_CLOSED, 0);
	fill_crate();
	return 1;
    }

    write("You hit the crate with your " + wdesc +
        " using all your might, yet you didn't manage to scratch it.\n");
    say(QCTNAME(TP) + " hits the crate with his " + wdesc +
        ", making a hollow sound.\n");

    return 1;
}
