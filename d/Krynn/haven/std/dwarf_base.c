/* 2017-05-20 Malus modified adj_list2, e.g. long bearded to long-bearded */
#include "/d/Krynn/common/defs.h"
#include <ss_types.h>
#include <wa_types.h>
#include <stdproperties.h>
#include <macros.h>
#include <filter_funs.h>
#include <money.h>
#include "/d/Krynn/haven/local.h"

inherit M_FILE

inherit "/std/act/domove";
inherit "/std/act/action";
inherit "/lib/unique";

#define I_HAVE_MONEY "_i_have_money"
#define I_KILLED_DWARVES "_i_killed_dwarves"

void setup_dwarf();
int i, level;
string *adj_list = ({ "stocky", "tall", "short", "heavy", "gruff", "stern",
  "broad-shouldered", "barrel-chested", "grumbling", "merry", "stout", 
  "hefty", "solemn", "muscular", "short-legged", "aged", "young", "old" });
string *adj_list2 = ({ "thick-bearded", "thinly-bearded", "grey-bearded", 
  "brown-bearded", "dark-haired", "brown-eyed", "black-bearded", "long-bearded",
  "short-bearded", "curly-bearded", "wavy-bearded" });
string *adj_list2_female = ({ "dark-haired", "brown-haired", "bright-eyed", 
  "dark-eyed", "long-haired", "curly-haired", "wavy-haired", "grey-haired" });
string adj1, adj2;
object weapon;

int
query_level()
{
    return level;
}

void
set_level(int i)
{
    level = i;
    setup_dwarf();
}

int
check_aggressive()
{
    return TP->query_prop(I_KILLED_DWARVES);
}

void
create_dwarf_npc()
{
    if (!level)
	set_level(random(5) + 1);
}

void
setup_dwarf()
{
    int i;
    set_base_stat(0, 80 + (query_level() * 5 / 2) +
                     random(query_level() * 5) /2);
    set_base_stat(1, 80 + (query_level() * 5));
    set_base_stat(2, 80 + (query_level() * 5 / 2) +
      random(query_level() * 5) /2);
    set_base_stat(3, 80 + (query_level() * 5));
    set_base_stat(4, 80 + (query_level() * 5));
    set_base_stat(5, 80 + (query_level() * 5 / 2) +
      random(query_level() * 5) /2);
    set_skill(SS_WEP_AXE, 40 + random(6 * level));
    set_skill(SS_WEP_CLUB, 40 + random(6 * level));
    set_skill(SS_DEFENCE, 40 + random(5 * level));
    set_skill(SS_PARRY, 30 + random(4 * level));
    set_skill(SS_WEP_SWORD, 40 + random(5 * level));
    set_skill(SS_AWARENESS, 30 + random(4 * level));
    set_skill(SS_BLIND_COMBAT, 10 + random(3 * level));
    set_skill(SS_UNARM_COMBAT, 10 + random(3 * level));
}

void
create_krynn_monster()
{
    int gen;
    if (!random(10))
	gen = 1;
    else
	gen = 0;

    set_name("dwarf");
    set_race_name("dwarf");
    set_alignment(random(400));
    set_gender(gen);
    adj1 = adj_list[random(sizeof(adj_list))];
    if (gen == 1)
	adj2 = adj_list2_female[random(sizeof(adj_list2_female))];
    else
	adj2 = adj_list2[random(sizeof(adj_list2))];

    set_adj(({ adj1, adj2 }));
    set_long("@@long_desc");
    set_short("@@short_desc");

    set_act_time(15);
    add_act("grumble");
    add_act("emote goes 'hmph!'.");
    add_act("say I'm sick of waitin' for those blasted Seekers to shut up so "+
      "we can trade!");
    add_act("say Some of 'em ain't too bad, them Seekers. Some of 'em, I'd just "+
      "as soon shave my beard as listen to, though.");
    add_act("emote inspects "+POSSESSIVE(TO)+" armour closely.");
    add_act("emote plops down on the ground, mumbling about something.");
    add_act("mumble something about the Seekers.");
    add_act("emote looks northeast towards Haven.");
    add_act("emote kicks at the dirt, apparently bored.");
    add_act("say It sure made me laugh when that human merchant in Solace told "+
      "us that the pass through Twin Peaks was too rough! Maybe for humans.");
    add_act("say Nothing like good dwarven armour and weapons! Don't ya think?");
    add_act("say I plan to get a lot off these Haven folk. Judging from the "+
      "looks of their lousy armour and weapons, I should have no trouble.");
    add_act("fume");
    add_act("twiddle");

    add_prop(LIVE_I_NEVERKNOWN, 1);
    add_prop(NPC_I_NO_LOOKS, 1);
    set_aggressive(VBFC_ME("check_aggressive"));
    create_dwarf_npc();

    seteuid(getuid(TO));
    set_alarm(0.5, 0.0, "arm_me");
}

int
weapon_comment(object ob)
{
    object *wep;

    wep = ob->query_weapon(-1);

    if (!sizeof(wep))
    {
	TO->command("say Look at this "+ob->query_race_name()+"! "+
	  (ob->query_gender() == 1 ? "She" : "He")+" doesn't even have "+
	  "the sense to use a weapon!");
	return 1;
    }

    if ((wep[0]->query_hit() + wep[0]->query_pen()) / 2 > 30)
    {
	TO->command("say Nice "+wep[0]->short()+" ya got there, "+ob->query_race_name()+
	  ". Must be dwarven.");
	TO->command("think");
	return 1;
    }

    TO->command("say I think the only thing more pathetic than that "+wep[0]->short()+
      " you're holding, is you, ya dumb "+ob->query_race_name()+"!");
    TO->command("snicker");
    return 1;
}

int
armour_comment(object ob)
{
    object *arm;

    arm = ob->query_armour(-1);

    if (!sizeof(arm))
    {
	TO->command("say Look at this "+ob->query_race_name()+"! "+
	  (ob->query_gender() == 1 ? "She" : "He")+" doesn't even have "+
	  "the sense to wear any armour!");
	return 1;
    }

    if (arm[0]->query_ac() > 30)
    {
	TO->command("say Nice "+arm[0]->short()+" ya got there, "+ob->query_race_name()+
	  ". Must be dwarven.");
	TO->command("think");
	return 1;
    }

    TO->command("say I think the only thing more pathetic than that "+arm[0]->short()+
      " you're wearing, is you, ya dumb "+ob->query_race_name()+"!");
    TO->command("snicker");
    return 1;
}

void
attacked_by(object ob)
{
    if (!ob->query_prop(I_KILLED_DWARVES))
	ob->add_prop(I_KILLED_DWARVES, 1);
    switch(random(5) + 1)
    {
    case 5:
	TO->command("shout Great Reorx!");
	break;
    case 4:
	TO->command("emote shakes " +POSSESSIVE(TO)+ " head at this " +
          "foolish " + ob->query_race_name() + ".");
	break;
    case 3:
	TO->command("emote sets " +POSSESSIVE(TO)+ " feet firmly on " +
          "the ground, getting " +POSSESSIVE(TO)+ " balance.");
	break;
    case 2:
	weapon_comment(ob);
	break;
    case 1:
	armour_comment(ob);
	break;
    }

    if (weapon)
    {
	if (E(weapon) != TO)
	    TO->command("emote searches frantically for "+POSSESSIVE(TO)+
	      " weapon, but cannot find it!");
	else if (weapon->query_wielded() != TO)
	    TO->command("emote confidently reaches for "+POSSESSIVE(TO)+" "+
	      weapon->short()+".");
	TO->command("wield "+weapon->query_name());
    }

    ::attacked_by(ob);
}

void
attack_object(object ob)
{
    if (weapon)
    {
	if (E(weapon) != TO)
	    TO->command("emote searches frantically for "+POSSESSIVE(TO)+
	      " weapon, but cannot find it!");
	else if (weapon->query_wielded() != TO)
	    TO->command("emote confidently reaches for "+POSSESSIVE(TO)+" "+
	      weapon->short()+".");
	TO->command("wield "+weapon->query_name());
    }

    ::attack_object(ob);
}

void
arm_me()
{

    if (!TO->query_prop(I_HAVE_MONEY))
    {
	TO->add_prop(I_HAVE_MONEY, 1);
	MONEY_MAKE_GC(random(query_level()) + query_level())->move(TO);
	MONEY_MAKE_SC(random(3 * query_level()) + 3 * query_level())->move(TO);
    }

    switch(random(10) + 1)
    {
    case 10:
	weapon = clone_object(DWEP + "sword");
	weapon->move(TO);
	break;
    case 1..3:
	weapon = clone_object(DWEP + "waraxe");
	weapon->move(TO);
	break;
    case 4..5:
	weapon = clone_object(DWEP + "battleaxe");
	weapon->move(TO);
	break;
    case 6..8:
	weapon = clone_object(DWEP + "mace");
	weapon->move(TO);
	break;
    default:
	weapon = clone_object(DWEP + "warhammer");
	weapon->move(TO);
	break;
    }

    if (TO->query_name() == "Colin")
    {
	weapon->remove_object();
	weapon = clone_unique(KRWEAPON + "war-mace", 7, 
	    DWEP + "mithril_hammer");
	weapon->move(TO);
	
	if ( weapon->id("war-mace") )
	    clone_unique(KRARMOUR + "kite-shield", 7, DARM + "shield")->move(TO);
	        
    }

    if (random(5))
	clone_object(DARM + "helm")->move(TO);

    if (weapon->query_hands() == 0)
    {
        clone_object(DARM + "shield")->move(TO);

    }
    
    if (!random(3))
	clone_object(DARM + "chainmail")->move(TO);
    else
	clone_object(DARM + "leather_armour")->move(TO);

    clone_object(DARM + "boots")->move(TO);

    command("wield all");
    command("wear all");
}

string
long_desc()
{
    return "This "+short()+" is a member of the small encampment of dwarves "+
    "here to trade with Haven from the south.\n";
}

string
short_desc()
{
    return adj1 + " "+ adj2 + (query_gender() == 1 ? " female" : " male") +
    " dwarf";
}

string
query_damage_desc(int hit)
{
    string *dam;

    switch (weapon->query_wt())
    {
    case W_SWORD:
	dam = ({ "completely missing", "barely nicking", "stabbing "+
	  "the point into", "driving the blade into", "burying the "+
	  "blade deeply into", "impaling"});
	break;
    case W_AXE:
	dam = ({ "completely missing", "barely cutting", "slicing "+
	  "into", "slashing into", "tearing deeply into", "ripping "+
	  "a gaping wound in" });
	break;
    case W_CLUB:
	dam = ({ "completely missing", "barely hitting", "striking",
	  "hurting", "mightily pounding", "crushing" });
	break;
    }

    switch (hit)
    {
    case 0:
	return dam[0];
	break;
    case 1..5:
	return dam[1];
	break;
    case 6..10:
	return dam[2];
	break;
    case 11..25:
	return dam[3];
	break;
    case 26..40:
	return dam[4];
	break;
    default:
	return dam[5];
	break;
    }
}

int
special_attack(object enemy)
{
    mixed* hitresult;
    object me = TO;
    int dt = weapon->query_dt();
    string dam_desc;
    int penet;

    if (random(3))
	return 0;

    if (weapon->query_wielded() == TO && random(3))
    {

	penet = TO->query_stat(SS_STR) + query_skill(weapon->query_wt())+
	(TO->query_level() + 5) * 10;

	hitresult = enemy->hit_me(penet, dt, me, -1);

	dam_desc = query_damage_desc(hitresult[0]);

	enemy->catch_msg(TO->query_The_name(enemy)+" swings hard with "+
	  POSSESSIVE(TO)+" "+weapon->short()+", "+dam_desc+" your "+
	  hitresult[1]+".\n");
	tell_watcher(QCTNAME(TO)+" swings hard with "+POSSESSIVE(TO)+
	  " "+weapon->short()+", "+dam_desc+" "+QTNAME(enemy)+"'s "+
	  hitresult[1]+"\n", enemy);

	if (enemy->query_hp() <= 0)
	    enemy->do_die(me);
	return 1;
    }  

    penet = TO->query_stat(SS_STR) + random(TO->query_stat(SS_STR));
    hitresult = enemy->hit_me(penet, W_BLUDGEON, me, -1);
    enemy->catch_msg(TO->query_The_name(enemy)+" headbutts you hard, making "+
      "you see stars.\n");
    tell_watcher(QCTNAME(TO)+" headbutts "+QTNAME(enemy)+" hard, who looks "+
      "a little dazed.\n", enemy);

    return 1;
}
