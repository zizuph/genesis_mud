/*******************************************************************\
| DOMAIN.C                                                          |
\*******************************************************************/

/*
 * 06/02/12 Arandir     Created
 *
 */

#include "defs.h"

inherit "/std/room";

inherit S_LIB_OBJECT;

void create_room ()
{
  set_short ("domain workroom");
  set_long ("This is the Sparkle Domain Workroom.\n");

  s_clone_here (S_DOMAIN_BOARD);
}

