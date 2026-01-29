// file name:        /d/Avenir/common/dark/obj/dblpole.c
// creator(s):       Denis
// revision history: Denis, Aug'96: Removed the tell_watcher function.
//                   Manat, Nov'02: Changed did_hit to match the change
//                                  in mudlib.
// purpose: unclear.
// notes:
//   This polearm allows wielder to fight more than 1 opponent at
//   once by means of weapon special attacks.
//   This ability is given to this polearm by 2 blades attached
//   to its both ends.
//   This defence move turns on at particular amount of hp
//   left in wielder && random(4) and lasts up to 1 min.
//   There are no restrictions on wielding this polearm, but
//   player is able to use its special abilities only if
//   his polearm skill and dexterity are high enough.
//
// Jul'96 thought: When did I code this? In Jun'95?
// bug(s):
// to-do:
 
inherit "/std/weapon";
#include "/d/Avenir/common/common.h"
#include <filter_funs.h>
#include <formulas.h>

#define A_OBJECT "/d/Avenir/common/dark/obj/dblarm.c"
#define S_WPEN 30
 
object wielder;
object armour_object;
mixed enemies;
int enemies_number;
int use_special;
int armour_working;
 
/*--[ Prototypes: ]-----*/
int hit_second_enemy(object enemy, int dam);
hit_all_enemies();
install_armour();
// Not needed anymore static void tell_watcher(string str, object enemy);
 
create_weapon()
{
    set_name("polearm");
 
    set_adj("double-bladed");
    add_adj("double");
    add_adj("black");
    add_adj("oak");
 
    set_short("double-bladed polearm");
 
    set_long("A 2 meters long polearm made of black oak "+
             "with steel blades on both it's ends.\n"+
             "The balance of this weapon is very strange.\n");
 
    set_default_weapon(30,30,W_POLEARM,W_SLASH|W_IMPALE,W_BOTH,TO);
 
    set_wf(TO);
}
 
/*--[ Special attacks and defence move ]-----*/
public varargs int
did_hit(int aid, string hdesc,
        int phurt,object enemy,int dt, int phit, int dam)
{
    string what;
    string how;
    int r = ::did_hit(aid, hdesc, phurt, enemy, dt, phit, dam);
 
    /*--[ If the wielder isn't skilled enough,     ]-*/
    /*--[ he don't need to use special attacks.    ]-*/
    if(!use_special)
        return r;
 
    /*--[ If we are feeling bad, maybe its time to ]-*/
    /*--[ start to spin our polearm?               ]-*/
    if((100*(HP(wielder)))/wielder->query_max_hp()<30&&
       !armour_working&&!random(4))
    {
        install_armour();
    }
 
    /*--[ Polearm hurts enemies in another way     ]-*/
    /*--[ when it is spinning.                     ]-*/
    if(armour_working)
    {
        if (phurt > -1)
        {
            switch(phurt)
            {
            case 0..4:
                how=" without any damage.\n";
                what="touches ";
                break;
            case 5..9:
                how=".\n";
                what="barely grazes ";
                break;
            case 10..19:
                how=".\n";
                what="hurts ";
                break;
            case 20..39:
                how=".\n";
                what="hurts ";
                break;
            case 40..69:
                how=".\n";
                what="cuts deep into ";
                break;
            case 70..97:
                how=", leaving several injures behind.\n";
                what="cuts deep into ";
                break;
            default:
                how=" into several parts.\n";
                what="divides ";
                break;
            }
            wielder->catch_msg(
              "Your spinning double-bladed polearm "+what+QTNAME(enemy)+how);
            enemy->catch_msg(
              "Spinning double-bladed polearm of your enemy "+what+
              "you"+how);
            wielder->tell_watcher(
              "Spinning double-bladed polearm of "+QTNAME(wielder)+" "+what+
              QTNAME(enemy)+how,enemy);
            if(phurt>70)
            {
                enemy->catch_msg("You scream in pain!\n");
                tell_room(environment(wielder),QCTNAME(enemy)+
                          " screams in pain!\n",enemy);
            }
        }
        else if (phurt == -1) // Dodge
        {
            wielder->catch_msg(
              "Your spinning double-bladed polearm is dodged by " + QTNAME(enemy) + ".\n");
            enemy->catch_msg(
              "You dodge the spinning double-bladed polearm of "+QTNAME(wielder)+".\n");
            wielder->tell_watcher(
              QCTNAME(enemy) + " dodges the spinning double-bladed polearm of "+
              QTNAME(wielder)+".\n", enemy);
        }
        else if (phurt == -2) // Parry
        {
            wielder->catch_msg(
              "Your spinning double-bladed polearm is dodged by " + QTNAME(enemy) + ".\n");
            enemy->catch_msg(
              "You dodge the spinning double-bladed polearm of "+QTNAME(wielder)+".\n");
            wielder->tell_watcher(
              QCTNAME(enemy) + " dodges the spinning double-bladed polearm of "+
              QTNAME(wielder)+".\n", enemy);
        }
        else // Unknown
        {
            wielder->catch_msg("Bugreport this: Unknown phurt(" + phurt + ").\n");
        }
        return 1;
    }
 
    /*--[ If we are fighting many enemies, maybe it is time ]-*/
    /*--[ To hit someone else than our first enemy ?        ]-*/
    if(!random(4)&&(dt==W_IMPALE)&&phurt>1)
    {
        return hit_second_enemy(enemy,dam);
    }
 
    /*--[ Maybe its time to swing polearm around and hit    ]-*/
    /*--[ everybody?                                        ]-*/
    if(!random(4)&&(dt==W_SLASH)&&phurt>1)
    {
        hit_all_enemies();
        return 1;
    }
    return r;
}
 
/*--[ It's a specific tell_watcher, beware! ]-----*/
/* It is not needed anymore *sigh*
static void
tell_watcher(string str, object enemy)
{
    object *ob;
    int i;
 
    ob = FILTER_LIVE(all_inventory(environment(wielder))) - ({wielder});
    ob -= ({ enemy });
    ob -= ({ wielder->query_attack() });
    for (i = 0; i < sizeof(ob); i++)
        if (ob[i]->query_see_blood())
            ob[i]->catch_msg(str);
}
*/
 
/*--[ Getting secondary enemies in the room array ]-----*/
get_enemies()
{
    wielder=query_wielded();
 
    enemies=filter(all_inventory(environment(wielder)),"if_is_enemy",TO);
    enemies_number=sizeof(enemies);
}
 
/*-----[ Hitting second enemy selected randomly ]-----*/
int
hit_second_enemy(object enemy, int dam)
{
    int second_dam;
    object second_enemy;
    mixed result;
    
    get_enemies();
    if (enemies_number==0) return 0;
    second_enemy=enemies[random(enemies_number)];
 
    result=second_enemy->hit_me(F_PENMOD(30,
			        query_wielded()->query_skill(SS_WEP_POLEARM)),
				W_IMPALE,query_wielded(),-1);
    
    if (result[0] < 5)
    {
        enemy->catch_msg(
          QCTNAME(wielder)+" thrusts you and then"+
          " aims "+QTNAME(second_enemy)+" with "+POSSESS(wielder)+
          " backward attack, but misses.\n");
 
        second_enemy->catch_msg(
          QCTNAME(wielder)+" thrusts "+QTNAME(enemy)+
          " and then aims you with "+POSSESS(wielder)+
          " backward attack, but misses.\n");
 
        wielder->catch_msg(
          "After thrusting your opponent"+
          " you try to hit "+QTNAME(second_enemy)+
          " with backward attack, but miss.\n");
 
        wielder->tell_watcher(QCTNAME(wielder)+" thrusts "+
          QTNAME(enemy)+ " and then aims "+QTNAME(second_enemy)+
          " with backward attack, but misses.\n", enemy, second_enemy);
    }
    else
    {
        enemy->catch_msg(
          QCTNAME(TP)+" thrusts you and then hurts "+
          QTNAME(second_enemy)+
          " with "+POSSESS(wielder)+" backward attack.\n");
 
        second_enemy->catch_msg(
          QCTNAME(wielder)+" thrusts "+QTNAME(enemy)+
          " and then hurts you "+
          "with "+POSSESS(TP)+" backward attack.\n");
 
        wielder->catch_msg(
          "After thrusting your opponent you hurt "+QTNAME(second_enemy)+
          " with your backward attack.\n");
 
        wielder->tell_watcher(
          QCTNAME(wielder)+" thrusts "+POSSESS(wielder)+" opponent "+
          " and then hurts "+QTNAME(second_enemy)+" with "+
          POSSESS(wielder)+" backward attack.\n",enemy, second_enemy);
    }
    return 1;
}
 
/*--[ Filter function ]-----*/
int if_is_enemy(object test_enemy)
{
   if (environment(wielder)==environment(test_enemy)&&
      wielder==test_enemy->query_enemy()&&
      wielder->query_enemy()!=test_enemy)
          return 1;
}
 
/*--[ Hitting all enemies around ]-----*/
hit_all_enemies()
{
    int i;
 
    get_enemies();
    for(i=0;i<enemies_number;i++)
    {
        enemies[i]->hit_me(F_PENMOD(S_WPEN,
			   query_wielded()->query_skill(SS_WEP_POLEARM)),
			   W_SLASH,query_wielded(),-1);
        enemies[i]->catch_msg(
          QCTNAME(wielder)+" swings "+POSSESS(wielder)+
          " polearm around and hurts all "+POSSESS(wielder)+
          " opponents.\n");
    }
    (wielder->query_enemy())->catch_msg(
          QCTNAME(TP)+" swings "+POSSESS(wielder)+
          " polearm around and hurts all "+POSSESS(wielder)+
          " opponents.\n");
    wielder->catch_msg(
      "You swing your polearm around and hurt all your opponents.\n");
}
 
mixed wield(object obj)
{
    wielder=TP;
    if(DEX(TP)>55&&TP->query_skill(SS_WEP_POLEARM)>50)
    {
        write("You know how to use this polearm to its full extent.\n");
        use_special=1;
        return;
    }
    write("This polearm seems strange to you.\nYou can't determine how "+
          "can it be used to rule the battle.\n");
    use_special=0;
    return;
}
 
mixed unwield(object obj)
{
    wielder=0;
    if(armour_working)
    {
        armour_working=0;
        armour_object->remove_object();
    }
}
 
install_armour()
{
    seteuid(getuid());
    armour_object=clone_object(A_OBJECT);
    armour_object->move(wielder);
    armour_object->set_pole(TO);
    if(armour_object->wear_me()!=1)
    {
	armour_object->remove_object();
	return;
    }
    armour_working=1;
 
    set_pen(40);
    set_hit(25);
}
 
reset_defence()
{
    armour_working=0;
    set_hit(30);
    set_pen(30);
}
