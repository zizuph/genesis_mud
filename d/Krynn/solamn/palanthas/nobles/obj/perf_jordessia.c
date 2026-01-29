/* Mortis 12.2005
 *
 * Add ability to remove dirt?  Or reserve that for spa baths?
 */

#include "../../local.h"
#include <macros.h>

inherit "/std/object";

#define I_AM_WEARING_A_SMELL		"_i_am_wearing_a_smell"

string psmell = "The latest fragrance from Jordesse fills your senses with "
	+ "passing memories of the full moon, its reflection blue upon the dark "
	+ "waters beneath your balcony as the night breeze tosses your hair "
	+ "back, and the dark outline of your companion appears from the "
	+ "shadows.  Underneath it all is the fragrance of a flower or musk or "
	+ "blossom you just can't place but cannot stop thinking about.";

void
create_object()
{
    set_name("jordessia");
	add_name(({"perfume", "bottle", "fragrance"}));
	add_pname(({"perfumes", "bottles", "fragrances"}));
    set_adj("glass");
    add_adj(({"polished", "black"}));
    set_short("polished black glass bottle");
	set_pshort("polished black glass bottles");
    set_long("A polished black glass bottle containing a tiny amount of a "
	+ "perfume.  \"Jordessia\" is written in white in the old style upon "
	+ "a small pink label beneath which is \"Jordesse Parfumerie\".  "
	+ "You may spray this perfume on once before it will be used up.\n");
    add_prop(OBJ_I_WEIGHT, 50);
    add_prop(OBJ_I_VOLUME, 80);
    add_prop(OBJ_I_VALUE, 0);
}

void
init()
{
    ::init();
    ADA("spray");
	ADA("smell");
}

int
spray(string str)
{
	if (TP->query_gender() == 1)
	{
    NF("Spray what on?\n");
    if(!parse_command(str, ({}), "[on] 'perfume' / 'jordessia' [on] [me] [myself]"))
	return 0;

    NF("You are already wearing a fragrance.\n");
    if(TP->query_prop(I_AM_WEARING_A_SMELL) == 1)
	return 0;

    write("You spray the perfume on your wrists and neck.  " + psmell + "\n");
    say(QCTNAME(TP)+" sprays " + HIS(TP) + " wrists and neck with the "
	+ "perfume from " +  HIS(TP) + " " + short() + " smiling to "
	+ HIMSELF(TP) + " as you catch a hint of the enthralling fragrance.\n");

    seteuid(getuid());
	TP->add_prop(I_AM_WEARING_A_SMELL, 1);
    clone_object(NOBLE + "obj/sub_jordessia")->move(TP);
    remove_object();
    return 1;
	}
	write("Jordessia is a women's perfume.\n");
	return 1;
}

int
smell(string str)
{
    if(parse_command(str, ({}), "'perfume' / 'bottle' / 'fragrance' / 'jordessia'"))
	{
		write("You smell your bottle of Jordessia.  " + psmell + "\n");
		say(QCTNAME(TP) + " smells " + HIS(TP) + " " + short() + " smiling "
		+ "to " + HIMSELF(TP) + ".\n");
		return 1;
	}
	return 0;
}