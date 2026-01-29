/*  A body painting shop.. Zayn feb 97 */

#pragma strict_types

inherit "/std/room";
inherit "/lib/trade";
#include "/sys/money.h"
#include "defs.h"
inherit "/d/Cirath/std/Cirath_magic_room_std";
#include "/d/Cirath/common/mobber.h"


#define COLOUR_ALLOW (TYR_PAINT+"colourok.txt")
#define COLOUR_OBJECT (TYR_PAINT+"colourob.c")
#define NUM sizeof(MONEY_TYPES)


void
reset_room()
{
    bring_room_mob("alstor", TYR_PAINT+"painter.c", 1, 1);
}

void
create_room()
{
	::create_room();
	set_short("body painting shop");
	set_long("You have entered a colourful room. There are stains of "
		+"colours everywhere mixed with heaps of sand and dust. "
		+"There is a sign on the wall for you to examine. This isn't "
		+"an ordinary room. This room must be used for something "
		+"special. There is a smell of thinner in the air.\n");

	add_item("colours", "There are colours here you have never seen "
		+"mixed with heaps of sand and dust.\n");

	add_item(({"sand", "dust"}), "You can see sand everywhere in this "
	      +"room. It must be extremely hard to remove it, because it "
		+"looks like it is stuck to the stains of paint.\n");

	add_item(({"smell", "air"}), "You probably don't want to "
		+"inhale all this thinner for too long. It won't make you feel "
		+"better if you do.\n");

	add_item("thinner","This is a bottle of colour-removing thinner. "
		+"It is used to remove colours, clean brushes and other things "
	       +"like that. If you want to have your skin cleaned and totally "
		+"free from colours, you'll probably have to ask the painter "
		+"to remove the colours.\n");

	add_item(({"sign", "picture"}),"On the sign you can see a picture "
		+"with a wide range of colours. There are colours you never "
		+"thought existed. There is also a bottle of thinner standing "
		+"on the sign. The painter will probably use it if you choose "
		+"to remove the colours that are painted on your skin, or "
		+"just clean the skin in general.  \n"
		+"\n"
+"       +~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~+\n"
+"       |                                                       |\n"
+"       | red              blue                   green         |\n"
+"       | strawberry red   steel blue             moss green    |\n"
+"       | ruby red         sea blue               sea green     |\n"
+"       | dark red         deep blue              turf green    |\n"
+"       | blood red        dark blue              orc green     |\n"
+"       | meat red         diamond blue           pale green    |\n"
+"       | crimson red      pale blue              turquoise     |\n"
+"       | dawn red         faint blue                           |\n"
+"       | pale red                                              |\n"
+"       |                  sparkling crystalline  black         |\n"
+"       | purple           shining crystalline    charred black |\n"
+"       | yellow           shimmering crystalline jet black     |\n"
+"       | orange                                  midnight black|\n"
+"       | pale orange      white                  velvet black  |\n"
+"       | dark yellow      frost white            ebony         |\n"
+"       | pale yellow      snow white             dusky         |\n"
+"       | shimmering gold  glowing white          grey          |\n"
+"       | silky gold       shimmering white       dark grey     |\n"
+"       | golden           milk white             pale grey     |\n"
+"       | silky golden     marble white                         |\n"
+"       | peach            translucent white      chartreuse    |\n"
+"       | succulent peach  pure alabaster         copper        |\n"
+"       | silky peach                             faded         |\n"
+"       | ivory            brown                  pale          |\n"
+"       | flawless ivory   earth brown            pink          |\n"
+"       | pale ivory pale  brown                  silver        |\n"
+"       | soft ivory       dark brown             tanned        |\n"
+"       | glowing ivory    dung brown             bronze        |\n"
+"       |                                                       |\n"
+"       +~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~+\n"
+"            You spot the ancient symbol for the word 'buycolour'\n"
	+"\n");

	add_cmd_item(({"thinner", "air"}), "inhale", "You take a deep breath "
		+"of the air and do not feel anything special about it, except "
		+"that it smells real funny. After about 10 seconds your head "
		+"feels like it it would explode, and then the feeling "
		+"disappears, leaving you with a feeling of sickness.\n");

	add_cmd_item("sign","read","It is against the law to be able "
		+"to read if you aren't a noble. Why don't you examine it "
		+"instead as ordinary people do.\n");

	add_exit(TYR_MARKET+"shdwsqrw.c", "east");

	INSIDE
        reset_room();
}

       
void init()
{
	::init();
	add_action("setcolour", "buycolour");
}

/* Search function.. compares each line in a file with a given string */
int
allowedcolours(string subject)
{
	int zip = 1;
	string current_line;
	string testcolour;

	testcolour=extract(subject+"                                    ",0,30);

	while(current_line=read_file(COLOUR_ALLOW,zip,1))
	{
		if (testcolour==extract(current_line,0,30)) return 1;
		if (extract(current_line,0,3)=="END") return 0;
		if (zip>250) return 0;
		zip=zip+1;
	} 
	return 0;
}

/* This function handles the paying routine */
int
buy_colour(string str)
{
	object buy_ob;
	string what, for_c, get_c, change;
	int *result, price;
	config_default_trade();
	set_money_give_max(1000);
	buy_ob=clone_object(COLOUR_OBJECT);

	price = buy_ob->query_prop(OBJ_I_VALUE);
        buy_ob->remove_object();

	result=pay(price,this_player(),for_c,0,0,get_c);

	if (sizeof(result)==1)
	{
		return 0;
	}

	write("You pay " + text(result[0 .. NUM -1]) + ".\n");
	if (change)
		write("You get " + change + " as change.\n");
	return 1;
}

/* Clones colourob.c to character if the string is approved. */
int
setcolour (string str)
{
	object char = TP;
	object colourob = present("_colour_ob_", char);

        if ((char->query_guild_name_race())=="Drow race guild")
        {
            NF("There isn't much I can do for your race.\n");
            return 0;
        }

	if (str=="none")
	{
		if (!buy_colour(str))
		{
			NF("Wow you'll have to get some money before I can "
			  +"clean your skin.\n");
		     say(QCTNAME(TP) + " tried to deceive the painter to "
		      +"clean "+HIS_HER(TP)+" skin without paying.\n");
			return 0;
		}
		colourob->set_colour_desc(str);
		char->catch_msg("Your skin is now totaly clean of colours "
			+"and dirt in general.\n");
		say(QCTNAME(TP) + " gets "+
		        HIS_HER(TP)+" skin cleaned of colours and dirt "
			+"in general.\n");
		return 1;
	}

	if (!strlen(str))
	{
		NF("You better use 'buycolour <text>' or you'll get no "
		+"colour at all.\n");
		return 0;
	}

	if (strlen(str)>30)
	{
		NF("Try to shorten your choice, it is not right.. it is way "
		  +"too long.\n");
		return 0;
	}

	if (!allowedcolours(str))
	{
		NF("That is not a valid colour.\n"
		  +"Why not try to find another colour on the pictures.\n");
		return 0;
	}

	if (!buy_colour(str))
	{
		write("The painter refuses to paint your body. You can't "
		     +"pay the fee.\n");
		say(QCTNAME(TP) + " tried to deceive the painter to paint "
		     +HIS_HER(TP)+" body without paying the fee.\n");
		return 0;
	}

	if (!colourob) 
	{
                object colourclone = clone_object(COLOUR_OBJECT);
		colourclone->set_colour_desc(str);
		colourclone->move(char);
		return 1;		
	}
	else 
	{
		colourob->set_colour_desc(str);
	}

	char->catch_msg("Your body is now painted in a "+str+" colour.\n");
	say(QCTNAME(TP) + "'s skin is now painted in a "+str+" colour.\n");
	return 1;
}
