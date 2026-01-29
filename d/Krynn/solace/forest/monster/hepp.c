/*
 * Hepp Teznakk
 * by Teth, April 25, 1996
 * modified from Fewmaster Toede
*/

#include <std.h>
#include <ss_types.h>
#include <wa_types.h>
#include <stdproperties.h>
#include <macros.h>
#include "/d/Krynn/common/defs.h";
inherit M_FILE
inherit AUTO_TEAM

inherit "/std/act/domove";     /* Allows Hepp to move */
inherit "/std/act/action";     /* Allows Hepp to act  */

#define OBJ    "/d/Krynn/solace/forest/obj/"

void
create_krynn_monster()
{
    string str;

    set_name("hepp");
    set_living_name("hepp");
    set_race_name("goblin");
    set_title("Teznakk, Guard of the Fewmaster");
    set_long("This goblin is a member of the Solace patrol. His crude " +
             "uniform covers only his torso. His lean body suggests " +
             "that he is well-disciplined and a formidable foe. One " +
             "large tooth extends upward and outward from his lower " +
             "jaw.\n");
    add_name("teznakk");
    set_adj("long-toothed");
    add_adj("lean"); 
    set_gender(G_MALE);
    add_prop(NPC_I_NO_LOOKS,1);
    set_introduce(1);

    set_stats(({130,110,160,70,60,85}));
    set_skill(SS_DEFENCE,        90);
    set_skill(SS_PARRY,          75);
    set_skill(SS_WEP_SWORD,      90);
    set_skill(SS_BLIND_COMBAT,   50);
    set_skill(SS_AWARENESS,      50);

    set_alignment(-400);
    set_knight_prestige(350);

    set_act_time(6);
    add_act(({"say These Solace citizens live far too long." ,
            "emote fingers the hilt of his sword."}));
    add_act("emote practices a feinting maneuver.");
    add_act("emote squeezes a pimple.");
    add_act("emote stops suddenly, lifts his leg, and picks out some " +
            "dirt from between his toes. He smells the dirt, then chews " +
            "on it before spitting it out.");
    add_act("emote flexes his biceps, admiring the ripples.");

    set_cact_time(6);
    add_cact("say If I kill you and find a blue crystal staff, Toede " +
             "will be most pleased.");
    add_cact("say You fight like a gully dwarf.");
    add_cact("emote swings his weapon wildly.");
    add_cact("emote grasps for your neck with his purplish-red hands.");	
}

public void
arm_me()
{
    clone_object(OBJ + "gsword")->move(TO);
    clone_object(OBJ + "garmour")->move(TO);
    command("wear all");
    command("wield all");
}

