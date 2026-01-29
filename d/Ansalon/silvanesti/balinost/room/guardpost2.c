#include "/d/Ansalon/common/defs.h"
#include <stdproperties.h>
#include "/d/Ansalon/silvanesti/balinost/local.h"
#include <macros.h>

inherit BALINOST_OUT;

object ob1,ob2,ob3;
reset_balinost_room()
{
  if(!objectp(ob1))
   {
   ob1 = clone_object(BLIVE + "guard");
   ob1->move_living("xxx",TO);
   }
  if(!objectp(ob2))
   {
   ob2 = clone_object(BLIVE + "guard");
   ob2->move_living("xxx",TO);
   }
  if(!objectp(ob3))
   {
   ob3 = clone_object(BLIVE + "guard");
   ob3->move_living("xxx",TO);
   }
   ob1->team_join(ob2);
   ob1->team_join(ob3);
   return;
}


create_balinost_room()
{
    set_short("At a guard station");

    set_long("The Balinost Guard posts men here to keep track of "+
      "who enters and leaves the city.  Those who cause trouble "+
      "within city limits are placed in jail.  The post is marked "+
      "only by a weapon rack attached to one of the tormented "+
      "trees.  "+season_descr()+tod_descr2()+tod_descr1()+"\n");
    add_item(({"rack","weapon rack"}),"The weapon rack is empty now "+
      "since all of the spare weapons have been removed from the city "+
      "due to the evacuation.\n");


    add_exit(BROOM + "street20","southwest",0);
    reset_balinost_room();
}

