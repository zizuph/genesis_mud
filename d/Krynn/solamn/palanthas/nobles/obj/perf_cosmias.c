/* Mortis 12.2005
 *
 * Add ability to remove dirt?  Or reserve that for spa baths?
 */

#include "../../local.h"
#include <macros.h>

inherit "/std/object";

#define I_AM_WEARING_A_SMELL		"_i_am_wearing_a_smell"

void
create_object()
{
    set_name("cosmias");
	add_name(({"perfume", "phial", "fragrance"}));
	add_pname(({"perfumes", "phials", "fragrances"}));
    set_adj("glass");
    add_adj(({"pale", "green"}));
    set_short("pale green glass phial");
	set_pshort("pale green glass phials");
    set_long("A pale green glass phial containing a tiny amount of a "
	+ "perfume.  \"Cosmias\" is written in black in the old style upon "
	+ "a small white label beneath which is \"Jordesse Parfumerie\".  "
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
    if(!parse_command(str, ({}), "[on] 'perfume' / 'cosmias' [on] [me] [myself]"))
	return 0;

    NF("You are already wearing a fragrance.\n");
    if(TP->query_prop(I_AM_WEARING_A_SMELL) == 1)
	return 0;

    write("You spray the perfume on your wrists and neck.  A sophisticated "
	+ "fragrance fills your senses with passing memories of champagne, "
	+ "hardwood dance floors, evening winds, dark growing vines, and "
	+ "nightblooms.  It quickens your pulse, bringing a smile to your "
	+ "lips.\n");
    say(QCTNAME(TP)+" sprays " + HIS(TP) + " wrists and neck with the "
	+ "perfume from " +  HIS(TP) + " " + short() + " smiling to "
	+ HIMSELF(TP) + " as you catch a hint of the sophisticated fragrance.\n");

    seteuid(getuid());
	TP->add_prop(I_AM_WEARING_A_SMELL, 1);
    clone_object(NOBLE + "obj/sub_cosmias")->move(TP);
    remove_object();
    return 1;
	}
	write("Cosmias is for women only.\n");
	return 1;
}

int
smell(string str)
{
    if(parse_command(str, ({}), "'perfume' / 'phial' / 'fragrance' / 'cosmias'"))
	{
		write("You smell your phial of Cosmias.  A sophisticated "
		+ "fragrance fills your senses with passing memories of champagne, "
		+ "hardwood dance floors, evening winds, dark growing vines, and "
	+ "nightblooms.  It quickens your pulse, bringing a smile to your "
	+ "lips.\n");
		say(QCTNAME(TP) + " smells " + HIS(TP) + " " + short() + " smiling "
		+ "to " + HIMSELF(TP) + ".\n");
		return 1;
	}
	return 0;
}