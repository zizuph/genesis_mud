//  /bazaar/Obj/wield/jdagger.c
// creator(s): Ilyian, May, 1995
// last update: October 8,1995: When jadestone dies, the
//              number of poisons left will be dropped
//              down to 4, and the HP strength of the
//              poison will be much weakened.
// Cirion, 4 April, 1996 - Updated it in accordance with man weapon_guide
//              per request by Boron.
// Cirion, 22 April 1996 - Made it more difficult to poison someone. You now
//              need to 'graze' them for a poison, strict typed it.
// purpose: Poisoned dagger for Jadestone Doll
// note: The dagger starts with 15 poisons, which will
//       be set at a strength of 300.
// bug(s):
// to-do:

#pragma strict_types

inherit "/d/Avenir/inherit/weapon";
inherit "/lib/keep";

#include <stdproperties.h>
#include <macros.h>
#include <wa_types.h>
#include <ss_types.h>
#include <formulas.h>
#include <filter_funs.h>
#include <poison_types.h>
#include <math.h>
#include "/d/Avenir/common/common.h"

/* Default configurations */
int poison_left = 15;
int my_strength = 300;
// Very powerful poison, at first....

void poison_enemy(object enemy, string hdesc);

void create_weapon()
{
    set_name("cinquedea");
    add_name(({"knife","dagger","weapon","blade"}));
    add_pname(({"cinquedeas","knives","daggers","weapons","blades"}));
    set_short("sinuous cinquedea");
    set_long("@@long_desc");
    set_adj("sinuous");
    add_adj("steel");

    set_hit(16);
    set_pen(14);   // as good as a non-magical knife is allowed to be
    set_wt(W_KNIFE);

    set_dt(W_IMPALE);
    set_hands(W_RIGHT);
    set_keep(1);

    add_prop(OBJ_I_VALUE, 1183);
    add_prop(OBJ_I_WEIGHT, 800);
    add_prop(OBJ_I_VOLUME, 1000);
    add_prop(OBJ_I_NO_DROP, "@@special_drop");

}

string stat_object()
{
   string special_info;
   special_info = "Number of poisons left: " + poison_left
          + ".\nHP damage strength of poison: "+my_strength+".\n";
   return ::stat_object() + special_info;
}


string long_desc()
{
    string eye;

    if(poison_left > 0)
       eye = "A tiny emerald eye is set in the handle's "+
             "serpent, and it gleams with a strange blue glow.\n";
    else
       eye = "A tiny emerald eye is set in the handle's "+
             "serpent which is a flat dark blue.\n";

    return "This long dagger is of marvelous craftsmanship. The "+
           "thin steel blade extends straight out from the hilt, "+
           "which is solid steel and crafted to look like two "+
           "intertwining serpents. At the tip of the blade is a "+
           "tiny notch leading into a hollow center in "+
           "the blade. " + eye;
}

int special_drop()
{
    object  tp = ENV(TO);

    if (tp->query_npc() && tp->id("jadestone") && 
        !query_prop(OBJ_I_BROKEN) && tp->query_hp() > 400) 
        {
        tell_room(ENV(tp), QCTNAME(tp) + " holds tightly"
          +" to the handle of her "+query_short()+".\n", tp);
        return 1;
        }
    else
        return 0;
// So the dagger can't be brawled from Jadestone Doll's
// hands.
}

public varargs int
did_hit(int aid, string hdesc, int phurt, object enemy, int dt,
        int phit, int dam)
{
    int i = ::did_hit(aid, hdesc, phurt, enemy, dt, phit, dam);

    if(poison_left > 0 && phurt >= 5 && !random(2))  // phurt >= 5  =  'graze'
        poison_enemy(enemy, hdesc);

    return i;
}

void poison_enemy(object enemy, string hdesc)
{
    object poison;

    seteuid(getuid(TO));
    poison = clone_object(BAZAAR+"Obj/misc/j_poison");
    poison_left--;
    enemy->catch_msg("You feel a stinging sensation in your "+
                          hdesc+".\n");
    query_wielded()->catch_msg("You turn the tip of the "+short()+
           " in "+QTNAME(enemy)+"'s "+hdesc+", and see some poison "+
           "enter the wound.\n");

    poison->reconfig_me(my_strength);
    poison->move(enemy, 1);
    poison->start_poison();
    return 0;
}

void weaken_poison(int newstr)
{
    my_strength = newstr;
    return;
}


void enter_env(object to, object old)
{
   ::enter_env(to, old);

   if(interactive(to))
    {
     weaken_poison(55);
     if(poison_left>4)
         poison_left = 4;
    }
}

