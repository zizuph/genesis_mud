/* Monstrance shawl - must be worn to handle a monstrance
**   Coder         Date                Action
** -------------- -------- ----------------------------------------------
** Zima           4/10/98  Created
**/
inherit "/std/armour";
#include "defs.h"
#include <formulas.h>
#include <stdproperties.h>
#define  SHAWL "shawl"
 
void create_armour() {
    set_name(SHAWL);
    add_name(({"vestment",SR_MON_SHAWL}));
    add_adj(({"ornate","rectangular","strange","golden","long","silk"}));
    set_short("ornate golden "+SHAWL);
    set_long(
       "It is a strange ornate shawl, made of a long rectangular piece "+
       "of golden silk. It is worn wrapped around the shoulders and "+
       "back, covering the arms and hands, as if to cover them while "+
       "handling a holy object. Intricate scrollwork in purple thread "+
       "is sewn around its border, and there is an image of an angel "+
       "sewn into the center, rays of sunlight beaming from his body.\n");
 
    set_ac(10);
    set_af(TO);
    set_at(A_HANDS | A_ARMS);
}
 
public mixed remove(object what) {
   object mon=present(SR_MONSTRANCE,TP);
   if (objectp(mon))
      {
      TP->catch_msg("You can not remove the "+query_short()+" while "+
                    "holding the "+(mon->query_short())+".\n");
      return -1;
      }
   return 0;
}
