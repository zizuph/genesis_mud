//  post.c - post office of Baile Ashlagh
//           Postmaster gives job to here to deliver mail
//  Zima  June 10, 98
//
inherit "/d/Khalakhor/std/room";
#include <stdproperties.h>
#include <macros.h>
#include "defs.h"
object   postman;
 
//
// reset_room
//
void reset_room()
{
   if (objectp(postman)) return;
   seteuid(getuid());
   postman=clone_object(NPC+"postman");
   postman->equip_me();
   postman->move(TO);
   tell_room(TO,QCNAME(postman)+" walks into the office.\n");
}
 
//
// create_khalakhor_room
//
void create_khalakhor_room()
{
   set_short("Baile Ashlagh Post Office");
   set_long(
      "This is the village post office, housed in another one of the "+
      "wood plank pastel colored buildings of the village. The office "+
      "is mostly empty, except for the west wall which is lined with "+
      "shelves filled with boxes and packages. A small hearth on the "+
      "north wall keeps the office warm.\n");
 
   add_item(({"shelves","packages","boxes"}),
      "Simple wood shelves line the west wall of the office, where "+
      "packages and boxes, probably filled with mail, are stored.\n");
   add_item(({"hearth","fire","fireplace"}),
      "It is a small clay brick hearth with a fire. It keeps the "+
      "office warm.\n");
 
   INSIDE;
   add_exit("court3","east");
   reset_room();
}
 
//
// enter_inv - add mailreader for those who enter
//
enter_inv(ob, from)
{
   ::enter_inv(ob, from);
   if (from == TO) return;
   if (present("mailreader", ob)) return;
   clone_object("/secure/mail_reader")->move(ob);
}
 
//
// leave_inv - remove mailreader when leaving
//
leave_inv(ob, to)
{
   object reader;
 
   ::leave_inv(ob, to);
   if (to == TO) return;
   reader = present("mailreader", ob);
   if (reader) reader->remove_object();
}
