/* 
 * Boots for the Union of the Warriors
 * of Shadow. Cirion 031696
 * foot armour only per Elders.
 *
 * * Lucius ??? ????: Revised to properly show broken status.
 * * Lucius May 2009: Small cleanups
 */
#pragma strict_types

#include <macros.h>
#include <language.h>
#include <wa_types.h>
#include <stdproperties.h>

#include "../defs.h"

inherit "/std/armour";
inherit "/lib/commands";
inherit "/lib/keep";
inherit (LIB + "union_arm");

private int dirt_alarm;

public void
create_armour(void)
{
    allow_buff = 1;
    allow_clean = 0;

    set_name("boots");
    add_name("boot");
    set_adj(({"black","knee","knee-length", "union"}));
    add_adj("unworn");

    set_pshort("pairs of black knee-length boots");
    set_long("These boots are made of thick, blackened leather "+
      "that forms a protective covering for the feet. A lighter, "+
      "more supple leather forms a sheathe from ankle to knee. "+
      "Supple suede folds over at the thighs down to "+
      "the knee, creating a wide cuff. The cuff itself is "+
      "bordered with a thin strip of webcloth-and-silver samite."+
      "@@my_long@@\n");

    add_item(({"cuff","cuffs","samite"}),
      "The cuffs of the boots are made of the same leather, only "+
      "sueded to a more pleasant texture. They reach the lower "+
      "thigh and fold over to cover the knee. The cuff is hemmed "+
      "in black webcoth woven with silver thread, a material "+
      "commonly known as samite.\n   Wearing them, you can "+
      "<boottap> and <boottug>.\n");

    add_prop(OBJ_I_VALUE,  146);
    set_at(A_FEET);
    set_af(TO);
    set_ac(10);
    set_keep(1);
}

public mixed 
wear(object ob)
{
    if (TP != ENV(TO))
	return 0;

    write("You pull "+ LANG_THESHORT(TO) +" on over "+
      "your feet and up to your thighs, then turn the "+
      "cuffs down at the knee.\n");
    say(QCTNAME(TP) +" pulls "+ LANG_ASHORT(TO) +" on over "+
      HIS(TP)+" feet and legs.\n");

    return 1;
}

public string 
my_long(void)
{
    string str;

    if (dirt < 0)
	dirt = 0;

    switch(dirt)
    {
    case 0: str = "are perfectly buffed and gleaming."; break;
    case 1: str = "are well-buffed and gleaming."; break;
    case 2: str = "are still buffed, but lacking in shine."; break;
    case 3: str = "have lost their gleam."; break;
    case 4: str = "are in need of a good buffing."; break;
    case 5: str = "are showing signs of neglect."; break;
    case 6: str = "covered with the muck of combat and travel."; break;
    case 7: str = "are in desperate need of a good buffing."; break;
    default:str = "so filthy that no self-respecting Warrior "+
	"would wear them."; break;
    }

    return " These boots " + str;
}

public void 
more_dirty(void)
{
    if (!living(ENV(TO)))
    {
	remove_alarm(dirt_alarm);
	dirt_alarm = 0;
    }
    else if (++dirt > 9) {
	dirt = 9;
    }
}

public void 
enter_env(object to, object from)
{
    ::enter_env(to, from);

    if (query_interactive(to))
    {
	if (!dirt_alarm)
	    dirt_alarm = set_alarm(5000.0, 5000.0, more_dirty);
    }
    else if (dirt_alarm)
    {
	remove_alarm(dirt_alarm);
	dirt_alarm = 0;
    }
}

public varargs string
short(object for_ob)
{
    string dirt_desc, str;

    if (query_prop(OBJ_I_BROKEN))
	return "pair of broken black knee-length boots";

    switch(dirt)
    {
    case 0:  dirt_desc = "gleaming";       break;
    case 1:  dirt_desc = "gleaming";       break;
    case 2:  dirt_desc = "well-buffed";    break;
    case 3:  dirt_desc = "well-buffed";    break;
    case 4:  dirt_desc = "buffed";         break;
    case 5:  dirt_desc = "well-worn";      break;
    case 6:  dirt_desc = "scuffed";        break;
    case 7:  dirt_desc = "scruffy";        break;
    case 8:  dirt_desc = "dirty";          break;
    case 9:  dirt_desc = "stained";        break;
    default: dirt_desc = "filthy";         break;
    }

    if (strlen(dirt_desc))
	str = dirt_desc + " ";
    else
	str = "mirror-";

    return "pair of "+ str + "black knee-length boots";
}

public int
do_tap(string str)
{
    string *how;

    if (!query_worn()) 
	return 0;

    if (!IS_MEMBER(TP))
	return 0;

    how = parse_adverb_with_space(str, "idly", 0);

    if (!strlen(how[0]))
    {
	write("You"+how[1]+" tap the toe of your "+ short() +
	  " against the ground underfoot.\n");
	all(how[1] +" taps the toe of "+ HIS(TP) +" "+
	  short() +" against the ground underfoot.");

	return 1;
    }

    write("You"+ how[1] +" tap the toe of your "+ short() +
      " against the ground underfoot.\n");
    all(how[1] +" taps the toe of "+ HIS(TP) +" "+
      short() +" against the ground underfoot.");

    return 1;
}

public int
do_pull(string str)
{
    string *how;

    if (!query_worn()) 
	return 0;

    if (!IS_MEMBER(TP))
	return 0;

    how = parse_adverb_with_space(str, "carefully", 0);

    if (!strlen(how[0]))
    {
	write("You give the tops of your "+ short() +
	  " a good tug and"+ how[1] +" fold the cuffs "+
	  "over at the knees.\n");
	all(" gives the tops of "+ HIS(TP) +" "+
	  short() +" a good tug and then"+ how[1] +
	  " folds the cuffs over at the knees.");

	return 1;
    }
    write("You give the tops of your "+ short() +
      " a good tug and"+how[1]+" fold the cuffs "+
      "over at the knees.\n");
    all(" gives the tops of "+ HIS(TP) +" "+
      short() +" a good tug and then"+ how[1] +
      " folds the cuffs over at the knees.");

    return 1;
}

public void
init(void)
{
    ::init();

    init_union_arm();

    add_action(do_pull,	"boottug");
    add_action(do_tap,	"boottap");
}
