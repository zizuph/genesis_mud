/* Knight of Solamnia base file by Morrigan, Jan 97
 * 
 * Adapted by Mortis for use in the retired Solamnian
 * knight Sir Engen, proprietor of the Solamnian Livery
 * in Palanthas.
 */

#include "../../local.h"
#include "/d/Krynn/solamn/vin/knight/guild.h"
#include <ss_types.h>
#include <wa_types.h>
#include <stdproperties.h>
#include <macros.h>
#include <money.h>
#include <filter_funs.h>
#include "/d/Krynn/common/defs.h"
//#include "/d/Krynn/solamn/vin/std/killer.h"

#define MONEY 3000 + random(5000)

inherit M_FILE
inherit "/lib/unique";
inherit "/std/act/domove";
inherit "/std/act/action";

int attacked = 0;

void get_me_soul();
string do_rescue();
int soul_id;
string block_dir;


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
reply_my_horses()
{
E(TO)->query_my_horses(TP);
return "";
}

void
create_krynn_monster()
{
    set_name("engen");
    set_race_name("human");
	//    create_knight_npc();
    seteuid(getuid(TO));
    add_name(({"engen", "knight", "proprietor"}));
	set_gender(G_MALE);
	set_adj("aging");
	add_adj("moustachioed");
	set_stats(({150,110,180,100,120,150}));
	set_alignment(1000);
	set_knight_prestige(-10);
	set_introduce(1);
	set_title("the Proprietor of the Solamnian Livery");
	set_long("A man getting on in years, perhaps in his mid fifties, "
	+ "he wears a long, brown, handlebar moustache.  His hair is straight, "
	+ "brown, has a few gray hairs, and is tied back into a short pony "
	+ "tail.  Though growing plump, it is not hard to notice the large, "
	+ "muscular frame beneath his clothes.  A plain, wooden scabbard "
	+ "hangs at his side, and he moves as if it's always been there.\n"
	+ "He is missing his left leg below the knee, but you can hardly tell "
	+ "by his steady gait.  It has been replaced by a plate armoured, "
	+ "boot leg the harness of which is hooked to a peg on his breastplate.\n"
	+ "The copper symbol emblazoned on his breastplate is a crown around "
	+ "a downward pointing greatsword.\n");

//  set_size_descs(string height, string width)
	set_size_descs("of normal length", "plump");
	set_appearance(7);
	
    set_skill(SS_2H_COMBAT,    60);
    set_skill(SS_DEFENCE,      90);
    set_skill(SS_PARRY,        95);
    set_skill(SS_WEP_SWORD,   100);
    set_skill(SS_UNARM_COMBAT, 70);
    set_skill(SS_AWARENESS,    50);
    set_skill(SS_BLIND_COMBAT, 70);
    set_skill(SS_KATTACK,     100);
    set_skill(SS_BLOCK,       100);
	set_skill(SS_ANI_HANDL, 30);
    set_skill(SS_RIDING, 30);

	set_all_hitloc_unarmed(50);
	
    set_act_time(12);
    add_act("@@do_rescue");
	add_act("say My family will see to it your horse is fed, groomed, "
	+ "and safe while stabled at our livery.  Know it is so.");
	add_act("emote slowly strokes his long, handlebar moustache with a "
	+ "far off look in his eyes.");
	add_act("smell");
	add_act("say Palanthas is the most noble city of the realms.  I call "
	+ "no other my home.");
    set_cact_time(10);
    add_cact("@@do_rescue");
	add_cact("kattack");

	add_prop(HAS_NO_LEFT_LEG, 1);
    add_prop(NPC_I_NO_RUN_AWAY, 1);
    add_prop("_knight_npc", 1);
	add_prop(NPC_I_NO_UNARMED, 1);

	add_ask(({"horse","my horses","my horse","about my horses",
		 "horses","about my horse"}), reply_my_horses,1);
	add_ask(({"knight", "knights", "solamnia"}), "He replies:  "
	+ "Yes, I was a knight of Solamnia, but I am retired now.  "
	+ "It was a time in my life I will always look back on with "
	+ "pride despite my loss.\n");
	add_ask(({"leg", "legs", "left leg", "loss"}), "He replies:  "
	+ "Old age came upon me as it comes for every man in his time.  "
	+ "It was in a campaign against the Green Dragonarmy that a "
	+ "hobgoblin officer took my left leg.  I was too slow.  That "
	+ "is all there is to it.\n");
	add_ask(({"palanthas", "city"}), "He replies:  Palanthas has a "
	+ "heart blessed by Paladine.  You must search far abroad to "
	+ "find its equal in nobility, learning, and trade.  And there "
	+ "is no safer city in all of Krynn.  By the Oath that is true.\n");
	add_ask(({"livery", "service", "services", "help"}), "He replies:  "
	+ "The Solamnian Livery will see to it your horse is fed, groomed, "
	+ "and safe in our stables.  The care of steeds is no service we "
	+ "take lightly.\n");
	add_ask("hobgoblin", "Engen strokes his long, handlebar moustache "
	+ "as he gazes past you, replying:  The worthier on the field that "
	+ "day.  My only regret is the loss of my left spur.  I don't "
	+ "remember much after the blow that severed my leg other than falling "
	+ "from my steed.  I always assumed he took it as a trophy.\n");

    soul_id = set_alarm(0.5, 0.0, &get_me_soul());
    
}

void
get_me_soul()
{
    add_cmdsoul("/d/Krynn/solamn/vin/knight/obj/solamnian_soul");
    add_cmdsoul("/d/Krynn/solamn/vin/obj/kattack_special");
    update_hooks();
    remove_alarm(soul_id);
}

string query_guild_name_occ() { return "Solamnian Knights"; }

void
arm_me()
{
    seteuid(getuid(TO));
    clone_object(NOBLE + "arms/engen_bp")->move(TO);
	clone_object(NOBLE + "arms/engen_legs")->move(TO);
    command("wear all");
	clone_object("/d/Krynn/solamn/vin/armour/s_helm")->move(TO);
	MONEY_MAKE_PC(random(2))->move(TO);
	MONEY_MAKE_GC(20 + random(15))->move(TO);
}

void
do_block()
{
    command("block " + block_dir);
}

void
attacked_by(object ob)
{
    switch(random(6))
    {
    case 5:
    command("kwep " + ob->query_real_name());
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

    if ( attacked == 0)
    {
		attacked++;
		command("emote draws his blade from the scabbard at his side.");
		clone_object("/d/Krynn/solamn/vin/weapon/s_sword")->move(TO);
		command("wield sword");
		command("shout My Shield!");
		write("A stablehand tosses the retired knight his shield.\n");
		clone_object("/d/Krynn/solamn/vin/armour/s_shield")->move(TO);
		command("wear shield");
		command("wear helm");
		command("emote dons his helm and shield and swivels on his metal "
		+ "leg into a combat stance, shield forth, blade raised high behind "
		+ "his head.");
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
/*
void
init_living()
{
    if (interactive(TP) && (TP->query_prop("_i_attacked_in_vingaard")
    || (TP->query_race() == "goblin")))
    set_alarm(0.5, 0.0, &attack_func(TP));
    ::init_living();
}
*/
void
emotes()
{
    switch (random(9))
    {
    case 1:
    command("kbow");
    break;
    case 2:
    command("pledge");
    break;
    case 3:
    command("kswear");
    break;
    case 4:
    command("kdanger");
    break;
    case 5:
    command("ksmooth");
    break;
    case 6:
    command("ksomber");
    break;
    case 7:
    command("kstudy");
    break;
    case 8:
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

    command("sp");
    return 0;
}

