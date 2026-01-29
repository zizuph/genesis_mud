/*  -*- LPC -*-  */

/*
 * Some unfinished project..
 * 
 * It seems like this weapon is an undead-disrupting weapon.
 * If the weapon hits an undead being, it will temporarily
 * 'stun' it, disarming the undead's weapons. It is 'holy',
 * so evil players (align < 100) can not wield it.
 *
 * Original Author: Unknown. (Odin perhaps.)
 * 
 * Fixes:  o Some bug fixes.            // Sir Rogon
 *         o Some better indentation.   // Sir Rogon.
 *
 * Suggestions:
 *         o Make the runes identifiable, at least 
 *           make a command to read them, although
 *           they need not tell anything useful.
 *         o Also make use of the add_stun()-function.
 *
 */

inherit "/std/weapon";

#include "/d/Shire/common/defs.h"
#include <macros.h>
#include <stdproperties.h>
#include <ss_types.h>
#include <wa_types.h>
#include <formulas.h>
#include <filter_funs.h>

#define MIN_ALIGN 100
#define MIN_SKILL 50
#define GET_OBJ "/d/Shire/moria/obj/get_get"

void
create_weapon()
{
    set_name("mace");
    add_name("_mace_of_disruption");
    set_adj("silver");
    set_adj("runed");
    set_short("silver runed mace");
    set_pshort("silver runed maces");
    set_long("This silvery runed mace is made of stunning "+
	     "mithril. It is light to the touch and as strong as stone. "+
	     "Ancient dwarvish runes cover "+
	     "the shaft of the mace, spelling doom upon your enemies.\n");
    set_default_weapon(45, 45, W_CLUB, W_BLUDGEON, W_ANYH);
    add_prop(MAGIC_AM_MAGIC, ({55, "enchantment"}));
    add_prop(OBJ_I_IS_MAGIC_WEAPON,1);
    add_prop(MAGIC_I_RES_DEATH, ({60, 1}));
    add_prop(MAGIC_AM_ID_INFO,({
	"The silver runed mace is known as the mace of disruption. ", 20,
	"It has a heavy enchantment of death magic laid upon it. ", 40,
	"It is a very ancient weapon made by the dwarven mithril " +
	    "smiths of Khazad-dum.\n", 60}));

    add_prop(OBJ_S_WIZINFO,"");
    add_prop(OBJ_I_WEIGHT,12000);
    add_prop(OBJ_I_VOLUME, 5000);
    add_prop(OBJ_I_VALUE,F_VALUE_WEAPON(45,45) + 300 + random(300));
}


int wield()
{
    if (TP->query_prop(LIVE_I_UNDEAD))
    {
        write("You feel absorbed into the " +short()+ "!\n" +
              "Your body fades from exsistence!\n");
        TP->command("drop all");
        TP->add_mana(-(TP->query_mana()));
        TP->heal_hp(-(TP->query_max_hp())/5);
        if (TP->query_hp() < 0)
            TP->do_die();
        say(" fades from exsistence for a moment trying to wield the " +short()+"!\n");
        return -1;
    }
    if (TP->query_alignment() < MIN_ALIGN)
    {
        write("You are burned by the "+short()+"!\n");
        say(" is burned attempting to wield the "+short()+"!\n");
        TP->heal_hp(-(TP->query_max_hp())/8);
	if(TP->query_hp() < 0)
	    TP->do_die();
        return -1;
    }
    else if(TP->query_skill(SS_WEP_CLUB) >= MIN_SKILL)
    {
        write("You wield the "+short()+" in both hands.\n");
        say(" wields the " + short() + " in both hands.\n");
        return 1;
    }
    else
    {
        write("You seem unable to wield the "+short()+".\n");
        say(" looks confused, and for some reason cannot wield the " +short()+".\n");
        return -1;
    }
}        

/*
 * Function name: tell_watcher
 * Description:   Send the string from the fight to people that want them
 * Arguments:     The string to send
 */
static void
tell_watcher(string str, object enemy)
{
    object me,*ob;
    int i;

    me = query_wielded();
    ob = FILTER_LIVE(all_inventory(environment(me))) - ({ me });
    ob -= ({ enemy });
    for (i = 0; i < sizeof(ob); i++)
        if (ob[i]->query_see_blood())
            ob[i]->catch_msg(str);
}


void
try_fade(object enemy)
{
    int ran, power;
    object wielder, getget;
    wielder = query_wielded();
    ran = random(5);
    FIXEUID;
        
    if(ran > 3)  /* This will happen 40% of the time */
    {
	enemy->catch_msg("The " +short()+ " burns you! You fade from " +
			 "exsistence for a moment!\n");
	wielder->catch_msg("The "+short()+" burns " + QTNAME(enemy) + "!\n" +
			   QTNAME(enemy) + " fades from existence for " +
			   "a moment!\n");
	tell_watcher(QTNAME(enemy) + " seems to fade from view for " +
		     "a moment!\n", enemy);
	enemy->command("drop all");
        getget = clone_object(GET_OBJ);
	getget->move(enemy);
    }
    return 0;
}
 
public varargs int
did_hit(int aid, string hdesc, int phurt, object enemy, int dt, int phit, int dam)
{
    object wielder;

    wielder = query_wielded();

    if (phurt == -1 || phurt == -2)
    {
        wielder->catch_msg("You swing wildly and miss your enemy horribly!\n");
        enemy->catch_msg(BSN("The " +short()+" misses you completely. Whew!"));
        tell_watcher(QCTNAME(wielder) + " attempts to smash " + QTNAME(enemy) +
                     " but swings and misses!\n" , enemy);
    }

    else if (phurt == 0)
    {
        wielder->catch_msg("You just barely graze your enemy with your " +
                           short()+ "!\n");
        enemy->catch_msg("The " +short()+ " just barely grazes you!\n");
        tell_watcher(QCTNAME(wielder) + " just barely grazes " +
                     QTNAME(enemy) + " with " + HIS_HER(wielder) + " " +  
                     short()+ "!\n", enemy);
    }

    else
    {
        wielder->catch_msg("You knock " + QTNAME(enemy) + " hard, " +
                           HE_SHE(enemy) + " staggers backwards from the " +
                           "blow!\n");
        enemy->catch_msg(QCTNAME(wielder)  + " knocks you hard with " + 
                         HIS_HER(wielder) + " " +short()+ " you stagger " +
                         "back from the blow!\n");
        tell_watcher(QCTNAME(wielder) + " knocks "+ QTNAME(enemy) +" hard, " +
                     HE_SHE(enemy) + " staggers back from the blow!\n", enemy);
        if(enemy->query_prop(LIVE_I_UNDEAD))
        {
             try_fade(enemy);
        }
    }
    return 1;
}

