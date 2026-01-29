/* Kirk of Port City - Class Room (Adventurers Guild) of the abbey
**
** History:
** Date        Coder       Action
**----------   ----------- ----------------------------------
** 4/10/97     Zima        Created
**
*/
#pragma save_binary
#pragma strict_types
 
inherit "/lib/guild_support";
inherit "/lib/skill_raise";
inherit "/d/Khalakhor/std/room";
 
#include <ss_types.h>
#include <stdproperties.h>
#include <macros.h>
#include <language.h>
 
#include "defs.h"
object   monk;
 
/* prototypes */
void set_up_skills();
 
/* reset room */
void reset_room() {
   if (!objectp(monk)) {
      monk=clone_object(SR_NPC+"finegas");
      monk->equip_me();
      monk->move(TO);
      tell_room(TO,QCTNAME(monk)+" walks reverently into the room.\n");
      return;
   }
   if (!(present(monk,TO))) {
      tell_room(environment(monk),QCTNAME(monk)+" leaves in a hurry.\n");
      monk->move(TO);
      tell_room(TO,QCTNAME(monk)+" walks reverently into the room.\n");
      return;
   }
}
 
/* create room */
public void create_khalakhor_room() {
   set_short("A classroom in the abbey");
   set_long(
      "   You are standing in what seems to be a class room in the abbey of "+
      "the kirk. There is a cabinet along the north wall filled with "+
      "books and other items of pedagogy. A simple desk and chair are "+
      "beneath the arched window on the west wall, while various pads "+
      "and pillows are scattered about the floor where novice manachs "+
      "sit. There is a long table along the south wall, with a few books "+
      "and other items on it, above which hangs a painting in an ornate "+
      "frame. You think you could probably learn a great "+
      "deal here from the manachs.\n");
 
   add_item("cabinet",
      "It is a tall cabinet with a framed glass door. It holds various "+
      "books, scrolls, quills, bottles of ink, mortars and pestles "+
      "along with some items you can't make out.\n");
   add_cmd_item("cabinet",({"open","unlock"}),
      "The cabinet can not be opened or unlocked.\n");
   add_item("books",
      "Written in an alphabet you don't understand, most of the books are "+
      "housed in the cabinet while a few are scattered on the table top.\n");
   add_item(({"desk","chair"}),
      "A simple desk sits in front of the window along the west wall with "+
      "a small chair behind it. It must be used by those who teach in this "+
      "place.\n");
   add_item(({"pads","pillows"}),
      "They are scattered about the floor, used by pupils who meet here as "+
      "a group for learning.\n");
   add_item("table",
      "It is a long table along the south wall cluttered with various "+
      "items, including a few books, a quill and ink bottle, and a mortar "+
      "and pestle.\n");
   add_item(({"quill","ink","bottle"}),
      "There is a quill and an ink bottle sitting on the table, probably "+
      "used by the instructors during their lectures.\n");
    add_item(({"mortar","pestle","mortar and pestle"}),
      "The mortar and pestle sitting on the table are used to grind herbs "+
      "and other substances into powder. Obviously alchemy is one of the "+
      "topics taught here.\n");
   add_item("window",
      "There is an opaque stained glass window in the western wall, framed "+
      "by a pointed arch. It has a pattern of a lattice of diamonds.\n");
   add_item("painting",
      "Hanging on the wall in an ornate frame, the painting portrays "+
      "a group of white-robed manachs standing in a circle around a "+
      "young elf dressed in a crude brown robe. The youth stands before "+
      "a table on which is placed a cup and plate. He holds out his "+
      "hands and his mouth is open, as if he is proclaiming something.\n");
   add_item("frame",
      "The frame of the picture is ornately carved of oak. There is an "+
      "inscripton on the frame in three sentences, one up the left side, "+
      "one across the top, and another down the right side.\n");
   add_item("inscription",
      "It is written in three sentences on the frame of the picture.\n");
   add_cmd_item("inscription","read",
      "I offer these gifts to Ardaugh the Most High!\n"+
      "The Fruits of the Earth and the Work of my Hands!\n"+
      "Praised be Ardaugh forever!\n");
 
   add_exit("kcorr6","east");
   add_exit("kapothecary","south");
   INSIDE;
 
   reset_room();
   create_guild_support();
   create_skill_raise();
   set_up_skills();
}
 
/*
 * Function name: init
 * Description  : Initializes some things when an object
 *                enters the room. Here, it adds the commands
 *                used by guild_support.c and skill_raise.c
 * Arguments    : n/a
 * Returns      : n/a
 */
public void init()
{
    ::init();
 
    init_skill_raise();
    init_guild_support();
}
 
/*
 * Function name: leave_inv
 * Description  : Called when an object leave our inventory. Used
 *                here to make sure the guild_support.c code knows
 *                when a player leaves the room.
 * Arguments    : ob - Object pointer to the object leaving.
 *                to - Object pointer to 'ob's new environment.
 * Returns      : n/a
 */
public void leave_inv(object ob, mixed to)
{
    ::leave_inv(ob, to);
    gs_leave_inv(ob, to);
}
 
#include "kclassrm.inc"
