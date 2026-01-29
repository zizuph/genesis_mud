#include "/d/Krynn/common/defs.h"
#include "local.h"
#include <macros.h>

#define GNOME_NAME "Gnomish Inventors"

inherit "/std/room";

int step, triggered;
string str;

void
create_room()
{
    set_short("Flying through the air");
    set_long("@@mylong");
    INSIDE;
    LIGHT;
    triggered = 0;
}

int
query_busy() { return triggered; }

void
phase1(object who, int num)
{
    triggered = 1;
    step = num;
    who->catch_msg("With loud clanking noises, the padded seat you are in is" +
		   " cranked back.\n");
    set_alarm(itof(random(6)),0.0,"phase2", who);
}

void
phase2(object who)
{
    who->catch_msg("The foreman quickly looks up your weight on a chart he" +
		   " holds, and takes careful aim.\n");
    set_alarm(itof(random(6)),0.0,"phase3", who);
}

void
phase3(object who)
{
    who->catch_msg("With a sudden hiss of steam, you are flung into the air! " +
	"You hope these gnomes know what they're doing...\n");
    set_alarm(2.0,0.0,"phase4", who);
}

void
phase4(object who)
{
    int i;
    i = random(5);
    if (i == 0)
      who->catch_msg("Your whole life flashes before your eyes as you arc" +
		     " through the air...\n");
    else if (i == 1)
      who->catch_msg("You notice the net crew on floor " + step +
		     " frantically adjusting something as you fly towards them.\n");
    else if (i == 2)
      who->catch_msg("As you are flung up, you think you hear the" +
		     " foreman mutter: 'Oops.'\n");
    else if (i == 3)
      who->catch_msg("You think your ribs were flattened during takeoff," +
		     " but flying is actually quite a bit of fun!\n");
    else
      who->catch_msg("Your departure triggers a siren up on floor " + step +
		     " to notify them of your arrival.\n");
    set_alarm(itof(step + 2), 0.0,"whatfloor", who);
}

void
whatfloor(object who)
{
    int i, floor;
    object heap;

    while (step >= 1)
    {
        /* 2017-11-14 Malus: Tinkerers get special treatment and the
         * flinger works better for gnomes */
        if (who->query_guild_name_race() == GNOME_NAME
                || random((QRACE(who)) == "gnome") || random(step + 1))
        {
            who->catch_msg("The gnomes on floor " + step + 
                " send out a net as" +
                " you pass by.  It whips out, grabs you, and pulls you" +
                " in to the landing.\nThe gnomes dust you off and help" +
                " you to your feet.\n");
            floor = step;
            step = 0;
        }
        else
        {
            i = random(5);
            if (i == 0)
                who->catch_msg("The net at floor " + step +
                    " misses you entirely!" +
                    "  You fall toward the ground...\n");
            else if (i == 1)
                who->catch_msg("The Net Guild representatives of floor " + 
                    step + " watch in horror as you fall past them. A heated" +
                    " dispute breaks out.\n");
            else if (i == 2)
                who->catch_msg("Moments too soon, the net from floor " + step +
                    " whips out to catch you. By the time you reach it," +
                    " it is gone...\n");
            else if (i == 3)
                who->catch_msg("A gnome watches you fall past the floor " +
                    step +
                    " landing.\n'Oh', he says, 'TheyMeantRightNOW...'\n");
            else
                who->catch_msg("The net from floor " + step +
                    " jams. You graze it" +
                    " as you plummet past.\n");
            step--;
        }
    }
    if (!floor)
    {
        who->catch_msg("Sirens start ringing as you fall past the first floor.\n" +
            "You watch as thousands of sponges spill out onto the " +
            "cavern floor below you.\n");
        heap = clone_object(OBJ + "sponge");
        heap->move(TDIR + "cavern5");
        who->move_living("crashing into the sponges", TDIR + "cavern5");
        who->catch_msg("The sponges break your fall as you land.  You sit up" +
            " dazedly...\n");
    }
    else
    {
        who->move_living("onto the landing", TDIR + "cavern" + floor + "1");
        who->catch_msg("A gnome says: Isn'tTechnologyWonderful?\nThe gnome "
            + "smiles happily.\n");
    }
    triggered = 0;
}

string
mylong()
{
    string str;
    if (triggered)
      str = BS("You are in transit from the gnomeflinger on the " +
	       "ground floor to floor " + step + ".  With a little luck, you " +
	       "might even make it...", 70);
    else
      str = "You take a seat in the catapult's launch seat.\n";
    return str;
}

