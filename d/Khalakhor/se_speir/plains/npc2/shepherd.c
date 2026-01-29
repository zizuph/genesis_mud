//
// shepherd - in the pasture on the plains
//
// Zima  - May 18, 1998
//
#pragma strict_types
 
#include <ss_types.h>
#include <stdproperties.h>
#include <macros.h>
#include "/d/Khalakhor/sys/defs.h"
#include "/d/Khalakhor/sys/paths.h"
#include "/d/Khalakhor/common/room/nameserver.h"
#include "npc.h"
 
inherit STDHUMAN;
inherit "/d/Khalakhor/lib/clan_support";
inherit "/d/Khalakhor/se_speir/port/npc/help_me";
 
int has_armed=0;
 
//
// arm_me
//
public void arm_me()
{
    if (has_armed) return;
    seteuid(getuid());
    clone_object("/d/Khalakhor/common/arm/shirt_cloth")->move(TO);
    clone_object("/d/Khalakhor/common/arm/vest_cloth")->move(TO);
    clone_object("/d/Khalakhor/common/arm/belt")->move(TO);
    clone_object("/d/Khalakhor/common/kilts/kilt_tabor")->move(TO);
    clone_object(WEP+"shep_staff")->move(TO);
    command("wield all");
    command("wear all");
    has_armed = 1;
}
 
//
// create_khalakhor_human
//
public void create_khalakhor_human()
{
    string name="Heilyn";
    set_name(name);
    set_living_name(name);
    add_name("shepherd");
    set_adj("stout");
    add_adj("dirty");
    cs_set_sept("Gilvary");
    cs_set_clan("Tabor");
    cs_set_title("Shepherd of the plains");
    set_long(
       "From his dress, you can see that this man is a shepherd. "+
       "He looks strong and protective as he keeps watch over his flock.\n");
 
    default_config_npc(60);
    set_skill(SS_AWARENESS, 75);
    set_skill(SS_UNARM_COMBAT, 40);
    set_skill(SS_DEFENCE, 40);
    set_skill(SS_PARRY,   40);
    set_skill(SS_WEP_KNIFE, 50);
 
    set_random_move(60);
    set_act_time(60);
    add_act("emote scans out over the plains looking for danger.");
    add_act("emote counts his sheep on his fingers.");
    add_act("emote prods a sheep with his staff.");
    add_act("emote leans on his staff and sighs tiredly.");
    add_act("emote nods at you politely.");
    add_act("emote calls out to the sheep.");
 
 
    set_default_answer("I dunno that. Perhaps you could ask me wife?");

    add_ask("wife", "say She's a fine lass, my Ceile!", 1);
 
    set_alignment(200);
    set_exp_factor(75);
    set_size_descs("tall", "of normal width");
}
 
/*
 * Function name: hook_return_intro
 * Description  : Called when someone introduces themselves
 *                to us.
 * Arguments    : str - Name of the player introducing.
 * Returns      : 1
 */
public int hook_return_intro(string str) {
    command("say G'day thar, friend!");
    command("say Me be "+query_name()+" "+query_title()+"!");
    command("say May yer gods keep watch o'er ye!");
    return 1;
}
 
