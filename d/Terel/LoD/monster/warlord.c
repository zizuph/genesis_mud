/* This comment tells emacs to use c++-mode  -*- C++ -*- */

/*
 * Mergula, the evil warlord.
 * Cloned to /d/Terel/LoD/war2.c
 *
 * Coded by Mortricia 931205.
 * updated by Lilith  050629.
 *
 * Modified by Lilith 5 July 2008
 *  -Updated and reimplemented Mergula.
 *   He was taken out about 10 years ago pending implementation
 *   of Maskyr Keep. Maskyr Keep is unrealized, and people miss
 *   the thrill of fighting Mergula, so he's back. Gods help em.
 *
 * Modified by Lilith 8 Aug 2008
 *  Eased up on the magic damage a bit
 *  Reduced the amount he heals
 *
 * Modified by Lilith Feb 2009
 *   updated add_stun so that it is actually removed.
 *
 * Modified by Lilith March 2009
 *   cloning magical items from the /d/Terel/unique/* dir now.
 *
 * Modified by Arman September 2017
 *   added a check in enter_env for query_no_show() to avoid
 *   spell objects and shadows from being dropped.
 *
 * Modified by Lilith Nov 2021
 *    updated SS_UNARM_COMBAT in preparation for unarm enhancing boots.
 *
 * Modified by Zizuph Dec 2021
 *    updated weapon special to be dull, rather than corrode.
 *
 * Modified by Lilith Feb 2022
 *    removed added magic resistance since the combat system now
 *    autocalcs it based on AC.
 *
 * Modified by Lilith Jun 2022
 *   added checks to his break armour and break weapon effects that
 *   check for OBJ_I_IS_MAGIC_ARMOUR and OBJ_I_IS_MAGIC_WEAPON
 *   since some things don't have MAGIC_AM_MAGIC set or are losing
 *   that prop.
 *
 */

#include "/d/Terel/include/Terel.h"
inherit STDMONSTER;
inherit "/lib/unique";
inherit "/std/act/action";
inherit "/std/act/seqaction";
inherit "/std/act/domove";
inherit "/d/Terel/mortricia/global/skill_support";

#include <files.h>
#include <ss_types.h>
#include <wa_types.h>
#include <money.h>
#include <language.h>

#define ALIGN           -500
#define BASE_SIZE       225
#define SPELL_DELAY     (15 + random(11))
#define PEACE_DELAY     5
#define KILLER          "_wl_killer"
#define PARA_OBJ        "/std/paralyze"
#define PARA_TIME       10
/* FRAC OBJ IS BUGGED
#define FRAC_OBJ        "/d/Terel/sorgum/fracture"
*/
#define MAX_HELP        2

#define OBJ_DIR         LOD_DIR + "obj/"
#define ARM_DIR         LOD_DIR + "armour/"
#define WEP_DIR         LOD_DIR + "weapon/"


#define DRINK           OBJ_DIR + "ew_drink"
#define SPEED           OBJ_DIR + "ew_speed"

#define BRIEFS          ARM_DIR + "ew_briefs"
#define CLOAK           ARM_DIR + "ew_cloak"

#define BOOTS           MAGIC_DIR + "ew_mboots"
#define HELMET          MAGIC_DIR + "ew_mhelmet"
#define GLOVES          MAGIC_DIR + "ew_mgloves"
#define MAIL            MAGIC_DIR + "ew_mmail"
#define SWORD           MAGIC_DIR + "ew_sword"

#define KILL_LOG        "/d/Terel/log/mergula_kills"

void set_spell_prop(object ob);
void bring_back_sword();
void break_weapon(object ob);
void break_armour(object ob);
void hurt_all_enemies();
void hurt_random_enemy();
void slow_down_enemy();
void ew_attack(object enemy, int wc_pen);
void call_for_help();
void cure_from_poison();
public void paralyze_enemy();
public nomask void peace_attack(object who);
void check_combat();
void drop_obj(object ob);

static object *pend_enemies;
object sword;
int no_help=0;
int prop_check=0;
int been_attacked=0;

void
init_living()
{
    ::init_living();
}

void
create_monster()
{
    set_name("mergula");
    add_name("warlord");
    set_living_name("mergula");
    set_title("the Warlord of the Legion of Darkness");
    set_long("It is a cold cruel-looking male human.\n"+
        "He has the malevolent look of one who takes "+
        "delight in the pain of others. "+
        "A giant amongst men, he is twice " +
        "as large as any other human you have seen before.\n" +
        "Judging by his appearance, you conclude that he "+
        "can only be the infamous Mergula, evil "+
        "warlord of the Legion of Darkness. Based upon "+
        "his reputation for fighting dirty, it would be "+
        "prudent to leave before he takes too much notice "+
        "of you.\n");

    set_adj(({"cruel-looking", "cold"}));
    set_race_name("human");
    set_gender(MALE);
    set_assist("officer");

    default_config_npc(random(25) + BASE_SIZE);

    SET_MAX_HP;
    SET_MAX_MANA;
    set_alignment(ALIGN);
    set_all_hitloc_unarmed(40);
    set_skill(SS_DEFENCE,      125);
    set_skill(SS_WEP_SWORD,    125);
    set_skill(SS_PARRY,        100);
    set_skill(SS_BLIND_COMBAT, 100);
    set_skill(SS_UNARM_COMBAT, 125);
    set_skill(SS_2H_COMBAT, 95);
    set_skill(SS_AWARENESS, 99);

    set_ss_skill("SPELL",   ({99, 50, 50}));
    set_ss_skill("FORM",    ({99, 80, 25, 50, 50, 50}));
    set_ss_skill("ELEMENT", ({99, 50, 55, 55, 50, 80}));

    add_prop(OBJ_I_RES_POISON,   75);
    add_prop(OBJ_I_RES_IDENTIFY, 55);

    add_prop(LIVE_I_SEE_DARK,   99);
    add_prop(LIVE_I_QUICKNESS, 100);
    add_prop(LIVE_I_NO_CORPSE,   1);
    
    add_prop(CONT_I_WEIGHT,     90000);
    add_prop(CONT_I_VOLUME,     90000);
    add_prop(CONT_I_HEIGHT,        240);

    add_prop(NPC_I_NO_FEAR,      1);
    add_prop(NPC_I_NO_LOOKS,     1);
    add_prop(NPC_I_NO_RUN_AWAY,  1);
    add_prop(BOSS_NPC,           1);
    
    remove_prop(NPC_M_NO_ACCEPT_GIVE);

    trig_new("%s 'introduces' %s", "intro_me");

    set_act_time(15);
    add_act(({"say Now, where is that map?", "frown", "ponder"}));
    add_act("grumble");
    add_act(({"say I did not come all this way from Maskyr Keep to "+
        "stand here and smell the stink of your farts.", "say We "+
        "have preparations to make for this Summer's advance."}));
    add_act("smile cold");
    add_act(({"say We should expand the soldiers quarters here.",
        "say I plan to move a batallion in as soon as Spring "+
        "melt arrives."})); 
    add_act("smile slow");
    add_act("growl");
    add_act("say The cold day in Hell has come.");
    add_act("@@check_combat@@");
 
    set_cact_time(5);
    add_cact("@@check_combat@@");

    set_exp_factor(175);

    set_alarm(2.0, -1.0, "set_spell_prop",  TO);
    prop_check = 1;
    equip_me();
}

void
equip_me()
{
    object ob;
    ::equip_me();
    FIX_EUID;

    MONEY_MAKE_PC(20+random(6))->move(TO);
    MONEY_MAKE_GC(50)->move(TO);
    
    clone_object(CLOAK)->move(TO);
    clone_object(BRIEFS)->move(TO);
 
    ob = clone_unique(MAIL, 4, ARM_DIR +"ew_mail_alt");
    ob->move(TO);
    ob = clone_unique(GLOVES, 4, "/d/Genesis/gems/obj/diamond_black");
    ob->move(TO);
    ob = clone_unique(HELMET, 4, ARM_DIR + "ew_helmet");
    ob->move(TO);
    ob = clone_unique(BOOTS, 4, ARM_DIR + "evil_boots");
    ob->move(TO);

    command("wear all");
   

    /* 90% chance of the sword being magical. Max 4 clones. */
    sword = clone_unique(SWORD, 4, "/d/Terel/LoD/weapon/deaths_sword", 1, 90);
    sword->move(TO);
    sword->add_prop(KILLER, TO->query_name());
    command("wield sword");

}

/*
 * Function name:   check_combat()
 * Description:     This function resets npc if not in combat
 *                  so smaller players don't get hammered.
 * Arguments:       
 * Notes:           called through add actions 
 */ 
void
check_combat()
{
    if (!objectp(query_attack()))
    {
        been_attacked = 0;
        no_help = 0;
    }

    /* If the fight has been going on for less than 3 mins, heal */
    if ((time() - been_attacked) < 239)
        TO->heal_hp(query_max_hp() / 6);

    /* If he does get stunned, the ck might not be called, so.. */ 
        cure_from_poison();
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
      break_weapon(victim);
    } else if (spell == 4) {
      break_armour(victim);
    } else if (spell == 5) {
      paralyze_enemy();
    } else if (spell == 6) {
      seteuid(getuid());
      if (!present("rum", TO))           
          clone_object(DRINK)->move(TO);
      command("drink rum");
      heal_hp(200+random(100));
      cure_from_poison();
      if (sword && sword->query_wielded() != TO)
          bring_back_sword();
    }
    call_for_help();
    set_alarm(itof(2+random(SPELL_DELAY)), -1.0, "set_spell_prop",  me);
    return;
}

void
bring_back_sword()
{
    object where;

    if (sword->query_prop(KILLER) != query_name())
         return;

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

/* This function has been updated to use more checks.
 * -- Lilith, June 2005
 */
void
break_weapon(object ob)
{
    object *all, fracture;
    int i;

    all = all_inventory(ob);

    for (i=0; i<sizeof(all); i++) 
    {
        if (!function_exists("create_weapon", all[i]))
             continue;
        if (all[i]->query_wielded() == ob) 
        {
            command("kick "+ ob->query_real_name() +" swift");
            ob->catch_msg("The swift kick connects with your " +
                all[i]->short() + ".\n");

            /* If magical, wear it down, don't break it */
			// added check for magic_weapon, too.--Lilith June 2022
            if (all[i]->query_prop(MAGIC_AM_MAGIC) ||
                all[i]->query_prop(OBJ_I_IS_MAGIC_WEAPON))
            {
                all[i]->set_dull(all[i]->query_dull() + 1);
                continue;
            }
            all[i]->remove_broken();

/*           Fracture is buggy.
 *           if (random(5) == 0 && !present("fracture", ob)) 
 *           {
 *               fracture = clone_object(FRAC_OBJ);
 *               fracture->add_prop(OBJ_M_NO_DROP,  
 *                   "Huh? Wanna lose your limb?\n");
 *               fracture->move(ob);
 *           }
 */
            ob->hit_me(200, MAGIC_DT, TO, -1);
            return;
        }
    }
}

/* This function has been updated to use more checks
 * -- Lilith, June 2005
 */
void
break_armour(object ob)
{
    object *all;
    int i;

    all = all_inventory(ob);

    for (i=0; i<sizeof(all); i++) 
    {
        if (!function_exists("create_armour", all[i]))
           continue;
        if (all[i]->query_worn() == ob) 
        {
			// Added ck for magic armour, too, since some items are 
			// missing the magic_am_magic prop
            if ( (all[i]->query_prop(OBJ_I_IS_MAGIC_ARMOUR)) ||
                 (all[i]->query_prop(MAGIC_AM_MAGIC)) ||
                 (all[i]->query_ac() < 10) || (all[i]->query_ac() > 40))
                continue;
            command("kick "+ ob->query_real_name() +" forcef");
            ob->catch_msg("The forceful kick squarely hits your " +
                all[i]->short() + ".\n");
            all[i]->remove_broken();
            return;
        }
    }
	
    command("kick "+ ob->query_real_name() +" deliber");
    ob->catch_msg("The kick lands on your solar plexus. "+
        "You hear a cracking noise and feel a sharp pain in your chest!\n");
    i = 600 + random(100) - ob->query_stat(SS_CON);
    if (i<100) i = 100;
    ob->hit_me(i, MAGIC_DT, TO, -1);
}

void
hurt_all_enemies()
{
    int i, dam;
    object *all;

    all = query_my_enemies();

    for (i=0; i<sizeof(all); i++) 
    {
        dam = (all[i]->query_alignment());
        if (dam < 100)
           dam = 100;
        if (dam > 1000)
           dam = 1000;
        if (sword && environment(sword) != TO) dam *= 2;
        command("stare malev at " + all[i]->query_real_name());
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

    dam = (enemy->query_max_hp() / 10);
    if (sword && environment(sword) != TO) dam *= 2;
    command("stare malev at " + enemy->query_real_name());
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
    for (i=0; i<sizeof(all); i++) 
    {
        if (MASTER_OB(all[i]) == SPEED) 
        {
            command("eyebrow " + enemy->query_real_name());
            break_weapon(enemy);
            return;
        }
    }
    time  = 120;
    time -= enemy->query_magic_res(MAGIC_I_RES_DEATH);
    time = time / 2;
    if (time <= 0) return;

    command("laugh malic at " + enemy->query_real_name());

    seteuid(getuid());
    speed = clone_object(SPEED);
    speed->set_duration(time);
    speed->set_quickness(-250);  /* Half as fast */
    speed->move(enemy);
}

void
set_spell_prop(object ob)
{
    prop_check = 0;
    if (!query_prop(LIVE_O_SPELL_ATTACK))
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
    command("grin slow");
}

void
enter_inv(object ob, object old)
{
    ::enter_inv(ob, old);

    if(ob->query_no_show())
	return;

    if (!old || !living(old)) 
        return;

    set_alarm(2.0, 0.0, &drop_obj(ob));
}

void
drop_obj(object ob)
{
    if (!objectp(ob))
        return;

    if (IS_WEAPON_OBJECT(ob) || IS_ARMOUR_OBJECT(ob))
    {
        if (ob == sword && ob->query_prop(KILLER) == query_name()) 
        {
            if (ob->query_prop(OBJ_I_BROKEN)) 
            {
                tell_room(ETO, QCTNAME(TO) +
                    " kisses the blade of his "+ ob->short() +
                    ".\n", TO);
                ob->remove_prop(OBJ_I_BROKEN);
            }
            command("wield sword");
            command("laugh evilly");
            return;
        }
        if (!(ob->query_prop(OBJ_I_BROKEN))) 
        {
            tell_room(ETO, QCTNAME(TO)+" breaks the "+ob->short()+
                 " with his left hand!\n", TO);
            ob->remove_broken(1);
        }
        command("grin evilly");
    }
    ob->move(ETO);
    tell_room(ETO, QCTNAME(TO)+" drops "+LANG_ASHORT(ob)+".\n", TO);
}

void
ew_attack(object enemy, int wc_pen)
{
    mixed *hres;
    string how;
    int dam;
   
    dam = (3*wc_pen + 3*random(400))/2;

    if (dam > 800) dam = 800;

    hres = enemy->hit_me(dam, MAGIC_DT, TO, -1);
    how = "seem unaffected";
    if (hres[0] > 0) how = "get a slight headache";
    if (hres[0] > 50) how = "get a headache";
    if (hres[0] > 100) how = "feel an aching pain in your head";
    if (hres[0] > 250) how = "feel an intense pain in your head";
    if (hres[0] > 350) how = "feel a terrible pain in your head";
    if (hres[0] > 500) how = "get an unbearable pain in your head";
    if (hres[0] > 750) how = "get an blinding pain in your head";   
    enemy->catch_msg("You "+how+" as "+QTNAME(TO)+" stares at you.\n");
    if (hres[0] > 250) 
    {
        tell_room(environment(enemy),
             QCTNAME(enemy) + " trembles in fear and pain.\n",
                  ({TO, enemy}));
        enemy->add_panic(hres[0]/3);
    }
    /* heal me part of what I hurt them */
    TO->heal_hp(hres[0]/3);   
    return;
}

void
do_die(object killer)
{
    int i;
    string str;
    object *enemies;
    
    if (query_hp() > 0) return;
    
    if (sword && sword->query_wielded() == TO) 
    {
        tell_room(ETO, QCTNAME(TO) +
            " kisses the blade of his "+ sword->short() +
            ".\n", TO);
        if (sword->query_prop(OBJ_I_BROKEN))
            sword->remove_prop(OBJ_I_BROKEN);
        if (killer && ETO == environment(killer)) 
        {
            sword->change_prop(KILLER, killer->query_real_name());
            killer->catch_msg(QCTNAME(TO) + 
                " salutes you with his " +
                sword->short() + " as he dies.\n");
            tell_room(ETO, QCTNAME(TO) + " salutes "+
                QTNAME(killer) + " with his sword "+ 
                " as he dies.\n", ({TO, killer}));
        }
        command("drop sword"); 
    }
    command("sigh");
    enemies = query_my_enemies();
    str = killer->query_name() + "[" + killer->query_average_stat() + "]";
    for (i=0; i<sizeof(enemies); i++) 
    {
      if (enemies[i] != killer)
          str += ", " + enemies[i]->query_name() +
                 "[" + enemies[i]->query_average_stat() + "]";
    }
    write_file(KILL_LOG, ctime(time()) +" by "+ str +"\n");
    
    ::do_die(killer);
}

void
call_for_help()
{
    object *enemies, knight;

    enemies = query_my_enemies();
    if (sizeof(enemies) == 0) 
    {
        add_panic(-query_panic());
        return;
    }

    if (query_hp() > query_max_hp() / 2)         
         return;

    if (no_help >= MAX_HELP) 
    {
        command("shout Knights! Attend me!");
        if (query_panic() < 100) command("panic");
        hurt_random_enemy();
        no_help++;
        return;
    }

    if (no_help == 0) 
    {
        command("shout Knight! Believe it or not, I need " +
                "help at once!");
        TO->heal_hp(query_max_hp() / 20);
    } else {
        command("shout Knight! Come to my aid! " +
                "These bastards are tough!");
    }
    FIX_EUID;
    knight = clone_object(LOD_DIR + "monster/devil_knight");
    knight->equip_me();
    knight->move_living("M", ETO);
    tell_room(ETO, QCTNAME(knight) + " arrives.\n");
    knight->equip_actions();
    knight->command("gasp");
    knight->help_the_boss(TO);
    knight->attack_someone();
    no_help++;
}

void
cure_from_poison()
{
    int i;
    object *all;

    all = all_inventory(TO);
    for (i=0; i<sizeof(all); i++) 
    {
        if (function_exists("cure_poison", all[i]) ==
            "/std/poison_effect") 
        {
            all[i]->cure_poison(({"all"}), 100);
            command("say Who's trying to poison me?");
            command("say Poison has little effect on me...");
            command("laugh evilly");
            hurt_all_enemies();
            return;
        }
    }
    all = all_inventory(TO);
    for (i=0; i<sizeof(all); i++) 
    {
        if (function_exists("stop_paralyze", all[i]) == "/std/paralyze") 
        {
            all[i]->stop_paralyze();
            command("say You thought you could slow me down?");
            command("say HA! Come here you miserable boot-licking worm!");
            command("smile cruel");
            hurt_all_enemies();
            return;
        }
    }

    /* Some guilds use these props to slow people down */
    remove_stun();
    TO->remove_prop(LIVE_I_STUNNED);
    add_prop(LIVE_I_QUICKNESS, 100);

    /* Some guilds use these props to blind people */
    TO->remove_prop(LIVE_I_SEE_INVIS);
    TO->remove_prop(LIVE_I_SEE_DARK);
    add_prop(LIVE_I_SEE_DARK,   99);

    if ((TO->query_max_hp() / 3) < TO->query_hp())
        TO->heal_hp(query_max_hp() / 20);

    if (random(3))
    {
       command("shout A rain of death and pain upon all who challenge me!");
       hurt_all_enemies();
    }
    return;
}

public int
query_knight_prestige()
{
    return 200;
}

void
remove_mstun(object enemy)
{
    enemy->remove_stun();
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
    for (i=0; i<sizeof(all); i++) 
    {
        if (MASTER_OB(all[i]) == PARA_OBJ) {
            command("kick " + enemy->query_real_name());
            break_weapon(enemy);
            return;
        }
    }

    time  = PARA_TIME + random(10);
    time -= random(enemy->query_magic_res(MAGIC_I_RES_DEATH));
    if (time <= 10) 
        time = 10;
    time = time + random(time);

    command("grin evilly at " + enemy->query_real_name());

/* This is not working, but that is ok, I think paralyze is too deadly
 * Using add_stun() instead. -- Lilith
 *    seteuid(getuid(TO));
 *   para = clone_object(PARA_OBJ);
 *   para->set_no_show();
 *   para->add_prop(OBJ_M_NO_DROP, 1);
 *   para->set_stop_verb("");
 *   para->set_remove_time(time);
 *   para->set_stop_object(0);
 *   para->set_stop_message("You are no longer paralyzed by the pain.\n");
 *   para->set_fail_message("You are still paralyzed by the pain.\n");
 *   para->move(enemy);
 */

    enemy->add_stun();
    enemy->catch_msg(QCTNAME(TO) +
                     "'s overwhelming appearance paralyzes you!\n");
    tell_room(ETO, QCTNAME(enemy) + " becomes paralyzed when " +
              QTNAME(TO) + " grins at " + enemy->query_objective() + ".\n",
              ({enemy, TO}));
    /* do this or the stun stays with player until they leave combat or the room */
    set_alarm(itof(time), 0.0, &remove_mstun(enemy));
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
/*
public nomask int
add_prop_live_i_quickness()
{
    if (prop_check) return 1;
    return 0;
}
*/
public nomask int
remove_prop_live_i_quickness()
{
    if (prop_check) return 1;
    return 0;
}

public nomask void
stop_fight(mixed elist)
{
    if (TP->query_wiz_level()) {
        ::stop_fight(elist);
        return;
    }
    pend_enemies = query_my_enemies();
    ::stop_fight(elist);
    set_alarm(itof(PEACE_DELAY+random(5)), -1.0, "peace_attack", TP);
}

public nomask void
peace_attack(object who)
{
    int i;
    
    if (query_hp() <= 0) return;

    tell_room(ETO, QCTNAME(TO) + " looks a bit confused for a while.\n");

    for (i=0; i<sizeof(pend_enemies); i++)
        if (pend_enemies[i] && present(pend_enemies[i], ETO))
            command("kill " + pend_enemies[i]->query_real_name());

    if (who && present(who, ETO))
        command("kill " + who->query_real_name());
}

public void
notify_spell_enemy_gone(object enemy)
{
    set_alarm(itof(2+random(SPELL_DELAY)), -1.0, "set_spell_prop", TO);    
}

/*
 * Function name:   attacked_by
 * Description:     This routine is called when we are attacked.
 * Arguments:       ob: The attacker
 */
void
attacked_by(object ob)
{
   object *arr;
   object officer;
   int i;
   
   ::attacked_by(ob);
   
   arr = (object *)query_team_others();
   for (i = 0; i < sizeof(arr); i++)
       arr[i]->notify_ob_attacked_me(this_object(), ob);

    if (!been_attacked)
    {
        been_attacked = time();
        write_file(KILL_LOG, ctime(time()) + " was attacked.\n");
    }

}
