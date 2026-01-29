/* counrcpt.c: Council reception room. 'Spot' the cylops will keep
 *     people out of the main chambers till the council is ready to
 *     go on line, at which point he will let some people through.
 *     Of course what the council names him is there own affair,
 *     but I have a think for the name Spot. - Serpine, 4-24-95.
 * - Revolt limit changed to 9 due to 16 players voted in last 
 *   election. So half the voters plus 1. This will be done manually
 *   until it can be automated. Damaris@Genesis 11/2006
 * - Added recruitment Overseer - Damaris@Genesis 12/2006
 * - No longer checks to see if cilops is there before blocking council
     room exit. Rhyn@Genesis 12/2006
 *
 *  2021-07-11 Meton expanded revolt to point out its against all overseers
 *
 *
 */
#pragma save_binary

inherit "/std/room";
inherit "/d/Cirath/athas/gladiator/cmd/list_overseers";
inherit "/d/Cirath/athas/gladiator/cmd/revolt";
inherit "/d/Cirath/athas/gladiator/cmd/regret_revolt";
inherit "/d/Cirath/std/Cirath_magic_room_std";

#include "defs.h"

void
create_room()
{
    set_short("hall of the Overseers");
    set_long("This vaulted chamber is where the Overseers of the " +
	"Gladiators of Athas can speak with their charges without " +
	"letting them into the private hall to the east. The High " +
	"Overseer can also appoint within this room. A stain " +
	"darkens the floor, a crimson stain.\n" +
        "Within this place you may 'list overseers', or even " +
        "'revolt' against all of them and their tyranical rule, "+
        "though the latter should only be done in the " +
        "case of extreme failure by the Overseers and often leads to " +
        "a severe case of 'regret'.\n");
    add_item(({"stains", "stain", "floor"}), "Think about it.\n");
    INSIDE
    add_exit(GLAD_ROOM + "stairwy3", "north", 0, 1);
    add_exit(GLAD_ROOM + "counmain", "east", "@@spot_block@@", 1);
}

int
spot_block()
{
    if(TP->query_wiz_level() || POSITION(TP) != POS_NONE)
        return 0;

    write("Suddenly an area of shadow in the eastern chambers " +
        "seems to take form: A long chitinous shape with two ... no ... " +
        "three sets of gigantic mandibles. Your mind tells you that " +
        "you must fear it: You have no choice in the matter. But as " +
        "you back away the fear subsides and the five yard greyish " +
        "mass again becomes one with the darkness.\n");
    return 1;
}

void
init()
{
    ::init();
    add_action(_cmd_list_overseers, "list");
    add_action(_cmd_revolt, "revolt");
    add_action(_cmd_regret_revolt, "regret");
}
