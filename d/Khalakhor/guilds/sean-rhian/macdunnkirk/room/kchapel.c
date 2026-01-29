/* Kirk of Port City - Candle Chapel
** Player can "light candle for <someone>" here
**
** History:
** Date        Coder       Action
**----------   ----------- ----------------------------------
** 4/5/97      Zima        Created
** 5/30/98     Zima        Changed to inherit kneelrm; cleaned up
** 4/15/07     Zima        Added pedestal with book/incense
*/
/* inherits/includes */
#include "defs.h"
inherit  ROOM+"ksanct";
inherit  SR_ROOM+"kneelrm";
#define  MAX_CANDLES 12
#include <stdproperties.h>
#include <macros.h>
#include <language.h>
 
string   *ForList=({});
object   monk=0;
 
//
// reset_room
//
void reset_room()
{
   ForList=({});
 
   if (!monk)
      {
      monk=clone_object(SR_NPC+"knovice");
      monk->equip_me();
      monk->set_wander(ROOM+"k", MASTER_OB(TO), 60);
      monk->move(TO);
      tell_room(TO,QCNAME(monk)+" enters the chapel.\n");
      }
   if (!present(monk,TO))
      {
      tell_room(ENV(monk),QCTNAME(monk)+" leaves in a hurry.\n");
      monk->move(TO);
      tell_room(TO,QCNAME(monk)+" enters the chapel.\n");
      }
   monk->command("emote holds his hands over the candles and prays briefly.");
   monk->command("emote blows out some of the candles.");
}
 
//
// create_khalakhor_room
//
void create_khalakhor_room()
{
   set_short("Chapel of the kirk");
   set_long(
      "   This is the chapel of the kirk, a place for folk to stop for a quiet "+
      "moment during their busy day. There is a long table draped with a "+
      "cloth sitting along the north wall filled with votive candles in "+
      "small green glasses. A large stained glass window on the wall "+
      "above "+
      "the table portrays an enchanting lady elf who seems to watch over "+
      "the flickering lights. There is a long padded kneeler on the floor "+
      "in front of the table, and a small plaque on the "+
      "east wall. The quiet of the chamber and the flicker of the candles "+
      "fill the chapel with an aura of peace.\n");
   INSIDE;
   add_prop(SR_K1SECURE,1);
   add_item(({"window","lady","figure"}),&windesc(1));
   add_item("kirk",
      "It is a large stone structure, obviously religious in nature.\n");
   add_item("table",
      "It is a long table which sits along the north side of the chapel, "+
      "covered with a white cloth. Small green glasses with candles are "+
      "clustered on its top. There is a large box filled with sticks "+
      "of incense on the right end.\n");
   add_item(({"box","sticks","incense","sticks of incense","box of incense"}),
      "There is a wooden box, waxed to a glowing sheen, sitting on the right "+
      "end of the table. It is filled with a large supply of sticks of "+
      "incense used for devotional purposes. If you are in a worshipful "+
      "mood, perhaps you could take some incense from the box.\n");
   add_item("cloth",
      "It is a large cloth, white and clean as snow, which is draped over "+
      "the table and falls down to floor level. There is an emblem of three "+
      "interlocked circles embroidered in the center of the part hanging "+
      "down in the front.\n");
   add_item("glasses",
      "They are small containers made of dark green glass, serving as "+
      "holders for the candles.\n");
   add_item("candles","@@exa_candles");
   add_item("kneeler",
      "It is just a long, short bench with padding, running in front of "+
      "the table, used for kneeling during meditation.\n");
   add_item(({"floor","ceiling","wall"}), "It is made of stone.\n");
   add_item("walls","They are made of stone.\n");
   add_item("plaque",
      "It is a small plaque bolted to the east wall. There is writing "+
      "on it.\n");
   add_cmd_item("plaque","read",
      "Light a candle for someone special. Please make a donation to the "+
      "poor.\n");
 
   add_exit("kfoyer","west","@@check_kneeling");
   clone_object(SR_BOOK+"omos.c")->move(TO);
   reset_room();
   kneel_before="candles";
}
 
//
// exa_candles
//
string exa_candles()
{
   int    num=MAX_CANDLES-(sizeof(ForList));
   string desc=
      "They are votives, small round candles set inside a glass and having "+
      "a light scent. They are lit in memory or in prayer for someone by "+
      "those who stop by here to pray or meditate. Their small flames seem "+
      "to flicker in unison in a silent song. ";
   if (num<=0)
      write(desc+"All the candles are lit.");
   else
      write(desc+"There are "+LANG_WNUM(num)+" candles unlit. You "+
                 "could light one for someone special.");
   return "\n";
}
 
//
// pray
//
int pray() {
   if (kneeling(TP))
      {
      write("You say a short prayer.\n");
      tell_room(TO,QCTNAME(TP)+" prays quietly.\n",TP);
      }
   else
      write("You should probably kneel first.\n");
   return 1;
}
 
//
// meditate
//
int meditate()
{
   if (kneeling(TP))
      {
      write("You meditate upon the mysteries of the universe.\n");
      tell_room(TO,QCTNAME(TP)+" meditates quietly.\n",TP);
      }
   else
      write("You should probably kneel first.\n");
   return 1;
}
 
//
// light_candle - kneeling player may light a candle for someone
//
int light_candle(string cmd) {
   string forwhom;
   object *inv=all_inventory(TP);
   object whom;
 
   notify_fail("Light candle for whom?\n");
   if ((!stringp(cmd))||(!parse_command(cmd,inv,"'candle' 'for' %w",forwhom)))
      return 0;
   forwhom=lower_case(forwhom);
   if (!kneeling(TP))
      write("You should kneel before lighting a candle.\n");
   else if (sizeof(ForList)>=MAX_CANDLES)
      write("All the candles are already lit.\n");
   else if (member_array(forwhom,ForList)>=0)
      write("There is already a candle lit for "+capitalize(forwhom)+".\n");
   else if (TP->id(forwhom))
      write("You may not light a candle for yourself.\n");
   else
      {
      write("You light a candle for "+capitalize(forwhom)+".\n");
      tell_room(TO,QCTNAME(TP)+" lights a candle for someone.\n",TP);
      ForList=ForList+({forwhom});
      whom=find_player(forwhom);
      if (objectp(whom))
         {
         set_this_player(whom);
         write("You feel as if someone is praying for you from afar.\n");
         }
      }
   return 1;
}
 
//
// take
//
int take(string cmd) {
    int i, rc=0, dropped=0;
    object stick, room = ENV(TP);
    object *inv=all_inventory(TP);    
    notify_fail("Take what?\n");
    if (!stringp(cmd)) return 0;
    if (!parse_command(cmd,inv,"[some] [sticks] [stick] [of] 'incense' 'from' [the] 'box'"))
        return 0;    
    if (!present(SR_OMOS_BOOK,TP)) {
       write("The incense is used by those prepared to worship here. "+
             "You feel unprepared and so leave the incense in the box.\n");
       return 1;
    }
    for (i=0; i<10; i++) {
       stick = clone_object(SR_TOOL+"incstick.c");
       if (!dropped) rc = stick->move(TP);    
       if (rc != 0) {
           dropped=1;
           stick->move(room);
       }
    }
    if (dropped) {
        write("You try to take sticks of incense from the box on the table, "+
              "but drop some of them on the floor.\n");
        tell_room(room,QCTNAME(TP)+" takes sticks of incense from the box "+
              "on the table, but drops some of them on the floor.\n",TP);
    }
    else {
        write("You take some sticks of incense from the box on the table.\n");
        tell_room(room,QCTNAME(TP)+" takes some sticks of incense from the "+
                  "box on the table.\n",TP);
    }
    return 1;
} // take

//
// init - add actions
//
public void init() {
   ::init();
   add_action(&pray(), "pray");
   add_action(&light_candle(),"light");
   add_action(&meditate(), "meditate");
   add_action(&take(), "take");
   add_action(&take(), "get");   
}
