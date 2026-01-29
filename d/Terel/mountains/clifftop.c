/*
 * Modified by Tomas for goblin cave addition -- Dec. 1999
 */

#include "/d/Terel/include/Terel.h"
#include <ss_types.h>
#include <cmdparse.h>
#include <composite.h>
inherit STDROOM;


public void
create_room()
{
    ::create_room();
    set_short("Clifftop");
    set_long("Atop this cliff, one can see out across much of the icy mountain " +
       "chain and even down to the ravine. To the east, you can see the entrance " +
       "to a cave.\n");

    add_item(("cave"), "The entrance to the cave looks large enough to enter.\n");
    add_item(("ravine"),"The ravine is just below you.\n");
    add_item(({"mountains","mountain","chain","mountain chain"}),
       "From your vantage point you can make out just how large vast " +
       "the mountains are.\n");
    add_item(("ground"),"Fresh snowfall covers most of the ground, but " +
       "you can make out some small tracks leading towards the cave entrance.\n");

    add_exit(MOUNTAIN_DIR + "cliff", "down");
    add_exit(MOUNTAIN_DIR + "goblincave/entrance","east", 0);

  reset_room();
}


public void
do_decay(object ob)
{

    ob->catch_msg("You burn in the sunlight.\n");
    tell_room(TO,QCTNAME(ob) + " howls in fury " +
        "as it burns in the direct sunlight.\n");
    ob->remove_object();
    return;
}


public void
enter_inv(object ob,object old)
{
    ::enter_inv(ob,old);

    if(!interactive(ob))
    {
        if (ob->query_prop("_terel_ghost"))
        {

            set_alarm(0.0,0.0,&do_decay(ob));
            return;
        }
    }
}

