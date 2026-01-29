inherit "/d/Cirath/ak_wela/inherit/outside.c";
#include "/d/Cirath/common/defs.h"

void
create_room()
{
    set_short("Szun Moon Boulevard");
    set_long("You are travelling along the busy Szun Moon Boulevard. " +
             "Many a traveller goes directly from the gate to the house " +
             "to the north, above which a sign with a scroll and feather " +
             "is swaying in the light sea breeze, indictating that this is " +
             "the post office. You are fairly certain that many a templar " +
             "is in there too, making their fortune on the illitarate people " +
             "coming there. From the south you get a waft from something that " +
             "only be fresh coffee.\n");
    add_exit(AK_WELA_DIR + "post_office", "north","@@po", 2);
    add_exit(AK_WELA_DIR + "szun_moon7", "east", 0, 2);
    add_exit(AK_WELA_DIR + "szun_moon9", "west", 0, 2);
    add_exit(AK_WELA_DIR + "coffee","south", 0, 2);
}

int po()
{
	write("As you enter the post office a templar hands you a mailreader.\n");
	return 0;
}