
/* Ckrik 1998
 * Modified by Marisol (08/31/98) to be used in Ovejuno, Emerald.
*/

inherit "/std/weapon";

#include "/sys/stdproperties.h"
#include "/sys/wa_types.h"
#include "/sys/formulas.h"
#include "/sys/macros.h"

#define WEAPON_HIT 40
#define WEAPON_PEN 40


void
create_weapon()
{
    set_name("sword");
    set_pname("swords");
    add_name("broadsword");
    add_pname("broadswords");

    set_adj("long-broaded");
    add_adj("silver-alloyed");

    set_short("long-broaded silver-alloyed broadsword");
    set_pshort("long-broaded silver-alloyed broadswords");
    
    set_long("A long-broaded silver-alloyed broadsword. It is "+
        "a beautiful elvish blade, long and broad and deadly " +             
        "beautiful as elvish weapons go. But don't be deceit by its "+
        "beauty. It could kill you as easy as slicing butter.\n");

    set_hit(WEAPON_HIT);
    set_pen(WEAPON_PEN);
    set_wt(W_SWORD);
    set_dt(W_SLASH | W_BLUDGEON);
    set_hands(W_BOTH);
    set_wf(this_object());

    add_prop(OBJ_I_VALUE, F_VALUE_WEAPON(WEAPON_HIT,WEAPON_PEN) + 500);
    add_prop(OBJ_I_WEIGHT, F_WEIGHT_DEFAULT_WEAPON(WEAPON_HIT,WEAPON_PEN) +
           3000);

    add_prop(OBJ_I_VOLUME, query_prop(OBJ_I_WEIGHT) / 5);
}

mixed
wield()
{
    if (this_player()->query_stat(0) < 80)
    {
      return "You are too weak to wield the " +
        this_object()->query_short() + ".\n";
    }

    return 0;
}

string
query_recover()
{                                                             
  {
  return MASTER + ":" + query_wep_recover();
  }
}


void
init_recover(string arg)
{
    init_wep_recover(arg);
}                   
