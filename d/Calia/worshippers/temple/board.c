
 /* Worshippers training room/private board room */
 /* by Jaacar 1996                               */
 /* 
  * Change log: 
  *             Baldacin, May 2004.
  *                Added a trash bin where people
  *                can throw useless items in.
  */ 

#pragma save_binary
#pragma strict_types

inherit "/std/room";
inherit "/lib/skill_raise";

#include <stdproperties.h>
#include <macros.h>
#include <language.h>
#include <money.h>
#include <ss_types.h>
#include "defs.h"
#include WORSHIP_HEADER

#define OLD_SKILL 114053

void load_board();
void set_up_skills();
 
#include "skills.h"

int
is_worship(object living)
{
    return living->query_guild_name_lay() == GUILD_NAME;
}

void
create_room()
{
    set_short("Training chamber");
    set_long("This chamber of the natural temple is a training "+
        "facility for the members of this circle. "+
        "There is also a bulletin "+
        "board here for members to share their thoughts and "+
        "ideas on. "+
        "To the northwest you see a large chamber with an altar "+
        "in it, and to the west a cosy chamber with beds. You "+
        "notice some various training tools in the corner and a fair "+
        "sized trash bin has been placed at the side of the board."+
        "\n");

    add_item(({"walls","wall"}),"The walls here are made of a "+
        "granite-like stone, much like the other walls in this "+
        "temple.\n");

    add_item(({"floor","ground"}),"The floor is a "+
        "nicely trimmed layer of green grass which feels good on your "+
        "feet as you walk around.\n");

    add_item(({"roof","ceiling"}),"The ceiling consists of grass, straw "+
        "and mud packed together in a tight weave to make a warm, sturdy "+
        "roof.\n");

    add_item(({"tools","training tools"}),"Among the tools you recognize "+
        "a few polearms, a few scrolls, some tomes, and various writing "+
        "implements.\n");

    add_item(({"polearms","polearm"}),"You notice a few wooden halberds, "+
        "and a couple of "+
        "wooden quarterstaves, usable only for training.\n");

    add_item(({"scroll","scrolls"}),"The scrolls are used for training in "+
        "the spellcasting arts.\n");

    add_item(({"tome","tomes"}),"These tomes contain examples of various "+
        "spells and languages for training.\n");

    add_item(({"writing implements","implements"}),"These writing implements "+
        "are used for learning spellcasting skills as well as practicing "+
        "various languages.\n");

    add_prop(ROOM_I_INSIDE,1);
    add_prop(ROOM_M_NO_ATTACK,1);

    add_exit(WOR_TEMPLE+"s_chamber","northwest",0,1);
    add_exit(WOR_TEMPLE+"startroom","west","@@check_worship",1);
    add_exit(WOR_TEMPLE+"discuss_recode","up",0,1);
    
    load_board();
    create_skill_raise();
    set_up_skills();
}

void
load_board()
{
    object bb;
    seteuid(getuid(this_object()));
    bb = clone_object(WOR_TEMPLE+"pboard");
    bb->move(this_object());
    clone_object(WOR_OBJECTS+"cabinet")->move(this_object());
    clone_object(WOR_OBJECTS+"trash_bin")->move(this_object());
}
 
int query_prevent_snoop()
{
    return 1;
}
 
void
init()
{
    ::init();
    init_skill_raise();
    if (TP->query_skill(OLD_SKILL))
    {
        TP->remove_skill(OLD_SKILL);
    }
}

public int
sk_improve(string sk)
{
    if (!is_worship(TP))
    {
        write("You are not a member of this guild!\n");
        return 1;
    }

    if (TP->query_skill(SS_PUNISHMENT) == 2)
    {
        write("You have been banned from training by the council!\n");
        return 1;
    }
    return ::sk_improve(sk);
}

int
check_worship()
{
    // Only worshippers and wizards can access the start room
    object player = this_player();
    if (player->query_wiz_level()
        || is_worship(player)
        || player->query_guild_name_occ() == "Spirit Circle of Psuchae")
    {
        return 0;
    }

    write("A voice echoes through your mind: 'Only those who "+
        "follow the Elemental ways may pass.'\n");
    return 1;
}
