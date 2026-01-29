/*********************************************************************
 * - smoke.c                                                       - *
 * - This is a smoking room for all in the Gentleman's Club        - *
 * - It is to provide smoking materials and an area to smoke in.   - *
 * - There are two stages to this room.                            - *
 * - Stage I: Is where a sugestion box is placed in room, for      - *
 * - members to suggest their smoking materials.                   - *
 * - Stage II: Is where implementation of stage I is complete.     - *
 * - This room in curently in Stage I                              - *
 * - Created by Damaris and Valen 12/2001                          - *
 *********************************************************************/
#pragma strict_types
#include <macros.h> /* For the Q macros in messages.. */
#include <stdproperties.h> /* for room props */
#include <money.h>
#include "/d/Raumdor/defs.h"
#include "../guild.h"
inherit CLUB;
inherit "/d/Raumdor/lib/tavern";
inherit "/lib/trade.c";
#include "fireplace.c"
#include "seating2.c"

#define SMOKE ("/d/Raumdor/guilds/gc/")
#define NUM sizeof(MONEY_TYPES)
string
menustuff(void)
{
    action_tavern_menu("menu");
    return "";
}

string
query_notice()
{
    return
        "                          Notice\n\n"+
        "               Gentleman Club Members Only\n\n"+
        "    Due to many different types of gentlemen that exist\n"+
        "    with different styles and different tastes. The club\n"+
        "    wishes to give you a chance to express what you would\n"+
        "    like for us to keep in stock for your smoking pleasure.\n"+
        "    We will supply the following for your smoking pleasure.\n\n"+
        "    Cigars, pipes, pipe tobacco, also containers for smoking\n"+
        "    materials.\n\n"+
        "    We need the following from you to help us serve your smoking\n"+
        "    needs better.\n"+
        "    - The name of the smoking material\n"+
        "    - The description.\n"+
        "    - The smoking messages if indicated.\n\n"+
        "    We will then sort through these suggestions and if we agree\n"+
        "    on your suggestion, then we will do our best to import it\n"+
        "    for you. If your selection is chosen we will place your name\n"+
        "    upon a lovely plaque and placed over the fireplace for all to\n"+
        "    know of your contribution.\n\n"+
        "    Please use the suggestion box, and you may submit as often as\n"+
        "    you like.\n"; 
}
string
query_plaque()
{
    return
           "               +========================================+\n"+
           "               +            Gentleman's Club            +\n"+
           "               +          Special Appreciation          +\n"+
           "               +         to the following members       +\n"+
           "               +========================================+\n"+
           "               +                                        +\n"+
           "               +      Pyriel            Mersereau       +\n"+
           "               +                                        +\n"+
           "               +========================================+\n"; 
}

public void
create_guild_room()
{
    object board;

    set_short("A smoking room");
    set_long("This is a rather substantial room. The walls are "+
        "decorated with fine tapestries. Refined rugs have been "+
        "placed on the hardwood floor as well. It is quite obvious "+
        "by the tables and chairs that this is a place where "+
        "gentlemen gather to have discussions and smoke their "+
        "various pleasures. There is a menu posted just below a "+
        "notice on the north wall. Also a fireplace adorns the corner with "+
        "a moderate fire dancing and there is a notice that has "+
        "been posted above the mantle.\n");
    add_item(({"room", "smoking room", "area"}), query_long);
    add_item(({"notice"}), query_notice);
    add_cmd_item("notice","read", query_notice);
    add_item(({"plaque"}), query_plaque);
    add_cmd_item("plaque","read", query_plaque);
    add_item("menu", menustuff);
    add_item(({"cushion","cushions"}), seat_desc);
    add_my_desc(seat_desc, this_object());
    add_item(({"lantern", "lanterns", "glass lanterns"}),
        "There are a few glass lanterns attched firmly to the walls.\n");
    add_item(({"wall", "walls"}),
        "The walls are made with wood panels and give the rooms a "+
        "bit of a closed in feeling. The walls have been decorated "+
        "with glass lanterns and fine tapestries.\n");
    add_item(({"floor", "flooring", "ground"}),
        "The flooring is made from a darkened hardwood and a few "+
        "rugs have been placed upon it.\n");
    add_item(({"rug", "rugs", "refined rug", "refined rugs"}),
        "The rugs placed here are made from the finest quality and "+
        "are interesting enough in very good shape.\n");
    add_item(({"ceiling", "roof"}),
        "The ceiling is dark just as the walls, but there is a large "+
        "symbol painted in gold.\n");
    add_item(({"symbol", "gold symbol"}),
        "The symbol is definately painted gold and is recognizable "+
        "as GC.\n");
    add_item(({"fireplace", "fire"}),
        "There is a large fireplace in the corner. A moderate fire dances in " +
        "the fireplace and lights the room. A notice is posted " +
        "above the mantle.\n");
    add_item(({"candles", "scented candles", "candle", "scented candle"}),
        "There are scented candles resting on some small tables.\n");
    add_item(({"table", "tables", "small table", "small tables"}),
        "There are small tables scattered in various places against the "+
        "walls and around a few of the chairs.\n");
    add_item(({"north", "south", "east", "west", "northwest", "northeast",
        "southwest"}),
        "There is a wall in that direction.\n");
    add_item(({"southeast"}),
        "There is a doorway in that direction.\n");
    add_item(({"north wall", "northern wall"}),
        "On the north wall there is a notice and below the notice "+
        "is a menu and a plaque.\n");
      
    set_tavern_name("Smoking wares");
    add_tavern_wares(({SMOKE + "cigar1",
                       SMOKE + "cigar2",
                       SMOKE + "cigar3",
                       SMOKE + "cigar4",
                       SMOKE + "cigar5",
                       SMOKE + "cigar6",
                       SMOKE + "humidor",
                      }));
    add_exit("join", "southeast");
    set_no_exit_msg(({"north", "south", "east", "west", "northeast",
        "northwest", "southwest"}),
        "You walked into a wall!\n"+
        "Ouch! That's gotta hurt!\n");

    setuid();seteuid(getuid());
    board = clone_object(GUILD_DIR + "sboard");
    board->move(this_object(), 1);
    
    config_default_trade();
}

public void
init()
{
    ::init();
    init_seat();
    init_fire();
    init_tavern();
}
