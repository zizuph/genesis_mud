inherit "/d/Avenir/inherit/air_steed";
#include "/d/Avenir/common/common.h"

void
create_air_steed()
{
    set_name("steed");
    set_race_name("steed");
    add_name("steed");

    set_adj("flying");

    set_short("flying steed");

    set_long("It is a great, winged steed.\n");

    set_places("park",   ({ UNION + "tomb/tomb_landing",
                            SHIP + "sea/darkseae8",
                            SHIP + "sea/darkseae7",
                            SHIP + "sea/darkseae6",
                            SHIP + "sea/darkseae5",
                            SHIP + "sea/darkseae4",
                            SHIP + "sea/darkseae3",
                            SHIP + "sea/darkseae2",
                            SHIP + "sea/darkseae1",
                            PK + "s_path6" }));

    set_places("tomb",   ({ PK + "s_path6",
                            SHIP + "sea/darkseae1",
                            SHIP + "sea/darkseae2",
                            SHIP + "sea/darkseae3",
                            SHIP + "sea/darkseae4",
                            SHIP + "sea/darkseae5",
                            SHIP + "sea/darkseae6",
                            SHIP + "sea/darkseae7",
                            SHIP + "sea/darkseae8",
                            UNION + "tomb/tomb_landing" }));
}

