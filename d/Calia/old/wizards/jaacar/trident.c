
 /* 
  * Golden trident for the Ruler of Thalassia
  * by Jaacar
  *
  */

inherit "/std/weapon";

#include <filter_funs.h>
#include <stdproperties.h>
#include <wa_types.h>
#include <ss_types.h>
#include <macros.h>
#include <formulas.h>
#include <options.h>
#include "/d/Calia/abbrev.h"

object wielder;

void
create_weapon()
{
    set_name("trident");
    set_short("golden trident");
    set_long("It is a very large golden trident.  You can see it "+
        "pulsing with power.  The shaft is decorated with cryptic "+
        "runes which you do not understand.\n");
    set_adj("golden");
    add_item("cryptic runes","These runes are written in an ancient "+
        "language that you just can't seem to understand.\n");
    set_hit(60);
    set_pen(60);
    set_wt(W_POLEARM);
    set_dt(W_IMPALE);
    set_hands(W_BOTH);
    set_wf(TO);
   
    add_prop(OBJ_I_VALUE, F_VALUE_WEAPON(35,54) + 1500);
    add_prop(OBJ_I_WEIGHT, 28000);
    add_prop(OBJ_I_VOLUME, 8000);
    add_prop(OBJ_I_IS_MAGIC_WEAPON, 1);
    add_prop(OBJ_M_NO_BUY,1);
    add_prop(MAGIC_AM_MAGIC,({40, "enchantment"}));
    add_prop(MAGIC_AM_ID_INFO,({"This weapon enchanted to only allow "+
        "a person with certain attributes to wield it.",10,
        "The wielder must have great strength and skill to use "+
        "this weapon.  It is also especially effective against certain types "+
        "of foes.",25,
        "The user must have titanic strength and the "+
        "polearm skill of a master journeyman to wield this "+
        "magnificent weapon of kroug slaying.",50}));

    add_prop(OBJ_S_WIZINFO,"The user must have a 100 str and a 50 "+
        "polearm to wield this.  It does extra (10-40%) damage to "+
        "krougs.\n");

    seteuid(getuid(TO));
}

static void
tell_watcher(string str, object enemy)
{
    object wielder, *ob;
    int i;

    wielder = query_wielded();
    ob = FILTER_LIVE(all_inventory(environment(wielder))) - ({ wielder });
    ob -= ({ enemy });
    for (i = 0; i < sizeof(ob); i++)
            ob[i]->catch_msg(str);
}

int
did_hit(int aid,string hdesc,int phurt,object enemy,int dt,int phit,int dam)
{
   
    if ((enemy->query_race_name() == "kroug") ||
        (enemy->query_race_name() == "water-kroug"))
    {
        enemy->heal_hp(-(((dam*(random(4)+1))/10)));
    }

    switch(phurt)
        {
        case -1:
            wielder->catch_msg("You thrust your golden trident, just "+
                "barely missing "+QTNAME(enemy)+".\n");
            enemy->catch_msg(QCTNAME(wielder)+"'s golden trident thrusts at "+
                "you forcefully.  You barely manage to escape its blow.\n");
            tell_watcher(QCTNAME(wielder)+"'s golden trident barely "+
                "misses "+QTNAME(enemy)+".\n",enemy);
            break;

         case 0:
             wielder->catch_msg("You thrust the trident very close to " +
                 QTNAME(enemy) + ", only narrowly missing your victim.\n");
             enemy->catch_msg(QCTNAME(wielder) + " thrusts the trident "+
                "very close to you, only narrowly missing you.\n");
             tell_watcher(QCTNAME(wielder) + " thrusts the trident "+
                "at " + QTNAME(enemy) + " and narrowly misses.\n", enemy);
             break;

         case 1..4:
             wielder->catch_msg("You graze the flesh of "+
                 QTNAME(enemy)+" with your golden trident.\n");
             enemy->catch_msg(QTNAME(wielder)+" grazes your flesh "+
                 "with "+wielder->query_possessive()+" golden trident.\n");
             tell_watcher(QTNAME(wielder)+" grazes the flesh of "+
                 QTNAME(enemy)+" with "+wielder->query_possessive()+" golden "+
                 "trident.\n",enemy);
             break;
         
         case 5..9:
             wielder->catch_msg("You violently slash the skin of "+QTNAME(enemy)+
                 " with your golden trident.\n");
             enemy->catch_msg(QCTNAME(wielder)+" violently slashes your skin "+
                 "with "+wielder->query_possessive()+" golden trident.\n");
             tell_watcher(QCTNAME(wielder)+ " violently slashes "+QTNAME(enemy)+
                 "'s skin with "+wielder->query_possessive()+" golden "+
                 "trident.\n",enemy);
             break;
         
         case 10..14:
             wielder->catch_msg("Your golden trident glows brightly as "+
                 "it cuts deeply into "+QTNAME(enemy)+".\n");
             enemy->catch_msg("You see "+QTNAME(wielder)+"'s golden trident glow "+
                 "brightly as it cuts deeply into you.\n");
             tell_watcher("You see "+QTNAME(wielder)+"'s golden trident "+
                 "glow brightly as it cuts deeply into "+
                 QTNAME(enemy)+".\n",enemy);
             break;
         
         case 15..19:
             wielder->catch_msg("Your golden trident vibrates rapidly as it "+
                 "tears a large gash in "+QTNAME(enemy)+"'s side.\n");
             tell_watcher(QTNAME(wielder)+"'s golden trident vibrates rapidly "+
                 "as it tears a large gash in "+QTNAME(enemy)+"'s "+
                 "side.\n",enemy);
             enemy->catch_msg(QCTNAME(wielder)+"'s golden trident vibrates rapidly "+
                 "as it tears a large gash in your side.\n");
             break;
         
         case 20..24:
             wielder->catch_msg("Your golden trident seems to come to life "+
                 "and burrows itself far within "+QTNAME(enemy)+"'s body.\n");
             enemy->catch_msg(QCTNAME(wielder)+"'s golden trident seems to come "+
                 "to life and burrows itself far within your body.\n");
             tell_watcher(QCTNAME(wielder)+"'s golden trident seems to come to "+
                 "life as it burrows itself far within "+QTNAME(enemy)+
                 "'s body.\n",enemy);
             break;
         
         case 25..30:
             wielder->command("cackle sadistically");
             wielder->catch_msg("You thrust the golden trident into "+
                 QTNAME(enemy)+"'s chest, leaving large, gaping wounds.\n");
             enemy->catch_msg(QCTNAME(wielder)+" thrusts "+
                 wielder->query_possessive()+" golden trident into your chest, "+
                 "leaving large, gaping wounds.\n");
             tell_watcher(QCTNAME(wielder)+" thrusts "+wielder->query_possessive()+
                 " golden trident into "+QTNAME(enemy)+"'s chest, leaving "+
                 "large, gaping wounds.\n",enemy);
             break;
         
         case 31..50:
             wielder->command("shout Die! Die! DIE!");
             wielder->command("laugh violently");
             wielder->catch_msg("You laugh out loud as your golden trident "+
                 "rams into the arm of "+QTNAME(enemy)+".\n");
             enemy->command("scream");
             enemy->catch_msg("You scream out in pain as "+QTNAME(wielder)+
                 "'s golden trident rams itself into your arm.\n");
             tell_watcher(QCTNAME(enemy)+" screams out in pain as "+
                 QTNAME(wielder)+"'s golden trident rams into "+
                 QTNAME(enemy)+"'s arm.\n",enemy);
             break;
         
         default:
             wielder->catch_msg("You thrust your trident heartlessly into "+
                 QTNAME(enemy)+"'s head, causing it to glow very brightly.\n");
             enemy->catch_msg(QCTNAME(wielder)+" heartlessly thrusts "+
                 wielder->query_possessive()+" trident into your head, causing "+
                 "it to glow very brightly.\n");
             tell_watcher(QCTNAME(wielder)+" heartlessly thrusts "+
                 wielder->query_possessive()+" golden trident into "+QTNAME(enemy)+
                 "'s head, causing it to glow very brightly.\n",enemy);
             break;
        }
        if(enemy->query_hp()<=0)
        {
            enemy->command("scream");
            enemy->catch_msg(QCTNAME(wielder)+" drives "+wielder->query_possessive()+
                " golden trident right through the centre of your body, "+
                "causing you to go into massive convulsions before dying.\n"+
                QCTNAME(wielder)+" coldly pushes your lifeless body off "+
                wielder->query_possessive()+" trident with "+
                wielder->query_possessive()+" foot.\n");
            wielder->catch_msg("You drive your trident right through the "+
                "centre of "+QTNAME(enemy)+", causing them to go into "+
                "massive convulsions before dying.\nYou coldly push "+
                "the corpse off of your trident with your foot.\n");
            tell_watcher(QCTNAME(wielder)+" drives "+wielder->query_possessive()+
                " golden trident right through the centre of "+
                QTNAME(enemy)+" causing them to go into massive convulsions "+
                "before dying.\n"+QCTNAME(wielder)+" coldly pushes the corpse "+
                "off of "+wielder->query_possessive()+" trident with "+
                wielder->query_possessive()+" foot.\n",enemy);
            enemy->do_die(wielder);
        }
    return 1;
}

mixed
wield(object ob)
{
    if(ob!=TO)
        return 0;
   
    if(TP->query_base_stat(SS_STR)>99)
    {
        if(TP->query_skill(SS_WEP_POLEARM)>49)
        {
            wielder = this_player();
            write("You struggle momentarily, then take control of "+
                "the golden trident.\n");
            return 0;
        }
    }
    TP->heal_hp(-random(50)-20);
    return "You are burned severely trying to wield this weapon!\n";
}


query_recover()
{
    return MASTER+":"+query_wep_recover();
}

init_recover(arg)
{
    init_wep_recover(arg);
}

