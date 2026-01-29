
/* Magic armour 

   Conjured by the Teikos spell of the Elemental Worshippers.

   Coded by Jaacar 

   Modifications by Maniac 30/9/96
*/

#include "defs.h"
#include <wa_types.h>
#include <stdproperties.h>
#include <ss_types.h>
#include <macros.h>
#include SPELLS_HEADER

inherit "/std/armour";
inherit WOR_MAGIC_OBJECT;


void 
create_armour()
{
    set_name("teikos armour");
  add_name(TEIKOS_ARM);
  set_no_show();
  remove_prop(OBJ_I_VALUE);
  remove_prop(OBJ_I_VOLUME);
  remove_prop(OBJ_I_WEIGHT);

  add_prop(OBJ_M_NO_DROP, 1); 
  add_prop(OBJ_M_NO_GIVE, 1); 
  add_prop(OBJ_I_IS_MAGIC_ARMOUR, 1); 
    add_prop(OBJ_I_INVIS,1);
    add_prop(MAGIC_AM_MAGIC,1);

  set_ac(15);
  set_at(A_MAGIC);
  set_af(this_object());

  set_shield_slot( ({ A_HEAD, A_BODY, A_L_ARM, A_R_ARM, A_LEGS}) );

  /* Will provide better protection from bludgeoning
   * weapons, not so good against impaling daggers, etc */

  /*      slash, impale, bludgeon */
  set_am(({ 2,   5,     9 }));

  set_element(SS_ELEMENT_EARTH);
  set_form(SS_FORM_DIVINATION);
}

/*
 * Spell timeout, or dispelled
 */
void notify_dispel_magic(object dispeller)
{
  query_worn()->catch_msg("The faceted light about you fades "
    + "away.\n");
}

/*
 * init_spell called from move_spell ... give the
 * message of the armour being created
 */
void init_spell(object caster, object target, object prev)
{
   set_this_player(target);
   wear_me();  // We needed to set_this_player for this...

   target->add_subloc(TEIKOS_ARM, this_object());
   target->catch_msg("Suddenly, a field of grey, faceted "
    + "light arises around you, indistinct and vague.\n"
    + "Strange shapes seem to weave across the light.\n");
}

/*
 * Show the armour, while it is in effect
 */
public string
show_subloc(string subloc, object me, object observer)
{
  if((me->query_prop(TEMP_SUBLOC_SHOW_ONLY_THINGS)) ||
     (subloc != TEIKOS_ARM) || query_worn() != me)
    return "";

  return "An indistinct field of grey, faceted light "
    + "surrounds " + ( observer == me ? "you" :
      me->query_objective() ) + ".\n";
}

// The armour protects everywhere.
int *query_shield_slots()
{
  return ({ A_HEAD, A_BODY, A_L_ARM, A_R_ARM, A_LEGS});
}


/*
 * Function name: got_hit
 * Description:   Notes that the defender has been hit. It can be used
 *                to reduce the ac for this hitlocation for each hit.
 * Arguments:     hid:   The hitloc id, ie the bodypart hit.
 *                ph:    The %hurt
 *                att:   Attacker
 *                aid:   The attack id
 *                dt:    The damagetype
 *                dam:   The damage done to us in hit points
 */
varargs int
got_hit(int hid, int ph, object att, int dt, int dam)
{
    if(dam <= 0)
        return 0;

       query_worn()->catch_msg("The faceted light around you " +
            "shifts.\n");
    tell_room(environment(query_worn()),"The faceted light surrounding "+
        QNAME(query_worn())+" shifts.\n",({ query_worn() }));

    return ::got_hit(hid, ph, att, dt, dam);
}

/*
 * called from the set_at - we want to be able to wear
 * the armour without printing messages
 */
public mixed wear(object obj)
{
  return 1;
}

public mixed remove(object obj)
{
  return 1;
}

query_recover()
{
    return 0;
}

void set_likely_break(int i)
{
    i=0;
    ::set_likely_break(i);
}

int set_condition(int i)
{
    i=0;
    ::set_condition(i);
}

varargs void
remove_broken(int silent = 0)
{
    return;
}
