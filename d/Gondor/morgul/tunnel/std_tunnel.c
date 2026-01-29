/*
 * This room is the standard room of the tunnel under the Morgulduin,
 * connecting the lair of Shelob, Torech Ungol with Minas Morgul.
 * It adds some properties and descriptions and sound dies it it!
 * Copied from std_lair by Mercade.
 *
 * Olorin, 07-oct-1993
 */

/*
 * This room doesn't use the time function by Elessar Telcontar for the lair
 * is too dark to see anything... The only thing you can do here is the
 * estimate the time of day.
 */
inherit "/std/room";
#include "/sys/stdproperties.h"
#include "/d/Gondor/defs.h"

/*
 * This function defines the room.
 */
varargs void
make_the_room(string extra_long)
{
    if (!extra_long) { extra_long = ""; }

    set_name("tunnel");
    set_short("Inside a tunnel");
    set_long(BSN(
        "Inside this tunnel there is nothing but darkness. " +
        "The air is still, stagnant, heavy and sound falls dead. " +
        "Sniffing the air you are overcome by a terrible smell. " +
        extra_long));

    add_item(({"cave", "tunnel"}), BSN("The darkness here prevents you to see " +
        "much of this tunnel. You feel evil lurking in the dark and wonder " +
        "what peril might be waiting for you."));
    add_item(({"wall", "walls"}), BSN(
        "The walls are carved out of the living rock. They feel remarkably " +
        "smooth. The dark rock seems to swallow all light in the room. "));
    add_item(({"floor", "ground"}), BSN("As you move around, you stumble " +
        "over rocks all over the floor."));
    add_item(({"roof", "ceiling"}), BSN("The ceiling is too high for you to " +
        "reach."));
    add_item(({"rock", "rocks"}), BSN("There are many rocks in this tunnel, " +
        "some of them are big, some are smaller. There is nothing special " +
        "about them though."));
    add_item("air", BSN("Even though the air in this tunnel is stagnant and " +
        "heavy, it cannot be seen. In fact you cannot see more than darkness " +
        "here, but there is a difference between air and darkness."));
    add_item("darkness", BSN("You are really curious are to what darkness " +
        "looks like."));

    add_prop(ROOM_I_TYPE, ROOM_NORMAL);
    add_prop(ROOM_I_INSIDE, 1);
    add_prop(ROOM_I_LIGHT, -1);
}

/*
 * Sound dies in the tunnel. (and you'd better not try to smell the air.)
 */
void
init()
{
    ::init();

    /*
     * If you try to give the time-command.
     */
    add_action("do_time_in_tunnel", "time");

    /*
     * the next add_actions are to make sure that no sound is heard in this
     * tunnel.
     */
    add_action("do_no_sound_in_tunnel", "whisper");
    add_action("do_no_sound_in_tunnel", "shout");
    add_action("do_no_sound_in_tunnel", "say");
    add_action("do_no_sound_in_tunnel", "grsay");
    add_action("do_no_sound_in_tunnel", "mumble");
    add_action("do_no_sound_in_tunnel", "ksay");
    add_action("do_no_sound_in_tunnel", "aasay");
    add_action("do_no_sound_in_tunnel", "dsay");
    add_action("do_no_sound_in_tunnel", "rasp");
    add_action("do_no_sound_in_tunnel", "hiss");
    add_action("do_no_sound_in_tunnel", "'", 1);
    add_action("do_no_sound_in_tunnel", "ask");
    add_action("do_no_sound_in_tunnel", "scream");
    add_action("do_no_sound_in_tunnel", "cry");
    add_action("do_no_sound_in_tunnel", "swear");
}

/*
 * Only with a 50 percent change, you are heard in the tunnel. The write,
 * return 1; construct is used to block speech etc. Wizards aren't affected
 * of course.
 * Since 'dwarves are a loud race' (Xeros), they fall silent only with
 * a 33% chance.
 */
int
do_no_sound_in_tunnel(string str)
{
    if(TP->query_race_name()=="dwarf")
    {
      if(random(3))
        return 0;
    }
    else if(random(2))
    {
        return 0;
    }
    write(BSN("The air is so heavy in this cave that the sound you " +
        "make dies out before anyone can hear it."));
    if(TP->query_wiz_level())
    {
        write("As a wizard, you are not affected, though.\n");
        return 0;
    }
    return 1;
}

/*
 * If you try to give the time-command.
 */
int
do_time_in_tunnel(string str)
{
    write(BSN("You guess it is " + call_other((CLOCK),
        "query_time_of_day") + " now, but since you are in this dark cave, " +
        "you cannot estimate the time more precisely."));
    return 1;
}
