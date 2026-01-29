/*
**  ARGOS - Metro - Park
**
**   History:
**   Date       Coder      Action
**   --------   ---------- ---------------------------------
**   8/12/95    Zima       Created
**
*/
inherit "/std/room";
inherit "/lib/pub";
#include <stdproperties.h>
#include <macros.h>
#include <money.h>
#include "defs.h"
 
void create_room() {
    set_short("Park of Argos");
    set_long(
        "You are standing in the northwestern corner of the park of "+
        "Argos, the centerpiece of which is a long pool with a statue "+
        "rising in the center. Flowering dogwood trees shade the "+
        "lush green grass of the park, their dark bark and foliage "+
        "contrasting with their white and pink blooms. A path leads "+
        "around the pool to the east and south, while another cuts "+
        "through the hedge around the park to the northwest.\n");
 
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
   add_item(({"bark","foliage"}),
        "The bark of the trees is black with dark green leaves, "+
        "a contrasting backdrop for the bright colored blooms.\n");
   add_item("grass","It carpets the park, shaded by the trees.\n");
   add_item(({"path","paths"}),
        "One path leads around the pool to the east and south, "+
        "while another cuts through the hedge around the park to "+
        "the northwest.\n");
   add_item("hedge",
        "It is a well-trimmed hedge of evergreen bushes, walling "+
        "the park on all sides.\n");
 
   add_item(({"water","in water","into water","from water"}),
        "The water in the pool is very clear.\n");
   add_item(({"in pool","into pool","from pool"}),"Examine what?\n");
   add_cmd_item(({"pool","in pool","into pool","water","in water",
                  "into water"}),({"dive","swim","enter"}),
                  "Swimming is not allowed in the pool.\n");
   add_cmd_item(({"water","pool","from water","from pool"}),"drink",
                  "But you don't know what they put in it to keep "+
                  "it so clear!\n");
   add_exit(ROOM_DIR+"droad11","northwest",0);
   add_exit(ROOM_DIR+"park4","east",0);
   add_exit(ROOM_DIR+"park2","south",0);
}
