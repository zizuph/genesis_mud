/* goblin caves
 * Fixed a bug with shout here. Rohim.
 */

#include "../local.h"
#include <config.h>
#include <ss_types.h>
#include <stdproperties.h>
#include <macros.h>

inherit SHIRE_ROOM;

void
create_shire_room()
{
    add_prop(ROOM_I_LIGHT, 1);
    add_prop(ROOM_I_INSIDE, 1);
    add_prop(ROOM_I_NO_TELEPORT,"That is not possible here.\n");

    set_short("treasure chamber");
    set_long("This is treasure chamber of goblin lord. It is very quiet "+
      "here and very odd thing is "+
      "that there is no treasure here. You would bet your life "+
      "that goblin lord has some treasure somewhere. Maybe it "+
      "is somewhere else.\n");

    add_item(({"wall","walls"}),"These walls seems to be natural. But "+
      "then again you have seen so many strange things in these "+
      "caves that you are not sure what you think you see or feel.\n");

    add_exit(CAVE_DIR+"d10", "west");
}


void
init()
{
    ::init();
    add_action("shout_name", "shout");
}

int
shout_name(string something)
{
    if (!something)
	return 0;
    if (something == call_other(CAVE_DIR + "d12", "query_rune"))
    {
	TP->catch_msg("You take deep breath and shout: "+something+
	  "\nStrangely all sound is absorbed by eastern "+
	  "wall.\nAfter the sound wall absorbs you too!\n");
	say(QCTNAME(TP)+" takes deep breath and shouts something. You can't "+
	  "tell what it was because the eastern wall absorbs the sound.\n"+
	  "Ooops!!! The wall absorbs "+QTNAME(TP)+" too!\n");
	tell_room(CAVE_DIR+"d12","The western wall starts to emit something. "+
	  "Suddenly "+QTNAME(TP)+" is standing here.\n");
	TP->move_living("M",CAVE_DIR+"d12", 1);
	return 1;
    }
    TP->catch_msg("You take deep breath and shout: "+something+"\n"+
      "Strangely all sound is absorbed by eastern wall.\n");
    say(QCTNAME(TP)+" takes a deep breath and shouts something. You can't "+
      "tell what it was because eastern wall absorbs all sound.\n");
    return 1;
}

void
enter_inv(object ob, object from)
{
    ::enter_inv(ob,from);
    if (!interactive(ob))
	return;

    if (file_name(from) == OWN_STATUE)
	ob->move(CAVE_DIR + "d10");

    ob->add_prop(MIRROR_CHECK, 1);
}

void
leave_inv(object ob, object to)
{
    ob->remove_prop(MIRROR_CHECK);
    ::leave_inv(ob, to);
}

