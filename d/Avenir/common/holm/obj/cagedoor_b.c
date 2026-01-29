
inherit   "/std/door";
#include  "/d/Avenir/common/holm/t_camp/camp.h"

void
create_door()
{
    set_door_id("_cage_door_1");
    set_pass_command(({"go through","out","exit", "north"}));         
    set_fail_pass("Walking through a door is a skill you haven't " +
        "mastered yet. Try opening it first.\n");
    set_door_name(({"iron grill","cage door", "cell door", "grill",
        "grille", "door"}));
    set_door_desc("A flat iron grill that acts as the door to this cage. "+
        "There is a lock on it.\n");
    set_other_room(T_CAMP + "c3");
    set_open(0);
    set_locked(1);
    set_open_command(({"open","open grill","turn","push"}));
    set_open_mess(({"pushes the grill open.\n", "The iron grill " +
        "slowly opens wide.\n"}));
    set_fail_open(({"The grill is already open!\n",
        "You must unlock the grill before it can be opened!\n"}));
    set_close_command(({"close","pull", "pull closed", "close grill"}));
    set_close_mess(({"pulls the grill closed.\n", "The iron grill " +
        "slowly slides closed.\n"}));
    set_fail_close("The iron grill is already closed.\n");
    set_lock_name(({"lock","keyhole"}));
    set_lock_desc("It is a small lock made of iron. It is a very simple "+
        "one.\n");
    set_lock_command(({"lock","turn key"}));
    set_lock_mess(({"turns a key in the lock of the cage door.\n",
        "You hear a click from the lock of the cage door.\n"}));
    set_fail_lock(({"The cage door is already locked.\n",
        "You feel silly trying to lock an open door!\n"}));
    set_unlock_command(({"unlock","turn key"}));
    set_unlock_mess(({"does something with the keyhole, unlocking "+
        "the grill.\n", "You hear a click from the lock on the "+
        "cell door, perhaps it is unlocked now.\n"}));
    set_fail_unlock("That doesn't seem possible...\n");
    set_key(CAGE_KEY);
    set_pick(10);
} 
