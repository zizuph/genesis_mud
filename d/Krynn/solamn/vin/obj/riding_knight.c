/* Knight of Solamnia base file by Morrigan, Jan 97 */
/* 13.4.2000 Modified by Milan, kattack and block skills set to 100 */
/* Modified by Navarre, March 2006, to be a riding knight with cavalry attacks
   and much more. Going to be used for Navarre's island, and warfare system */

#include "/d/Krynn/common/defs.h"
#include "/d/Krynn/solamn/vin/knight/guild.h"
#include <ss_types.h>
#include <wa_types.h>
#include <stdproperties.h>
#include <macros.h>
#include <filter_funs.h>
#include <money.h>
#include "./riding_knight_defs.h"

/* Extra xp given due to extra special (cavalry), extra parry,
   and extra speed.
   To compare rose knights in the warfare system gives 145.
 */
#define EXP_PERCENTAGE 150


inherit M_FILE
inherit "/lib/unique";
inherit AUTO_TEAM

inherit "/std/act/domove";
inherit "/std/act/action";

object shadow; 
object horse;
int charge_alarm_id;
int kdied = 0;

void setup_knight();
void get_me_soul();
string do_rescue();
void arm_me();
string short_desc();
string long_desc();

int level, soul_id;
string *dwarf_adj = ({ "stocky", "stout", "barrel-chested", "short",
  "tall", "gruff", "dour", "muscular", "sturdy" });
string *dwarf_adj2 = ({ "bearded", "grey-bearded", "dark-bearded",
  "thick-bearded", "light-bearded", "curly-bearded", "red-bearded" });
string *human_adj = ({ "stern", "pale", "stoic", "tall", "silent",
  "cold", "noble", "muscular", "proud", "nonchalant" });
string *human_adj2 = ({ "moustachioed", "dark-haired", "long-haired",
  "blue-eyed", "dark-eyed", "brown-eyed", "black-eyed", "green-eyed",
  "blond-haired", "red-haired", "grey-haired" });
string *elf_adj = ({ "slender", "pointy-eared", "light-skinned", "pale",
  "quiet", "sullen", "retrospective", "thin", "dark-eyed", "handsome",
  "fair-skinned", "slight" });
string *elf_adj2 = ({ "chestnut-haired", "light-haired", "brown-haired",
  "red-haired", "bright-eyed", "blue-eyed", "green-eyed", "brown-eyed",
  "thinly-bearded" });
string *dwarf_fadj = ({ "stocky", "stout", "barrel-chested", "gruff",
  "short", "tall", "sturdy", "merry" });
string *dwarf_fadj2 = ({ "dark-haired", "grey-haired", "black-haired",
  "white-haired", "brown-haired", "brown-eyed", "black-eyed", "dark-eyed",
  "dark-haired" });
string *human_fadj = ({ "slender", "long-haired", "noble", "pale", "tall",
  "short", "stern", "stoic", "proud", "pretty" });
string *human_fadj2 = ({ "blonde-haired", "dark-haired", "red-haired",
  "green-eyed", "auburn-haired", "brown-eyed", "blue-eyed" });
string *elf_fadj = ({ "slender", "graceful", "beautiful", "slim",
  "thin", "quiet", "fair-skinned", "light-skinned", "pale", "long-haired",
  "thoughtful" });
string *elf_fadj2 = ({ "blonde-haired", "dark-haired", "red-haired",
  "green-eyed", "auburn-haired", "brown-eyed", "blue-eyed",
  "chestnut-haired" });
string adj1, adj2, race, gender, block_dir;


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

void
set_block_dir(string str)
{
    block_dir = str;
}

string
query_block_dir()
{
    return block_dir;
}

string
query_adj(string gen)
{
    if (gen == "female")
    switch(race)
    {
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
clean_up(object shadow, object horse)
{
  shadow->remove_shadow();
  horse->set_owner(0);
  horse->remove_prop(OBJ_M_NO_ATTACK);
}

// Redefinition of do_die for _all_ npcs inside the Keep to make
// the Knight guards aggressive towards the killer.
void
do_die(object killer)
{
    if(!kdied)
    {
        command("kdie true");
        command("kdie true");
        kdied = 1; 

        return;
    }
    if (!killer->query_prop("_i_attacked_in_vingaard"))
        killer->add_prop("_i_attacked_in_vingaard", 1);
    if (!killer->query_prop(I_WAS_EVIL))
        killer->add_prop(I_WAS_EVIL, 1);
    set_alarm(1.0, 0.0, &clean_up(shadow, horse));
    ::do_die(killer);
}

void
create_knight_npc()
{
  // Rose or Sword knight, orig was: set_level(random(2) + 2)
  // but we don't want squires on horses etc
    if (!level){
        set_level(4+random(2));
    }
    kdied = 0;
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
    case 81..90:
    race = "dwarf";
    break;
    case 91..100:
    race = "half-elf";
    break;
    }

    switch(random(100) + 1)
    {
    case 1..90:
    gender = "male";
    break;
    case 91..100:
    gender = "female";
    break;
    }

/* This one is not used right now, as we dont want squires on the horse.
   I left it here incase someone changes his mind later.

    if (level == 2){
      add_name("squire");
    }
*/
    set_race_name(race);
    set_gender(gender == "female" ? 1 : 0);
    set_alignment(500 + random(5 * level));
    set_knight_prestige(-3 - random(level));
    adj1 = query_adj(gender);
    adj2 = query_adj2(gender);
    set_adj(({ adj1 }));

    set_short(short_desc());
    set_long(long_desc());

    for(i = 0; i < 6; i++)
	set_base_stat(i, 125 + (10 * level) + random(10 * level));

    set_skill(SS_2H_COMBAT,    80 + random(2 * level));
    set_skill(SS_WEP_POLEARM,  70 + random(5 * level));
    set_skill(SS_WEP_CLUB,     80 + random(4 * level));
    set_skill(SS_DEFENCE,      50 + random(5 * level));
    set_skill(SS_PARRY,        50 + random(8 * level));
    set_skill(SS_WEP_SWORD,    70 + random(6 * level));
    set_skill(SS_AWARENESS,    60 + random(3 * level));
    set_skill(SS_BLIND_COMBAT, 50 + random(4 * level));
    set_skill(SS_KATTACK,     100);
    set_skill(SS_BLOCK,       100);

    // last 3 for cavalry knights, to help them not fall off the horse so often.
    set_skill(SS_RIDING, 100);
    set_skill(SS_ANI_HANDL, 100);
    set_skill(SS_MOUNTED_COMBAT, 100);
}

void
horse_me(object me)
{
    horse = clone_object(WARFARE_KNIGHT_PATH+"knight_horse");

    horse->set_owner(TO);
    horse->move(E(TO));
    shadow = clone_object(WARFARE_KNIGHT_PATH+"cavalry_npc_shadow");
    shadow->shadow_me(this_object(), "layman", "fighter", "Solamnian Cavalry");
    this_object()->command("mount horse");
}


void
create_krynn_monster()
{
    set_pick_up_team(({ "knight", "squire" }));
    set_max_team_size_auto_join(5);

    set_name("knight");
    create_knight_npc();
    seteuid(getuid(TO));
    set_act_time(1);
    add_act("@@do_rescue");
    add_act("wear all");
    add_act("wield all");
    set_cact_time(1);
    add_cact("wear all");
    add_cact("wield all");
    add_cact("@@do_rescue");
    add_prop(LIVE_I_NEVERKNOWN, 1);
    add_prop(NPC_I_NO_RUN_AWAY, 1);
    add_prop("_knight_npc", 1);
    MONEY_MAKE_GC(random(25) + 5)->move(TO);

    soul_id = set_alarm(0.5, 0.0, &get_me_soul());
    set_exp_factor(EXP_PERCENTAGE);
    set_alarm(1.0, 0.0, &horse_me(this_object()));
    set_alarm(1.0, 0.0, &arm_me());
}


public void
hook_friend_killed(object friend, object killer)
{
    command("kill " + OB_NAME(killer));
}

public void
hook_friend_attacked(object friend, object enemy)
{
    command("assist " + OB_NAME(friend));
    command("charge");
}

public void
hook_friend_attack(object friend, object enemy)
{
    command("assist " + OB_NAME(friend));
    command("charge");
}



void
check_for_horse()
{
  if(!present(horse, environment(this_object())))
  {
    remove_prop(LIVE_O_STEED);
  }
}

void
get_me_soul()
{
    setuid();
    seteuid(getuid());
    add_cmdsoul(KOBJ + "solamnian_soul");
    add_cmdsoul(VOBJ + "kattack_special");
    update_hooks();
    remove_alarm(soul_id);
}

string
long_desc()
{
    string str;

    switch (level)
    {
    case 5:
    str = "Order of the Rose";
    break;
    case 4:
    str = "Order of the Sword";
    break;
    case 3:
    str = "Order of the Crown";
    break;
    default:
    str = "Knighthood";
    break;
    }

    return "This is a "+adj1+ " "+adj2+" "+gender+" "+race+", "+
    "serving as a guard for the Knights of Solamnia.\n"+
    C(POSSESSIVE(TO))+" tunic is decorated with the symbol of the "+str+".\n";
}

string
short_desc()
{
    return adj1+" "+adj2+" "+gender+" "+(level == 2 ? "squire" :
      "knight");
}

string query_guild_name_occ() { return "Solamnian Knights"; }

int query_knight_level() { return level; }

void
arm_me()
{
    object kn_clay;

    clone_object(VARM+"s_helm")->move(TO);
    clone_object(VARM+"s_gauntlets")->move(TO);

    if ((level == 3 && !random(3)) ||
        (level == 4 && !random(2)) || (level == 5))
        clone_object(VARM + "full_armour")->move(TO, 1);
    else
        clone_object(VARM + "s_armour")->move(TO, 1);

    switch(random(20) + 1)
    {
    case 1..5:
    clone_object(VARM+"s_shield")->move(TO);
    clone_object(VWEP + "s_sword")->move(TO);
    break;
    case 6..7:
    clone_unique("/d/Ansalon/balifor/flotsam_forest/obj/weapon/flail", 10,
                  VWEP+"s_mace")->move(TO);
    clone_object(VARM+"s_shield")->move(TO);
    break;
    case 8:
    clone_object(VWEP+"s_shortsword")->move(TO);
    clone_object(VARM+"s_shield")->move(TO);
    break;
    case 9..12:
    clone_unique(VWEP+"kclaymore", 15,VWEP+"two_handed_sword")->move(TO);
    break;
    case 13..15:
    clone_unique(VWEP+"kn_lance", 10, VWEP+"s_halberd")->move(TO);
    break;
    case 16..17:
    clone_object(VWEP+"s_sword")->move(TO);
    clone_object(VWEP+"s_shortsword")->move(TO);
    break;
    case 18:
    clone_object(VWEP+"s_sword")->move(TO);
    clone_unique("/d/Ansalon/balifor/flotsam_forest/obj/weapon/flail", 10,
                  VWEP+"s_mace")->move(TO);
    break;
    case 19:
    clone_object(VWEP+"s_shortsword")->move(TO);
    clone_unique("/d/Ansalon/balifor/flotsam_forest/obj/weapon/flail", 10,
                  VWEP+"s_mace")->move(TO);
    break;
    case 20:
    clone_object(VWEP+"s_shortsword")->move(TO);
    clone_object(VWEP+"s_shortsword")->move(TO);
    break;
    default:
    clone_object(VWEP+"s_sword")->move(TO);
    clone_object(VARM+"s_shield")->move(TO);
    }

    command("wear all");
    command("wield all");
}

void
do_block()
{
    command("block "+block_dir);
}

void
do_horse_charge(){
  if(!query_prop("_kcharge_preparing")){
    if(query_attack()){
      command("charge");      
    }
  }
}

void
attacked_by(object ob)
{
    switch(random(6))
    {
    case 5:
    command("kwep "+ob->query_real_name());
    break;
    case 4:
    command("kc2 death");
    break;
    case 3:
    command("kc2");
    break;
    case 2:
    command("kc1");
    break;
    case 1:
    command("kfirm");
    break;
    default:
    command("kamused");
    break;
    }

    if (ob->query_race_name() != "draconian")
    do_rescue();

    if (ob->query_average_stat() > 130 && block_dir)
    set_alarm(2.0, 0.0, &do_block());

    do_horse_charge();

    ::attacked_by(ob);
}

void
attack_object(object ob)
{
    if (ob->query_average_stat() > 89 && block_dir)
    set_alarm(2.0, 0.0, &do_block());

    do_horse_charge();
    ::attack_object(ob);
}


void
attack_func(object enemy)
{
    if (enemy->query_race() == "goblin" && !random(3))
    {
    command("shout Goblin filth!");
    }
    if (!random(3))
	command("shout Knights! Attack!");
    command("kill "+enemy->query_real_name());
}

void
init_living()
{
    init_team_pickup();
    if (interactive(TP) && (TP->query_prop("_i_attacked_in_vingaard")
    || (TP->query_race() == "goblin")))
    set_alarm(0.5, 0.0, &attack_func(TP));
    ::init_living();
}

void
emotes()
{
    switch (random(9))
    {
    case 0:
    command(level > 2 ? "kbow" : "kaspire");
    break;
    case 1:
    command("pledge");
    break;
    case 2:
    command("kswear");
    break;
    case 3:
    command("kdanger");
    break;
    case 4:
    command(race == "half-elf" ? "ksmooth h" : "ksmooth");
    break;
    case 5:
    command(level > 3 ? "ksomber" : "kfaith");
    break;
    case 6:
    command("kstudy");
    break;
    case 7:
    command("tend weapons");
    break;
    default:
    command("tend armours");
    }
}

string
do_rescue()
{
    /* rescue a fellow knight who is currently under attack */
    object *who, *ene, *good = ({ }), *bad = ({ });
    object person;
    int i,j;

    if (!objectp(E(TO)))
    {
	set_alarm(0.0, 0.0, &remove_object());
	return "";
    }

    if (!random(60))
    emotes();

    who = FILTER_LIVE(all_inventory(E(TO)));
    who -= ({ TO, 0 });
    ene = who->query_attack(-1);
    for(i = 0;i<sizeof(ene);i++)
    if (who[i] != TO && (who[i]->id("knight") ||
        MEMBER(who[i]))
      && ene[i] && !ene[i]->id("knight") &&
      !MEMBER(ene[i]))
    {
        good += ({ who[i] });
        bad += ({ ene[i] });
    }
    if (!good || !sizeof(good))
    return "";
    i = random(sizeof(good));
    j = random(sizeof(bad));
    if (good[i]->id("knight") || random(5))
    {
    if (good[i]->query_hp() < query_hp() &&
      bad[j]->query_attack() == good[i])
    {
        attack_object(bad[j]);
        bad[j]->attack_object(TO);
        tell_room(E(TO),QCTNAME(TO) + " heroically rescues " +
          QTNAME(good[i]) + ".\n", good[i]);
        good[i]->catch_msg(QCTNAME(TO)+" heroically rescues "+
          "you.\n");
    }
    }
    else
    {
    if ( E(TO)->not_called_for_help_yet() &&
      ( (bad[j])->query_race_name() != "draconian") || ( (bad[j])->query_race_name() != "dragon" ) )
        E(TO)->call_for_help(TO,good[i],bad[j]);
    }
    return "";
}

int
special_attack(object enemy)
{
    if (!random(5) &&
            ( (enemy->query_race_name() == "draconian") ||
              (enemy->query_race_name() == "dragon") ) )
    return 0;

    if((query_prop("_kcharge_resetting")) || (!query_prop(LIVE_O_STEED))){
      command("sp");
    }
    else{
      command("charge");
    }
    return 0;
}
