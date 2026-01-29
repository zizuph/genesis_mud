/* Satyr Forest, a Newbie area
**
** History
** Date        Coder       Action
** --------  ------------  ----------------------
** 2/18/95   Zima          Created
** 2010/09/01  Lavellan    Typos
**
** Changelog:
**    Baldacin, 2004-02-29: Added connection to the Silent
**                          Forest.
**/
/* inherits/includes */
inherit "/std/room";
#include <stdproperties.h>
#include <macros.h>
#include "defs.h"
#define NumSatyrs 3
#include "sfornpcs.h"
 
/* room definition */
void create_room() {
   set_short("A dense forest");
   set_long(
       "You step into a dark nook of the forest, the oaks and maples "+
       "growing so densely that it seems dark enough to be dusk. To "+
       "the southwest you see the sunlight of the clearing. You hear "+
       "a hiss from beneath the underbrush and decide you had better "+
       "leave before you get snake-bitten. A small overgrown trail leads "+
	   "off to the northeast.\n");
 
#include "sfordesc.ext"
 
   /* exits */
   add_exit(ROOM_DIR+"sfor6","southwest",0);
   add_exit(ARGOS_DIR+"silent_forest/trail01","northeast",0);
   set_alarm(5.0,0.0,"reset_room");
}
