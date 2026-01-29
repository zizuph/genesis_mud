#pragma strict_types

inherit "/d/Gondor/common/room";

#include "/sys/macros.h"
#include "/sys/ss_types.h"
#include "/sys/stdproperties.h"

#include "/d/Gondor/defs.h"

public void    reset_room();

static object  patrol;

public void
create_room()
{
    set_short("Before the Mordor Gate of Minas Morgul");
    set_long("@@long_func");
    add_exit(MORGUL_DIR + "vale/mrd5","east",0,3);
    clone_object(MORGUL_DIR + "city/mordorgate1.c")->move(TO);
    reset_room();
}

void
add_stuff()
{
    if (!patrol) 
    {
        patrol = clone_object(NPC_DIR+"redleadorc");
        patrol->set_monster_home(MORGUL_DIR+"city/o_egate");
        patrol->set_restrain_path(({MORGUL_DIR +"vale"}));
        patrol->set_pack_size(6);
        patrol->move(TO);
    }
}

public string
long_func()
{
    object  gate = present("door");
 
    if (gate->query_open())
        return BSN("You are standing before the Mordor Gate of Minas "
          + "Morgul. The cavernous gate, shaped like an open mouth "
          + "with gleaming teeth, is gaping wide. Inside the city "
          + "looks pale and gloomy, and you think twice before "
          + "entering. The road winds up towards the Nameless Pass "
          + "high on the Ephel Duath to the east, gleaming faintly.");
    return BSN("You are standing before the Mordor Gate of Minas "
      + "Morgul. The dark and ominous gate is closed, but you feel as "
      + "if you are being watched. The road winds down towards the "
      + "bridge to the north.");
}

void
reset_room()
{
    add_stuff();
}


