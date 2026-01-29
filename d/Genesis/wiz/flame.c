#pragma save_binary

#include <stdproperties.h>
#include "default.h"

#define BS(str) break_string(str, 65)

create_room() 
{
    set_short("Wizard battle room");
    set_long("Wizard battle room.\n"
	   + "This is a room for violent socialising and discussion.\n");
    add_exit(THIS_DIR + "lounge", "up");
    change_prop(ROOM_I_LIGHT, 10);
    add_default_exits();
    load_board("war");
}

enter_inv(ob, from)
{
    if (ob && living(ob))
	ob->catch_msg("The air smells of violence!\n\n" + 
	BS("No rules of decency apply here, no insults are too vile, no words too offensive. If you know you're a weak-minded sissy be sure to read the board only in the company of an adult.\n\n"));
}

leave_inv(ob, to)
{
    if (ob && living(ob))
	ob->catch_msg("The air feels fresh again!\n");
}