/* Ashlar, 3 Aug 97 */
/* Weapon with a stun special */
/* Louie Nov 2005 - Nurfed stun chance and duration */

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
#include "../local.h"

#define HIT 30
#define PEN 30

create_weapon()
{
    set_name("whip");
    set_adj("heavy");
    add_adj("leather");
    set_short("heavy leather whip");
    set_long("The whip is made of leather with a sturdy handle, and " +
        "is several meters long.\n");
    set_hit(HIT);
    set_pen(PEN);
    set_wt(W_CLUB);
    set_dt(W_SLASH);
    set_hands(W_ANYH);
    add_prop(OBJ_I_VALUE,F_VALUE_WEAPON(HIT,PEN)+random(50)-25);
    add_prop(OBJ_I_VOLUME, 2000);
    add_prop(OBJ_I_WEIGHT, 3500);
}

int
do_whip(string str)
{
    object *oblist;
    
    oblist = COMMAND_DRIVER->parse_this(str, "[the] %l");

    if (!sizeof(oblist))
    {
            notify_fail("Whip whom?\n");
            return 0;
    }

    COMMAND_DRIVER->actor("You give", oblist, " a lash with your whip to " +
        "let " + (sizeof(oblist)>1 ? "them know their" :
        OBJECTIVE(oblist[0]) + " know " + POSSESSIVE(oblist[0])) +
        " place.");

    COMMAND_DRIVER->all2act(" gives", oblist, " a lash with " + POSSESSIVE(TP) +
        " whip.");
    COMMAND_DRIVER->target(" gives you a lash with " + POSSESSIVE(TP) +
        " whip! That really stings!", oblist);
    return 1;
}

void
init()
{
    ::init();
    add_action(do_whip,"whip");
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

    if(!random(10))
    {
        if(dam)
        {
            switch(phurt)
            {
                case 0..14:
                    how = ({ ", stunning you",
                        ", stunning " + OBJECTIVE(enemy),
                        ", stunning " + OBJECTIVE(enemy) });
                    delay = 2;
                    break;
                case 15..44:
                    how = ({ ", making you stumble",
                        ", making " + OBJECTIVE(enemy) + " stumble",
                        ", making " + OBJECTIVE(enemy) + " stumble" });
                    delay = 5;
                    break;
                case 45..74:
                    how = ({ ", throwing you off balance for a while",
                        ", throwing " + OBJECTIVE(enemy) + " off balance for "+
                            "a while",
                        ", throwing " + OBJECTIVE(enemy) + " off balance for "+
                            "a while" });
                    delay = 7;
                    break;

                default:
                    how = ({ ". With a quick pull of the whip, " +
                        QTNAME(wielder) + " makes you fall down, stunned",
                        ". With a quick pull of the whip, you make " +
                        OBJECTIVE(enemy) + " fall down, stunned",
                        ". With a quick pull of the whip, " +
                        QTNAME(wielder) + " makes " + QTNAME(enemy) +
                        " fall down, stunned" });
                    delay = 10;
                    break;
            }
            
            enemy->add_attack_delay(delay,1);
            wielder->catch_msg("You lash out with the whip, wrapping it " +
                "around " + QTNAME(enemy) + "'s " + hdesc + how[1] + ".\n");

            enemy->catch_msg(QCTNAME(wielder) + " lashes out with " +
                POSSESSIVE(wielder) + " whip, wrapping it around your " +
                hdesc + how[0] + ".\n");
            tell_watcher(QCTNAME(wielder) + " lashes out with " +
                POSSESSIVE(wielder) + " whip, wrapping it around " +
                QTNAME(enemy) + "'s " + hdesc + how[2] + ".\n", enemy);

        }
    }

    return ::did_hit(aid, hdesc, phurt, enemy, dt, phit, dam);
}

