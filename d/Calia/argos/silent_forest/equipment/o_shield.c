/*   o_shield.c
 *
 *  The spiked obsidian shield, a pretty
 *  good shield, breaks slightly easier
 *  then regular armours. It cowers the arm
 *  its worn on and the torso.
 *
 * Baldacin@Genesis, Sep 2003
 * Fixed typo - Jaacar, May 2016
 */
inherit "/std/armour";
#include "../ldefs.h"
#include <formulas.h>
#include <stdproperties.h>

string
query_inverted()
{
    return (SFEQDIR + "c_shield.c");
}
 
void create_armour() 
{
    set_name("shield");
    set_adj(({"spiked","obsidian"}));
    set_short("spiked obsidian shield");
    set_long("This shield, made of pure obsidian is heavily ornamented with "+
      "gems and pearls, forming a magnificent pattern. Steel spikes has been "+
      "garnished around the edge of the shield, mostly for decorating purposes. "+
      "It feels very light, which probably affects its condition.\n");
    set_ac(35);
    set_at(A_SHIELD);
	set_af(TO);
    add_prop(OBJ_I_WEIGHT, 2200);
    add_prop(OBJ_I_VOLUME, 1600);
    add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(22 + random(15)));
    
    set_likely_cond(5);
    
    add_item(({"magnificent pattern", "pattern"}),"The decorating gems and pearls "+
      "forms a magnificent pattern, resembling an ancient dragon.\n");
}

/*
 * Function name: fix_slots
 * Description  : This updates the shield with the new shield slots
 * Arguments    : 
 * Returns      : 
 */
void
fix_slots()
{
  int *slot;
  object wearer = TO->query_worn();

  /* If it's not worn, bail out! */
  if (!wearer) 
	  return;

  slot = TO->query_slots();

  if(slot[0] == 512)
  {
     TO->set_shield_slot(({ TS_TORSO, TS_RARM }));
  }
 
  if(slot[0] == 1024)
  {
     TO->set_shield_slot(({ TS_TORSO, TS_LARM }));
  }

  wearer->update_armour(TO);
}

mixed
wear(object obj)
{
	set_alarm(0.5, 0.0, &fix_slots());
	return 0;
}

int
remove()
{
	return 0;
}