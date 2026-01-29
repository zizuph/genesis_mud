/* 
 * This room contains the private board for the Calian Guild 
 * Basically this is a copy of the main boardroom, coded by 
 * Zima, with some minor changes for trainees by Maniac 
 * 
 * History: 
 * 17/4/02    Maniac      copied over and modified from boardroom 
 * 
 */

#pragma save_binary

#include <stdproperties.h>
#include <macros.h>
#include <composite.h>
#include "defs.h"
inherit CRPALACE_LIGHT_ROOMS + "couches_room";
#include COUNCIL_HEADER

static object this;


void
create_room()
{
    set_short("Board room for trainees of the Calian Guild");
    set_long(
        "This is a small trapezoidal-shaped room whose north and south walls " +
        "slope away from you to the west. " +
	"This room contains the board for trainees of the Calian Guild. " +
	"Plush couches sit along the south wall where members may sit and " +
	"discuss the guild's business. " +
	"A heavy oak writing table sits against the north wall, over which " +
      "hangs a large gold seal." +
        "\n");

    add_exit(CRPALACE_LIGHT_ROOMS + "guild", "northeast", can_leave); 

    add_item("couches", describe_couches);

    add_item( ({ "table", "writing table" }),
        "Made of sturdy oak, this table looks centuries old, " +
        "though well kept. Parchment, an inkwell and a quill " +
        "sit atop the table to be used for writing." +
        "\n");
 
    add_item("seal",
        "Bearing the insignia of someone thinking very hard, this "  +
        "seal is encircled by a band of simple leaves and symbolizes " +
        "the Calian Warriors Guild." +
        "\n");

    add_prop(ROOM_M_NO_TELEPORT_TO, 1);
    add_prop(ROOM_I_INSIDE, 1);

    this = THIS;
    seteuid(getuid(this));
    clone_object(CRPALACE_OBJECTS + "calian_trainee_board")->move(this);
    clone_object(CRPALACE_OBJECTS + "trainee_chest")->move(this);
    ::create_room();
}
