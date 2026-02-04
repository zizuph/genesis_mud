/*
 *
 * Dabaayhab the Master Pirate of the Hand
 *
 * Goldberry - February, 2000
 * Last modified:
 *   07242002 Goldberry
 *     Refined the pick pocketing
 *     Various cosmetic changes
 *
 */


#include "/d/Terel/include/Terel.h"
inherit "/lib/unique";
inherit STDMONSTER;

#include <macros.h>
#include <formulas.h>
#include <stdproperties.h>
#include <ss_types.h>
#include <wa_types.h>
inherit "/std/act/action";
inherit "/std/act/seqaction";
inherit "/std/act/domove";

#define KILL_LOG "/d/Terel/dabaay/log/dabaayhab_kills"
#define STEAL_LOG "/d/Terel/dabaay/log/dabaayhab_steals"
#define GEM_DIR "/d/Genesis/gems/obj/"
#define DAB_NPC "/d/Terel/dabaay/npc/"
#define DUNK_MAN "/d/Terel/dabaay/obj/dunk_man"
#define HOLD   "/d/Terel/gsl_ships/last-dabaay/ship/hold"

string *rgems = ({"alexandrite","beryl_red","diamond","emerald","ruby"}),
       *mgems = ({"sapphire","jade","pearl","spinel_blue","aquamarine","bloodstone"}),
       *cgems = ({"moonstone","onyx","topaz","chrysoprase","garnet","turquoise","coral","agate"});

void dress_me();
int react_enter(string who, object owho);
void un_stun(object who);

int SATTACK = 6;

public void
create_monster()
{
    set_name("dabaayhab");
    set_living_name("dabaayhab");
    set_adj("black-haired");
    set_adj("brown-eyed");
    set_race_name("halfling");
    set_alignment((random(300) + 500) * -1);
//    set_title("the Master Pirate of the Hand");
    set_gender(0);
    set_short("black-haired brown-eyed male halfling");
    set_stats(({110+random(30), 
                175+random(30), 
                145+random(20), 
                120+random(20), 
                120+random(20), 
                120+random(30)}));
    set_exp_factor(130);

    set_skill(SS_WEP_KNIFE, 100);
    set_skill(SS_WEP_SWORD, 100);
    set_skill(SS_DEFENCE, 95);
    set_skill(SS_PARRY, 95);
    set_skill(SS_2H_COMBAT, 100);
    set_skill(SS_AWARENESS, 100);
    set_skill(SS_SNEAK, 100);
    set_skill(SS_HIDE, 100);
    set_skill(SS_BACKSTAB, 100);
    set_skill(SS_PICK_POCKET, 85);
    set_skill(SS_BLIND_COMBAT, 85);

    add_prop(LIVE_I_QUICKNESS, random(60) + 95);
    add_prop(OBJ_I_HIDE, 105);
    add_prop(OBJ_M_HAS_MONEY, random(600) + 900);
    set_aggressive("@@attack_big");
    add_cchat("It is a wonder that you have lived so long.");
    add_cchat("You are more foolish than you appear.");
    add_cchat("Arr, you went and got on the wrong boat this time "+
              "didn't you now?");
    add_cchat("There is no escape from the vengeance."); 
    set_cchat_time(2);
    dress_me();
}


void
dress_me()
{
    object unique;

    FIX_EUID;
    clone_object(DABAAY_DIR + "weapon/sdagger")->move(TO);
    clone_object(DABAAY_DIR + "weapon/short")->move(TO);
    clone_object(DABAAY_DIR + "armour/sm_greaves")->move(TO);
    clone_object(DABAAY_DIR + "armour/htunic")->move(TO);
    clone_object(DABAAY_DIR + "armour/hcloak")->move(TO);
    clone_object(DABAAY_DIR + "obj/eyepatch_n")->move(TO);
    clone_object(GEM_DIR + rgems[random(sizeof(rgems))])->move(TO);
    clone_object(GEM_DIR + rgems[random(sizeof(rgems))])->move(TO);
    clone_object(GEM_DIR + mgems[random(sizeof(mgems))])->move(TO);
    clone_object(GEM_DIR + mgems[random(sizeof(mgems))])->move(TO);
    clone_object(GEM_DIR + cgems[random(sizeof(cgems))])->move(TO);
    clone_object(GEM_DIR + cgems[random(sizeof(cgems))])->move(TO);

    unique = clone_unique(DABAAY_DIR + "weapon/ddagger",7,
        DABAAY_DIR + "weapon/short", 1, 20)->move(TO);
    unique->move(TO);

/*
    clone_unique(DABAAY_DIR + "obj/eyepatch",5,DABAAY_DIR + "obj/eyepatch_n")->move(TO);
*/

   

    command("wield steel dagger");
    command("wield sword");
    command("wear all");
}

/* mask the kind of initial attack he makes so he can backstab */
void
aggressive_attack(object ob)
{
    if(!(ENV(TO) == find_object(HOLD)))
    {
       say(QCTNAME(this_player()) + " dissappears in a flurry "+
          "of black velvet!\n");
       write("You are tackled from behind!\n"+
             "You are falling!\n");
       ob->command("$scream");
       ob->move_living("M", HOLD,0,0);
       TO->move_living("M", HOLD,0,0);
       TO->add_prop(OBJ_I_HIDE, 100);
       return;
    }
    command("backstab "+lower_case(ob->query_name())+
    " with dagger");
    tell_room(ENV(TO), "You hear the sounds of blades being drawn.\n",0,TO);
    command("say Your luck has just run out fool!");
    ob->add_panic(random(50) + 225 - ob->query_stat(SS_DIS));
    TO->set_intoxicated(TO->intoxicated_max());
    return;
}

mixed
attack_big()
{
    react_enter(TP->query_name(), TP);
    if(TP->query_prop(HAND_MARK) < 2)
     return 0;
    return 1;
}
    
int
react_enter(string who, object owho)
{
 object *who_stuff = all_inventory(owho);
 mixed *s_stuff;

 int i;
 int n=0;

 mixed targ_steal;
 s_stuff = allocate(sizeof(who_stuff));
   if (!(owho->query_wiz_level()) && !(TO->query_enemy()))
     add_prop(OBJ_I_HIDE, 105);
   if ((random(11) > 7) && (owho->query_average_stat() > 85))
   {
       for (i=0; i<sizeof(who_stuff); i++)
       {
           if ((!(who_stuff[i]->query_prop(OBJ_M_NO_STEAL))) &&
               (!(who_stuff[i]->query_worn())) &&
               (!(who_stuff[i]->query_no_show())) &&
               (!(who_stuff[i]->query_prop(OBJ_M_NO_DROP))) &&
               (!(who_stuff[i]->query_wielded())))
           {
              if (!(who_stuff[i]->query_pname()))
                s_stuff[n] = who_stuff[i]->query_name();
              else
                s_stuff[n] = who_stuff[i]->query_pname();
              n++;
           }
       }   
       if (n)
       {
        targ_steal = s_stuff[random(n+1)];
        command("steal "+targ_steal+" from "+ lower_case(who));
        write_file(STEAL_LOG,"Attempted to steal "+targ_steal+" from "+ who
         + " (" + ctime(time()) + ")\n" ); 
       }
   }
}

void
do_die(object killer)
{
    int i, sdunk;
    string str;
    object *enemies;
    
    if (query_hp() > 0) return;
    enemies = query_my_enemies();
    str = killer->query_name() + "[" + killer->query_average_stat() + "]";
    for (i=0; i<sizeof(enemies); i++) {
       if (enemies[i] != killer)
           str += ", " + enemies[i]->query_name() +
           "[" + enemies[i]->query_average_stat() + "]";
      }
    sdunk = DUNK_MAN->summon_dunker();

    write_file(KILL_LOG, str + " (" + ctime(time()) + ", " + sdunk + ")\n");
    if (killer->query_prop(HAND_MARK) < 3)
       killer->add_prop(HAND_MARK, 3);
      
    if (sdunk)
      killer->catch_tell(
        TO->query_The_name(killer)+ " gasps to you: The hunt continues. "+
        "He comes for you.\n");
    else
      killer->catch_tell(
        TO->query_The_name(killer)+ " gasps to you: The hunt continues. "+
        "He waits for you.\n");
    TO->command("emote struggles vainly for a breath.");
    ::do_die(killer);
}

void
un_stun(object who)
{
    who->remove_stun();
    who->catch_tell("The stunned feeling of the fall seems to have "+
                    "worn off.\n");
}

int
special_attack(object enemy)
{
    mixed* hitresult;
    string how;
    object me;
    int intox,hurt, i, Hand, blind, fnum;
    Hand = 0;

    /* Take them downtown if they ain't already there */
    if(!(ENV(TO) == find_object(HOLD)))
    {
       command("emote hisses angrily.");
       say(QCTNAME(this_player()) + " dissappears in a flurry "+
          "of black velvet!\n");
       write("You are tackled from behind!\n"+
             "You are falling!\n");
       enemy->command("$scream");
       enemy->move_living("M", HOLD,0,0);
       TO->move_living("M", HOLD,0,0);
       enemy->add_stun();
       command("say It is a shame that you are so foolish.");
       command("say I could have made use of your talents.");
       command("say Now you will die, alone.");
       set_alarm(25.0,0.0,"un_stun",enemy);
       return 1;
    }


    if(enemy->query_prop(HAND_MARK))
    {
        Hand = query_prop(HAND_MARK) * 30;
    }
    else
        Hand = 100;

    me = TO;
    blind = TO->query_skill(SS_BLIND_COMBAT);

    if(random(SATTACK) > 8) 
    {
        SATTACK = 6;

        fnum = 40+Hand;

        if (!TO->can_see_in_room() || enemy->query_invis())
          fnum = fnum * blind / 100;

        hurt = F_PENMOD(fnum, fnum);

        hitresult = enemy->hit_me(hurt, W_SLASH, me, -1);

        how = "unharmed";
        if (hitresult[0] > 0)
            how = "slightly hurt";
        if (hitresult[0] > 20)
            how = "rather hurt";
        if (hitresult[0] > 50)
            how = "crushed";
        if (hitresult[0] > 100)
            how = "devastated";

        tell_watcher(QCTNAME(me) + " slashes at " + QCTNAME(enemy) + ".\n",
                             enemy);
        enemy->catch_tell(query_The_name(enemy) + " slashes at you!\n" +
            "You feel " + how + ".\n");

        if (enemy->query_hp() <= 0)
        {
            command("cackle maniacally");
            enemy->do_die(me);
            TO->set_hp(9999);
            TO->move_living("M", SHIP_DIR + "T_DECK",0,0);
            TO->add_prop(OBJ_I_HIDE, 105);

        }
        if (random(2))
        {
         TO->set_intoxicated(TO->intoxicated_max()); 
         command("burp");
        }
        return 1;
    }

    SATTACK++;
    return 0;
}

