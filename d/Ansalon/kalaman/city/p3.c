#include "/d/Ansalon/common/defs.h"
#include "../local.h"
#include <macros.h>
#include <stdproperties.h>

inherit KALAMAN_IN;

object c1;

void
reset_kalaman_room()
{
    if(!objectp(c1))
    {
	c1 = clone_object(KNPC + "chamberlain");
	c1->arm_me();
	c1->move(TO);
    }
}

void
create_kalaman_room()
{
    set_long("@@long_descr");
    set_short("Within the palace of Kalaman before a spiral staircase");

    add_item(({"spiral staircase","staircase"}),
      "A graceful spiral staircase leads up to the floor above.\n");
    add_item(({"hallway","hallways"}),
      "Hallways lead away from here to the northeast and northwest.\n");
    add_item(({"servants wing","servants' wing"}),
      "To the northwest is the Servant's Wing.\n");
    add_item(({"guests wing","guests' wing"}),
      "To the northeast is the Guests' Wing.\n");
    add_item(({"tapestry","red tapestry","bright red tapestry"}),
      "This beautiful tapestry woven with fine red wool has the " +
      "Canticle of the Dragon embroidered into it. You " +
      "could read it if you wanted to.\n");

    add_cmd_item(({"tapestry","canticle of the dragon"}),
      "read","@@read_tapestry");

    add_exit(CITY + "p2","north",0);
    add_exit(CITY + "p5","northwest","@@servant");
    add_exit(CITY + "p4","northeast","@@guest");
    add_exit(CITY + "p4","up","@@go_up");

    reset_kalaman_room();
}

int
go_up()
{
    if(objectp(c1) && E(c1) == TO)
    {
	if(TP->query_knight_level())
            if(TP->query_knight_sublevel() == 10)
	    {
		c1->command("say Greetings " +TP->query_knight_subtitle()+ ". " +
		  "Lord Calof will see you.");
		write("The chamberlain lets you pass up the stairs.\n");
		return 0;
	    }
	if(!CAN_SEE(c1, TP))
	{
	    write("The solemn chamberlain doesn't notice you " +
	      "sneaking up the stairs.\n");
	    return 0;
	}
	write("The solemn chamberlain stops you from " +
	  "climbing the stairs.\n");
	say(QCTNAME(TP) + " is stopped by the chamberlain from " +
	  "climbing the stairs.\n");
	c1->command("say I am sorry, but Lord Calof " +
	  "is not to be disturbed.");
	return 1;
    }
    return 0;
}

int
servant()
{
    write("You peer down the hallway to the northwest, and " +
      "see nothing but servants running around doing whatever " +
      "it is servants do. You decide not to go down that way.\n");
    say(QCTNAME(TP) + " peers down the hallway to the northwest, " +
      "but sees nothing of interest.\n");
    return 1;
}

int
guest()
{
    write("You look down the hallway to the northeast " +
      "to where the Guests' Wing is, but see nothing " +
      "down there that interests you.\n");
    say(QCTNAME(TP) + " looks down the hallway to the " +
      "northeast, but seems to loose interest in whatever " +
      "is down there.\n");
    return 1;
}

string
long_descr()
{
    return "You stand within the palace of Kalaman. Here a " +
    "spiral staircase leads up to the next floor, while to " +
    "the northeast a hallway leads away to the Guests' Wing, and to " +
    "the northwest a hallway leads away to the Servants' Wing. " +
    "A bright red tapestry hangs on the southern wall.\n";
}

string
read_tapestry()
{
    TP->more("You read the Canticle of the Dragon from the tapestry:\n"+
	"\n" +
	"     Hear the sage as his song descends\n" +
	"     like heaven's rain or tears,\n" +
	"     and washes the years, the dust of the many stories\n" +
	"     from the High Tale of the Dragonlance.\n" +
	"     For in ages deep, past memory and word,\n" +
	"     in the first blush of the world\n" +
	"     when the three moons rose from the lap of the forest,\n" +
	"     dragons, terrible and great,\n" +
	"     made war on the world of Krynn.\n\n" +
	"     Yet out of the darkness of dragons,\n" +
	"     out of our cries for light\n" +
	"     in the blank face of the black moon soaring,\n" +
	"     a banked light flared in Solamnia,\n" +
	"     a knight of truth and of power,\n" +
	"     who called down the gods themselves\n" +
	"     and forged the mighty Dragonlance, piercing the soul\n" +
	"     of dragonkind, driving the shade of their wings\n" +
	"     from the brightening shores of Krynn\n\n" +
	"     Thus Huma, Knight of Solamnia,\n" +
	"     Lightbringer, First Lancer,\n" +
	"     followed his light to the foot of the Khalkist Mountains,\n" +
	"     to the stone feet of the gods,\n" +
	"     to the crouched silence of their temple.\n" +
	"     He called down the Lancemakers, he took on\n" +
	"     their unspeakable power to crush the unspeakable evil,\n" +
	"     to thrust the coiling darkness\n" +
	"     back down the tunnel of the dragon's throat.\n\n" +
	"     Paladine, the Great God of Good,\n" +
	"     shone at the side of Huma,\n" +
	"     strengthening the lance of his strong right arm,\n" +
	"     and Huma, ablaze in a thousand moons,\n" +
	"     banished the Queen of Darkness,\n" +
	"     banished the swarm of her shrieking hosts\n" +
	"     back to the senseless kingdom of death, where their curses\n" +
	"     swooped upon nothing and nothing\n" +
	"     deep below the brightening land.\n\n" +
	"     Thus ended in thunder the Age of Dreams\n" +
	"     and began the Age of Might,\n" +
	"     When Istar, kingdom of light and truth, arose in the east,\n" +
	"     where minarets of white and gold\n" +
	"     spired to the sun and to the sun's glory,\n" +
	"     announcing the passing of evil,\n" +
	"     and Istar, who mothered and cradled the long summers of good,\n" +
	"     shone like a meteor\n" +
	"     in the white skies of the just.\n\n" +
	"     Yet in the fullness of sunlight\n" +
	"     the Kingpriest of Istar saw shadows:\n" +
	"     At night saw the trees as things with daggers, the streams\n" +
	"     blackened and thickened under the silent moon.\n" +
	"     He searched books for the paths of Huma,\n" +
	"     for scrolls, signs, and spells\n" +
	"     so that he, too, might summon the gods, might find\n" +
	"     their aid in his holy aims,\n" +
	"     might purge the world of sin.\n\n" +
	"     Then came the time of dark and death\n" +
	"     as the gods turned from the world.\n" +
	"     A mountain of fire crashed like a comet through Istar,\n" +
	"     the city split like a skull in the flames,\n" +
	"     mountains burst from once furtile valleys,\n" +
	"     seas poured into the graves of mountains,\n" +
	"     the deserts sighed on abandoned floors of the seas,\n" +
	"     the highways of Krynn erupted\n" +
	"     and became the paths of the dead.\n\n" +
	"     Thus began the Age of Despair.\n" +
	"     The roads were tangled.\n" +
	"     The winds and sandstorms dwelt in the husks of cities,\n" +
	"     The plains and mountains became our home.\n" +
	"     As the old gods lost their power,\n" +
	"     we called to a blank sky\n" +
	"     into the cold, dividing gray to the ears of the new gods.\n" +
	"     The sky is calm, silent, unmoving.\n" +
	"     We have yet to hear their answer.\n\n");

    return "";
}
