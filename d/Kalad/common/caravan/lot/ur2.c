#include "../default.h"
inherit CVAN_ROOM;

void
create_cvan_room()
{
    add_prop(ROOM_I_INSIDE, 1);

    add_prop(ROOM_I_LIGHT, 0);

    add_prop(ROOM_S_DARK_LONG, "A dark and dismal passage.\n");

    set_short("An underground dead end");
    set_long("You've reached a dead end.\n"+
      "You can barely see inside this dark and dismal passage. "+
      "From what little light there is, you can see, and smell several "+
      "reeking piles of filth "+
      "scattered across the ground. Upon the walls and ceiling dozens of "+
      "bugs can be seen crawling all about. To your north there is nothing "+
      "save for a blank stone wall. A dark passage leads south.\n");

    add_item(({ "filth", "piles", "pile", "reeking piles", "reeking pile" }),
      "It is too disgusting to adequately describe. It lies in stinking piles "+
      "on the floor.\n");

    add_item(({ "walls", "ceiling" }),
      "This entire passage is made solely of mud, save for the northern "+
      "wall. It surprises you that this passage has managed to stay intact, "+
      "since no supports are visible. Dozens of little bugs are crawling "+
      "all over the passageway.\n");

    add_item(({ "bugs", "bug" }),
      "Filthy creatures! Cockroackes, centipedes and other nasty creatures "+
      "cover the walls and ceiling, making you think that even their small "+
      "weight might make the entire passage collapse in upon you, causing "+
      "your slow and agonizing death as hundreds of pounds of mud slowly "+
      "suffocate you...\n");

    add_item(({ "blank stone wall", "stone wall", "wall" }),
      "The northern wall looks quite old, yet seems to be intact. Examining "+
      "the wall closer you feel moisture seeping out from in between the "+
      "stone blocks that make up the wall.\n");

    add_item(({ "stone blocks", "blocks" }),
      "You peer intently at the wall and notice one block that appears to "+
      "be loose. Moving it aside, you see a dark, cramped hole. It looks "+
      "like you might be able to fit inside it.\n");

    add_item(({ "dark cramped hole", "dark hole", "cramped hole", "hole" }),
      "A tight-looking hole, filled with darkness.\n");

    set_noshow_obvious(1);

    add_exit(CVAN + "lot/ur3", "south");
}

int
enter(string s)
{
    if(!s || s != "hole")
    {
	notify_fail("What ?\n");
	return 0;
    }
    write("You start to enter the hole but realize you are too big!\n");
    say(QCTNAME(TP) + " starts to enter the hole but realizes " 
    + TP->query_pronoun() + " is too big!\n");
    return 1;
}

void
init()
{
    ::init();
    AA(enter,enter);
}
