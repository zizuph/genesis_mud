/*
 * What         : Base file for Krynn minotaurs from different tribes
 * Description  : Contains a standard special attack.
 * Made by      : Cherek, Feb 2007
 */

#include "/d/Krynn/common/defs.h"
#include <ss_types.h>
#include <wa_types.h>
#include <filter_funs.h>
#include <macros.h>
#include <money.h>
#include "../local.h"

inherit M_FILE

string TYPE;
int gender = random(2);

/*
 * Function name: set_type
 * Description  : Is called in the minotaur file and sets its type,
 *                different types of minotaurs get different type of
 *                special attack.
 */

public void
set_type(string str)
{
    TYPE = str;
    switch (TYPE)
    {
         case "CHIEFTAIN":
             {
               set_stats(({ 143 + random(20), 
                            120 + random(20), 
                            150 + random(20), 
                             90 + random(20), 
                             50 + random(20), 
                            100 + random(20) }));
               set_skill(SS_PARRY, 72);
               set_skill(SS_DEFENCE, 72);
               set_skill(SS_WEP_SWORD, 96);
               set_skill(SS_WEP_AXE, 96);
               set_skill(SS_AWARENESS, 50);
               set_skill(SS_UNARM_COMBAT,96); 
               set_skill(SS_BLIND_COMBAT, 70);
               set_all_hitloc_unarmed(24); 
             }
             break;

         case "SAGE":     
             {
               set_stats(({ 132 + random(20), 
                            96 + random(20), 
                            132 + random(20), 
                             96 + random(20), 
                             96 + random(20), 
                            132 + random(20) }));
               set_skill(SS_PARRY, 72);
               set_skill(SS_DEFENCE, 72);
               set_skill(SS_WEP_SWORD, 96);
               set_skill(SS_WEP_AXE, 96);
               set_skill(SS_AWARENESS, 50);
               set_skill(SS_UNARM_COMBAT,96); 
               set_skill(SS_BLIND_COMBAT, 96);
               set_all_hitloc_unarmed(20); 
             }
             break;

         case "CAPTAIN":   
             {
               set_stats(({ 127 + random(20), 
                            101 + random(20), 
                            127 + random(20), 
                            101 + random(20), 
                            101 + random(20), 
                            127 + random(20) }));
               set_skill(SS_PARRY, 69);
               set_skill(SS_DEFENCE, 69);
               set_skill(SS_WEP_SWORD, 92);
               set_skill(SS_WEP_AXE, 92);
               set_skill(SS_AWARENESS, 50);
               set_skill(SS_UNARM_COMBAT,92); 
               set_skill(SS_BLIND_COMBAT, 92);
               set_all_hitloc_unarmed(22); 
             }
             break;         

         case "HESTOS":   
             {
               set_stats(({ 121 + random(20), 
                            88 + random(20), 
                            121 + random(20), 
                             88 + random(20), 
                             88 + random(20), 
                            121 + random(20) }));
               set_skill(SS_PARRY, 66);
               set_skill(SS_DEFENCE, 66);
               set_skill(SS_WEP_SWORD, 88);
               set_skill(SS_WEP_AXE, 88);
               set_skill(SS_AWARENESS, 50);
               set_skill(SS_UNARM_COMBAT,88); 
               set_skill(SS_BLIND_COMBAT, 70);
               set_all_hitloc_unarmed(21); 
             }
             break;

         case "STANDARD": /* Standard minotaurs are villagers */ 
             {
               set_stats(({ 110 + random(20), 
                            80 + random(20), 
                            110 + random(20), 
                             80 + random(20), 
                             80 + random(20), 
                            110 + random(20) }));
               set_skill(SS_PARRY, 60);
               set_skill(SS_DEFENCE, 60);
               set_skill(SS_WEP_SWORD, 80);
               set_skill(SS_WEP_AXE, 80);
               set_skill(SS_AWARENESS, 50);
               set_skill(SS_UNARM_COMBAT,80); 
               set_skill(SS_BLIND_COMBAT, 70);
               set_all_hitloc_unarmed(20); 
             }
             break;         

         default:
             {      
               set_stats(({ 110 + random(20), 
                            80 + random(20), 
                            110 + random(20), 
                             80 + random(20), 
                             80 + random(20), 
                            110 + random(20) }));
               set_skill(SS_PARRY, 60);
               set_skill(SS_DEFENCE, 60);
               set_skill(SS_WEP_SWORD, 80);
               set_skill(SS_WEP_AXE, 80);
               set_skill(SS_AWARENESS, 50);
               set_skill(SS_UNARM_COMBAT,80); 
               set_skill(SS_BLIND_COMBAT, 70);
               set_all_hitloc_unarmed(20); 
             }
    } 
}

void
create_minotaur()
{
}

void
create_krynn_monster()
{
    setuid();
    seteuid(getuid());   
    
    set_name("minotaur");
    set_race_name("minotaur"); 
    
    set_exp_factor(110);
    set_alignment(0 - random(100));
    add_prop(LIVE_I_NEVERKNOWN, 1);   

    create_minotaur();

    add_leftover("/d/Krynn/solace/lake/obj/horn_remains","horn",2,"",0,0);
    add_leftover("/d/Krynn/common/commerce/leather_scrap","skin",1,"",0,0);

}

int
special_attack(object enemy)
{
    mixed *hitresult;
    string how1, how2, ghow1, ghow2;
    int playerDEX;

    switch (TYPE)
    {
         case "CHIEFTAIN":
             return 0;    /* The chieftain has another attack */  
             break;

         case "SAGE":     /* The Sage is an ok fighter */   
             if (random(6))
             {
                 return 0;
             }
             break;

         case "CAPTAIN":  /* The captain is a good fighter */  
             if (random(4))
             {
                 return 0;
             }
             break;         

         case "HESTOS":   /* Hestos minotaurs are good fighters */  
             if (random(6))
             {
                 return 0;
             }
             break;

         case "STANDARD": /* Standard minotaurs are villagers */ 
             if (random(8))
             {
                 return 0;
             }
             break;         

         default:         /* If no type is given, no special attack */
             return 0;
    }

    /* Calculate damage, how well you evade it is somewhat 
       dependant on the player's DEX */ 
 
    playerDEX = enemy->query_stat(1) / 50;

    hitresult = enemy->hit_me(300+random(100), W_IMPALE, TO, -1);    

    hitresult[0] = hitresult[0] - playerDEX;
    
    if(hitresult[0] < 0) 
    {
        hitresult[0] = 0;
    }

    switch (hitresult[0])
    {
        case 0:
            how1 = "barely manage to evade the sharp horns. \n";

            how2 = "are not hurt at all. \n"; 

            ghow1 = " barely manages to evade the sharp horns. \n";

            ghow2 = " is not hurt at all. \n";
            break;

        case 1..5:
            how1 = "almost evade the sharp horns. \n";

            how2 = "are lightly scratched. \n"; 

            ghow1 = " almost manages to evade the sharp horns. \n";

            ghow2 = " is lightly scratched. \n";
            break;

        case 6..10:
            how1 = "cannot evade the sharp horns. \n";

            how2 = "are deeply scratched. \n"; 

            ghow1 = " cannot evade the sharp horns. \n";

            ghow2 = " is deeply scratched. \n";
            break;

        case 11..15:
            how1 = "completely fail to evade the sharp horns. \n";

            how2 = "are deeply wounded. \n"; 

            ghow1 = " completely fails to evade the sharp horns. \n";

            ghow2 = " is deeply wounded. \n";
            break;

        case 16..20:
            how1 = "do not react quick enough and are hit by the " +
                   "sharp horns. \n";

            how2 = "are badly wounded. \n"; 

            ghow1 = " does not react quick enough and is hit by the " +
                    "sharp horns. \n";

            ghow2 = " is badly wounded. \n";
            break;           

        default:
            how1 = "freeze in terror and are penetrated by the sharp " +
                   "horns. \n";

            how2 = "are left staring down at a bleeding wound. The " +
                   "minotaur shakes its head violently, causing " +
                   "tremendous damage to an already horrible injury. \n";

            ghow1 = " freezes in terror and is penetrated by the " +
                    "sharp horns. \n";

            ghow2 = " is left staring down at a bleeding wound. The " +
                    "minotaur shakes its head violently, causing " +
                    "tremendous damage to an already horrible injury. \n";
    }

    enemy->catch_tell(query_The_name(enemy) + " charges directly at you! \n" +
                      "You " + how1 + "You " + how2); 

    tell_watcher(QCTNAME(TO) + " charges at " + QTNAME(enemy) + "!\n" +
                 capitalize(enemy->query_pronoun()) + ghow1 + 
                 capitalize(enemy->query_pronoun()) + ghow2, enemy);

    if (enemy->query_hp() <= 0)
    {
        write("The minotaur bellows victoriously! \n");
        
        enemy->do_die(this_object());
    }

    return 1;
}
