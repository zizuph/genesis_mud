/*
**  MCLUB - Memorial Shrine, Lower Level, Central Room
**
**  History:
**  Coder        Date                       Action
**  ---------- --------  -----------------------------------------------------
**  Zima       5/5/95    Created
**
*/
inherit "/std/room";
#include <stdproperties.h>
#include <macros.h>
#include <composite.h>
#include "defs.h"
 
create_room() {
   set_short("Convocation Chamber");
   set_long(
      "This spacious room is the convocation chamber of the conclave, a "+
      "place where those who remember "+
      "the arcane faith may meet in "+
      "esoteric peace. A large stone hearth is built into the northwestern "+
      "corner, its quiet flames filling the chamber with "+
      "light and warmth. Three elegant sofas are set in a square toward "+
      "the hearth, above which hangs a rather large painting. A feeling "+
      "of unity and tranquility abides here.\n");
 
   add_item(({"room","chamber","convocation"}),
      "It is the central chamber of the conclave of the shrine, "+
      "the place where those who abide here meet in peace.\n");
   add_item("hearth",
      "The large stone hearth is set into the northwestern corner, "+
      "where a large but tranquil fire burns. Above the hearth is "+
      "a large painting.\n");
   add_item(({"fire","flames"}),
      "It burns peacefully in the hearth, filling the room with "+
      "warmth and light.\n");
   add_item(({"sofa","sofas"}),
      "The three sofas are made of fine wood and cushioned with blue "+
      "silk, etched with silver thread. They are set in a square pattern "+
      "with the hearth along the fourth side.\n");
   add_item("conclave","It is the lower level of the shrine.\n");
   add_item("painting","@@exa_painting");
 
   add_prop(ROOM_I_INSIDE,1);
 
   add_exit(ROOM_DIR+"shconlib","north",0);
   add_exit(ROOM_DIR+"shconent","south",0);
   add_exit(ROOM_DIR+"shconsac","east",0);
   add_exit(ROOM_DIR+"start","west",0);
    add_exit(ROOM_DIR+"post","northeast",0,1);
}
 
 
string exa_painting() {
   object TP=this_player();
   string MList;
   string *Mem;
   int    i;
   string desc="It is a painting depicting a circle of figures dressed "+
               "in long white robes, their faces cowled, each holding "+
               "a single blue candle. ";
   if (InMClub(TP)) {
      MList=read_file(MCLUB_MEMLIST);
      Mem=explode(MList,"\n");
      desc=desc+"You recognize the figures as "+(COMPOSITE_WORDS(Mem))+".\n";
      }
   else desc=desc+"\n";
   return desc;
}
int prevent_quey_snoop() { return 1; }
