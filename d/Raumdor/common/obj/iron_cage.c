/*
 *  Iron gibbet cage
 *
 *  Nerull 21/6-10
 */

/* 2017-05-24 Malus: Changing "corpse" to "cadaver" to avoid targetting
 * conflicts. Added chain description.
 */
/* 2017-08-28 Malus: Changing description to match bridge location */

inherit "/std/object";
#include "/d/Raumdor/defs.h"

void
create_object()
{
    set_name("cage");
    add_adj("iron");
    add_adj("gibbet");
    add_adj("suspended");
    set_short("suspended iron gibbet cage");
    
    set_long("This dreadful man-sized cage is made of iron, and " +
    "it's hanging a couple of feet above the ground, dangling in an " +
    "iron chain that leads up to the stone bridge. Inside the cage you " +
    "see the horrible sight of a rotting skeletal cadaver.\n");
    
    add_item(({"cadaver", "skeletal cadaver"}),
    "This ghasty skeletal cadaver stands in an upright " +
    "position, and it appears to be of a human. It appears to have been " +
    "in the cage for quite some time, and nearly all of the clothes it " +
    "still wears are nothing but tattered rags. For some reason, you get " +
    "the eerie feeling of it watching your every move, despite no sign " +
    "of life or movement beside the cage dangling in the soft winds.\n");

    add_item(({"chain","iron chain"}), "The iron chain is fastened to the " +
           "bridge, suspending an iron gibbet cage just above the stream.\n"); 

    add_prop(OBJ_I_NO_GET,1);
    add_prop(OBJ_I_NO_STEAL,1);
}

