#include "outroom.h"

create_outroom() {
  set_short("Steep mountain path");
  set_long(
	   "You're climbing a steep north-south mountain path. "+
	   "It winds up towards a peak under a greater mountain. "+
	   "It looks like there might be a wonderful view up there, but "+
	   "it is hard to tell whether it is possible to get there from "+
	   "here.");
  add_item("path","It is rather steep.\n");
  add_item(({"peak","mountain"}),"You might try further up to the north.\n");
  EXIT("rom5","north");
  EXIT("rom3","south");
}
