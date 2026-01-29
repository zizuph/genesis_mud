inherit "/std/door";
#include "../../guild.h"

create_door()
{
    set_door_id("_grandmaster_door_");
    set_pass_command(({"ne", "northeast", "grandmaster"}));
    set_fail_pass("Walking through doors is a skill you haven't " +
      "mastered yet. Try opening it first.\n");
    set_door_name(({"Grandmaster door", "grandmaster door", "grandmaster",
	"door", "platinum door", "gm"}));

    set_door_desc("The door is coated with platinum, and an exquisite engraving "+
      "of the Triumvirate decorates it, bearing the symbols of the Crown, Sword, "+
      "and Rose. Rather heavy, it looks like it would take the combined weights "+
      "of several men thrown against it to force the door open.\n");
    set_other_room(VROOM + "grandmaster_office");
    set_open(0);
    set_locked(1);
    set_open_desc("An open platinum door leads northeast into the office of the Grand Master.\n");
    set_closed_desc("");

    set_open_command(({"open","turn","push"}));
    set_open_mess(({"pushes the platinum door open.\n",
	"The platinum door slowly opens wide.\n"}));
    set_fail_open(({"The platinum door is already open!\n",
	"You must unlock the platinum door before it can be opened!\n"}));
    set_close_command(({"close","pull", "pull closed", "shut"}));
    set_close_mess(({"pulls the platinum door closed.\n", "You pull the platinum " +
	"door closed.\n"}));
    set_fail_close("The platinum door is already closed.\n");
    set_lock_name(({"lock","keyhole"}));
    set_lock_desc("It is difficult to discern anything about the lock.\n");
    set_lock_command(({"lock","turn key"}));
    set_lock_mess(({"turns a key in the lock of the platinum door.\n",
	"You hear a click from the lock of the platinum door.\n"}));
    set_fail_lock(({"The platinum door is already locked.\n",
	"You feel silly trying to lock an open door!\n"}));
    set_unlock_command(({"unlock","turn key"}));
    set_unlock_mess(({"turns a key in the keyhole, unlocking the platinum door.\n",
	"You hear a click from the lock on the platinum door, perhaps it is "+
	"unlocked now.\n"}));
    set_fail_unlock("You feel silly trying to lock a door that is " +
      "already locked!\n");
    set_key("_grandmaster_key");
    set_pick(101);
}

