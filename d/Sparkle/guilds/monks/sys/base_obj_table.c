/*******************************************************************\
| BASE_OBJ_TABLE.C                                                  |
+-------------------------------------------------------------------+
| Base table module for the dragon area.                            |
\*******************************************************************/

/*
 * 98/06/06 Cirion	Created
 * 02/02/12 Arandir	Ported to the new area
 * 03/12/12 Arandir     Made the table a larger container
 * 03/12/23 Arandir     Removed the default name
 *
 */

#include <composite.h>
#include <filter_funs.h>
#include <stdproperties.h>

#include "../defs.h"

inherit "/std/container";

//-------------------------------------------------------------------

// The number of items visible on the table.

#define DG_TABLE_NOTICE		5

// The default prefix of the table description.

string sDescPrefix = "Standing in the room is a table";

//-------------------------------------------------------------------

/*
 * Function name : dg_compare_volume
 * Description   : Compares two objects by volume.
 *
 */

int dg_compare_volume (object oA, object oB)
{
  int iVolumeA, iVolumeB;

  iVolumeA = oA->query_prop (OBJ_I_VOLUME);
  iVolumeB = oB->query_prop (OBJ_I_VOLUME);

  if (iVolumeA == iVolumeB) return (0);
  if (iVolumeA < iVolumeB) return (1);
                      else return (-1);
}

/*
 * Function name : dg_get_description
 * Description   : Returns a description of the table with most
 *                 prominent contained objects included.
 *
 */

string dg_get_description ()
{
  object *aoItems;
  int    iItems;
  string sDesc;

  sDesc = sDescPrefix;

  aoItems = FILTER_DEAD (all_inventory ());
  switch (sizeof (aoItems))
  {
    case 0:
      sDesc += ".";
      break;

    case 1 .. DG_TABLE_NOTICE:
      sDesc += ", upon which you see " +
               COMPOSITE_DEAD (aoItems) +
               ".";
      break;

    default:
      sDesc += ", scattered upon which are many things, including " +
               COMPOSITE_DEAD (sort_array (aoItems, dg_compare_volume) [0 .. DG_TABLE_NOTICE - 1]) +
               ".";
      break;
  };

  return (sDesc);
}

//-------------------------------------------------------------------

/*
 * Function name : dg_set_description_prefix
 *
 */

void dg_set_description_prefix (string sPrefix)
{
  sDescPrefix = sPrefix;
}

//-------------------------------------------------------------------

void create_container ()
{
  ::create_container ();

  add_prop (CONT_I_MAX_WEIGHT, 1000000);
  add_prop (CONT_I_MAX_VOLUME, 1000000);
  add_prop (CONT_I_WEIGHT, 100000);
  add_prop (CONT_I_VOLUME, 100000);
  add_prop (CONT_I_ATTACH, TRUE);
  add_prop (CONT_I_RIGID, TRUE);
  add_prop (OBJ_I_VALUE, 1000);
  add_prop (OBJ_M_NO_GET, "It does not move.\n");

  set_no_show_composite (TRUE);
}

//-------------------------------------------------------------------

