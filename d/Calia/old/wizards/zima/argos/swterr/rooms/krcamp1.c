/* Kretan encampment along the dirt road of SWTERR
**
** History
** Date       Coder        Action
** -------- -------------- --------------------------------------------
** 1994     Zima           Coded
** 8/16/96  Zima           Added stewpot, cleaned up file
*/
inherit "/std/room";
#include <stdproperties.h>
#include <macros.h>
#include "defs.h"
#define  KRETAN_LIST ({"tcomder/tcomder2","sentry/sentry2","sentry/sentry2",\
                       "sentry/sentry2","boycook"})
#define  ORIGIN_MSG "out of the tent."
#include KRETAN_SENTRY_H
object stewpot;
 
void reset_room() {
   make_kretans();
   stewpot->reset_stew();
}
 
/* room definition */
void create_room() {
   set_short("A secluded military campsite");
   set_long(
       "You are standing in the middle of a small military campsite, "+
       "a secluded outpost of some sort hidden along the edge of the "+
       "dark forest. A banner hangs from a tall pole planted next to "+
       "the entrance of a tent erected amongst the trees to the west, "+
       "while a small hidden path leads back to the road to the east. "+
       "The hearty aroma of cooking lingers in the clearing, probably "+
       "attracting beasts from the forest.\n");
 
    add_item("path",
        "A narrow dirt path winding through the trees, somewhat muddy " +
        "from recent rains.  It leads east through the forest.\n");
    add_item(({"canopy","leaves"}),
        "The dense canopy of leaves shades the small clearing");
    add_item("pole",
        "It is a tall, thin wooden pole set in front of the tent " +
        "entrance. A red banner hangs from it.\n");
    add_item("banner",
        "Hanging from a rod atop the pole, the red banner flutters " +
        "in the gentle breeze, embroidered in black thread with a " +
        "seven-headed hydra.\n");
    add_item(({"trees","forest"}),
        "A dense wall of dark mohagany trees surrounds the clearing, " +
        "the canopy of leaves almost blotting out the sun. Twisted " +
        "vines seem to strangle the trunks and branches of these " +
        "ancient giants.\n");
    add_item("tent",
        "It is a small round tent made of canvas. The entrance " +
        "to the tent is open to the west.\n");
 
    /* add a stewpot */
    stewpot=clone_object(KRCAMP_DIR+"objects/stewpot");
    stewpot->move(THIS);
 
    /* exits */
    add_exit(ROOM_DIR+"krcampt","west","@@check_blocked");
    add_exit(ROOM_DIR+"r16","east",0);
    reset_room();
}
