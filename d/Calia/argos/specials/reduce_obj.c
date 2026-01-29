/* Clean up room function
** This function is used to destruct any objects in the room which have
** been left laying around by players.
** It is intended as a "clean up" after superchamps who kill and leave
** loot laying around, which causes too many objects in the room.
** The function should be invoked from reset_room()
** Should be INHERITED in a room object.
** The property ARGOS_NO_CLEANME,1 may be added to any object which
** should not be removed.
*/
#include <filter_funs.h>
#include <stdproperties.h>
#include "../argos.h"
void reduce_objects() {
   object *inv;           /* list of all object in this room  */
   object *players;       /* list of all players in this room */
   int    i,numobj;       /* loop var and # objecs in room    */
 
   /* get list of all objects in this room. If none, we're done */
   inv=all_inventory();
   if (sizeof(inv)<=0) return;
 
   /* get list of players from list of objects. If any, we're done */
   players=FILTER_PLAYERS(inv);
   if (sizeof(players)>0) return;
 
   /* remove all non-living objects */
   numobj=sizeof(inv);
   for (i=0; i<numobj; i++)
      if (!((inv[i]->query_prop(LIVE_I_IS))  ||   /* Iif not living   */
         (inv[i]->query_prop(ARGOS_NO_CLEANME))))
            (inv[i])->remove_object();            /* remove the obj    */
}
