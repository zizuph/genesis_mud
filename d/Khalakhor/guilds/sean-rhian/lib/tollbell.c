/* Kirk bell ringing function
**
** History:
** Date        Coder       Action
**----------   ----------- ----------------------------------
** 4/1/97      Zima        Created
**
** Given a list of path names of rooms where the bell can be heard,
** cycles through each room, and if an interactive is present, the
** interactive hears the tolling of the bells. The first room of the list
** is assumed to be the belfry (where the bells actually are) To be inherited
** in belltower rooms.
*/
#include <filter_funs.h>
void toll_bell(string *list) {
   int    i;
   object room;
   object *player;
   for (i=0; i<sizeof(list); i++) {
      log_file("zima",list[i]+"\n");
      room=find_object(list[i]);
      if (objectp(room)) {
         player=FILTER_PLAYERS(all_inventory(room));
         log_file("zima","   found room, np="+(sizeof(player))+"\n");
         if (sizeof(player)>0) {
            log_file("zima","   found player, ringing bell\n");
            tell_room(room,"The bells of the kirk ring out in a "+
                           "clammering toll!\n");
            if (i==0)
               tell_room(room,"You are almost defeaned by the thundering "+
                              "clangs!\n");
         }
      }
   }
}
