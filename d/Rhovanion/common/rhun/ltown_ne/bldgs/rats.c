#pragma save_binary

inherit "/d/Rhovanion/lib/room";
inherit "/lib/trade";

#include <macros.h>
#include <stdproperties.h>
#include "/d/Rhovanion/defs.h"

#define PRICE 10
#define RAT "/d/Rhovanion/common/npcs/pigeon"

void init()
{
  ::init();
  add_action("rat_func", "buy");
}

void create_room()
{
  set_short("Pigeon house");
  set_long("This is the messenger-pigeon house of this large town"
    +" in Rhun.  It is quite dirty, with noisy pigeons inside their cages."
    +"  These pigeons will carry messages to faraway places."
    +"  You may `buy' a pigeon here for 10 coppers,"
    +" or exit back to the west.\n");

  config_default_trade();

  add_exit(RHUN_DIR+"ltown_ne/bldgs/po","west",0);

  add_prop(ROOM_I_INSIDE,1);

  add_item(({"pigeon", "pigeons"}), "They are everywhere"
            +" in this room, and are quite dirty and smelly.\n");
}

int rat_func(string rat)
{
  if(rat !="pigeon")
  {
    NF("The only thing you can buy here is a pigeon.\n");
    return 0;
  }
  if(!can_pay(PRICE,TP))
  {
    NF("You can't pay the price!!\n");
    return 0;
  }
  pay(PRICE,TP);
  write("You purchase a messenger pigeon.\n");
  reset_euid();
  clone_object(RAT)->move(TP);
  return 1;
}