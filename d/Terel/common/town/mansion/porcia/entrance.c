/*
    Entrance to Porcia's rooms, leading to one (or several) logical riddles
    Dust 921016
 */
inherit "/std/room";
#include <stdproperties.h>
#include <macros.h>
#include "/d/Terel/common/terel_defs.h"

#define PORDIR "/d/Terel/common/town/mansion/porcia/"

void
create_room()
{
    set_short("mysterious hall");
    set_long(break_string("You find yourself in a very mysterious, old " +
	"hall. There's absolutely no furniture in it and the hall " +
	"is so big that you can hear your own echo and the echo of " +
	"the floor cracking under your feet. The only remarkable " +
	"feature in this room is a huge question mark painted " +
	"on the floor. You also notice a sign over the south exit. " +
	"A narrow tunnel leads to the north.\n",70));
    add_item(({"floor"}), break_string(
        "The floor is made of wooden boards which have shrunk in this " +
        "dry climate, hence leaving quite large gaps between the boards. " +
        "There's a huge question mark painted on the floor.\n",70));
    add_item(({"wall", "walls"}), break_string(
        "The dusty wooden walls have not been touched by human hands " +
        "for many years.\n",70));
    add_item(({"web", "webs", "cobwebs", "cobweb"}), break_string(
        "From the size of the cobwebs you realise that the creatures " +
        "who made them must be quite big.\n",70));
    add_item(({"question mark", "mark"}), break_string("You have no " +
	"idea why somebody painted this question mark on the floor. " +
	"But an inner voice tells you that you shouldn't be too " +
	"curious, but rather wise and prudent. Being curious could " +
	"be bad for your health..\n",70));
    add_item("sign", "@@exam_sign");
    add_cmd_item("sign", "read", "@@read_sign");
/*  'READ' ability added to sign by Napture.
    add_item(({"sign"}), break_string("The sign reads: Don't dare to " +
	"enter this room unless you're very convinced of your " +
	"intellectual skills, or you'll never be able to leave this " +
	"room again!\n",70));
*/

    add_prop(ROOM_I_INSIDE, 1);

    add_exit(MANSION + "wing_e3", "east", 0);
    add_exit(PORDIR + "riddle_room", "west", 0);
    add_exit(PORDIR + "tunnel", "north", 0);
    add_exit(PORDIR + "nimroom","south",0);
}

exam_sign()
{
    return break_string("The sign reads: Don't dare to " +
   "enter this room unless you're very convinced of your " +
   "intellectual skills, or you'll never be able to leave this " +
   "room again!\n",70);
}

read_sign()
{
    write(exam_sign());
    return 1;
}
