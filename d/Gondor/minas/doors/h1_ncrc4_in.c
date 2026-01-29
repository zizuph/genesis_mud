inherit "/std/door";

#include <macros.h>
#include "/d/Gondor/defs.h"

void
create_door()
{
    ::create_door();
    set_door_id("MT_h1_ncrc4");
    set_pass_command(({"s","south"}));
    set_door_name(({"wooden door", "door"}));
    set_other_room(MINAS_DIR + "houses/g1ncrc4");
    set_door_desc(BSN("The wooden door looks rather old, but it "
      + "obviously has been painted regularly so there is hardly "
      + "any wear noticeable."));
    set_lock_command("lock");
    set_lock_name("lock");
    set_unlock_command("unlock");
    set_open(0);
    set_locked(0);
    set_key("MT_h1_ncrc4");
}

