/*********************************************************************
 * - dagger.c                                                      - *
 * - Created by Damaris 7/2005                                     - *
 * - Optimized a bit by Tapakah, 05/2021                            - *
 *********************************************************************/

#pragma strict_types

#include <stdproperties.h>
#include <wa_types.h>

#include "../defs.h"

inherit SM_WEAPON;

void
create_weapon()
{
  set_name(({"dagger", "knife"}));
  set_pname(({"daggers", "knives"}));
  set_short("fine dagger");
  set_adj(({"fine"}));
  set_long("This is a finely forged " + short() + ". It "+
           "is amazingly light as daggers go. It has intricate "+
           "etchings along the slender handle.\n");
  add_item(({"etching", "etchings"}),
           "The etchings along the handle are precise in design.\n");
  add_item(({"design"}),
           "The design is of a flaming tree.\n");
  add_item(({"handle", "slender handle"}),
           "The handle is slender with etchings along the side.\n");
  add_item(({"blade"}),
           "The blade is two sided and appears to have a jagged edge "+
           "to one side.\n");
  add_item(({"jagged edge", "edge"}),
           "The jagged edge has a sheen to it.\n");
  set_default_weapon(14, 14, W_KNIFE, W_SLASH | W_IMPALE, W_ANYH);
  add_prop(OBJ_I_VALUE, query_prop(OBJ_I_VALUE)+random(300));
  set_wf(TO);
  set_likely_dull(5);
  set_likely_break(5);
}

