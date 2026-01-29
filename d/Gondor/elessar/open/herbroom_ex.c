inherit "/d/Gondor/common/room";
#include "/d/Gondor/elessar/lib/herbsearch.h"
#include "/d/Gondor/defs.h"
#include "/sys/stdproperties.h"
#include "/sys/macros.h"

create_room()
{
  set_short("The western edge of the Ithilien Forest");
  set_long(BS("This is the western edge of the forest, and the great river "+
    "Anduin runs to the west of here. The forest consists of tall oaks and "+
    "larches here, while broad-leaved bushes and shrubberies grow alongside "+
    "the river.\n"));
  add_item("river","The great river Anduin flows west of here, on its way\n"+
    "south towards the Sea. The river is wide and strong.\n");
  add_item("forest","The green forests of Ithilien might very well resemble\n"+
    "paradise - fresh flowers and fragrant herbs, green trees and a number\n"+
    "of grassing game.\n");
  add_item("oaks","The oak trees are old and magnificent of stature.\n");
  add_item("larches","The larch trees are tall and green, reaching even higher\n"+
    "than the oaks.\n");
  add_item("bushes","The broad-leaved bushes are the primary contents of the\n"+
    "undergrowth here.\n");
  add_item("shrubberies","The green shrubberies with small flowers grow amongst\n"+
    "the broad-leaved bushes.\n");
  add_item("ground","The ground is overgrown with flowers, herbs and bushes.\n");
  add_item(({"flowers","herbs"}),BS("The flowers and herbs growing here give "+
    "the air a sweet fresh fragrance.\n"));
  add_exit(ITH_DIR+"forest/edge1","north",0);
  set_search_places(({"bushes","shrubberies","forest","flowers"}));
  add_prop(OBJ_I_SEARCH_TIME,2);
  add_prop(OBJ_S_SEARCH_FUN,"herb_search");
  add_herb_file(HERB_DIR+"attanar");
  add_herb_file(HERB_DIR+"tuo");
}

reset_room()
{
  set_searched(0);
}
