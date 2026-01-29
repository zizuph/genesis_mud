/* Created by Lucas */

inherit "/std/door";

create_door()
{
    set_other_room("/d/Emerald/eclipsia/coral_requiem/cr19");
    set_door_desc("The great stone slabs are very intimidating indeed. " +
        "They probably weigh more than you can imagine.\n");
    set_door_name("door");
    set_door_id("crdoor");
    set_open(0);
    set_open_desc("The great stone slabs have retracted into the walls.\n");
    set_closed_desc("The stone door is closed.\n");
    set_pass_command("southeast");
    set_fail_pass("The great door is closed.\n");
    set_open_mess(({"opens the great door.\n", "The great " +
        "stone slabs slide open.\n"}));
    set_fail_open(({"The door is already open.\n", "The door won't " +
        "budge. It must be locked.\n"}));
    set_close_mess(({"pulls the slabs shut.\n", "The stone slabs slide shut.\n"}));
    set_fail_close("The door is already closed.\n");
    set_locked(1);
    set_lock_name("crack");
    set_lock_desc("The crack looks to be some kind of lock.\n");
    set_lock_command("lock");
    set_lock_mess(({"slides the key into the crack and locks the door.\n", "You hear the door lock.\n"}));
    set_fail_lock(({"The door is already locked.\n", "The door is still open.\n"}));
    set_unlock_command("unlock");
    set_unlock_mess(({"slides the key into the crack and unlocks the door.\n", "You hear the door lock.\n"}));
    set_fail_unlock("The door is already unlocked.\n");
    set_key(2280);
    set_pick(100);
    set_str(10);
}
