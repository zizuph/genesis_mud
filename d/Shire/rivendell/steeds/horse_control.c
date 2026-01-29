/*
* Used to test summon/dismiss horse before feature
* was incorporated into the Noldor's soul.
 */

inherit "/std/object";
#include "/d/Shire/sys/defs.h"
#include <stdproperties.h>

/* Function Prototypes */
public int summon_horse();
public int dismiss_horse();


void
create_object()
{
    ::create_object();
    setuid();
    seteuid(getuid());
    set_name(({"horse control", "control"}));
    set_pname("horse controls");
    set_adj("shiney");
    set_short("horse control");
    set_long("A short stick.\n");
}


public int
summon_horse()
{
    object horse;
    string *saved_data;
    mapping steed_owners = ([ ]);
    string horse_name;

    steed_owners = restore_map("/d/Shire/rivendell/steeds/steed_owners");
    if (!steed_owners[TP->query_real_name()])
    {
        say("You don't have a horse. Go visit the stable master.");
        return 1;
    }
    saved_data = steed_owners[TP->query_real_name()];
    horse_name = saved_data[2];

    if (find_living(lower_case(horse_name)))
    {
        horse = find_living(lower_case(horse_name));
        horse->move_living("null", ENV(TP));
        return 1;
    }

    horse = clone_object("/d/Shire/rivendell/steeds/horse");
    horse->add_desc(saved_data);
    horse->move_living("null", ENV(TP));
    return 1;
}


public int
dismiss_horse()
{
    object horse;
    string *saved_data;
    mapping steed_owners = ([ ]);
    string horse_name;
    steed_owners = restore_map("/d/Shire/rivendell/steeds/steed_owners");
    if (!steed_owners[TP->query_real_name()])
    {
        write("You don't own a horse to dismiss. Go visit the stable master.");
        return 1;
    }
    saved_data = steed_owners[TP->query_real_name()];
    horse_name = saved_data[2];

    if (find_living(lower_case(horse_name)))
    {
        horse = find_living(lower_case(horse_name));
        horse->remove_object;
        write("You send your horse off to graze.");
        return 1;
    }


    return 1;
}


init()
{
    ::init();
    add_action(summon_horse, "hsummon");
    add_action(dismiss_horse, "hdismiss");

}
