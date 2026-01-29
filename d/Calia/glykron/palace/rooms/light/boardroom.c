/*
 * This room contains the private board for the Calian Guild
 *
 * CODER: Zima  08/09/93
 * MODIFIED: Glykron 08/15/93
 * Modified to include poster: Maniac 14/4/94
 * Modified to handle recruiters: Glykron 20/11/94
 * Recruiter stuff moved to recruiter room: Maniac 3/1/95
 * Council retirements plaque moved in: Maniac 7/7/95
 * ROOM_I_INSIDE added by Maniac 18/8/95
 * ROOM_M_NO_ATTACK property removed, 
 * changed ROOM_M_NO_TELEPORT to ROOM_M_NO_TELEPORT_TO, Maniac 12/9/98
 * Couches upgraded by Glykron 05/26/00
 */

#pragma save_binary

#include <stdproperties.h>
#include <macros.h>
#include <composite.h>
#include "defs.h"
inherit GLYKRON_LIGHT_ROOMS + "couches_room";
#include COUNCIL_HEADER

static object this;

status
west()
{
    if (!(COUNCIL_CODE->is_council_member(TP->query_name()) ||
          COUNCIL_CODE->is_calian_wiz(TP)))
    {
        TP->catch_msg("You are not allowed to enter the Council " +
                      "chambers.\n");
        return 1;
    }

    return can_leave();
}

/*
 * Function: enter_inv
 * Description: block non-interactives from entering.
 */
void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);

    if (living(ob) && !interactive(ob))
        ob->move(from);
}

void
create_room()
{
    set_short("Private Board room of the Calian Guild");
    set_long(
        "This is a small trapezoidal-shaped room whose north and south walls " +
        "slope away from you to the west.  " +
	"This room contains the private board for the Calian Guild.  " +
	"Plush couches sit along the north wall where members may sit and " +
	"discuss the guild's business.  " +
	"A heavy oak writing table sits against the south wall, over which " +
        "hangs a large gold seal." +
        "\n");

    add_exit(ROOM("light_councilroom1"), "west", west);
    add_exit(ROOM("light_guild"), "south", can_leave);
    add_exit(ROOM("light_recruiter"), "north", can_leave);
    add_exit(GLYKRON_LIGHT_ROOMS + "maul_room", "northwest", can_leave); 

    add_item("couches", describe_couches);

    add_item( ({ "table", "writing table" }),
        "Made of sturdy oak, this table looks centuries old, " +
        "though well kept.  Parchment, an inkwell and a quill " +
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
    clone_object(OBJECT("calian_private_board"))->move(this);
    clone_object(GLYKRON_OBJECTS + "plaque")->move(this);
    ::create_room();
}
