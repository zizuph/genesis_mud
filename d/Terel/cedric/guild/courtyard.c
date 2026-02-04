#pragma save_binary

inherit "/std/room.c";
#include <macros.h>
#include "/d/Terel/common/terel_defs.h"
#include "/d/Terel/cedric/guild/guild_defs.h"

#define GUILD_CHANGE_OBJ "/d/Terel/guilds/minstrels/obj/change_orb"

#define THANK_TEXT \
  "The Guildmaster Cedric ordered that this plaque be erected here to \n" \
+ "acknowledge his tremendous gratitude towards the following people: \n" \
+ "	Azireon\n" \
+ "	Mortricia\n" \
+ "	Karath\n" \
+ "	Juanita\n" \
+ "	Kithkanan\n" \
+ "	Tilton\n" \
+ "Without their help this guild would not be what it is today. Cedric \n" \
+ "would also like to express special appreciation for the creative and\n" \
+ "coding skills of Jorl and Horatio, and the support and guidance of \n" \
+ "Mecien. Without their help the guild would not be here at all.\n"

/* 
 * The Minstrel Guild Headquarters: Courtyard
 * This oddly shaped courtyard is actually an accoustically perfect 
 * transmitter; from the dais in the center one can be heard by Minstrels
 * the world over.
 *
 * Cedric 1/93
 */

object orb;

void
reset_room()
{
    seteuid(getuid());

    if(!objectp(orb))
    {
        orb = clone_object(GUILD_CHANGE_OBJ);
        orb->move(this_object(), 1);
    }    
}

void
create_room()
{
    set_short("The Courtyard of the Minstrels Palace");
    set_long(BS("You find yourself within the inner courtyard of the "
    + "guild.  The walls rise up from the central dais in gently graceful "
	+ "curves.  Sound behaves strangely here, as if the walls focused "
	+ "the music of the spheres. You expect the chaos of sound to produce "
	+ "a cacophony, surprisingly however, the sounds are quite distinct. " 
    + "The beautiful tones of the tower bells, though rung some time ago, "
	+ "seem to echo still.  This is obviously a place of some power.  "
	+ "As you stand in awe you are compelled to approach the dais. "
    + "The courtyard may be exited to the north or south, or you could climb "
    + "the dais steps.\n")+"A burnished plaque of some strange metal.\n");
    add_item("plaque",THANK_TEXT);
    add_cmd_item("plaque","read",THANK_TEXT);
    
    set_noshow_obvious(1);

    reset_room();
    
    add_exit(GUILD+"nice", "north");
    add_exit(GUILD+"auditorium", "south");
    add_exit(GUILD+"dais", "climb");
}

init()
{
    add_action("do_echo", "shout");
    ::init();
}

do_echo()
{
    TP()->catch_msg(BS("OUCH!\nThe echo from your shouting has left your ears "
    + "ringing!\n"));
}