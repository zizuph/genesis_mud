inherit "/std/room";
#include "/d/Cirath/common/defs.h"
#include "/d/Cirath/common/teamer.h"
#include "/d/Cirath/tyr/tyr.h"
#include "wbt.h"

void
reset_room()
{
	bring_room_team(WWORK+"guard.c", 1, 1, WWORK+"guard.c", 1);
}

void
create_room()
{
   set_short("Entrance to Warriors School");
   set_long("Before you stands a large marble gate, which "
	+"is open.  Loud noises of combat come from inside "
	+"the gate, along with shouted instructions.  Beyond "
	+"the gate you can see a large building surrounding "
	+"a courtyard where young men seem to be training in "
	+"martial skills.  As they practice, from time to time "
	+"you see an older person you assume to be an instructor "
	+"approach and strike them with blunt swords.  You notice "
	+"a bronze plaque attached to the gate that appears to "
	+"have some words on it.\n");
   add_item("gate","This large marble gate is wide open "
	+"giving a good view of what appears to be a school of "
	+"some sort.  There is a bronze plaque attached "
	+"to the gate as well.\n");
   add_item("building","The building resembles a two story "
	+"barracks basically.\n");
  add_item("courtyard","The courtyard seems to be hard packed "
	+"earth, on which young men are practicing with "
	+"weapons.\n");
   add_item(({"men","young men"}),"They are practicing with "
	+"weapons in the courtyard.\n");
   add_item(({"person","older person","instructor"}),"They "
	+"are patrolling the courtyard and watching over the "
	+"young people that are practicing.\n");
   add_item(({"plaque","bronze plaque"}),"It appears to have "
	+"words on it, in addition to the picture drawing which seems "
	+"to represent a school of fighting.\n");
   add_cmd_item("plaque","read","The plaque reads:\n"
	+"The Warrior School of Tyr.\n");
	
	ADD_SUN_ITEM;
	OUTSIDE;

   add_exit(WWORK+"ent2","west");
   add_exit(TYR_WARREN+"rd_vr_05","east");
    set_alarm(1.0,0.0,"reset_room");
}
