/*
* the store for the Palanthas shop.
*/

inherit "/std/room";
inherit "/lib/store_support";

#include "../local.h"
#include "/sys/stdproperties.h"
#include "/d/Ansalon/common/defs.h"

#define  LOLLIPOP KOBJ + "lollipop"

public void
enter_inv(object ob, object from)
{
   ::enter_inv(ob, from);
   store_update(ob);
}

create_room()
{
   set_short("The shop's store room");
   set_long("This is the store room for the shop.\n");
   
   add_exit(KROOM + "candy_store","north");
   
   INSIDE;  /* This is an inside room */
   reset_room();
}

reset_room()
{
   object ob;
   seteuid(getuid(TO));
   if (!P(LOLLIPOP, TO))
      {
      ob = clone_object(LOLLIPOP);
      ob->add_name(LOLLIPOP);
      ob->move(TO);
      ob = clone_object(LOLLIPOP);
      ob->add_name(LOLLIPOP);
      ob->move(TO);
      ob = clone_object(LOLLIPOP);
      ob->add_name(LOLLIPOP);
      ob->move(TO);
      ob = clone_object(LOLLIPOP);
      ob->add_name(LOLLIPOP);
      ob->move(TO);
      ob = clone_object(LOLLIPOP);
      ob->add_name(LOLLIPOP);
      ob->move(TO);
      ob = clone_object(LOLLIPOP);
      ob->add_name(LOLLIPOP);
      ob->move(TO);
      ob = clone_object(LOLLIPOP);
      ob->add_name(LOLLIPOP);
      ob->move(TO);
      }
   if (!P("taffy", TO))
      ob = clone_object(KOBJ + "taffy")->move(TO);
      clone_object(KOBJ + "taffy")->move(TO);
      clone_object(KOBJ + "taffy")->move(TO); 
      clone_object(KOBJ + "taffy")->move(TO);
      clone_object(KOBJ + "taffy")->move(TO);
      clone_object(KOBJ + "taffy")->move(TO);
      clone_object(KOBJ + "taffy")->move(TO);
   if (!P("toffy", TO))
     {
      clone_object(KOBJ + "toffy")->move(TO);
      clone_object(KOBJ + "toffy")->move(TO);
      clone_object(KOBJ + "toffy")->move(TO);
      clone_object(KOBJ + "toffy")->move(TO);
      clone_object(KOBJ + "toffy")->move(TO);
      clone_object(KOBJ + "toffy")->move(TO);
      clone_object(KOBJ + "toffy")->move(TO);
     }
   if (!P("caramel", TO))
     {
      clone_object(KOBJ + "caramel")->move(TO);
      clone_object(KOBJ + "caramel")->move(TO);
      clone_object(KOBJ + "caramel")->move(TO);
      clone_object(KOBJ + "caramel")->move(TO);
      clone_object(KOBJ + "caramel")->move(TO);
      clone_object(KOBJ + "caramel")->move(TO);
      clone_object(KOBJ + "caramel")->move(TO);
     }
   if (!P("rock", TO))
     {
      clone_object(KOBJ + "rock")->move(TO);
      clone_object(KOBJ + "rock")->move(TO);
      clone_object(KOBJ + "rock")->move(TO);
      clone_object(KOBJ + "rock")->move(TO);
      clone_object(KOBJ + "rock")->move(TO);
      clone_object(KOBJ + "rock")->move(TO);
      clone_object(KOBJ + "rock")->move(TO);
     }
   if (!P("licorice", TO))
     {
      clone_object(KOBJ + "licorice")->move(TO);
      clone_object(KOBJ + "licorice")->move(TO);
      clone_object(KOBJ + "licorice")->move(TO);
      clone_object(KOBJ + "licorice")->move(TO);
      clone_object(KOBJ + "licorice")->move(TO);
      clone_object(KOBJ + "licorice")->move(TO);
      clone_object(KOBJ + "licorice")->move(TO);
     }
   if (!P("butterscotch", TO))
     {
      clone_object(KOBJ + "butterscotch")->move(TO);
      clone_object(KOBJ + "butterscotch")->move(TO);
      clone_object(KOBJ + "butterscotch")->move(TO);
      clone_object(KOBJ + "butterscotch")->move(TO);
      clone_object(KOBJ + "butterscotch")->move(TO);
      clone_object(KOBJ + "butterscotch")->move(TO);
      clone_object(KOBJ + "butterscotch")->move(TO);
     }
   if (!P("maple", TO))
     {
      clone_object(KOBJ + "maple")->move(TO);
      clone_object(KOBJ + "maple")->move(TO);
      clone_object(KOBJ + "maple")->move(TO);
      clone_object(KOBJ + "maple")->move(TO);
      clone_object(KOBJ + "maple")->move(TO);
      clone_object(KOBJ + "maple")->move(TO);
      clone_object(KOBJ + "maple")->move(TO);
     }
}
