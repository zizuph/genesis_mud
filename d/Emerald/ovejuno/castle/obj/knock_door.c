inherit "/d/Emerald/std/door";

#include <macros.h>

string
respond_to_knock()
{
    object odoor = query_other_door(), env, doorman;

    if (odoor && (env = environment(odoor)))
    {
        if (doorman = present("ov_castle_doorman", env))
	{
            set_alarm(1.0, 0.0, &doorman->command("open door"));
	}
    }
        
    return standard_knock_resp2();
}

void
create_emerald_door()
{
    set_name("door");
    set_door_name(({ "door" }));
    set_door_desc("This is a magnificent mahoney door. Intricate "+
        "carvings cover the door from top to bottom, showing "+
        "elves doing different activities like hunting and "+
        "falconery. It makes a stark constrast with the rest of "+
        "portico.\n");
    set_adj(({ "magnificent", "mahoney" }));
    set_unlock_command("unlock");
    set_lock_command("lock");
    set_knock_resp(({ VBFC_ME("standard_knock_resp0"), "@@respond_to_knock@@",
                      VBFC_ME("standard_knock_resp2") }));
    set_open(0);
    set_locked(0);
    set_key("01");
}
