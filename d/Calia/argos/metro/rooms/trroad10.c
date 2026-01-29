/*
**   ARGOS - Metro - Tritos Roads
**
**   History:
**   Date       Coder      Action
**   --------   ---------- ---------------------------------
**   8/12/95    Zima       Created
**
*/
/* inherits/includes */
inherit "/std/room";
#include <stdproperties.h>
#include <macros.h>
#include "defs.h"
 
void create_room() {
   set_short("Tritos Road");
   set_long(
       "You are walking down Tritos road in the commercial district "+
       "of the city. There is an entrance to the Aeropagus between "+
       "the pillars which surround it to the west, while there is an "+
       "entrance to an ornate building to the east, next to which a blue "+
       "banner hangs. The road leads north and south through the city.\n");
 
   add_item(({"aeropagus","Aeropagus"}),
       "The Aeropagus is an open-air convocation center of the city. "+
       "It is lined with a set of pillars on its sides, through which "+
       "there is an entrance to the west.\n");
   add_item(({"pillar","pillars"}),
       "Tall columns of marble with ornate capitols, they stand "+
       "independently around the Aeropagus like a wall of marble "+
       "trees spaced perfectly apart.\n");
   add_item("building",
       "Pillars are set into the wall of the building, their capitols "+
       "supporting a shallow angled roof on top. The banner hanging next to "+
       "the entrance tells you it is some kind of government building.\n");
   add_item("banner",
       "Made of blue silk, the banner is embroidered with the arms "+
       "of Argos, a shield emblazoned with a rampant winged horse, "+
       "surmounted by a crown with three jewels.\n");
 
   /* exits */
   add_exit(ROOM_DIR+"trroad9",  "north",0);
   add_exit(ROOM_DIR+"trroad11", "south",0);
   add_exit(ROOM_DIR+"post",     "east",0);
   add_exit(ROOM_DIR+"aeropagus","west",0);
}
