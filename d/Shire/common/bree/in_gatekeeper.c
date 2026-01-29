#include "/d/Shire/common/defs.h"
#include "/sys/ss_types.h"
#include "/sys/stdproperties.h"

inherit "/d/Shire/room";

void add_stuff();
create_room() {
    set_short("Gatekeeper's lodge");
   set_long("This gatekeeper's lodge is bright with the light "+
   "of many candles, either to scare away the darkness or "+
   "light travellers' paths, it is hard to say. "+
   "On the wall is a sign listing the most current traveller's "+
   "advisories.\n");

   add_item(({"wall","sign","advisory","advisories"}),
   "Perhaps you should read the sign?\n");


    add_item("lodge", break_string(
   "The lodge is big enough to house the gatekeepers "+
   "and overnight guests in case of emergency. Perhaps "+
   "you should read all about the traveller's "+
   "advisories posted here?\n",70));


   add_prop(ROOM_I_INSIDE, 1);
   add_prop(ROOM_I_LIGHT, 4);
    add_exit(BREE_DIR + "gatekeeper", "out");

   reset_room();
}

void
reset_room()
{
    add_stuff();
}

void
add_stuff()
{
   object keeper;
   if(!present("hobbit"))
    {
     keeper = clone_object("/d/Shire/michel/npc/militia");
     keeper->move(TO);
   }
}


void
init()
{
    ::init();
   add_action("do_read","read");
}

int
do_read(string str)
{
   if (str != "sign")
   {
     return 0;
   }

write("The following traveller's advisories have been "+
     "posted by the Mayor of the Shire:\n"+
    "1) Trollshaws-  very very dangerous\n"+
     "2) Mountain area- your life is in peril!\n"+
     "3) Hollin/Eregion- do not go here!\n"+
     "4) Moria/Khazad-dum The evil has awakened. \n"+
     "\n\n"+
     "It is best to stick to the road, dear traveller! "+
     "For otherwise, you might fall into traps or trolls!\n");

     return 1;
}
