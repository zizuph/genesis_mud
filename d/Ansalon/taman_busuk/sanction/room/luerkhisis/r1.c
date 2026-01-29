#include "/d/Ansalon/common/defs.h"
#include "/d/Ansalon/taman_busuk/sanction/local.h"
#include <macros.h>
#include <stdproperties.h>

inherit SANCINROOM;

#define MEMBER(p1)     (p1->query_guild_member("Priests of Takhisis"))

void
create_sanction_room()
{
    set_short("entrance chamber to the temple of Luerkhisis");
    set_long("You stand within the entrance chamber of the " +
      "temple of Luerkhisis. " + "@@align_desc@@"+
      " To your northeast stand huge black doors that open into " +
      "the audience chamber of Ariakas, Dragon Highlord of the Red " +
      "Dragonarmy, while hallways lead off to your southeast " +
      "and northwest.\n");

    add_item("floor","The floor here is made of the same "+
      "material as the walls.\n");
    add_item(({"chamber","entrance chamber"}),
      "You stand within the entrance chamber of the temple of " +
      "Luerkhisis.\n");
    add_item("walls","Made of dark stone, these walls seem to hum " +
      "with an evil energy.\n");
    add_item(({"dark stone","stone"}),"The walls here are made " +
      "of a dark stone.\n");
    add_item(({"huge black doors","black doors","doors","door"}),
      "To your northeast stands huge black doors that open into " +
      "the audience chamber of Ariakas, Dragon Highlord.\n");
    add_item("hallways","Hallways lead further into the temple " +
      "to your northwest and southeast.\n");
    add_item("audience chamber","Through the huge black doors to your " +
      "northeast is the audience chamber of Ariakas, Highlord of the " +
      "Red Dragonarmy.\n");
    add_item("ceiling","Far above you, cloaked in shadows, is "+
      "the ceiling of the temple.\n");

    add_exit("","northwest","@@block_hall");
    add_exit("","southeast","@@block_hall");
    add_exit(SRED + "r6","southwest","@@exit_temple");
    add_exit(DGUILD + "joinroom_red","northeast","@@enter_chamber");
}

int
block_hall()
{
    write("The hallway has been declared off limits " +
      "by Ariakas, Highlord of the Red Dragonarmy!\n");
    return 1;
}

int
exit_temple()
{
    write("You step out of the temple of Luerkhisis.\n\n");
    return 0;
}

int
enter_chamber()
{
    write("You step into the audience chamber of Ariakas, " +
      "Highlord of the Red Dragonarmy!\n\n");
    return 0;
}

string
align_desc()
{
    int align = TP->query_alignment();

    if(MEMBER(TP))
	return "The walls around you seem to hum with the power " +
	"of your mistress, the Queen of Darkness! Your black heart "+
	"quickens with euphoria as you realize you stand at the center of "+
	"her power structure in Krynn... Here her great secret lies, " +
	"a secret that you have been entrusted with, that being "+
	"the hiding place of the good dragons precious eggs, and the place where "+
	"the unholy rites of draconian creation take place.";
    if(align > 200)
	return "The walls around you seem to hum with " +
	"evil energies, making you feel slightly nauseous. "+
	"Irrational fears play at your mind, reminding you that " +
	"this is an unholy temple to the Dark Queen, a place you " +
	"don't belong in.";
    if(align > -200)
	return "This place is obviously sacred to those " +
	"with an evil nature and disposition, making " +
	"you a little nervous, despite your neutral nature.";
    else
	return "The walls around you seem to hum with " +
	"evil energies, filling your mind with images of victorious battles, " +
	"the gruesome and slow deaths of your enemies, and other " +
	"such thoughts which your black heart exults in.";
}
