// Kirk of Port City - Guild Class Room
//
// History:
// Date        Coder       Action
//----------   ----------- ----------------------------------
// 7/19/98     Zima        Created
//
#pragma save_binary
#pragma strict_types
 
//inherit "/lib/guild_support";
inherit "/lib/skill_raise";
inherit "/d/Khalakhor/std/room";
 
#include <ss_types.h>
#include <stdproperties.h>
#include <macros.h>
#include <language.h>
 
#include "defs.h"
object   monk;
 
// prototypes
void set_up_skills();
 
//
// reset room
//
void reset_room() {
   if (!objectp(monk)) {
      monk=clone_object(SR_NPC+"laihder");
      monk->equip_me();
      monk->move(TO);
      tell_room(TO,QCTNAME(monk)+" walks into the room.\n");
      return;
   }
   if (!(present(monk,TO))) {
      tell_room(environment(monk),QCTNAME(monk)+" abruptly leaves.\n");
      monk->move(TO);
      tell_room(TO,QCTNAME(monk)+" walks into the room.\n");
      return;
   }
}
 
//
// create room
//
public void create_khalakhor_room()
{
   set_short("A classroom in the abbey");
   set_long(
      "   This is the primary classroom of the abbey, where the most skilled "+
      "manachs teach their skills to those who seek wisdom in their "+
      "ways. A simple desk and chair are beneath the arched window on "+
      "the west wall, while various pads and pillows are scattered about "+
      "the floor where students sit.\n");
 
   add_item(({"desk","chair"}),
      "A simple desk sits in front of the window along the west wall with "+
      "a small chair behind it. It must be used by those who teach in this "+
      "place.\n");
   add_item(({"pads","pillows"}),
      "They are scattered about the floor, used by pupils who meet here as "+
      "a group for learning.\n");
   add_item("window",
      "There is an opaque stained glass window in the western wall, framed "+
      "by a pointed arch. It has a pattern of a lattice of diamonds.\n");
 
   add_exit("ucorr3","east");
   INSIDE;
 
   reset_room();
   create_skill_raise();
   set_up_skills();
}
 
//
// init
//
public void init()
{
    ::init();
 
    init_skill_raise();
}
 
#include "uclassrm.inc"
