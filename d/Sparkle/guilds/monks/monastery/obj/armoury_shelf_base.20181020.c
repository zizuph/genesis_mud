/*******************************************************************\
| ARMOURY_SHELF_BASE.C                                              |
\*******************************************************************/

/*
 * 03/09/12 Arandir     Created
 * 10/10/21 Lavellan    Modified for new saving rack system.
 *          Inherited by individual racks now, not all clones of same object.
 *
 */

#pragma no_clone

#include <language.h>

#include <macros.h>     //for IS_CLONE

#include "../defs.h"

inherit DG_OBJ_TABLE_BASE;
inherit "/d/Genesis/specials/lib/item_recovery_lib.c";

//-------------------------------------------------------------------

/*
 * Function name : m_configure_shelf
 * Descriptions  : Sets basic characteristics of the shelf
 *
 */

void m_configure_shelf (
  string *asAdj,
  string sShort,
  string sPrefix)
{
  add_adj (asAdj);
  set_short (sShort);
  dg_set_description_prefix (sPrefix);

}


/*
 * Function name : create_container
 *
 */

void create_container ()
{
  ::create_container ();

  set_name ("shelf");
  set_adj (({ "wooden", "armoury" }));

  set_long ("The wooden shelf is made of thick and rough " +
            "oak boards, anchored at both ends in the " +
            "stone walls. An extra beam of the same " +
            "wood supports the boards in the middle, " +
            "making the entire structure look sturdy " +
            "indeed.\n");

  add_prop(CONT_I_MAX_WEIGHT, 4000000);
  add_prop(CONT_I_MAX_VOLUME, 4000000);

  if (IS_CLONE)
  {
    set_enable_logging(0);
    set_enable_recovery(1);
    init_database();
    set_alarm(0.0, 0.0, &recover_objects_from_database()); 
  }
}

//-------------------------------------------------------------------

void enter_inv (object oWhat, object oFrom)
{
  ::enter_inv (oWhat, oFrom);
  environment ()->m_observe_drop (oFrom, oWhat);
  
  
  if (oFrom == this_object())
  {
    return;
  }
  add_rack_entry(oWhat);
}


void leave_inv (object oWhat, object oWhere)
{
  ::leave_inv (oWhat, oWhere);
  environment ()->m_observe_take (oWhere, oWhat);
  
  
  if (oWhere == this_object() || !objectp(oWhere))
  {
    // Not actually leaving this container, just return
    return;
  }
  remove_rack_entry(oWhat);
}

//-------------------------------------------------------------------
