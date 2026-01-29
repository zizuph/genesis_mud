#include "../../defs.h"
#include <filter_funs.h>
#include <macros.h>

inherit "/std/room";

object *spiders = ({ });

#define DATA_DIR            "/d/Genesis/specials/guilds/test/data/"

int test_level = 0;
int tests_remaining = 0;
string data_file;
object test_subject;
int start_time = 0;

void 
create_room()
{
    set_short("Mirkwood Spider Test Room");
    set_long("Test room for the mirkwood spiders.\n");
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

public void
next_test()
{
    if (tests_remaining == 0) 
    {
        test_level++;
        tests_remaining = 10;
    }

    if (test_level > 6)
    {
        write_file(MIRKWOOD_SPIDER_DIR + "test/log/" + data_file, "Tests completed.\n\n");
        tell_room(this_object(), "Tests completed.\n");

        test_level = 0;
        tests_remaining = 0;
        return;
    }

    tests_remaining--;

    setuid();
    seteuid(getuid());

    test_subject = clone_object(MIRKWOOD_SPIDER_DIR + "test/test_npc");
    test_subject->load_data(data_file);
    test_subject->move(this_object());

    set_alarm(2.0, 0.0, spawn_spiders);
/*
    object *mortals = (what == "spiders") ? 
        filter(FILTER_IS_MORTAL(FILTER_LIVE(all_inventory())), &->query_humanoid())
        : ({ this_player() });

    foreach(object mortal : mortals)
    {
        spiders += (MIRKWOOD_SPIDER_DIR + "coordinator")->create_spiders_for_target(mortal, level);
    }

    enter_next_spider();
    */
}

void
cleanup()
{
    object *targets = filter(FILTER_LIVE(all_inventory()), not @ interactive);
    targets->remove_object();
}

private string
describe_object(object ob)
{
    int total_time = time() - start_time;

    int total_healed = ob->query_total_healed();
    if (total_healed)
    {
        return sprintf("%s (%d / %d + %d) [%ds]", ob->query_race_name(), ob->query_hp(), 
            ob->query_max_hp(), total_healed, total_time);
    }

    return sprintf("%s (%d / %d) [%ds]", ob->query_race_name(), ob->query_hp(), 
        ob->query_max_hp(), total_time);
}

void
fight_finished()
{
    object *report_obs = ({ test_subject }) + filter(all_inventory(), &->id(MIRKWOOD_SPIDER_ID));
    write_file(MIRKWOOD_SPIDER_DIR + "test/log/" + data_file, sprintf("Level %d: %s\n", 
        test_level, implode(map(report_obs, describe_object), " ")));

    cleanup();
    next_test();
}

public int
test_cmd(string args)
{
    int level = 1;
    string what = "";

    if (!args || !sscanf(args, "%s", what))
    {
        notify_fail("Test with what data file?\n");
        return 0;
    }

    if (test_level != 0) 
    {
        notify_fail("Tests already running.\n");
        return 0;
    }

    if (file_size(DATA_DIR + what + ".o") <= 0)
    {
        notify_fail("Could not find datafile for " + what + ".\n");
        return 0;
    }

    write_file(MIRKWOOD_SPIDER_DIR + "test/log/" + what, "Tests initiated.\n");
    write("Tests started.\n");

    data_file = what;
    set_alarm(0.1, 0.0, next_test);
    return 1;
}

public void 
init()
{
    ::init();
    add_action(test_cmd, "test");
}