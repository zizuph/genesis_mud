


#pragma save_binary

inherit "/std/room";
#include <macros.h>
#include <std.h>
#include <stdproperties.h>
#include <language.h>
#include "defs.h"
#include COUNCIL_HEADER

void
load_board()
{
    clone_object(WOR_OBJECTS+"council_board")->move(THIS);
}

void
load_book()
{
    clone_object(WOR_OBJECTS+"council_log_book")->move(THIS);
}

int
query_prevent_snoop()
{
    return 1;
}

void 
create_room()
{
    set_short("The Worshippers Councilroom.\n");
    set_long("You are standing in the council chambers of the "+
        "Elemental Worshippers of Calia.  This chamber is lit "+
        "by glowing rocks set into the walls.  There is a large "+
        "banner hanging on the western wall, and a scroll hanging "+
        "below it.  In one corner you see a small table.\n");

    add_item(({"rocks","glowing rocks"}),"The rocks are all different "+
        "sizes, and seem to be magical in nature.  They must be a gift "+
        "from the Elementals to light this chamber.\n");
    add_item(({"table","small table"}),"In the corner of the room "+
        "there is a small wooden table.  On top of the table is "+
            "a brown book which the council records its actions in.\n");
    add_item("scroll","There is writing on the scroll that you can read.\n");

    add_item("banner","On the banner you see:\n"+
            "council            - check council members.\n" +
            "leader             - check current leader.\n" +
            "addleader <player> - promote <player> to leader.\n"+
            "remleader <player> - remove <player> as leader.\n"+
            "trainban <player>  - ban <player> from training.\n" +
            "spellban <player>  - ban <player> from using spells.\n"+
            "expel <player>     - expel <player> from the Worshipper guild.\n" +
            "rempunish <player> - remove current punishment from <player>.\n" +
            "addmem <player>    - add <player> to the Worshipper Council.\n" + 
            "remmem <player>    - remove <player> from the Worshipper council.\n\n"+
            "To initiate a new Worshipper:\n"+
            "wjpray <player>    - This will allow <player> to join.\n"+
            "                     Once they have done this, they need only\n"+
            "                     'worship <diety>' to enter their service.\n\n");

    add_prop(ROOM_I_INSIDE, 1);
    add_prop(ROOM_I_LIGHT, 1);

    add_exit(WOR_SHRINE+"common","down",0,1);
   
    load_book();
    load_board();   

    seteuid(getuid());
    COUNCIL_CODE->load_me();
}


/*
 * Function: enter_inv
 * Description: block unwanted people from entering.
 */
void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);

    if (!living(ob)) return;

    if (!(COUNCIL_CODE->is_council_member(ob->query_name()) ||
        COUNCIL_CODE->is_calian_wiz(ob)) &&
        (SECURITY->query_wiz_rank(ob->query_real_name()) < WIZ_ARCH))
    {
        ob->move(from);
        ob->catch_msg("You're not coming into the Worshippers Council " +
            "chambers without special permission!\n");
        return;
    }

}

int
see_council(string str)
{
    return COUNCIL_CODE->see_council(str);
}

int
query_leader(string str)
{
    write(COUNCIL_CODE->query_leader(str));
    return 1;
}

int
see_pending_commands(string str)
{
    return COUNCIL_CODE->see_pending_commands(str);
}


int
cancel_pending_commands(string str)
{
    return COUNCIL_CODE->cancel_pending_commands(str);
}


int
record_stop_train(string str)
{
    return COUNCIL_CODE->record_stop_train(str);
}

int
record_spell_banned(string str)
{
    return COUNCIL_CODE->record_spell_banned(str);
}

int
record_expel_player(string str)
{
    return COUNCIL_CODE->record_expel_player(str);
}


int
record_discharge_player(string str)
{
    return COUNCIL_CODE->record_discharge_player(str);
}


int
record_remove_punish(string str)
{
    return COUNCIL_CODE->record_remove_punish(str);
}

int
add_council_member(string str)
{
    return COUNCIL_CODE->add_council_member(str);
}

int
add_leader(string str)
{
    return COUNCIL_CODE->add_leader(str);
}

int
remove_council_member(string str)
{

    return COUNCIL_CODE->remove_council_member(str);
}

int
remove_leader(string str)
{
    return COUNCIL_CODE->remove_leader(str);
}

int
read_scroll(string str)
{
    if (str != "scroll")
        return 0;

    seteuid(getuid());
    tail(CONLOG);
    return 1;
}

int
no_drop(string str)
{
    if (!str)
        return 0;
    write("You cannot drop things in this room.\n");
        return 1;
}
    
void 
init()

{
    ::init();
    add_action(add_leader,"addleader");
    add_action(query_leader,"leader");
    add_action(remove_leader,"remleader");
    add_action(see_council, "council");
    add_action(record_stop_train, "trainban");
    add_action(record_spell_banned, "spellban");
    add_action(record_expel_player, "expel");
    add_action(record_remove_punish, "rempunish");
    add_action(add_council_member, "addmem");
    add_action(remove_council_member, "remmem");
    add_action(read_scroll,"read");
    add_action(no_drop,"drop");
    add_action(no_drop,"put");
}
