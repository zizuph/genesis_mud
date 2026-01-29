#pragma save_binary

inherit "/d/Shire/eastroad/std/er_base";
#include "/d/Shire/common/defs.h"
#include "/sys/stdproperties.h"
#include "/sys/macros.h"
/* Put something here like Mithlond defs or Bree defs that describe that area. */

#define EXIT1 ERE_DIR + "ser17","west",0,1
#define EXIT2 ERE_DIR + "ser19","east",0,1

object troll;

void
reset_room()
{
    ::reset_room();

    if(!troll)
    {
	troll = clone_object("/d/Shire/star/sertroll");
	troll->move(this_object());
    }
}
void
create_er_room()
{

    area = "just off of";
    areaname = "the River Bruinen";
    land = "Eriador";
    areatype = 1;
    areadesc = "bank";


    extraline ="The river looks quite deep next to you, but "+
    "you could most likely still manage to get across it "+
    "safely, if you are trying to go east into the Misty Mountains.  "+
    "To your west, the path continues through the forest.";
    add_item(({"river","River Bruinen","water"}),"The water "+
      "beside you looks very cold, and is deep and flowing "+
      "swiftly.  You may be able to cross it, although it "+
      "isn't the easiest way across.\n");
    add_item(({"grass","grassy bank","ground"}),"The grass here has "+
      "been walked over quite a bit recently and the grass is not "+
      "in the best of shape.  You can make out some tracks that "+
      "look like they belong to a big troll.\n");
    add_item(({"trees","treetops","woods","heavy woods"}), "The "+
      "trees are quite thick around you, and are a perfect place "+
      "for trolls to sit and wait for someone like you to wander by.\n");


    add_exit(EXIT1);
    add_exit(EXIT2);

    reset_room();
}
