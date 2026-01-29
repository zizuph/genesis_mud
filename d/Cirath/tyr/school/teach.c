#include "/d/Cirath/common/defs.h"
inherit "/std/room";
#include <wa_types.h>
#include "wbt.h"

void
create_room()
{
   set_short("Teachers' Sleeping Chamber");
   set_long("This is the room that the teachers at the school "
	+"all share.  It is much nicer than the other "
	+"dormitories you have seen thus far in the school. "
	+"It appears as if there is enough space for each teacher "
	+"to have a bed, desk, and chest.  The teachers "
	+"quarters are seperated from the adepts chambers and "
	+"are protected by guards.  There are thick wooden "
	+"doors here that help keep the noise of practicing "
	+"students out.  One thing that catches your eye here "
	+"is the pictures placed around the room.\n");
   add_item("bed","It is a simple wooden bedframe with a "
   +"simple mattress on it.  The mattress looks like "
	+"it is probably made of some form of fabric with a "
	+"light filling in it.  Simple, yet comfortable.\n");
   add_item("chest","A medium sized wooden chest used for "
	+"storing belongings.\n");
   add_item("desk","A simple wooden desk used for preparing "
	+"classes for the students and other academic pursuits.\n");
   add_item(({"door","doors"}),"They are large wooden doors that "
	+"keep "
	+"some of the noise from training out of the teachers' "
	+"quarters.\n");
   add_item(({"pictures","picture"}),"They depict a variety of "
	+"tough looking men, most of whom are posing with "
	+"weapons.  You assume they are ex-teachers, but "
	+"can't be sure.\n");

	INSIDE;

	add_exit(WWORK+"bar1.c", "north", 0,0);
}

