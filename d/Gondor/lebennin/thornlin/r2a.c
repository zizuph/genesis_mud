#include "/d/Gondor/defs.h"
inherit (THORN_DIR + "out_door_master.c");

#include <language.h>
#include <macros.h>
#include "locals.h"

void
create_area_room()
{
    set_areatype(4);
    set_areadesc("busy");
    set_whereis("in");
    set_cityname("Thornlin");
    set_areaname("Lossarnach");
    set_land("Gondor");
    set_extraline("This is the western part of a square in the centre "+
      "of "+cityname+". West you see a stone building, "+
      "with a sign hanging from it. North of here there is "+
      "an important looking building. Between the two buildings "+
      "the road leads northwest out of the village. South the "+
      "square continues.");

    add_item("road","The road enters the village from the northwest and "+
      "widens into a square here. It continues further into the "+ 
      "village to the south.\n");
    add_item("square","The square seems to be surrounded by different "+
      "buildings.\n");
    add_item("buildings","You see two close by, one to the north, that one "+
      "looks important, and one to the west, the western building is "+
      "made of stone, it looks like an Inn.\n");
    add_item(({"stone building","inn","western building"}),"The stone "+
      "build lies west of the square. The stones in the walls "+
      "are making the building very strong, they are also "+
      "making the building grey. Over the door there hangs a "+
      "sign.\n");
    add_item(({"important building","important looking building",
	"northern building"}),"The building to the north are "+
      "rather small, but looks important, there is a plaque "+
      "on the door leading in, and next to the door hangs a "+
      "poster.\n");
    add_item("sign","\n"+
      "    0                    0\n"+
      "    8                    8\n"+
      "    0                    0\n"+
      "._-_b__-_-_-___-__-___- _b_-_.\n"+
      "|                            |\n"+
      "|  TTTTTTT                   |\n"+
      "|     T                      |\n"+
      "|     T H E  L O S T  P I G  |\n"+
      "|     T                      |\n"+
      "|  Famous for our pork meals |\n"+
      "|____-_-______-____-__-___-__|\n");
    add_item("plaque","the plaque reads:\n"+
      "      +-+->Guards House<-+-+\n");
    add_item("poster","The poster reads:\n\n"+
      "Anyone who enters this village shall obey the laws of "+
      "Gondor, and respect the commands of the Steward, Lord "+
      "Denethor II\n\nAnyone who fail to do so will be delt "+
      "with.\n\nThe village of Thornlin got ourself protections "+
      "from orcs and other scum, if you are in need of help, "+
      "call upon the Militias.\n");

    add_exit(THORN_DIR + "r1.c","northwest",0);
    add_exit(THORN_DIR + "r2c","south",0);

    clone_object(OBJ_DIR + "inndoorb")->move(TO);
    clone_object(OBJ_DIR + "guarddoorb")->move(TO);
}
