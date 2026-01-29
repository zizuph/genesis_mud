/*
 * Basic indoor room of Green Oaks
 * By Finwe, August 2004
 */

#pragma strict_types

#include "defs.h"
#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>

inherit INDOORS_BASE;

int test_tour(object player);

void
create_indoor_room()
{
    object board;

    add_prop(ROOM_S_MAP_FILE, "faerie_map.txt");
    set_short("Entrance of the " + ACADEMY_NAME);
    set_long("This is the " + short() + ". Elves from all over " +
        "come here to discuss what they know and have learned to those " +
        "seeking knowledge. The building is the center of the " +
        ACADEMY_NAME + " with several archways leading out to other " +
        "buildings. Several boards are scattered around the area. One " +
        "board is set in the center of the room. Public notices " +
        "and other documents of interest are posted on it for everyone " +
        "to read and comment on. On the shelf are some scrolls to read.\n");

    set_add_dome();
// setup board
    if (!objectp( board) )
    {
        board = clone_object("/std/board");
        board->set_num_notes(30);
        board->set_board_name(BOARD_DIR);
        board->move(this_object());
        board->set_long("This is the public discussion board of the " +
        ACADEMY_NAME + " of Green Oaks. It is tall and set in the " +
            "center of the room. You may post notes of interest or leave " +
            "comments on it. Below are instructions on how to use it.\n\n");
        board->add_prop(OBJ_M_NO_GET, "It's firmly attached to the floor.\n");
    }
    add_item(({"shelf"}),
        "The shelf is against a wall and made of wood. Sitting on the " +
        "shelf are some scrolls, which can be read.\n");
    add_item(({"scrolls"}),
        "They are large and sit on the shelf. There is a scroll of Green Oaks and another of Faerie.\n");
    add_item(({"scroll of green oaks", "green oaks"}),
        "It is large and set on the shelf. It looks like you could read it.\n");
    add_cmd_item(({"scroll of green oaks", "green oaks"}), "read", "@@read_green_oaks@@");
    add_item(({"scroll of faerie", "faerie"}),
        "It is large and set on the shelf. It looks like you could read it.\n");
    add_cmd_item(({"scroll of faerie", "faerie"}), "read", "@@read_faerie@@");

    add_item(({"buildings"}),
        "You can't examine any buildings since you're indoors.\n");
    add_item(({"building"}),
        "This is the inside of the " + short() + ".\n");
    add_item(({"notices", "documents"}),
        "These are comments left on boards for everyone to read.\n"); 

    set_add_arch("There are several of them, which lead outdoors and " +
        "to other buildings.");

    add_exit(GO_DIR + "road11", "north");
    add_exit(GO_DIR + "ac_ags", "south");
    add_exit(GO_DIR + "ac_common", "west");
    add_exit(GO_DIR + "ac_agn", "northwest");

}

void reset_room()
{
}

void
init()
{
    ::init();
    test_tour(TP);
}

void
tour_done(object player)
{
    player->catch_msg("\nThis is the entrance of the Academy. Feel free " +
        "to explore here and see what you can learn. When you are " +
        "finished, return and report to the Chief Delegate.\n");
}

void
test_tour(object player)
{
     object  note;

     if (!objectp(note = present("faerie_tour_note", TP)))
        return;

    if ((note->query_tour_no() != BOARD_TOUR_NUM) || (note->query_tour_done()))
    return;

    note->set_tour_done();

    set_alarm(2.0, 0.0, &tour_done(TP));
}

string read_green_oaks()
{
    return "You take the scroll from the shelf and unroll it. You read " +
        "the following:\n\n" + 
"    o                                                                    o\n" +
"   |+|                                                                  |+|\n" +
"   |+|                                                                  |+|\n" +
" |+++++|                                                              |+++++|\n" +
"|-------|============================================================|-------|\n" +
"|/ / / /|                                                            |/ / / /|\n" +
"| / / / |  This is a map of our fair city, Green Oaks. It has been   | / / / |\n" +
"|/ / / /|  commissioned by Menerial, Chief Delegate of Green Oaks.   |/ / / /|\n" +
"|/ / / /|                                                            |/ / / /|\n" +
"| / / / |  Istdhol, Master Cartographer of Green Oaks                | / / / |\n" +
"| / / / |                                                            | / / / |\n" +
"|/ / / /|                    G R E E N   O A K S                     |/ / / /|\n" +
"| / / / |                   ---------------------                    | / / / |\n" +
"|/ / / /|              or - or - or - or - or - or - or              |/ / / /|\n" +
"| / / / |      Road to  |    |    |    |    |    |    |     To       | / / / |\n" +
"|/ / / /|       Faerie or - or - or - or - or - or - or  Trade Road  |/ / / /|\n" +
"| / / / |            \\  |    |    |    |    |    |      /            | / / / |\n" +
"|/ / / /|              rd - or - rd - rd - rd - or   rd              |/ / / /|\n" +
"| / / / |               |    | / |    |     | \\ |  /                 | / / / |\n" +
"|/ / / /|      house - rd - rd   sh - bk   po   rd                   |/ / / /|\n" +
"| / / / |               |                     /                      | / / / |\n" +
"|/ / / /|      winery  gd - gd - gd - rd - rd - herbalist            |/ / / /|\n" +
"| / / / |          | /  | \\  | /  |         |                        | / / / |\n" +
"|/ / / /| house - rd   gd - FT - gd   ag   rd                        |/ / / /|\n" +
"| / / / |          |    | /  | \\  |      \\  | \\                      | / / / |\n" +
"|/ / / /|         rd   gd - gd   gd   cb - bd  rd - Portal from      |/ / / /|\n" +
"| / / / |          |  /      |      \\       | \\      Silverdell      | / / / |\n" +
"|/ / / /|         rd - ls   of   rd - rd   ag  rd                    |/ / / /|\n" +
"| / / / |             \\         /  |          /                      | / / / |\n" +
"|/ / / /|              rd - rd   pb   rd - rd                        |/ / / /|\n" +
"| / / / |            /    \\     /   /                                | / / / |\n" +
"|/ / / /|       house       rd - rd                                  |/ / / /|\n" +
"| / / / |                         |                                  | / / / |\n" +
"|/ / / /|                     Wild Elves                             |/ / / /|\n" +
"| / / / |                                                            | / / / |\n" +
"|/ / / /|      ag - adventurer guilds  po - post office              |/ / / /|\n" +
"|/ / / /|      bd - board              of - office                   |/ / / /|\n" +
"| / / / |      bk - bank               or - orchard                  | / / / |\n" +
"|/ / / /|      cb - common board       pb - pub                      |/ / / /|\n" +
"| / / / |      FT - fountain           rd - road                     | / / / |\n" +
"|/ / / /|      gd - garden             sh - shop                     |/ / / /|\n" +
"| / / / |      ls - leather shop                                     | / / / |\n" +
"|/ / / /|                                                            |/ / / /|\n" +
"|-------|============================================================|-------|\n" +
" |+++++|                                                              |+++++|\n" +
"   |+|                                                                  |+|\n" +
"   |+|                                                                  |+|\n" +
"    o                                                                    o\n\n";
}

string read_faerie()
{
    return "You take the scroll from the shelf and unroll it. You read " +
        "the following:\n\n" + 
"    o                                                                    o\n" +
"   |+|                                                                  |+|\n" +
"   |+|                                                                  |+|\n" +
" |+++++|                                                              |+++++|\n" +
"|-------|============================================================|-------|\n" +
"| / / / |                                                            | / / / |\n" +
"|/ / / /|                       F A E R I E                          |/ / / /|\n" +
"| / / / |                      -------------                         | / / / |\n" +
"|/ / / /|                                                            |/ / / /|\n" +
"| / / / |  Below is a general map of our surrounding areas. I        | / / / |\n" +
"|/ / / /|  mapped it during my countless patrols and travels.        |/ / / /|\n" +
"| / / / |                                                            | / / / |\n" +
"|/ / / /|  Istdhol, Master Cartographer of Green Oaks                |/ / / /|\n" +
"| / / / |                                                            | / / / |\n" +
"|/ / / /|                                                            |/ / / /|\n" +
"| / / / |                                    Pier                    | / / / |\n" +
"|/ / / /|                                      |                     |/ / / /|\n" +
"| / / / |                                    road                    | / / / |\n" +
"|/ / / /|                                      |                     |/ / / /|\n" +
"| / / / |                                    road                    | / / / |\n" +
"|/ / / /|                                   /                        |/ / / /|\n" +
"| / / / |                               road                         | / / / |\n" +
"|/ / / /|                     To          |                          |/ / / /|\n" +
"| / / / |                    Faerie     road - clearing              | / / / |\n" +
"|/ / / /|               mt /              |                          |/ / / /|\n" +
"| / / / |              road             road                         | / / / |\n" +
"|/ / / /|          mt /                /    \\                        |/ / / /|\n" +
"| / / / |         road            Cairn      road - Graveyard        | / / / |\n" +
"|/ / / /|        /                             |                     |/ / / /|\n" +
"| / / / |   mt road                          road                    | / / / |\n" +
"|/ / / /|      |                                 \\                   |/ / / /|\n" +
"| / / / |   mt road                               road               | / / / |\n" +
"|/ / / /|      |                                    |                |/ / / /|\n" +
"| / / / |   mt road                               road               | / / / |\n" +
"|/ / / /|         \\  mt                          /                   |/ / / /|\n" +
"| / / / |           road              Start road                     | / / / |\n" +
"|/ / / /|                \\  mt           | /                         |/ / / /|\n" +
"| / / / |                  road        road                          | / / / |\n" +
"|/ / / /|                      \\      /                              |/ / / /|\n" +
"| / / / |                        Green                               | / / / |\n" +
"|/ / / /|                        Oaks                                |/ / / /|\n" +
"| / / / |                          |                                 | / / / |\n" +
"|/ / / /|                        Wild                                |/ / / /|\n" +
"| / / / |                        Elves                               | / / / |\n" +
"|/ / / /|                                                            |/ / / /|\n" +
"|-------|============================================================|-------|\n" +
" |+++++|                                                              |+++++|\n" +
"   |+|                                                                  |+|\n" +
"   |+|                                                                  |+|\n" +
"    o                                                                    o\n\n";


}
