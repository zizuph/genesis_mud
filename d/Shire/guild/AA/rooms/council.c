/*  The AA council room
 *
 *  Modification log:
 *
 *     2008.06.17, Toby: Allowed for wizards to enter.
 */

#pragma save_binary
#pragma strict_types

#include <macros.h>
#include <stdproperties.h>
#include <std.h>
#include "../guild.h"

inherit SHIRE_ROOM;

#define BOARD_NAME  (AA_DIR+"boards/aa_board_council")
#define JOIN_LOG    (AA_DIR + "log/join_log")

void create_room()
{
    object board;

    set_short("Council room of Army of Angmar");
    set_long("This is the council room of Army of Angmar. Here, council " +
        "members , together with Captain and Lieutenants, can discuss " +
        "business about the Army in privacy. There is an exit east " +
        "to a private post office, west to the Council library, and " +
        "south to the guuild. A sign hangs on the wall.\n");

    add_item("sign", "It has some writing on it. Maybe you should read it.\n");
    add_cmd_item("sign", "read", "@@read_sign@@");

    add_exit(AA_DIR+"rooms/c_post","east");
    add_exit(AA_DIR+"library/council/c_library","west");
    add_exit(AA_DIR+"rooms/vote","south");

    add_prop(ROOM_I_INSIDE,1);  /* This is a real room */

    FIXEUID;
    board = clone_object("/d/Shire/std/board");
    board->set_board_name(BOARD_NAME);
    board->set_remove_str("You are not able to delete any messages.\n");
    board->set_num_notes(50);
    board->set_reader(VBFC_ME("check"));
    board->set_writer(VBFC_ME("check"));
    board->set_remove(VBFC_ME("check"));
    board->move(TO);
}

int check()
{
    /*** Council+Cap+Lieut+Shire wiz allowed ***/
    string name = TP->query_name();
//    if(name == "Milan") return 0;
//    if(name == "Novo") return 0;
    if(AA_RANKS_OBJ->lieut_cap(name)) return 0;  /* Lieutenant or Captain */
    if(AA_COUNCIL_OBJ->is_council(name)) return 0;
    if(SECURITY->query_wiz_dom(name) == "Shire") return 0;
    if(SECURITY->query_wiz_dom(name) == "Gondor") return 0;
    return 1;
}

void enter_inv(object ob, object from)
{
    ::enter_inv(ob,from);
    if(!living(ob)) return;
    set_this_player(ob);
    if(check())
    {
        if (this_player()->query_wiz_level())
        {
            write("As a wizard you can remain in this room even though "+
                  "you are not on the Army of Angmar council.\n");
            return;
        }
        write("You are not allowed in Angmar's Army council room! Begone!!!\n");
        ob->move(from);
        return;
    }
    write("Welcome in Angmar's Army council room!\n"+
        "May your decisions always benefit the Army.\n");
}

int query_prevent_snoop(){ return 1; }

string
read_sign()
{
    seteuid(getuid());
    write("\n----------------------------------------------------------------" +
        "---------------\n");
    write("                  Recent Enlistments and Leavings of the Army");
    write("\n--------------------------------------------------------------" +
        "-----------------\n\n");

    tail("/d/Shire/guild/AA/log/join_log");

    write("--------------------------------------------------------" +
            "-----------------------\n\n");
    return "";
}
