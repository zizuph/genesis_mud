// Kirk of Port City - Tabernacle
//
// History:
// Date        Coder       Action
//----------   ----------- ----------------------------------
// 4/5/98      Zima        Created
// 5/30/98     Zima        Recoded to use "real" monstrance/altar objects
//                         "Death trap" code moved to monstrance
// 7/20/98     Zima        Recoded to use new meditation room support
//
inherit  "/d/Khalakhor/std/room";
inherit  "/d/Khalakhor/guilds/sean-rhian/room/meditationrm";
#include <macros.h>
#include <stdproperties.h>
#include "defs.h"
#define  TPN      QCTNAME(TP)
 
//
// create_khalakhor_room()
//
void create_khalakhor_room()
{
   object mon;
   set_short("Tabernacle of the kirk");
   set_long(
      "   This chamber is the tabernacle of the kirk, a room for meditation "+
      "and quiet. On the north wall hangs a beautifully woven tapestry, "+
      "flanked by a pair of tall golden candlesticks holding large white "+
      "pillar candles. On the floor is a kneeling pad to comfort the "+
      "knees of the manachs who kneel here for meditation. An arched "+
      "doorway leads back into the sanctuary to the south.\n");
   INSIDE;
   add_prop(SR_K1SECURE,1); // secure area
   add_item(({"doorway","arch","arcwhay","entrance"}),
      "A pointed arch marks the entance of the chamber on the south "+
      "wall.\n");
   add_item(({"candles","candle"}),
      "The candles atop the candlesticks are thick cylindrical pillar "+
      "candles, cast of pure white wax, and standing about an arm's "+
      "length tall. Three interlocked circles of green wax decorate "+
      "their sides, their flames burning silently at about eye-level.\n");
   add_item(({"candle sticks","sticks","candlesticks","candlestick"}),
      "The candlesticks stand about arm's lengths high, and are "+
      "made of gold cast with intricate scrollwork. Each stands along "+
      "the north wall, one on either side of the tapestry.\n");
   add_item("tapestry",
      "It is finely woven of silk and portrays a scene of an elderly elf "+
      "standing beneath an oak tree next to a shallow brook. He wears a "+
      "white cassock with an ornate white stole over his shoulders. A "+
      "white mitre trimmed in gold bears an emblem of three inter-locked "+
      "circles. He holds aloft a small shamrock with one hand and points "+
      "to it with another. His eyes exude wisdom and peace.\n");
   add_item(({"pad","kneeling pad"}),
      "It is a thick kneeling pad, covered with green silk, placed "+
      "in front of the altar to comfort the knees which spend many "+
      "hours on the floor here.\n");
 
   add_exit("ksanct9","south","@@check_kneeling");
 
   mon   = clone_object(SR_TOOL+"monstrance");
   altar = clone_object(SR_OBJ+"covaltar");
   altar->move(TO);
   mon->add_amt(mon->query_max_shamrock()); // "charge" the monstance
   mon->move(altar);
   kneel_before=(altar->short());
}
 
//
// pray
//
int pray(string cmd)
{
   string verb=query_verb();
   object pen;
   object mon = present(SR_MONSTRANCE,altar);
 
   if (!(kneeling(TP)))
      write("You should kneel first.\n");
   else if (!(stringp(cmd)))
      write("You "+verb+" momentarily.\n");
   else if (lower_case(cmd)=="for wisdom in the mysteries of ardaugh")
      {
      write("You pray for wisdom in the mysteries of Ardaugh.\n");
      pen=present(SHAM_PENDANT,TP);
      if (objectp(mon_ok()) && objectp(pen))
         pen->report_prayer(TP,mon,altar);
      }
   else
      write("You pray "+cmd+".\n");
   return 1;
}
 
//
// init - add actions to the room
//
void init()
{
   ::init();
   add_action(&pray(), "pray");
}
