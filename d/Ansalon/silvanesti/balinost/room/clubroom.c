
#include "/d/Ansalon/common/defs.h"
#include <stdproperties.h>
#include "/d/Ansalon/silvanesti/balinost/local.h"
#include <macros.h>

inherit BALINOST_IN;

reset_balinost_room()
{
    return;
}


create_balinost_room()
{
    set_short("Believers in the True Gods of Krynn");
    set_long("This small building was home to a group that called "+
      "themselves the Believers in the True Gods of Krynn.  The group "+
      "was very reclusive since many had lost faith since the Cataclysm."+
      "  The group always liked to gain new members, and when rumours "+
      "of the gods' return came to Silvanesti, their numbers swelled.  "+
      "Now that Silvanesti is being abandoned, the group has moved.  "+
      "A note is posted upon one of the walls.\n");


   add_item("note","A note is posted upon one of the walls, it seems "+
     "to contain valuable information.\n");
   add_cmd_item("note","read","@@read_note");

    add_exit(BROOM + "street14","east",0);
}

string
read_note()
{
    return "\n"+
"Greetings to any who may be interested in worshipping the true gods,\n"+
"\n"+
"   Due to the evacuation of our home, our club has relocated.  I, "+
"however, have chosen instead to roam the lands to inform the people "+
"of our gods and their return.  If you are interested in joining my "+
"group, please come find me and I will tell you what you need to "+
"know.  Good luck, and gods speed!\n\n"+
"Taloran, Devoted follower of the True Gods\n\n";
}
