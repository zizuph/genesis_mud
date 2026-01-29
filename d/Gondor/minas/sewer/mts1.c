inherit "/d/Gondor/minas/sewer/sewer";
#include "/d/Gondor/defs.h"

object rat1,rat2,rat3;
void create_sewer() 
{
    make_the_room("");
    enable_reset();
    smelly_air(1);
}

void
add_stuff()
{
    if(!rat1)
        rat1 = clone_object(MINAS_DIR + "sewer/lrat");
        rat1->move(this_object());
    if(!rat2)
        rat2 = clone_object(MINAS_DIR + "sewer/rat");
        rat2->move(this_object());
        rat2->team_join(rat1);
    if(!rat3)
        rat3 = clone_object(MINAS_DIR + "sewer/rat");
        rat3->move(this_object());
        rat3->team_join(rat1);
}

void
reset_room()
{
    add_stuff();
}
    
