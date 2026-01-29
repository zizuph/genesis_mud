inherit "/d/Earthsea/std/room";

#include <ss_types.h>
#include "/sys/stdproperties.h"
#include "/sys/macros.h"
#include "/d/Earthsea/atuan/defs.h"



void
create_earthsea_room()
{
	set_short("In the bedroom.");
	set_long(BS("Inside the bedroom is a double bed which is neatly made, and has"+
		" many coloured pillows thrown across it, along with a green and white chequered"+
		" blanket. Beside it, a chair has a pair of trousers neatly folded across the"+
		" back, and a small chest of drawers sits in one corner.",70));
		 	
	INSIDE;
	
	add_item(({"bed","double bed"})," A very neat bed with orange, green and yellow pillows"+
		" thrown across it, and a beautiful blanket across it.");
	add_item(({"blanket","chequered blanket"}),"A beautifully woven woolen blanket");
	add_item(({"trousers"})," A pair of leather trousers which has a serrated cut down"+
		" the length of one leg like it had been cut with a knife.");
	add_item(({"cut","serrated cut"}),"@@examine_cut");
	add_item(({"drawers","chest of drawers"}),"A set of drawer containing some clothing"+
		" and other various items such as soap, brushes and a mirror.");
	add_item(({"soap","brush","brushes"}),"These are various items to aid personal grooming.");
	add_item(({"mirror"}),"Wow, who is that handsome "+TP->query_race_name() + "?");

add_exit(GAR + "gar_house2","west",0);


}



examine_cut()
{
	int wisdom;
	string DESC;
	
		wisdom = TP->query_stat(4);
		if (wisdom > 40){
			DESC = (BS("The cut looks like it was made with very sharp teeth.",70));
			/* This cut was made by a shark which attacked the old woman's husband */
				{
		else{
			DESC = (BS("You are unsure what made this cut.",70));
		}

		return DESC;
}

		

