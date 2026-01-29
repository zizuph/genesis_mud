/*
 *  /d/Sparkle/area/orc_temple/escape_route.c
 *
 *  We want to give players this way to escape the dungeon for 2 reasons.
 *  Firstly, it make it possible for them to remove themselves from a jail
 *  cell in the event that they get locked in. Secondly, it gives players
 *  a way to get out of the newbie dungeon without having to pass through
 *  the obvious exit which could be a very convenient ambush point for a
 *  would-be assasain who wants to take advantage of the effects of the
 *  amulet.
 *
 *  Created January 2011, by Cooper Sherry (Gorboth)
 */
#pragma strict_types

#include <filepath.h>
#include <macros.h>
#include <stdproperties.h>
#include <time.h>
#include "../defs.h"
#include "/d/Sparkle/sys/quests.h"

inherit ROOMS_DIR + "dungeon_room";

/* prototypes */
public void        create_dungeon_room();
public void        choose_event();
public void        first_message(object who);
public void        second_message(object who);
public void        third_message(object who);
public void        fourth_message(object who);
public void        fifth_message(object who);
public void        sixth_message(object who);
public void        seventh_message(object who);
public void        eighth_message(object who);
public void        ninth_message(object who);
public void        transfer(object who);
public void        enter_inv(object ob, object from);
public void        remove_amulet(object who);

/* global variables */
public string     *Events = ({
                     "Reaching a bend, you angle to the left and keep"
                   + " crawling foward ...",
                     "You reach a seeming dead end, and then realize"
                   + " the tunnel turns sharply to the right, so you"
                   + " continue to crawl foward ...",
                     "You reach a damp patch, and elbow your way"
                   + " slowly through a section of wet mud ...",
                     "A sudden sound of scurrying comes from somewhere"
                   + " ahead. You pause, and then continue forward ...",
                     "Your elbows and knees chafe against what feels"
                   + " like sharp rocks of some kind, but you keep"
                   + " crawling forward, grimmacing with pain ...",
                     "What feel like tree roots suddenly swipe against"
                   + " your face and you scramble to crawl through the"
                   + " web of dirt caked organic netting ...",
                     "The tunnel opens suddenly onto a small chamber"
                   + " in the earth. You see the corpse of a long-dead "
                   + one_of_list(({ "dwarf", "elf", "gnome", "man",
                     "woman", "hobbit" })) + " resting against the"
                   + " wall. Quickly, you continue forward into a narrow"
                   + " opening and continue to crawl ...",
                     "You feel a sudden shift in the composition of the"
                   + " tunnel, and realize you are crawling through very"
                   + " sandy soil. The going is tough, but you work your"
                   + " way slowly forward, eventually finding packed"
                   + " earth again ...",
                            });


/*
 * Function name:        create_dungeon_room
 * Description  :        set up the room
 */
public void
create_dungeon_room()
{
    /* We remove the name of the dungeon room so that the player can
     * take off their amulet, if they are wearing one.
     */
    remove_name(DUNGEON_ROOM);

    set_short("you are crawling forward through a horribly narrow dirt"
      + " tunnel");
    set_long(capitalize(short()) + ".\n\n");

    add_item( ({ "here", "area", "room", "tunnel", "dirt tunnel",
                 "narrow tunnel", "horribly narrow tunnel",
                 "horribly narrow dirt tunnel",
                 "narrow dirt tunnel", }),
        "Ugh! There isn't much to see here, and you decide not to"
      + " waste time on the scenery but instead keep crawling"
      + " forward.\n\n");
    add_item( ({ "dirt" }),
        "Yes. Lovely. Let's keep crawling!\n\n");

    add_prop(ROOM_M_NO_TELEPORT,
        "A strange force prevents your travel.\n");
    add_prop(ROOM_I_INSIDE, 1);
} /* create_dungeon_room */


/*
 * Function name:        choose_event
 * Description  :        choose a random event from the array and then
 *                       remove it
 * Returns      :        string - the event text
 */
public string
choose_event()
{
    string  this_event = one_of_list(Events);

    Events -= ({ this_event });

    return this_event + "\n\n";
} /* choose_event */


/*
 * Function name:        first_message
 * Description  :        first message for the player
 * Arguments    :        object who - the player
 */
public void
first_message(object who)
{
    who->catch_tell("You make your way slowly forward through a horribly"
      + " narrow dirt tunnel, crawling on your hands and knees.\n\n");
    set_alarm(6.0, 0.0, &second_message(who));

    return;
} /* first_message */


/*
 * Function name:        second_message
 * Description  :        second message for the  player
 * Arguments    :        object who - the player
 */
public void
second_message(object who)
{
    who->catch_tell(choose_event());
    set_alarm(6.0, 0.0, &third_message(who));

    return;
} /* second_message */


/*
 * Function name:        third_message
 * Description  :        third message for the  player
 * Arguments    :        object who - the player
 */
public void
third_message(object who)
{
    who->catch_tell(choose_event());
    set_alarm(6.0, 0.0, &fourth_message(who));

    return;
} /* third_message */


/*
 * Function name:        fourth_message
 * Description  :        fourth message for the player
 * Arguments    :        object who - the player
 */
public void
fourth_message(object who)
{
    who->catch_tell(choose_event());
    set_alarm(6.0, 0.0, &fifth_message(who));

    return;
} /* fourth_message */


/*
 * Function name:        fifth_message
 * Description  :        fifth message for the player
 * Arguments    :        object who - the player
 */
public void
fifth_message(object who)
{
    who->catch_tell(choose_event());
    set_alarm(6.0, 0.0, &sixth_message(who));

    return;
} /* fifth_message */


/*
 * Function name:        sixth_message
 * Description  :        sixth message for the player
 * Arguments    :        object who - the player
 */
public void
sixth_message(object who)
{
    who->catch_tell(choose_event());
    set_alarm(6.0, 0.0, &seventh_message(who));

    return;
} /* sixth_message */


/*
 * Function name:        seventh_message
 * Description  :        seventh message for the player
 * Arguments    :        object who - the player
 */
public void
seventh_message(object who)
{
    who->catch_tell(choose_event());
    set_alarm(6.0, 0.0, &eighth_message(who));

    return;
} /* seventh_message */

/*
 * Function name:        eighth_message
 * Description  :        eighth message for the player
 * Arguments    :        object who - the player
 */
public void
eighth_message(object who)
{
    who->catch_tell("You suddenly feel yourself crawling uphill ...\n\n");
    set_alarm(6.0, 0.0, &ninth_message(who));

    return;
} /* eighth_message */


/*
 * Function name:        ninth_message
 * Description  :        ninth message for the player
 * Arguments    :        object who - the player
 */
public void
ninth_message(object who)
{
    who->catch_tell("Without warning, you tumble out of a hole, roll down"
      + " a sharp incline and come to rest in a heap. Standing up,"
      + " you dust yourself off and blink in the light.\n");
    set_alarm(0.0, 0.0, &transfer(who));

    return;
} /* ninth_message */


/*
 * Function name:        transfer
 * Description  :        move the player to the new room
 * Arguments    :        object who - the player
 */
public void
transfer(object who)
{
    who->move_living("M", "/d/Genesis/start/human/wild2/orc_sett", 1, 1);

    tell_room(environment(who), QCTNAME(who) + " rolls suddenly into"
      + " the area. Standing up, " + who->query_pronoun()
      + " dusts " + who->query_objective() + "self off and blinks"
      + " in the light.\n", who);

    write_file(LOG_DIR + "escape",
        TIME2FORMAT(time(), "mm/dd/yyyy")
      + " (" + ctime(time())[11..18] + ") "
      + capitalize(this_player()->query_name())
      + " used the escape route " + FILE_NAME(MASTER) + ".\n");

    set_alarm(1.0, 0.0, &remove_object());
    return;
} /* transfer */


/*
 * Function name: enter_inv
 * Description:   Called when objects enter this container or when an
 *                object has just changed its weight/volume/light status.
 * Arguments:     ob: The object that just entered this inventory
 *                from: The object from which it came.
 */
public void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);

    set_alarm(6.0, 0.0, &first_message(ob));
    set_alarm(2.0, 0.0, &remove_amulet(ob));

    return;
} /* enter_inv */


/*
 * Function name:        remove_amulet
 * Description  :        Have players remove the amulet if they are
 *                       wearing it.
 * Arguments    :        object who - the player
 */
public void
remove_amulet(object who)
{
    mixed  amulet = present(AMULET, this_player());

    if (!amulet)
    {
        return;
    }

    if (!amulet->query_worn())
    {
        return;
    }

    who->catch_tell("The amulet around your neck catches beneath the weight"
      + " of your chest as you crawl, making going difficult.\n");
    who->command("remove " + AMULET);
    who->catch_tell("\n");
} /* remove_amulet */
