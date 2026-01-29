/*   c_shield.c
 *
 *  The spiked crystal shield, a pretty
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
 
void create_armour() 
{
    set_name("shield");
    set_adj(({"spiked","crystal"}));
    set_short("spiked crystal shield");
    set_long("This shield, made of pure crystal is heavily ornamented with "+
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

/*
 * Function name: remove_broken
 * Description  : The armour got broken so we remove it from the
 *                player.
 * Arguments    : int silent - true if no message should be generated
 *                             about the fact that the armour breaks.
 */
void 
remove_broken()
{
    object wearer = TO->query_worn();
    object shards;

    /* If it's not worn, bail out! (Ehh, it should be worn though)*/
    if (!wearer) 
        return ::remove_broken();

    object room = environment(wearer);

    tell_object(wearer, "The " + short(wearer) + " breaks!!!\nWhat used "+
        "be a splendid piece of crystal armour is now only a pile of "+
        "broken shards on the ground.\n");
    tell_room(environment(wearer), "The " + QSHORT(this_object()) +
        " worn by " + QTNAME(wearer) + " breaks!!!\nWhat used "+
        "to be a splendid piece of crystal armour is now only "+
        "a pile of broken shards on the ground.\n", wearer);

    if (objectp(room))
    {
        setuid();
        seteuid(getuid());
	shards = clone_object(SFOBJDIR+"crystal_shards.c");
	shards->add_prop(OBJ_I_WEIGHT,  TO->query_prop(OBJ_I_WEIGHT));
	shards->add_prop(OBJ_I_VOLUME,  TO->query_prop(OBJ_I_VOLUME) / 2);
	shards->move(environment(wearer), 1);
    }

    return TO->remove_object();
}

