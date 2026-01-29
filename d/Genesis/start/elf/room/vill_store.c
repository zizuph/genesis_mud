#include "../stddefs.h"
#include <stdproperties.h>
#include <macros.h>
#include <language.h>
#include <cmdparse.h>
#include <composite.h>
#include <filter_funs.h>

#pragma save_binary

inherit ELFROOM;
inherit "/lib/store_support";
inherit "lib/trade";


#define SHOP    ROOMDIR + "vill_shop"

#define SHORT "In a shop's store room"

#define LONG \
  "You are in the store room belonging to " + SHOP + ".\n"


create_room()
{
  set_short(SHORT);
  set_long( LONG);

  add_prop(ROOM_I_INSIDE, 1);
  
  stock();
}

reset_room()
{
  stock();
}


stock()
{
  restock_object(OBJDIR + "gibber_knife", 3, "knife");
  restock_object(OBJDIR + "torch",        2, "torch");
  restock_object(OBJDIR + "troll_club",   1, "club");
}
void
enter_inv(object obj, object from)
{
    ::enter_inv(obj, from);
    store_update(obj);
}
