


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
inherit "/d/Krynn/std/patrol";



void
create_krynn_monster()
{
    string str;

    set_race_name("elf");
    set_long("This elf looks to be a young warrior of the Silvanesti elves. "+
	"He doesn't appear to be terribly experienced, yet he has survived "+
	"battle where much blood was spilled.\n");
    set_adj(({"wary","haughty"}));
    set_gender(G_MALE);
    add_prop(NPC_I_NO_LOOKS,1);

    set_stats(({90,90,100,90,90,80}));
    set_skill(SS_DEFENCE,        90);
    set_skill(SS_PARRY,          75);
    set_skill(SS_WEP_POLEARM,    60);
    set_skill(SS_WEP_SWORD,      60);
    set_skill(SS_BLIND_COMBAT,   50);
    set_skill(SS_AWARENESS,      50);

    set_alignment(500);
}


public void
arm_me()
{
    clone_object("/d/Emerald/arm/patrol_lplate")->move(TO);
    clone_object("/d/Emerald/wep/patrol_longsword")->move(TO);
    command("wear all");
    command("wield all");
}
