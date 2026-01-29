#pragma save_binary
#pragma strict_types

#include "../../defs.h"

inherit ROOMS_DIR + "sparkle_room_base";
inherit "/lib/store_support";





void
fill_store()
{
    for (int i = 0; i < 10; i++)
     {
        clone_object(OBJ_DIR + "magic/minor_heal_p")->move(this_object());
        
      }
      
       for (int i = 0; i < 10; i++)
     {
        
        clone_object(OBJ_DIR + "magic/minor_mana_p")->move(this_object());
      }
      
}


public void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);

    store_update(ob);
}

void
create_sparkle()
{
    set_short("The magic mojo's store room");
    set_long("The magic mojo's store room.\n");
    
    fill_store();
}

