#include <stdproperties.h>
#include <wa_types.h>
#include <ss_types.h>
#include <macros.h>
#include "/d/Ansalon/common/defs.h"
#include "/d/Ansalon/balifor/flotsam_forest/local.h"

inherit AM_FILE

#define WEP WEAPON + "sol_sword"
#define ARM1 ARMOUR + "sol_armour"
#define ARM2 ARMOUR + "sol_boots"

#define PLAYER_I_FOUND_TAIL "_player_i_found_tail"
#define PLAYER_I_ANSWER_RIDDLES "_player_i_answer_riddles"
#define PLAYER_I_PASS_MAZE "_player_i_pass_maze"
#define PLAYER_I_ENTER_LAIR "_player_i_enter_lair"

mixed
no_accept_from_dragonarmy()
{
    if (TP->query_dragonarmy_occ_member())
	return 1;
    return 0;
}

void
create_krynn_monster()
{
    if(!IS_CLONE)
	return;

    set_name("darryn");
    set_title("Marque, Knight of the Rose");
    set_race_name("human");
    set_adj("elderly");
    add_adj("noble");
    set_gender("G_MALE");
    set_long("Before you stands the leader of the covert " +
      "Circle of the Knights of Solamnia that operates outside of " +
      "Flotsam, an extremely dangerous yet important position " +
      "considering the lands around here are controlled by the " +
      "dragonarmies.\n");

    set_stats(({160,160,160,119,119,129}));
    set_hp(query_max_hp());

    set_skill(SS_WEP_SWORD, 100);
    set_skill(SS_DEFENCE, 100);
    set_skill(SS_PARRY, 100);
    set_skill(SS_BLIND_COMBAT, 90);
    set_skill(SS_AWARENESS, 80);

    set_alignment(1200);
    set_knight_prestige(-1000);
    set_act_time(0);
    add_act("say Although having to hide down here like rats is a slight to " +
      "our pride, it is our duty to maintain this Circle as " +
      "the Code and the Measure demands.");
    add_act("say May I inquire what you are doing here and how you found us?");
    add_act("sigh");

    set_cact_time(0);
    add_cact("say So be it fiend! Die like the scum you are!");

    add_ask("tanis","say Never heard of him",1);
    add_ask(({"berem","green gemstone man","gemstone man"}),"@@ansv_berem");
    add_ask(({"quest","task"}),"@@ansv_quest");
    add_ask(({"artifacts","heirloom"}),"@@ansv_arti");
    add_ask(({"plate armour","armour","plate armour of Solamnus"}),
      "@@ansv_armour");
    add_ask(({"circle","circle of knights","knights"}), "@@ansv_circle");
    set_default_answer("He decides not to answer your question.\n");

    add_prop(NPC_M_NO_ACCEPT_GIVE, no_accept_from_dragonarmy);
    seteuid(getuid());
}

int
check_dragonarmy()
{
    if (TP->query_dragonarmy_occ_member())
    {
	command("say I do not answer to a Dragonarmy rat!");
	return 1;
    }
    return 0;
}

string
ansv_berem()
{
    if (!check_dragonarmy())
    {
	command("say The dragonarmies seek this gemstone man for some " +
	  "foul purpose I do not know.");
	command("say I just hope they do not get their hands on him.");
    }
    return "";
}

string
ansv_quest()
{
    if (!check_dragonarmy())
    {
	command("say There are many ways you " +
	  "can help the knighthood in these occupied areas.");
	command("say We certainly could do with a small band of loyal " +
	  "warriors fighting the draconians, stinging them where we can.");
	command("say We could also do with some adventurers with a bit of " +
	  "smarts, who could retrieve artifacts of the knighthood that have " +
	  "been stolen from us during the war.");
    }
    return "";
}

string
ansv_arti()
{
    if (!check_dragonarmy())
    {
	command("say Of late, a young knight came to us in search of " +
	  "a family heirloom.");
	command("say It was stolen from the corpse of his brother who " +
	  "had fallen in battle against a powerful dragonarmy officer.");
	command("say He disappeared into Flotsam a few days ago, and " +
	  "we have not heard word from him since.");
	command("say Perhaps you could help him?");
	command("hmm");
        command("say There has also been reports from Vingaard Keep that " +
	  "one of the tombs in the High Clerist Tower has been pillaged.");
	command("say A suit of plate armour of Solamnus was stolen.");
	command("say The retrieval of that would be an inspiring " +
	  "omen for the knighthood.");
    }
    return "";
}

string
ansv_armour()
{
    if (!check_dragonarmy())
    {
	command("say The finest armour ever made if the legends are true.");
	command("say Little is known of the suit's whereabouts, " +
	  "although what little information our intelligence has gathered " +
	  "us has amounted to us finding out that it is well guarded.");
    }
    return "";
}

string
ansv_circle()
{
    if (!check_dragonarmy())
    {
	command("say In most civilised places there are representatives " +
	  "of the noble Knights of Solamnia.");
	command("say They are known as Circles of Knights.");
    }
    return "";
}

int
special_attack(object enemy)
{
    int     attacktype,
    pen,
    att,
    wloc;

    mixed hitres;

    string *hitloc,
    *attack,
    how,
    weapon;


    if (!sizeof(query_weapon(-1)))
	return 0;

    attacktype = random(5);

    hitloc = ({"left arm","right arm","body","left leg","right leg"});

    attack = ({"thrust", "swing"});

    weapon = query_weapon(-1)[0]->query_short();

    if (attacktype == 1)
    {
	pen = 200 + random(200);
	hitres = enemy->hit_me(pen, W_IMPALE, TO, -1);

	wloc = random(5);
	att  = random(2);

	if (hitres[0] <= 0)
	    how = "his " + weapon + " barely missing";
	if(hitres[0] > 0)
	    how = "his " + weapon + " lightly grazing";
	if(hitres[0] > 10)
	    how = "his " + weapon + " slicing a shallow wound in";
	if(hitres[0] > 20)
	    how = "his " + weapon + " cutting a gash across";
	if (hitres[0] > 40)
	    how = "his " + weapon + " cutting a deep gash into";
	if (hitres[0] > 60)
	    how = "his " + weapon + " lethally injuring";

	enemy->catch_msg(QCTNAME(TO) + 
	  " looks at you grimly, then makes a mighty " + attack[att]
	  + " at you, " + how + " your " + hitloc[wloc] + ".\n");

	tell_room(E(TO), QCTNAME(TO) + " looks grimly at " + QCTNAME(enemy)
	  + ", then makes a mighty " + attack[att] + " at "
	  + OBJECTIVE(enemy) + ", " + how + " " + POSSESSIVE(enemy)
	  + " " + hitloc[wloc] + ".\n", ({ enemy, TO }));

	if (enemy->query_hp() <= 0)
	{
	    enemy->do_die(TO);
	}

	return 1;
    }
    return 0;
}

void
return_intro(string who)
{
    if (P(L(who), E(TO)))
	command("introduce myself");
}

void
add_introduced(string who)
{
    set_alarm(2.0, 0.0, &return_intro(who));
}

void
arm_me()
{
    seteuid(getuid(TO));
    clone_object(WEP)->move(TO,1);
    command("wield all");

    clone_object(ARM1)->move(TO,1);
    clone_object(ARM2)->move(TO,1);
    command("wear all");
}

void
calculate_experience(object who)
{
    int xp_base = 50000;

    if(who->test_bit("ansalon", 0, 17))
    {
	who->catch_msg("Nice job, but no experience second time.\n");

	return;
    }

    xp_base -= (who->query_prop(PLAYER_I_FOUND_TAIL) ? 0 : 10000);
    xp_base -= (who->query_prop(PLAYER_I_ANSWER_RIDDLES) ? 0 : 5000);
    xp_base -= (who->query_prop(PLAYER_I_PASS_MAZE) ? 0 : 5000);
    xp_base -= (who->query_prop(PLAYER_I_ENTER_LAIR) ? 0 : 10000);
    who->catch_msg("You feel MUCH more experienced!\n");
    if (who->query_wiz_level())
    {
	who->catch_msg("xp: " + xp_base + "\n");
    }

    who->add_exp(xp_base, 0);
    who->set_bit(0, 17);

    A_QUEST_LOG("quest","Solamnian Armour Quest", who, xp_base);

    return;
}

void
return_give_armour(object from)
{
    object spirit;
    string who, what;

    who = from->query_real_name();

    command("gasp");
    command("say By Huma's ghost! This looks like the plate " +
      "armour of Solamnus that was stolen from the High Clerist " +
      "Tower!");
    command("emote strokes his chin thoughtfully.");
    command("say This will certainly bolster morale within the " +
      "knighthood! We owe you our thanks.");

    calculate_experience(from);

    command("say I had best return this to Vingaard at once!");
    command("emote bows formally, and leaves the room.");
    remove_object();
}

void
give_it_back(object ob, object from)
{
    if (!objectp(ob) || !objectp(from))
	return;
    command("peer " + OB_NAME(from));
    command("say Thank you for this gift, although " +
      "I don't know what you want me to do with it.");
    command("give " + OB_NAME(ob) + " to " + OB_NAME(from));
}

void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);

    if(ob->id("_ansalon_quest_s_armour_"))
    {
	set_alarm(1.0, 0.0, &return_give_armour(from));
	return;
    }

    if(ob->id("longsword"))
    {
	return;
    }
    if(ob->id("boots"))
	return;
    if(ob->id("_sol_armour_"))
	return;

    if (objectp(ob) && objectp(from))
	set_alarm(1.0, 0.0, &give_it_back(ob, from));
    return;
}

