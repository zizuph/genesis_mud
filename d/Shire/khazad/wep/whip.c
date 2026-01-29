//
// whip.c 
// 
// A first test to see if it is possible at all to make whips.
// Rogon.
//
// Ported by Dunstable for the New Moria 1/8/96

inherit "/std/weapon";

#include <wa_types.h>
#include <ss_types.h>
#include <formulas.h>
#include <stdproperties.h>
#include <macros.h>
#include <cmdparse.h>
#include <language.h>

void
create_weapon()
{
    set_name("whip");
    set_short("@@my_short@@");
    set_long("This blackened whip nearly blisters your hands "+
    "with its intense heat, though no flame is visible. It has three "+
    "clusters of sharp blackened thongs attached to the end of its "+
     "long, strong handle by a string of material you cannot recognize. "+
    "The handle itself is of a cold black metal, as strong and light as "+
    "mithril, yet somehow of fouler make.\n");
    set_adj(({"many-thonged","many","thonged"}));
    add_adj(({"blackened","flaming"}));
    set_hit(26);
    set_pen(39);
    set_wt(W_POLEARM); 
    set_dt(W_SLASH);
    set_hands(W_ANYH); 
    add_prop(OBJ_I_VALUE, F_VALUE_WEAPON(26,39)+ random(200));
    add_prop(OBJ_I_VOLUME, 1000);
    add_prop(OBJ_I_WEIGHT,  400);

}

string
my_short()
{
   object wielder;

  wielder = query_wielded();
  if(wielder->query_npc())
  {
	  return "flaming many-thonged whip";
    }
  else
	return "blackened many-thonged whip";
}
