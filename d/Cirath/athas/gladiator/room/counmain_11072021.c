/*
 * The functions contained herein were completely re-written from scratch
 * as was the MANAGER object itself.  The old design, to put it frankly,
 * sucked, and sucked pretty damned hard.  So I have re-written things
 * to be more robust and effective and efficient.  It should also be
 * much simpler to add future functionality now.
 *
 * Unfortunately, do to horrendous design flaws in the original guild
 * there is absolutely no way to track the current membership of the
 * guild.  And it's far far to late to add it in a few years later without
 * closing the guild and requiring everyone rejoin.
 *
 * The above disclaimer is simply there if your wondering why some of
 * the functions rely on hit & miss routines.
 *
 *    --= Lucius Kane
 */
#pragma save_binary
#pragma strict_types

inherit "/std/room";
inherit "/d/Cirath/athas/gladiator/cmd/help_powers";
inherit "/d/Cirath/athas/gladiator/cmd/punish";
inherit "/d/Cirath/athas/gladiator/cmd/lesser";
inherit "/d/Cirath/athas/gladiator/cmd/brutus";
inherit "/d/Cirath/athas/gladiator/cmd/logs";
inherit "/d/Cirath/std/Cirath_magic_room_std";

#include "defs.h"
#include <std.h>
#include <composite.h>

private object cilops;
private object board;

public int
query_prevent_snoop() { return 1; }

public void
reset_room()
{
    CLONE(cilops, GLAD_NPC + "cilops");
    CLONE(board, GLAD_ROOM + "counbord");
}

public int
create_room()
{
    setuid(); seteuid(getuid());

    set_short("overseer sanctum");
    set_long("This stone chamber is cold and hard, like the ones who "
      +"use it: The Overseers of the Gladiators. "
      +"Shelves with records line one wall, while near "
      +"another is the nest of a gigantic insect, but otherwise "
      +"there is little adornment.\n");

    add_prop(ROOM_I_INSIDE, 1);

    add_item(({ "shelf", "shelves", "records", "record" }),
      "There are records on the comings and goings of the "+
      "Gladiators of Athas.\n");
    add_item("nest", "It is made of discarded refuse found in the "+
      "guild, including broken weapons, discarded betting chits, and "+
      "even the occasional skeleton.\n");
    add_item(({ "hexagon"}), "Its solidly built and rather ugly "+
      "but serves its purpose well.\n");
    add_item(({"scratch", "scratches"}), "They seem to spell out the "+
      "words 'help powers'. What could it mean?\n");

    add_exit(GLAD_ROOM+"counrcpt", "west", 0, 1);

    LOAD_ERR("/d/Cirath/athas/gladiator/npc/brutus");
    reset_room();
}

void
init()
{
    int pos = POSITION(this_player());

    ::init();

    if(pos == POS_NONE)
    {
        return;
    }

    /* Only Overseers get these actions. */
    add_action(_cmd_help_powers, "help");
    add_action(_cmd_punish, "punish");
    add_action(_cmd_brutus, "brutus");
    add_action(_cmd_logs, "logs");

    if(pos != POS_HIGH && pos != POS_WIZ)
    {
        return;
    }

    /* Only the High Overseers get these actions. */
    add_action(_cmd_lesser, "lesser");
}
