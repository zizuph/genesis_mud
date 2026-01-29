#include "/d/Krynn/common/defs.h"
#include "../local.h"
#include <macros.h>
#include <stdproperties.h>
#include "/d/Krynn/common/clock/clock.h"

inherit THARK_OUT;
inherit HERBSEARCHNEW

#define KNPC "/d/Krynn/solamn/splains/living/"

string *herbs = HERB_MASTER->query_herbs(({"mountains","hills",}));
object drac1, drac2, drac3, drac4, hob1, hob2;

void
reset_tharkadan_room()
{
    set_searched(random(2));

   if(!objectp(drac1) && (GET_SEASON != WINTER))
      {
      drac1 = clone_object(LIVING + "sivak_leader");
      drac1->move(TO); 
   }
   if(!objectp(drac2) && (GET_SEASON != WINTER))
      {
      drac2 = clone_object(KNPC + "kapak");
      drac2->set_stats(({90,90,90,60,60,150}));
      drac2->set_color("red");
      drac2->move(TO);
   }
   if(!objectp(drac3) && (GET_SEASON != WINTER))
      {
      drac3 = clone_object(KNPC + "kapak");
      drac3->set_stats(({90,90,90,60,60,150}));
      drac3->set_color("red");
      drac3->move(TO);
   }
   if(!objectp(drac4) && (GET_SEASON != WINTER))
      {
      drac4 = clone_object(KNPC + "bozak");
      drac4->set_stats(({90,90,90,90,60,150}));
      drac4->set_color("red");
      drac4->move(TO);
   }
   if(!objectp(hob1) && (GET_SEASON != WINTER))
      {
      hob1 = clone_object(LIVING + "hob_archer");
      hob1->arm_me();
      hob1->move(TO);
   }
   if(!objectp(hob2) && (GET_SEASON != WINTER))
      {
      hob2 = clone_object(LIVING + "hob_archer");
      hob2->arm_me();
      hob2->move(TO);
   }

    if((GET_SEASON == WINTER) && (objectp(drac1)))
    {
        drac1->command("emote retreats down the trail with his patrol " +
           "back to Pax Tharkas as the winter snows block the trail.");
        drac2->remove_object();
        drac3->remove_object();
        drac4->remove_object();
        hob1->remove_object();
        hob2->remove_object();
    }

}

create_tharkadan_room()
{
    set_short("@@short_descr");
    set_long("@@long_descr");

    add_item(({"snow","snow-covered","snow-covered ground",
	"white","snow-covered land","winters snow","winter's snow"}),
      "@@add_item_snow");
    add_item(({"path","road","rugged pass","rugged path","trail"}),
      "@@add_item_path");

    add_exit(ROOM + "path5","southeast","@@check_pass");
    add_exit(ROOM + "path3","northwest",0);

    seteuid(getuid(TO));
    set_up_herbs( ({ ONE_OF(herbs), ONE_OF(herbs), ONE_OF(herbs),
       ONE_OF(herbs), ONE_OF(herbs) }), ({ "pass","ground" }), 6);

    reset_tharkadan_room();
}

string
short_descr()
{
    return short_mountain_desc();
}

string
long_descr()
{
    return long_mountain_desc()+"\n";
}

int
check_pass()
{
    if(objectp(drac1) && (E(drac1) == TO))
    {
       if(!CAN_SEE(drac1, TP))
       {
          write("You manage to pass the Dragonarmy patrol without " +
              "being observed.\n");
          return 0;
        }
       if(TP->query_guild_name_occ() == "Priests of Takhisis")
       {
          write("The Dragonarmy patrol lets you pass without question.\n");
          return 0;
        }
       if(TP->query_guild_name_occ() == "Dragonarmy")
       {
          if(TP->query_dragonarmy_division() == "blue")
          {
             drac1->command("spit " +TP->query_real_name());
             drac2->command("snicker");
             drac1->command("say Blue skum! Get out of here back to your" +
                " bitch of a Highlord. This is Red territory!");
             drac4->command("flex menacing");
             return 1;
          }
          drac1->command("nod . " +TP->query_real_name()); 
          drac1->command("say Verminaard will have our heads if we " +
             "don't catch those escaped prisoners! Go get them!");
          return 0;
        }
       if(TP->query_guild_name_occ() == "Solamnian Knights")
       {
          drac1->command("say Knight scum! Attack!");
          drac1->command("kill " +TP->query_real_name()); 
          return 1;
       }

       write("The Dragonarmy patrol blocks you from going southeast.\n");
       drac1->command("say By order of Lord Verminaard, the pass is " +
            "closed!");
       return 1;
    }
  
   return 0;
}