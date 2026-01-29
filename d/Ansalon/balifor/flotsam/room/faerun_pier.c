#include "/d/Ansalon/common/defs.h"
#include "/d/Ansalon/balifor/flotsam/local.h"

inherit FLOTSAM_OUT;

// Prototypes
string long_descr();
string read_sign();

reset_flotsam_room()
{
}

create_flotsam_room()
{
   set_short("At the pier to Faerun");
   set_long(long_descr);
   
   add_item(({"docks","piers","dock","pier"}),"Sturdy " +
      "barnacle-covered jetties jut out into the Blood Bay, where " +
      "far-travelled ships that sail the Blood Sea dock. \n");
   add_item(({"street","streets","main streets"}),"The main " +
      "streets to the south are crowded with the likes of draconians, " +
      "goblins and evil mercenaries.\n");

   add_item("sign", "The sign indicates where the boat from this pier " +
            "sails to. It has letters written on it.\n");

   add_item("letters", "They are written on the sign.\n");
   
   add_cmd_item("sign","read",read_sign);
   add_cmd_item("letters","read",read_sign);
   add_exit(FROOM + "street10","south",0);
   reset_flotsam_room();
}

string
long_descr()
{
    return tod_descr1() + tod_descr2() + "You stand at the docks " +
        "of Flotsam. To the south you see the main streets crowded with soldiers of the Dragonarmy. "+
        season_descr() + "\nA sign is planted here.\n";
}


string
read_sign()
{
    write("    ________________________ \n"
      +   "   |                        |\n"
      +   "   | This boat sails to the |\n"
      +   "   | Sword Coast of Faerun  |\n"
      +   "   |                        |\n"
      +   "   |________________________|\n"
      +   "             |  | \n"
      +   "             |  | \n");
    return "";
}
