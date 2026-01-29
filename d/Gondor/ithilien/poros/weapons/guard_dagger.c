/*
 *   /d/Gondor/ithilien/poros/weapons/black_dagger.c
 *
 *   This is a modified black_dagger.c for use by some corsair guards.
 *
 *   Talisan,  February 1996
 */
#pragma strict_types

inherit "/std/weapon";
inherit "/lib/keep";
#include <ss_types.h>
#include <wa_types.h>
#include "/d/Gondor/defs.h"
#include <poison_types.h>
#include <macros.h>
#include "/sys/formulas.h"
#include <language.h>

//The number should be one less then the number of poisons you want, and 
//minus 
#define POISON -4

//    Prototypes:
void  init_recover(string  arg);

//    Global Variables:

int poison_used;

public void
create_weapon()
{
    set_name(({"dagger", "knife", "black-steel dagger"}));
    set_short("black-steel dagger");
    set_long("@@long_desc");  /* This is VBFC to tell of the poison on the */
    set_adj(({"black", "steel", "long", "cold", "grooved", "shiny"}));

    set_wf(this_object());

    
    set_hit(14);
    set_pen(16);
    set_wt(W_KNIFE);

    set_dt(W_IMPALE);
    set_hands(W_ANYH);

    /* 
     * The poison is used, upon creation 
     */
    poison_used = POISON;

}

string
long_desc()
{
    if(poison_used >= 1)
        return "This is a long, thick bladed dagger made from a "
      + "black steel. The symbol of a great winged drake is engraved "
      + "upon the weapon's grooved blade.\n";
    else
        return "This is a long, thick bladed dagger made from a "
      + "black steel. The symbol of a great winged drake is engraved "
      + "upon the weapon's grooved blade, in which you notice a "
      + "clear liquid sits.\n";
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

            poison->move(enemy);
            poison->set_time(500);            /* Nice and long */
            poison->set_interval(20);
            poison->set_strength(60);
            poison->set_damage(({POISON_FATIGUE, 100}));
            poison->start_poison();
            tell_object(query_wielded(),
        "The thick black-steel blade causes a vicious, deep cut in your "
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
    TP->catch_msg(BSN("As you grip the dagger you notice the weapon is remarkably well balanced."));
  return 1;
}

int
unwield()
{
    query_wielded()->catch_msg(BSN("You release your grip on the black dagger."));
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
