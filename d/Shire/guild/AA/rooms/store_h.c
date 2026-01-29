#pragma save_binary
#pragma strict_types

#include "../guild.h"

#define OBJ_DIR (AA_DIR+"obj/")

inherit "/std/room";
inherit "/lib/store_support";


void
reset_room()
{
  int i;

  seteuid(getuid());

  for(i=0; i<5; i++)
    clone_object(OBJ_DIR+"oilflask")->move(TO);
  for(i=0; i<3; i++)
    clone_object(OBJ_DIR+"torch")->move(TO);
  for(i=0; i<2; i++)
    clone_object(OBJ_DIR+"oil_lamp")->move(TO);
  for(i=0; i<3; i++)
    clone_object(OBJ_DIR+"backpack")->move(TO);
}

void
create_room()
{
   set_short("The shop's store room");
   set_long("This is the store room for the shop.\n");

   add_exit(AA_DIR + "rooms/store_r", "west");

   set_max_values(19, 5);

   reset_room();
}

public void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);
    store_update(ob);
}
