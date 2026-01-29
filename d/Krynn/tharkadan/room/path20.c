#include "/d/Krynn/common/defs.h"
#include "../local.h"
#include <macros.h>
#include <stdproperties.h>
#include "/d/Krynn/common/clock/clock.h"
#include "/d/Ansalon/guild/neidar/guild.h"

inherit THARK_OUT;
inherit HERBSEARCHNEW

#define LIVE_I_CAN_FISH      "_live_i_can_fish"

string *herbs = HERB_MASTER->query_herbs(({"mountains","hills",}));
object dwarf, war1, war2, war3, pig1, pig2;

void
reset_tharkadan_room()
{
    set_searched(random(2));

    if(!objectp(dwarf))
    {
      dwarf = clone_object(LIVING + "neidar_scout");
      dwarf->sit_down();
      dwarf->move(TO);
    }

   if(objectp(dwarf) && (!dwarf->query_attack()))
   {
      dwarf->sit_down();
   }

   if(objectp(war1) && (!war1->query_attack()))
   {
      war1->command("emote returns to the village.");
      war1->remove_object();
   }

   if(objectp(war2) && (!war2->query_attack()))
   {
      war2->command("emote returns to the village.");
      war2->remove_object();
   }

   if(objectp(war3) && (!war3->query_attack()))
   {
      war3->command("emote returns to the village.");
      war3->remove_object();
   }

   if(objectp(pig1) && (!pig1->query_attack()))
   {
      pig1->command("emote returns to the village.");
      pig1->remove_object();
   }

   if(objectp(pig2) && (!pig2->query_attack()))
   {
      pig2->command("emote returns to the village.");
      pig2->remove_object();
   }

}

create_tharkadan_room()
{
    set_short("@@short_descr");
    set_long("@@long_descr");

    add_item(({"snow","snow-covered","snow-covered ground",
	"white","snow-covered land","winters snow","winter's snow"}),
      "@@add_item_snow");
    add_item(({"path","trail","pass","valley pass"}),
      "You stand on a trail running through the Tharkadan Mountain " +
      "Range. Here the trail heads west down to a village of " +
      "wooden cabins and east along the side of a crystal clear " +
      "mountain lake.\n");
    add_item(({"lake","crystal clear lake","clear lake","mountain lake"}),
      "A clear mountain lake to your south created from glacial melt " +
      "reflects the peaks of the Tharkadan Mountain Ranges.\n");
    add_item(({"village","wooden cabins","cabins","cabin",
      "lodgepole buildings","buildings","lodgepole cabins","encampment"}),
      "To your west is a village of lodgepole cabins nestled into a "+
      "narrow valley of pine trees. Based on their precise " +
      "construction and low height it looks like an encampment of hill " +
      "dwarves of the Neidar clan. The smell of wood fires blow up " +
      "from the village on the fresh mountain air.\n");
    add_item(({"pines","pine trees","trees","lodgepole pine trees"}),
      "In the valley down to your west lodgepole pines grow crowded " +
      "together, with the cabins made from these very pines the " +
      "only thing breaking the sea of deep green below.\n"); 
    add_item(({"smoke"}),"Smoke rises up to you on the crisp " +
      "mountain air from the dwarven village below.\n");

    add_prop(LIVE_I_CAN_FISH, "alpine_lake");

    add_exit(ROOM + "dwarf/village1","west","@@closed_village");
    add_exit(ROOM + "path19","east",0);

    seteuid(getuid(TO));
    set_up_herbs( ({ ONE_OF(herbs), ONE_OF(herbs), ONE_OF(herbs),
       ONE_OF(herbs), ONE_OF(herbs) }), ({ "pass","ground" }), 6);

    reset_tharkadan_room();
}

string
short_descr()
{
    return "before a crystal clear lake in the Tharkadan Mountains";
}

string
long_descr()
{
    return long_mountain_desc()+ "Stretching out to your south is " +
       "a crystal clear mountain lake, along which the trail heads " +
       "east into the mountains and west down into a narrow valley " +
       "filled with pines. A village of wooden cabins is nestled " +
       "down there, with wisps of smoke rising from the lodgepole " +
       "buildings.\n";
}

int
closed_village()
{
   object stick;

   if(IS_MEMBER(TP))
   {
      write("The " +dwarf->short()+ " allows you to pass down to the " +
          "village.\n");
      dwarf->command("rsay Welcome, Neidar.");
      return 0;
   }

   if(this_player()->query_wiz_level())
   {
      write("The " +dwarf->short()+ " allows you to pass down to the " +
          "village.\n");
      return 0;
   }

   if(objectp(stick = present("_stick_of_ancestors", TP)))
   {
      write("The " +dwarf->short()+ " notices with surprise you " +
          "carry a branch from the Tree of Ancestors, and allows " +
          "you to pass down to the village.\n");
      return 0;
   }

   if(objectp(dwarf))
   {
      dwarf->stand_up();
      write("The " +dwarf->short()+ " blocks your way down to the " +
          "village.\n");
      say(QCTNAME(dwarf)+ " blocks "+QTNAME(TP)+ " from entering the " +
           "village.\n");
      dwarf->command("rsay I cannae let anyone into the village until " +
          "the Chieftain returns.");
      return 1;
   }

   write("You head down the trail to your west, but quickly return " +
     "after being gruffly rebuffed by the local hill dwarf residents.\n");
   say(QCTNAME(TP)+ " heads down the trail to your west into the " +
     "village, but quickly returns after being rebuffed by the local " +
     "hill dwarf residents.\n");
   return 1;
}

void
summon_clan_warriors()
{
    setuid();
    seteuid(getuid());

    if(!objectp(war1))
    {
        war1 = clone_object(LIVING + "elite_dwarf");
        war1->move(this_object());
        war1->command("emote arrives from the village below.");
        war1->command("assist dwarf");       
    }
    if(!objectp(war2))
    {
        war2 = clone_object(LIVING + "elite_dwarf");
        war2->move(this_object());
        war2->command("emote arrives from the village below.");
        war2->command("assist dwarf");     
    }

    if(!objectp(war3))
    {
        war3 = clone_object(LIVING + "elite_dwarf");
        war3->move(this_object());
        war3->command("emote arrives from the village below.");
        war3->command("assist dwarf");     
    }

    if(!objectp(pig1))
    {
        pig1 = clone_object("/d/Ansalon/estwilde/living/warboar");
        pig1->move(this_object());
        pig1->command("emote arrives from the village below.");
        pig1->command("assist dwarf");    
    }

    if(!objectp(pig2))
    {
        pig2 = clone_object("/d/Ansalon/estwilde/living/warboar");
        pig2->move(this_object());
        pig2->command("emote arrives from the village below.");
        pig2->command("assist dwarf");    
    }

   return;
}
