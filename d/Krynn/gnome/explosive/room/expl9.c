/**
* Coded by Louie 2004
* 
* Gnome Manufacturing Room.
* This room is where a player can build a prototype explosive device.
* They will need a design and a box of parts which they can get earlier
* in the quest.
* If the proto_gnome is present, he'll prevent people from trying to
* build something without the proper paperwork.
*
*/
#pragma strict_types

#include "../local.h"
inherit GNOME_IR;

/*prototypes*/
string state_descrip();
int do_read(string str);
int do_construct(string str);
void construct_explosive();
void phase1();
void phase2();
void phase3();
void phase4();
void final_phase();


/*
* Reset
*/
void
reset_gnome_room()
{
	object gnome;
	
	if (!present("_gnome_proto"))
	{
		gnome = clone_object(GNOME_NPC+"proto_gnome");
		gnome->move_living("xxx",TO);
	}
}

/*
* Create
*/
void
create_gnome_room()
{

    SHORT("Manufacturing Room in the Explosives Development Center");
    LONG("This is the manufacturing room in the Explosives Development Center " +
    	"of Gnomish "+
      "Industries.  " +
      "The room is small and empty, containing only a table for initially " +
      "constructing devices.  " +
      "A sign is attached to the wall.  " +
      "@@state_descrip@@" +
      "\n");


    EXIT(GNOME_ROOM + "expl8", "south", 0, 1);

	ITEM(({"table","wooden table","plain table","plain wooden table"}),
		"The table is plain and wooden, except for a few scorch and " +
		"burn marks.  " +
		"Apparently constructing an explosive device is not as " +
		"safe as one would think.  " +
		"\n");
		
	ITEM(({"scorch marks","burn marks","marks"}),
		"These marks indicate that constructing an explosive device " +
		"may be risky business.  " +
		"\n");
		
	ITEM(({"sign"}),
		"The sign indicates that it is possible to construct " +
		"a prototype explosive device, assuming you have the " +
		"required design form, request form, and parts.  " +
		"\n");
	
	reset_gnome_room();
}

void
init()
{
	::init();
	ADD("do_read","read");
	ADD("do_construct","construct");
}

int 
do_read(string str)
{

	if (!strlen(str) || !(str == "sign")) 
	{
		NF("Read what?\n");
		return 0;
	}
	
	write("The sign indicates that it is possible to construct " +
		"a prototype explosive device, assuming you have the " +
		"required design form, request form, and parts.  " +
		"\n");
    
    return 1;
}

/*
* Check that everything is in proper order before allowing someone to
* construct a prototype. 
* The player needs a signed/approved waiver, design form, and a box
* of parts.
*/
int
do_construct(string str)
{
	object ob,ob2,gnome;

	if (!strlen(str) || (!(str == "prototype") 
		&& !(str == "device") && !(str == "prototype device")
		&& !(str == "explosive device") && !(str == "a prototype")
		&& !(str == "prototype explosive device")))
	{
		NF("Construct a prototype?\n");
		return 0;
	}
	
	if (present("_gnome_proto",TP))
	{
		NF("You already have a prototype!\n");
		return 0;
	}
	
	if (!present("_gnome_design_form",TP))
	{
		NF("You have no design to work off of!\n");
		return 0;
	}
	
	ob = present("_gnome_design_form",TP);
	ob2 = present("_gnome_request_form",TP);
	gnome = present("_gnome_proto");
	
	/* If the gnome is around he'll make sure people have the right paperwork*/
	
	if (gnome && !(ob->is_approved())) {
		gnome->command("say WaitASecondIDon'tSeeTheStampOfApprovalOn"+
			"YourDesignForm!");
		NF("You are stopped from constructing a prototype.\n");
		return 0;
	}
	
	if (gnome && !(ob2->is_approved())) {
		gnome->command("say HeyIDon'tSeeAnApprovedRequestForm,ICan't"+
			"LetYouDoAnythingUntilYouHaveOne!");
		NF("You are stopped from constructing a prototype.\n");
		return 0;
	}
	
	/**They have to have a bag of parts before they can build**/
	
	
	if (!present("_gnome_parts_box",TP)) {
		NF("You have no parts to work with!\n");
		return 0;
	}
	
	/** This makes sure that they're not in the middle of **/
	/** constructing something already **/
	
	
	if (present("_gnome_constructing_ob", TP)) {
		NF("You are already constructing something!\n");
		return 0;
	}
	
	/** Finally they can't create a grenade if they're already **/
	/** carrying one **/
	
	if (present("_gnome_grenade", TP))
	{
		NF("You are already carrying a gnomish explosive device, it "+
			"would be too dangerous to carry more than one.\n");
		return 0;
	}
	
	/*Begin construction*/
	construct_explosive();
	
	return 1;
	
}

/*
* Begin building the prototype device - it just prints messages 
* through the phases
*/
void
construct_explosive()
{
	object ob;
	object con_ob;
	
	ob = present("_gnome_design_form",TP);
	write("You begin to construct your prototype.\n");
	SAY(" beings constructing a prototype device.");
	
	con_ob = clone_object(GNOME_OBJ+"constructing_ob");
	con_ob->move(TP);
	
	switch(random(2)) {
		case 0:
			write("You attach some sharp pieces to the device.\n");
			SAY(" attaches some sharp looking things to the device.");
			break;
		case 1:
			write("You attach some wires to the device.\n");
			SAY(" attaches some wires to the device.");
			break;
		default:
			break;
	}
		
	set_alarm(3.0,0.0,"phase1");
	
}

void
phase1()
{
	object ob;
	ob = present("_gnome_design_form",TP);
	
	switch(random(2)) {
		case 0:
			write("You attach some little gears.\n");
			SAY(" attaches some little gears.");
			break;
		case 1:
			write("You adjust some pieces.\n");
			SAY(" adjusts some pieces.");
			break;
		default:
			break;
	}
	
	set_alarm(3.0,0.0,"phase2");
}

void 
phase2()
{
	object ob;
	ob = present("_gnome_design_form",TP);
	
	switch(random(2)) {
		case 0:
			write("You use a bit of cord to secure some parts.\n");
			SAY(" uses a bit of cord to secure some parts.");
			break;
		case 1:
			write("A piece falls off.  You force it back into place.\n");
			SAY(" frowns as a piece falls off, but "+HE(TP)+" forces "+
				"it back into place.");
			break;
		default:
			break;
	}
	
	set_alarm(3.0,0.0,"phase3");
}

void
phase3()
{
	object ob;
	ob = present("_gnome_design_form",TP);
	
	switch(random(2)) {
		case 0:
			write("You piece together the ignition component.\n");
			SAY(" pieces together the ignition component.");
			break;
		case 1:
			write("You fumble the device and almost drop it.\n");
			SAY(" fumbles the device and almost drops it.");
			break;
		default:
			break;
	}
	
	set_alarm(3.0,0.0,"phase4");
}

void
phase4()
{
	object ob;
	ob = present("_gnome_design_form",TP);
	
	switch(random(2)) {
		case 0:
			write("You carefully insert the explosion mechanism.\n");
			SAY(" carefully inserts the explosion mechanism.");
			break;
		case 1:
			write("You wipe some sweat off your brow.\n");
			SAY(" wipes some sweat off "+HIS(TP)+" brow.");
			break;
		default:
			break;
	}
	
	set_alarm(3.0,0.0,"final_phase");
}

/*
* Clone the prototype device they built and set some of its properties.
* remove their box of parts.
*/
void 
final_phase()
{
	object con_ob;
	object parts;
	object proto;
	object design;
	
	con_ob = present("_gnome_constructing_ob",TP);
	parts = present("_gnome_parts_box",TP);
	design = present("_gnome_design_form",TP);
	
	if (con_ob) {
		con_ob->remove_object();
	}
	
	if (parts) {
		parts->remove_object();
	}	
	
	proto = clone_object(GNOME_OBJ+"proto");
	proto->set_do_disarm(design->eff_disarm_ct());
	proto->set_do_damage(design->eff_damage_ct());
	proto->move(TP);
	
	write("You successfully create a prototype device!\n");
	SAY(" successfully creates a prototype device!");
}


string
state_descrip()
{
    string desc = "";

    if (IS_EXPL) 
    {
	
	desc = "A loud alarm bell rings incessantly.  ";

    } 

    return desc;

}
