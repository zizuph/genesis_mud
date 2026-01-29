/* Mercenary guard base file, by Morrigan 11/01 */
/* Adapted from Knight of Solamnia base file by Morrigan, Jan 97 */

#include "/d/Krynn/common/defs.h"
#include "../merc.h"
#include <ss_types.h>
#include <wa_types.h>
#include <stdproperties.h>
#include <macros.h>
#include <filter_funs.h>

inherit M_FILE

inherit "/std/act/domove";
inherit "/std/act/action";

void setup_knight();
void get_me_soul();
void arm_me();
string short_desc();

int level, soul_id;

string *dwarf_adj = ({ "stocky", "stout", "barrel-chested", "short",
  "tall", "gruff", "dour", "muscular", "sturdy" });
string *dwarf_adj2 = ({ "bearded", "grey-bearded", "dark-bearded",
  "thick-bearded", "light-bearded", "curly-bearded", "red-bearded" });
string *human_adj = ({ "stern", "bronze-skinned", "stoic", "tall", "silent",
  "cold", "slender", "muscular", "strong", "black-skinned" });
string *human_adj2 = ({ "square-jawed", "dark-haired", "long-haired",
  "blue-eyed", "dark-eyed", "brown-eyed", "black-eyed", "green-eyed",
  "blond-haired", "red-haired", "grey-haired" });
string *elf_adj = ({ "slender", "pointy-eared", "light-skinned", "pale",
  "quiet", "haughty", "cold", "thin", "dark-eyed", "handsome",
  "fair-skinned", "slight" });
string *elf_adj2 = ({ "chestnut-haired", "light-haired", "brown-haired",
  "red-haired", "bright-eyed", "blue-eyed", "green-eyed", "brown-eyed",
  "thinly-bearded" });
string *dwarf_fadj = ({ "stocky", "stout", "barrel-chested", "gruff",
  "short", "tall", "sturdy", "merry" });
string *dwarf_fadj2 = ({ "dark-haired", "grey-haired", "black-haired",
  "white-haired", "brown-haired", "brown-eyed", "black-eyed", "dark-eyed",
  "dark-haired" });
string *human_fadj = ({ "slender", "long-haired", "black-skinned", "pale", "tall",
  "short", "graceful", "skinny", "proud", "pretty" });
string *human_fadj2 = ({ "blonde-haired", "dark-haired", "red-haired",
  "green-eyed", "auburn-haired", "brown-eyed", "blue-eyed" });
string *elf_fadj = ({ "slender", "graceful", "beautiful", "slim",
  "thin", "quiet", "fair-skinned", "light-skinned", "pale", "long-haired",
  "thoughtful" });
string *elf_fadj2 = ({ "blonde-haired", "dark-haired", "red-haired",
  "green-eyed", "auburn-haired", "brown-eyed", "blue-eyed",
  "chestnut-haired" });

string adj1, adj2, race, gender;

int
query_level()
{
    return level;
}

void
set_level(int i)
{
    level = i;
    setup_knight();
}

string
query_adj(string gen)
{
    if (gen == "female")
    switch(race)
    { 
    case "elf":
    case "half-elf":
    return elf_fadj[random(sizeof(elf_fadj))];
    break;
    case "human":
    return human_fadj[random(sizeof(human_fadj))];
    break;
    case "dwarf":
    return dwarf_fadj[random(sizeof(dwarf_fadj))];
    break;
    }

    if (gen == "male")
    switch(race)
    {
    case "elf":
    case "half-elf":
    return elf_adj[random(sizeof(elf_adj))];
    break;
    case "human":
    return human_adj[random(sizeof(human_adj))];
    break;
    case "dwarf":
    return dwarf_adj[random(sizeof(dwarf_adj))];
    break;
    }
}

string
query_adj2(string gen)
{
    if (gen == "female")
    switch(race)
    {
    case "elf":
    case "half-elf":
    return elf_fadj2[random(sizeof(elf_fadj2))];
    break;
    case "human":
    return human_fadj2[random(sizeof(human_fadj2))];
    break;
    case "dwarf":
    return dwarf_fadj2[random(sizeof(dwarf_fadj2))];
    break;
    }

    if (gen == "male")
    switch(race)
    {
    case "elf":
    case "half-elf":
    return elf_adj2[random(sizeof(elf_adj2))];
    break;
    case "human":
    return human_adj2[random(sizeof(human_adj2))];
    break;
    case "dwarf":
    return dwarf_adj2[random(sizeof(dwarf_adj2))];
    break;
    }
}

void
create_knight_npc()
{
    if (!level)
    set_level(random(4));
}

void
setup_knight()
{
    int i;

    switch(random(100) + 1)
    {
    case 1..80:
    race = "human";
    break;
    case 81..83:
    race = "dwarf";
    break;
    case 84..97:
    race = "half-elf";
    break;
    case 98..100:
    race = "elf";
    break;
    }

    switch(random(100) + 1)
    {
    case 1..80:
    gender = "male";
    break;
    case 81..100:
    gender = "female";
    break;
    }

    if (level == 2)
    set_race_name(race);
    add_name(race);
    set_gender(gender == "female" ? 1 : 0);
    set_alignment(50 - random(60));
    adj1 = query_adj(gender);
    adj2 = query_adj2(gender);
    set_adj(({ adj1 }));

    set_short(short_desc());

    for(i = 0; i < 6; i++)
	set_base_stat(i, 100 + (5 * level));

    set_skill(SS_WEP_CLUB,     60 + random(6 * level));
    set_skill(SS_DEFENCE,      50 + random(6 * level));
    set_skill(SS_PARRY,        50 + random(6 * level));
    set_skill(SS_WEP_SWORD,    60 + random(6 * level));
    set_skill(SS_AWARENESS,    30);
    set_skill(SS_HUNTING,      30 + random(20));
    set_skill(SS_MERC_TACTICS,     60 + random(8 * level));
}

void
create_krynn_monster()
{
    set_name("mercenary");
    add_name("guard");
    add_name("_mercenary_renegade_");
    create_knight_npc();
    seteuid(getuid(TO));
    set_act_time(10);
    add_act("@@emotes");
    set_cact_time(10);
    add_prop(LIVE_I_NEVERKNOWN, 1);
    add_prop(MERC_S_DEFAULT_HAIL, "Hail in the name of Draysen the Warlord!");
    add_prop(MERC_S_DEFAULT_BATTLECRY, "Victory to Draysen the Warlord!");

    set_monster_home(MERC_CAMP + "center");
    set_restrain_path(MERC_CAMP);
    set_random_move(20);

    soul_id = set_alarm(0.5, 0.0, &get_me_soul());
    set_alarm(1.0, 0.0, arm_me);
}

void
get_me_soul()
{
    add_cmdsoul(MDIR + "merc_soul");
    update_hooks();
    remove_alarm(soul_id);
}

string
short_desc()
{
    return adj1+" "+adj2+" "+gender+" "+race;
}

string query_guild_name_occ() { return "Mercenaries"; }

void
arm_me()
{
    clone_object(MOBJ+"helm")->move(TO);
    clone_object(MOBJ+"gauntlets")->move(TO);
    clone_object(MOBJ + "armour")->move(TO);
    clone_object(MOBJ + "shield")->move(TO);
    if (random(3))
        clone_object(MOBJ+"sword")->move(TO);
       else
	clone_object(MOBJ+"club")->move(TO);
    command("wear all");
    command("wield all");
}

public void assist_other(object ob)
{
    command("kill "+ob->query_name());
}

public void get_assistance(object ob)
{
    object *livings = FILTER_LIVE(all_inventory(environment(this_object())));
    int i;

    for (i=0;i<sizeof(livings);i++)
	if (livings[i]->id("_mercenary_renegade_") && !livings[i]->query_attack())
	    livings[i]->assist_other(this_object()->query_attack());
}
    
void
attacked_by(object ob)
{
    get_assistance(TO);

    if (!ob->query_prop(PLAYER_I_ATTACK_MERC_CAMP))
	ob->add_prop(PLAYER_I_ATTACK_MERC_CAMP, 1);

    ::attacked_by(ob);
}

void
attack_object(object ob)
{
    get_assistance(TO);

    ::attack_object(ob);
}

void
emotes()
{
    if (!random(2))
	return;

    if (environment(this_object()) == find_object(MLIB + "library"))
	return;

    switch (random(12))
    {
    case 0:
    command("mdestiny");
    break;
    case 1:
    command("mtomorrow");
    break;
    case 2:
    command("mclean weapon");
    break;
    case 3:
    command("minspect weapon");
    break;
    case 4:
        switch (random(10))
        {
		case 0:
                command("say We will soon have enough numbers to rival "+
			"Maligant's mercenaries.");
		break;
		case 1:
		command("say It will be interesting to see what Draysen "+
			"decides to do.");
		break;
		case 2:
		command("say What will we do if Maligant attacks now?");
		break;	
		case 3:
		command("say Soon we will have the numbers to defend "+
			"ourselves if Maligant attacks!");
		break;
		case 4:
		command("say I look forward to a day when we are strong "+
			"enough to invade Maligant's camp!");
		break;
		case 5:
		command("say I'm just here for the fight, I don't care "+
			"about the reason.");
		break;
		case 6:
		command("say Draysen or Maligant, it makes no difference "+
			"to me as long as I am paid well.");
		break;
		case 7:
		command("say I hope we leave soon, before Maligant attacks.");
		break;
		case 8:
		command("say Have you heard any rumours of attacks?");
		break;
		case 9:
		command("say Let him come, I have something for him!");
		break;
	}
    break;
    case 5:
    command("emote swears loyalty to Draysen the Warlord.");
    break;
    case 6:
    command("mclean armour");
    break;
    case 7:
    command("msuggest");
    break;
    case 8:
    command("minspect shield");
    default:
    command("mhail everyone");
    }
}


int
special_attack(object enemy)
{
    if (!random(15))
	command("mkill");

    if (!random(5))
    command("mattack");
    return 0;
}

public object
query_my_shield()
{
    object *worn_armours;
    object shield;
    int i;

    worn_armours = this_object()->query_armour(-1);

    for (i = 0; i < sizeof(worn_armours); i++)
    {
	if (worn_armours[i]->query_at() == A_SHIELD)
	    shield = worn_armours[i];
    }

    return shield;
}

int query_not_attack_me(object who, int aid)
{
    object combat_object = who->query_combat_object();
    int attack = combat_object->query_attack(aid);
    object shield;

//    get_assistance(this_object());

    if (!attack)
        return ::query_not_attack_me(who, aid);

    if (!(shield = query_my_shield()))
    {
        return ::query_not_attack_me(who, aid);
    }

    if (!random(5))
    {
	who->catch_msg("The "+this_object()->short()+" blocks your "+
	    "attack with "+POSSESSIVE(this_object())+" "+shield->short()+".\n");
	this_object()->tell_watcher(this_object()->short()+" blocks "+
	    QTNAME(who)+"'s attack with "+POSSESSIVE(this_object())+
	    " "+shield->short()+".\n", 
	    ({ who, this_object() }));
	return 1;
    }
            
    return ::query_not_attack_me(who, aid);
}

void init_living()
{
    get_assistance(TO);

    ::init_living();
}
