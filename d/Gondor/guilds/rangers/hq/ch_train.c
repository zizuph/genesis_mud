/*
 *  /d/Gondor/guilds/rangers/hq/ch_train.c
 *  
 *  Training hall of Ranger Central Headquarters.
 *
 *  Coded by Alto and Gwyneth, 26 June 2001
 *  
 *   Previous incarnation:
 *
 *   Rangers of Gondor training hall - modified by Elessar, from:
 *   adv_guild.c    Styles   Wed Jan 22 1992
 *
 *   The train hall of Gondor Company
 *   Modified by Olorin, 30-Oct-1993
 *
 *   Modified by Gwyneth, Aug 13, 2002: Made changes for the recode
 *   Modified by Gwyneth, May 3, 2004: neatened up
 */
inherit "/d/Gondor/guilds/rangers/train_base.c";
/*
inherit "/d/Shire/lib/training";
*/

#include "../rangers.h"
#include "/d/Gondor/defs.h"
#include <files.h>
#include <macros.h>
#include <options.h>
#include <ss_types.h>

#define PRACTICE_WITH_DUMMY       "_practice_with_dummy"

public string      long_desc();
public int         practice_orc();
public int         practice_troll();
public int         practice_mage();
public int         practice_haradrim();
public int         finish_practice(object tp);
public int         check_practice(object tp);
public string      exa_plaque();


string
long_desc()
{
    return "This large hall appears to be designed for the express "
        + "purpose of combat training and practice. The wooden floor is "
        + "free of furniture, and is painted with an intricate pattern of "
        + "concentric and overlapping circles. Several mannequins are "
        + "suspended from the ceiling by sturdy ropes. If you choose to "
        + "train here, expect many bruises, and although you may shed no "
        + "blood, count on shedding several buckets of sweat before your "
        + "training is complete. A master ranger moves through the room "
        + "now and then, looking for weaknesses in your technique. "
        + "You also notice a large barrel to one side "
        + "with a wooden plaque nailed above it.\n";
}

void
create_trainhall()
{
    set_short("the training room of Central Headquarters");
    set_long(&long_desc());

    add_exit(RANGERS_HQ_DIR + "office", "west", check_practice, 2);

    add_item(({"room", "hall", "large hall"}), &long_desc());
    add_item(({"wall", "walls", "north wall", "wall to the north"}), "The "
        + "walls, like most things in the "
        + "hideout, are constructed from wood. You feel a warm glow in this "
        + "place, rather unlike the cold stone rooms and dwellings in "
        + "so-called civilized regions. The north wall is also a little warmer "
        + "as a result of the iron torch stand mounted upon it.\n");
    add_item(({"circles", "circle", "concentric circles",
        "overlapping circles"}), "The circles are painted in a perplexing "
        + "array of patterns. Some circles lie within larger circles, while "
        + "others stand alone, and yet others overlap. When a Master ranger "
        + "works with the apprentices, he or she uses these circles to test "
        + "the agility of each novice. As noviciates rise in skill, they are "
        + "able to leap and roll through more circles before the Master "
        + "leaves them flat on their backs and blinded with sand.\n");
    add_item(({"mannequin", "mannequins", "sturdy ropes", "ropes"}), "There "
        + "are mannequins suspended by sturdy ropes in the four corners "
        + "of the room. The first mannequin resembles an orc, the second "
        + "a troll, the third a mage and the fourth a haradrim warrior.\n");
    add_item(({"first mannequin", "orc", "orc mannequin"}), 
        "This practice mannequin is made "
        + "from old stained sheets stuffed with greasy rags. It looks and "
        + "smells very much like one of the filthy orcs of Mordor. Sewed "
        + "onto its head is a leather helmet bearing the emblem of the "
        + "Red Eye. You feel a sudden urge to practice on it.\n");
    add_item(({"second mannequin", "troll", "troll mannequin"}), 
        "This practice mannequin is made "
        + "from several large burlap sacks filled with rocks. This, coupled "
        + "with its immense size, gives it the look and feel of a hill troll. "
        + "It rocks slowly back and forth on its rope, silently urging you "
        + "to practice on it.\n");
    add_item(({"third mannequin", "mage", "black-robed mannequin",
        "mage mannequin"}), "Made from black canvas, this "
        + "practice mannequin resembles a hooded mage in the service of Mordor. "
        + "It is so realistic that you almost feel the cold light of corruption "
        + "leering at you from under its hood. If you are brave, you can "
        + "try to practice on it.\n");
    add_item(({"fourth mannequin", "haradrim", "warrior", "haradrim warrior",
        "haradrim mannequin", "haradrim warrior mannequin"}),
        "This practice mannequin is made from brown strips of leather "
        + "bound together with cunning knots and stitches. Gilded paint has "
        + "been applied to the head such that the mannequin appears to have "
        + "ear and nose rings. It might be worth your while to practice on "
        + "it.\n");
    add_item(({"barrel", "large barrel"}), "Painted on the side of the barrel "
        + "in bold red letters is a single word: \n\t\t\tS A N D.\n");
    add_item(({"sheets", "rags", "burlap", "sacks", "canvas", "leather",
        "strips", "knots", "stitches", "paint", "rocks"}), "The various "
        + "mannequins are constructed of such things.\n");
    add_item(({"wooden sword", "sword", "wooden practice sword", 
        "practice sword"}), "Scattered about the room are "
        + "a number of wooden practice swords. Although useless as a weapon "
        + "in real combat, they are cunningly weighted and balanced to "
        + "resemble the feel of an actual sword.\n");
    add_item(({"string"}), "Hmm, there seems to be a small string attached "
        + "to the back of the mage mannequin.\n");
    add_item(({"hole", "hole in wall", "hole in the wall"}), "Hmm, there "
        + "seems to be a small hole in the wall behind the mage mannequin.\n");
    add_item(({"sand"}), "There is a huge quantity of it in the barrel. You "
        + "suddenly realize how rangers always seem to have sand when they "
        + "need it.\n");
    add_item(({"ranger", "master ranger"}), "The master ranger passes through "
        + "the room now and then, often pausing to shake his head at your "
        + "amateur technique. His battle-hardened wisdom was well-earned. "
        + "Pay heed to anything he tells you.\n");

    add_item(({"wooden plaque", "plaque"}), &exa_plaque());
    add_cmd_item(({"wooden plaque", "plaque"}), "read", &exa_plaque());

    add_cmd_item(({"first mannequin", "on first mannequin", "orc", 
        "on orc", "on the first mannequin", "on the orc"}), "practice",
            &practice_orc());
    add_cmd_item(({"second mannequin", "on second mannequin", "troll", 
        "on troll", "on the second mannequin", "on the troll"}), "practice",
            &practice_troll());
    add_cmd_item(({"third mannequin", "on third mannequin", "mage", 
        "on mage", "on the third mannequin", "on the mage"}), "practice",
            &practice_mage());
    add_cmd_item(({"fourth mannequin", "on fourth mannequin", "haradrim", 
        "on haradrim", "on the fourth mannequin", "on the haradrim",
        "warrior", "on warrior", "on the warrior"}), "practice",
            &practice_haradrim());


    add_prop(ROOM_I_INSIDE, 1);
    add_prop(ROOM_I_LIGHT, 1);

    set_company_num(APPRENTICE_LEVEL);
}

int
practice_orc()
{
    object tp = this_player();

    if (tp->query_prop(PRACTICE_WITH_DUMMY))
    {
        tp->catch_tell("You are already practicing!\n");
        return 1;
    }

    tp->add_prop(PRACTICE_WITH_DUMMY, 1);

    set_alarm(1.0, 0.0, &tp->catch_tell("\nYou kneel down and focus your "
        + "concentration on the orc mannequin. Taking up a wooden "
        + "practice sword, you spring into a fighting stance.\n\n"));
    set_alarm(1.0, 0.0, &tell_room(environment(tp), QCTNAME(tp)
        + " kneels down, takes up a wooden practice sword and approaches "
        + "the orc mannequin.\n\n", tp)); 

    set_alarm(4.0, 0.0, &tp->catch_tell("Your first blow to the mannequin "
        + "results in a barely audible smack that does not even cause "
        + "it to swing on its rope. Come on, put some heart into it!\n\n"));
    set_alarm(4.0, 0.0, &tell_room(environment(tp), QCTNAME(tp)
        + " bats weakly at the orc mannequin. It does not even rock "
        + "upon its rope.\n\n", tp)); 

    set_alarm(7.0, 0.0, &tp->catch_tell("Stepping back, you examine the "
        + "mannequin more carefully.\n\n"));
    set_alarm(7.0, 0.0, &tell_room(environment(tp), QCTNAME(tp)
        + " steps back and carefully examines the orc mannequin.\n\n", tp));

    set_alarm(12.0, 0.0, &tp->catch_tell("You notice a small " +
        "rip in the cloth making up the head of the orc " +
        "mannequin. Gripping the wooden practice sword in both " +
        "hands you hack at the head repeatedly.\n\n"));
    set_alarm(12.0, 0.0, &tell_room(environment(tp), QCTNAME(tp)
        + " begins to hack at the head of the orc mannequin repeatedly.\n\n",
        tp));

    set_alarm(15.0, 0.0, &tp->catch_tell("Stuffing flies in all directions as "
        + "your sword bites into the head of the orc mannequin!\n\n"));
    set_alarm(15.0, 0.0, &tell_room(environment(tp), "Stuffing flies "
        + "in all directions as " + QTNAME(tp) + " rips into the "
        + "head of the orc mannequin!\n\n", tp)); 

    set_alarm(18.0, 0.0, &tp->catch_tell("The orc mannequin swings back and "
        + "forth in defeat as you cast the wooden practice sword away.\n\n"));
    set_alarm(18.0, 0.0, &tell_room(environment(tp), "The orc "
        + "mannequin swings back and forth in defeat as " + QTNAME(tp)
        + " casts the wooden practice sword away.\n\n", tp));

    set_alarm(18.0, 0.0, &finish_practice(tp));

    return 1;

}

int
practice_troll()
{
    object tp = this_player();

    if (tp->query_prop(PRACTICE_WITH_DUMMY))
    {
        tp->catch_tell("You are already practicing!\n");
        return 1;
    }

    tp->add_prop(PRACTICE_WITH_DUMMY, 1);

    set_alarm(1.0, 0.0, &tp->catch_tell("\nYou kneel down and focus your "
        + "concentration on the troll mannequin. Taking up a wooden "
        + "practice sword, you spring into a fighting stance.\n\n"));
    set_alarm(1.0, 0.0, &tell_room(environment(tp), QCTNAME(tp)
        + " kneels down, takes up a wooden practice sword and approaches "
        + "the troll mannequin.\n\n", tp)); 

    set_alarm(4.0, 0.0, &tp->catch_tell("You strike the troll mannequin " +
        "with all your might! As your wooden practice sword connects " +
        "with the body of the mannequin, the sword cracks down the " +
        "middle! The mannequin, which is made of stone, does not " +
        "seem very impressed.\n\n"));
    set_alarm(4.0, 0.0, &tell_room(environment(tp), QCTNAME(tp)
        + " strikes the troll mannequin with a mighty blow! As the "
        + "wooden practice sword connects with the body of the mannequin, "
        + "the sword cracks down the middle! The mannequin, which is made "
        + "of stone, does not seem very impressed.\n\n", tp)); 

    set_alarm(7.0, 0.0, &tp->catch_tell("Stepping back, you examine the "
        + "mannequin more carefully.\n\n"));
    set_alarm(7.0, 0.0, &tell_room(environment(tp), QCTNAME(tp)
        + " steps back and carefully examines the troll mannequin.\n\n", tp));

    set_alarm(12.0, 0.0, &tp->catch_tell("You notice that while " +
        "the head and body of the mannequin are filled with " +
        "stone, the neck is really just a thick piece of rope " +
        "running through its center. Taking careful aim, you " +
        "swing your practice sword at the neck.\n\n"));
    set_alarm(12.0, 0.0, &tell_room(environment(tp), QCTNAME(tp)
        + " swings the wooden practice sword directly at the neck of "
        + "the troll mannequin.\n\n", tp));

    set_alarm(15.0, 0.0, &tell_room(environment(tp), "With a loud "
        + "BOOM, the heavy rock-filled body of the troll mannequin "
        + "crashes to the floor!\n\n")); 

    set_alarm(18.0, 0.0, &tp->catch_tell("Several ranger apprentices " +
        "arrive to reconnect the troll body with its head as you " +
        "cast your wooden practice sword away. As soon as it is " +
        "together once more, the apprentices bustle away on other " +
        "business.\n\n"));
    set_alarm(18.0, 0.0, &tell_room(environment(tp), "Several ranger "
        + "apprentices arrive to reconnect the troll body with its head as "
        + QTNAME(tp) + " casts the wooden practice sword away. The "
        + "apprentices then quickly bustle away on other business.\n\n", tp));

    set_alarm(18.0, 0.0, &finish_practice(tp));

    return 1;

}


int
practice_mage()
{
    object tp = this_player();


    if (tp->query_prop(PRACTICE_WITH_DUMMY))
    {
        tp->catch_tell("You are already practicing!\n");
        return 1;
    }

    tp->add_prop(PRACTICE_WITH_DUMMY, 1);

    set_alarm(1.0, 0.0, &tp->catch_tell("\nYou kneel down and focus your "
        + "concentration on the mage mannequin. Taking up a wooden "
        + "practice sword, you spring into a fighting stance.\n\n"));
    set_alarm(1.0, 0.0, &tell_room(environment(tp), QCTNAME(tp)
        + " kneels down, takes up a wooden practice sword and approaches "
        + "the mage mannequin.\n\n", tp)); 

    set_alarm(4.0, 0.0, &tp->catch_tell("By some clever design of " +
        "its construction the black-robed mannequin seems to float " +
        "out of range as your first swing cuts through nothing " +
        "but thin air!\n\n"));
    set_alarm(4.0, 0.0, &tell_room(environment(tp), QCTNAME(tp)
        + " cuts through nothing but air as the black-robed mannequin "
        + "seems to float just out of range!\n\n", tp)); 

    set_alarm(7.0, 0.0, &tp->catch_tell("Stepping back, you examine the "
        + "mannequin more carefully.\n\n"));
    set_alarm(7.0, 0.0, &tell_room(environment(tp), QCTNAME(tp)
        + " steps back and carefully examines the mage mannequin.\n\n", tp));

    set_alarm(12.0, 0.0, &tp->catch_tell("You notice a small string " +
        "running from the back of the mannequin through a hole in " +
        "the wall behind it. Quickly, you scoop some sand from the " +
        "barrel and fling it through the hole. Coughing sounds can " +
        "be heard from the other side of the wall!\n\n"));
    set_alarm(12.0, 0.0, &tell_room(environment(tp), QCTNAME(tp)
        + " scoops some sand from the barrel and flings it at the wall "
        + "behind the mage mannequin. Coughing sounds can be heard from "
        + "the other side of the wall!\n\n", tp));

    set_alarm(15.0, 0.0, &tp->catch_tell("This time as you bring " +
        "your sword down upon its head, the mannequin does not " +
        "move. You rip it open from stem to stern!\n\n"));
    set_alarm(15.0, 0.0, &tell_room(environment(tp), "This time the "
        + "black-robed mannequin does not move as " +  QTNAME(tp) + " rips "
        + "it from stem to stern with the wooden practice sword!\n\n", tp)); 

    set_alarm(18.0, 0.0, &tp->catch_tell("The mage mannequin is " +
        "left nothing more than a collection of tattered black " +
        "rags as you cast the wooden practice sword away.\n\n"));
    set_alarm(18.0, 0.0, &tell_room(environment(tp), "The mage "
        + "mannequin is left nothing more than a collection of tattered black " 
        + "rags as " + QTNAME(tp)
        + " casts the wooden practice sword away.\n\n", tp));

    set_alarm(18.0, 0.0, &finish_practice(tp));
    return 1;
}

int
practice_haradrim()
{
    object tp = this_player();

    if (tp->query_prop(PRACTICE_WITH_DUMMY))
    {
        tp->catch_tell("You are already practicing!\n");
        return 1;
    }

    tp->add_prop(PRACTICE_WITH_DUMMY, 1);

    set_alarm(1.0, 0.0, &tp->catch_tell("\nYou kneel down and focus your "
        + "concentration on the haradrim mannequin. Taking up a wooden "
        + "practice sword, you spring into a fighting stance.\n\n"));
    set_alarm(1.0, 0.0, &tell_room(environment(tp), QCTNAME(tp)
        + " kneels down, takes up a wooden practice sword and approaches "
        + "the haradrim mannequin.\n\n", tp)); 

    set_alarm(4.0, 0.0, &tp->catch_tell("Your first blow skewers " +
        "the mannequin and pins it to the wall! Haradrim " +
        "are wimps!\n\n"));
    set_alarm(4.0, 0.0, &tell_room(environment(tp), QCTNAME(tp)
        + " skewers the haradrim mannequin and pins it to the wall with "
        + "the wooden practice sword. Haradrim are wimps!\n\n", tp)); 

    set_alarm(7.0, 0.0, &tp->catch_tell("You turn from the mannequin and "
        + "cast the wooden practice sword away.\n\n"));
    set_alarm(7.0, 0.0, &tell_room(environment(tp), QCTNAME(tp)
        + " turns from the haradrim mannequin and casts the wooden practice "
        + "sword away.\n\n", tp));

    set_alarm(7.0, 0.0, &finish_practice(tp));
    return 1;
}

int
finish_practice(object tp)
{
    tp->remove_prop(PRACTICE_WITH_DUMMY);
    return 1;
}

int
check_practice(object tp)
{
    if (tp->query_prop(PRACTICE_WITH_DUMMY))
    {
        tp->catch_tell("You cannot leave in the middle of practice!\n");
        return 1;
    }

    return 0;
}

public string
exa_plaque()
{
    return "Here you may <meditate> to set your stat-preferences, and <learn> "
        + "or <improve> your skills. You may also <list guilds> to discover "
        + "information about the guilds of which you are a member.\n";
}
