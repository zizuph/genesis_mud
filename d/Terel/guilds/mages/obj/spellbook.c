#include "/d/Terel/guilds/mages/lib/mages.h"
#include "/d/Terel/include/Terel.h"
#include <stdproperties.h>

inherit "/std/book";
inherit "/d/Genesis/newmagic/spellcasting";

// Prototypes
public static int env_check();


string query_auto_load() { return MASTER + ":"; }

/* cannot be both recoverable and autoloadable */
string query_recover() { return 0; }

void
create_book()
{
    set_max_pages(8);
    set_name("book");
    add_name("arcanum_mages_spell_book");
    add_name("spellbook");
    set_adj(({ "smooth", "white" }));
    set_short("smooth white book");
    set_long("A smooth white book with the words " +     
      "\n\t" + GUILD_NAME + ".\n embossed on the front " + 
      "cover.\n");

    add_item(({"letters","black letters","words"}),
      "The embossed letters read: " +
      "\n\t" + GUILD_NAME + ".\n");

    add_prop(OBJ_I_WEIGHT, 150);
    add_prop(OBJ_I_VOLUME, 400);
    add_prop(OBJ_M_NO_DROP, env_check);
    add_prop(OBJ_M_NO_GIVE, env_check);
}

void
setup_spells(object player, int spell)
{
    int known_spells = player->query_skill(SS_ARCANUM_SPELL_LIST);

    // We are just adding a spell here.
    if (spell)
	known_spells = spell;

    if (known_spells & SPELL_FLAMEWAVE)
	add_spell(MAGES_SPELLS + "flamewave");
//        add_spell("/w/tomas/wizday/spells/flamewave");
    if (known_spells & SPELL_HEAL)
        add_spell(MAGES_SPELLS + "heal");
    if (known_spells & SPELL_TELL)
        add_spell(MAGES_SPELLS + "tell");
}

/*
 * Function name:       env_check
 * Description  :       VBFC for the DROP and GIVE props,
 *                      which are only allowed if env is 
 *                      non-living (??) or a wizard.
 * Returns      :       int -- 0 if allowed, 1 if not.
 */
public int
env_check()
{

    object env = environment();

    if (!living(env) ||
      env->query_wiz_level()) 
    {
	return 0;
    }
    return 1;

} /* env_check */


void
enter_env(object env, object from)
{
    object temp;

    ::enter_env(env, from);
    add_spell_object(env);
    if (objectp(temp = present("arcanum_mages_spell_book", env)))
	temp->transfer_spells(env);
    set_alarm(1.0, 0.0, &setup_spells(env, 0));
}

void
leave_env(object from, object to) 
{
    remove_spell_object(from);
    ::leave_env(from, to);
}

varargs void
read_book_at_page(int which, string verb)
{
    object player = this_player();
    int skill = player->query_skill(SS_ARCANUM_SPELL_LIST);
    string txt;

    setuid(); seteuid(getuid());
    switch (which)
    {
    case 1:
	txt = "Magic used by the Mages of the Arcanum.";
	txt += "\n\n\n";
	txt += "     Page 1: ...............  Index.\n\n";
	if (!skill)
	{
	    txt += "The rest of the pages are blank.\n";
	    break;
	}
	if (skill & SPELL_FLAMEWAVE)
	    txt += "     Page 2: ...............  Roasting your enemies.\n\n";
	if (skill & SPELL_HEAL)
	    txt += "     Page 3: ...............  Healing.\n\n";
	if (skill & SPELL_TELL)
	    txt += "     Page 4: ...............  Chat with your friends.\n\n";
	if (skill & SPELL_HEAL)
	    txt += "     Page 5: ...............  Ways of Cleansing.\n\n";
	if (skill & SPELL_HEAL)
	    txt += "     Page 6: ...............  Ways of Seeing.\n\n";
	if (skill & SPELL_HEAL)
	    txt += "     Page 7: ...............  Ways of Warding against "+
	    "the undead.\n\n";
	if (skill & SPELL_HEAL)
	    txt += "     Page 8: ...............  Ways of Growth.\n\n";
	break;
    case 2:
	if (skill & SPELL_FLAMEWAVE)
	    txt = read_file(MAGES_SPELL_TXT + "flamewave.txt");
	else
	    txt = "The page is empty.\n";
	break;
    case 3:
	if (skill & SPELL_HEAL)
	    txt = read_file(MAGES_SPELL_TXT + "heal.txt");
	else
	    txt = "The page is empty.\n";
	break;
    case 4:
	if (skill & SPELL_TELL)
	    txt = read_file(MAGES_SPELL_TXT + "tell.txt");
	else
	    txt = "The page is empty.\n";
	break;
    case 5:
	if (skill & SPELL_HEAL)
	    txt = read_file(MAGES_SPELL_TXT + "heal.txt");
	else
	    txt = "The page is empty.\n";
	break;
    case 6:
	if (skill & SPELL_HEAL)
	    txt = read_file(MAGES_SPELL_TXT + "heal.txt");
	else
	    txt = "The page is empty.\n";
	break;
    case 7:
	if (skill & SPELL_HEAL)
	    txt = read_file(MAGES_SPELL_TXT + "heal.txt");
	else
	    txt = "The page is empty.\n";
	break;
    case 8:
	if (skill & SPELL_HEAL)
	    txt = read_file(MAGES_SPELL_TXT + "heal.txt");
	else
	    txt = "The page is empty.\n";
	break;
    }

    player->catch_tell(txt);
    return;
}

nomask int
use_component()
{
    return 1;
}
// Remove this when mudlib is fixed.

public int
start_spell_fail(string verb, string arg)
{
    object spell;

    gArg = arg;
    gCaster = this_player();
    gTargets = ({});

    if (!(spell = get_spell_object(verb)))
    {
	return 1;
    }

    /* I hate to have to do this here and again when the target is
     * acquired.  The problem is that I need to get information from
     * the spell to do the targeting, so I need to do setup for that.
     * I also want to allow the spell to be configured depending on
     * the targets, so I need to do setup for that as well.  The
     * alternative to repeating setup is to have a separate config
     * hook that only gets called after targets are found.  For now
     * I'm leaning toward repeating setup.
     */
    if (spell->do_spell_setup(0))
    {
	return 1;
    }

    if (spell->query_spell_pretarget())
    {
	gTargets = spell->target_spell(gCaster, arg);

	if (!sizeof(gTargets))
	{
	    return 1;
	}
    }

    if (spell->do_spell_setup(gCaster, gTargets, arg))
    {
	return 1;
    }

    return spell->concentrate_spell(gCaster, gTargets, arg);
}

