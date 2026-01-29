/* An evil warlord. Mortricia 931205 */
inherit "/std/monster";

inherit "/std/act/action";
inherit "/std/act/seqaction";
inherit "/std/act/domove";
inherit "/d/Terel/mortricia/global/skill_support";

#include <stdproperties.h>
#include <macros.h>
#include <ss_types.h>
#include <wa_types.h>
#include <money.h>
#include <language.h>

#define BS(message)     break_string(message, 72)
#define BSN(message)    break_string(message + "\n", 72)
#define NF(xx)          notify_fail(xx)
#define TP              this_player()
#define TO              this_object()
#define ETO             environment(this_object())
#define ALIGN           -1080
#define SPELL_DELAY     26
#define PEACE_DELAY     5
#define KILLER          "_wl_killer"
#define PARA_OBJ        "/std/paralyze"
#define PARA_TIME       157
#define FRAC_OBJ        "/d/Terel/sorgum/fracture"
#define MAX_HELP        2

#define MANSION         "/d/Terel/common/town/mansion/"
#define CLOAK           MANSION+"obj/ew_cloak"
#define HELMET          MANSION+"obj/ew_helmet"
#define GLOVES          MANSION+"obj/ew_gloves"
#define MAIL            MANSION+"obj/ew_mail"
#define SWORD           MANSION+"obj/ew_sword"
#define DRINK           MANSION+"obj/ew_drink"
#define SPEED           MANSION+"obj/ew_speed"

#define KILL_LOG        MANSION+"mon/warlord_kills"

void set_spell_prop(object ob);
void bring_back_sword();
void break_weapon(object ob);
void break_armour(object ob);
void hurt_all_enemies();
void hurt_random_enemy();
void slow_down_enemy();
void ew_attack(object enemy, int wc_pen);
void call_for_help();
public object *query_my_enemies();
void cure_from_poison();
public void paralyze_enemy();
void peace_attack(object who);

static object *pend_enemies;
object sword;
int no_help=0;
int prop_check=0;

void
init_living()
{
    ::init_living();
}

void
create_monster()
{
    if (!IS_CLONE) return;

    set_name("mergula");
    add_name("warlord");
    set_living_name("mergula");
    set_long(BSN(
	"It is a mean-looking human. This awful being is twice " +
	"as large as any other human you ever have seen before. " +
	"Judged by his appearance you conclude that he must be " +
	"the evil warlord of the Legion of Darkness. " +
	"You should not mess with him unless you are very " +
	"sure about your capabilities since he is known to " +
	"deliver a surprise, or two, when he fights."
        ));
    set_adj(({"mean-looking", "evil"}));
    set_race_name("human");
    set_gender(0);

    set_stats(({173,188,165,110,117,129}));
    set_hp(9999);
    set_mana(9999);
    set_alignment(ALIGN);
    set_all_hitloc_unarmed(60);
    set_all_attack_unarmed(35, 40);
    set_skill(SS_DEFENCE, 100);
    set_skill(SS_WEP_SWORD, 100);
    set_skill(SS_PARRY, 100);
    set_skill(SS_BLIND_COMBAT, 100);
    set_skill(SS_UNARM_COMBAT, 40);
    set_skill(SS_2H_COMBAT, 95);
    set_skill(SS_AWARENESS, 99);

    set_ss_skill("SPELL", ({99, 50, 50}));
    set_ss_skill("FORM", ({99, 80, 25, 50, 50, 50}));
    set_ss_skill("ELEMENT", ({99, 50, 55, 55, 50, 80}));

    add_prop(OBJ_I_RES_FIRE, 35);
    add_prop(OBJ_I_RES_MAGIC, 35);
    add_prop(OBJ_I_RES_DEATH, 35);
    add_prop(OBJ_I_RES_POISON, 75);
    add_prop(OBJ_I_RES_IDENTIFY, 55);

    add_prop(LIVE_I_SEE_DARK, 99);
    add_prop(LIVE_I_QUICKNESS, 100);
    add_prop(CONT_I_WEIGHT, 240000);
    add_prop(CONT_I_VOLUME, 240000);
    add_prop(CONT_I_MAX_WEIGHT, 390000);
    add_prop(CONT_I_MAX_VOLUME, 390000);
    remove_prop(NPC_M_NO_ACCEPT_GIVE);

    trig_new("%s 'introduces' %s", "intro_me");

    set_act_time(40);
    add_act(({"say Now, where is that map?", "frown", "ponder"}));

    seq_new("do_first");
    seq_addfirst("do_first", "@@dress_me");
    
    set_alarm(2.0, -1.0, "set_spell_prop",  TO);
    prop_check = 1;
}

void
dress_me()
{
    seteuid(getuid());

    MONEY_MAKE_PC(2+random(4))->move(TO);
    MONEY_MAKE_GC(5)->move(TO);

    clone_object(CLOAK)->move(TO);
    clone_object(MAIL)->move(TO);
    clone_object(GLOVES)->move(TO);
    clone_object(HELMET)->move(TO);
    command("wear all");

    sword = clone_object(SWORD);
    sword->move(TO);
    sword->add_prop(KILLER, TO->query_name());
    command("wield sword");
}

void
spell_attack(object me, object victim)
{
    int spell;

    spell = random(7);
    if (spell == 0) {
      hurt_all_enemies(); 
    } else if (spell == 1) {
      hurt_random_enemy();
    } else if (spell == 2) {
      slow_down_enemy();
    } else if (spell == 3) {
      command("kick " + victim->query_real_name());
      break_weapon(victim);
    } else if (spell == 4) {
      command("kick " + victim->query_real_name());
      break_armour(victim);
    } else if (spell == 5) {
      paralyze_enemy();
    } else if (spell == 6) {
      seteuid(getuid());
      if (!present("rum", TO)) clone_object(DRINK)->move(TO);
      command("drink rum");
      heal_hp(200+random(100));
      cure_from_poison();
      if (sword && sword->query_wielded() != TO) bring_back_sword();
    }
    call_for_help();
    set_alarm(itof(2+random(SPELL_DELAY)), -1.0, "set_spell_prop",  me);
    return;
}

void
bring_back_sword()
{
    object where;

    if (sword->query_prop(KILLER) != query_name()) return;

    where = environment(sword);
    if (where == TO) {
	command("wield sword");
	return;
    } else if (where == ETO) {
	sword->move(TO);
	tell_room(ETO, QCTNAME(TO) + " gets " +
		  LANG_ASHORT(sword) + ".\n", TO);
	command("wield sword");
	return;
    } else if (living(where)) {
	command("snap");
	sword->move(TO);
	where->catch_msg("The " + sword->short() +
		         " suddenly disappears!\n");
	tell_room(ETO, "The " + sword->short() +
	          " suddenly reappears in the hands of " +
	          QTNAME(TO) + ".\n", TO);
	return;
    } else {
	command("snap");
	sword->move(TO);
	if (where->query_prop(ROOM_I_IS))
	    tell_room(where, "The " + sword->short() +
			     " suddenly disappears!\n");
	tell_room(ETO, "The " + sword->short() +
	          " suddenly reappears in the hands of " +
	          QTNAME(TO) + ".\n", TO);
	command("wield sword");
	return;
    }
}

void
break_weapon(object ob)
{
    object *all, fracture;
    int i;

    all = all_inventory(ob);

    for (i=0; i<sizeof(all); i++) {
	if (!function_exists("create_weapon", all[i])) continue;
	if (all[i]->query_wielded() == ob) {
	    ob->catch_msg("The forceful kick hit your " +
			      all[i]->short() + ".\n");
	    all[i]->remove_broken();
            if (random(5) == 0 && !present("fracture", ob)) {
                fracture = clone_object(FRAC_OBJ);
                fracture->move(ob);
            }
	    return;
	}
    }
    break_armour(ob);
}

void
break_armour(object ob)
{
    object *all;
    int i;

    all = all_inventory(ob);

    for (i=0; i<sizeof(all); i++) {
	if (!function_exists("create_armour", all[i])) continue;
	if (all[i]->query_worn() == ob) {
	    ob->catch_msg("The forceful kick hit your " +
			      all[i]->short() + ".\n");
	    all[i]->remove_broken();
	    return;
	}
    }
    ob->catch_msg("The forceful kick hit you " +
		  "right in the solar plexus!\n");
    i = 320 + random(400) - ob->query_stat(SS_CON);
    if (i<100) i = 100;
    ob->reduce_hit_point(i);
    if (ob->query_hp() <= 0) ob->do_die(TO);
}

void
hurt_all_enemies()
{
    int i, dam;
    object *all;

    all = query_my_enemies();

    for (i=0; i<sizeof(all); i++) {
        dam = all[i]->query_alignment() - query_alignment();
        if (sword && environment(sword) != TO)
            dam = dam/4;
        else
            dam = dam/6;
        command("stare evilly at " + all[i]->query_real_name());
        ew_attack(all[i], dam);
    }
}

void
hurt_random_enemy()
{
    int dam;
    object *enemies, enemy;

    enemies = query_my_enemies();
    if (sizeof(enemies) == 0) return;
    enemy = enemies[random(sizeof(enemies))];

    dam = enemy->query_alignment() - query_alignment();
    if (sword && environment(sword) != TO)
        dam = dam/2;
    else
        dam = dam/3;
    command("stare evilly at " + enemy->query_real_name());
    ew_attack(enemy, dam);
}

void
slow_down_enemy()
{
    int i, time;
    object *all, *enemies, enemy, speed;

    enemies = query_my_enemies();
    if (sizeof(enemies) == 0) return;
    enemy = enemies[random(sizeof(enemies))];

    all = all_inventory(enemy);
    for (i=0; i<sizeof(all); i++) {
        if (MASTER_OB(all[i]) == SPEED) {
            command("kick " + enemy->query_real_name());
            break_weapon(enemy);
            return;
        }
    }
    time  = enemy->query_alignment() - query_alignment();
    time -= enemy->query_magic_res(MAGIC_I_RES_LIFE);
    time = time/3;
    if (time <= 0) return;

    command("grin evilly at " + enemy->query_real_name());

    seteuid(getuid());
    speed = clone_object(SPEED);
    speed->set_duration(time);
    speed->set_quickness(-90);
    speed->move(enemy);
}

void
set_spell_prop(object ob)
{
    prop_check = 0;
    add_prop(LIVE_O_SPELL_ATTACK, ob);
    prop_check = 1;
}

void
intro_me(string s1, string s2)
{
    set_alarm(2.0, -1.0, "do_intro");
}

void
do_intro()
{
    command("introduce myself");
    command("grin");
}

void
enter_inv(object ob, object old)
{
    ::enter_inv(ob, old);
    if (!old || !living(old)) return;
    set_alarm(2.0, -1.0, "drop_ob", ob);
}

void
drop_ob(object ob)
{
    if (function_exists("create_weapon", ob) ||
        function_exists("create_armour", ob)) {
	if (ob == sword && ob->query_prop(KILLER) == query_name()) {
	    if (ob->query_prop(OBJ_I_BROKEN)) {
                tell_room(ETO, QCTNAME(TO) +
                          " kisses the blade of his " + ob->short() +
		          ".\n", TO);
		ob->remove_prop(OBJ_I_BROKEN);
	    }
	    command("wield sword");
	    command("laugh evilly");
	    return;
	}
	if (!(ob->query_prop(OBJ_I_BROKEN))) {
	    ob->remove_broken();
            tell_room(ETO, QCTNAME(TO)+" breaks the "+ob->short()+
		 " with his left hand!\n", TO);
	}
	command("grin evilly");
    }
    ob->move(ETO);
    tell_room(ETO, QCTNAME(TO)+" drops "+LANG_ASHORT(ob)+".\n", TO);
}

string
query_title()
{
    return "the evil Warlord of the Legion of Darkness";
}

void
ew_attack(object enemy, int wc_pen)
{
    mixed *hres;
    string how;
    int dam;
   
    if (wc_pen <= 2)
	dam = 2;
    else
	dam = (3*wc_pen + 2*random(wc_pen))/5;

    hres = enemy->hit_me(dam, MAGIC_DT, TO, -1);
    how = "seem unaffected";
    if (hres[0] > 0) how = "get a slight headache";
    if (hres[0] > 25) how = "feel an aching pain";
    if (hres[0] > 40) how = "feel an intense pain";
    if (hres[0] > 60) how = "feel a terrible pain";
   
    enemy->catch_msg("You "+how+" as "+QTNAME(TO)+" stares at you.\n");
    if (hres[0] > 40) {
	tell_room(environment(enemy),
		  QCTNAME(enemy) + " trembles of fear and pain.\n",
		  ({TO, enemy}));
	enemy->add_panic(hres[0]/2);
    }
   
    if (enemy->query_hp() <= 0) enemy->do_die(TO);
    return;
}

void
do_die(object killer)
{
    int i;
    string str;
    object *enemies;
    
    if (query_hp() > 0) return;
    
    if (sword && sword->query_wielded() == TO) {
        tell_room(ETO, QCTNAME(TO) +
                  " kisses the blade of his " + sword->short() +
		  ".\n", TO);
	if (sword->query_prop(OBJ_I_BROKEN))
	    sword->remove_prop(OBJ_I_BROKEN);
	if (killer && ETO == environment(killer)) {
            sword->change_prop(KILLER, killer->query_name());
	    killer->catch_msg(QCTNAME(TO) + " points at you with his " +
			      sword->short() + " as he dies.\n");
            tell_room(ETO, QCTNAME(TO) + " points at " +
		      QTNAME(killer) + " with his " + sword->short() +
		      " as he dies.\n", ({TO, killer}));
	}
        command("drop sword"); 
    }
    command("sigh");
    enemies = query_my_enemies();
    str = killer->query_name() + "[" + killer->query_average_stat() + "]";
    for (i=0; i<sizeof(enemies); i++) {
      if (enemies[i] != killer)
          str += ", " + enemies[i]->query_name() +
                 "[" + enemies[i]->query_average_stat() + "]";
    }
    write_file(KILL_LOG, str + " (" + ctime(time()) + ")\n");
    
    ::do_die(killer);
}

void
call_for_help()
{
    object *enemies, knight;

    enemies = query_my_enemies();
    if (sizeof(enemies) == 0) {
	add_panic(-query_panic());
	return;
    }

    if (query_hp() > query_max_hp()/(2 + 2*no_help)) return;

    if (no_help >= MAX_HELP) {
	command("shout Knights! I need help! Where are you?");
	if (query_panic() < 100) command("panic");
	hurt_random_enemy();
	no_help++;
        return;
    }

    if (no_help == 0) {
        command("shout Knight! Believe it or not, but I need " +
		"help at once!");
    } else {
        command("shout Knight! Come to my aid! " +
		"These bastards are tough!");
    }
    seteuid(getuid());
    knight = clone_object(MANSION + "mon/dknight");
    knight->move_living("M", ETO);
    tell_room(ETO, QCTNAME(knight) + " arrives.\n");
    knight->command("gasp");
    knight->help_the_boss(TO);
    knight->attack_someone();
    no_help++;
}

public object *
query_my_enemies()
{
    int i;
    object *all, *enemies;

    all = all_inventory(ETO);

    enemies = ({ });
    for (i=0; i<sizeof(all); i++) {
	if (living(all[i]) && all[i] != TO &&
	    member_array(TO, all[i]->query_enemy(-1)) >= 0) {
	    enemies += ({ all[i] });
        }
    }
    return enemies;
}

void
cure_from_poison()
{
    int i;
    object *all;

    all = all_inventory(TO);
    for (i=0; i<sizeof(all); i++) {
	if (function_exists("cure_poison", all[i]) ==
	    "/std/poison_effect") {
	    all[i]->cure_poison(({"all"}), 100);
	    command("say Who's trying to poison me?");
	    command("say Poison has little effect on me...");
	    command("laugh evilly");
	    hurt_all_enemies();
	    return;
	}
    }
}

public int
query_knight_prestige()
{
    return 200;
}

public void
paralyze_enemy()
{
    int i, time;
    object *all, *enemies, enemy, para;

    enemies = query_my_enemies();
    if (sizeof(enemies) == 0) return;
    enemy = enemies[random(sizeof(enemies))];

    all = all_inventory(enemy);
    for (i=0; i<sizeof(all); i++) {
        if (MASTER_OB(all[i]) == PARA_OBJ) {
            command("kick " + enemy->query_real_name());
            break_weapon(enemy);
            return;
        }
    }
    time  = PARA_TIME;
    time -= enemy->query_stat(SS_INT);
    time -= random(enemy->query_magic_res(MAGIC_I_RES_DEATH));
    if (time <= 10) time = 10;
    
    time = 5 + random(time);

    command("grin evilly at " + enemy->query_real_name());

    seteuid(getuid(TO));
    para = clone_object(PARA_OBJ);
    para->set_stop_verb("");
    para->set_remove_time(time);
    para->set_stop_object(0);
    para->set_stop_message("You stop being paralyzed.\n");
    para->set_fail_message("You are still paralyzed.\n");
    para->move(enemy);
    
    enemy->catch_msg(QCTNAME(TO) +
                     "'s overwhelming appearance paralyzes you!\n");
    tell_room(ETO, QCTNAME(enemy) + " becomes paralyzed when " +
              QTNAME(TO) + " grins at " + enemy->query_objective() + ".\n",
              ({enemy, TO}));
}

/*
 * Function name: remove_prop_live_o_spell_attack
 * Description:   To prevent unauthorized removal of LIVE_O_SPELL_ATTACK.
 *                Since Mergula is dependent on his spell attacks, we don't
 *                want any removal or change of this property
 * Arguments:     -
 * Returns:       1 / 0.
 */
public nomask int
remove_prop_live_o_spell_attack()
{
    if (prop_check) return 1;
    return 0;
}

/*
 * Function name: add_prop_live_o_spell_attack
 * Description:   To prevent unauthorized changing of LIVE_O_SPELL_ATTACK.
 *                Since Mergula is dependent on his spell attacks, we don't
 *                want any removal or change of this property
 * Arguments:     -
 * Returns:       1 / 0.
 */
public nomask int
add_prop_live_o_spell_attack()
{
    if (prop_check) return 1;
    return 0;
}

/*
 * Function name: add_prop_live_i_attack_delay
 * Description:   To prevent changing of LIVE_I_ATTACK_DELAY.
 *                Since Mergula is dependent on his spell attacks, we don't
 *                want any extra delay of special_attack
 * Arguments:     -
 * Returns:       1 / 0.
 */
public nomask int
add_prop_live_i_attack_delay()
{
    if (prop_check) return 1;
    return 0;
}

public nomask int
remove_prop_live_i_attack_delay()
{
    if (prop_check) return 1;
    return 0;
}

/*
 * Function name: add_prop_live_i_quickness
 * Description:   To prevent changing of LIVE_I_QUICKNESS.
 *                Since Mergula is dependent on his spell attacks, we don't
 *                want any extra delay of special_attack
 * Arguments:     -
 * Returns:       1 / 0.
 */
public nomask int
add_prop_live_i_quickness()
{
    if (prop_check) return 1;
    return 0;
}

public nomask int
remove_prop_live_i_quickness()
{
    if (prop_check) return 1;
    return 0;
}

public void
stop_fight(mixed elist)
{
    pend_enemies = query_my_enemies();
    ::stop_fight(elist);
    if (TP->query_wiz_level()) return;
    set_alarm(itof(PEACE_DELAY+random(5)), -1.0, "peace_attack", TP);
}

public void
peace_attack(object who)
{
    int i;
    
    if (query_hp() <= 0) return;

    tell_room(ETO, QCTNAME(TO) + " looks a bit confused for a while.\n");
    if (who && present(who, ETO))
        command("kill " + who->query_real_name());

    for (i=0; i<sizeof(pend_enemies); i++)
        if (pend_enemies[i] && present(pend_enemies[i], ETO))
            command("kill " + pend_enemies[i]->query_real_name());
}
