#include <ss_types.h>
#include <macros.h>
#include <stdproperties.h>
#include "/d/Ansalon/common/defs.h"
#include "/d/Ansalon/estwilde/local.h"
#include <wa_types.h>

#define WEP1 WEP + "iron_axe"
#define ARM1 ARMOUR + "chainmail"
#define ARM2 ARMOUR + "leggings"
#define ARM3 ARMOUR + "i_gauntlets"
#define ARM6 ARMOUR + "i_boots"
#define ARM4 ARMOUR + "shield"
#define ARM5 ARMOUR + "horned_helmet"

inherit AM_FILE

void
create_krynn_monster()
{
    if(!IS_CLONE)
	return;

    set_name("hofta");
    add_name("trainer");
    set_living_name("hofta");
    set_title("Greymane, Clan Trainer");
    set_race_name("dwarf");
    set_adj("muscular");
    add_adj("grey-bearded");
    set_gender("G_MALE");
    set_long("This is the dwarven warrior who trains clan " +
      "members the skills needed to survive the rugged lands " +
      "of Estwilde. He looks as gnarled and old as an ancient tree stump, " +
      "but you have no doubt that he could still hack down an " +
      "ogre or two.\n");

    set_stats(({160,119,170,89,89,110}));
    set_hp(query_max_hp());
    set_skill(SS_WEP_AXE, 100);
    set_skill(SS_DEFENCE, 100);
    set_skill(SS_PARRY, 100);
    set_skill(SS_AWARENESS, 80);
    set_skill(SS_BLIND_COMBAT, 100);

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

    set_cact_time(0);
    add_cact("emote roars 'Great Reorx!' in astonishment!");
    add_cact("say curse yas to eternal rust and corrosion!");
    add_cact("emote roars: You doorknob! What ye think yur do'en?");

    trig_new("%w 'introduces' %s","react_to_intro");

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

void
return_intro(string who)
{
    who = L(who);
    if (P(who, E(TO)))
    {
	command("introduce myself");
    }
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

    if(!sizeof(query_weapon(-1)))
	return 0;

    attacktype = random(5);

    hitloc = ({ "left arm", "right arm", "body", "left leg", "right leg"});

    weapon = query_weapon(-1)[0]->query_short();

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
	    how = "burying his " + weapon + "deeply into";
	if (hitres[0] > 60)
	    how = "his " + weapon + " splattering blood everywhere " +
	    "as he almost removes";

	enemy->catch_msg(QCTNAME(TO) + " charges at " +
	  "you in a furious attack, " + how + " your "
	  + hitloc[wloc] + ".\n");

	tell_room(E(TO), QCTNAME(TO) + " charges at " + QCTNAME(enemy)
	  + " in a furious rage, " + how + " " + QCTNAME(enemy) + "'s" +
	  " " + hitloc[wloc] + ".\n", ({enemy,TO}));

	if (enemy->query_hp() <= 0)
	{
	    enemy->do_die(TO);
	}

	return 1;
    }
    return 0;
}

