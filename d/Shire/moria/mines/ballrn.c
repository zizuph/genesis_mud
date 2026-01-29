#include "defs.h"

int key_here;
int key_possible;

CONSTRUCT_ROOM {
   set_short("Northern Ballroom");
   set_long("The northern part of the ballroom. In a niche there is a "+
      "table.\n");
   add_item("table","@@exa_table@@");
   add_item("niche","You see nothing special.");
   add_item("velvet", "It is in a beautiful red.");
   add_call(({"get", "grab", "take"}), "[the] [rune] 'key' 'from' [the] 'table'",
      "get_key");
   add_cmd_item(({"table","dust"}),({"clean","undust"}),"@@my_dust@@");
   SOUTH("ballr");
   
   key_here = 0;
   key_possible = 1;
}

RESET_ROOM {
   if (!key_here)
      key_possible = 1;
}

string
my_dust()
{
   say(QCTNAME(TP)+" cleans the table, but it remains dusty, nevertheless.\n");
   return "You clean the table, but it remains dusty, nevertheless.";
}

int
produce_key()
{
   if (key_here || !key_possible)
      return 0;
   
   key_here = 1;
   key_possible = 0;
   tell_room(TO, "A puff of smoke appears from the table!\n");
   return 1;
}

string
exa_table()
{
   if (!key_here)
      return "It is clothed in a red velvet, but it is quite dusty.";
   
   return "It is clothed in a red velvet, but it is quite dusty.\n" + 
   "On the table lies what must be a key!";
}

int
get_key()
{
   if (!key_here)
      return 0;
   
   write("You " +query_verb()+" the key from the table.\n");
   say(QCTNAME(TP) + " grabs a key from the table.\n");
   TP->add_prop("i_got_the_rune_key",1);
   
   clone_object(MORIA_OBJ + "rune_key")->move(TP);
   key_here = 0;
   return 1;
}
