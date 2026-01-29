/*
   Wayreth.

   conclave.c
   ----------

   Coded ........: 95/06/02
   By ...........: Jeremiah

   Latest update : February 1997
   By ...........: Kentari

*/

#include <macros.h>
#include "/d/Krynn/wayreth/local.h"
#include "/d/Krynn/wayreth/guild/local.h"
inherit TOWERROOM;

#define ADM    "/d/Krynn/wayreth/guild/admin/admin.c"
#define WHITE  ADM->query_conclave_head("white")
#define RED    ADM->query_conclave_head("red")
#define BLACK  ADM->query_conclave_head("black")

int check_whitehead();
int check_redhead();
int check_blackhead();


void
create_tower_room()
{
   set_short("Conclave board room and lobby");
   set_long("This is the area of the conclave of the mages of Wayreth. " +
             "Here the masters of the three factions of mages have " +
             "their private studies. White is to the north, Red is " +
	     "to the west, and Black is to the south. A colored bell " +
	     "cord hangs in front of each of the three offices of the " +
	     "Wayreth conclave and an exit leads east to the stairwell.\n");

   AI(({"spectres","powerful spectres","spectre","guardian","subtle spectres"}),
	"Though you can't see them, you have no doubt that they'll make " +
	"their presence known should you attempt to enter an office unbidden.\n");
	
   AI(({"colored cord","cord","cords","bell cord","bell cords","colored bell cords"}),
	"Which bell cord? The white, red, or black cord?\n");
   AI(({"white cord","white bell cord","silk"}),
	"Pull this cord, made of thick, pure white silk, to ring the bell " +
	"inside the office of "+capitalize(WHITE)+", Master of the White " +
	"Robed Mages.\n");
   AI(({"red cord","red bell cord","satin"}),
	"Pull this cord, made of thick, vibrant crimson satin, to ring the " +
	"bell inside the office of "+capitalize(RED)+", Master of the Red " +
	"Robed Mages.\n");
   AI(({"black cord","black bell cord"}),
	"Pull this cord, made of thick, deep midnight velvet, to ring the " +
	"bell inside the office of "+capitalize(BLACK)+", Master of the " +
	"Black Robed Mages.\n");

   add_exit(WTOWER + "stairwell08", "east", 0);
   add_exit(WTOWER + "whitestudy", "north", check_whitehead);
   add_exit(WTOWER + "blackstudy", "south", check_blackhead);
   add_exit(WTOWER + "redstudy", "west", check_redhead);

   clone_object(WOBJ + "conclave_board")->move(this_object());
}

int
check_whitehead()
{
	if (((IS_CONCLAVE(TP)) && ((ADMIN->query_member_type(TP))==TYPE_WHITE)) || (TP->query_wiz_level()))
	  {
	   write("The spectral guardian obediently reports that no " +
		"one has entered your office since you left and humbly " +
		"steps aside as you enter your office.\n");
	   say("The spectral guardian briefly reports to "+QTNAME(TP)+" and " + 
	     "humbly steps aside for "+HIM(TP)+" as "+HE(TP)+
	     " enters "+HIS(TP)+" office.\n");
	   return 0;
	  }
	write("A powerful and ghastly spectral guardian appears before " +
		"you and with a single, freezing touch " +
		"halts all thoughts of entering the office of the Head " +
		"of the White Robed Wizards.\n");
	return 1;
}

int
check_redhead()
{
	if (((IS_CONCLAVE(TP)) && ((ADMIN->query_member_type(TP))==TYPE_RED)) || (TP->query_wiz_level()))
	  {
	    write("The spectral guardian obediently reports that no " +
		"one has entered your office since you left and humbly " +
		"steps aside as you enter your office.\n");
            say("The spectral guardian briefly reports to "+QTNAME(TP)+" and " +
                "humbly steps aside for "+HIM(TP)+" as "+HE(TP)+
		" enters "+HIS(TP)+" office.\n");
            return 0;
	   }
	write("A powerful and ghastly spectral guardian appears before " +
		"you and with a single, freezing touch " +
		"halts all thoughts of entering the office of the Head " +
		"of the Red Robed Wizards.\n");
        return 1;
}

int
check_blackhead()
{
	if (((IS_CONCLAVE(TP)) && ((ADMIN->query_member_type(TP))==TYPE_BLACK)) || (TP->query_wiz_level()))
	  {
	    write("The spectral guardian obediently reports that no " +
		"one has entered your office since you left and humbly " +
		"steps aside as you enter your office.\n");
            say("The spectral guardian briefly reports to "+QTNAME(TP)+" and " +
                "humbly steps aside for "+HIM(TP)+" as "+HE(TP)+
		" enters "+HIS(TP)+" office.\n");
            return 0;
	  }
	write("A powerful and ghastly spectral guardian appears before " +
		"you and with a single, freezing touch " +
		"halts all thoughts of entering the office of the Head " +
		"of the Black Robed Wizards.\n");
        return 1;
}



