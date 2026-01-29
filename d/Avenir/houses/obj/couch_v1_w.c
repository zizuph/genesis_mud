#include "/d/Avenir/common/city/zigg/zigg.h"

inherit (ZIG_LIB + "seating");

public void
create_seating(void)
{
    set_name("couch");
    add_adj(({"silk","plush","west", "western", "azure"}));
    set_short("azure silk couch");
    set_long("This plush couch stretches along the western wall. "+ 
	"It is long and wide enough that it "+
    "could double as a bed for napping on. The cushions are made "+
    "of azure-blue silk, which contrasts nicely with the milky "+
    "onyx walls.\n");

    set_seat_names(({"couch", "west couch", "azure couch"}));
    set_seat_id("_azure_couch");

    add_item(({"azure silk", "azure cushions", "azure silk cushions", 
	"silk", "silk cushions"}), "They are plump and soft and very "+
    "luxurious.\n");
	
    set_max_seat(3);
    set_lay_num(2);

    set_shift_seat(1);
    set_allow_kinky(1);
}
