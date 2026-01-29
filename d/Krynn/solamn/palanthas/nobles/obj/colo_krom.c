/* Mortis 12.2005
 *
 * Add ability to remove dirt?  Or reserve that for spa baths?
 */

#include "../../local.h"
#include <macros.h>

inherit "/std/object";

#define I_AM_WEARING_A_SMELL		"_i_am_wearing_a_smell"

string psmell = "Ancient and mystic, the scents of an age past fill your senses "
	+ "with passing memories of the battles of gods and giants and men "
	+ "who lived and died by the mettle of which they were tempered.  Iron, "
	+ "leather, and musk...  no man may match you under Krom.";

void
create_object()
{
    set_name("krom");
	add_name(({"cologne", "philter", "fragrance"}));
	add_pname(({"colognes", "philters", "fragrances"}));
    set_adj("stone");
    add_adj(({"mottled", "beige"}));
    set_short("mottled beige stone philter");
	set_pshort("mottled beige stone philters");
    set_long("A mottled beige stone philter containing a tiny amount of a "
	+ "cologne.  \"Krom\" is written in red in the old style upon "
	+ "a small, dark brown label beneath which is \"Jordesse Parfumerie\".  "
	+ "You may spray this cologne on once before it will be used up.\n");
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
	if (TP->query_gender() == 0)
	{
    NF("Spray what on?\n");
    if(!parse_command(str, ({}), "[on] 'cologne' / 'krom' [on] [me] [myself]"))
	return 0;

    NF("You are already wearing a fragrance.\n");
    if(TP->query_prop(I_AM_WEARING_A_SMELL) == 1)
	return 0;

    write("You spray the cologne on your wrists and neck.  " + psmell + "\n");
    say(QCTNAME(TP)+" sprays " + HIS(TP) + " wrists and neck with the "
	+ "cologne from " +  HIS(TP) + " " + short() + " smiling to "
	+ HIMSELF(TP) + " as you catch a hint of the ancient, mystic fragrance.\n");

    seteuid(getuid());
	TP->add_prop(I_AM_WEARING_A_SMELL, 1);
    clone_object(NOBLE + "obj/sub_krom")->move(TP);
    remove_object();
    return 1;
	}
	write("Krom is a men's cologne.\n");
	return 1;
}

int
smell(string str)
{
    if(parse_command(str, ({}), "'cologne' / 'philter' / 'fragrance' / 'control'"))
	{
		write("You smell your philter of Krom.  " + psmell + "\n");
		say(QCTNAME(TP) + " smells " + HIS(TP) + " " + short() + " smiling "
		+ "to " + HIMSELF(TP) + ".\n");
		return 1;
	}
	return 0;
}