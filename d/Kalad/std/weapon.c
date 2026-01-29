/* weapon.c: Kalad standard inheritable: Fysix, Sarr, Serpine - 06/15/98 */

inherit "/std/weapon";
inherit "/lib/keep";
inherit "/d/Kalad/std/volume";

#include <wa_types.h>

#define K_WEP_DRAWS   ({ ({5,10,8}), ({5,8,10}), ({5,8,4}), \
              ({5,10,8}), ({5,0,6}), ({5,1,12}), ({5,8,5}) })
/*
 * Weapon drawbacks for Kalad - more to my liking
 *
 * weapon		dull     corr     break
 * -------              ----     ----     -----
 * sword		  5       10         8
 * polearm		  5        8        10
 * axe                    5        8         4
 * knife		  5       10         8
 * club			  5        0         6
 * missile                5        1        12
 * javelin                5        8         5
 */


public varargs string 
short(object for_obj)
{
    string res;

    if (!obj_short)
    {
	remove_adj("unwielded");
	res = ::short(for_obj);
	add_adj("unwielded");
	return res;
    }
    else
    {
	return ::short(for_obj);
    }
}

void
create_weapon()
{
    ::create_weapon();
}

void
set_wt(int type)
{
    int *likely;

    if (query_lock())
	return;           /*changes locked out*/

    if (type >= 0 && type < W_NO_T)
    {
	wep_wt = type;
	likely = K_WEP_DRAWS[type];
	likely_dull = likely[0];
	likely_corr = likely[1];
	likely_break = likely[2];
    }
}

