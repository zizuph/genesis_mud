/*******************************************************************\
| TRASHCAN.C                                                        |
\*******************************************************************/

/*
 * 03/09/13 Arandir     Created
 * 03/12/12 Arandir     Made the trashcan bigger
 *
 */

#include <stdproperties.h>

#include "../defs.h"

inherit "/std/container";

//-------------------------------------------------------------------

void create_container ()
{
  ::create_container ();

  set_name ("trashcan");
  set_adj (({ "small", "round", "simple" }));
  set_short ("small trashcan");
  set_long ("The trashcan is of a simple design, small and round.\n");

  add_prop (CONT_I_MAX_WEIGHT, 1000000);
  add_prop (CONT_I_MAX_VOLUME, 1000000);
  add_prop (CONT_I_WEIGHT, 10000);
  add_prop (CONT_I_VOLUME, 10000);
  add_prop (CONT_I_ATTACH, FALSE);
  add_prop (CONT_I_TRANSP, FALSE);
  add_prop (CONT_I_RIGID, TRUE);
  add_prop (OBJ_I_VALUE, 1000);
  add_prop (OBJ_M_NO_GET, "It does not move.\n");

  set_no_show_composite (TRUE);
}

//-------------------------------------------------------------------

