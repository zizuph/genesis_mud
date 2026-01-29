/* ARGOS - NWTERR - Vineyard Keeper's dwelling
**
** Date     Coder    Action
** -------- -------- --------------------------------
** 1/93     Zima     Created
** 8/26/95  Zima     Added grandma for grandma quest in metro area
**
*/
inherit "/std/room";
#include <stdproperties.h>
#include <macros.h>
#include "defs.h"
 
object knife=0;
object grandma=0;
 
void make_knife() {
    if (knife) return;
    knife=clone_object(WEAPON_DIR+"vmknife");
    knife->move(THIS);
}
void make_grandma() {
    if (grandma) return;
    grandma=clone_object(NPC_DIR+"grandma");
    grandma->move(THIS);
    tell_room(THIS,QCNAME(grandma)+" walks in.\n");
}
void reset_room() {
   make_knife();
   make_grandma();
}
 
/* room definition */
void create_room() {
   set_short("A vineyardman's dwelling");
   set_long(
       "You walk into the small dwelling of a local vineyardman.  This one-" +
       "room house is sparsely furnished with a bed and a table.  A crate " +
       "full of grapes sits by the door, though it is locked.  There is " +
       "also a stone hearth on the southern wall with a small fire.  A " +
       "doorway leads back out into the clearing.\n");
 
    add_prop(ROOM_I_INSIDE,1);
 
    add_item("bed",
       "Made of a simple wooden frame, this bed is neatly made with " +
       "wool blankets.\n");
 
    add_item("table",
             "A sturdy oak table surrounded by four chairs.  There are " +
             "some bottles sitting on it.\n");
    add_item(({"crate","grapes"}),"You imagine the crate is full of grapes "+
               "but it is locked and can't be opened.\n");
    add_item("bottles", "They are corked bottles of grapejuice or wine.\n");
    add_item("hearth",
             "A small fireplace made of stone, it takes up most of the " +
             "southern wall of the dwelling.  A small fire burns inside " +
             "it, giving a little warmth.\n");
 
 
    /* exits */
    add_exit(ROOM_DIR+"vyard1","out",0);
    reset_room();
}
