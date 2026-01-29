#include "/d/Ansalon/common/defs.h"
#include "/d/Ansalon/taman_busuk/sanction/local.h"
#include <stdproperties.h>
#include <macros.h>
#include <money.h>

inherit SANCINROOM;
inherit "/lib/trade";

#define NUM sizeof(MONEY_TYPES) /* How many types of money do we use? */


object wench;

void
reset_sanction_room()
{
    if(!objectp(wench))
    {
       wench = clone_object(SNPC + "wench");
       wench->move(TO);
    }
}


void
create_sanction_room()
{
    set_short("long feasthall under The Resting Blade Inn");
    set_long("You are standing in a large feasthall under The Resting " +
      "Blade Inn. A long table has been set up here, with steaming food " +
      "and many glasses of Dragonbrew placed regularly along it. A firepit is " +
      "set into the far wall to your north, making the room somewhat hot " +
      "and stuffy.\n");

    add_item(({"table","long table"}),
      "A long wooden table has been set up here for what looks like a big banquet. " +
      "Many platters of food and glasses of Dragonbrew have been placed along it, that you " +
      "could probably grab.\n");
    add_item(({"food","platters","platters of food","steaming food"}),
      "A variety of food has been placed on platters along the table. " +
      "You can <grab food> from the table if you feel your stomach needs filling!\n");
    add_item(({"dragonbrew","brew","glasses"}),
      "Many glasses of the famous Dragonbrew have been placed along the table. You can " +
      "<grab dragonbrew> if you are hankering for a nice strong drink! But be warned, " +
      "it is addictive stuff!\n");
    add_item(({"far wall","wall","firepit","fire"}),
      "To your north is a firepit, where on occasion a spit or pot is placed. " +
      "Unfortunately, one has not been set up for this banquet, however perhaps in the " +
      "future something shall be organised?\n");

    add_exit(SCITY + "feast_entry","south",0);

    set_alarm(15.0,200.0,"stnoise"); 

    reset_sanction_room();
}

void
stnoise()
{
    switch(random(4))
    {
    case 0:
        tell_room(this_object(),
          "The fire pops loudly, sending an ember flying across the room.\n");
        break;
 
    case 1:
        tell_room(this_object(),
          "A glass of Dragonbrew falls off the table, smashing on the floor.\n");
        break;
 
    case 2:
        tell_room(this_object(),
          "The fire flares briefly, making the shadows dance throughout the room.\n");
        break;
 
    case 3:
        tell_room(this_object(),
          "A rat scutters along the floor looking for food, and then vanishes into the shadows.\n");
        break;
 
    }
}


private int
do_grab(string str)
{
    if(!str || ((str != "food") && (str != "dragonbrew")))
    {
       notify_fail("Grab what? Food or dragonbrew?\n");
       return 0;
    }

    seteuid(getuid());

    if(str == "food")
    {
      TP->catch_msg("You grab a plate of food off the table.\n");
      say(QCTNAME(TP)+ " grabs a plate of food off the table.\n");
      clone_object("/d/Ansalon/kalaman/obj/plate")->move(TP,1);
      return 1;
    }

    if(str == "dragonbrew")
    {
      TP->catch_msg("You grab a glass of Dragonbrew off the table.\n");
      say(QCTNAME(TP)+ " grabs a glass of Dragonbrew off the table.\n");  
      clone_object("/d/Ansalon/taman_busuk/neraka/obj/drink/dragonbrew")->move(TP,1); 
      return 1;   
    }

    return 0;

}

void
init()
{
    ::init();
    add_action(do_grab, "grab");
 
}


