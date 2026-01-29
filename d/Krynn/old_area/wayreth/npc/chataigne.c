


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

    set_name("chataigne");
    set_living_name("chataigne");
    add_prop("LIVE_I_ALWAYS_KNOWN",1);
    set_race_name("human");
    set_title("Mellegien of Northern Ergoth, the Mistress of the "+
	 "Order of the Black Robes");
    set_adj(({"dark-robed","hooded"}));
    set_scar(778);
    set_gender(G_FEMALE);


    set_stats(({96,103,100,121,105,103}));
    set_skill(SS_DEFENCE,        30);
    set_skill(SS_PARRY,          15);
    set_skill(SS_WEP_POLEARM,    30);
    set_skill(SS_BLIND_COMBAT,   20);
    set_skill(SS_AWARENESS,      50);

    set_alignment(-600);
    set_appearance(67);
    add_prop("_cont_i_height",175);
    add_prop("_cont_i_weight",59855);
}


public void
arm_me()
{
    clone_object("/d/Krynn/wayreth/guild/black/robe")->move(TO);
    command("wear all");
}

string
query_guild_name_occ()
{
    return "Wizards of High Sorcery";
}
