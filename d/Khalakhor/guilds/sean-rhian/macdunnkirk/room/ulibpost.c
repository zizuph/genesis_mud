// Kirk of Port City - Abbey Library - postoffice room
//
// History:
// Date        Coder       Action
//----------   ----------- ----------------------------------
// 5/2/98      Zima        Created
// 7/16/98     Zima        Updated
//
#include "defs.h"
inherit  ROOM+"ulib";
#include <stdproperties.h>
 
void create_khalakhor_room()
{
   create_library("north"," beneath which sits a desk and chair used "+
                  "for reading and writing letters",0);
 
   add_item(({"desk","writing desk","chair"}),
      "A small oak writing desk and chair sit along the northern "+
      "wall beneath the window. They are used by the manachs "+
      "and saggarts for writing and reading mail.\n");
 
   add_exit("ulib1","east");
}
 
enter_inv(ob, from)
{
   ::enter_inv(ob, from);
   if (from == this_object()) return;
   if (present("mailreader", ob)) return;
   clone_object("/secure/mail_reader")->move(ob);
}
 
leave_inv(ob, to)
{
   object reader;
 
   ::leave_inv(ob, to);
   if (to == this_object()) return;
   reader = present("mailreader", ob);
   if (reader) reader->remove_object();
}
