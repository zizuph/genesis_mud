#include <filter_funs.h>
#include <formulas.h>
#include <wa_types.h>
#include "../local.h"
#include "/d/Shire/sys/defs.h"


inherit SHIRE_MONSTER;
inherit KILL_LOGGER;
inherit "/lib/unique";

#define SUP_GOBLIN_LEVEL      140
#define HIGH_GOBLIN_LEVEL     100
#define MEDIUM_GOBLIN_LEVEL    70

#define I_KILL_GOBLINS "_i_killed_misty_goblins_"

// Prototypes
void slow_init_attack(object player);

string *ran_wep = ({ "pole", "sword", "axe", "club" });
string *ran_arm = ({ "helm", "shield" });
string *def_arm = ({ "mail" });

string *looks = ({"cruel","angry","mean","foul","brutal","sinister",
  "ugly","nasty","evil","savage","dangerous","strong" });
string *c_chats = ({ "I hate intruders in our caves!!!",
  "We will have fresh flesh to feed on!",
  "Someone go and prepare our pot!",
	"I got axe for you!"});
string *chats = ({ "What is our lord going to do with that prisoner?",
  "I am hungry!!!",
  "Watch out! I have news that there are intruders in our cave.",
	"Me so horned, me hurt you long time!"});
int base_gob = 30;
int ran_gob = 90;
int knight_prestige, base;
string type = "_low";

/* Function create_goblin() to be redefined when creating a goblin in order
 * to set your own values to:
 *  ran_wep, ran_arm, def_arm, looks, c_chats, chats, base_gob, ran_gob
 * Use below defined functions.
 */
void create_goblin(){}

nomask void set_ran_wep (string *s){ ran_wep  = s; }
nomask void set_ran_arm (string *s){ ran_arm  = s; }
nomask void set_def_arm (string *s){ def_arm  = s; }
nomask void set_looks   (string *s){ looks    = s; }
nomask void set_c_chats (string *s){ c_chats  = s; }
nomask void set_chats   (string *s){ chats    = s; }
nomask void set_base_gob(int i)    { base_gob = i; }
nomask void set_ran_gob (int i)    { ran_gob  = i; }

nomask void
create_shire_monster()
{
    int i;
    string ll_2, ll_1 = "medium";

    add_prop(LIVE_I_NEVERKNOWN, 1);
    add_prop(LIVE_I_SEE_DARK, 3);
    add_prop(CONT_I_HEIGHT, 120);
    add_prop(CONT_I_WEIGHT, 36000);
    add_prop(CONT_I_VOLUME, 36000);
    /*
      add_prop(DO_I_TELL_RUMOURS, 1);
    */
    set_name("_misty_goblin_");
//    add_name ("goblin");
    set_long("It is a very ugly and nasty lookin' goblin.\n");

    create_goblin();

    base = base_gob + random(ran_gob);
    if (base >= MEDIUM_GOBLIN_LEVEL){ type = "_med"; ll_1 = "big"; }
    if (base >= HIGH_GOBLIN_LEVEL){ type = "_high"; ll_1 = "massive"; }
    if (base >= SUP_GOBLIN_LEVEL){ type = "_sup"; ll_1 = "huge"; }
    ll_2 = ONE_OF(looks);

    set_pname("goblins");
    set_race_name("goblin");
    set_adj(({ ll_1, ll_2 }));
    set_short(ll_1 + " " + ll_2 + " goblin");

    set_base_stat(SS_STR, (base * 3 / 4) + random(base / 2));
    set_base_stat(SS_DEX, (base * 3 / 4) + random(base / 2));
    set_base_stat(SS_CON, (base * 3 / 4) + random(base / 2));
    set_base_stat(SS_WIS, (base * 2 / 5) - random(base / 3));
    set_base_stat(SS_INT, (base * 2 / 5) - random(base / 3));
    set_base_stat(SS_DIS, (base * 4 / 5) + random(base / 2));

    refresh_mobile(); /* full hp, mana, fatigue */


    set_alignment(-(4 * base));
    knight_prestige = 4 * base;

    set_aggressive(random(3));

    set_skill(SS_BLIND_COMBAT, MIN(100,(base * 3 / 4) + random(base / 2)));
    set_skill(SS_WEP_SWORD,    MIN(100,(base * 3 / 4) + random(base / 2)));
    set_skill(SS_WEP_CLUB,     MIN(100,(base * 3 / 4) + random(base / 2)));
    set_skill(SS_WEP_AXE,      MIN(100,(base * 3 / 4) + random(base / 2)));
    set_skill(SS_WEP_POLEARM,  MIN(100,(base * 3 / 4) + random(base / 2)));
    set_skill(SS_WEP_KNIFE,    MIN(100,(base * 3 / 4) + random(base / 2)));
    set_skill(SS_PARRY,        MIN(100,(base * 3 / 4) + random(base / 2)));
    set_skill(SS_DEFENCE,      MIN(100,(base * 3 / 4) + random(base / 2)));
    set_skill(SS_AWARENESS,    MIN(100,(base * 3 / 4) + random(base / 2)));

    set_chat_time(10 + random(30));
    for (i = 0; i < sizeof(chats); i++)
	add_chat(chats[i]);

    set_cchat_time(random(10));
    for (i = 0; i < sizeof(c_chats); i++)
	add_cchat(c_chats[i]);

    set_act_time(10 + random(20));
    add_act("burp");
    add_act("hiss");
    add_act("spit");
    add_act("eat all");
    add_act("drink all");
    add_act("get all");

    set_cact_time(random(10));
    add_cact("scream");
    add_cact("grin");
    add_cact("@@do_tackle");
    add_cact("@@do_knee");
    add_cact("@@do_kick");

}

/*
 * Give the goblin armour and a weapon.
 */
void arm_me()
{
    int i;
    object cash, wep, arm;

    seteuid(getuid());

    wep = clone_object(WEP_DIR + ONE_OF(ran_wep) + type);
    wep->move(TO,1);
    if (wep->query_prop(OBJ_I_IS_MAGIC_WEAPON))
    {
	// Ugly but we'll live with it.
	wep->remove_object();
	wep = clone_unique(WEP_DIR + "club" + type, MAX_UNIQUE_ITEMS, 
	  WEP_DIR + "club_med");
	wep->move(TO, 1);
    }
    if (wep->query_prop(OBJ_I_IS_MAGIC_WEAPON))
	set_kill_log_name("club_shield");
    arm = clone_object(ARM_DIR + ONE_OF(ran_arm) + type);
    arm->move(TO, 1);
    for (i = 0; i < sizeof(def_arm); i ++)
	clone_object(ARM_DIR + def_arm[i] + type)->move(TO,1);

    command("wield all");
    command("wear all");

    cash = clone_object("/std/coins");
    cash->set_coin_type("copper");
    cash->set_heap_size(random(base));
    cash->move(TO,1);
#ifdef 0
    if(base > MEDIUM_GOBLIN_LEVEL)
    {
	cash = clone_object("/std/coins");
	cash->set_coin_type("silver");
	cash->set_heap_size(random(base / 3));
	cash->move(TO,1);
    }
    if(base > HIGH_GOBLIN_LEVEL)
    {
	cash = clone_object("/std/coins");
	cash->set_coin_type("gold");
	cash->set_heap_size(random(base / 9));
	cash->move(TO,1);
    }
    if(base > SUP_GOBLIN_LEVEL)
    {
	cash = clone_object("/std/coins");
	cash->set_coin_type("platinum");
	cash->set_heap_size(random(base / 27));
	cash->move(TO,1);
    }
#endif
}

void init_attack()
{
    set_alarm(itof(random(20)), 0.0, &slow_init_attack(TP));
}

void slow_init_attack(object tp)
{
    if (!tp || query_attack() || !present(tp, environment()))
	return;

    /* wizards aren't attacked... */
    if (tp->query_wiz_level()) return;

    /* Goblins aren't attacked either, unless they've killed one of us */
    if (tp->query_race_name() == "goblin" &&
      (!tp->query_prop(I_KILL_GOBLINS)))
	return;

    if (!F_DARE_ATTACK(TO,tp))
	return;

    aggressive_attack(tp);
    if(!random(3))
	set_alarm(itof(random(10)), 0.0, "command", "grin "+tp->query_real_name());
}

/*
 * Function name: attacked_by
 * Description:   This function is called when somebody attacks this object
 * Arguments:     ob - The attacker
 */
void attacked_by(object ob)
{
    object *arr;
    int i;

    ::attacked_by(ob);

    if(!random(3)) set_alarm(itof(random(10)), 0.0, "shout_for_help_2", ob);
    arr = FILTER_LIVE(all_inventory(environment()));
    for (i = 0; i < sizeof(arr); i++)
	if((arr[i]->query_real_name() == "_misty_goblin_") && (arr[i] != TO))
	    arr[i]->notify_ob_attacked_me(ob);
}

void notify_ob_attacked_me(object ob)
{
    if(query_attack()) return;
    if (random(10) && F_DARE_ATTACK(TO, ob))
	set_alarm(itof(5+random(10)), 0.0, "help_friend", ob);
}

void help_friend(object ob)
{
    if (ob && !query_attack() && present(ob, environment()))
    {
	if(!random(3)) command("grin "+ob->query_real_name());
	command("kill "+ob->query_real_name());
    }
}

void do_knee()  { command("knee "+query_attack()->query_real_name()); }
void do_kick()  { command("kick "+query_attack()->query_real_name()); }
void do_tackle(){ command("tackle "+query_attack()->query_real_name()); }

void
notify_you_killed_me(object who)
{
    command("shout Another dead body!!!");
    command("laugh");
    set_alarm(2.0, 0.0, "command", "get all from corpse");
}

void shout_for_help_2(string who)
{
    int i;
    object *arr;

    if(!who) return;
    arr = TO->query_enemy(-1);

    for(i=0; i < sizeof(arr); i++)
	if(arr[i]->query_name() == who)
	    command("shout Help!!! The "+arr[i]->query_nonmet_name()+
	      " wants to kill me!");
}

/*
 * Solamnian knight prestige
 */
int query_knight_prestige(){ return knight_prestige; }

int special_attack(object enemy)
{
    object prisoner;

    /* some special attacks dont call attacked_by() */
    if(!random(3)) attacked_by(enemy);

    prisoner = present("_misty_prisoner_", environment());
    if(!prisoner || (TO->query_attack()==prisoner)) return 0;
    if(prisoner->check_seen(TO))
    {
	TO->attack_object(prisoner);
	prisoner->attack_object(TO);
    }

    /*
      prisoner = find_living("_misty_prisoner_");
      if (!prisoner) return 0;
      if(TO->query_attack() == prisoner) return 0;
if (present(prisoner, environment()))
	if((member_array(prisoner, TO->query_enemy(-1)) != -1) ||
	   (prisoner->check_seen(TO)))
	{
	   TO->attack_object(prisoner);
	   prisoner->attack_object(TO);
	}
    */

    return 0;
}

public void
do_die(object killer)
{

    if (killer->query_race_name() == "goblin" && 
      (!killer->query_prop(I_KILL_GOBLINS)))
    {
	command("shout Traitor!!!  There be a traitor in our ranks!!!");
	killer->add_prop(I_KILL_GOBLINS, 1);
    }
    return ::do_die(killer);
}
