inherit "/d/Cirath/ak_wela/inherit/outside.c";
#include "/d/Cirath/common/defs.h"
#define CHALK_ID "_graffitti_chalk_"
#define STD_LINE_WIDTH 80


string *graffittis = ({ });

void
create_room()
{
    set_short("Szun Moon Boulevard");
    set_long("This large thoroughfare runs through the very heart of the " +
             "city.  To your north, you see the Inn of Ak Wela, where " +
             "weary travelers can spend a few coins to rest their bones " +
             "for a while.  The sturdy, dark brown wall of Phiringy " +
             "Trading's warehouse blocks the view to the south.  " +
             "@@check_graffitti@@Szun Moon Boulevard ends at the " +
             "boardwalk a short distance to the east.  Beyond that are " +
             "the docks.  A short ways westward rises a tall, triangular " +
             "building, with a shorter pagodah just beyond that.  Further " +
             "on, the street eventually leaves the city.\n");
    add_item( ({"graffitti", "wall"}), "@@read_graffitti");
    add_exit(AK_WELA_DIR + "inn", "north", 0, 2);
    add_exit(AK_WELA_DIR + "szun_moon1", "east", 0, 2);
    add_exit(AK_WELA_DIR + "szun_moon3", "west", 0, 2);

    graffittis += ({"Scrawled in red chalk here you see:\nKilroy was here!"});
    graffittis += ({"Scrawled in purple chalk here you see:\n" +
                    "So you thought you could kill me, fool.  -- WoY"});
}


string
check_graffitti()
{
    if (sizeof(graffittis))
        return("Some graffitti has been written on the wall here.  ");
    return ("  ");
}


int
write_graffitti(string args)
{
    string where, message, *exploded;
    object chalk, *inv;
    int count = 0;

    inv = all_inventory(TP);
    for (count = 0; count < sizeof(inv); count++)
        if (member_array(CHALK_ID, inv[count]->query_name()) > -1)
            chalk = inv[count];

    if (!chalk || !objectp(chalk))
    {
        notify_fail("You don't have anything with which to " + query_verb() +
                    "!\n");
        return 0;
    }

    exploded = explode(args, " ");
    where = exploded[0];
    message = implode(exploded[1..sizeof(exploded)], " ");

    if (where != "graffitti" || where != "wall")
    {
        notify_fail("What or where did you want to scrawl?\n");
        return 0;
    }

    if (strlen(message) > STD_LINE_WIDTH)
        TP->catch_msg("You ran out of room on the wall!\n");
    else
    {
        graffittis += ({"Scrawled in " + (chalk->query_adjs())[0] +
                        "chalk here you see:\n" + message});
        TP->catch_msg("You scribble your message on the wall.\n");
    }

    chalk->remove_object();
    return 1;
}


string
read_graffitti()
{
    int count;
    string tmp = "";

    if (!sizeof(graffittis))
        return ("The wall has recently been washed clean of all graffitti.\n");
    for (count = 0; count < sizeof(graffittis); count++)
        tmp += graffittis[count] + "\n";
    return tmp;
}


void
init()
{
    add_action("read_graffitti", "read");
    add_action("write_graffitti", "write");
    add_action("write_graffitti", "scrawl");
    add_action("write_graffitti", "scribble");
    ::init();
}


string
wizinfo()
{
    return ("If an inappropriate message is placed on the wall here, you " +
            "may erase it with:\n\nCall here reset_graffitti <num>\n\n" +
            "To erase all graffittis, do not give a number.  Please " +
            "feel free to use this.  I did not place this here so " +
            "players could give out quest info or cuss each other out.\n");
}


varargs string
reset_graffitti(int which)
{
    int count, size;

    size = sizeof(graffittis);

    if (!size)
        return "The board now reads:\n@@read_graffitti";

    if (size == 1 || !which)
    {
        graffittis = ({});
        return "The board now reads:\n@@read_graffitti";
    }

    if (which < 0 || which > size)
    {
        TP->catch_msg("Invalid graffitti number: " + which + "\n", TO);
        return "The board now reads:\n@@read_graffitti";
    }

    if (which == sizeof(graffittis))
        graffittis = graffittis[0..sizeof(graffittis) - 2];
    which--;
    if (!which)
        graffittis = graffittis[1..sizeof(graffittis) - 1];
    else
        graffittis = graffittis[0..which - 1] + graffittis[which + 1..size - 1];

    return "The board now reads:\n@@read_graffitti";
}
