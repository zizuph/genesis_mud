/* 
*   Half-Giants village in the pass overhauled.
*   /d/Kalad/common/wild/pass/giantpass/
*   Modified by Meton - 2020
*/

inherit "/d/Kalad/std/active_monster_base.c";
inherit "/d/Kalad/lib/special";
inherit "/d/Kalad/lib/prestige";
inherit "/d/Genesis/specials/npc/stat_based_specials.c";

#include <wa_types.h>
#include "../local.h"
#include <macros.h>
#include "/sys/money.h"
#include <files.h>

inherit LIV + "npc_looting.c";

#define C_OVERWHELMED   "_c_overwhelmed"
int summoning_done;
public int          react_attack(string who, string dummy);
public int          summon_help();
int time_summon;
int second_summon;
int third_summon;

public void         create_giant_living();

/*
* Function name: create_active_monster
* Description  : Constructor. Creates the monster.
*/
nomask void create_active_monster()
{
/* Redefine this function to customize the npcs */
    
    create_giant_living();
    
} /* create_active_monster */

void
create_giant_living()
{
    set_name("giant");
    add_name("_hgiant_friends");
    set_race_name("hill giant");
    set_adj(one_of_list(GIANTADVERBS));
    set_long("A massive humanoid!\n" +
    one_of_list(GIANTDESC) + capitalize(HE(TO)) + " is "
        + one_of_list(HEIGHT) + " and " + one_of_list(WIDTH)
        + " for a Hill Giant.\n");
    set_stats(({175,90,125,75,75,120}));
    set_alignment(-400);
    set_skill(SS_WEP_CLUB,80);
    set_skill(SS_DEFENCE,80);
    set_skill(SS_PARRY,50);
    set_skill(SS_AWARENESS,50);
    set_skill(SS_BLIND_COMBAT,50);
    set_prospective_cluster(({"_hgiant_friends"}));
    set_gender(random(2));
    add_prop(LIVE_I_NEVERKNOWN,1);

    set_act_time(9);
    add_act("smile stupidly");
    add_act("duh");
    add_act("scratch behind");
    add_act("get all from corpse");

    set_cact_time(9);
    add_cact("say Me smash you like bug!");
    add_cact("say Me eat you for dinner!");
    add_speak("You know go away, me want to bash you.\n");

    set_knight_prestige(50);
    add_prop(CONT_I_WEIGHT,2000000);
    add_prop(CONT_I_VOLUME,2000000);
    //Thich skin, easiest pierced, hard to slash, absorbs bludgeon.
    set_all_hitloc_unarmed(({28, 25, 22}));

    equip(({WEP + "gclub",
            ARM + "gfur"}));
    MONEY_MAKE_CC(random(100))->move(TO);

    trig_new("%w 'attacks' %s","react_attack");

    /*  Compare with /d/Kalad/common/noble/npc/house_guards
        guards are at 120 for armour+special
        cbd sets Giants with less hit, almost double pen and more 
        damage reduction.
        */
    set_exp_factor(140);

}

/* Function:         query_my_enemies() : written by Mortricia
* What's it do:     Creates an array of enemies to be used for randomizing
*/
public varargs object *
query_my_enemies(int how_to_sort = 0)
{
    int i, j, swap = 0;
    object foo, *all, *enemies = ({ });
    all = all_inventory(environment(TO)) - ({ TO });
    for (i=0; i<sizeof(all); i++) {
        if (living(all[i]) && member_array(TO, all[i]->query_enemy(-1)) >= 0)
            enemies += ({ all[i] });
    }
    if (how_to_sort == 0) return enemies;
    
    for (i=0; i<sizeof(enemies)-1; i++) {
        for (j=i+1; j<sizeof(enemies); j++) {
            switch (how_to_sort) {
                case -1:     /* Sort in decreasing stat order */
                    if (enemies[i]->query_average_stat() <
                        enemies[j]->query_average_stat()) swap = 1;
                    break;
                case 1:      /* Sort in increasing stat order */
                    if (enemies[i]->query_average_stat() >
                        enemies[j]->query_average_stat()) swap = 1;
                    break;
                default:
                    return enemies;
            }
            if (swap) {
                foo = enemies[i];
                enemies[i] = enemies[j];
                enemies[j] = foo;
                swap = 0;
            }
        }
    }
    return enemies;
}/*query_my_enemies*/


/*
 * Function name: special_attack()
 * Description  : 25% triggers the special attack
 * Arguments    : Enemy = the enemy of the object
 */
 int
 special_attack(object enemy)
 {
    if (second_summon == 0 && query_hp() <= (query_max_hp() / 2))
    {
        second_summon = 1;
        summon_help();
    }
    if (third_summon == 0 && query_hp() <= (query_max_hp() / 3))
    {
        third_summon = 1;
        summon_help();
    }
    if (random(100) >= 25)
    {
        return 0;
    }
    else
    {
        object *ob;
        object *enemies;
        object enemy;
        int i;
        int pen;
        int enemysize2,mysize2,teameffect,propeffect;
        string overwhelmed_message;
        object me;
        mixed* hitresult;
        string how;
        me = this_object();
        
        enemies = query_my_enemies();
        
        if (sizeof(enemies) == 0) return 0;

        enemy = TO->query_attack();

        //getting the amount of teammembers
        enemysize2 = (sizeof(enemy->query_team_others()) + 1);
        mysize2 = (sizeof(TO->query_team_others()) + 1);
        teameffect = mysize2 - enemysize2;

        switch (teameffect)
        {
        case -10..0:
            overwhelmed_message = " with a massive roar, ";
            break;
        case 1:
            propeffect = 5;
            overwhelmed_message = " with a massive roar echoed by "
            + HIS(TO) + " friends, ";
            break;
        case 2..3:
            propeffect = 10;
            overwhelmed_message = " with a bellowing roar by "+ HIM(TO)
            + " and friends, ";
            break;
        case 4..10:
            propeffect = 15;
            overwhelmed_message = " with a stunning roar from all "
            + HIS(TO) +" team, ";
            break;
        default:
            overwhelmed_message = "Please make a bug report.\n";
            break;
        }
        command("special");
        /* Adding the small pen from overwhelmed to damage, not hit*/
        pen = query_pen_by_stat(TO->query_average_stat());
        pen += propeffect;
        hitresult = enemy->hit_me(pen);
        
        switch (hitresult[3])
        {
            case 0..20:
                how = " without effect ";
                break;
            case 21..50:
                how = " softly ";
                break;
            case 51..80:
                how = " hard ";
                break;
            case 81..110:
                how = " very hard ";
                break;
            case 111..140:
                how = " extremely hard ";
                break;
            case 141..170:
                how = " smashingly ";
                break;
            default:
                how = " smashingly ";
                break;
        }
        me -> catch_msg("You attack "+ overwhelmed_message +" and hit "
        + "your foe "+how+me->query_possessive()+"!\n");
        enemy->catch_msg(QCTNAME(me) + " raises " + me->query_possessive()
        + " club" + overwhelmed_message + "and brings it down, hitting "
        + "your body" + how + "before slamming " + me->query_possessive()
        + " " + query_weapon(-1)[0]->short() + " into the ground.\n"); 
        tell_watcher(QCTNAME(me) + " raises " + me->query_possessive()
        + " club " + overwhelmed_message + "and brings it down, hitting "
        + QTNAME(enemy) + "'s body" + how
        + "before slamming " + me->query_possessive() + " "
        + query_weapon(-1)[0]->short()
        + " into the ground.\n", enemy);

        if (enemy->query_hp() <= 0)
        {
            enemy->do_die(me);
            return 1;
        }
    }
    return 1;
}

/*
*   Function name:        react_attack
*   Description  :        This function will be called if someone
*                       is attacked.
*   Arguments    :        string who, string dummy
*   Returns      :        1
*   Copied from Lord Urian of Kabal.
*
*/
public int
react_attack(string who, string dummy)
{
    string *str_check;
    if(who){
        who = lower_case(who);
        str_check = explode(dummy, " ");
        if (sscanf(str_check[0],"you%s",dummy))
        {
            set_alarm(0.0,0.0,"summon_help",who);
            return 1;
        }
        return 1;
    }
}

/*
*   Function name:        summon_help
*   Description  :        Summons a goblin and a wolf.
*   Arguments    :        
*   Returns      :        0
*
*/
public void
summon_help()
{
    
    if (time() - time_summon < 5)
    {
        return 0;
    }
 
    if (summoning_done < 3)
    {
        object goblin, wolf, enemy;
        enemy = this_object()->query_attack();

        tell_room(E(TO), "The giant whistles loudly.\n");
        summoning_done += 1;
        setuid();
        seteuid(getuid(TO));
        goblin = clone_object(LIV + "goblinraider.c");
        goblin->move_living("M", E(TO));
        tell_room(E(TO),"A goblin raider rides in on a wolf to help "
        + "the giant!\n");
        goblin->command("$kill " + enemy->query_name());
        wolf = clone_object(LIV + "hgwolf.c");
        wolf->move_living("M", E(TO),1,1);
        wolf->command("$kill " + enemy->query_name());
        time_summon = time();
        return 0;
    }
    return 0;
}