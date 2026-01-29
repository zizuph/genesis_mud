/*
 *   Vision of Delphia - Alpha tome
 *
 *   DESCRIPTION:
 *   This tome is one of 7 used in the Vision of Delphia quest based
 *   in the Temple of Dephonia in the southwest territory of Argos.
 *   Together, the tomes tell of a vision that Delphia, first High
 *   Priestess of Dephonia, had.  Re-enacting the vision, as an evil
 *   ritual, makes up the quest. Thus, these tomes are the major
 *   hints.
 *
 *   LOCATION FOUND: On a special table in the Library. (rooms/library3)
 *
 *   HISTORY:
 *   CODER         DATE             ACTION
 *  ------------ -------- -----------------------------------------------
 *   Zima         1/15/95   Created
 *
 */
 
inherit "/std/scroll";
#include <macros.h>
#include <stdproperties.h>
#include <ss_types.h>
#include <config.h>
#include <cmdparse.h>
#define  LANG_LEVEL ALPHA_LANG_LEVEL
#include "tomedefs.h"
#include "defs.h"
 
#define HOME_ROOM ROOM_DIR+"library3.c"
#define OBJ_NUM 0
#include "../retrnobj.h"
 
void
create_scroll()
{
    set_name(({"ancient tome","tome","alpha tome"}));
    set_short("ancient tome");
    set_long(break_string(
       "An ancient tome entitled: The Vision of Delphia - Alpha. " +
       "\n(Try 'read alpha tome').\n",100));
 
    add_prop(OBJ_M_NO_SELL,1);
    add_prop(OBJ_I_WEIGHT, 20);
    add_prop(OBJ_I_VOLUME, 150);
 
    set_file(OBJ_DIR+"tomea.txt");
}
