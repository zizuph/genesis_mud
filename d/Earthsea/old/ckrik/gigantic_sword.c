inherit "/d/Earthsea/std/weapon";

#include "/sys/stdproperties.h"
#include "/sys/wa_types.h"
#include "/sys/formulas.h"
#include "/sys/macros.h"

#define WEAPON_HIT 40
#define WEAPON_PEN 40


void
create_earthsea_weapon()
{
  set_name("sword");
  set_pname("swords");
  add_name("broadsword");
  add_pname("broadswords");

  set_adj("gigantic");
  add_adj("steel");

  set_short("gigantic steel broadsword");
  set_pshort("gigantic steel broadswords");
  
  set_long(break_string("A gigantic steel broadsword. It is extraordinarily " +
	   "long and has a blade wider than any sword you have " +
	   "ever seen. It is very heavy. This sword should be " +
	   "to inflict a lot of damage on its victims.\n", 70));

  set_hit(WEAPON_HIT);
  set_pen(WEAPON_PEN);
  set_wt(W_SWORD);
  set_dt(W_SLASH | W_BLUDGEON);
  set_hands(W_BOTH);
  set_wf(this_object());
  
  add_prop(OBJ_I_VALUE, F_VALUE_WEAPON(WEAPON_HIT,WEAPON_PEN) + 500);
  add_prop(OBJ_I_WEIGHT, F_WEIGHT_DEFAULT_WEAPON(WEAPON_HIT,WEAPON_PEN) + 
	   5000);
  
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
  return MASTER + ":" + query_wep_recover();
}

void
init_recover(string arg)
{
    init_wep_recover(arg);
}

