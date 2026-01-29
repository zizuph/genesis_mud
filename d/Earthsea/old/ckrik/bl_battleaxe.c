/* Created by Ckrik Nov 1997 for Earthsea in Genesis
 * Gorn's Axe
 *
 */
inherit "/d/Earthsea/std/weapon";

#include "/sys/stdproperties.h"
#include "/sys/wa_types.h"
#include "/sys/formulas.h"
#include "/sys/macros.h"
#include <ss_types.h>


/* Hit varies from 35 to 55 dependning on the user's polearm skill.
 */
#define WEAPON_HIT 35
#define WEAPON_PEN 55


void
create_earthsea_weapon()
{
  set_name("axe");
  set_pname("axes");
  add_name("battleaxe");
  add_pname("battleaxes");
  
  set_adj("blackened");
  set_adj("heavy");
  
  set_short("blackened heavy battleaxe");
  set_pshort("blackened heavy battleaxes");
  
  set_long("A blackened heavy battleaxe. It is long and extremely " +
	   "heavy. Just a bit longer and this axe would qualify as " +
	   "a halberd. A gigantic double blade, decorated by eerie " +
	   "dragon reliefs, topping the long handle " +
	   "makes this axe extremely lethal. It can probably hack " +
	   "someone in half without any trouble.\n");
  
  set_hit(WEAPON_HIT);
  set_pen(WEAPON_PEN);
  set_wt(W_AXE);
  set_dt(W_SLASH | W_BLUDGEON);
  set_hands(W_BOTH);
  set_wf(this_object());

  add_prop(OBJ_I_VALUE, F_VALUE_WEAPON(WEAPON_HIT,WEAPON_PEN) + random(100) 
	   + 1500);
  add_prop(OBJ_I_WEIGHT, F_WEIGHT_DEFAULT_WEAPON(WEAPON_HIT,WEAPON_PEN) 
	   + random(5000) + 25000);
  
  add_prop(OBJ_I_VOLUME, query_prop(OBJ_I_WEIGHT) / 8);
  add_prop(OBJ_M_NO_BUY, 1);
  add_prop(OBJ_I_IS_MAGIC_WEAPON, 1);
  add_prop(OBJ_S_WIZINFO,
	   "This weapon magically exists in a flux as " +
	   "both an axe and a polearm, though it seems to want " +
	   "to stay as an axe. A mage tried to change the property " +
	   "of this axe and failed. A person that has skill in " +
	   "handling polearms will be able to control this strange " +
	   "weapon better. Also, because it is made of a " +
	   "special enchanted, but extremely dense, alloy, " +
	   "it causes severe damage to its victims. " +
	   "Its to_hit varies between 35 and 55 depending on " +
	   "the polearm skill of the user.\n");
  add_prop(MAGIC_AM_ID_INFO,
	   ({"This weapon is magically enchanted.\n", 5,
	       "You find that it magically exists " +
	       "in a flux as both an axe and a polearm, though " +
	       "it seems to want to stay as an axe.\n", 20,
	       "It seems to be made of an enchanted, but " +
	       "extremely dense, alloy that allows it to " +
	       "cause severe damage to its victims.\n", 35,
	       "A person that has skill in handling " +
	       "polearms will be able to control this strange " +
	       "weapon better.\n", 51}));
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



mixed
wield()
{    
  if (this_player()->query_stat(0) < 70)
    return "You lack the strength to wield the " + 
      this_object()->query_short() + ".\n";
 
  if (this_player()->query_stat(3) < 60 ||
      this_player()->query_stat(4) < 80 ||
      this_player()->query_skill(SS_WEP_AXE) < 75)
    {
      this_object->move(environment(this_player()));
      tell_room(environment(this_player()), QCTNAME(this_player()) +
		" fumbles and drops the " + this_object()->query_short());
      return "You wield the " + this_object()->query_short() +
	", but you can't seem handle it and drop it.\n";
    }

  if (this_player()->query_stat(5) < 70)
    {
      return "The dragon relief glows bright red and you decide " +
	"it's better to not to wield it.\n";
    }

  write("You feel you like splitting " +
	"someone in half wielding this axe.\n");
  say(QCTNAME(this_player()) + "'s eyes flare with " +
      "the urge of creating carnage.\n");
  set_hit(WEAPON_HIT + 
	  (this_player()->query_skill(SS_WEP_POLEARM) - 
	   (this_player()->query_skill(SS_WEP_POLEARM) % 10)) / 5); 
  return 1;
}

int
unwield()
{
  say(QCTNAME(query_wielded()) + " looks normal again.\n");
  set_hit(WEAPON_HIT);
  return 0;
}
