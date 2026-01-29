/*
 *  /d/Gondor/clubs/nisse/obj/stone.c
 *
 *  This stone initate joining ceremony of Nisse Ohtar when it is thrown
 *  into the ceremony pool.
 *
 *  Deagol, March 2003
 */

inherit "/std/object";

#include <stdproperties.h>
#include <macros.h>

#include "/d/Gondor/defs.h"
#include "../nisse_defs.h"

void
create_object()
{
    ::create_object();
    
    set_name(({"stone", "stone", "rock"}));
    set_adj("small");
    add_adj("black");
    set_short("small black stone");
    set_long("You study the " + short() + ". You wonder who lost it here. " +
        "It has a diamond shape, but is competely dull. Obviously " +
        "it is not a black diamond. After a closer look you notice its " +
        "surface is carved with letters.\n");

    add_item(({"letters"}), "You revealed a secret of Nisse Ohtar. If you " +
        "want to join the Nisse Ohtar club, throw the stone in the pool. " +
        "Otherwise throw it away.\n");

    add_prop(OBJ_I_WEIGHT, 50);
    add_prop(OBJ_I_VOLUME, 50);
}

/*
 *  Function name: read_letters
 *  Description  : This routine is called when a player examine the letters.
 *  Arguments    : string str - as entered by the player
 *  Returns      : 0 / 1
 */
int
read_letters(string str)
{
    if (!strlen(str) || !parse_command(str, ({}),
        "'letters' [on] [the] [small] [black] [stone]"))
    {
        notify_fail("Read what?\n", 0);
        return 0;
    }
    
    write("You revealed a secret of Nisse Ohtar. If you want to join the " +
        "Nisse Ohtar club, throw the stone in the pool. Otherwise throw " +
        "it away.\n");
    return 1;
}

/*
 *  Function name: throw_stone
 *  Description  : It initiates the joining ceremony.
 *  Arguments    : string str - as entered by the player
 *  Returns      : 0 / 1
 */
int
throw_stone(string str)
{
    if (!strlen(str))
    {
        notify_fail("Throw what?\n", 0);
        return 0;
    }
    
    if (str == "stone away")
    {
        write("You throw " + short() + " away.\n");
        say(QCTNAME(TP) + " throws " + short() + " away.\n");
        remove_object();
        return 1;
    }
    
    if (file_name(ENV(TP)) != NISSE_ROOM_DIR + "o_pool" && str == "stone")
    {
        write("You throw " + short() + " away.\n");
        say(QCTNAME(TP) + " throws " + short() + " away.\n");
        remove_object();
        return 1;
    }

    if (!parse_command(str, ({}),
        "'stone' [in] [into] [the] [tranquil] 'pool' / 'water'"))
    {
        notify_fail("Throw what where?\n", 0);
        return 0;
    }
    
    if (TP->query_nisse_level() != 0 || TP->query_wiz_level())
    {
        write("You throw the " + short() + " into the tranquil pool.\n");
        say(QCTNAME(TP) + " throws a " + short() + " into the tranquil " +
            "pool.\n");
        remove_object();
        return 1;
    }

    (NISSE_OBJ_DIR + "nisse_admin")->join_nisse();
    remove_object();
    return 1;
}

void
init()
{
    ::init();
    
    add_action(throw_stone, "throw");
    add_action(read_letters, "read");
}
