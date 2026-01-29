/* A path in the foothills (28). ~mucalytic/hills/locations/path28 */

#include "../defs.h"
#include "/sys/macros.h"

inherit STD + "hill_path";

void create_hill_path()
{
    add_exit(LOCATIONS + "path30", "west", 0, 3);
    add_exit(PUZZLE_QUEST + "locations/entrance", "north", "@@check_force_field", 1);
}

void create_room()
{
    string desc;

    ::create_room();

    desc = extract(query_long(), 0, (strlen(desc) - 2));

    desc += " The northward path runs up to a stone arch in the side of a "+
        "nearby hill which you presume leads into an underground cavern of "+
        "some sort. There is a sign nailed above this.\n";

    set_long(desc);

    add_item("sign", "The sign is made of an untarnishable copper-coloured "+
        "metal and has neat writing etched onto its surface.\n");

    add_item(({"arch", "stone arch"}), "The arch has been built into the "+
        "side of a hill just to your north. You notice that a faint blue "+
        "light plays between its entrance and that there is a sign nailed "+
        "to its upper portion.\n");
}

void init()
{
    ::init();

    add_action("do_read", "read");
}

int check_force_field()
{
    if(TP->query_wiz_level())
        return 0;
    else
    {
        write("You try to enter through the arch but are repelled by a "+
            "force-field.\n");
        say(QCTNAME(TP)+" tries to enter through the arch but is repelled "+
            "by force-field.\n");
        return 1;
    }
}

int do_read(string str)
{
    if(!strlen(str))
        return 0;

    if(str == "sign")
    {
        write("The sign reads:\n\nThis area is still under development. As "+
            "soon as it is completed, the force-field will be removed.\n\n"+
            "Kind regards - Sir Mucalytic.\n");

        if(!TP->query_invis())
            say(QCTNAME(TP)+" reads the writing on the sign above the arch.\n");
        return 1;
    }
    else
        write("Read what? IE: 'read sign'.\n");        
    return 1;
}
