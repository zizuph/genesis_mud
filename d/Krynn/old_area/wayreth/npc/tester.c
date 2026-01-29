


    /*    Written and coded by Belize    */
    /*    With a great help of Teth    */
    /*    17.01.1997    */




#include <std.h>
#include <ss_types.h>
#include <wa_types.h>
#include <stdproperties.h>
#include <macros.h>
#include "/d/Krynn/common/defs.h";
inherit M_FILE
inherit AUTO_TEAM

inherit "/std/act/domove";   /* Allows Dranin to move */
inherit "/std/act/action";   /* Allows Dranin to act */



void
create_krynn_monster()
{
    string str;

    set_race_name("guardian");
    set_long("This apparition is barely visable, yet it's eyes gleam "+
	"brighter, and darker, than the hottest of flames. It's very "+
	"presence leaves you in fear.\n");
    set_adj(({"ghastly","spectral"}));
    set_gender(G_MALE);
    add_prop(NPC_I_NO_LOOKS,1);

    set_stats(({90,160,160,90,90,80}));
    set_skill(SS_DEFENCE,        90);
    set_skill(SS_UNARM_COMBAT,   00);
    set_skill(SS_BLIND_COMBAT,   90);
    set_skill(SS_AWARENESS,      90);

    set_alignment(0);
}
