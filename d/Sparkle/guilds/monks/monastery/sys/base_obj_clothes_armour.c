/*******************************************************************\
| BASE_OBJ_CLOTHES_ARMOUR.C                                         |
\*******************************************************************/

/*
 * 03/05/10 Arandir     Created
 *
 */

#include <macros.h>
#include <language.h>

#include "../defs.h"

inherit "/std/armour";

//-------------------------------------------------------------------

// This is a mixin that cannot be inherited because of
// conflicts between armour and wearable classes.

#define M_CLOTHES_ARMOUR
#include "base_obj_clothes.h"

//-------------------------------------------------------------------

