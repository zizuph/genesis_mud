/*******************************************************************\
| COUNCIL_POST.C                                                    |
\*******************************************************************/

/*
 * 98/06/14 Cirion	Created
 * 02/05/01 Arandir	Ported to new area without rewrite
 * 03/04/25 Arandir     Polished up
 * 03/09/09 Arandir     Added the elders alias
 * 04/08/15 Arandir     Added the missing inside property
 *
 */

#include <stdproperties.h>

#include "../defs.h"

inherit M_ROOM_BASE;

inherit "/d/Genesis/lib/post";

//-------------------------------------------------------------------

void create_room ()
{
  set_short ("small, quiet room");
  set_long ("This is a small, quiet room. There is a wide doorway " +
            "in the south wall, and three oaken writing desks against the " +
            "other three walls. The room is quiet, solemn, a place that " +
            "has a feel of calmness and contemplation.\n");

  add_prop (ROOM_I_INSIDE, TRUE);

  add_exit ("council", "south");
}

//-------------------------------------------------------------------

void init ()
{
  ::init ();
  post_init ();
}

void leave_inv (object oWhat, object oWhere)
{
  ::leave_inv (oWhat, oWhere);
  post_leave_inv (oWhat, oWhere);
}

void add_aliases (object oReader)
{
  oReader->set_alias ("guildmaster", M_MASTERS_ACTIVE);
  oReader->set_alias ("council", m_get_council_members ());
  oReader->set_alias ("elders", m_get_elder_members ());
}

//-------------------------------------------------------------------

/*
 * Function name : query_prevent_snoop
 * Description   : Wizards should not snoop on council affairs.
 *
 */

int query_prevent_snoop ()
{
  return (TRUE);
}

//-------------------------------------------------------------------

