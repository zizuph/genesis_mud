#pragma save_binary

inherit "/d/Shire/eastroad/std/er_base";
#include "/d/Shire/common/defs.h"
#include "/sys/stdproperties.h"
#include "/sys/macros.h"
static object trolls;
void reset_room();

#define EXIT1 ERE_DIR + "err9","northeast",0,1
#define EXIT2 ERE_DIR + "err16","southeast",0,2

void
create_er_room()
{

    area = "near";
    areaname = "the Great East Road";
    land = "Eriador";
    areatype = 7;
    areadesc = "clearing";
    grass = "green";
    treetype = "pine";

    extraline = "Something about this clearing calls to mind "+
    "legends from the past. Surrounded by stately pine trees and "+
    "with a sprinkling of bushes and other shrubbery, there "+
    "seems to be an aura of history in this clearing, giving a "+
    "feeling that something great once happened here.";

    add_item(({"bush","bushes","shrubberyy","other shrubber"}), "The "+
      "bushes and shubbery grow randomly in various parts of this "+
      "clearing.\n");


    add_exit(EXIT1);
    add_exit(EXIT2);

    reset_room();
}

void
reset_room(){

    if (!trolls)
    {
	trolls = clone_object("/d/Shire/shanna/bill");
	trolls->move(TO);
    }
}
