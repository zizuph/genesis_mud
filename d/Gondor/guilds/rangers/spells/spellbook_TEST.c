/*
 * /d/Gondor/guilds/rangers/spells/spellbook.c
 *
 * Modification log:
 *   Alto, February 2002. Move, no major modifications.
 */
#include "../rangers.h"
#include "/d/Gondor/defs.h"
#include <stdproperties.h>

inherit "/std/book";
inherit "/d/Genesis/newmagic/spellcasting";

// Prototypes
public static int env_check();

void
create_book()
{
    set_max_pages(8);
    set_name(({ "book", "_new_ranger_spellbook", "ranger_spell_book",
        "spellbook" }));
    set_adj(({ "brown", "little", "leatherbound", }));
    set_short("little brown book");
    set_long("The brown leatherbound book still smells of animal hides, " +
      "fresh as if it has just been made. You can sense a strange " +
      "feeling of magic about it, confirmed by a few words in " +
      "swirling black letters written on the front:" +
      "\n\tMagic of the Rangers.\n");

    add_item(({"letters", "black letters", "words"}),
      "The elaborate black letters are not easy to read, " +
      "but you find that they read: Magic of the Rangers.\n");

    add_prop(OBJ_I_WEIGHT, 250);
    add_prop(OBJ_I_VOLUME, 503);
    add_prop(OBJ_M_NO_DROP, env_check);
    add_prop(OBJ_M_NO_GIVE, env_check);
}

void
setup_spells(object player, int spell)
{
    int known_spells = player->query_skill(SS_RANGER_SPELL_LIST);

    // We are just adding a spell here.
    if (spell)
        known_spells = spell;

    add_spell(RANGERS_SPELL + "dispell");

    if (known_spells & SPELL_WHISTLE)
        add_spell(RANGERS_SPELL + "whistle");

    if (known_spells & SPELL_HEAL)
        add_spell(RANGERS_SPELL + "heal");

    if (known_spells & SPELL_CLEANSE)
        add_spell(RANGERS_SPELL + "cleanse");

    if (known_spells & SPELL_REST)
        add_spell(RANGERS_SPELL + "rest");

    if (known_spells & SPELL_NIGHTVISION)
        add_spell(RANGERS_SPELL + "nightvision");

    if (known_spells & SPELL_ELBERETH)
        add_spell(RANGERS_SPELL + "elbereth");

    if (known_spells & SPELL_SPEEDGROW)
        add_spell(RANGERS_SPELL + "speedgrow");

    if (known_spells & SPELL_BLESS)
        add_spell(RANGERS_SPELL + "bless");

    if (known_spells & SPELL_CONCEAL)
        add_spell(RANGERS_SPELL + "conceal");
}

/*
 * Function name: env_check
 * Description  : VBFC for the DROP and GIVE props,
 *                which are only allowed if env is 
 *                non-living (??) or a wizard.
 * Returns      : int -- 0 if allowed, 1 if not.
 */
public int
env_check()
{
    object env = environment();

    if (!living(env) || env->query_wiz_level()) 
        return 0;

    return 1;
}

void
enter_env(object env, object from)
{
    object temp;

    ::enter_env(env, from);

    add_spell_object(env);

    if (objectp(temp = present("_old_ranger_spellbook", env)))
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
    int skill = player->query_skill(SS_RANGER_SPELL_LIST);
    string txt;

    setuid();
    seteuid(getuid());

    switch (which)
    {
    case 1:
        txt = "Magic in Nature as used by the Rangers and Clerics.";
        txt += "\n\n\n";
        txt += "     Page 1: ...............  Index.\n\n";
        if (!skill)
        {
            txt += "The rest of the pages are blank.\n";
            break;
        }

        if (skill & SPELL_WHISTLE)
            txt += "     Page 2: ...............  Ways of Communing.\n\n";
        if (skill & SPELL_REST)
            txt += "     Page 3: ...............  Ways of Resting.\n\n";
        if (skill & SPELL_HEAL)
            txt += "     Page 4: ...............  Ways of Healing.\n\n";
        if (skill & SPELL_CLEANSE)
            txt += "     Page 5: ...............  Ways of Cleansing.\n\n";
        if (skill & SPELL_NIGHTVISION)
            txt += "     Page 6: ...............  Ways of Seeing.\n\n";
        if (skill & SPELL_ELBERETH)
            txt += "     Page 7: ...............  Ways of Warding against " +
                "the undead.\n\n";
        if (skill & SPELL_SPEEDGROW)
            txt += "     Page 8: ...............  Ways of Growth.\n\n";
        if (skill & SPELL_BLESS)
            txt += "     Page 9: ...............  Ways of Blessing.\n\n";
        if (skill & SPELL_CONCEAL)
            txt += "     Page 10: ..............  Ways of Concealing.\n\n";
        break;
    case 2:
        if (skill & SPELL_WHISTLE)
            txt = read_file(RANGER_SPELL_TXT + "whistle.txt");
        else
            txt = "The page is empty.\n";
        break;
    case 3:
        if (skill & SPELL_REST)
            txt = read_file(RANGER_SPELL_TXT + "rest.txt");
        else
            txt = "The page is empty.\n";
        break;
    case 4:
        if (skill & SPELL_HEAL)
            txt = read_file(RANGER_SPELL_TXT + "heal.txt");
        else
            txt = "The page is empty.\n";
        break;
    case 5:
        if (skill & SPELL_CLEANSE)
            txt = read_file(RANGER_SPELL_TXT + "cleanse.txt");
        else
            txt = "The page is empty.\n";
        break;
    case 6:
        if (skill & SPELL_NIGHTVISION)
            txt = read_file(RANGER_SPELL_TXT + "nightvision.txt");
        else
            txt = "The page is empty.\n";
        break;
    case 7:
        if (skill & SPELL_ELBERETH)
            txt = read_file(RANGER_SPELL_TXT + "elbereth.txt");
        else
            txt = "The page is empty.\n";
        break;
    case 8:
        if (skill & SPELL_SPEEDGROW)
            txt = read_file(RANGER_SPELL_TXT + "speedgrow.txt");
        else
            txt = "The page is empty.\n";
        break;
    case 9:
        if (skill & SPELL_BLESS)
            txt = read_file(RANGER_SPELL_TXT + "bless.txt");
        else
            txt = "The page is empty.\n";
        break;
    case 10:
        if (skill & SPELL_CONCEAL)
            txt = read_file(RANGER_SPELL_TXT + "conceal.txt");
        else
            txt = "The page is empty.\n";
        break;
    }

    player->more(txt);
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
        return 1;

    if (spell->query_spell_pretarget())
    {
        gTargets = spell->target_spell(gCaster, arg);

        if (!sizeof(gTargets))
            return 1;
    }

    if (spell->do_spell_setup(gCaster, gTargets, arg))
        return 1;

    return spell->concentrate_spell(gCaster, gTargets, arg);
}

