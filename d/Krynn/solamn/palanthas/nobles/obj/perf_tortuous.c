/* Mortis 12.2005
 *
 * Add ability to remove dirt?  Or reserve that for spa baths?
 */

#include "../../local.h"
#include <macros.h>

inherit "/std/object";

#define I_AM_WEARING_A_SMELL		"_i_am_wearing_a_smell"

string psmell = "Your body temperature rises as this hypnotic fragrance "
	+ "captures your senses with memories of long nights, the darkest red "
	+ "wine, tight embraces, and passionate dances around a fire under the "
	+ "moon as the music and clapping of the watchers drives you on and a "
	+ "hot wind shakes the leaves from the trees above.  You snap yourself "
	+ "out of your reverie short of breath, your heart beating fiercely, "
	+ "and you smile to yourself as you wipe your brow and catch your "
	+ "breath.";

void
create_object()
{
    set_name("tortuous");
	add_name(({"perfume", "bottle", "fragrance"}));
	add_pname(({"perfumes", "bottles", "fragrances"}));
    set_adj("glass");
    add_adj(({"dark", "red"}));
    set_short("dark red glass bottle");
	set_pshort("dark red glass bottles");
    set_long("A dark red glass bottle containing a tiny amount of a "
	+ "perfume.  \"Tortuous\" is written in dark red in the old style upon "
	+ "a small black label beneath which is \"Jordesse Parfumerie\".  "
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
    if(!parse_command(str, ({}), "[on] 'perfume' / 'tortuous' [on] [me] [myself]"))
	return 0;

    NF("You are already wearing a fragrance.\n");
    if(TP->query_prop(I_AM_WEARING_A_SMELL) == 1)
	return 0;

    write("You spray the perfume on your wrists and neck.  " + psmell + "\n");
    say(QCTNAME(TP)+" sprays " + HIS(TP) + " wrists and neck with the "
	+ "perfume from " +  HIS(TP) + " " + short() + " smiling to "
	+ HIMSELF(TP) + " as you catch a hint of the captivating fragrance.\n");

    seteuid(getuid());
	TP->add_prop(I_AM_WEARING_A_SMELL, 1);
    clone_object(NOBLE + "obj/sub_tortuous")->move(TP);
    remove_object();
    return 1;
	}
	write("Tortuous is a women's perfume.\n");
	return 1;
}

int
smell(string str)
{
    if(parse_command(str, ({}), "'perfume' / 'bottle' / 'fragrance' / 'tortuous'"))
	{
		write("You smell your bottle of Tortuous.  " + psmell + "\n");
		say(QCTNAME(TP) + " smells " + HIS(TP) + " " + short() + " smiling "
		+ "to " + HIMSELF(TP) + ".\n");
		return 1;
	}
	return 0;
}