/* ash_bow.c
 * A longbow used by Qualinesti elves.
 *
 * Blizzard, 12.05.2003
 * 24.6.2004 various fixes and cleaning by Milan
 */

#pragma strict_types

#include <stdproperties.h>
#include <macros.h>
#include <formulas.h>
#include "/d/Krynn/common/defs.h"
#include "../local.h"

inherit "/std/bow";

void draw_dagger(object tp);
int drawn = 0;

public void
create_bow()
{
    set_adj(({"ashwood", "ash", "long"}));
    add_name("longbow");
    set_short("ashwood longbow");
    set_long("This very light bow is made out of a long branch " +
        "of ash wood. It is tightly-strung, and has a fair amount of " +
        "stopping power. Being crafted by elves, you would expect it " +
        "to be quite a powerful bow.\n"); 

    add_prop(OBJ_I_WEIGHT, 900);
    add_prop(OBJ_I_VOLUME, 3250);
    add_prop(OBJ_I_VALUE, F_VALUE_WEAPON(40, 40));

    set_hit(40);
    set_pen(40);
    
    seteuid(getuid(TO));
}

void
remove_broken()
{
	set_alarm(3.0, 0.0, &draw_dagger(query_wielded()));        
	::remove_broken();
}

void
wield_another()
{
	set_alarm(2.0, 0.0, &draw_dagger(E(TO)));
}

void
init()
{
    add_action(wield_another, "elf_wield_sec_weapon");
    ::init();
}

void
draw_dagger(object tp)
{
	object enemy, wep;

	if ( !objectp(tp) || drawn) // We switch weapon only once.
		return;
        
    if ( tp->id("qualthas") )
    {
        wep = clone_object(WEP + "qual_sword");
    }
    else
	{
		if ( tp->id("scout") || tp->id("archer") )
		{
			switch ( random(3) )
			{
			case 0:
				wep = clone_object(WEP + "edagger");
				break;
			case 1:
				wep = clone_object(WEP + "elongsword");
				break;
			default:
				wep = clone_object(WEP + "shortsword");
			}
		}
		else
			return; // action taken only for the above
	}

	drawn = 1;
    wep->move(tp, 1);
    tp->command("wield " + OB_NAME(wep));
        
    enemy = tp->query_attack();
	if (!objectp(enemy)) // No further messages if there is no enemy
		return;

    enemy->catch_msg(QCTNAME(tp) + " moves to face you in close combat.\n");
    tell_room(E(tp), QCTNAME(tp) + " moves to attack " + QTNAME(enemy) + 
        " in close combat.\n", enemy);
    
    if ( tp->id("qualthas") )
    {
        switch (random(3))
        {
        case 0:
            tp->command("say I will show you now, how to use a sword!");
            tp->command("emote grins.");
			break;
        case 1:
            tp->command("say Maybe now you will manage to scratch me!");
            tp->command("emote laughs.");
			break;
        default:
            tp->command("say Do not think it will be easier now!");
        }
    }
    else
    {
        switch ( random(3) )
        {
        case 0:
            tp->command("say Ha! Let's fight!");
			break;
        case 1:
            tp->command("emote grins madly.");
			break;
        default:
            tp->command("say Do not think it will be easier now!");
        }
    }
}

/* 
 * Function name: did_parry 
 * Description:   Called when this weapon was used to parry an attack. It can 
 *                be used to wear down a weapon. Note that his method is called 
 *                before the combat messages are printed out. 
 * Arguments:     att:   Attacker 
 *                aid:   The attack id 
 *                dt:    The damagetype 
 */
public varargs void
did_parry(object att, int aid, int dt)
{    
    if (query_stringed() && !random(F_BOWSTRING_SNAP_CHANCE))    
    {        
        set_alarm(3.0, 0.0, &draw_dagger(query_wielded()));
        snap_string();
    }
}
