#include "/d/Avenir/common/city/zigg/zigg.h"

inherit (ZIG_LIB + "seating");

public void
create_seating(void)
{
    set_name("couch");
    add_adj(({"satin","plush","east", "eastern", "crimson","wool"}));
    set_short("crimson satin couch");
    set_long("This plush couch stretches along the eastern wall. "+ 
	"It is long and wide enough that it "+
    "could double as a bed for napping on. It is made of pine "+
    "and white wool, with crimson satin cushions. "+
    "It looks very comfortable.\n");

    set_seat_names(({"couch", "east couch", "crimson couch"}));
    set_seat_id("_crimson_couch");

    add_item(({"crimson satin", "crimson cushions", "crimson satin cushions", 
	"satin", "satin cushions"}), "They are plump and soft and very "+
    "luxurious.\n");
	
    set_max_seat(3);
    set_lay_num(2);

    set_shift_seat(1);
    set_allow_kinky(1);
}
