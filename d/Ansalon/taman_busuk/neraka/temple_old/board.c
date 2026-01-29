/* Ashlar, 30 Sep 97 */

#include "/d/Ansalon/common/defs.h"
#include "../local.h"
#include <stdproperties.h>
#include "../guild/guild.h"

inherit TEMPLE_BASE;

object  behind_arras;

void
reset_neraka_room()
{
}

string
long_descr()
{
    return "You are in a square room within the lower level of the temple. " +
    "The walls are bare stone in here, and so is the floor. A large " +
    "bulletin board is posted here, for the Priests of Takhisis to use. " +
    "Doorways lead north and southeast, and an arras stands along the " +
    "west wall.\n";
}

void
create_neraka_room()
{
    set_short("boardroom in the temple");
    set_long("@@long_descr");

    add_temple_items();
    add_item(({"doorway","small doorway"}),
    "The doorway is decorated with a wooden frame painted white.\n");
    add_item(({"frame","wooden frame","white frame"}),
    "The frame is made of wood, but you cannot discern the type of " +
    "wood. The white paint contrasts nicely with the darker walls.\n");
    add_item(({"arras", "tapestry"}),
    "The arras is made of a dark grey tapestry.\n");

    reset_room();

    add_exit(NTEMPLE + "d2", "north");
    add_exit(NTEMPLE + "common", "southwest");
    add_exit(NTEMPLE + "library", "southeast","@@go_southeast");

    clone_object(NOBJ + "guild_board")->move(TO);

    behind_arras = 0;
}

int
go_southeast()
{
    write("You feel a chill passing through you as you go southeast, and " +
    "you realise that the passage there is warded.\n");
    return 0;
}

/*
void
arras_reveal(object revealer)
{
}

int
arras_hide(string arg)
{
    string vb = query_verb();

    if (!(arg == "myself behind arras" || arg == "myself behind the arras"))
    {
        if (vb == "hide")
        {
            notify_fail("What?\n");
            return 0;
        }
        else
        {
            notify_fail(capitalize(vb) + " whom where?\n");
            return 0;
        }
    }

    if (behind_arras && E(behind_arras) != TO)
        behind_arras = 0;

    if (behind_arras)
    {
        write("You start to sidle in behind the arras, but there is " +
        "already someone behind there!\n");
        arras_reveal(this_player());
        return 1;
    }
    else
    {
        write("You sidle in behind the arras, concealing yourself.\n");
        // hide
        behind_arras = this_player();
        return 1;
    }
}

int
arras_look(string arg)
{
    if (arg != "behind arras" || arg != "behind the arras")
    {
        notify_fail("Look at what?\n");
        return 0;
    }

    if (behind_arras && E(behind_arras) != TO)
        behind_arras = 0;

    if (behind_arras)
    {
        if (behind_arras == this_player())
        {
            write("You look behind the arras, and find what must " +
            "be your long lost twin... no, wait... it's you. That " +
            "must mean YOU were hiding behind the arras.\n");
            return 1;
        }
        
        write("You look behind the arras and descover " +
            behind_arras->query_the_name(this_player()) + "!\n";
        arras_reveal(this_player());
        return 1;
    }
    else
    {
        write("You look behind the arras, but find nothing.\n";
        say(" looks behind the arras.\n");
        return 1;
    }
}

void
init()
{
    ::init();
    add_action(arras_hide, "conceal");
    add_action(arras_hide, "hide");

    add_action(arras_look, "look");
}

void
leave_inv(object ob, object to)
{
    if (ob == behind_arras)
    {
        behind_arras = 0;
    }
    ::leave_inv(ob, to);
}
*/
