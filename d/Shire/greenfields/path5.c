inherit "/d/Shire/eastroad/std/er_base";
#include "/d/Shire/common/defs.h"
#include "/sys/stdproperties.h"
#include "/sys/macros.h"
#include <ss_types.h>


#define EXIT1 GREEN_DIR + "camp/entrance","north","@@north@@"
#define EXIT2 GREEN_DIR + "path4","east",0,1

int
north()
{
    int ran, skill;
    ran = random(70);
    skill = TP->query_skill(SS_CLIMB);
    if(ran > skill)  /* Some failure */
    {
	write("You trip as you try to climb up the slippery slope.\n");
	say(QCTNAME(TP)+" tries to climb up the slope but slides down again.\n");
	TP->add_fatigue(-10);
	return 1;
    }
    return 0;

}

void
create_er_room()
{

    area = "a good bit from";
    areaname = "Greenfields";
    land = "the Shire";
    areatype = 5;
    areadesc = "canyon";
    grass = "brown";


    extraline = "The hills here in this canyon are very steep and rocky.  "+
    "Echoes play tricks on your mind here, it is almost as if you hear "+
    "hundreds of voices whispering to you, beckoning you nearer.  The "+
    "slope to the east is the easiest grade, and the only other possible "+
    "movement is north, apparently where these noises come from.";

    add_item(({"canyon","hills","rock","slope","grade"}),
      "The canyon you stand in is nearly a box canyon, but for the two lower "+
      "sides that lead east and north respectively.  These lower sides offer the "+
      "gentlest gradient and most probable means of succeeding in leaving this "+
      "eerie place.\n");

    add_exit(EXIT1);
    add_exit(EXIT2);

}

