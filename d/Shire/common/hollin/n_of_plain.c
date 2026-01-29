#include "lakeroom.h"

create_lakeroom() {
  set_short("NORTH of plain");
  set_long(
	   "This is the northern edge of the plain in front of the Misty Mountains. "+
	   "Paths from the west, north and south meet here, and to the east there is a "+
	   "long and narrow wall of rock. To the south however, a plain covered with "+
	   "soil, pebbles and tussocks opens, and to the southwest extends the Sirannon Lake. ");
  ADD_EXA("plain","It looks to be filled with tussocks and pebbles, and is situated\n"+
               "between a high rocky mountain to the east and the lake in the west.");
  ADD_EXA("path,paths","There are paths going east,west and north.");
  ADD_EXA("wall,rock,wall of rock","It is unclimbable.");
  ADD_EXA("cloads,cload","Most definitely cloads of snow, since the tops are covered in white.\n");
  add_cmd_item( ({ "rock","wall"}), ({"climb","kick"}),
		({ "You try, but fail, and fall back to earth.\n",
		   "Nothing happens.\n"}) );  
  NORTH("m_path1");
  WEST("rom7");
  SOUTH("plain_n");
}
