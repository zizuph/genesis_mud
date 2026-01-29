/*
   Wayreth.

   meditation.c
   ------------

   Coded ........: 95/06/02
   By ...........: Jeremiah

   Latest update : 95/08/08
   By ...........: Jeremiah

*/

#include "/d/Krynn/wayreth/local.h"
#include "/d/Krynn/common/defs.h"
#include <macros.h>

inherit TOWERROOM;
inherit "/lib/guild_support";


void
create_tower_room()
{
   set_short("Meditation room");
   set_long("You are standing in a strangely quiet room. The light " +
            "is pleasantly dim and there is an atmosphere of tranquility " +
            "in here. A large circle, bordered with ancient runes, has " +
            "been carved into the dark floor. Entering the circle will " +
            "make it possible for you to meditate and choose where to " +
            "focus your learning. To the north is the sleeping quarters " +
	    "of Wayreth Tower.\n");

   create_guild_support();
   set_wall_type(2);

   add_item(({"circle","large circle","large magic circle","magic circle"}), 
            "This is a large magic circle carved into the " +
            "floor. The circle is large enough for several persons to " +
            "enter it at the same time. Magic runes of protection have " +
            "been carved into the floor all along the perimeter of the " +
            "circle.\n");

   add_item("runes", "Magic runes of protection carved into the floor " +
            "along the inside of the circle perimeter. These runes will " +
            "protect anyone entering the circle, giving the person the " +
            "necessary peace to meditate.\n");

   add_item("floor", "The floor is of the same dark obsidian as the walls " +
            "of this tower. A large circle has been carved into the floor " +
            "in here.\n");

   add_exit(WTOWER + "training", "east", "@@remove_medi_props");
   add_exit(WTOWER + "sleeproom", "north", 0);
   add_exit(WTOWER + "equiproom", "south", "@@check_entry_ban");
}


int
remove_medi_props()
{
    TP->remove_prop(LIVE_I_MEDITATES);
    TP->remove_prop(LIVE_S_EXTRA_SHORT);
}


void
init()
{
    ::init();
    init_guild_support();
    add_action("gs_meditate", "enter");
}


int
gs_meditate(string what)
{
    string *med_cmds; /* Valid strings to enter the magic circle */
                      /* to start meditating.                    */

    med_cmds = ({ "circle", "Circle", "magic circle", "Magic circle",
                  "the circle", "the large circle", "large circle",
                  "in the circle","in the large circle","in circle"});

    NF("Enter what? The large circle?\n");

    if(!what)
       return 0;

    if(member_array(what, med_cmds) == -1)
       return 0;

    return ::gs_meditate();
}


void
gs_hook_start_meditate()
{
    write("You enter the large magic circle and slowly kneel down. " +
          "You start to concentrate solely upon your own mind and you " +
          "block off all your senses. A feeling of great ease and self " +
          "control falls upon you as you slowly sink into a deep " +
          "trance. You can now <estimate> your different stats and <set> " +
          "the learning preferences at your own desire. Just <rise> " +
          "when you are done meditating.\n");

    say(QCTNAME(TP) + " enters the large magic circle and slowly kneels " +
          "down. " + C(PRONOUN(TP)) + " sinks into a deep trance and " +
          "seems lost to the world around " + OBJECTIVE(TP) + ".\n"); 
}


int
gs_hook_rise()
{
    write("As if ascending from a great depth, you rise to the surface " +
          "of your consciousness. You exhale and feel very relaxed as " +
          "you get up and prepare yourself for whatever may lie ahead. " +
          "You slowly leave the large magic circle.\n");

    say(QCTNAME(TP) + " slowly surfaces from a deep trance. " +
          C(PRONOUN(TP)) + " slowly rises and leaves the large magic " +
          "circle.\n"); 
}


void
leave_inv(object ob, object to)
{
   gs_leave_inv(ob, to);
   ::leave_inv(ob, to);
}
