/*
 *   /d/Gondor/ithilien/poros/weapons/black_dagger.c
 *
 *   This is one of the weapons used by the corsair's first mate. The
 *   dagger is only a slightly modified version of /d/Gonodor/minas/shades
 *   /obj/sdagger.c. The blade is poisoned...
 *
 *   Talisan,  February 1996
 */
#pragma strict_types

inherit "/std/weapon";
inherit "/lib/keep.c";

#include <ss_types.h>
#include <wa_types.h>
#include "/d/Gondor/defs.h"
#include <poison_types.h>
#include <macros.h>
#include <formulas.h>
#include <language.h>

//The number should be one less then the number of poisons you want, and 
//minus 
#define POISON -3

//    Prototypes:
void  init_recover(string  arg);

//    Global Variables:

int poison_used;

public void
create_weapon()
{
    set_name(({"dagger", "knife", "ebony-bladed dagger"}));
    set_short("ebony-bladed dagger");
    set_long("@@long_desc");  /* This is VBFC to tell of the poison on the */
    set_adj(({"black", "cruel", "long", "cold", "grooved", "shiny",
              "ebony-bladed"}));

    /*
     *   Be adviced that the way you use set_wf, others in the room won't
     *   get a message when the weapon is un/wielded. This is in some cases
     *   fine but I would think that you should make a check on the watchers
     *   awereness. before deciding if they should get a message or not.
     *   maybe people with awereness abive 50 and would get a message ?
     *      -Boron
     */    
    set_wf(this_object());


    set_hit(19);
    set_pen(17);
    set_wt(W_KNIFE);

    set_dt(W_IMPALE | W_SLASH);
    set_hands(W_ANYH);

    add_prop(OBJ_I_WEIGHT, F_WEIGHT_DEFAULT_WEAPON(17, W_KNIFE) - 25);
    add_prop(OBJ_I_VOLUME, query_prop(OBJ_I_WEIGHT) / 2);
    add_prop(OBJ_I_VALUE, F_VALUE_WEAPON(17, 19) + 400);
    /* 
     * The poison isn't used, upon creation 
     */
    poison_used = POISON;

}

string
long_desc()
{
    if(poison_used >= 1)
	return "This is a long, cruel looking dagger. Its cold black "
	+ "twisting blade is grooved and shiny. An aura of evil seems to "
	+ "radiate from the weapon.\n";
    else
	return "This is a long, cruel looking dagger. Its cold black "
	+ "twisting blade is grooved and shiny. An aura of evil seems to "
	+ "radiate from the weapon. Along the blade's groove, a clear "
	+ "liquid can be seen.\n";
}

/*
 * We redefine did_hit() in order to actually poison the player.  We will
 * set it up so that the poison wears off the blade after a while.
 */

public varargs int
did_hit(int aid, string hdesc, int phurt, object enemy, int dt, int
  phit)
{
    object poison;
    seteuid(getuid(this_object()));
    if (phurt <=0) return 0;
    if(poison_used < 1) {
	poison = clone_object("/std/poison_effect");
	if(poison) {
	    if(poison_used <= 0)
		poison_used += 1;
	    write_file("/d/Gondor/log/curses",enemy->query_name()+" was poisoned by a ebony-bladed dagger, by "+query_wielded()->query_name()+" on "+ctime(time())+".\n");
	    poison->move(enemy, 1);
	    poison->set_time(2250);            /* Nice and long */
	    poison->set_interval(25);
	    poison->set_strength(75);
	    poison->set_damage(({POISON_HP, 90, POISON_STAT, SS_STR}));
	    poison->set_poison_type("corsair_poison");
	    poison->start_poison();
	    tell_object(query_wielded(),
	      "The cold ebony blade causes a vicious, deep cut in your "
	      + "opponent's "+hdesc+", and the foul poison along the "
	      + "blade's groove enters into the wound!\n");
	    return 0;
	}
	else 
	    write("Failed to load poison for some reason.\n"); 
    }
    return 0;
}
int
wield()
{
    TP->catch_msg(BSN("A cold chill runs throughout your body as you grip "
	+ "the ebony dagger."));
    return 1;
}

int
unwield()
{
    query_wielded()->catch_msg(BSN("As you release the dagger a cold chill runs "
	+ "throughout your body."));
    return 1;
}


string
query_recover()
{
    return MASTER + ":" + query_wep_recover() + "#p_u#" + poison_used + "#";
}

void
init_recover(string  arg)
{
    string dummy;
    init_wep_recover(arg);
    sscanf(arg, "%s#p_u#%d#%s", dummy, poison_used, dummy);
}
/*
 * Function name: query_poison_status()
 * Description:   Is for wizards to call so, one can get how many poisons
 *                are left, and how many there was origanilly.
 * Returns:       Poisons to begin with, and poisons left
 */

string
query_poison_status()
{
    string str;

    str = "\n Poisons to begin with: " + ((POISON * - 2) / 2 )+ "\n"
    + " Poisons left: " + ((poison_used * - 2) / 2 ) + "\n"
    + " Minus means there is no poisons left.\n";
    return str;  

}
