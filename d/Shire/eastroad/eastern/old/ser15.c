#pragma save_binary

inherit "/d/Shire/eastroad/std/er_base";
#include "/d/Shire/common/defs.h"
#include "/sys/stdproperties.h"
#include "/sys/macros.h"
/* Put something here like Mithlond defs or Bree defs that describe that area. */

#define EXIT1 ERE_DIR + "ser3","southeast",0,1
#define EXIT2 ERE_DIR + "ser16","northeast",0,1

object troll1,troll2;

void
reset_room()
{
    ::reset_room();

    if(!troll1)
    {
	troll1 = clone_object("/d/Shire/star/sertroll");
	troll1->move(this_object());
    }
    if(!troll2)
    {
	troll2 = clone_object("/d/Shire/star/sertroll");
	troll2->move(this_object());
    }
}
void
create_er_room()
{

    area = "somewhere west of";
    areaname = "the River Bruinen";
    land = "Eriador";
    areatype = 9;
    areadesc = "clearing";


    extraline ="There is not much in this clearing at first glance, "+
    "except for an old, burned out campfire.  The clearing is "+
    "surrounded by trees, except for to the southeast, and to "+
    "the northeast.";
    add_item(({"trees","treetops","woods","heavy woods"}), "The "+
      "trees surround you almost completely, and make this "+
      "clearing seem a bit unwelcoming.\n");
    add_item(({"campfire","old campfire","burned out campfire"}),"The "+
      "coals of the campfire are very cold, and are slightly scattered "+
      "around the area.\n");


    add_exit(EXIT1);
    add_exit(EXIT2);

    reset_room();
}
