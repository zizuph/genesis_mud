inherit "/std/door";
#include "/d/Gondor/defs.h"

create_door()
{
    ::create_door();
    set_door_id("greatgate");
    set_pass_command(({"sw","southwest"}));
    set_door_name(({ "great gate", "gate", "gates" }));
    set_other_room(ROH_DIR+"horn/burg/outer_court1");
    set_door_desc(BS("The great gate looks sturdy. It's made of "+
    "timber with great hinges of iron. The gate is reinforced with iron "+
    "bars.\n"));
    set_lock_command("lock");
    set_lock_name("lock");
    set_lock_desc("A massive lock.\n");
    set_unlock_command("unlock");
    set_open(0);
    set_locked(0);
    set_key(8000346);
    set_knock_command(0);
}

/*
 * Function name: pass_door
 * Description:   Pass the door.
 * Arguments:     arg - arguments given
 */
int
pass_door(string arg)
{
    int dexh;

    if (!other_door)
        load_other_door();

    if (open_status)
    {
        if (IS_EVIL(TP))
            ENV(TO)->close_gate_to_stop_invaders(TP);
        else
            TP->move_living(query_verb(), other_room);
    }
    else
        write(check_call(fail_pass));

    return 1;
}
