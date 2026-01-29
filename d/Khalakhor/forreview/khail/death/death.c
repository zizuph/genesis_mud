/* death.c */
/* Mrpr 901120 */
/* Tintin 911031 */
/* Nick 920211 */

inherit "/std/monster";
#include "/sys/stdproperties.h"

/*
 * Function name: init
 * Description:   Init Death
 */
init_living() 
{
    add_action("take_it", "take");
    add_action("take_it", "get");
}

/*
 * Function name: query_init_master
 * Description:   Make sure Death's master object is initialized
 */
public int
query_init_master()
{
    return 1;
}

/*
 * Function name: reset
 * Description:   Reset Death
 */
void
create_monster() 
{
    set_name("figure");
    set_name("moot");
    set_name("death");
    set_race_name("immortal");
    set_adj("shadowlike");
    set_short("shadowlike figure, clad in black");
    add_item("scythe",
	"An extremly sharpened scythe. It's so sharp that gusts of wind " +
	"actually try\nto turn away from the edge rather than be sliced " +
	"in two by the wicked looking\nblade. It does strange things with " +
	"light as well as unlucky photons split into\ntheir " +
	"sub-components when they hit the blade.\n");
    add_item("robe",
	"A black hooded robe with numerous pockets. It doesn't seem to " +
	"fit you very\nwell however. It seems to have been tailored " +
	"for a very lean customer.\nVERY lean actually...\n");
    set_long("" +
	"Death seems to have taken Jane Fonda's exercise and diet " +
	"program much too\nseriously. A clear case of Anorexia Neurosa. " +
	"Except for a wicked looking scythe\nhe's dressed in a black " +
	"hooded robe that suits him admireably well.  There's\nsomething " +
	"about his eyes as well, or maybe the lack of eyes, that you\n" +
	"feel you'd better not investigate too closely.\n");

    add_prop(LIVE_I_ALWAYSKNOWN, 1);
}

/*
 * Function name: take_it
 * Description:   Try to take something from death.
 */
take_it(str)
{
    
    string name;
    int extra;
    
    name = capitalize(this_player()->query_real_name());
    extra = random(900) + 10;
    
    if (str == "scythe" || str == "robe")
    {
	write(
"You take a firm grip on the " + str + " and try to pull it towards you.\n" +
"Death frowns, raps you smartly across your fingers with a bony hand and says:\n" +
"STUPID MORTAL. YOU JUST EARNED " + extra + " EXTRA YEARS IN PURGATORY!\n");

	return 1;
    }
}
