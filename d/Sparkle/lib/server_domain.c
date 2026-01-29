/*******************************************************************\
| SERVER_DOMAIN.C                                                   |
+-------------------------------------------------------------------+
| Data holder for the entire domain. The object is responsible for  |
| holding all persistent structures related to the domain. The      |
| domain libraries can use this object to obtain a reference        |
| to any structure. No structures are changed here except           |
| for the versioning related conversions.                           |
\*******************************************************************/

/*
 * 06/03/18 Arandir     Added development hook
 * 06/02/08 Arandir     Created
 *
 */

#include "defs.h"

//-------------------------------------------------------------------

/*
 * Function name : create
 *
 */

void create ()
{
  // We have to preload rooms where the message boards reside to
  // make sure an instance of the board will always be ready when
  // a note is to be posted from within the code.

  S_LOAD (S_COMMON_ROOM_DIR + "domain");

  // Launch activities that take care of various domain mechanics.

  S_LIB_LOGGING->s_logging_hook_create ();
  S_LIB_DEVELOPMENT->s_development_hook_create ();
}

//-------------------------------------------------------------------

