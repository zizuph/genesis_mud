/* 921016: Dust: gold room for porcia quest */
/*
    Modified: 11 June 2003, by Bleys
        - Updated to use the newer Terel defs. Altered the quest
            log entry to be more detailed.

    Modified: 20 Aug 2003, by Bleys
        - Added a log line to the failure log if this room damages
            a mortal.
        - Added the zodiac includes.

*/

#include <stdproperties.h>
#include "/d/Terel/include/Terel.h"
#include "/d/Terel/include/quest_bits.h"

inherit STDROOM;

#include "/d/Terel/include/zodiac.h"

#define PORDIR MANSION + "porcia/"
#define DBASE  PORDIR + "riddles"
#define METAL ({"gold", "silver", "lead"})

int metal=0;
string desc_text; /* Description of the painting */

public void
set_metal(int m)
{
    metal = m;
}

public int
get_metal()
{
    return metal;
}

public void
create_metal_room(int m)
{
    object door;
    
    set_metal(m);
    
    set_short("A " + METAL[metal] + " room");
    set_long("@@desc");
    
    add_item(({"picture","painting","drawing"}),
             "This picture is very dusty. You can hardly make out " +
             "anything on it.\n");
    add_cmd_item(
        ({"picture","painting","drawing"}),
        ({"dust","clean"}),
        ({"@@clean_pic","@@clean_pic"}));
    
    add_prop(ROOM_I_INSIDE,1);

    seteuid(getuid());
    door = clone_object(PORDIR + "door_" + METAL[metal] + "_back");
    door->move(this_object());
}

public void
do_move(object who)
{
    tell_object(who, "You feel magically summoned...\n");
    who->move_living("X", PORDIR + "nimroom");
}

public void
init()
{
    int damage;
    object riddleroom;

    ::init();
    
    riddleroom = find_object(PORDIR + "riddle_room");
    desc_text = "";
    if (!riddleroom)
        return;
    damage = riddleroom->get_damage(metal);
    riddleroom->reset_room(); /* Change Riddle */
    if (damage > 0) {   /* wrong room entered */
        damage = this_player()->query_max_hp() * damage / 100;
        write("As you enter the room, you smell the odor of " +
              "death. You suddenly realize that you didn't find the " +
              "correct solution. The punishment of Porcia hits you with " +
              "full power...\n");
        this_player()->reduce_hit_point(damage);
        set_alarm(2.0, -1.0, &do_move(this_player()));
        this_player()->do_die(this_object());
        write_file(FAIL_LOG, TP->query_name() + " mistakenly entered " +
            "Porcia's " + METAL[metal] + " room. Damage done: " +
            damage + ". Mortal's hit points: " + TP->query_hp() +
            " of " + TP->query_max_hp() + ". Timestamp: " +
            ctime(time()) + "\n");
        return;
    }
    desc_text = riddleroom->query_final_hint();
}

public string
desc()
{
    return("This room is made of pure " + METAL[metal] + ". You're dazzled " +
        "by the richness of decorations in this room. On the northern wall " +
        "you can see a dusty painting.\n");
}

public string
quest_solved()
{
    int exp_to_give;

    seteuid(getuid());
    if (this_player()->test_bit("Terel", QUEST_POR_GROUP, QUEST_POR_BIT))
        return(" ");
    this_player()->set_bit(QUEST_POR_GROUP,QUEST_POR_BIT);
    exp_to_give = this_player()->query_exp();
    if (exp_to_give > QUEST_POR_EXP)
        exp_to_give = QUEST_POR_EXP;
    this_player()->add_exp(exp_to_give, 0);
    write_file(QUEST_LOG, this_player()->query_name() +
        " solved porcia-quest (" + ctime(time()) + ")\n");
    write_file(QUEST_LOG, TP->query_name() + " solved " +
        "the Zodiac yellow component (porcia-quest) (" + 
        ctime(time()) + ")\n");
    return("Suddenly you feel much more experienced and " +
        "enlightened than before...\n");
}

/*
 * This function describes the dusty painting after cleaning it
 */
string
clean_pic()
{
    if (desc_text == "") return("The painting remains empty.\n");
    return(desc_text + quest_solved());
}
