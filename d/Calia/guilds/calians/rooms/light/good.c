
/* 
   Room with the good elf that administers the sword of light quest in
   the palace.

   Coded by Glykron.

   History:
            6/4/96     tidied up kroug handling                 Maniac
           22/9/95       kroug raid code installed              Maniac
*/


#pragma save_binary

inherit "/d/Calia/std/kroug_palace_room";
#include <stdproperties.h>
#include <macros.h>
#include "defs.h"

object calian = 0, this;

void
bow_to(object ob)
{
    calian->command("bow " + ob->query_name());
}


void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);

    if (!living(ob) || !calian || !present(calian, this))
	return;

    set_alarm(1.0, 0.0, &bow_to(ob)); 
}

void
reset_room()
{
    if (objectp(calian))
	return;

    calian = clone_object(MONSTER("good_calian"));
    calian->move(this);
    tell_room(this, QCTNAME(calian) + " arrives.\n");
    calian->command("bow");
}

void
create_room()
{
    set_short("The room of goodness");
    set_long(
	"This is a small trapezoidal-shaped room whose south and east walls " +
	"slope away from you to the northwest.  " +
	"There is a bed and an altar against the northwest wall.  " +
	"\n");
    add_prop(ROOM_I_INSIDE, 1);
    add_exit(ROOM("light_late"), "south", 0);
    add_exit(ROOM("light_silver"), "southeast", 0);
    add_item("bed", "The bed is emitting white light.\n");
    add_item("altar", "The altar is giving off a white glow.\n");
    this = THIS;
    reset_room();
}
