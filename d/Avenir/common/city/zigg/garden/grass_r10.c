#include "zigg.h"

inherit (ZIG_LIB + "seating");

public void
create_seating(void)
{
    set_name(({"grass","patch"}));
    add_adj(({"thick","silvery","oval"}));
    set_short("oval patch of thick, silvery grass");
    set_long("The grass is long and silvery. It appears almost coarse, but "+
    "is actually extremely soft. The oval is defined by river rocks and "+
    "looks like a perfect place for a picnic or to lie a while "+
    "and watch the iridescent fluctuations of the Source above.\n");

    add_item(({"rock","rocks","river rock","river rocks","smooth rock",
    "smooth rocks","grey rock","grey rocks","smooth grey river rock",
    "smooth grey river rocks"}), "The rocks are oval-shaped and smooth "+
    "and flat. They are placed to form a border around the oval patch "+
    "of grass.\n");

    set_seat_names(({"grass","patch"}));

    set_seat_id("__zigg_garden_grass");

    set_max_seat(7);
    set_lay_num(2);

    set_shift_seat(1);
    set_allow_kinky(1);
}
