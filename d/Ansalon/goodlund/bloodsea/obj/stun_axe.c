/* Ashlar, 3 Aug 97 */
/* Weapon with a stun special */
/* Modified by Arman  26/4/2004 */
/* Navarre July 3rd 2006, fixed typo */

inherit "/std/weapon";
inherit "/lib/keep";
#include <wa_types.h>
#include <stdproperties.h>
#include <macros.h>
#include <formulas.h>
#include <options.h>
#include <ss_types.h>
#include <filter_funs.h>
#include <files.h>
#include "/d/Ansalon/common/defs.h"
#include "/d/Ansalon/taman_busuk/neraka/local.h"

#define HIT 35
#define PEN 40

create_weapon()
{
    set_name("waraxe");
    add_name("axe");
    set_adj("black");
    add_adj("steel-handled");
    set_short("black steel-handled waraxe");
    set_long("This waraxe has been made out of some "+
       "shiny black metal. The axehead is extremely "+
       "heavy, however the steel-handle acts as "+
       "a partly counterweight. The blade is "+
       "sharp as a razor, and if wielded properly it might "+
       "be able to knock an enemy off his feet "+
       "if the blow hits his legs.\n");

    add_prop(OBJ_I_IS_MAGIC_WEAPON, 1);
    add_prop(MAGIC_AM_MAGIC,({ 10, "enchantment"}));
    add_prop(MAGIC_AM_ID_INFO,({"This weapon has been " +
        "enchanted so that its edge always remains sharp, making " +
        "it more damaging when it strikes. The enchantment also " +
        "makes strikes against the legs more likely to knock them " +
        "from their feet.\n",5}));

    set_hit(HIT);
    set_pen(PEN);
    set_wt(W_AXE);
    set_dt(W_SLASH);
    set_hands(W_RIGHT);
    add_prop(OBJ_I_VALUE,F_VALUE_WEAPON(HIT,PEN)+random(80)-15);
    add_prop(OBJ_I_VOLUME, 7000);
    add_prop(OBJ_I_WEIGHT, 7500);
    set_likely_dull(0);

}

static void
tell_watcher(string str, object enemy)
{
    object me,*ob;
    int i;

    me = query_wielded();
    ob = FILTER_LIVE(all_inventory(environment(me))) - ({ me });
    ob -= ({ enemy });
    for (i = 0; i < sizeof(ob); i++)
        if (!ob[i]->query_option(OPT_BLOOD) && CAN_SEE_IN_ROOM(ob[i]))
        {
            if (CAN_SEE(ob[i], me))
                ob[i]->catch_msg(str);
            else
                tell_object(ob[i], "Someone is hit by someone.\n");
        }
}


public mixed
did_hit(int aid,string hdesc,int phurt,object enemy,int dt,int phit,int dam)
{
    string *how;
    int delay;
    object wielder;

    wielder = E(TO);

    if(enemy->query_humanoid())
    {
      if(!random(6))
      {
        if(phurt > 0)
        {
            switch(phurt)
            {
                case 0..44:
                    how = ({ ", making you stumble",
                        ", making " + OBJECTIVE(enemy)+ " stumble",
                        ", making " + OBJECTIVE(enemy)+ " stumble" });
                    delay = 5;
                    break;
                case 45..74:
                    how = ({ ", making you fall",
                        ", making " + OBJECTIVE(enemy) + " fall",
                        ", making " + OBJECTIVE(enemy) + " fall" });
                    delay = 10;
                    break;
                default:
                    how = ({ ", the axe hits your thigh muscle, paralyzing you "+
                             "for a short time",
                        ", the axe hits " + HIS(enemy) + " thigh muscle, "+
                            "paralyzing " +HIM(enemy)+ " for a short time",
                        ", the axe hits " + HIS(enemy) + " thigh muscle, "+
                            "paralyzing " +HIM(enemy)+ " for a short time" });
                    delay = 15;
                    break;
            }
            
            enemy->add_attack_delay(delay,1);
            wielder->catch_msg("You swing your " +short()+ " in a large arch " +
                "striking the legs of " +QTNAME(enemy) + how[1] + ".\n");

            enemy->catch_msg(QCTNAME(wielder) + " swings " +
                POSSESSIVE(wielder) + " " +short()+ " in a large arch, striking " +
                "your legs" + how[0] + ".\n");
            tell_watcher(QCTNAME(wielder) + " swings " +
                POSSESSIVE(wielder) + " " +short()+ " in a large arch, striking " +
                QTNAME(enemy) + "'s legs" + how[2] + ".\n", enemy);

        }
      }
    }

    return ::did_hit(aid, hdesc, phurt, enemy, dt, phit, dam);
}

