//-*-C++-*-
 // The Dancing Potato Inn
 // file name: /d/Avenir/common/bazaar/intr/inn.c
 // creator(s):  Glinda, may, 1995
 // last update:  Lilith, June 2004: Moved inn to the port.
 // revisions:    Lilith, Sep 1999: Facelift.
 // purpose:      An Inn for the Bazaar
 // note:         All descriptions taken from Ilyians Dancing potato
 //               All food by Ilyian
 //               I had to modify to fit with my waiter.
 //               Update the logs (Ilyian, Oct 30, 1995)
 // bug(s):
 // to-do:

#pragma strict_types;

inherit "/std/room";
#include "/d/Avenir/common/bazaar/bazaar.h";

static object waiter, cleaner, thief;

int exa_man(string str);
int sit_at_table = 1;

void
create_room()
{
    set_short("The Stormy Haven Inn");
    set_long("The Stormy Haven is a large inn which caters to the "+
        "basic needs of those visiting Sybarus.  You are in the "+
        "great hall of the inn, a long room with a low "+
        "stone barrel-vault ceiling and polished slate floors.  "+
        "The walls are of granite blocks covered here and there "+
        "with heavy draperies which are hung from floor to ceiling "+
        "in an attempt to soften the bleakness of cold stone.  "+
        "Everything here is made of stone, from the tables to the "+
        "stone benches pushed neatly underneath them, which isn't "+
        "surprising considering the rarity of trees in the area.  "+
        "From the open doorway to the south you can hear the voice "+
        "of the proprietor over the muted roar of the waterfall. "+
        "Set near the west wall is a counter from which the wait"+
        "staff work and watch over the room. A circular staircase "+
        "leads up.\n");
    add_item(({"rug","tapestry","tapestries","draperies"}),
        "The draperies are quite heavy and contribute a lot to "+
        "making the room more hospitable. The cinnamon-brown and "+
        "bright green colours contrast nicely with the cool gray "+
        "stone of the floor and walls.\n");
    add_item(({"table","tables","chair","chairs","bench","benches"}),
       "@@desc_table");
    add_item(({"counter", "mosaic"}),
       "The counter is of stone, its surface an "+
       "abstract mosaic of shell, bone and bits of semi-precious "+
       "stone.  Upon it are scattered various forms and papers "+
       "necessary for running a business in this area.\n");
    add_item(({"papers", "forms"}),
       "You spot a prominently placed paper that seems to indicate "+
       "that this establishment has been approved by the High "+
       "Commissioner's office.\n");
	
	IN;       // Avenir is an undergound domain.
	IN_IN;    // Interior room, no flux msgs, steeds etc.

    add_exit(PORT + "pub", "south", 0, 1);
    add_exit(PORT + "landing", "up", 0, 2);
  //    add_exit(BAZAAR + "intr/innroom", "up", 0, 2);
    add_exit(BAZAAR + "intr/kitchen", "north", 0, 1);

    reset_room();
 }

void
reset_room()
{
    object thief, pal;
    int i;

    if(!objectp(waiter))
    {
        waiter=clone_object(NPC + "waiter");
        waiter->move(TO);
    }

    if(!objectp(cleaner))
    {
        cleaner=clone_object("/d/Avenir/common/mon/cleaner");
        cleaner->move(TO);
    }

 
    if(!objectp(thief))
        sit_at_table = 1;
 
    if (sizeof(FILTER_PLAYERS(all_inventory(TO))))
        return;


    for (i = 0; i <= 2; i++)
    {
        pal = present("pal", TO);
        if (pal)
            pal->remove_object();
    }

}

void
init()
{
::init();

    add_action("exa_man", "examine");
    add_action("exa_man", "exa");
}

string
desc_table()
{
    string text;

    text = "The tables and benches are made entirely from stone. They "+
       "appear to be quite old and well-used. ";
    if (sit_at_table)
        text+= "At one table you see an undescript stranger " +
            "drinking a beer.";
    text+= "\n";
    return text;

}

int
exa_man(string str)
{

    if (!(str))
        return 0;

    if (!(sit_at_table))
        return 0;

    if (!((str == "stranger") || (str == "undescript stranger")))
        return 0;

    thief = clone_object(PORT + "mon/thief");
    thief->move(TO, 1);
    TP->catch_msg("The stranger catches your eyes, gets up " +
        "from the table and clumsily bumps into you while " +
        "he passes you on his way to the counter.\n");
    sit_at_table = 0;
    string steal_command = "steal platinum from " +TP->query_race_name()+"";
    set_alarm(0.5, 0.0, &thief->command("steal_command"));
    thief->command("steal_command");
    tell_room(TO, "A stranger at a table walks up " +
        "to the counter.\n", TP);
    return 1;

}
