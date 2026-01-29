/* This is a guild start room.  Note that default start locations
 * need to be registered with /secure/master.c.  See an archwizard
 * to have your start location registered.
*
*The start location was registered on the 17/6/98
*Arman
 */

#pragma strict_types
#include "/d/Ansalon/common/defs.h"
#include "../local.h"
#include <macros.h>
#include <stdproperties.h>

inherit KEN_OUT;
inherit "/lib/guild_support";


void
reset_kendermore_room()
{
    return;
}

void
create_kendermore_room()
{
    set_short("Secluded branch in a giant oak tree");
    set_long("Here you have come across a secluded area of " +
      "the oak tree where the oak tree branches off into several smaller " +
      "limbs. These limbs have been hollowed out slightly and filled " +
      "with leaves, a comfortable resting place for kender who " +
      "wish to sleep. Kender may <sleep here>, and will wake here " +
      "next time they wish to travel.\n");

    add_item("limbs","Several limbs here have been hollowed " +
      "out and filled with leaves, making them comfortable-" +
      "looking beds for the weary.\n");
    add_item("leaves","These leaves look like they would be " +
      "cozy to snuggle up in.\n");

    add_exit(KROOM + "r4","northeast",0);

    reset_kendermore_room();
}

int
start(string str)
{
    if (str != "here") 
    {
	notify_fail("Sleep here?\n");
	return 0;
    }

    if(TP->query_race_name() != "kender")
    {
	notify_fail("You don't feel safe sleeping up in these branches. " +
	  "Kender must truly be fearless, or absolute doorknobs, " +
	  "to do so!\n");
	return 0;
    }

    if (this_player()->set_default_start_location(GUILD_STARTLOC))
    {
	write("You will now wake up here when you begin " +
	  "your travels through the realms!\n");
    }
    else
    {
	write("Sorry, some problem prevents you from starting here.\n");
    }

    return 1;
}

void
check_kender(object ob)
{
    if(interactive(ob) && !ob->query_wiz_level() && ob->query_race_name() != "kender")
    {
	write("You don't feel comfortable starting your " +
	  "travels from up a kender tree. You think you'll start " +
	  "from a nice safe church from now on thats on the ground.\n");
	ob->set_default_start_location(ob->query_def_start());
	ob->move_living("M",ob->query_def_start(), 1,0);
    }
}

void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);
    set_alarm(2.0, 0.0, &check_kender(ob));
}

void
init()
{
    ::init();

    add_action(start, "sleep");
    init_guild_support();
}
