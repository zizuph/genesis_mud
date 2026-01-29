#include "/d/Ansalon/common/defs.h"
#include "/d/Ansalon/balifor/flotsam/local.h"

inherit FLOTSAM_OUT;
object gob1;
object gob2;

void
reset_flotsam_room()
{
    if(!objectp(gob1))
    {
	gob1 = clone_object(FNPC + "tiny_gob");
	gob1->move(TO);
    }
    if(!objectp(gob2))
    {
	gob2 = clone_object(FNPC + "tiny_gob");
	gob2->move(TO);
    }
}

create_flotsam_room()
{
    set_short("Outside a barred store at the edge of Flotsam");
    set_long("@@long_descr");

    add_item("cliff","The cliff disappears into the darkness below. " +
      "You can hear the sounds of the waves of the Blood Sea crashing " +
      "upon the rocks below. \n");
    add_item(({"small store","store"}),"What seems to have been " +
      "a shop dealing in seafood, it must have closed down after " +
      "the occupation of Flotsam by the Dragonarmies. \n");
    add_item(({"doors","door"}),"The front door looks locked and barred, " +
      "with no chance of entrance.\n");
    add_item(({"windows","window"}),"The windows of the fish shop are " +
      "barred, closed and locked, although you notice one has had it's " +
      "glass panes smashed. You could probably squeeze through it and into " +
      "the fish shop if you wanted.\n");

    add_exit(FROOM + "street16","west",0);
    add_cmd_item(({"through window","in window"}),
      ({"squeeze","enter","climb"}),
      "@@enter_window");

    reset_flotsam_room();
}

string
long_descr()
{
    return tod_descr1() + tod_descr2() + "On the edge of a cliff " +
    "a small store stands before you. Its doors and windows seem to have been " +
    "barred up some time ago, and do not look like they are opening anytime soon. " +
    season_descr() + " \n";
}

string
enter_window()
{
    write("You squeeze through the barred window and into a deserted " +
      "fish shop.\n");
    TP->move_living("through the window",FROOM + "fish_shop",1,0);
    return "";
}
