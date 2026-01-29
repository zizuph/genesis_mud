/*
 * /d/Shire/guild/AA/rooms/forge.c
 *
 * AA forge. Forge problems were with a base file
 * which was fixed by Zhar around September 2021
 *
 * Re-opened 11/6/2021 - Varian
 *
 */


#pragma save_binary
#pragma strict_types

#include "../guild.h"

inherit SHIRE_ROOM;

static object aruzagar;

void
reset_room()
{
//  object ob;
//
//  seteuid(getuid());
//
//  if(!aruzagar)
//  {
//    ob = clone_object(AA_DIR+"npc/blacksmith");
//    ob->move(this_object());
//  }

  if(aruzagar)
  {
    if(present(aruzagar,TO)) 
        return;

    aruzagar->command("oops");
    aruzagar->command("say I need more supplies ...!");
    aruzagar->command("ponder how to get more supplies ...");
    return;
  }
  
  aruzagar = clone_object(AA_DIR+"npc/blacksmith");
  aruzagar->arm_me();
  aruzagar->move_living("M",TO);
  aruzagar->command("emote runs back in with more supplies.");
  aruzagar->command("sigh relieved");
  aruzagar->command("say That will not happen again.");
} 


void
create_room()
{
    set_short("mountain clearing");
    set_long("This is a wide clearing in the middle of the mountains. " +
        "Trees and other vegetation has been cleared away, down to " +
        "rocks and gravel. A large smithy has been built here with a " +
        "forge set in the center of it. A metal sign hangs on a wall.\n");

    add_item("mountains",
        "Mountains look somehow dark and ominous. Maybe there is danger " +
        "brooding there.\n");
    add_item(({"smithy", "workshop"}),
        "The smithy is made of stone blocks and is square shaped. It " +
        "is large and set in the center of the clearing. A large forge " +
        "is set in the center.\n");
    add_item(({"stone", "stone blocks"}),
        "They are hewn from the nearby mountain. They are covered with " +
        "soot from the nearby forge and used to make the workshop, " +
        "and surround the forge.\n");
    add_item(({"forge"}),
        "It is a large furnace used to heat metals. Stone blocks " +
        "surround the forge. An anvil, tools, and a pair of bellows " +
        "are set next to the forge.\n");
    add_item(({"anvil"}),
        "It is a massive block of metal set next to the forge. The " +
        "anvil is rectangular shaped with a flattened top. It is " +
        "flattened and used to work metals.\n");
    add_item(({"bellows", "pair of bellows"}),
        "The pair of bellows is a device used to blow a strong blast " +
        "of air into the forge. It looks well used.\n");
    add_item(({"tools", "forging tools"}),
        "They are items used by the blacksmuith to forge armours, " +
        "weapons, and other things for the Army. They sit next the anvil.\n");
    add_item(({"ceiling"}),
        "The ceiling is made of stone and is peaked. Soot lines the " +
        "ceiling.\n");
    add_item(({"walls"}),
        "The walls are constructed of stone blocks and are covered " +
        "with soot.\n");
    add_item(({"floor", "ground"}),
        "The ground is nothing but trampkled earth. Bits and scraps " +
        "of metal are scattered acrossed the ground.\n");
    add_item(({"soot"}),
        "It is black and covers the walls and ceiling of the workshop.\n");

    add_item("sign", "It is made of metal and hangs on a wall.\n");
    add_cmd_item("sign", "read", "@@read_sign@@");

    add_exit(AA_DIR+"rooms/g3", "northwest");
    reset_room();
}

string read_sign()
{
    return "\n" +
        "\t+----------------------------------------+\n" +
        "\t|                                        |\n" +
        "\t|  These are the commands available:     |\n" +
        "\t|                                        |\n" +
        "\t|  repair <armour>                       |\n" +
        "\t|    This will repair worn down armours  |\n" +
        "\t|                                        |\n" +
        "\t|  sharpen <weapon>                      |\n" +
        "\t|    This will sharpen dull weapons      |\n" +
        "\t|                                        |\n" +
        "\t|  polish <weapon>                       |\n" +
        "\t|    This will repair corroded weapons   |\n" +
        "\t|                                        |\n" +
        "\t|                                        |\n" +
        "\t|  Broken items cannot be fixed here.    |\n" +
        "\t|                                        |\n" +
        "\t+----------------------------------------+\n\n";
}

