/*
 *  Added fishing properties allowing fishing - Arman 2021
 */

#include "/d/Ansalon/common/defs.h"
#include "/d/Ansalon/balifor/flotsam/local.h"

inherit FLOTSAM_OUT;
object elf;

#include "/d/Krynn/common/herbsearch.h"
#define H1 "/d/Krynn/common/herbs/ss_grass"
#define H2 "/d/Krynn/common/herbs/surf_grass"

#define LIVE_I_CAN_FISH      "_live_i_can_fish"

void
reset_flotsam_room()
{
   if(!objectp(elf))
      {
      elf = clone_object(FNPC + "sea_elf");
      elf->arm_me();
      elf->move(TO);
   }
}

create_flotsam_room()
{
   set_short("Sheltered cove");
   set_long("@@long_descr");
   
   add_item(({"sandy beach","beach","sand"}),"A thin " +
      "strip of golden sand at the bottom of the cliff. \n");
   add_item("sea","Before you the Blood Sea is calm and " +
      "tranquil. Whether it is due to a reef around the cove " +
      "or something mystical about the place, you do not know. \n");
   
   add_exit(FROOM + "street23","west",0);

    add_cmd_item(({"water","sea","waves"}),
      ({"swim","dive","wade", "enter"}),"@@swim_water");

    seteuid(getuid(TO));
    set_search_places(({"sand","beach","herbs"}));
    add_prop(OBJ_I_SEARCH_TIME,3);
    add_prop(OBJ_S_SEARCH_FUN,"herb_search");
    add_prop(LIVE_I_CAN_FISH, "bloodsea");

    add_herb_file(H1);
    add_herb_file(H2);
   
   reset_flotsam_room();
}

string
long_descr()
{
   return tod_descr1() + "You stand upon a sandy beach at the " +
   "bottom of the cliff. You can faintly hear the sound of the " +
   "waves crashing against rocks further out to sea, but apart " +
   "from that, all is calm and peaceful. \n";
}

string
swim_water()
{
    write("You enter the red waters of the Blood Sea and begin to swim "+
          "northward.\n");
    TP->move_living("into red waters of the Blood Sea",
      FROOM + "blood_sea1", 1, 0);
    return "";
}
