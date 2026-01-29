#pragma strict_types

inherit "/std/monster.c";
inherit "/d/Gondor/common/lib/logkill.c";

#include <macros.h>
#include <ss_types.h>

#include "/d/Gondor/defs.h"

public void
create_monster()
{
    set_name(({"guard","cityguard","guard of the citadel"}));
    set_race_name("human");
    set_short("strong guard");
    set_long("This guard is one of the Guards of the Citadel. He is robed in black,\n"+
    "and has a strange, high-crowned helmet with wings of seabirds set above\n"+
    "some long, close-fitting cheek-guards. Upon his black surcoat you can\n"+
    "see the embroidered image of a white tree in blossom beneath a silver\n"+
    "crown and many-pointed stars. This is the emblem of the heirs of Elendil,\n"+
    "and none except the Guards of the Citadel wear it now.\n");
    set_adj(({"tall","strong"}));
    set_pshort("strong guards");
    set_alignment(400+random(80));
    default_config_npc(random(13)+58);
    set_base_stat(SS_CON,random(14)+62);
    set_skill(SS_WEP_SWORD, random(10)+70);
    set_skill(SS_WEP_POLEARM, random(10)+80);
    set_skill(SS_PARRY,85);
    set_skill(SS_DEFENCE,85);
    set_chat_time(16);
    add_chat("Looks like the War is drawing nigh.");
    add_chat("What are you hanging around here for?");
    add_chat("Minas Tirith is a well-guarded city.");
    add_chat("I am with the Guards of the Citadel.");
    add_chat("I don't like the dark clouds gathering in the east.");
}

public void
arm_me() 
{
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

/* Knights will loose prestige on this one */
public int query_knight_prestige() { return -8; }

