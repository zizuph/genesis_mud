/* 	Spirit Circle of Psuchae Council Chambers

    coder(s):   Jaacar

    history:    24. 7.03    room coded                      Jaacar

*/

/* Navarre: December 13th 2006.
 * Removed snoop block.
 * Removed the scroll that gave access to read log of entry.
 * This was removed by request from the AoB.
 */

#pragma save_binary

inherit "/std/room";
#include <macros.h>
#include <std.h>
#include <stdproperties.h>
#include <language.h>
#include "defs.h"
#include COUNCIL_HEADER

// #define TEMPLE_ENTRY_LOG "/d/Calia/log/spirit_circle/spirit_temple_entry_log"

void
load_board()
{
    clone_object(COUNCIL_OBJECTS+"council_board")->move(THIS);
}

void
load_book()
{
    clone_object(COUNCIL_OBJECTS+"log_book")->move(THIS);
}

void 
create_room()
{
    set_short("The Spirit Circle Councilroom");
    set_long("You are standing in the council chambers of the "+
        "Spirit Circle of Psuchae. This chamber is lit "+
        "by glowing rocks set into the walls. There is a golden "+
        "banner hanging on the western wall, and a silver banner "+
        "on the eastern wall. On the "+
        "northern wall hangs a copper banner and a bronze banner. In "+
        "one corner you see a small table.\n");

    add_item(({"rocks","glowing rocks"}),"The rocks are all different "+
        "sizes, and seem to be magical in nature.  They must be a gift "+
        "from the Elementals to light this chamber.\n");
    add_item(({"table","small table"}),"In the corner of the room "+
        "there is a small wooden table.  On top of the table is "+
            "a brown book which the council records its actions in.\n");
//    add_item("scroll","There is writing on the scroll that you can read.\n");

    add_item("banner","Which banner do you wish to examine? The copper banner, "+
        "bronze banner, the silver banner or the golden banner?\n");

    add_item("copper banner","On the copper banner you see:\n"+
             "liberator    - see who is the current Liberator of Souls (if any).\n"+
             "cultivator   - see who is the current Cultivator of Life (if any).\n"+
             "beacon       - see who is the current Beacon of Spirits (if any).\n"+
             "missionary   - see who is the current Missionary of the Spirit\n"+
             "               Circle (if any).\n"+
             "emissary     - see who is the current Emissary (if any).\n"+
             "luminary     - see who is the current Luminary of the Spirit\n"+
             "               Circle (if any).\n"+
             "conservators - list the current Conservators of the Armaments (if\n"+
             "               any).\n"+
             "illuminati   - see who is the current Illuminati (if any).\n"+
             "intercessor  - see who is the current Intercessor of the\n"+
             "               Spirit Circle (if any).\n");

    add_item("bronze banner","On the bronze banner you see:\n"+
             "setliberator <player>   - set <player> as Liberator of Souls.\n"+
             "setcultivator <player>  - set <player> as Cultivator of Life.\n"+
             "setbeacon <player>      - set <player> as Beacon of Spirits.\n"+
             "setmissionary <player>  - set <player> as Missionary of the\n"+
             "                          Spirit Circle.\n"+
             "setemissary <player>    - set <player> as Emmisary.\n"+
             "setluminary <player>    - set <player> as Luminary of the Spirit\n"+
             "                          Circle.\n"+
             "addconservator <player> - add <player> as a Conservator of the\n"+
             "                          Armaments.\n"+
             "setilluminati <player>  - set <player> as Illuminati.\n"+
             "setintercessor <player> - set <player> as Intercessor of the\n"+
             "                          Spirit Circle.\n"+
             "remliberator <player>   - remove <player> as Liberator of Souls.\n"+
             "remcultivator <player>  - remove <player> as Cultivator of Life.\n"+
             "rembeacon <player>      - remove <player> as Beacon of Spirits.\n"+
             "remmissionary <player>  - remove <player> as Missionary of the\n"+
             "                          Spirit Circle.\n"+
             "rememissary <player>    - remove <player> as Emmisary.\n"+
             "remluminary <player>    - remove <player> as Luminary of the Spirit\n"+
             "                          Circle.\n"+
             "remconservator <player> - remove <player> as a Conservator of the\n"+
             "                          Armaments.\n"+
             "remilluminati <player>  - remove <player> as Illuminati.\n"+
             "remintercessor <player> - remove <player> as Intercessor of the\n"+
             "                          Spirit Circle.\n");

    add_item("silver banner","On the silver banner you see:\n"+
             "council             - list council members.\n" +
             "mentors             - list all mentor/apprentice pairs.\n"+
             "apprentices         - list all Spirit Circle Apprentices.\n"+
             "masters             - list all Spirit Circle Master Members.\n"+
             "elders              - list all Spirit Circle Elder Members.\n"+
             "archonr             - see who is the current Archon of Revelation (if any).\n"+
             "archond             - see who is the current Archon of Deliverance (if any).\n"+
             "archona             - see who is the current Archon of Apotheosis  (if any).\n"+
             "speakers            - list all Spirit Circle approved Speakers.\n"+
             "templebanned        - list all who are banned from the Temple.\n"+
             "call (<room>)       - call all Spirit Circle members in the realms\n"+
             "                      to <room>. (NOTE: If no room is given, they\n"+
             "                      will be called to the Chapel.\n"+
             "\n");
    
    add_item("golden banner","On the golden banner you see:\n"+
             "trainban <player>     - ban <player> from training.\n" +
             "spellban <player>     - ban <player> from using gifts.\n"+
             "restrict <player>     - restrict <player> to the Temple.\n"+
             "expel <player>        - expel <player> from the Spirit Circle.\n" +
             "rempunish <player>    - remove current punishment from <player>.\n" +
             "addcouncil <player>   - add <player> to the Spirit Circle Council.\n" +
             "remcouncil <player>   - remove <player> from the Spirit Circle Council.\n"+
             "apromote <player>     - promote <player> to Master ranking from\n"+
             "                        Apprentice ranking.\n"+
             "mpromote <player>     - promote <player> to Elder ranking from\n"+
             "                        Master ranking.\n"+
             "mdemote <player>      - demote <player> to Apprentice ranking from\n"+
             "                        Master ranking.\n"+
             "edemote <player>      - demote <player> to Master ranking from\n"+
             "                        Elder ranking.\n"+
             "setarchonr <player>   - set <player> to Archon of Revelation.\n"+
             "setarchond <player>   - set <player> to Archon of Deliverance.\n"+
             "setarchona <player>   - set <player> to Archon of Apotheosis.\n"+
             "remarchonr <player>   - remove <player> as Archon of Revelation.\n"+
             "remarchond <player>   - remove <player> as Archon of Deliverance.\n"+
             "remarchona <player>   - remove <player> as Archon of Apotheosis.\n"+
             "remmentor <player>    - remove apprentice from <player>.\n"+
             "addspeaker <player>   - add <player> to approved Speakers.\n"+
             "remspeaker <player>   - remove <player> from approved Speakers.\n"+
             "addbanned <player>    - add <player> to the temple banned list.\n"+
             "rembanned <player>    - remove <player> from the temple banned list.\n"+
             "\n");

    IN;
    add_prop(ROOM_M_NO_ATTACK,"You cannot attack in here, you are in a "+
        "sacred place!\n");
    add_prop(ROOM_M_NO_MAGIC_ATTACK,"You cannot attack in here, you are in "+
        "a sacred place!\n");
    add_prop(ROOM_I_LIGHT, 1);

    add_exit(SPIRIT_TEMPLE+"chapel","south",0,1);

    load_book();
    load_board();   
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
        ob->query_wiz_level()) &&
        (SECURITY->query_wiz_rank(ob->query_real_name()) < WIZ_ARCH))
    {
        ob->move(from);
        ob->catch_msg("You are not permitted into the Spirit Circle Council " +
            "chambers.\n");
        return;
    }

}

varargs int
message_spirits(string str)
{
    string area;
    int i;
    object *members;

    if (!str)
        area = "Chapel";
    else
        area = capitalize(str);

    members = filter(users(), &->is_spirit_member());

    if (!sizeof(members))
    {
        NF("There are no members to notify.\n");
        return 0;
    }
    
    map(members, &->catch_msg("\n\nThe voice of Psuchae echoes through your "+
        "mind saying:\nYour presence has been requested in the "+area+".\n\n"));
   
    return 1;
}

int
see_council(string str)
{
    return COUNCIL_CODE->see_council(str);
}

int
see_speakers(string str)
{
    return COUNCIL_CODE->see_speakers(str);
}

int
see_temple_banned(string str)
{
    return COUNCIL_CODE->see_temple_banned(str);
}

int
see_mentors(string str)
{
    return COUNCIL_CODE->see_mentors(str);
}

int
see_spirit_apprentices(string str)
{
    return COUNCIL_CODE->see_spirit_apprentices(str);
}

int
see_spirit_masters(string str)
{
    return COUNCIL_CODE->see_spirit_masters(str);
}

int
see_spirit_elders(string str)
{
    return COUNCIL_CODE->see_spirit_elders(str);
}

int
see_liberator(string str)
{
    return COUNCIL_CODE->see_liberator(str);
}

int
see_cultivator(string str)
{
    return COUNCIL_CODE->see_cultivator(str);
}

int
see_beacon(string str)
{
    return COUNCIL_CODE->see_beacon(str);
}

int
see_missionary(string str)
{
    return COUNCIL_CODE->see_missionary(str);
}

int
see_emissary(string str)
{
    return COUNCIL_CODE->see_emissary(str);
}

int
see_luminary(string str)
{
    return COUNCIL_CODE->see_luminary(str);
}

int
see_conservators(string str)
{
    return COUNCIL_CODE->see_conservators(str);
}

int
see_illuminati(string str)
{
    return COUNCIL_CODE->see_illuminati(str);
}

int
see_intercessor(string str)
{
    return COUNCIL_CODE->see_intercessor(str);
}

int
see_theurgist(string str)
{
    return COUNCIL_CODE->see_theurgist(str);
}

int
see_archon(string str)
{
    return COUNCIL_CODE->see_archon(str);
}

int
see_patriarch(string str)
{
    return COUNCIL_CODE->see_patriarch(str);
}

int
record_stop_spells(string str)
{
    return COUNCIL_CODE->record_stop_spells(str);
}

int
record_temple_restrict(string str)
{
    return COUNCIL_CODE->record_temple_restrict(str);
}

int
record_stop_train(string str)
{
    return COUNCIL_CODE->record_stop_train(str);
}

int
record_expel_player(string str)
{
    return COUNCIL_CODE->record_expel_player(str);
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
add_speaker(string str)
{
    return COUNCIL_CODE->add_speaker(str);
}

int
add_temple_banned(string str)
{
    return COUNCIL_CODE->add_temple_banned(str);
}

int
remove_council_member(string str)
{

    return COUNCIL_CODE->remove_council_member(str);
}

int
remove_speaker(string str)
{
    return COUNCIL_CODE->remove_speaker(str);
}
int
remove_temple_banned(string str)
{
    return COUNCIL_CODE->remove_temple_banned(str);
}

int
set_liberator(string str)
{
    return COUNCIL_CODE->set_liberator(str);
}

int
set_cultivator(string str)
{
    return COUNCIL_CODE->set_cultivator(str);
}

int
set_beacon(string str)
{
    return COUNCIL_CODE->set_beacon(str);
}

int
set_missionary(string str)
{
    return COUNCIL_CODE->set_missionary(str);
}

int
set_emissary(string str)
{
    return COUNCIL_CODE->set_emissary(str);
}

int
set_luminary(string str)
{
    return COUNCIL_CODE->set_luminary(str);
}

int
add_conservator(string str)
{
    return COUNCIL_CODE->add_conservator(str);
}

int
set_illuminati(string str)
{
    return COUNCIL_CODE->set_illuminati(str);
}

int
set_intercessor(string str)
{
    return COUNCIL_CODE->set_intercessor(str);
}

int
set_theurgist(string str)
{
    return COUNCIL_CODE->set_theurgist(str);
}

int
set_archon(string str)
{
    return COUNCIL_CODE->set_archon(str);
}

int
set_patriarch(string str)
{
    return COUNCIL_CODE->set_patriarch(str);
}

int
rem_liberator(string str)
{
    return COUNCIL_CODE->remove_liberator(str);
}

int
rem_cultivator(string str)
{
    return COUNCIL_CODE->remove_cultivator(str);
}

int
rem_beacon(string str)
{
    return COUNCIL_CODE->remove_beacon(str);
}

int
rem_missionary(string str)
{
    return COUNCIL_CODE->remove_missionary(str);
}

int
rem_emissary(string str)
{
    return COUNCIL_CODE->remove_emissary(str);
}

int
rem_luminary(string str)
{
    return COUNCIL_CODE->remove_luminary(str);
}

int
rem_conservator(string str)
{
    return COUNCIL_CODE->remove_conservator(str);
}

int
rem_illuminati(string str)
{
    return COUNCIL_CODE->remove_illuminati(str);
}

int
rem_intercessor(string str)
{
    return COUNCIL_CODE->remove_intercessor(str);
}

int
rem_theurgist(string str)
{
    return COUNCIL_CODE->remove_theurgist(str);
}

int
rem_archon(string str)
{
    return COUNCIL_CODE->remove_archon(str);
}

int
rem_patriarch(string str)
{
    return COUNCIL_CODE->remove_patriarch(str);
}

int
rem_mentor(string str)
{
    return COUNCIL_CODE->remove_mentor(str);
}

int
promote_apprentice(string str)
{
    return COUNCIL_CODE->promote_apprentice(str);
}

int
promote_master(string str)
{
    tell_room((SPIRIT_TEMPLE+"statue_chamber"),"A pile of rubble appears "+
        "on the ground. It begins to stir around on its own then suddenly "+
        "rises up and begins to form something. More chucks of rubble "+
        "crash together and there is a blinding flash of light, causing "+
        "you to look away. When you look back, there is a new statue!\n");
    return COUNCIL_CODE->promote_master(str);
}

int
demote_elder(string str)
{
    tell_room((SPIRIT_TEMPLE+"statue_chamber"),"One of the statues cracks, "+
        "then crumbles and finally falls apart making just a pile of rubble "+
        "on the ground. The rubble quickly disappears.\n");
    return COUNCIL_CODE->demote_elder(str);
}

int
demote_master(string str)
{
    return COUNCIL_CODE->demote_master(str);
}

/*
int
read_scroll(string str)
{
    if (str != "scroll")
        return 0;

    seteuid(getuid());
    tail(TEMPLE_ENTRY_LOG);
    return 1;
}
*/

void 
init()
{
    ::init();
    add_action(see_spirit_apprentices,"apprentices");
    add_action(see_spirit_masters,"masters");
    add_action(see_spirit_elders,"elders");
    add_action(see_mentors, "mentors");
    add_action(see_council, "council");
    add_action(see_speakers, "speakers");
    add_action(see_temple_banned, "templebanned");

    add_action(see_theurgist,"archonr");
    add_action(see_archon,"archond");
    add_action(see_patriarch,"archona");

    add_action(see_liberator,"liberator");
    add_action(see_cultivator,"cultivator");
    add_action(see_beacon,"beacon");
    add_action(see_missionary,"missionary");
    add_action(see_emissary,"emissary");
    add_action(see_luminary,"luminary");
    add_action(see_conservators,"conservators");
    add_action(see_illuminati,"illuminati");
    add_action(see_intercessor,"intercessor");

    add_action(record_stop_train, "trainban");
    add_action(record_expel_player, "expel");
    add_action(record_stop_spells, "spellban");
    add_action(record_remove_punish, "rempunish");
    add_action(record_temple_restrict, "restrict");

    add_action(add_council_member, "addcouncil");
    add_action(remove_council_member, "remcouncil");
    
    add_action(add_speaker, "addspeaker");
    add_action(remove_speaker, "remspeaker");

    add_action(add_temple_banned, "addbanned");
    add_action(remove_temple_banned, "rembanned");
    
    add_action(promote_apprentice, "apromote");
    add_action(promote_master, "mpromote");
    
    add_action(demote_elder, "edemote");
    add_action(demote_master, "mdemote");

    add_action(set_liberator,"setliberator");
    add_action(set_cultivator,"setcultivator");
    add_action(set_beacon,"setbeacon");
    add_action(set_missionary,"setmissionary");
    add_action(set_emissary,"setemissary");
    add_action(set_luminary,"setluminary");
    add_action(add_conservator,"addconservator");
    add_action(set_illuminati,"setilluminati");
    add_action(set_intercessor,"setintercessor");
    
    add_action(set_theurgist,"setarchonr");
    add_action(set_archon,"setarchond");
    add_action(set_patriarch,"setarchona");
    
    add_action(rem_liberator,"remliberator");
    add_action(rem_cultivator,"remcultivator");
    add_action(rem_beacon,"rembeacon");
    add_action(rem_missionary,"remmissionary");
    add_action(rem_emissary,"rememissary");
    add_action(rem_luminary,"remluminary");
    add_action(rem_conservator,"remconservator");
    add_action(rem_illuminati,"remilluminati");
    add_action(rem_intercessor,"remintercessor");

    add_action(rem_theurgist,"remarchonr");
    add_action(rem_archon,"remarchond");
    add_action(rem_patriarch,"remarchona");
    add_action(rem_mentor,"remmentor");

    // add_action(read_scroll,"read");
    add_action(message_spirits,"call");
}
