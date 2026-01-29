/*
 *   This is one of the weapons used by the roughians in sanction.
 *   Adapted from the Ebony dagger in Gondor.
 *   Navarre January 24th 2008.
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
#define POISON -5

//    Prototypes:
void  init_recover(string  arg);
string long_desc();
int poison_used;

public void
create_weapon()
{
    set_name(({"dagger", "knife"}));
    set_adj("sickly");
    add_adj("green");
    add_adj("thin");
    add_adj("sharp");
    add_adj("steel");
    set_short("sickly green dagger");
    set_long(long_desc);

    set_hit(30);
    set_pen(20);
    set_wt(W_KNIFE);

    set_dt(W_IMPALE | W_SLASH);
    set_hands(W_ANYH);

    add_prop(OBJ_I_WEIGHT, F_WEIGHT_DEFAULT_WEAPON(30, W_KNIFE));
    add_prop(OBJ_I_VOLUME, query_prop(OBJ_I_WEIGHT) / 2);
    add_prop(OBJ_I_VALUE, F_VALUE_WEAPON(30, 20));
    poison_used = POISON;
}

string
long_desc()
{
    if(poison_used >= 1)
        return "This is a thin steel dagger with an incredible sharp blade. " +
               "The blade has an unusual green colour, and the white bone " +
               "handle makes it stand out even more.\n";
    else
        return "This is a thin steel dagger with an incredible sharp blade. " +
               "The blade has an unusual green colour, and the white bone " +
               "handle makes it stand out even more.\n" +
               "The blade is covered in sticky clear liquid can be seen.\n";
}

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
            poison->move(enemy, 1);
            poison->set_time(900);
            poison->set_interval(35);
            poison->set_strength(75);
            poison->set_damage(({POISON_HP, 90, POISON_STAT, SS_STR}));
            poison->set_poison_type("snake_poison");
            poison->start_poison();
            tell_object(query_wielded(),
                        "The sickly green blade leaves a foul poison in your wound.\n");
            return 0;
        }
        else 
            write("Failed to load poison for some reason.\n"); 
    }
    return 0;
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
