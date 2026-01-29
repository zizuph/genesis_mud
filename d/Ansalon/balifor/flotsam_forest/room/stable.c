/* Updated March 1998 by Kentari - added horse stabling feature     *
 *                                                                  */


#include "/d/Ansalon/common/defs.h"
#include "/d/Ansalon/balifor/flotsam_forest/local.h"
#include <macros.h>
#include <stdproperties.h>
#include <ss_types.h>
#include <money.h>
#include <cmdparse.h>
#include <composite.h>

inherit FOREST_IN;
#define STABLE_INTERNAL FROOM+"stable2"
mapping gHorse = ([ ]);
object horse1;
object horse2;

void
reset_flotsam_room()
{
   if(!objectp(horse1))
      {
      horse1 = clone_object(FNPC + "horse");
      horse1->move(TO);
   }
   
   if(!objectp(horse2))
      {
      horse2 = clone_object(FNPC + "horse");
      horse2->move(TO);
   }
}

create_flotsam_room()
{
   set_short("stable");
   set_long("@@long_descr");
   
   add_item(({"small wooden stable","wooden stable","small stable","stable"}),
      "@@long_descr");
   add_item("sign","@@read_sign");
   add_cmd_item("sign","read","@@read_sign");
   add_item(({"smell","fresh hay","hay","manure","horse manure"}),
      "The source of the hay and manure smell leads, surprisingly, to hay " +
      "and manure that is randomly scattered around the stable.\n");
   add_item(({"saddle","saddles","well-oiled saddles","wall"}),
      "Against the wall of the stable are two well-oiled leather saddles " +
      "of a make similar to those used by large warhorses. They seem to " +
      "have been well looked after.\n");

   add_prop(ROOM_I_ALLOW_STEED,1);   
   add_exit(FROOM + "pathf","out",0);
   
   reset_flotsam_room();
}

string
long_descr()
{
   return "You stand within a small wooden stable. It smells of fresh " +
   "hay and horse manure. Two well-oiled saddles have been placed " +
   "against the wall here.\n";
}

string
read_sign()
{
        return "For one silver coin, you may " +
	"<stable> your horse here, and <fetch> it later at " +
        "your leisure.\n";
}

int
do_stable(string arg)
{
        object *horses;
        string pn;
	NF("Stable what? Your horse perhaps?\n");
        if (!stringp(arg))
		return 0;
        horses = FIND_STR_IN_OBJECT(arg, TO);
        if (!sizeof(horses))
                return 0;
        NF("You can only stable one horse at a time.\n");
        if (sizeof(horses)>1)
		return 0;

        NF("You can only stable horses here!\n");
        if (!horses[0]->id("horse"))
                return 0;

        pn = TP->query_real_name();
        if (!pointerp(gHorse[pn]))
		gHorse += ([ pn : horses ]);
        else
                gHorse[pn] += horses;
        horses[0]->move_living("M",STABLE_INTERNAL);

	tell_room(TO, QCTNAME(TP) + " pays the stablehand, and he " +
	"leads the " + horses[0]->short() + " away.\n", TP);
        write("You pay the stablehand, and he leads the " +
		horses[0]->short() + " away.\n");
        return 1;
}

int
do_fetch(string arg)
{
        object *horses;
        string pn;
	int i;
        NF("Fetch what? Your horse perhaps?\n");
        if (!stringp(arg))
                return 0;

        if ((arg!="horse") && (arg!="my horse") &&
                 (arg!="horses") && (arg!="my horses"))
        {
                return 0;
        }

        pn = TP->query_real_name();
        if (!pointerp(gHorse[pn]))
	{
		NF("But you have no horse stabled here.\n");
                return 0;
	}
        horses = gHorse[pn];
        for(i=0;i<sizeof(horses);i++)
		horses[i]->move_living("M",TO);
        tell_room(TO,"The stablehand fetches " +
	COMPOSITE_LIVE(horses) + ".\n");
        return 1;
}

public void
init()
{
    ::init(); // Since it is a room, this must be done.
    add_action(do_stable, "stable");
    add_action(do_fetch, "fetch");
}
