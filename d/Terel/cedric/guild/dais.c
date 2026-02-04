#pragma save_binary

inherit "/std/room.c";
#include <macros.h>
#include "/d/Terel/common/terel_defs.h"
#include "/d/Terel/cedric/guild/guild_defs.h"
#include "/d/Terel/cedric/guild/guild_funs.c"

/*
 * The Minstrel Guild Headquarters: Dais
 * From this dais, exactly centered in the accoustically perfect magical
 * courtyard of the Minstrels guild, one can be heard by minstrels everywhere.
 * Cedric 1/93
 */

void
init()
{
    ::init();
    add_action("do_project", "project");
}

void
create_room()
{
    set_short("The Dais of the Minstrels");
    set_long(BS("This oddly shaped dais is beautiful, an altar to sound and "
        + "music. And yet you get the sense that the dais is also much more. "
        + "An ambient roar fills the air, and you know somehow (without being quite "
        + "sure how you know) that every sound in the world is funneled to this "
        + "very spot. The ringing of bells, the clash of battle, the soft babbling "
        + "of a gentle stream...uncounted voices speaking innumerable languages. The "
        + "footsteps of the weary traveler, the selling cry of the market merchant, "
        + "the soft rustle of an assassin's robe...you hear, as you stand upon the "
        + "dais, each of these sounds as if the source were right beside you. Yet "
        + "somehow the cacophony does not deafen, but enlightens you. It is as if "
        + "the divine Muses were somehow a little closer here.\n")+"A burnished plaque "
        + "of some strange metal.\n");
        add_item(({"plaque","metal plaque"}),BS("FOCUS YOUR MIND AND MEDITATE UPON THE "
        + "BEAUTY AND POWER OF SOUND. YOU SHALL FIND THAT YOU MAY <PROJECT> YOUR VOICE "
        + "OVER GREAT DISTANCES.\n"));
        add_cmd_item("plaque","read",BS("FOCUS YOUR MIND AND MEDITATE UPON THE "
    + "BEAUTY AND POWER OF SOUND. YOU SHALL FIND THAT YOU MAY <PROJECT> YOUR VOICE "
        + "OVER GREAT DISTANCES.\n"));

    add_exit(GUILD+"courtyard", "down");
}

int
do_project(string str)
{
    object *folks;
    int i;
    
    if (!MEMBER(TP()))
    {
	notify_fail(BS("Your voice seems weak even to yourself, overwhelmed "
	+ "by the sheer power of sound in this place.\n"));
	return 0;
    }
    if (!strlen(str))
    {
        notify_fail(BS("What would you like to project? Keep in mind that " 
        + "Minstrels the world over shall hear your words.\n"));
        return 0;
    }
    folks = on_line();
    for (i=0;i<sizeof(folks);i++)
        if (!present(folks[i]))
        {
            if (folks[i]->query_hear_dais())
                folks[i]->catch_msg("From afar you hear "+TP()->query_name()
                + ", voice amplified by the magic "
                + "of the Dais:\n"+str+"\n");
        }
        else
            if (folks[i]!=TP())
                folks[i]->catch_msg(TP()->query_name()+" draws upon the magic of "
                + "the Dais, and projects to the world:\n"+str+"\n");
    write(BS("You draw upon the magic of this place, and project your "
    + "voice to Minstrels the world over.\n"));
    return 1;
}