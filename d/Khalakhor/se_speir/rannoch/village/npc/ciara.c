/* File         : /d/Khalakhor/se_speir/rannoch/npc/ciara.c
 * Creator      : Darragh@Genesis
 * Date         : 00-10-03      
 * Purpose      : Npc in the Loch Rannoch area.
 * Related Files: 
 * Comments     : 
 * Modifications: 
 */

#pragma strict_type

#include "/d/Khalakhor/sys/defs.h"
#include "/d/Khalakhor/sys/paths.h"
#include <ss_types.h>
#include <macros.h> 
#include <stdproperties.h>
#include "npc.h"

inherit "/d/Khalakhor/lib/clan_support";
inherit "/d/Khalakhor/se_speir/port/npc/help_me";
inherit STDHUMAN;

mapping remembered;
object last_attacker;
int return_alarm_id,
    attacker_alarm_id,
    has_armed;

public void
arm_me()
{
    if (has_armed)
        return;

    seteuid(getuid());

    clone_object("/d/Khalakhor/common/arm/belt")->move(TO);
    clone_object("/d/Khalakhor/se_speir/rannoch/arm/skirt")->move(TO);
    clone_object("/d/Khalakhor/se_speir/rannoch/arm/shirt")->move(TO);
    clone_object("/d/Khalakhor/se_speir/rannoch/obj/basket")->move(TO);
    clone_object("/d/Khalakhor/se_speir/rannoch/arm/boots")->move(TO);
    clone_object("/d/Khalakhor/se_speir/rannoch/arm/bonnet")->move(TO);

    command("wear all");
    command("hold basket");
    command("smile cutely");

    has_armed = 1;

}
public void
create_khalakhor_human()
{
    set_name("ciara");
    set_living_name("ciara");
    add_name(({"girl","villager"}));
    set_gender(G_FEMALE);
    set_adj(({"young", "fragile"}));
    set_long("A local girl, dressed in simple clothing. She is obviously "
           + "looking for something, and she looks a bit worried.\n"
           + "She has keen chestnut brown eyes.\n"
           + "Her hair is shoulder length, brown, and styled with pigtails.\n");  

    default_config_npc(30);

    set_skill(SS_UNARM_COMBAT, 20);
    set_skill(SS_PARRY, 10);
    set_skill(SS_DEFENCE, 20);
    set_skill(SS_BLIND_COMBAT, 25);

    set_skill(SS_APPR_MON, 30);
    set_skill(SS_AWARENESS, 80);

    set_skill(SS_LANGUAGE, 30);
    set_skill(SS_HERBALISM, 50);

    set_alignment(500);
    set_exp_factor(30);
    set_size_descs("short", "skinny");
    remembered = ([]);
    set_alarm(0.5, 0.0, arm_me);

    set_m_in("skips in");
    set_m_out("smiles broadly and skips");
 
    add_prop(NPC_M_NO_ACCEPT_GIVE," says: Mother tells me I shouldn't let strangers give me things. "
                                + "But it looked interesting!\n");
    add_prop(NPC_I_NO_LOOKS, 1);

    set_restrain_path("/d/Khalakhor/se_speir/rannoch/road");
    set_random_move(10);

    set_default_answer("Umm...I don't want to talk to you.");
    add_ask(({"road","path","paths","roads"}),
            "say I keep to the road, to stay out of trouble.",1);
    add_ask(({"mother","father","family"}),
            "say Mother and father does not know I am on this "
          + "side of the gate. I wanted to surprise them with a "
          + "basket full of berries.",1);
    add_ask(({"berries","berry","mushroom","mushrooms"}),
            "say I am really good at finding berries, and I "
          + "like eating them too!",1);
    add_ask(({"bridge"}),
            "say I used to sit on the bridge and look at the river "
          + "go by. But someone ruined it! I hope they'll rebuild it.",1);
    add_ask(({"trouble"}),
            "say There are bandits in the woods, the hilltop is haunted, "
          + "and there's always old Bolok to worry about.",1);
    add_ask(({"bolok","boar"}),
            "say Bolok is an old boar that live in the hills. He is very, "
          + "very mean, look out if you're going up there!",1);
    add_ask(({"basket"}),
            "say Mother made this basket, and I was going to fill it before "
          + "going home again. But I don't dare go into the woods.",1);
    add_ask(({"village","home"}),
            "say I live in the village east of here, by the lake. But they don't "
          + "strangers in, you know.",1);
    add_ask(({"hilltop","hill","hills"}),
            "say Don't go up to the hilltop, they say it's haunted!",1);
    add_ask(({"bandits","bandit","thieves"}),
            "say I don't know much about those, never seen any. But it sounds "
          + "like they're not friendly at all!\n"
          + "The young fragile female human closes her eyes and pouts petulantly.",1);
    add_ask(({"clan","macfaolain"}),
            "say That's the major clan of our village. I don't care much for "
          + "clans and that, you know!",1);

    set_act_time(6 + random(3));
    add_act("smile cutely");
    add_act("bite");
    add_act("emote looks into her basket and sighs deeply.");
    add_act("emote adjusts her bonnet.");
    add_act("emote peers into the woods.");
    add_act("emote strokes one of her pigtails absentmindedly.");
    add_act("emote sings a cheerful song about squirrels.");
    add_act("emote pouts and mutters to herself.");

    set_chat_time(8 + random(3));
    add_chat("Have you seen any berries or mushrooms close to the road?");
    add_chat("I should have brought a smaller basket.");
    add_chat("A shame about the bridge. The best berries are on the other side.");
    add_chat("I sure hope that mean old boar don't show up...");

    add_cact("cry");
    add_cact("cower");
    add_cact("scream");
    add_cact("whine");

    add_cchat("Hey, I am only twelve!");
    add_cchat("Please stop!");
}

public int
my_communicate(string str)
{
    string temp;

    if (temp = TO->query_prop(LIVE_M_MOUTH_BLOCKED))
    {
	write(stringp(temp) ? temp : "You are gagged and cannot " +
	  "speak.\n");
    }

    tell_room(environment(), QCTNAME(TO) + " " + VBFC_ME("race_sound") +
      ": " + str + "\n");
}

public int
hook_return_intro(string str)
{
    command("bite");
    command("say Sorry " + capitalize(str) + ", but I'm really "
          + "not supposed to talk to you!");

    return 1;
}
