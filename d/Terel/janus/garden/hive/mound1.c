/* mound1.c */
/* janus 920901 */
/*
 * Lucius - Jan 2021
 *    Cleaned up and modernized.
 */
inherit "/std/room";
#include <stdproperties.h>

#include "/d/Terel/common/terel_defs.h"

#define TP  this_player()
#define TO  this_object()

#define LIVE_S_FROM_FILE        "_live_s_from_file"

public void
create_room()
{
    set_short("hive entrance");
    set_long("You stand at the entrance to the enormous hive. "+
      "There are huge marks in the ground after the bugs, but there are "+
      "no bugs in your vicinity as you can see. The smell from the hive "+
      "has an acrid tang to it. You can either go north into the hive or "+
      "wait here for the magical shrinking effects to wear off.\n");

    add_item("hive", "The only possible entrance" +
        " to the hive seems to be to the north.\n");

    add_exit(JANUSDIR + "garden/hive/mound2","north",0);
    add_object(JANUSDIR + "other/krympp");
}

public void
wait_and_grow(object who)
{
    if (!objectp(who))
        return;

    string back = who->query_prop(LIVE_S_FROM_FILE);

    if (environment(who) == TO && strlen(back))
    {
	who->catch_tell("You grow back to normal size.\n");
	who->remove_prop(LIVE_S_FROM_FILE);
	who->move_living("this miniature world", back, 1);
    }
}

public void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);

    if (!living(ob) || !strlen(ob->query_prop(LIVE_S_FROM_FILE)))
        return;

    set_alarm(25.0, -1.0, &wait_and_grow(ob));
}
