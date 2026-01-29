inherit "/d/Gondor/minas/sewer/sewer";

#include <macros.h>

#include "/d/Gondor/defs.h"

void    reset_room();

object  snake;

void
create_sewer() 
{
    set_extra_long("This tunnel connects two other tunnels, "
      + "one northwest of here, the other to the southeast, "
      + "but a massive iron grid blocks the entrance into the "
      + "tunnel to the northwest. "
      + "The slope of this connecting part of the sewers is "
      + "rather steep, going down to the southeast.");
 
    add_exit(MINAS_DIR + "sewer/s1c3", "southeast", 0, 0);
    add_exit(MINAS_DIR + "sewer/s2c4", "northwest", "@@grid_block@@", 0);

    floor("southeast");
    passage("southeast");
    grid("northwest");

    reset_room();
}

void
reset_room()
{
    if (objectp(snake))
        return;

    snake = clone_object(NPC_DIR + "snake");
    snake->set_restrain_path(MINAS_DIR +"sewer");
    snake->set_random_move(4);
    snake->set_whimpy(80);
    snake->move(TO);
    tell_room(TO, QCNAME(snake)+" arrives.\n");
}
