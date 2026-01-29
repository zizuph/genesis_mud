// vestibule
// grace aug 1994
/**********************************************************************
 * - Added the following:                                           - *
 * -   #include "/d/Krynn/solamn/vin/std/no_scry_room.c"            - *
 * -   add_prop(ROOM_M_NO_SCRY, query_no_scry);                     - *
 * -                                                                - *
 * - Modified by Damaris@Genesis 03/2005                            - *
 **********************************************************************/ 
#include "../local.h"
inherit SPURRM;
#include "/d/Krynn/solamn/vin/std/no_scry_room.c"
create_spur_room()
{
    add_prop(ROOM_M_NO_SCRY, query_no_scry);
    SHORT("Vestibule");
    LONG("This is the place where a Knight awaits his turn to "+
      "pray in the Chapel.  The stone walls are white-washed "+
      "and lined with narrow benches. Ornate candle stands "+
      "provide a muted light which makes any metal in the room " +
      "gleam dully.  Upon the floor is a thick carpet woven " +
      "from undyed wool.\n");

   INSIDE;
   LIGHT;

   AE(ROOM + "passage12", "east", 0);
   AE(ROOM + "chapel", "west", "@@do_tingle");

   AI(({"candles","candle"}), "Long white beeswax candles.\n");
   AI("carpet", "It is woven of undyed wool, so the colour is a " +
      "creamy-white with occasional darker fibres.\n");
   AI("walls", "The walls are white-washed stone.\n");
   AI(({"stand", "stands", "candle stand", "candle stands"}), "The candle stands "+
   "are made of ornately wrought bronze.\n");
   AI(({"bench","benches"}), "They are narrow and made of hardwood. " +
      "The benches look uncomfortable for sitting.\n");
   ACI(({"bench","benches"}), ({"sit","sit on"}), "@@do_sit"); 
   AI("metal", "It gleams dully in the light of the candles.\n");
   AI(({"floor","stone floor"}),
      "It is so shiny you can see your reflection in it.\n");
   AI(({"reflection", "my reflection"}), "Yes, sure enough, that "+
      "is a distorted image of your face. At least, you hope it "+
      "is distorted. You've seen draconians prettier than that!\n");
   ACI(({"candle","candles"}), ({"get","take","remove"}),"@@do_get"); 
}

do_tingle()
{
   if (TP->query_alignment() < 0)
      {
      write("As you pass through the archway, the skin on your face "+
         "feels like it has been pricked with hundreds of pins.\n" +
         "Much to your revulsion, you sense tremendous good in this room.\n");
      TP->add_panic(50);
      return 0;
   }
   else
      {
      write("As you pass through the archway, a feeling like a warm " +
         "breeze blows over you, caressing your skin.\nYou sense " +
         "tremendous goodness in this room, welcoming you.\n");
      TP->add_fatigue(10);
   }
   return 0;
}
      
init()
{
    ::init();
    ADA("do_get");
    ADA("do_sit");
}

int
do_get()
{
   write("As you try to remove the candle from its holder, hot wax "+
      "spills onto your skin, burning it.\n");
   say(QCTNAME(TP) + " tries to take a candle and gets burned.\n");
      TP->add_fatigue(-10);
   return 1;
}

int
do_sit()
{
   write("You sit down on one of the hard benches.\n");
   say(QCTNAME(TP) + " sits on one of the benches.\n");
   return 1;
}

