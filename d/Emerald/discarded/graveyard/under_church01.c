inherit "/std/room";

#include "/d/Emerald/common/guild/vamp/guild.h"
#include "defs.h"

void
create_room()
{
    set_short("Secret chamber");
    set_long("    A small chamber deep beneath the church.  The air is " +
       "stale and damp, and the stone walls show evidence of flooding.  " +
       "Standing prominently against the west wall is a dark statue of " +
       "a vaguely humanoid figure.\n");

    add_item(({ "statue", "figure", "dark statue", "humanoid figure" }),
       "The dark figure is a powerfully built, humanoid creature, except " +
       "for the featherless wings outstretched from its back.  The statue is " +
       "formed from a black, glassy crystal, and the details are so " +
       "perfectly rendered that you question whether any mortal sculptor " +
       "could create such a work.  It wears upon its face an expression of " +
       "rage and contempt, and as your gaze passes over its countenance, " +
       "you notice a faint glimmer of light in its eyes.\n");

    add_item(({ "walls", "stone walls" }),
       "The smooth, stone walls reach up over six meters to the ceiling.  " +
       "About two meters from the bottom, you can see where the stone " +
       "has been discoloured, evidence of flooding.\n");

    add_exit("church", "up");
}

public int
touch(string str)
{
    string coven;
    
    if (!strlen(str))
    {
        notify_fail(capitalize(query_verb()) + " what?\n");
        return 0;
    }

    if (parse_command(str, ({}),
        "[the] [the] [dark] [humanoid] 'statue' / 'figure'"))
    {
        write("You touch the statue.\n");
        return 1;
    }

    if (!parse_command(str, ({}), 
        "[the] 'eye' / 'eyes' [of] [the] [dark] [humanoid] " +
        "[statue] / [figure]"))
    {
        notify_fail(capitalize(query_verb()) + " what?\n");
        return 0;
    }

    setuid();
    seteuid(getuid());

    coven = LAIR_MANAGER->query_coven(CHURCH_LAIR);

    if (coven && (coven != this_player()->query_vamp_coven()))
    {
        write("You touch the statue.\n");
        return 1;
    }

    write("You touch the eyes of the statue.\n");

    this_player()->move_living("X", 
        "/d/Emerald/kroad/graveyard/under_church02", 1);

    return 1;
}

public void
init()
{
    ::init();
    add_action(touch, "touch");
    add_action(touch, "press");
    add_action(touch, "push");
}
