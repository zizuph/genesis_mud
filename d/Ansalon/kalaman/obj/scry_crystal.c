/* Copied from Sorgum:  21 Dec 93 */
/*  Borrowed from Lilith's open directory 20/5/97 */


/* Navarre Oct 26th 2007, Added scry properties check to follow standard.
 *                        It is no longer possible to scry protected rooms or persons
 */


#include "/d/Ansalon/common/defs.h"
inherit "/std/object";

#include <stdproperties.h>
#include <macros.h>
#include <ss_types.h>

/*
query_auto_load()
{
    string name;
    int i;

    sscanf(file_name(this_object()),"%s#%d", name, i);
    return name;
}
*/

create_object()
{
    set_name("crystal");
    add_name("_scry_crystal");
    set_adj("blue-tinged");
    add_adj("blue");
    set_short("blue-tinged crystal");
    set_long("This long thin crystal seems to glow from within " +
      "with a mystical blue light. It feels warm in your hands, " +
      "and you cannot help but wanting to grip it.\n");
    add_prop(OBJ_I_VOLUME, 75);
    add_prop(OBJ_I_WEIGHT, 100);
    add_prop(OBJ_I_VALUE, 1500);

    add_prop(MAGIC_AM_ID_INFO,
      ({"This crystal is a scrying device, allowing one to search the planes for " +
	"the location of a person. The use of these crystals is fairly simple, but the preservation " +
	"of them after use takes a high level of skill in both spellcraft and divination skills. " +
	"Attempting to use these crystals to find the location of the Gods or such immortal " +
	"creatures has in the past lead to some users going mad, others dying in great pain, with " +
	"no one going unscathed.\n",25}));
    add_prop(MAGIC_AM_MAGIC, ({50,"enchantment"}));
}

init()
{
    add_action("better_scry", "scry");
    add_action("crystal_message","grip");
}

int
crystal_message(string str)
{
    if(!strlen(str))
    {
	notify_fail("Grip what? The crystal?\n");
	return 0;
    }

    if(str == "crystal" | str == "blue crystal" | str == "blue-tinged crystal")
    {
	write("You grip the crystal tightly. You suddenly know you can scry on people if you wanted with this item.\n");
	return 1;
    }
    return 0;
}

int
better_scry(string who)
{
    object target, old_env, target_env;
    string them;

    if (!strlen(who)) {
	notify_fail("scry whom?\n");
	return 0;
    }

    them = lower_case(who);
    target = find_living(them);

    if (!target) {
        write("Cannot locate that person.\n");
	return 1;
    }

    if (target->query_npc()) {
        write("Cannot locate that person.\n");
	return 1;
    }

    if(TP->query_mana() < 49)
    {
	write("Your mind is too tired to focus on scrying on anyone.\n");
	return 1;
    }

    if(target->query_wiz_level())
    {
	write("The crystal explodes violently, with shards tearing into your body! The " +
	  "immortals don't appreciate being spied upon!\n");
	say("The crystal in " +QTNAME(TP) + "'s hand explodes violently, sending sharp " +
	  "shards of crystal flying everywhere. You are fortunate none hit you, because you are " +
	  "sure that they could do some nasty damage.\n");
	TP->heal_hp(-500);
	if(TP->query_hp() <= 0)
	{
	    TP->do_die(TO);
	}
	TP->add_mana(-750);
	remove_object();
	return 1;
    }

    write("The blue-tinged crystal begins to glow as " +
      "you peer into it. In its glassy depths you see...\n");
    say("A blue-tinged crystal begins to glow as " +QTNAME(TP) +
      " stares into it.\n");
    old_env = environment(this_interactive());
    target_env = environment(target);

    if(target->query_prop(LIVE_I_NO_SCRY) || target_env->query_prop(ROOM_I_NO_SCRY))
    {
        write("Nothing! It is as if a strange force interferes with the magic of the crystal.\n");
	return 1;
    }



    this_interactive()->move(target_env, 1);
    catch(this_interactive()->do_glance(0));
    this_interactive()->move(old_env, 1);
    TP->add_mana(-50);
    target->catch_msg("You feel you are being watched.\n");
    if((TP->query_skill(SS_SPELLCRAFT) + TP->query_skill(SS_FORM_DIVINATION)) > random(200))
    {
	write("You manage to keep the crystal from exploding with " +
	  "your knowledge of magical divination items.\n");
	return 1;
    }
    write("The crystal shatters in your hand!\n");
    say(QCTNAME(TP) + "'s crystal shatters in " +HIS(TP)+ " hand!\n");
    remove_object();
    return 1;
}


