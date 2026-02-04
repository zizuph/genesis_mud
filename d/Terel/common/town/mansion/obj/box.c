/*
    This box is used to deliver the reward and the hint for the
        violet component of the Zodiac quest.
    Created: Most likely sometime in '92, when Dust was working
        on the Zodiac quest.

    Modified: 11 June 2003, by Bleys
        - Changed to use modern defs. Now also logs to the moden
            quest log file.
        - Changed the gem from the proprietary version to the
            standard ruby.

*/

#include "/d/Terel/include/Terel.h"

inherit "/std/container";

#include <stdproperties.h>
#include "/d/Terel/include/quest_bits.h"
#include "/d/Terel/include/zodiac.h"

int exp_given;  /* Flag if xp are already given */
object  gem;

public void
fill_it()
{
    seteuid(getuid());
    //gem = clone_object(MANSION + "obj/gem");
    gem = clone_object("/d/Genesis/gems/obj/ruby");
    gem->move(this_object());
}

/*
 * contains a precious gem, but main purpose is the hint
 */
public void
create_container()
{
    seteuid(getuid());
    set_name("box");
    set_short("box");
    set_adj("old");
    set_long("@@long_desc");
    add_prop(CONT_I_WEIGHT, 500);
    add_prop(CONT_I_MAX_WEIGHT,600);
    add_prop(CONT_I_VOLUME, 0);
    add_prop(CONT_I_MAX_VOLUME,100);
    add_prop(CONT_I_TRANSP,1);
    add_prop(CONT_I_RIGID,1);
    add_prop(CONT_I_CLOSED,0);
    add_prop(OBJ_I_NO_GET,1);
    add_prop(OBJ_I_NO_DROP,1);
    set_alarm(2.0, -1.0, fill_it);
    exp_given = 0;
}

public string
quest_solved()
{
    int exp_to_give;

    seteuid(getuid());
    if (exp_given) return("");
    exp_given++;
    if (this_player()->test_bit("Terel", QUEST_MAZE_GROUP, QUEST_MAZE_BIT))
        return(" ");
    this_player()->set_bit(QUEST_MAZE_GROUP, QUEST_MAZE_BIT);
    exp_to_give = this_player()->query_exp();
    if (exp_to_give > QUEST_MAZE_EXP)
        exp_to_give = QUEST_MAZE_EXP;
    this_player()->add_exp(exp_to_give,0);
    /* Original log message
    write_file(QUEST_LOG, this_player()->query_name() +
        " solved maze-quest (" + ctime(time()) + ")\n");
    */
    write_file(QUEST_LOG, TP->query_name() + " solved " +
        "the Zodiac violet component (maze-quest) (" +
        ctime(time()) + ")\n");
    return(" Suddenly you feel much more experienced and " +
        "enlightened than before...");
}


string
long_desc()
{
    return("This is a very old box shimmering in all " +
        "rainbow colors. On the cover of the box you see the " +
        "picture of " + SIGPR[calc_hint(5)] + SIGEQ[calc_hint(5)] + "." +
        quest_solved() + "\n");
}

