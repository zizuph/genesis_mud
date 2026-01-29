/* A slab of whale blubber, cut from the carcass of a beached whale
** used to make oil
**
** History:
** Date        Coder       Action
**----------   ----------- ----------------------------------
** 4/20/98     Zima        Created
**
*/
inherit "/std/object";
#include <stdproperties.h>
#include "defs.h"
 
void create_object() {
    set_name("blubber");
    add_name(({"whale blubber","slab","slab of blubber",
               "slab of whale blubber", SR_WBLUBBER}));
    set_adj(({"thick","whale","smelly","soft","oily"}));
    set_short("slab of blubber");
    set_pshort("slabs of blubber");
    set_long(
       "It is a thick slab of blubber, cut from the carcass "+
       "of a whale. It is soft, oily and very smelly.\n");
    add_prop(OBJ_I_WEIGHT,1000);
    add_prop(OBJ_I_VOLUME,1000);
    add_prop(OBJ_I_VALUE,0);
}

int do_eat(string cmd) {
   if (!stringp(cmd)) return 0;
   if (!parse_command(cmd,all_inventory(this_player()),"%s 'blubber'"))
      return 0;
   write("You wouldn't want to do that, it smells awful and would "+
         "probably make you sick!\n");
   return 1;
}
 
void init() {
   ::init();
   add_action(&do_eat(),"eat");
}
