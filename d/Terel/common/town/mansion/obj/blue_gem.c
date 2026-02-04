/* Dust 921105: blue gem
 *
 *  This gem is the solution for the blue component of the Zodiac
 *      quest and provides the hint for that part of the overall
 *      Zodiac quest solution.
 *
 *  Modified: 11 June 2003, by Bleys
 *      - Updated to use modern includes and inherit.
 *      - Now logging to the right quest file.
 *
 */

#include "/d/Terel/include/Terel.h"

inherit STDOBJECT;

#include <stdproperties.h>
#include "/d/Terel/include/quest_bits.h"
#include "/d/Terel/include/zodiac.h"

public void
do_destroy()
{
    object where = environment(this_object());
    
    if (living(where)) {
        where->catch_msg("The blue gem suddenly disintegrates to dust.\n");
    } else if (where->query_prop(ROOM_I_IS)) {
        tell_room(where, "The blue gem suddenly disintegrates to dust.\n");
    }
    remove_object();
}

public void
create_object()
{
    set_name("gem");
    set_adj("blue");
    set_long("@@long_desc");

    add_prop(OBJ_I_WEIGHT,500);
    add_prop(OBJ_I_VOLUME,500);
    add_prop(OBJ_I_VALUE,2000);

    set_alarm(180.0, -1.0, do_destroy);
}

public string
quest_solved()
{
    int exp_to_give;

    seteuid(getuid());
    if (this_player()->test_bit("Terel",QUEST_CHI_GROUP,QUEST_CHI_BIT))
        return(" ");
    this_player()->set_bit(QUEST_CHI_GROUP,QUEST_CHI_BIT);
    exp_to_give = this_player()->query_exp();
    if (exp_to_give > QUEST_CHI_EXP)
        exp_to_give = QUEST_CHI_EXP;
    this_player()->add_exp(exp_to_give, 0);
    /*
    write_file(QUEST_LOG,this_player()->query_name() +
        " solved chisel-quest (" + ctime(time()) + ")\n");
    */
    write_file(QUEST_LOG, TP->query_name() + " solved " +
        "the Zodiac blue component (chisel-quest) (" +
        ctime(time()) + ")\n");
    return(" Suddenly you feel much more experienced and " +
        "enlightened than before...");
}


public string
long_desc()
{
    return("That's a very strange gem, it looks " +
        "somehow unreal. It's glowing in a blue color, and its " +
        "shape reminds you of " + SIGPR[calc_hint(4)] +
         SIGEQ[calc_hint(4)] + ". It looks very precious!" +
         quest_solved() + "\n");
}


