/*
 * cadu_guild.c
 *
 * This was once a part of the domain Roke.
 * Cleaned up and moved into Khalakhor by Glindor, Nov 2001.
 *
 * Set a standard charity box instead of custom one.
 * TAPAKAH 31/05/2005
 */

#pragma save_binary
#pragma strict_types

inherit "/std/room";
inherit "/lib/guild_support";
inherit "/lib/skill_raise";

#include "defs.h"
#include <ss_types.h>
#include <stdproperties.h>
#include <std.h>

#define CHARITY "/d/Genesis/start/human/obj/cbox"

void set_up_skills();

void
create_room()
{
    object board, box;

    set_short("Adventurer's guild");
    set_long("You are in the Adventurer's Guild in Cadu.\n" +
        "This is a cosy and very nice place to be. There is a nice " +
        "log-fire in a corner and you can see nice pictures on the wall.\n" +
        "Here you can leave messages to your fellow adventurers.\n" +
        "It's also possible to improve your skills and if you want to " +
        "change your stat-priorities, you can also meditate here.\n");
    
    add_item("fire", "The fire brings heat to the house.\n");

    add_item(({"paintings", "pictures"}),
        "You see the pictures of three mighty " +
        "wizards. You see that they are the wizards whose statues are " +
        "located at the town square.\n");

    INSIDE;
    add_prop(OBJ_I_HAS_FIRE, 1);
    
    add_exit("cadu_a5", "north");
    add_exit("common" , "common");

    box = clone_object(CHARITY);
    box->set_long(
		  "It's a rather large box, made of gold and valuable crystals.\n"+
		  "A small sign is placed on one of the sides, close to the floor.\n"
		  );
    box->move(TO);
    clone_object(ROKEDIR + "wep/orc_knife")->move(box);
    
    board = clone_object("/std/board");
    board->set_board_name(ROKEDIR + "board");
    board->set_num_notes(17);         /* Number of notes         */
    board->set_silent(0);             /* Make noise when reading */
    board->set_show_lvl(0);
    board->set_remove_rank(WIZ_LORD);         /*Lords or higher  */
    board->set_remove_str("You somehow failed.");
    board->move(this_object());

    create_skill_raise();
    set_up_skills();
}

void
leave_inv(object ob, object to)
{
    gs_leave_inv(ob, to);
    ::leave_inv(ob, to);
}

void
init()
{
    init_guild_support();
    init_skill_raise();
    ::init();
}

void
set_up_skills()
{
    /*
     * Default messages will then be:
     * You improve your ability to <str1> ....
     * XXX improves <his> ability to <str2> ...
     */
    // sk_add_train(snum, desc, name, costf, maxskill, stat, weight)

    sk_add_train(SS_APPR_MON,   "appraise opponents",           0, 0, 30);
    sk_add_train(SS_APPR_OBJ,   "appraise different objects",   0, 0, 30);
    sk_add_train(SS_TRACKING,   "track",                        0, 0, 30);
    sk_add_train(SS_CLIMB,      "climb walls and mountains",    0, 0, 30);
    sk_add_train(SS_ANI_HANDL,  "handle animals",               0, 0, 30);
    sk_add_train(SS_AWARENESS,  "be aware of the surroundings", 0, 0, 30);
    sk_add_train(SS_LOC_SENSE,  "not get lost",                 0, 0, 30);
    sk_add_train(SS_SWIM,       "swim",                         0, 0, 30);
    sk_add_train(SS_DEFENCE,    "not get hit",                  0, 0, 10);
//  Removed the following skills - Maximum allowed is 250 slots
//  Damaris 01/2005
//    sk_add_train(SS_HERBALISM,  "find and identify herbs",      0, 0, 20);
//    sk_add_train(SS_LANGUAGE,   "understand foreign languages", 0, 0, 30);    
//    sk_add_train(SS_SPELLCRAFT, "use spellcraft",               0, 0, 20);
    
    }
