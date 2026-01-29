/*******************************************************************\
| ARMOURY_SHELF.C                                                   |
\*******************************************************************/

/*
 * 03/09/12 Arandir     Created
 *
 */

#include <language.h>

#include "../defs.h"

inherit DG_OBJ_TABLE_BASE;

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

  add_prop(CONT_I_MAX_WEIGHT, 2000000);
  add_prop(CONT_I_MAX_VOLUME, 2000000);
}

//-------------------------------------------------------------------

void enter_inv (object oWhat, object oFrom)
{
  ::enter_inv (oWhat, oFrom);
  environment ()->m_observe_drop (oFrom, oWhat);
}


void leave_inv (object oWhat, object oWhere)
{
  ::leave_inv (oWhat, oWhere);
  environment ()->m_observe_take (oWhere, oWhat);
}

//-------------------------------------------------------------------

