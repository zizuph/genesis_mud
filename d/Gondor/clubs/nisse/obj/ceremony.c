/*
 *  /d/Gondor/clubs/nisse/obj/ceremony.c
 *
 *  This file contains joining ceremony of the Nisse Ohtar club. It is
 *  bound to nisse_admin.c file.
 *
 *  Deagol, March 2003
 */

#pragma save_binary
#pragma strict_types

#include <stdproperties.h>
#include <macros.h>

#include "/d/Gondor/defs.h"
#include "../nisse_defs.h"

/*
 *  Global variables
 */
int	alarm_id = 0;
object	paralyze;
string	*lines = ({
    "You see dozens of hawks soaring and circling in the skies above you. " +
        "One by one they swoop over your head, pulling up just inches " +
        "away from you. It seems as if each one is evaluating you for some " +
        "reason.\n",
    "A young tan hawk begins to circle lower and lower, screeching " +
        "inquisitively, demanding that you understand her.\n",
    "Swooping downward, her talons stretched out, she lands upon your " +
        "shoulder.\n",
    "The talons of the hawk cause you pain, but lost in what you see, you " +
        "barely notice.\n",
    "The hawk stares at you, and your eyes are drawn to hers. The " +
        "unblinking yellow eyes of the hawk seem to mesmerize you, and you " +
        "find yourself falling into their depths.\n",
    "Suddenly you break free of your mortal body shivering in the pool " +
        "and fly as one with the hawk. She launches into the air taking " +
        "your soul with her.\n",
    "You soar through the skies riding thermal winds free and wild. The " +
        "people below you seem like tiny beings as they scurry across the " +
        "plains.\n",
    "You see the city of Pelargir and the mighty Anduin flowing endlessly.\n",
    "You see the White City on the far horizon and feel yourself swoop " +
        "and dive as the hawk circles its huge spires. You see the wild " +
        "forests and the peak of Amon Din.\n",
    "Spotting something moving among the ocean of greenery, the hawk swoops " +
        "shrieking fiercely. You feel the thrill of the hunt and the kill, " +
        "and the warm, wet satisfaction of a full crop and the sluggishness " +
        "that comes after a meal.\n",
    "As your journey continues, you hear your own heart beating exactly " +
        "in time with that of the hawk, your hearts and souls becoming " +
        "one, forever intertwined.\n",
    "You soar over the Shire and the fisher folk who dwell there, and then " +
        "eastward toward the Bruinen and the hidden valley of Imladris.\n",
    "The strangeness begins to overwhelm you and you start to panic and " +
        "falter in the air. You hear the soothing inner voice of your hawk " +
        "calming you and pulling you back toward the connection you now " +
        "share.\n",
    "You see the Misty Mountains below you and then the dark mysteries " +
        "of Mirkwood. You stare in awe at the wonders of Ithilien and the " +
        "bleak terror that is Minas Morgul.\n",
    "You swoop down toward a ship docked at the Fords of Poros and head " +
        "along the shoreline to the south.\n",
    "You speed along the shoreline, close to the water, seeing the fishes " +
        "beneath you and feeling the cool breeze of the sea air beneath " +
        "your wings.\n",
    "You soar upwards again as you approach the southern tip of Pelargir " +
        "and suddenly the camp of the Nisse Ohtar comes once more into " +
        "view.\n",
    "You circle the camp a few times before coming to rest upon your own " +
        "shoulder again.\n",
    "You feel yourself drain once more into your own body, but the " +
        "connection to your hawk remains strong.\n",
    "The pain of the hawk's talons in your shoulder is suddenly very " +
        "present and real. You feel the talons dig into your shoulder " +
        "blade as the hawk launches once more into the sky, this time " +
        "leaving you behind.\n",
    });

/*
 *  Function name: display_sequence
 *  Description  : This routine displays a vision for the player.
 *  Arguments    : object player - the player who is joining
 *                 int line - line of string lines (defined beyond)
 */
void
display_sequence(object player, int line)
{
    alarm_id = 0;

    player->catch_tell(lines[line] + "\n");

    line++;
    if (line < sizeof(lines))
    {
        alarm_id = set_alarm(9.0, 0.0, &display_sequence(player, line));
    }
    else
       {
            player->catch_msg("You emerge from the pool.\n\n");
            tell_room(NISSE_ROOM_DIR + "o_pool", QCNAME(TP) + " emerges " +
                "from the pool and appears suddenly beside you.\n");
            tell_room(NISSE_ROOM_DIR + "o_pool", "A tan hawk feather falls " +
                "down from the sky and " + QNAME(TP) + " catches it " +
                "skillfully.\n");
            paralyze->remove_object();
            player->move_living("M", NISSE_ROOM_DIR + "o_pool", 1, 0);
            player->catch_msg("A tan hawk feather falls down from the sky " +
                "and you catch it skillfully.\n");
       }
}

/*
 *  Function name: start_ceremony
 *  Description  : Runs the ceremony, paralyze the player and moves her
 *                 to the i_pool.c.
 *  Returns      : 0/1
 */
int
start_ceremony()
{
    object	player;
    string	name;

    setuid();
    seteuid(getuid());
    
    player = TP;
    name = player->query_real_name();
    
    if (!strlen(name))
    {
        return 0;
    }

    paralyze = clone_object("/std/paralyze");
    paralyze->set_stop_object(0);
    paralyze->set_stop_fun(0);
    paralyze->set_remove_time(190); // to be sure the paralyze will be removed
    paralyze->set_stop_verb(0);
    paralyze->set_fail_message("You are in a trance, you cannot do this.\n");
    paralyze->set_stop_message(0);
    paralyze->move(TP, 1);

    player->move_living("M", NISSE_ROOM_DIR + "i_pool", 1, 1);
    display_sequence(TP, 0);

    return 1;
}
