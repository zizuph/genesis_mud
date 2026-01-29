/*
 * Rod of summoning for the Sphere of Guild Defence
 *
 * Cirion, January 1997
 */
inherit "/std/object";

#include <macros.h>
#include <language.h>
#include <stdproperties.h>

#include "../defs.h"


public int
valid_tell(object who)
{
    return (LIST->query_is_friend(who->query_real_name()) ||
	    LIST->query_is_member(who->query_real_name()));
}

public int
tell_members_and_allies(string str)
{
    object *people = filter(users(), valid_tell);

    people -= ({ all_inventory(ENV(TP)) });

    if (!sizeof(people))
	return 0;

    people->catch_msg(str);
    return 1;
}

public void
create_object()
{
    set_name("rod");
    set_short("long rod of dark steel");
    set_pshort("long rods of dark steel");

    add_name(({"steel", BAR_ID, "bar"}));
    set_adj(({"long","steel","dark"}));
    add_adj("union");

    set_long("It is a long rod of darkened steel, very heavy "
      + "and strong. The ends of the rod are both shod with "
      + "rings of bloodstone, which shimmers with an inner "
      + "flame. Flecks of some shiny stone, perhaps feldspar, "
      + "run up along the length of the rod.\n"
      + "Etched along the side of the rod is "
      + "an inscription.\n");

    add_cmd_item(({"inscription","rod","the rod","the steel rod",
	    "steel rod","the inscription"}), "read",
	"\tYou Shall Summon Your Allies Only In Times Of Great Need\n"+
	"\t     Held Aloft My Cry Shall Be Heard Everywhere\n");

    add_prop(OBJ_I_WEIGHT, 300);
    add_prop(OBJ_I_VOLUME, 200);
    add_prop(OBJ_M_NO_DROP, "It will not leave your hands.\n");
    add_prop(OBJ_M_NO_SELL, 1);
    add_prop(OBJ_M_NO_BUY, 1);
    add_prop(OBJ_I_VALUE, 350);
    add_prop(MAGIC_AM_MAGIC, ({ 10, "conjuration", 10, "fire" }));
    add_prop(MAGIC_AM_ID_INFO, ({ "It shall summon forth "
	+ "those friends and discipled of the Union.\n", 15,
	"It was forged in the very Flame by the smith "
	+ "Hephamenios.\n", 76 }));
    add_prop(OBJ_S_WIZINFO, "This object is cloned into the inventory "
      + "of those Union members and allows them to summon the "
      + "aid of other Union members and Allies of the Union in "
      + "times of emergency.\n");

}

public void
dest(void)
{
    ENV(TO)->catch_tell("The rod fades away with a swirl "+
	"of fiery gloaming.\n");
    remove_object();
}

public void
enter_env(object to, object from)
{
    ::enter_env(to, from);

    if (!MEMBER_SPHERE(to, SPH_PROTECTION))
	set_alarm(0.5, 0.0, dest);
}

public int
hold_rod(string str)
{
    NF("Hold what?\n");
    if (!strlen(str))
	return 0;

    if (!parse_command(str, ({}), "[the] 'rod' / 'bar' [over] / [in] "+
	    "[my] / [the] 'head' / 'air' / 'aloft'"))
	return 0;

    write("You hold " + LANG_THESHORT(TO) + " aloft, and cry "+
	"out in a booming voice:\n\tAmusk Shin Akon Fi!\n");
    say(QCTNAME(TP) +" holds " + LANG_ASHORT(TO) + " aloft and "+
	"cries out in a booming voice:\n\tAmusk Shin Akon Fi!\n");
    tell_room(ENV(TP), "Etherial and indistinct flames begin to flicker "+
	"all about, like shadows building with rage.\n");

    if (!tell_members_and_allies("A shadow passes nearby, "+
	    "brought on the currents of war and battle.\n"+
	    "The voice of Shin Akon Fi!\n"))
	write("Your voice reaches no one, you are alone in the world.\n");

    return 1;
}

public void
init(void)
{
    ::init();

    if (TP == environment())
	add_action(hold_rod, "hold");
}
