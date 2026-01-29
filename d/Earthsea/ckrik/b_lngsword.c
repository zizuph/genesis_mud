inherit "/std/weapon";

#include "/sys/stdproperties.h"
#include "/sys/wa_types.h"
#include "/sys/formulas.h"
#include "/sys/macros.h"

#define WEAPON_HIT 35
#define WEAPON_PEN 39


void
create_weapon()
{
  set_name("sword");
  set_pname("swords");
  add_name("longsword");
  add_pname("longswords");
  
  set_adj("bronze");
  set_adj("shiny");

  set_short("shiny bronze longsword");
  set_pshort("shiny bronze longswords");
  
  set_long("This longsword is standard issue for the castle" +
	   " guards. It is long and of medium width giving it strength," +
	   " without too much extra weight. Its bronze metallic" +
	   " colour gives off a golden orange sheen. It is well" +
	   " forged and balanced, an excellent weapon indeed.\n");

  set_hit(WEAPON_HIT);
  set_pen(WEAPON_PEN);
  set_wt(W_SWORD);
  set_dt(W_SLASH | W_IMPALE);
  set_hands(W_ANYH);
  
  add_prop(OBJ_I_VALUE, F_VALUE_WEAPON(WEAPON_HIT,WEAPON_PEN) + random(20) -10);
  add_prop(OBJ_I_WEIGHT, F_WEIGHT_DEFAULT_WEAPON(WEAPON_HIT,WEAPON_PEN) + random(50) - 25);
  
  add_prop(OBJ_I_VOLUME, query_prop(OBJ_I_WEIGHT)/5);
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
