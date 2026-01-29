/* Mortis 12.2005
 *
 * Add ability to remove dirt?  Or reserve that for spa baths?
 */

#include "../../local.h"
#include <macros.h>

inherit "/std/object";

#define I_AM_WEARING_A_SMELL		"_i_am_wearing_a_smell"

string psmell = "A commanding scent rises to your nostrils as your mind is "
	+ "filled with the essence of confidence, reliance, and cool resolve.  "
	+ "Your every word is chosen well and well received, and your deepest "
	+ "desires within your grasp.  You are in... Control.";

void
create_object()
{
    set_name("control");
	add_name(({"cologne", "vial", "fragrance"}));
	add_pname(({"colognes", "vials", "fragrances"}));
    set_adj("ceramic");
    add_adj(({"polished", "black"}));
    set_short("polished black ceramic vial");
	set_pshort("polished black ceramic vials");
    set_long("A polished black ceramic vial containing a tiny amount of a "
	+ "cologne.  \"Control\" is written in white in the old style upon "
	+ "a small pink label beneath which is \"Jordesse Parfumerie\".  "
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
    if(!parse_command(str, ({}), "[on] 'cologne' / 'control' [on] [me] [myself]"))
	return 0;

    NF("You are already wearing a fragrance.\n");
    if(TP->query_prop(I_AM_WEARING_A_SMELL) == 1)
	return 0;

    write("You spray the cologne on your wrists and neck.  " + psmell + "\n");
    say(QCTNAME(TP)+" sprays " + HIS(TP) + " wrists and neck with the "
	+ "cologne from " +  HIS(TP) + " " + short() + " smiling to "
	+ HIMSELF(TP) + " as you catch a hint of the commanding fragrance.\n");

    seteuid(getuid());
	TP->add_prop(I_AM_WEARING_A_SMELL, 1);
    clone_object(NOBLE + "obj/sub_control")->move(TP);
    remove_object();
    return 1;
	}
	write("Control is a men's cologne.\n");
	return 1;
}

int
smell(string str)
{
    if(parse_command(str, ({}), "'cologne' / 'vial' / 'fragrance' / 'control'"))
	{
		write("You smell your vial of Control.  " + psmell + "\n");
		say(QCTNAME(TP) + " smells " + HIS(TP) + " " + short() + " smiling "
		+ "to " + HIMSELF(TP) + ".\n");
		return 1;
	}
	return 0;
}