/*
 *  /d/Gondor/minas/npc/g7_guard_in.c
 *      Modified from /d/Gondor/minas/npc/citadel_guard.c
 *      Alto, 28 April 2001
 *
 */

#pragma strict_types

inherit "/d/Gondor/minas/npc/mtirith_monster.c";
inherit "/d/Gondor/common/lib/binbit.c";
inherit "/std/act/domove";
inherit "/std/act/action";
inherit "/std/act/attack";

#include <language.h>
#include <ss_types.h>
#include <macros.h>
#include <stdproperties.h>

#include "/d/Gondor/defs.h"
#include "/d/Gondor/bits.h"

#define INNER_MINAS "/d/Gondor/minas"

string check_visitor();

public void
create_monster()
{

    set_name(({"guard","cityguard","guard of the citadel"}));
    set_race_name("human");
    set_short("strong guard");
    set_long("This guard is one of the Guards of the Citadel. He is robed "
        + "in black and has a strange, high-crowned helmet with wings of "
        + "seabirds set above the long, close-fitting cheek-guards. Upon his "
        + "black surcoat you can see the embroidered image of a white tree "
        + "in blossom beneath a silver crown and many-pointed stars. This is "
        + "emblem of the heirs of Elendil, and none except the Guards of "
        + "the citadel wear it now.\n");
    set_adj(({"tall","strong"}));
    set_pshort("strong guards");

    set_alignment(400+random(80));

    default_config_npc(random(13)+58);

    set_base_stat(SS_CON,random(14)+62);
    set_skill(SS_WEP_SWORD, random(10)+100);
    set_skill(SS_WEP_POLEARM, random(10)+100);
    set_skill(SS_PARRY,100);
    set_skill(SS_DEFENCE,100);

    clone_object(INNER_MINAS + "/obj/gate_seven_key.c")->move(TO);


    add_ask(({"to unlock gate", "unlock gate", "gate", "open gate", "open the gate",
        "open gates", "about gate", "to unlock the gate"}), &check_visitor());


    FIX_EUID;
    clone_object(WEP_DIR + "halberd")->move(TO);
    command("wield halberd");
    clone_object(ARM_DIR + "gchainmail")->move(TO);
    command("wear chainmail");
    clone_object(ARM_DIR + "winghelm")->move(TO);
    command("wear helm");
    clone_object(OBJ_DIR + "tower_surcoat")->move(TO);
    command("wear surcoat");


}


string
close_gate()
{
    command("close seventh gate");
    command("lock seventh gate with key");
}


string
check_visitor()
{
    if ((query_friend_or_foe(TP) < 0) && (!TP->query_wiz_level()))
    {
        command("scowl " + TP->query_real_name());
        command("say You are an enemy of the city!");
        command("say Begone!");
        return "";
    }

    else
    {
        command("say You may pass.");
        command("unlock seventh gate with key");
        command("open seventh gate");
        set_alarm(7.0, 0.0, &close_gate());
        return "";
    }
}



/* Knights will loose prestige on this one */
public int query_knight_prestige() { return -8; }

