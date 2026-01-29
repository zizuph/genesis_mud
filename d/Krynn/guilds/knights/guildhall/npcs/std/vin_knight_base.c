/* Knight of Solamnia base file by Morrigan, Jan 97 */
/* 13.4.2000 Modified by Milan, kattack and block skills set to 100 */
/* June 11th 2006, Navarre added the use of the second adj. */
/* June 20th 2006, Navarre changed query_race == goblin to query_race_name == goblin
   to avoid knights calling minotaurs for goblins. I also added the check for hobgoblins
   so they dont get treated special, that would make real goblins jealous :)
 */

#include "/d/Krynn/common/defs.h"
#include "../../../guild.h"
#include <ss_types.h>
#include <wa_types.h>
#include <stdproperties.h>
#include <macros.h>
#include <filter_funs.h>

inherit M_FILE
inherit "/lib/unique";

inherit "/std/act/domove";
inherit "/std/act/action";

#include "killer.h"

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
create_knight_npc()
{
    if (!level)
    set_level(random(2) + 2);
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

    if (level == 2)
    add_name("squire");
    set_race_name(race);
    set_gender(gender == "female" ? 1 : 0);
    set_alignment(500 + random(5 * level));
    set_knight_prestige(-3 - random(level));
    adj1 = query_adj(gender);
    adj2 = query_adj2(gender);
    set_adj(adj1);
    add_adj(adj2);

/* Milan: Why use VBFC??? its waste of CPU
    set_short("@@short_desc");
    set_long("@@long_desc");
*/
    set_short(short_desc());
    set_long(long_desc());

    for(i = 0; i < 6; i++)
	set_base_stat(i, 60 + (10 * level) + random(10 * level));

    set_skill(SS_2H_COMBAT,    50 + random(2 * level));
    set_skill(SS_WEP_POLEARM,  50 + random(5 * level));
    set_skill(SS_WEP_CLUB,     50 + random(4 * level));
    set_skill(SS_DEFENCE,      50 + random(5 * level));
    set_skill(SS_PARRY,        60 + random(8 * level));
    set_skill(SS_WEP_SWORD,    70 + random(6 * level));
    set_skill(SS_AWARENESS,    50 + random(3 * level));
    set_skill(SS_BLIND_COMBAT, 50 + random(4 * level));
    set_skill(SS_KATTACK,     100);
    set_skill(SS_BLOCK,       100);
//  set_skill(SS_KATTACK,     100 + random(6 * level));
//  set_skill(SS_BLOCK,       110 + random(level) * 4);
}

void
create_krynn_monster()
{
    set_name("knight");
    create_knight_npc();
    seteuid(getuid(TO));
    set_act_time(1);
    add_act("@@do_rescue");
    add_act("wear all");
    add_act("wield all");
    set_cact_time(1);
    add_act("wear all");
    add_act("wield all");
    add_cact("@@do_rescue");
    add_prop(LIVE_I_NEVERKNOWN, 1);
    add_prop(NPC_I_NO_RUN_AWAY, 1);
    add_prop("_knight_npc", 1);

    soul_id = set_alarm(0.5, 0.0, &get_me_soul());
    set_alarm(1.0, 0.0, arm_me);
}

void
get_me_soul()
{
    add_cmdsoul(SOULS + "solamnian_soul");
    update_hooks();
    remove_alarm(soul_id);

    setuid();
    seteuid(getuid());
    object sh = clone_object(SHADOWS + "occ_shadow");
    int ret = sh->shadow_me(TO, "occupational", "fighter", sh->query_guild_name_occ(), 0);

    if (ret != 1)
    {
        sh->remove_object();
    }
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

    if ((level == 3 && !random(3)) || (level == 4 && !random(2)) || (level == 5))
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
    set_alarm(2.0, 0.0, do_block);

    ::attacked_by(ob);
}

void
attack_object(object ob)
{
    if (ob->query_average_stat() > 89 && block_dir)
    set_alarm(2.0, 0.0, do_block);

    ::attack_object(ob);
}


void
attack_func(object enemy)
{
    if ( ((enemy->query_race_name() == "goblin") ||
          (enemy->query_race_name() == "hobgoblin")) && !random(3))
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
    if (interactive(TP) && (TP->query_prop("_i_attacked_in_vingaard")
    || (TP->query_race_name() == "goblin") || (TP->query_race_name() == "hobgoblin")))
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
	set_alarm(0.0, 0.0, remove_object);
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

    command("kattack");
    return 0;
}

// Knights who block should not block other knights who are not currently
// in battle with them.
public int
query_ignore_block(object player)
{
    if (player->query_guild_name_occ() == "Solamnian Knights"
        && !IN_ARRAY(player, query_enemy(-1)))
    {
        return 1;
    }
    return 0;
}
