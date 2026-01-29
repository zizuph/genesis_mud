/**********************************************************************
 * - Added the following:                                           - *
 * -   #include "/d/Krynn/solamn/vin/std/no_scry_room.c"            - *
 * -   add_prop(ROOM_M_NO_SCRY, query_no_scry);                     - *
 * -                                                                - *
 * - Modified by Damaris@Genesis 03/2005                            - *
 *                                                                  - *
 * - Modified by Arman 10/2018 to add battlefield map               - *
 **********************************************************************/
#include "/d/Krynn/common/defs.h"

#include <std.h>
#include <stdproperties.h>
#include <macros.h>
#include <ss_types.h>
#include <config.h>
#include "../../guild.h"

inherit IN_BASE;
inherit RECRUIT_BASE
inherit WARFARE_MAP;

#include "./std/no_scry_room.c"

static mapping positions = ([ ]);

object board;

void
load_board()
{
    board = clone_object(VOBJ + "warboard");
    board->move(TO);
}

void
reset_vin_room()
{
    if (!board)
    {
        load_board();
    }
}

void
create_vin_room()
{
    set_army("Knights");

    set_short("War room of Vingaard Keep");
    set_long("This room was obviously designed to hold the large "+
        "circular table which rests in the center of it. The table "+
        "is covered with a large map of Ansalon, and a war map covered " +
        "with miniature soldiers - probably where "+
        "plans are made for defending the lands against the "+
        "Dragonarmies. A banner hangs along one wall, and a sign "+
        "is placed on the wall beneath it." +
        " A poster has been hung on another wall concerning the " +
        "recruitment of new guards." +
        "\n");
    add_cmd_item("sign", "read", "@@sign_desc");
    add_item("banner", "@@banner_desc");
    add_item(({"table", "map"}), "Upon the table are two maps. A large " +
        "map of Ansalon, and a war map showing the current battlefields " +
        "across the land.\n");
    add_item(({"large map of ansalon", "large map", "map of ansalon"}), 
        "@@show_map");
    add_item(({"war map", "battlefields", "battlefield map"}), 
      "@@exa_knight_warmap");
    add_item(({"soldiers","miniature soldiers", "armies", "miniatures"}), 
      "Across the war map of Krynn miniature soldiers have been arrayed, " +
      "indicating the armies vying for control of these lands.\n");
    add_item("sign", "@@sign_desc");
    add_item(({"recruitment poster","recruit","recruit poster","poster"}),
        "@@read_recruit_sign@@");
    add_cmd_item(({"recruitment poster","recruit","recruit poster","poster"}),
        "read", "@@read_recruit_sign@@");
    add_prop(ROOM_M_NO_SCRY, query_no_scry);
    add_exit(VROOM + "east_hallway", "west");
    seteuid(getuid());

    load_board();
}

void
init()
{
    add_action("appoint", "appoint");
    add_action("remove", "remove");
    add_action("resign", "resign");
    /*add_action("check_positions", "list");*/

    init_recruit();
    ::init();
}

int
hook_allowed_to_recruit(object who)
{
    if (!who)
    {
        return 0;
    }
    return 1;
}


string
sign_desc()
{
    return "Commands available here: appoint, remove, resign.\n"+
        "Generals may be appointed by the Conclave or Grandmaster.\n"+
        "Commanders may be appointed by the Conclave, Grandmaster, or\n"+
        "   the General.\n"+
        "The Warden of the High Clerist's Tower may only be appointed\n"+
        "   by the High Clerist.\n"+
        "The Swordmaster may be appointed by the Conclave or Grandmaster,\n"+
        "   but should usually be appointed by the present Swordmaster\n"+
        "   only after he/she has been defeated in a duel of arms courteous\n"+
        "   by another Knight.\n\n"+
        "Syntax: 'appoint <knight> as <warden, general, swordmaster, "+
        "\n         east[ern] / south[ern] commander> for <reason>'\n";
}

string
banner_desc()
{
    int i;
    string str;

    positions = restore_map(APPOINT_FILE);

    str = " \n      Warden of the High Clerist's Tower - "+
        (positions[POSITIONS[0]] == 0 ? "None" : positions[POSITIONS[0]])+
        "\n         Commander of the Eastern Armies - "+
        (positions[POSITIONS[3]] == 0 ? "None" : positions[POSITIONS[3]])+
        "\n        Commander of the Southern Armies - "+
        (positions[POSITIONS[4]] == 0 ? "None" : positions[POSITIONS[4]])+
        "\n                   General of the Armies - "+
        (positions[POSITIONS[2]] == 0 ? "None" : positions[POSITIONS[2]])+
        "\n                 Swordmaster of Solamnia - "+
        (positions[POSITIONS[1]] == 0 ? "None" : positions[POSITIONS[1]])+
        "\n";
    return str+"\nYou may <appoint> Knights to positions here, "+
        "provided you have the authority to do so. For more info"+
        "rmation, read the sign.\n";
}


string
show_map()
{
    return read_file(VOBJ + "ansalon_map");
}

string
exa_knight_warmap()
{
    say(QCTNAME(TP)+ " examines the soldiers arrayed on the war " +
        "table with interest.\n");
    return "You look at the map on the war table, examining the " +
        "locations of the various armies vying for control of " +
        "Krynn...\n" + exa_warmap();
}

int
resign()
{
    int i;

    positions = restore_map(APPOINT_FILE);
    NF("You are not in a position you may resign from.\n");
    if (member_array(TP->query_name(), m_values(positions)) < 0)
	return 0;

    if (!TP->query_prop("_i_typed_resign"))
    {
	write("Resign from your position? Type again to confirm.\n");
	TP->add_prop("_i_typed_resign", 1);
	return 1;
    }

    TP->remove_prop("_i_typed_resign");
    for (i = 0; i < sizeof(POSITIONS); i++)
    {
	if (positions[POSITIONS[i]] == TP->query_name())
	{
	    positions[POSITIONS[i]] = 0;
	    TP->remove_position();
	    write("You resign from your station as "+POSITIONS[i]+".\n");
	    write_file(APPOINT_LOG, ctime(time())+", "+TP->query_name()+
                " resigned position of "+POSITIONS[i]+".\n");
	    save_map(positions, APPOINT_FILE);
	    return 1;
	}
    }

    write("Resignation failed.\n");
    return 1;
}

int
remove(string str)
{
    int i;

    if (member_array(TP->query_name(), GUILDMASTERS) >= 0 &&
        TP->query_knight_sublevel() != 11)
    {
	return 0;
    }

    positions = restore_map(APPOINT_FILE);
    for (i = 0; i < sizeof(POSITIONS); i++)
    {
	if (positions[POSITIONS[i]] == str ||
            positions[POSITIONS[i]] == C(str))
	{
	    NF("You cannot remove that person!\n");
	    if (i == 0 && member_array(TP->query_name(), GUILDMASTERS) < 0)
	    {
		if ((ADMIN)->query_conclave("sword") != TP->query_name())
		    return 0;
	    }
	    else if (i == 1 && member_array(TP->query_name(), GUILDMASTERS) < 0)
	    {
		if (!(ADMIN)->is_conclave(TP->query_name())
                    && !(ADMIN)->is_grandmaster(TP->query_name()))
		    return 0;
	    }
	    else if (i == 2 && member_array(TP->query_name(), GUILDMASTERS) < 0)
	    {
		if (!(ADMIN)->is_conclave(TP->query_name())
                    && !(ADMIN)->is_grandmaster(TP->query_name()))
		    return 0;
	    }
	    else if (i == 3 || i == 4
                && member_array(TP->query_name(), GUILDMASTERS) < 0)
	    {
		if (!(ADMIN)->is_conclave(TP->query_name())
                    && !(ADMIN)->is_grandmaster(TP->query_name())
                    && positions[POSITIONS[3]] != TP->query_name())
		    return 0;
	    }

	    positions[POSITIONS[i]] = 0;
	    if (find_living(L(str)))
		find_living(L(str))->remove_position();
	    write("You removed "+C(str)+" from the position of "+
                POSITIONS[i]+".\n");
	    find_living(L(str))->catch_msg("You have been removed from the "+
                "position of "+POSITIONS[i]+".\n");
	    save_map(positions, APPOINT_FILE);
	    write_file(APPOINT_LOG, ctime(time())+", "+TP->query_name()+" removed "+
                C(str)+" from position of "+POSITIONS[i]+".\n");
	    return 1;
	}
    }

    write(C(str)+" was not removed from any position.\n");
    return 1;
}

int
is_worthy(string str, object ob)
{
    if (str == POSITIONS[0])
    {
	if (ob->query_knight_level() < 3)
	    return 0;
	return 1;
    }
    else if (str == POSITIONS[1])
    {
	return 1;
    }
    else if (str == POSITIONS[2])
    {
    if (ob->query_knight_level() < 4 && ob->query_knight_sublevel() < 10)
	    return 0;
	return 1;
    }
    else
    {
	if ((ob->query_knight_level() == 3 &&
	    ob->query_knight_sublevel() == 10) ||
            (ob->query_knight_level() > 3 &&
                ob->query_knight_sublevel() > 5))
	    return 1;
	return 0;
    }
}

int
can_appoint(string str, object ob)
{
    if (member_array(ob->query_name(), GUILDMASTERS) >= 0)
	return 1;

    if (str == POSITIONS[0])
    {
	if ((ADMIN)->query_conclave("sword") != ob->query_name())
	    return 0;
	return 1;
    }
    else if (str == POSITIONS[1])
    {
	positions = restore_map(APPOINT_FILE);
	if (!(ADMIN)->is_conclave(ob->query_name()) &&
            (!(ADMIN)->is_grandmaster(ob->query_name()))
            && positions[POSITIONS[1]] != ob->query_name())
	    return 0;
	return 1;
    }
    else if (str == POSITIONS[3] || str == POSITIONS[4])
    {
	if (!(ADMIN)->is_conclave(ob->query_name()) &&
            (!(ADMIN)->is_grandmaster(ob->query_name()))
            &&positions[POSITIONS[2]] != ob->query_name())
	    return 0;
	return 1;
    }
    else
    {
	if (!(ADMIN)->is_conclave(ob->query_name()) &&
            (!(ADMIN)->is_grandmaster(ob->query_name())))
	    return 0;
	return 1;
    }
}

int
add_swordmaster(object act, object tar)
{
    clone_object(SHADOWS + "swordmaster_shadow")->shadow_me(tar);
    /*tar->add_autoshadow(KOBJ + "swordmaster_shadow:");*/
    act->remove_position();
    positions = restore_map(APPOINT_FILE);
    positions += ([POSITIONS[1]:tar->query_name()]);
    save_map(positions, APPOINT_FILE);
    return 1;
}

int
add_general(object tar)
{
    clone_object(SHADOWS + "general_shadow")->shadow_me(tar);
    /*tar->add_autoshadow(KOBJ + "general_shadow:");*/
    positions = restore_map(APPOINT_FILE);
    positions += ([POSITIONS[2]:tar->query_name()]);
    save_map(positions, APPOINT_FILE);
    return 1;
}

int
add_warden(object tar)
{
    clone_object(SHADOWS + "warden_shadow")->shadow_me(tar);
    /*tar->add_autoshadow(KOBJ + "warden_shadow:");*/
    positions = restore_map(APPOINT_FILE);
    positions += ([POSITIONS[0]:tar->query_name()]);
    save_map(positions, APPOINT_FILE);
    return 1;
}

int
add_south_lt(object tar)
{
    clone_object(SHADOWS + "south_lt_shadow")->shadow_me(tar);
    /*tar->add_autoshadow(KOBJ + "south_lt_shadow:");*/
    positions = restore_map(APPOINT_FILE);
    positions += ([POSITIONS[4]:tar->query_name()]);
    save_map(positions, APPOINT_FILE);
    return 1;
}

int
add_east_lt(object tar)
{
    clone_object(SHADOWS + "east_lt_shadow")->shadow_me(tar);
    /*tar->add_autoshadow(KOBJ + "east_lt_shadow:");*/
    positions = restore_map(APPOINT_FILE);
    positions += ([POSITIONS[3]:tar->query_name()]);
    save_map(positions, APPOINT_FILE);
    return 1;
}

int
appoint_player(object act, object tar, string title, string reason)
{
    int add_position;

    if (title == POSITIONS[0])
    {
	add_position = add_warden(tar);
    }
    else if (title == POSITIONS[1])
    {
	add_position = add_swordmaster(act, tar);
    }
    else if (title == POSITIONS[2])
    {
	add_position = add_general(tar);
    }
    else if (title == POSITIONS[3])
    {
	add_position = add_east_lt(tar);
    }
    else if (title == POSITIONS[4])
    {
	add_position = add_south_lt(tar);
    }

    tar->catch_msg("You have been appointed as "+title+" by "+
        QTNAME(act)+".\n");
    act->catch_msg("You appoint "+QTNAME(tar)+" as "+title+".\n");
    tell_room(E(act), QCTNAME(tar)+" is appointed as "+title+
        " by "+QTNAME(act)+".\n", ({ act, tar }));
    write_file(APPOINT_LOG, ctime(time())+ ", "+tar->query_name()+
        " appointed "+title+" by "+act->query_name()+" because "+
        reason +"\n");

    return add_position;
}

int
appoint(string str)
{
    string who, pos, reason, name;
    object ob;

    NF("Appoint <who> as <which position> for <what reason>?\n");
    if (!str)
	return 0;

    if (sscanf(str, "%s as %s for %s", who, pos, reason) != 3)
	return 0;

    NF("No one by the name of "+C(who)+" is in the room.\n");
    if (!find_living(who))
	return 0;

    ob = find_living(who);

    if (!P(ob, E(TP)))
	return 0;

    NF(ob->query_name()+" is not a Knight!\n");
    if (!MEMBER(ob))
	return 0;

    if (pos == "Warden" || pos == "warden")
	pos = POSITIONS[0];

    if (pos == "Swordmaster" || pos == "swordmaster")
	pos = POSITIONS[1];

    if (pos == "General" || pos == "general")
	pos = POSITIONS[2];

    if (pos == "east commander" || pos == "eastern commander" ||
        pos == "East Commander" || pos == "Eastern Commander")
	pos = POSITIONS[3];

    if (pos == "south commander" || pos == "southern commander" ||
        pos == "South Commander" || pos == "Southern Commander")
	pos = POSITIONS[4];

    NF("Award "+C(who)+" with which position?\n");
    if (member_array(pos, POSITIONS) < 0)
	return 0;

    NF("You do not have the authority to appoint positions.\n");
    if (!can_appoint(pos, TP))
	return 0;

    NF("You do not feel "+C(who)+" is worthy of that position yet.\n");
    if (!is_worthy(pos, ob))
	return 0;

    NF(ob->query_name()+" is already in a position of power.\n");
    if (ob->query_knight_sublevel() == 11 &&
        pos != POSITIONS[1])
	return 0;

    positions = restore_map(APPOINT_FILE);

    NF("There is already a "+pos+".\n");
    if (positions[pos])
	return 0;

    NF(ob->query_name()+" already fills a position.\n");
    if (member_array(ob->query_name(), m_values(positions)) >= 0)
	return 0;

    return appoint_player(TP, ob, pos, reason);
}

