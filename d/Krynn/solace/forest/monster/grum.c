/*
 * Grum Skunkbreath
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

inherit "/std/act/domove";     /* Allows Grum to move */
inherit "/std/act/action";     /* Allows Grum to act  */

#define OBJ    "/d/Krynn/solace/forest/obj/"

void
create_krynn_monster()
{
    string str;

    set_name("grum");
    set_living_name("grum");
    set_race_name("goblin");
    set_title("Skunkbreath, Guard of the Fewmaster");
    set_long("This goblin is a member of the Solace patrol. His crude " +
             "uniform covers only his torso. It is difficult to tell if " +
             "he is actually bald, or if he shaves his head. Although " +
             "somewhat overweight, it seems that he is well-muscled " +
             "underneath his fat.\n");
    add_name("skunkbreath");
    set_adj("jaw-gnashing");
    add_adj("slovenly"); 
    set_gender(G_MALE);
    add_prop(NPC_I_NO_LOOKS,1);
    set_introduce(1);

    set_stats(({115,94,130,70,60,100}));
    set_skill(SS_DEFENCE,        90);
    set_skill(SS_PARRY,          75);
    set_skill(SS_WEP_SWORD,      90);
    set_skill(SS_BLIND_COMBAT,   50);
    set_skill(SS_AWARENESS,      50);

    set_alignment(-400);
    set_knight_prestige(350);

    set_act_time(6);
    add_act(({"say Da citizens of Solace are bugs beneath my feet!" ,
            "emote stomps his foot as if squishing a bug."}));
    add_act("emote rubs his head in apparent thought.");
    add_act("emote picks his nose.");
    add_act("emote blows his nose into his hand, then wipes his hand on " +
            "his leg.");
    add_act("emote grins, thinking of looting Solace.");

    set_cact_time(6);
    add_cact("say If I kill you and find a blue crystal staff, Toede " +
             "will be most pleased.");
    add_cact("tackle all");
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

