inherit "/std/room";
#include "/d/Cirath/common/defs.h"
#include "/d/Cirath/common/teamer.h"

void reset_room()
{
        object momma=clone_object(AK_WELA_DIR+"/npc/momma.c");
        momma->arm_me();
        momma->move_living("into the room",TO);
	object poppa=clone_object(AK_WELA_DIR+"/npc/poppa.c");
        poppa->arm_me();
        poppa->move_living("into the room",TO);
        object kid=clone_object(AK_WELA_DIR+"/npc/famkid.c");
        object kid2=clone_object(AK_WELA_DIR+"/npc/famkid.c");
        kid->move_living("into the room",TO);
	kid2->move_living("into the room",TO);
	poppa->team_join(momma);
        poppa->team_join(kid);
        poppa->team_join(kid2);
}
		
void
create_room()
{
    set_short("A family home in Ak Wela");
    set_long("This seems to be the home of a family living here in Ak Wela."+
             "Nothing much of interest is here, just some cushion-seats and" +
             "a very low table, and some straw mats for beds in a corner. " +
             "This family is not very rich, judging by this home, but "+
             "it is a clean place with a homely atmosphere.\n");
    INSIDE

    add_exit(AK_WELA_DIR + "szun_moon10", "south", 0, 2);

    add_item("table","This is a small table with cushion-seats on the sides "+
             "in the middle of the room. It doesn't look very sturdy, and "+
             "not very valueable either.\n");
    add_item(({"cushion","cushions","cushion-seat","cushion-seats"}),"Theese "+
             "seats surround the small table in the centre of the room.\n");
  
    reset_room();
}


void init()
{
	::init();
	add_action("my_sit","sit");
}

int
my_sit(string s)
{
	if(s!="on seat" && s!="on cushion" && s!="on cushion-seat")
		{
		NF("sit on what ?\n");
		return 0;
		}
	write("You briefly sit down on one of the cushions. However "+
              "it is rather uncomfortable, so you quickly rise again.\n");
	say(QCTNAME(TP)+" sits on one of the seats for a brief moment, then "+
            "rises again.\n");
return 1;
}

		