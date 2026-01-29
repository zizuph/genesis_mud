/* 
 * /d/Kalad/common/wild/pass/goblin/guild/plan_room.c
 * Purpose    : Fang board room
 * Located    : Fang Guild
 * Created By : Sarr  ??.??.??
 * Modified By: Sarr 17.Apr.97
 */ 
#pragma save_binary
#include <stdproperties.h>
inherit "/d/Kalad/room_std";
#include "/d/Kalad/defs.h"
#include "/d/Kalad/common/guilds/red_fang/default.h"
#define BOARD_DIR "/d/Kalad/log/red_fang"


void
create_room()
{
    object bb;
    ::create_room();
    INSIDE;
    set_short("The battle planning room");
    set_long("\n   You are in a cozy little cavern.  The room is filled "+    
    "with maps, posters, and decorations.  This is the central "+
    "planning room of the Red Fang. Here, the warriors plot and "+
    "discuss their mayhem.  There are tables here with chairs "+
    "where the members sit and plan their treachery.\n\n");
    add_item(({"posters","maps"}),"Pictures and maps of Kabal, "+
    "the area around Kabal, the caravan route, the sewers, the various "+
    "districts of Kabal, and the port.\n");
    add_item("decorations","Swords, shields, daggers, tapestries, "+
    "rugs, valuable lanterns, and all kinds of beautiful treasures "+
    "you would not expect a goblins to posses. Probably loot from "+
    "their raids.\n");
    add_item("tables","Beautiful oak ones, covered with papers.\n");
    add_item("chairs","Beautiful oak ones, with fluffy seats.\n");
    add_exit(FANG_DIR(rooms/joinroom),"west",0,-1);
    
    setuid();
    seteuid(getuid());
    bb = clone_object("/std/board");
    bb->set_board_name(BOARD_DIR);
    bb->set_num_notes(30);
    bb->set_silent(0);
    bb->set_show_lvl(0);
    bb->move(this_object(), 1);
}

