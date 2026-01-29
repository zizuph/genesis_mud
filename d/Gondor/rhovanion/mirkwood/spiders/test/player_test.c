#include "../../defs.h"
#include <filter_funs.h>
#include <macros.h>

inherit "/std/room";

object *spiders = ({ });

int test_level = 0;
object test_subject;
int start_time = 0;

void 
create_room()
{
    set_short("Mirkwood Spider Test Room");
    set_long("Test room for the mirkwood spiders.\n");

    add_exit("test_room", "south");
}

void 
enter_next_spider()
{
    if (!sizeof(spiders)) return;

    object spider = spiders[random(sizeof(spiders))];
    spiders -= ({ spider });

    tell_room(this_object(), "Leaping from the trees " 
        + QTNAME(spider) + " attacks " 
        + QTNAME(spider->query_victim())+ ".\n", 
        ({ spider->query_victim() }), spider);

    spider->set_restrain_path("/d/Gondor/rhovanion/mirkwood/spiders/test");
    spider->set_home(this_object());
    spider->move(this_object());

    object victim = spider->query_victim();
    victim->catch_tell(spider->query_The_name(victim) + " leaps from "
        + "the trees and attacks you!\n");

    set_alarm(itof(random(5)), 0.0, enter_next_spider);
}

public void
spawn_spiders()
{
    start_time = time();
    spiders += (MIRKWOOD_SPIDER_DIR + "coordinator")->create_spiders_for_target(test_subject, test_level);
    enter_next_spider();
}

public int
test_cmd(string args)
{
    if (!args || !sscanf(args, "%d", test_level))
    {
        notify_fail("Test with what level?\n");
        return 0;
    }

    test_subject = this_player();
    spawn_spiders();
    return 1;
}

public void 
init()
{
    ::init();
    add_action(test_cmd, "test");
}