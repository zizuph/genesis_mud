inherit "/d/Gondor/common/lib/town";
#include "/d/Gondor/defs.h"

create_room() {
  hillside="north";
  height=5;
  road=2;
  density=4;
  extraline="These are the stairs leading up to the platform on which "
	+ "the golden hall Meduseld stands. On either side of the "
	+ "topmost step are stone-hewn seats for the guards. ";
  add_exit("/d/Gondor/rohan/edoras/meduseldgate","south",0,0);
  add_exit("/d/Gondor/rohan/edoras/lawn","north",0);
  make_the_room();
  add_item("platform",
    BSN("On this platform at the crown of the hill stands the golden hall "
      + "Meduseld, built by Eorl the Young."));
  add_item(({"seat","seats"}),
    BSN("The seats for the guards are hewn into the stone at either side "
      + "of the topmost step."));
  add_item(({"stair","stairs","steps"}),
    BSN("The stair leading up to the platform are high and broad. "
      + "At either side of the topmost step are stone-hewn seats for "
      + "the guards."));
}
