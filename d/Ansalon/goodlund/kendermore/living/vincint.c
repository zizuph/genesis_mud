/* Vincint, the learned Ogre Trainer of Kendermore, Gwyneth, June 1999 */

#include <stdproperties.h>
#include <ss_types.h>
#include <macros.h>
#include "/d/Ansalon/common/defs.h"
#include "/d/Ansalon/goodlund/kendermore/local.h"

inherit "/std/act/action.c";
inherit "/lib/unique";

inherit AM_FILE

create_krynn_monster()
{
    if (!IS_CLONE)
      return;

    set_name("vincint");
    set_long("This massive ogre is one of the ugliest creatures you've " + 
        "ever laid eyes on, yet a kindness lies behind his big baggy eyes. " + 
        "Large gaps show in his teeth when he smiles, and you can detect " + 
        "a subtle gentleness in his meaty gnarled hands. This must be the " + 
        "most unusual ogre in all of Krynn. He stands in this large " + 
        "courtyard, training those who wish it.\n");
    set_race_name("ogre");
    set_adj("massive");
    add_adj("friendly");
    set_gender(G_MALE);
    set_stats(({130, 85, 110, 70, 70, 85}));
    set_hp(query_max_hp());
    add_prop(NPC_I_NO_LOOKS, 1);

    set_act_time(5);
    add_act("climb wall");
    add_act("say Kender are wonderful folk.");
    add_act("say The kender in Kendermore treat me very well. They don't " + 
        "mind at all that I'm an ogre.");
    add_act("say I'm not your typical ogre.");
    add_act("emote swings his club in practice.");
    add_act("say Would you like to train?");
    add_prop(NPC_M_NO_ACCEPT_GIVE, " doesn't look very interested.\n");

    set_skill(SS_DEFENCE, 30);
    set_skill(SS_WEP_CLUB, 90);
    set_skill(SS_CLIMB, 80);

    set_alignment(100);
    set_knight_prestige(-10);

    set_alarm(1.0,0.0,"arm_me");
}

/* Function name : Arm me
 * Description : Clones, wears and wields armours and weapons.
 * Returns : Null
*/

void
arm_me()
{
    setuid();
    seteuid(getuid(TO));
    clone_object(KOBJ + "ogrechain")->move(TO, 1);
    clone_object(KOBJ + "ogrepants")->move(TO, 1);
    clone_unique(KOBJ + "sturdy_mace", 5, KOBJ+"ogreclub")->move(TO,1);
    command("wield all");
    command("wear all");
}


