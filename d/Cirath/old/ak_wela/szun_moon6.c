inherit "/d/Cirath/ak_wela/inherit/outside.c";
#include "/d/Cirath/common/defs.h"

void
create_room()
{
    set_short("Szun Moon Boulevard");
    set_long("This large boulevard runs east-west through the very heart of the " +
             "city.  To your north, you see an impressive stone structure, with " +
             "a sign with a coin painted upon it. You realise that this must be the " +
             "bank. From the south exotic smells reach your nose, drowning the " +
             "otherwise allways present smell of fish and the sea. It must probably " +
             "be a perfume shop or something, but you see no entrance from here." +
             "East, the boulevard continues toward the docks, and westwards it " +
             "leads to a gate out of the city.\n");
    add_exit(AK_WELA_DIR + "bank", "north", 0, 2);
    add_exit(AK_WELA_DIR + "szun_moon5", "east", 0, 2);
    add_exit(AK_WELA_DIR + "szun_moon7", "west", 0, 2);
}
