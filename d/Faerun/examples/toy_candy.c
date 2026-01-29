/* 
	*A magical piece of candy from a magical toy!
	*Altrus, March 2005
*/
inherit "/std/food";
#include <stdproperties.h>

void create_food()
{
	set_name("candy");
	set_pname("candies");
	set_adj("red");
	set_short("red candy");
	set_pshort("red candies");
	set_long("This is a magical piece of candy! It was " +
	"produced by magic from a specially made toy! You " +
	"are quite unsure of its flavor. Of course you can eat " +
	"this candy, but at first you might try to simply " +
	"'taste' it.\n");
	
	set_amount(50); 
	add_prop(OBJ_I_WEIGHT, 50); 
	add_prop(OBJ_I_VOLUME, 30);
}

void init()
{
	add_action("taste_candy", "taste");
}

int taste_candy(string str)
{
	if(str == "candy" || str == "red candy")
	{
		this_player()->catch_msg("As soon as you lick " +
		"candy, it explodes into a plethora of flavors! " +
		"There are so many passing across your tongue, " +
		"but you think you taste cherry, lemonade, " +
		"peppermint and so many more! You taste them " +
		"all at once, yet they do not mingle and mix " +
		"together. What a wonderful experience!\n");
	}
	
	else
	{
		this_player()->catch_msg("Taste what? " +
		"The candy?\n");
	}
	
	return 1;
}