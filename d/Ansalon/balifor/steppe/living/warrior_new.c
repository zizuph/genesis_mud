#include <stdproperties.h>
#include <wa_types.h>
#include <ss_types.h>
#include <macros.h>
#include "/d/Ansalon/common/defs.h"
#include "/d/Ansalon/balifor/steppe/local.h"

inherit AM_FILE
inherit "/lib/unique";

#define ADMIN     "/d/Krynn/solamn/vin/knight/admin/admin.c"

#define WEP  SOBJ + "longsword"
#define WEP2 "/d/Ansalon/common/wep/sword/longsword3"
#define ARM1 SOBJ + "chainmail"
#define ARM2 SOBJ + "helmet"
#define ARM3 SOBJ + "cloak"
#define ARM4 SOBJ + "shield"
#define PLAYER_KILLED_VIRIDIAN "_player_killed_viridian"
#define PLAYER_ATTACKED_VIRIDIAN_WITH_SPELLS "_player_attacked_viridian_with_spells"


void
create_krynn_monster()
{
    if(!IS_CLONE)
	return;

    set_name("viridian");
    set_living_name("viridian");
    set_title("Swordsmaster of Valkinord");
    set_race_name("human");
    set_adj("old");
    add_adj("sharp-eyed");
    set_gender("G_MALE");
    set_long("Before you stands an old rugged looking male " +
      "human. He looks like he has been travelling for quite " +
      "some time. Still, he is no ordinary traveller. His eyes " +
      "are sharp, missing nothing, and his hand rests comfortably " +
      "on the hilt of his sword.\nHe wears the insignia " +
      "of the crimson kestrel, the mark of a swordsmaster " +
      "of the realms.\n");

    set_stats(({185, 150, 180, 140, 130, 100}));
    set_hp(query_max_hp());

    add_prop(CONT_I_WEIGHT, 60000);
    add_prop(CONT_I_HEIGHT, 185);

    set_skill(SS_WEP_SWORD, 100);
    set_skill(SS_DEFENCE, 100);
    set_skill(SS_PARRY, 100);
    set_skill(SS_BLIND_COMBAT, 90);
    set_skill(SS_AWARENESS, 80);
    add_prop("_ranger_m_not_disarm",1);

    set_alignment(500);
    set_knight_prestige(-3);
    set_act_time(6);
    add_act("emote scans the area with seasoned eyes, " +
      "searching for danger.");
    add_act("emote crosses his arms, supremely confident " +
      "in his abilities with his blade.");
    add_act("emote pokes the campfire with a stick.");
    add_act("say Ah Valkinord! If that fine city had not been " +
      "burned to the ground by the dragonarmies, I would still " +
      "be there.");

    add_ask(({"quest","task"}),"say I have neither grand quest " +
      "nor small task for you to do. If you consider yourself " +
      "a swordsman worthy of my attention though, you may " +
      "like to display your sword skill before me.",1);
    add_ask("valkinord","say The city I come from, up on the " +
      "coastland of Nordmaar. The dragonarmies burnt it to the " +
      "ground, curse those fiends!",1);
    add_ask(({"insignia","insignia of the crimson kestrel",
	"crimson kestrel","kestrel"}),"say The insignia of " +
      "the crimson kestrel has long been the mark of all those " +
      "who are masters of the blade.",1);
    add_ask("talisman","say You come from the shaman of " +
      "the glades? Yes, he gave " +
      "me a talisman that would protect me from the wyverns poison. " +
      "Alas! I lost it when Flotsam was attacked by the " +
      "cursed dragonarmies! It would be there if you seek " +
      "it, buried in the destruction most likely.",1);
}

init_living()
{
    add_action("display_sword","display");
}


int
wielding_f_sword(object who)
{
    object *wielded_weapons;

    wielded_weapons = who->query_weapon(-1);

    if(!sizeof(wielded_weapons))
    {
	return 0;
    }

    if(wielded_weapons[0]->id("sword"))
    {
	return 1;
    }

    return 0;
}
int
display_sword(string str)
{
    if (str != "sword skill")
    {
	NF("Display what? Sword skill???\n");
	return 0;
    }

    if(!wielding_f_sword(TP))
    {
	NF("You don't have a sword to display your sword skill with.\n");
	return 0;
    }

    if(TP->query_prop(PLAYER_KILLED_VIRIDIAN))
    {
	TO->command("say To earn the crimson kestrel and be truly a master "+
	  "swordsman, one must have control and respect.");
	TO->command("say You have neither! Begone!");
	return 1;
    }

    if (TP->query_skill(SS_WEP_SWORD) > 80)
    {
	write("You display your ability with a sword, exhibiting " +
	  "graceful spins and powerful lunges with the blade.\n");
	say(QCTNAME(TP) + " displays " + POSSESSIVE(TP) +
	  " ability with a sword, exhibiting graceful spins and " +
	  "powerful lunges with the blade.\n");
	command("emote nods his head approvingly.");
	command("say Indeed you are a master with the blade!");
	if (P("ansalon_sword_object",TP))
	{
	    command("say You already have an insignia marking you " +
	      "as a master with the blades, so there is no point " +
	      "in me giving you another one.");
	    return 1;
	}
	command("smile warm");
	command("It is my place to award you with the insignia " +
	  "of the crimson kestrel, the mark worn by the greatest " +
	  "swordsmen and women in the Realms. Congratulations!");
	write("You have been awarded the crimson kestrel insignia " +
	  "by Viridian, Swordsmaster of Valkinord! Wear it with " +
	  "pride.\n");
	say(QCTNAME(TP) + " has been awarded the crimson kestrel " +
	  "insignia by Viridian, Swordsmaster of Valkinord!\n");
	clone_object(SOBJ + "insignia")->move(TP);
	return 1;
    }
    write("While under the watchful eyes of the swordsmaster, " +
      "you jab and swing your sword wildly, your nervousness " +
      "evident.\n");
    say(QCTNAME(TP) + " jabs and swings " + POSSESSIVE(TP) +
      " sword wildly, " + POSSESSIVE(TP) + " lack of grace " +
      "probably due to being nervous before the swordsmaster.\n");
    command("emote laughs in amusement.");
    command("say You are no swordsmaster.");
    command("emote rubs his chin thoughtfully.");
    command("say Still, you have potential. Come back to " +
      "me when you have improved your skills a bit.");
    command("grin .");
    return 1;
}

void
attacked_by(object ob)
{
    object ash;
    object wound, target;

    ::attacked_by(ob);

    /* A quick fix by Stralle to allow for spellcasters to attack
     * Viridian without him seeing it as being attacked prior to
     * combat
     */
    if (calling_function() == "cast_spell")
    {
	if (ob->query_prop(PLAYER_ATTACKED_VIRIDIAN_WITH_SPELLS) ==
	  OB_NUM(TO))
	    return;
	else
	    ob->add_prop(PLAYER_ATTACKED_VIRIDIAN_WITH_SPELLS, OB_NUM(TO));
    }

    ob->add_prop(PLAYER_KILLED_VIRIDIAN, 1);
    if(P("ansalon_sword_object", ob))
    {
	command("say You certainly don't deserve this!");
	ob->catch_msg(QCTNAME(TO) + " rips your crimson kestrel insignia "+
	  "from you, and throws it in the fire.\n");
	ob->tell_watcher(QCTNAME(TO) + " rips " +QTNAME(ob)+ "'s "+
	  "crimson kestrel insignia off, and tosses it in the fire.\n", ob);
	P("ansalon_sword_object", ob)->remove_object();
    }

    if(ob->test_bit("Krynn", 1, 0)) 
    {
	command("spit");
	command("say Dark days it is when a Knight of Solamnia attacks "+
	  "a refugee of Nordmaar!");
	command("say Take your tainted honour scum! And i'll be taking "+
	  "this!");
	ob->catch_msg(QCTNAME(TO) + " slashes low at you with his "+
	  "blade!  Before you can react, he has wounded you grievously!\n");
	ob->tell_watcher(QCTNAME(TO) + " slashes low at " +QTNAME(ob)+ " with "+
	  "his blade!  Before " +QTNAME(ob)+ " could react, the swordmaster " +
	  "deals " +HIM(ob)+ " a grievous wound, neutering " +HIM(ob)+ "!\n", ob);
	ob->set_gender(G_NEUTER);
        ob->set_hp(ob->query_hp() - 300);
    }
    else
    {
	if(random(2) == 1)
	{
	    ob->catch_msg(QCTNAME(TO)+ " kicks ash into your face! " +
	      "You are blinded by burning coals!\n");
	    TO->tell_watcher(QCTNAME(TO)+ " kicks ash into " +
	      QTNAME(ob)+ "'s face, blinding " +HIM(ob)+ "!\n", ob);
	    ash = clone_object("/d/Ansalon/balifor/steppe/obj/blind_obj");
	    ash->set_time(60);
	    ash->move(ob);
	    command("say A Swordsmaster has many tricks! How " +
	      "does that one feel fool?");
	}
	else
	{
	    ob->catch_msg(QCTNAME(TO)+ " slices a nasty wound along your " +
	      "hamstring, incapacitating your leg!\n");
	    TO->tell_watcher(QCTNAME(TO) + " slices a nasty wound along " +
	      QTNAME(ob)+ "'s hamstring, incapacitating " +HIS(ob)+
	      " leg!\n", ob);
	    wound = clone_object("/d/Ansalon/balifor/steppe/obj/stun_obj");
	    wound->move(ob);
	    command("say Try running away with that wound fool! " +
	      "Prepare to die!");
	}
    }
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
	pen = 400 + random(200);
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
	  " spins his longsword rapidly, then makes a skillful " +
	  attack[att]
	  + " at you, " + how + " your " + hitloc[wloc] + ".\n");

	tell_room(E(TO), QCTNAME(TO) +
	  " spins his longsword rapidly before " + QTNAME(enemy) +
	  ", then makes a skillful " + attack[att] + " at "
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
add_introduced(string who)
{
    object pl = find_player(L(who));
    if (pl && !pl->query_met(TO))
	set_alarm(2.0, 0.0, &command("introduce me"));
}

void
arm_me()
{
    seteuid(getuid(this_object()));
    clone_unique(WEP, 5, WEP2)->move(this_object(),1);
    command("wield all");

    clone_object(ARM1)->move(this_object(),1);
    clone_object(ARM2)->move(this_object(),1);
    clone_object(ARM3)->move(this_object(),1);
    clone_object(ARM4)->move(this_object(),1);
    command("wear all");
}

