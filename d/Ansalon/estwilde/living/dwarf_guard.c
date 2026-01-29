// Edited March 29 2006 by Navarre. Set limit on unlimited boars. 
// Logg abused this be reentering the room, making the players
// keep switching target, summoning more and more boars.
// This lead to this change.

/*
 * Louie April 2006 - Fixed minor bug that kept goblin enemies 
 * from being attacked.
 */

/*
 * Navarre December 18th 2007,
 * Added report mechanism for neidars to query their guards for
 * descriptions of encounted players that are non neidar, and non wizards.
 */
#include <ss_types.h>
#include <macros.h>
#include <stdproperties.h>
#include "/d/Ansalon/common/defs.h"
#include "../local.h"
#include <wa_types.h>

#define WEP1 WEP + "iron_axe"
#define ARM1 ARMOUR + "chainmail"
#define ARM2 ARMOUR + "leggings"
#define ARM3 ARMOUR + "i_gauntlets"
#define ARM6 ARMOUR + "i_boots"
#define ARM4 ARMOUR + "shield"
#define ARM5 ARMOUR + "horned_helmet"

inherit AM_FILE
inherit AUTO_TEAM

string *gAdj1 = ({"grumpy","gruff","scarred","jovial",
  "stout","old","young","gnarled"});
string *gAdj2 = ({"black-bearded","fork-bearded","red-bearded",
  "brown-bearded","long-bearded","grey-bearded"});

int summoned_boars = 0;

#ifndef ONE_OF
#define ONE_OF(x) (x[random(sizeof(x))])
#endif

#ifndef ADMIN
#define ADMIN "/d/Ansalon/guild/dwarf/admin"
#endif

// Prototype
string give_report();

void
create_krynn_monster()
{
    if(!IS_CLONE)
	return;

    set_pick_up_team(({"dwarf","boar"}));
    set_max_team_size_auto_join(6);
    set_race_name("dwarf");
    set_name("clan_guard");
    set_adj(ONE_OF(gAdj1));
    add_adj(ONE_OF(gAdj2));
    set_gender("G_MALE");
    set_long("This is dwarven warrior of Iron Delving. He " +
      "looks like he is prepared for anything, and does not " +
      "look like the type of person to shy away from a fight.\n");

    set_stats(({200,119,240,89,89,110}));
    set_hp(query_max_hp());
    set_skill(SS_WEP_AXE, 100);
    set_skill(SS_DEFENCE, 100);
    set_skill(SS_PARRY, 100);
    set_skill(SS_AWARENESS, 80);
    set_skill(SS_BLIND_COMBAT, 100);

    add_prop(LIVE_I_NEVERKNOWN, 1);
    add_prop(LIVE_I_SEE_DARK, 10);
    add_prop(OBJ_I_RES_MAGIC, 50);
    add_prop(OBJ_I_RES_POISON, 70);

    set_alignment(100);
    set_knight_prestige(-1);

    set_default_answer("The dwarf looks at you funnily, as if " +
      "you should already know the answer to that.\n");

    set_act_time(5);
    add_act("emote stretches his gnarled hands before him.");
    add_act("emote curses the Mountain dwarves to eternal rust " +
      "and corrosion.");
    add_act("emote grumbles about the weather.");
    add_act("emote strokes his greying beard lovingly.");

    set_cact_time(5);
    add_cact("assist");
    add_cact("assist dwarf");
    add_cact("emote roars 'Great Reorx!' in astonishment!");
    add_cact("say curse yas to eternal rust and corrosion!");
    add_cact("emote roars: You doorknob! What ye think yur do'en?");
    add_ask(({"report", "reports", "encounters"}), give_report);

}

void
arm_me()
{
    seteuid(getuid(TO));
    clone_object(WEP1)->move(TO,1);
    clone_object(ARM1)->move(TO);
    clone_object(ARM2)->move(TO,1);
    clone_object(ARM3)->move(TO,1);
    clone_object(ARM4)->move(TO,1);
    clone_object(ARM5)->move(TO,1);
    clone_object(ARM6)->move(TO,1);
    command("wield all");
    command("wear all");
}


void
react_to_intro(string who, string garbage)
{
    set_alarm(2.0,0.0,"return_intro",who);
}



int
special_attack(object enemy)
{
    int   attacktype,
    pen,
    wloc;

    mixed hitres;

    string *hitloc,
    how,
    weapon;

    object enemy_weapon;
    string wep_string;

    if(!sizeof(query_weapon(-1)))
	return 0;

    attacktype = random(5);

    hitloc = ({ "left arm", "right arm", "body", "left leg", "right leg"});

    weapon = query_weapon(-1)[0]->query_short();
    if(sizeof(enemy->query_weapon(-1)))
    {
	enemy_weapon = enemy->query_weapon(-1)[0];
	wep_string = enemy->query_weapon(-1)[0]->query_short();
    }

    if(attacktype == 0)
    {
	if(enemy->query_weapon(-1) && !enemy->query_npc())
	{
	    enemy->catch_msg(QCTNAME(TO) + " takes a mighty swing at " +
	      "your " +wep_string+ ", hitting it with " +HIS(TO)+ " " +weapon+ "!\n");
	    tell_room(E(TO), QCTNAME(TO) + " takes a mighty swing at " +
	      QTNAME(enemy)+ "'s " +wep_string+ ", hitting it with " +
	      HIS(TO)+ " " +weapon+ "!\n", ({enemy, TO}));

	    if ( enemy->query_npc() )
		return 1;

	    enemy_weapon->remove_broken();
	    return 1;
	}
	return 1;
    }

    if (attacktype == 1)
    {
	pen = 350 + random(200);

	hitres = enemy->hit_me(pen, W_SLASH, TO, -1);

	wloc = random(5);

	if (hitres[0] <= 0)
	    how = "his " + weapon + " just missing";
	if (hitres[0] > 0)
	    how = "his " + weapon + " grazing the skin of";
	if (hitres[0] > 10)
	    how = "slicing his " + weapon + " deeply into";
	if (hitres[0] > 20)
	    how = "his " + weapon + " deeply penetrating";
	if (hitres[0] > 40)
	    how = "burying his " +weapon+ " deeply into";
	if (hitres[0] > 60)
	    how = "his " + weapon + " splattering blood everywhere " +
	    "as he almost removes";

	enemy->catch_msg(QCTNAME(TO) + " charges at " +
	  "you in a furious attack, " + how + " your "
	  + hitloc[wloc] + ".\n");

	tell_room(E(TO), QCTNAME(TO)+ " charges at "+ QTNAME(enemy)
	  + " in a furious rage, " +how+ " " +QTNAME(enemy)+ "'s" +
	  " " + hitloc[wloc] + ".\n", ({enemy,TO}));

	if (enemy->query_hp() <= 0)
	{
	    enemy->do_die(TO);
	}

	return 1;
    }
    return 0;
}

void
attack_func(object enemy)
{
    object rg1, rg2;

    if(!CAN_SEE(TO, enemy))
    {

	enemy->catch_msg(QCTNAME(TO)+ " is oblivious to your presence.\n");
	return;
    }
    command("shout Scum! Die ye bastard!");
    command("kill " +enemy->query_real_name());
    command("blow horn");
    if(!enemy->query_npc() && enemy->query_average_stat() > 130)
    {
        if(!summoned_boars)
        {
            command("say This one ain't small! Call the pigs in!");
	    tell_room(E(TO),"Two massive war boars charge in, answering the call to battle!\n");
            rg1 = clone_object(LIVING + "warboar");
	    rg1->move(E(TO),1);
	    rg1->command("kill " +enemy->query_real_name());
	    rg2 = clone_object(LIVING + "warboar");
	    rg2->move(E(TO),1);
            rg2->command("kill " +enemy->query_real_name());
	    rg1->initial_attack(enemy);
            summoned_boars = 1;
        }
    }
}

void
attack_gobbo(object enemy)
{
    if(!CAN_SEE(TO, enemy))
    {
	enemy->catch_msg(QCTNAME(TO)+ " is oblivious to your presence.\n");
	return;
    }
    command("growl");
    command("say Get out of here gobbo! Before I split yur skull!");
}

void
attacked_by(object ob)
{
    object rg1, rg2;

    ob->add_prop(DWARF_ENEMY, 1);
    command("say Attackers! Summon the clan!");
    command("blow horn");
    if(!ob->query_npc() && ob->query_average_stat() > 130)
    {
        if(!summoned_boars)
        {
          command("say This ones a toughy! Summon the war boars!");
	  tell_room(E(TO),"Two massive war boars charge in, answering the call to battle!\n");
	  rg1 = clone_object(LIVING + "warboar");
	  rg1->move(E(TO),1);
	  rg1->command("kill " +ob->query_real_name());
	  rg2 = clone_object(LIVING + "warboar");
	  rg2->move(E(TO),1);
	  rg2->command("kill " +ob->query_real_name());
	  rg1->initial_attack(ob);
          summoned_boars = 1;
        }
    }
    ::attacked_by(ob);
}

void
greet_func(object enemy)
{
    if(!CAN_SEE(TO, enemy))
    {
	enemy->catch_msg(QCTNAME(TO)+ " is oblivious to your presence.\n");
	return;
    }
    if(random(3) == 1)
    {
	if(random(2) == 1)
	{
	    command("say to " +enemy->query_real_name() + " Greetins to ya!");
	    command("emote raises his iron battleaxe in greetings.");
	}
	else
	{
	    command("emote raises his iron battleaxe, saying: " +
	      "Axes high friend!");
	    command("smile dwarvish " +enemy->query_real_name());
	}
    }
}

void
init_living()
{
    if (TP->query_prop(DWARF_ENEMY)) {
        set_alarm(0.5, 0.0, "attack_func", TP);
    }
 
    if(TP->query_race_name() == "goblin" ||
       TP->query_race_name() == "hobgoblin")
    {
        if (TP->query_npc()) {
          set_alarm(0.5, 0.0, "attack_func", TP);
        }
        else {
          set_alarm(0.5, 0.0, "attack_gobbo", TP);
        }
    }
 
    if(TP->query_guild_member("Dwarven Warriors of the Neidar Clan") ||
       TP->query_race_name() == "dwarf" || P("ansalon_rune_object", TP) )
    {
	set_alarm(0.5, 0.0, "greet_func", TP);
    }
    init_team_pickup();

    if(!TP->query_wiz_level() && interactive(TP) && !(TP->query_guild_member("Dwarven Warriors of the Neidar Clan")))
    {
        ADMIN->report_encounter(capitalize(LANG_ADDART(TP->query_nonmet_name())));
    }
    ::init_living();
}

string give_report()
{
    string encounter_report = ADMIN->query_encounter_report();

    if(strlen(encounter_report) > 0 &&
       (TP->query_guild_member("Dwarven Warriors of the Neidar Clan") ||
        TP->query_wiz_level()))
    {
        TP->catch_msg(QCTNAME(this_object())+" shows you "+HIS(this_object())+" report.\n");
        tell_room(environment(this_object()), QCTNAME(this_object())+" shows something to " +QCTNAME(TP)+ ".\n", TP); 
        TP->catch_tell(ADMIN->query_encounter_report());
        return "";
    }
    command("say Nothing to report!");
    return "";
}
