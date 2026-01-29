#include "lakeroom.h"

create_lakeroom() 
{
  set_short("Southern part of plain");
  set_long("This is the southern part of the plain between the lake and the mountain. "+
	   "To the east there is a scree, and to the south the plain narrows into a cleft "+
	   "sloping downwards. ");
  ADD_EXA("plain","Full of tussocks and pebbles.");
  ADD_EXA("tussock,tussocks,pebble,pebbles","Lots of them, however, utterly useless.");
  ADD_EXA("scree","It seems some of the rocks was pushed out by the force of water and cold.");
  ADD_EXA("cleft","The ground slopes down into a cleft.");
  ADD_EXA("ground","It is hard, filled with stones and pebbles");
  ADD_EXA("rocks,rock,stone,stones","Watch out for Rolling Stones.");
  NORTH("in_front");
  SOUTH("cleft");
}

		  
		    
