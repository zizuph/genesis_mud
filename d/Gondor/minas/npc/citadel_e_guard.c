/*
 *  /d/Gondor/minas/npc/citadel_e_guard.c
 *      Modified from /d/Gondor/minas/npc/citadel_guard.c
 *      Alto, 20 April 2001
 *
 */

#pragma strict_types

inherit "/d/Gondor/minas/npc/mtirith_monster.c";
inherit "/d/Gondor/common/lib/binbit.c";
inherit "/std/act/domove";
inherit "/std/act/action";
inherit "/std/act/attack";


#include "/d/Gondor/minas/lib/porter_defs.h"
#include <language.h>
#include <ss_types.h>
#include <macros.h>
#include <stdproperties.h>

#include "/d/Gondor/defs.h"
#include "/d/Gondor/bits.h"

#define INNER_MINAS "/d/Gondor/minas"

object actor, *inv;

public void   open_door();

public void
create_monster()
{

    if (!IS_CLONE) return;
    seteuid(getuid());
 

    ::create_monster();
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

    clone_object(INNER_MINAS + "/obj/tower_door_key.c")->move(TO);

    set_chat_time(11);

    add_chat("None may pass except those on the business of the Steward.");
    add_chat("A storm is coming. Let us hope the city is prepared.");
    add_chat("Do not try the patience of the Lord. He is in a fell mood "
        + "this day.");
    add_chat("What is your business here, stranger?");
    add_chat("Have you news of Faramir?");

    set_act_time(10);
    add_act("emote looks closely at you.");
    add_act("emote adjusts his surcoat.");
    add_act("emote peers carefully about the area.");
    add_act("emote adjusts his winged helm.");
    add_act("hmm");
    add_act("pace");
    add_act("sigh");

    add_ask(({"to be admitted", "unlock door", "door", "open door", 
        "to open door", "about door"}), &open_door());


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
close_door()
{
    command("close door");
    command("lock door with key");
}

string
open_door()
{
    if (TP->query_wiz_level())
    {
        command("say But of course, Wizard.");
        command("bow");
        command("unlock door with key");
        command("open door");
        set_alarm(7.0, 0.0, &close_door());
        return "";
    }

    if (TP->query_prop(SENT_TO_DENETHOR))
    {
        command("say Ahh, you have business with the Steward.");
        command("bow");
        command("unlock door with key");
        command("open door");
        set_alarm(7.0, 0.0, &close_door());
        return "";
    }

    if (TP->test_bit("gondor", MTIRITH_PORTER_GROUP, MTIRITH_DENETHOR_BIT))
    {
        command("say Greetings, Servant of the Tombs.");
        command("bow");
        command("unlock door with key");
        command("open door");
        set_alarm(7.0, 0.0, &close_door());
        return "";
    }


    else
    {
        command("peer" + TP->query_real_name());
        command("say You have no business with the Steward. Begone!");
    }
    return "";
}



/* Knights will loose prestige on this one */
public int query_knight_prestige() { return -8; }

