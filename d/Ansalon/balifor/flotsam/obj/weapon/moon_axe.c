/* Navarre June 25th 2006, added keep ability */
/* Navarre Oct 2006, added check on me, to avoid runtime. 
 *                   also added a random to the HIT and PEN of the weapon.
 */

inherit "/std/weapon";
inherit "/lib/keep";
#include "/sys/stdproperties.h"
#include "/sys/wa_types.h"
#include "/sys/formulas.h"
#include "/sys/macros.h"
#include <options.h>
#include <ss_types.h>
#include <filter_funs.h>
#include "/d/Ansalon/common/defs.h"

#define WEAPON_HIT (35+random(5))
#define WEAPON_PEN (35+random(5))

object wielder;

void
create_weapon()
{
    set_name("waraxe");
    add_name("axe");
    add_pname(({"waraxes","axes"}));
    set_adj("half-moon");
    set_adj("bladed");
    add_adj("metal");  /* added by Gorboth, July 2007 */
    set_short("half-moon bladed waraxe");
    set_long("Consisting of a broad half-moon blade on one " +
      "side of the head of the axe, and a curved spike on the " +
      "other side, it is obvious this axe was not crafted for " +
      "a woodsman's tool. While plainly made, it is excellently " +
      "balanced, most likely made by a very good weaponsmith, " +
      "perhaps even a master.\n");

    set_hit(WEAPON_HIT);
    set_pen(WEAPON_PEN);
    set_wt(W_AXE);
    set_dt(W_SLASH);
    set_hands(W_LEFT);
    set_wf(TO);
    add_prop(OBJ_M_NO_BUY,"Oops! That axe wasn't for sale. Please make different purchase.\n");
    add_prop(OBJ_I_IS_MAGIC_WEAPON, 1);
    add_prop(MAGIC_AM_MAGIC,({50,"enchantment"}));
    add_prop(MAGIC_AM_ID_INFO,({"This waraxe has been imbued " +
	"with the spirit of a roguish warrior, trapped in the " +
	"axe via a curse from an evil sorcerer. The spirit " +
	"enchants the axe so that it does greater damage against " +
	"opponents. The spirit also assists females who wield " +
	"the axe by drawing on the targets lifeforce with his " +
	"undead powers.\n",1}));

    add_prop(OBJ_I_WEIGHT, 10000);
    add_prop(OBJ_I_VOLUME, 4000);
    add_prop(OBJ_I_VALUE,F_VALUE_WEAPON(WEAPON_HIT,WEAPON_PEN));

    seteuid(getuid(TO));
}


mixed
wield(object what)
{
    if(TP->query_gender() == 1)
	write("As you grip the half-moon bladed waraxe, " +
	  "you hear a roguish voice inside your head say: " +
	  "Milady! Let us weave a song of death for your enemies! " +
	  "I am yours, only to serve.\n");

    wielder = TP;

    return 0;
}

mixed
unwield()
{
    wielded = 0;
    return 0;
}

static void
tell_watcher(string str, object enemy)
{
    object me,*ob;
    int i;

    me = query_wielded();

    if(!me)
        return;

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
    string dam_descr;

    if(wielder->query_gender() == 0)
    {
	return ::did_hit(aid, hdesc, phurt, enemy, dt, phit, dam);
    }

    if(wielder->query_gender() == 1)
	if(!random(4))
	{
	    if(phurt > 0)
	    {
		switch(dam)
		{
		case 0..75:
		    dam_descr = " draws blood from ";
		    break;

		case 76..150:
		    dam_descr = " cuts deeply into ";
		    break;

		default:
		    dam_descr = " slices a ghastly wound in ";
		    break;
		}

		wielder->catch_msg(QCTNAME(enemy) + " turns pale " +
		  "as your " + short() + dam_descr + POSSESSIVE(enemy)
		  + " " + hdesc + ".\n");
		enemy->catch_msg("You feel chilled, your life force " +
		  "being drained as " + QTNAME(wielder)
		  + "'s " + short() + dam_descr + "your " + hdesc + ".\n");
		tell_watcher(QCTNAME(enemy) + " turns pale as "
		  + QTNAME(wielder) + "'s " + short() + dam_descr
		  + POSSESSIVE(enemy) + " " + hdesc + ".\n", enemy);

		enemy->heal_hp(-dam);
	    }
	}

    return ::did_hit(aid, hdesc, phurt, enemy, dt, phit, dam);
}
