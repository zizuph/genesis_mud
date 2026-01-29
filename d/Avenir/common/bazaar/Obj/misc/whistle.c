// whistle           /d/Avenir/common/Bazaar/Obj/misc/whistle.c       
// creator(s):      Lilith  12/08/01
// purpose:         WHISTLE FOR SUMMONING MESSENGERS
/* Revisions:
 *	Vyasa, Oct 2016:  Fixed dest upon reaching max SUMMONS
 *	Lucius, May 2017: Fixed new bug that allowed infinite messengers.
 *	Lucius, Jul 2017: Recover current count. Also adjust value to more
 *			  of a real-world reflection.
 *  Lilith, May 2022: added item_recovery
 */
#pragma strict_types

inherit "/std/object";
inherit "/lib/keep";

#include <macros.h>
#include <cmdparse.h>
#include <stdproperties.h>

#include "/d/Avenir/include/defs.h"
#include "/d/Avenir/include/paths.h"

#define DEPTH	3   /* How many rooms away the whistle is heard.*/
#define SUMMONS	6
/* 1 Gold * SUMMONS + 1 gold for convenience */
#define VALUE	((144 * SUMMONS) + 144)

public int alarm = 0, count = 0;


public void
create_object()
{
    setuid();  
    seteuid(getuid());

    set_name("whistle");
    set_short("white gold whistle");
    add_adj(({"white", "gold"}));
    set_long("This is a slender whistle, barely the length of your "+
      "smallest finger.  It is made of white gold. Inscribed along "+
      "the length of it are the words:\n"+
      "   Blow to summon a messenger.\n");

    add_prop(OBJ_I_WEIGHT, 200);
    add_prop(OBJ_I_VOLUME, 200);
    add_prop(OBJ_I_VALUE, VALUE);

    if (IS_CLONE)
      set_item_expiration(); 
}

public int
summon_child(object player)
{
    object child = clone_object(BAZAAR +"intr/child");

    write("A small child sidles up to you and pulls on your "+
      "sleeve.\n");

    if (child->move(player))
    {
	write("You cannot carry the child!\n");
	child->remove_object();
    }

    return 1;
}

public void
dest_it(void)
{
    write("The whistle crumbles into a gold dust and blows away.\n");
    remove_object();
}

public int
do_blow(string str)
{
    object troom;

    if (!str)
	return 0;

    if (!objectp(troom = environment(this_player())))
	return 0;

    if (environment() != TP)
	return notify_fail("You should get it, first.\n");    

    if (!parse_command(str, ({ }), "[on] [the] 'whistle'"))
	return notify_fail("Try <blow whistle>.\n");

    write("You raise the "+ short() +" to your mouth "+
      "and blow forcefully into it.\n");
    say(QCTNAME(this_player()) +" raises a "+ short() +" to "+ 
      POSSESS(TP) +" mouth and blows forcefully into it.\n");       

    if (alarm)
    {
	write("But the whistle makes no sound.\n");
	return 1;
    }

    foreach(object room: FIND_NEIGHBOURS(troom, DEPTH))
    {
	tell_room(room,
	  "You hear a high, shrill whistling sound.\n");
    }

    if (++count < SUMMONS)
    {
	set_alarm(10.0, 0.0, &summon_child(this_player()));
    }
    if (count < SUMMONS - 1)
    {
        // Dest it, unless it has remaining summons.
        return 1;
    }
    alarm = set_alarm(15.0, 0.0, dest_it);
    return 1;
}

public void
init(void)
{
    ::init();
    add_action(do_blow, "blow");
}

public void
init_recover(string arg)
{
    sscanf(arg, "%d", count) + init_item_expiration_recover(arg);
}

public string
query_recover(void)
{
    return MASTER + ":"+ count + query_item_expiration_recover();
}
