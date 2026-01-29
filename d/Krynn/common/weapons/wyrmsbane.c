/*
   Pax Tharkas, Wyrmslayer. The ancient sword of Kith-kanan.
   But is actually Wyrmsbane! Wyrmslayer was 2-handed, and Wyrmsbane was
   the one-handed sword given to Tanis. Teth.

   Wyrmsbane.c
   -----------

   Coded ........: 95/04/23
   By ...........: Jeremiah

   Latest update : 97/02/23
   By ...........: Teth


   This is the ancient sister sword to Kith-kanan's Wyrmslayer, crafted 
   during the second dragon war, in Silvanesti. This sword is 35/35 any 
   handed sword. When the wielder is fighting a Dragon or a draconian, 
   the sword does (dam + dam) hp's of damage. If the enemy is a Dragon 
   the blade will hum aggressively. Against a black dragon, this sword
   will do (dam * 3) damage.

*/

inherit "/std/weapon";

#include <ss_types.h>
#include <wa_types.h>
#include <formulas.h>
#include <options.h>
#include <macros.h>
#include <filter_funs.h>
#include "/d/Krynn/common/defs.h"

object wielder;

void
create_weapon()
{
    set_name("wyrmsbane");
    add_name("redeemer");
    add_name(({"sword","weapon","blade"}));
    add_pname(({"swords","weapons","blades"}));
    set_adj("elven");
    add_adj(({"long","slender","metal","green-gemmed"}));
    set_short("elven blade");
    set_pshort("elven blades");
    set_long("This is a sword of elven design. The bright blade is " +
      "long, slender and looks almost unnaturally sharp. A " +
      "deep green gem, visible from both sides of the sword, " +
      "adorns the hilt, at the point where the blade meets " +
      "the hilt. Leather bands are wrapped tight around the " +
      "hilt, giving the wielder a firm grip on the weapon.\n");

    add_item("gem", "A deep green gem, adorning the hilt of this " +
      "magnificent elven weapon. The gem seems to glow with " +
      "an inner light, as if it had a life of its own.\n");

    set_default_weapon(35, 35, W_SWORD, W_SLASH | W_IMPALE, W_ANYH);
    set_wf(TO);
    add_prop(OBJ_M_NO_BUY, 1);
    add_prop(OBJ_I_IS_MAGIC_WEAPON, 1);
    add_prop(OBJ_S_WIZINFO,
      "This is the ancient sister sword of Wyrmslayer. Crafted during " +
      "the second dragon war, it is Silvanesti in origin. This " +
      "weapon is magical. It gets extra hit/pen when fighting " + 
      "dragonkin, such as dragons, or draconians. It does triple " + 
      "damage to black dragons.\n");
    add_prop(MAGIC_AM_ID_INFO,
      ({"This weapon is magically enchanted.\n", 5,
        "The blade was forged during the second dragon war, " +
        "by elven weaponsmiths in Silvanesti.\n", 25,
        "The blade is named Wyrmsbane and is especially " +
        "useful against dragonkin.\n", 55, "This blade " +
        "despises black dragons and other swamp serpents.\n", 65,}));
    add_prop(MAGIC_AM_MAGIC,({80,"enchantment"}));
    add_prop(OBJ_I_ALIGN, 600);
    add_prop(OBJ_I_VOLUME, 1500);
    add_prop(OBJ_I_WEIGHT, 5000);
    add_prop(OBJ_I_VALUE, F_VALUE_WEAPON(35,35) + 500 + random(500)); 
}


mixed
wield(object what)
{
    if(TP->query_alignment() < 600)
        return "The " + short() + " refuses you. You cannot wield it.\n";

    wielder = TP;
    return 0;
}


mixed
unwield()
{
    wielder = 0;
    return 0;
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
        if (ob[i]->query_option(OPT_BLOOD) == 0)
            ob[i]->catch_msg(str);
}


public mixed
did_hit(int aid,string hdesc,int phurt,object enemy,int dt,int phit,int dam)
{
    string dam_descr;

    if(QRACE(enemy) == "dragon")
    {
        if(!random(2))
            wielder->catch_msg("Your " + short() + " gives off a deep humming " +
              "sound.\n");
        tell_room(E(wielder), "The " + short() + " wielded by " + 
          QTNAME(wielder) + " gives off a deep humming sound.\n", 
          wielder);
    }

    if(QRACE(enemy) == "dragon" || QRACE(enemy) == "draconian")
    {
        if(dam) 
        {
            switch(dam)
            {
            case 0:
                dam_descr = " glances off the ";
                break;

            case 1..100: 
                dam_descr = " cuts into the ";
                break;

            case 101..200: 
                dam_descr = " cuts deeply into the ";
                break;

            default:
                dam_descr = " cuts a gaping wound in the ";
                break;
            }

            wielder->catch_msg("Your " + short() + dam_descr +
              hdesc + " of " + QTNAME(enemy) + ".\n");
            tell_watcher("The " + short() + " wielded by " + 
              QCTNAME(wielder) + dam_descr + hdesc + " of " +
              QTNAME(enemy) + ".\n", enemy);

            if ((enemy->query_colour() == "black") && 
              (QRACE(enemy) == "dragon"))
                enemy->heal_hp(-dam);
            enemy->heal_hp(-dam);
        }
    }

    return ::did_hit(aid, hdesc, phurt, enemy, dt, phit, dam);
}


