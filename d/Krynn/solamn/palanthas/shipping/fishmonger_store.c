/*
 * the fishmonger storeroom.
 */

inherit "/std/room";
inherit "/lib/store_support";

#include "../local.h"
#include "/sys/stdproperties.h"

public void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);
    store_update(ob);
}

create_room()
{
    set_short("The fish markets store room");
    set_long("This is the store room for the fish markets.\n");

    add_exit(SHIP + "fishmonger","south");

    INSIDE;  /* This is an inside room */
    reset_room();
}

reset_room()
{
    object ob;
    seteuid(getuid(TO));
    if (!P("global_fish_obj", TO))
      {
      ob = clone_object("/d/Krynn/common/fishing/fish_object");
      ob->set_fish_value("freshwater", 1, 0);
      ob->generate_fish();
      ob->create_fish();
      ob->move(TO);
      ob = clone_object("/d/Krynn/common/fishing/fish_object");
      ob->set_fish_value("saltwater", 1, 0);
      ob->generate_fish();
      ob->create_fish();
      ob->move(TO);
      ob = clone_object("/d/Krynn/common/fishing/fish_object");
      ob->set_fish_value("saltwater", 1, 0);
      ob->generate_fish();
      ob->create_fish();
      ob->move(TO);
      ob = clone_object("/d/Krynn/common/fishing/fish_object");
      ob->set_fish_value("saltwater", 1, 0);
      ob->generate_fish();
      ob->create_fish();
      ob->move(TO);
      ob = clone_object("/d/Krynn/common/fishing/fish_object");
      ob->set_fish_value("saltwater", 1, 0);
      ob->generate_fish();
      ob->create_fish();
      ob->move(TO);
      }
}
