// updated by Lilith, 2 Nov 1996, for use with the dark_treas_pmodule.c
// file in /dark/obj/*. It places crates here.


inherit "/d/Avenir/inherit/room";

#include "/d/Avenir/common/dark/dark.h"

void
create_domain_room()
{
  set_short("cavern");
  set_long("The clean tunnel meets here with a large, naturally formed\n" +
	   "cavern. The stones here glow with a slight, eerie luminescence.\n"+
	   "The tunnel continues out to the east and west.\n");
  
  add_item(({"stones","rock","rocks","light","luminescence"}),
	   "The rock of this naturally formed cavern sheds its own strange" +
	   " light, so dim it can hardly be perceived.\n");
  
  add_exit(L2 + "n3", "east");
  add_exit(L2 + "n7", "west");
  BLACK;
  IN;
}
