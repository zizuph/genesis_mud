#include "/d/Ansalon/common/defs.h"
#include "/d/Ansalon/taman_busuk/sanction/local.h"

inherit SANCOUTROOM;


void
create_sanction_room()
{
    set_short("A street in the southern parts of Sanction " +
      "before the Temple of Duerghast");
    set_extra_long("Here you walk along a street on the southern " +
      "edge of a teeming slum consisting of filthy, closely-packed " +
      "buildings that create a maze of winding alleys. " +
      "To your south you notice a tall, black fortress-like " +
      "structure, surrounded by high walls and sealed " +
      "with two solid iron gates.");

    add_item("street","You stand upon a cobbled street in the city of " +
      "Sanction, just north of the imposing Temple of Duerghast.\n");
    add_item(({"structure","fortress","fortress-like structure",
	"edifice","forbidding edifice","temple",
	"temple of duerghast"}),
      "This forbidding edifice is the Temple of " +
      "Duerghast, used by the Red Dragon Highlord " +
      "Ariakas as a prison and torture chamber. High " +
      "walls surround it and two solid iron gates " +
      "seal the only entrance in.\n");
    add_item(({"high walls","walls","wall"}),
      "High walls surround the Temple of Duerghast. They look " +
      "unscaleable.\n");
    add_item(({"iron gates","gates"}),
      "Two iron gates seal the entrance into the Temple " +
      "of Duerghast. You cannot open them.\n");

    add_exit(SCITY + "street4","west",0);
    add_exit(SCITY + "street11","east",0);
    add_exit("","south","@@enter_temple");

    slum_descriptions();
}

int
enter_temple()
{
    write("The two solid iron gates to the " +
      "Temple of Duerghast are closed and sealed.\n");
    return 1;
}
