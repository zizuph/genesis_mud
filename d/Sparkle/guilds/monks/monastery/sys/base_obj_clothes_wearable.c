/*******************************************************************\
| BASE_OBJ_CLOTHES_WEARABLE.C                                       |
\*******************************************************************/

/*
 * 03/05/10 Arandir     Created
 *
 */

#include <macros.h>
#include <language.h>

#include "../defs.h"

inherit "/std/object";
inherit "/lib/wearable_item";

//-------------------------------------------------------------------

// This is a mixin that cannot be inherited because of
// conflicts between armour and wearable classes.

#define M_CLOTHES_WEARABLE
#include "base_obj_clothes.h"

//-------------------------------------------------------------------

