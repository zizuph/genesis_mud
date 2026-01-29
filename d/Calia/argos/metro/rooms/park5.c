/*
**   ARGOS - Metro - Park
**
**   History:
**   Date       Coder      Action
**   --------   ---------- ---------------------------------
**   8/12/95    Zima       Created
**   2/8/02     Maniac     Fixed typo.
**
*/
inherit "/std/room";
inherit "/lib/pub";
#include <stdproperties.h>
#include <macros.h>
#include <money.h>
#include "defs.h"
 
object alexis;
 
void reset_room() {
    if (alexis) return;
    alexis=clone_object(NPC_DIR+"alexis");
    alexis->equip_me();
    alexis->move(THIS);
    tell_room(THIS, QCTNAME(alexis)+" walks down the path.\n");
}
 
void create_room() {
    set_short("Park of Argos");
    set_long(
        "The branches of the dogwoods populating the park rustle "+
        "gently in the breeze, adding to the relaxing atmosphere of "+
        "the grass-carpeted area. You admire the craftsmanship of the "+
        "statue rising from the middle of the pool, a monument to the "+
        "deities worshipped in this city. The path continues around the "+
        "long pool to the north and south.\n");
 
   add_item(({"centerpiece","pool"}),
        "The centerpiece of the park is a long pool edged with marble "+
        "inlaid with blue tile. The clear waters of the pool glisten "+
        "in the sunlight. A large statue rises out of the center of "+
        "the pool.\n");
   add_item("statue",
        "Standing on a pedestal which rises from the pool's center, "+
        "the statue is of three deities standing back to back in a "+
        "triangular fashion. One is dressed in battle armour and has "+
        "a falcon perched on his shoulder. The second wears an long "+
        "elaborate robe and holds an owl above her head. The third "+
        "is dressed modestly in a knee-length tunic and cradles a "+
        "dove in his hands.\n");
   add_item(({"dogwoods","trees"}),
        "A small grove of dogwood trees frames the pool, shading "+
        "the lush grass of the park.\n");
   add_item(({"flowers","blooms"}),
        "The blooms of the trees have four petals and are pink or "+
        "white.\n");
   add_item(({"water","in water","into water","from water"}),
        "The water in the pool is very clear.\n");
   add_item(({"in pool","into pool","from pool"}),"Examine what?\n");
   add_cmd_item(({"pool","in pool","into pool","water","in water",
                  "into water"}),({"dive","swim","enter"}),
                  "Swimming is not allowed in the pool.\n");
   add_cmd_item(({"water","pool","from water","from pool"}),"drink",
                  "But you don't know what they put in it to keep "+
                  "it so clear!\n");
   add_item(({"bark","foliage"}),
        "The bark of the trees is black with dark green leaves, "+
        "a contrasting backdrop for the bright colored blooms.\n");
   add_item("grass","It carpets the park, shaded by the trees.\n");
   add_item(({"path","paths"}),
        "It leads north and south between the pool on the west "+
        "and the grove of dogwoods to the east.\n");
   add_item("hedge",
        "It is a well-trimmed hedge of evergreen bushes, walling "+
        "the park on all sides.\n");
 
   add_exit(ROOM_DIR+"park4","north",0);
   add_exit(ROOM_DIR+"park6","south",0);
   reset_room();
}
