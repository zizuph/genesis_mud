/* 	this is a room of the second floor of the crystalline palace

    coder(s):   Glykron
    history:
                 26/11/97   typo fixed                      Maniac
                 6.21.94    modified                        Glykron

    purpose:    guild quest, exit to upper levels of palace
    exits:      down to main stairs on first floor

    objects:    crystalline guild orb
    npcs:       none

    quests:     guild orb quest
    special:    none

    to do:      none
    bug:        none known
*/

#pragma save_binary

inherit "/std/room";
#include <stdproperties.h>
#include <macros.h>
#include "defs.h"
#include CALIAN_HEADER

object orb = 0, this;
string word = "";

string
table_desc()
{
    return "There is a little wooden table here.  " +
	"A scintillating tablet " +
	(orb ? "and a crystalline orb rest " : "rests ") +
	"on the table.\n";
}

string
tablet_desc()
{
    return word == "" ?
	"There is a scintillating tablet here that has enough room for one " +
	"word to be written on it.\n" :
	"There is a scintillating tablet here that has the word " + word +
	" written on it.\n";
}

void
reset_room()
{
    if (orb && present(orb, this))
	return;

    orb = clone_object(OBJECT("crystalline_orb"));
    orb->move(this);
    tell_room(this, capitalize(LANG_ADDART(QSHORT(orb))) + " appears!\n");
}

void
create_room()
{
    set_short("Central Stairs");
    set_long(
	"This is a large octogonal-shaped room.  " +
	"A spiral staircase ascends upward and descends downward.  " +
	"An intense beam of white light shines through the spiral.  " +
	"A table resides in the middle of the room.  " +
	"\n");
    add_prop(ROOM_I_INSIDE, 1);
    add_prop(ROOM_I_TYPE, ROOM_NORMAL);
    add_prop(ROOM_I_LIGHT, 1);
    add_exit(ROOM("light_stairs"), "down", 0);
    add_item( ({ "staircase", "stair", "stairs" }), "It is made of crystal.\n");
    add_item("table", "@@table_desc");
    add_item("tablet", "@@tablet_desc");
    this = THIS;
    call_out("reset_room", 1);
}

int
write_on_tablet(string str)
{
    string message;
    string *words;
    object tp;

    notify_fail("Write what?\n"); 
    if (!stringp(str) || !strlen(str)) 
	return 0;

    if (sscanf(str, "%s on tablet", message) != 1)
	message = str;

    words = explode(message, " ");
    word = words[0];

    if (sizeof(words) > 1)
	write("Only the word \"" + word + "\" will fit on the tablet.\n");
    else
	write("Ok.\n");

    tp = TP;
    say(QCTNAME(tp) + " writes \"" + word + "\" on the tablet.\n");

    if (orb && present(orb, THIS) && orb->query_prop(OBJ_M_NO_GET) &&
	word == (ROOM("light_guild"))->query_keyword() &&
	!tp->query_guild_member(GUILD_NAME))
    {
	write("The orb emits a flash of white light and then rolls off " +
	    "the table.\n");
	orb->remove_prop(OBJ_M_NO_GET);
	orb = 0;

	if (!tp->test_bit("Calia", 0, 1))
	{
	    write("You feel more experienced.\n");
	    tp->add_exp(2000);
	    tp->set_bit(0, 1);
	}
    }

    return 1;
}

void
init()
{
    ::init();
    add_action(write_on_tablet, "write");
}

public int
clean_up()
{
    if (!orb)
        remove_object();

    return 1;
}
