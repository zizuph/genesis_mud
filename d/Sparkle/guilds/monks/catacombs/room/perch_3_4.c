/*******************************************************************\
| PERCH_3_4.C                                                       |
\*******************************************************************/

/*
 * 03/07/23 Arandir     Created
 *
 */

#include "../defs.h"

inherit CC_ROOM_PERCH_BASE;

//-------------------------------------------------------------------

void create_room ()
{
  cc_create_perch (
    3, 4,
    "carrying a relief of a large and luxurious room, furnished with " +
    "most expensive items from an ornate throne to priceless silver " +
    "mirrors.",
    "carrying a relief of an expensively furnished room, dominated by " +
    "a shimmering shape of a magnificient red dragon.",
    "krynn red dragon",
    "The shimmering shape of the red dragon is magnificent in its size, " +
    "with strong muscles bulging under brilliantly red skin. Its teeth " +
    "and talons look sharp and very destructive, and its eyes shine with " +
    "intelligence and malevolence.");
}

//-------------------------------------------------------------------

