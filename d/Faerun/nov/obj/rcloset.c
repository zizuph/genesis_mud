#pragma strict_types

inherit "/std/receptacle.c";

#include <stdproperties.h>
#include "../nov.h"

void
create_receptacle()
{
    
    set_short("black wooden closet");
    set_pshort("black wooden closets");
    set_name("closet");
    set_adj("black");
    add_adj("wooden");
    set_long("This is a black-painted wooden closet.\n");
    

    add_item(({"door", "doors"}),
     "The black wooden closet has two doors attached to it.\n");  
    //set_no_show_composite(1);

    add_prop(OBJ_M_NO_GET, "The black wooden closet is fixed to the floor, you cannot take it.\n");
    add_prop(CONT_I_MAX_VOLUME, 50000);
    add_prop(CONT_I_MAX_WEIGHT, 75000);
    add_prop(CONT_I_VOLUME,  4500);
    add_prop(CONT_I_WEIGHT,  5000);
    add_prop(CONT_I_RIGID,      1);
    add_prop(CONT_I_TRANSP,     0);
    add_prop(CONT_I_CLOSED, 1);
    
    setuid();
    seteuid(getuid());
    
    
    
    clone_object(NOV_DIR + "obj/necro_robe")->move(this_object(), 1);
    clone_object(NOV_DIR + "obj/necro_robe")->move(this_object(), 1);
    clone_object(NOV_DIR + "obj/necro_robe")->move(this_object(), 1);
    clone_object(NOV_DIR + "obj/necro_robe")->move(this_object(), 1);
    clone_object(NOV_DIR + "obj/necro_robe")->move(this_object(), 1);
    clone_object(NOV_DIR + "obj/necro_robe")->move(this_object(), 1);
    clone_object(NOV_DIR + "obj/necro_robe")->move(this_object(), 1);
    clone_object(NOV_DIR + "obj/necro_robe")->move(this_object(), 1);
    clone_object(NOV_DIR + "obj/necro_robe")->move(this_object(), 1);
    clone_object(NOV_DIR + "obj/necro_robe")->move(this_object(), 1);
    clone_object(NOV_DIR + "obj/necro_robe")->move(this_object(), 1);
    clone_object(NOV_DIR + "obj/necro_robe")->move(this_object(), 1);
    clone_object(NOV_DIR + "obj/necro_robe")->move(this_object(), 1);
    clone_object(NOV_DIR + "obj/necro_robe")->move(this_object(), 1);
    clone_object(NOV_DIR + "obj/necro_robe")->move(this_object(), 1);
    clone_object(NOV_DIR + "obj/necro_robe")->move(this_object(), 1);
    clone_object(NOV_DIR + "obj/necro_robe")->move(this_object(), 1);
    clone_object(NOV_DIR + "obj/necro_robe")->move(this_object(), 1);
    clone_object(NOV_DIR + "obj/necro_robe")->move(this_object(), 1);
    clone_object(NOV_DIR + "obj/necro_robe")->move(this_object(), 1);


}
