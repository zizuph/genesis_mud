/*
 * Filename:  dragonadmin.c
 * Thanks to the same file in Neraka
 *
 *
 */

/* dragonadmin.c
 * Carridin, 27 Nov 97
 * This is the bugger-o admin thingy for random dragonattacks in Neraka
 * Updated 18 Jan 97, Ashlar
 * Added min stat to be attacked, and young dragons, and colour distribution.
 */

inherit "/std/room";

#include <stdproperties.h>
#include <macros.h>
#include <files.h>
#include "/d/Krynn/common/defs.h"
#include "../local.h"

object dragon;
object draconian1;
object draconian2;

int dragon_cloned = 0;
int alarm_id;
int idleness;

/* Prototypes */
void dragon_attack(object *list);
void draconian_attack(object *list);
void dragon_flyby();
void check_for_dragonattack();

/* filter function */
static int
tn_filter(object ob, string *subdir, string basedir)
{
    object e;
    int i;
    string f;

    e = environment(ob);
    if (!e)
        return 0;

    f = file_name(e);

    for (i = 0; i < sizeof(subdir); i++)
    {
        //tell_room(TO, "/d/Krynn/" + basedir + "/" + subdir[i] + "*");
        if (wildmatch("/d/Krynn/" + basedir + "/" + subdir[i] + "*", f))
        {
            tell_room(TO, "Found " + ob->short() + " in " + f + "\n");
            return 1;
        }
    }
    return 0;
}

/*
 * Function name: tell_area
 * Description:   sends a message to players on icewall
 * Arguments:     mixed subdir
 *                      string - to players in that subdir
 *                      string * - to players in the subdirs in the array
 *                mixed message
 *                      string - message to send
 *                      string * if io = 3, then the first item is outside
 *                              message, the second is inside message
 *                int io
 *                      1 - send to outside rooms only
 *                      2 - send to inside rooms only
 *                      3 - send to inside and outside rooms
 *                object *exclude
 *                      an array of rooms not to send the message to
 * Returns:       (object *) the players that were within the rooms
 */
varargs public object *
tell_area(mixed subdir, mixed message, int io = 1, object *exclude = ({ }),
                           string basedir = "icewall")
{
    object *p;
    int i;

    if (stringp(subdir))
        subdir = ({ subdir });

    p = filter(users(), &tn_filter(,subdir,basedir));

    for (i = 0; i < sizeof(p); i++)
    {
        if (member_array(E(p[i]), exclude) >= 0)
            continue;

        if (io == 1 && !E(p[i])->query_prop(ROOM_I_INSIDE))
        {
            p[i]->catch_msg( stringp(message) ? message : message[0] );
        }
        else if (io == 2 && E(p[i])->query_prop(ROOM_I_INSIDE))
        {
            p[i]->catch_msg( stringp(message) ? message : message[0] );
        }
        else if (io == 3)
        {
            if (!E(p[i])->query_prop(ROOM_I_INSIDE))
            {
                p[i]->catch_msg( stringp(message) ? message : message[1] );
            }
            else
            {
                p[i]->catch_msg( stringp(message) ? message : message[0] );
            }
        }
    }
    return p;
}

void
create_room()
{
    set_short("Dragonattack admin");
    set_long("This is the administration object for dragonattacks on " +
        "Icewall.\n");

    alarm_id = set_alarm(1.0, 60.0, check_for_dragonattack);
}

/*
 * Function name: check_for_dragonattack
 * Description: checks for mortals in Neraka that can be attacked
 */
void
check_for_dragonattack()
{
    object *obs;
    object *obs2;
    object *list = ({ });
    object *list2 = ({ });
    int i;
    string s;

    tell_room(TO, "Function check_for_dragon_attack() called\n");

    if (objectp(dragon))
    {
        if (dragon->query_attack())
            idleness = 0;
        else if (++idleness > 1)
        {
            tell_room(E(dragon), "The dragon takes to the skies!\n");
            dragon->remove_object();
            dragon_cloned = 0;
            idleness = 0;
        }
        tell_room(TO, "Exiting function check_for_dragon_attack()\n");

        return;
    }

    obs = users();
    for(i=0;i<sizeof(obs);i++)
    {
        if(E(obs[i]) && !E(obs[i])->query_prop(ROOM_I_INSIDE) &&
            (obs[i]->query_average_stat() > 80))
        {
        if( wildmatch("*/icewall/*", file_name(E(obs[i]))) )
            {
                list += ({ obs[i] });
            }
        }
    }

    obs2 = users();
    for(i=0;i<sizeof(obs2);i++)
    {
        if(E(obs2[i]) && E(obs2[i])->query_prop(ROOM_I_INSIDE) &&
            (obs2[i]->query_average_stat() > 80) )
        {
        if( wildmatch("*/icewall/*", file_name(E(obs2[i]))) )
            {
                list2 += ({ obs2[i] });
            }
        }
    }


    switch (random(100))
    {
        case 0..8:
            if (sizeof(list) == 0)
            {
                tell_room(TO, "Exiting function check_for_dragon_attack(): (1) No players to scare\n");
                return;
            }
            dragon_attack(list);    /* Attack a player */
        break;
        case 9..13:
            if (sizeof(list2) == 0)
            {
                tell_room(TO, "Exiting function check_for_dragon_attack(): (2) No players to scare\n");
                return;
            }
            draconian_attack(list2);    /* Attack a player */
        break;
        case 70..99:    dragon_flyby();     /* Send a text message to all of neraka */
        break;
        default:
        tell_room(TO, "Exiting function check_for_dragon_attack(): Nothing to do\n");
    }
}

/*
 * Function name: dragon_attack
 * Description:   Starts an attack on a randomly chosen player
 * Arguments:     object *list - list of players in Neraka
 */
void
draconian_attack(object *list)
{
    int firstDracMsg = 0;
    object player = list[random(sizeof(list))];
    string *col = ({"white","white"});
    string setcol = col[random(sizeof(col))];

    tell_room(TO, "Function draconian_attack() called\n");

    if ( !objectp(draconian1) && !(E(player)->query_prop(NO_DRAGON_ATTACK)))
    {
        draconian1 = clone_object("/d/Krynn/std/aurak.c");

        draconian1->set_color(setcol);


        draconian1->heal_hp(dragon->query_max_hp());
        draconian1->move_living("M", E(player));
        draconian1->set_agressive(1);


        if (player->query_average_stat() > 170)
        {
            draconian1->set_hunting(player);
            draconian2->set_hunting(player);
        }

        if (draconian1)
        {
            firstDracMsg = 1;
            tell_room(E(player), "\nAn evilfaced draconian comes storming at you!\n\n");
            draconian1->command("kill " + player->query_real_name());

        }
    }

    if ( !objectp(draconian2) && !(E(player)->query_prop(NO_DRAGON_ATTACK)) )
    {
        draconian2 = clone_object("/d/Krynn/std/sivak.c");
        draconian2->set_color(setcol);
        draconian2->heal_hp(dragon->query_max_hp());
        draconian2->move_living("M", E(player));
        draconian2->set_agressive(1);

        if (player->query_average_stat() > 170)
        {
            draconian2->set_hunting(player);
        }

        if (draconian2)
        {
            if (firstDracMsg)
            {
                tell_room(E(player), "\nOh no! An uglyfaced draconian comes running!\n\n");
                firstDracMsg = 0;
            }
            else
            {
                 tell_room(E(player), "\nAn uglyfaced draconian comes storming at you!\n\n");
            }

            draconian2->command("kill " + player->query_real_name());

        }
    }
}

/*
 * Function name: dragon_attack
 * Description:   Starts an attack on a randomly chosen player
 * Arguments:     object *list - list of players in Neraka
 */
void
dragon_attack(object *list)
{
    object player = list[random(sizeof(list))];
    string *age = ({"young","young","adult","adult","adult"});
    string *col = ({"white","white"});
    string setage = age[random(sizeof(age))];
    string setcol = col[random(sizeof(col))];

    tell_room(TO, "Function dragon_attack() called\n");

    if (!objectp(dragon) && !dragon_cloned && !(E(player)->query_prop(NO_DRAGON_ATTACK)))
    {
        dragon = clone_object("/d/Krynn/icewall/castle2/npc/attackdragon.c");
        dragon->set_colour(setcol);
        dragon->set_age(setage);
        dragon->set_aggressive(1);
        dragon->heal_hp(dragon->query_max_hp());
        dragon->move_living("M", E(player));
        dragon_cloned = 1;

        if (player->query_average_stat() > 130)
            dragon->set_hunting(player);

        if (dragon)
        {
            tell_room(E(player), "\nWith an blood-chilling shriek, a great " + dragon->query_colour() +
                " dragon swoops down on you from the skies above.\n\n");
            dragon->command("kill " + player->query_real_name());

        }
    }
    else
        tell_room(TO, "Else on: !objectp(dragon) && !dragon_cloned\n");
}

/*
 * Function name: dragon_flyby
 * Description: Sends a message to Neraka
 */
void
dragon_flyby()
{
    tell_room(TO, "Function dragon_flyby() called\n");
    switch (random(5))
    {
        case 0: tell_area("", ({"You hear someone hissing angrily close by.\n",
            "A great shadow sweeps past you on the ground.\n"}),3);
        break;
        case 1: tell_area("", ({"You feel someone trying to take control of " +
                            "your mind...\nAn evilfaced draconian attacks you!\n" +
                            "No, its all in your head.\n",
            "Something in the sky far above you " +
            "catches your eye, but when you look again, it's gone.\n"}),3);
        break;
        case 2: tell_area("", ({"You can hear a patrol walking somewhere.\n",
            "Above you, a great dragon swoops by. " +
            "As the beast flies away, you give a sigh of relief.\n"}),3);
        break;
        case 3: tell_area("", ({"Someone shouts: Hurry! Lets get this over with.\n",
            "A flight of dragons glides through the skies.\n"}),3);
        break;
        case 4: tell_area("", ({"An evilfaced draconian comes storming at you!\n" +
            "No, its just in your mind playing games with you.\n",
            "A lone dragon flies through the skies above Icewall.\n"}),3);
        break;
    }
    TP->add_panic(TP->query_average_stat() - (TP->query_stat(5) / 3));
}




void
reset_room()
{
    tell_room(TO, "Function reset_room() called\n");
    if (!objectp(dragon))
         dragon_cloned = 0;

    if (!get_alarm(alarm_id))
        alarm_id = set_alarm(1.0, 60.0, check_for_dragonattack);

}
