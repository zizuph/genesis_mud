
#include "/d/Ansalon/common/defs.h"
#include "../local.h"
#include <macros.h>
#include <stdproperties.h>

inherit KURINOST_IN;
object drac;
object drac2;
object drac3;
object drac4;
object drac5;

void
reset_kurinost_room()
{
    if(!objectp(drac))
    {
	drac = clone_object(KNPC+"baaz");
	drac->GREEN;
	drac->move(TO);
    }
    if(!objectp(drac2))
    {
	drac2 = clone_object(KNPC+"bozak");
	drac2->GREEN;
	drac2->move(TO);
    }
    if(!objectp(drac3))
    {
	drac3 = clone_object(KNPC + "bozak");
	drac3->move(TO);
	drac3->GREEN;
    }
    if(!objectp(drac4))
    {
	drac4 = clone_object(KNPC + "kapak");
	drac4->move(TO);
	drac4->GREEN;
    }
    if(!objectp(drac5))
    {
	drac5 = clone_object(KNPC + "kapak");
	drac5->move(TO);
	drac5->GREEN;
    }
    return;
}


create_kurinost_room()
{
    set_short("Green Dragonarmy guard post at Kurinost");
    set_long("The guardpost for the Green Dragonarmy's camp here "+
      "outside Kurinost is marked only by a large piece of canvas "+
      "that has been stretched between trees to provide cover from "+
      "the elements.  Guards posted here are to be sure nobody "+
      "unwanted enters the camp.  People who oppose the Dark "+
      "Queen, enter at their own risk.\n");

    add_item(({"canvas","piece of canvas"}),"A dark green piece of canvas "+
      "has been stretched and tied to nearby trees providing shelter from "+
      "the elements as well as marking this as the guardpost of the camp.\n");
    add_item("kurinost","The Silvanesti city of Kurinost "+
      "to the east.  From here it appears to be more of "+
      "a village than a city.\n");
    add_item("camp","You stand in the Green Dragonarmy's "+
      "camp at Kurinost.  The camp is noted by a series "+
      "of tents clustered in a clearing of the forest.\n");
    add_item("guardpost","@@drac_here");
    add_item(({"forest","trees"}),"The forest here is healthy and "+
      "beautiful, but you notice that not far off to the "+
      "southwest the trees begin to look gnarled and ugly.\n");

    add_exit(KROOM + "road2","southwest","@@knight_check");
    add_exit(KROOM + "road","northeast",0);
    reset_kurinost_room();
}

int
knight_check()
{
    if(TP->test_bit("Krynn",1,0))
    {
	if((objectp(drac)  && (TO == E(drac))  ) || 
	  ( objectp(drac2) && (TO == E(drac2)) ) ||
	  ( objectp(drac3) && (TO == E(drac3)) ) ||
	  ( objectp(drac4) && (TO == E(drac4)) ) ||
	  ( objectp(drac5) && (TO == E(drac5)) ) )
	{
	    write("A draconian says: No Knights are allowed in the camp!\n");
	    say(QCTNAME(TP)+ " is blocked from entering the camp by the "+
	      "draconian.\n");
	    return 1;
	}
    }
    return 0;
}

string
drac_here()
{
    if((objectp(drac)  && (TO == E(drac))  ) || 
      ( objectp(drac2) && (TO == E(drac2)) ) ||
      ( objectp(drac3) && (TO == E(drac3)) ) ||
      ( objectp(drac4) && (TO == E(drac4)) ) ||
      ( objectp(drac5) && (TO == E(drac5)) ) )
    {
	return "The entrance to the Dragonarmy camp is guarded by draconians.  "+
	"They are here to prevent unwanted visitors from disturbing "+
	"the camp.\n";
    }

    return "The guardpost seems deserted, no draconians stand guard.\n";
}
