/*
 *  Added fishing properties allowing fishing - Arman 2021
 */

#include "/d/Ansalon/common/defs.h"
#include "/d/Ansalon/balifor/flotsam/local.h"

inherit FLOTSAM_OUT;

#include "/d/Krynn/common/herbsearch.h"
#define H1 "/d/Krynn/common/herbs/ss_grass"
#define H2 "/d/Krynn/common/herbs/surf_grass"

#define LIVE_I_CAN_FISH      "_live_i_can_fish"

void
reset_flotsam_room()
{
    return;
}

create_flotsam_room()
{
    set_short("Sandy beach along the bottom of a cliff near Flotsam");
    set_long("@@long_descr");

    add_item(({"sand","beach","sandy beach"}),"A thin " +
      "strip of golden sand at the bottom of the cliff, with the odd " +
      "shell or piece of half-buried wreckage scattered along its " +
      "length.\n");
    add_item("shells","Sifting through the sand you find the " +
      "odd piece of broken shell, but unfortunately nothing else of " +
      "interest.\n");
    add_item("seagulls","Seagulls fly overhead and nest in " +
      "the nearby cliff.\n");
    add_item(({"wreckage","vessels"}),"Scattered along the beach are the remains " +
      "of vessels that did not survive a Blood Sea storm. \n");
    add_item("cliff","The cliff rises a fair distance up into the sky. " +
      "You see seagulls nesting in its rocky face, as well as a path " +
      "leading up to the top of the cliff to your southwest. \n");

    add_exit(FROOM + "street23","east",0);
    add_exit(FROOM + "street16","southwest","@@path",0);

    add_cmd_item(({"water","sea","waves"}),
      ({"swim","dive","wade"}),"@@swim_water");

    set_tell_time(95);
    add_tell("Waves lap against the sandy shore.\n");

    seteuid(getuid(TO));
    set_search_places(({"sand","beach","herbs"}));
    add_prop(OBJ_I_SEARCH_TIME,3);
    add_prop(OBJ_S_SEARCH_FUN,"herb_search");
    add_prop(LIVE_I_CAN_FISH, "bloodsea");

    add_herb_file(H1);
    add_herb_file(H2);

    reset_flotsam_room();
}

string
long_descr()
{
    return tod_descr1() + tod_descr2() + "You stand upon " +
    "a sandy beach at the bottom of the cliff. " + season_descr() +
    " \n";
}

string
swim_water()
{
    write("The water looks a little rough to "+
      "swim around in, so you decide against it.\n");
    return "";
}

int
path()
{
    write("You climb the steep path to the top of the cliff. \n");
    return 0;
}

public void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);
    
    if (interactive(ob))
        start_room_tells();
}
