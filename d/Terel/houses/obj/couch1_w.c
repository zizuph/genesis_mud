#include "/d/Avenir/common/city/zigg/zigg.h"

inherit (ZIG_LIB + "seating");

public void
create_seating(void)
{
    set_name("couch");
    add_adj(({"silk","plush","west", "western", "maroon","wool"}));
    set_short("maroon silk couch");
    set_long("This plush couch stretches along the western wall. "+ 
	"It is long and wide enough that it "+
    "could double as a bed for napping on. It is made of pine "+
    "and white wool, with maroon silk cushions. "+
    "It looks very comfortable.\n");

    set_seat_names(({"couch", "west couch", "azure couch"}));
    set_seat_id("_maroon_couch");

    add_item(({"maroon silk", "maroon cushions", "maroon silk cushions", 
	"silk", "silk cushions"}), "They are plump and soft and very "+
    "luxurious.\n");
	
    set_max_seat(3);
    set_lay_num(2);

    set_shift_seat(1);
    set_allow_kinky(1);
}
