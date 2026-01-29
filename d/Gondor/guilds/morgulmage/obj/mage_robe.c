/* 
 *  /d/Gondor/guilds/morgulmage/obj/mage_robe.c
 *
 *  Robe for the morgul mages. Unlike the previous version,
 *  the new spellcasting system no longer requires a spell
 *  object, as such this robe is transformed into one that
 *  just hides the mages identity.
 *
 *  Eowul, Februari 2013  
 */
#pragma save_binary
#pragma strict_types

inherit "/std/object";
inherit "/lib/wearable_item";

#include <files.h>
#include <formulas.h>
#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>
#include <wa_types.h>

#include "../morgulmage.h"

object hood_shadow;
int spellcraft_boost;
int deathmagic_boost;

// This is temporarily provided until the guru quest is available.
#define SKILL_BOOST 10

public int valid_owner();

#include <time.h>
#include <formulas.h>
#include <state_desc.h>

/*
 * Function name: create_object
 * Description:   Creator.
 */
public void 
create_object()
{
    set_name(({ "robe", "cloak" }));
    add_name(({ "morgul_guild_object", "token", "guild token", 
        "mage token", "morgul token", MORGUL_S_SPELL_OBJECT }));
    set_adj(({"large", "black", "hooded"}));
    set_short("black hooded robe");
    set_long("This is a large black robe, with a wide hood. You sense "+
        "a great yet dark power emanating from it.\n");
    add_item(({"hood", "wide hood", }), "When worn over the head "
        + "the wide hood of the robe will hide the features of the "
        + "person wearing the robe.\n");

    set_wf(this_object());
    set_slots(A_ROBE);

    add_prop(OBJ_I_VALUE,     0);
    add_prop(OBJ_I_WEIGHT, 1200);
    add_prop(OBJ_I_VOLUME,  650);
    add_prop(OBJ_I_NO_DROP,   1);
    add_prop(OBJ_M_NO_GIVE,   1);

    set_looseness(20);
    set_layers(1);
}

public mixed remove(object ob)
{    
    environment(ob)->remove_nifarist_shadow();

    if (objectp(hood_shadow)) {
        hood_shadow->remove_hood_shadow();
        hood_shadow = 0;
    }
    if (spellcraft_boost)
    {
        wearer->set_skill_extra(SS_SPELLCRAFT,
            wearer->query_skill_extra(SS_SPELLCRAFT)
             - spellcraft_boost);
        spellcraft_boost = 0;
    }
    if (deathmagic_boost)
    {
        wearer->set_skill_extra(SS_ELEMENT_DEATH,
            wearer->query_skill_extra(SS_ELEMENT_DEATH)
             - deathmagic_boost);
        deathmagic_boost = 0;
    }

    return 0;
}

public mixed wear( object ob )
{
    if (ob != this_object())
    {
        return -1;
    }

    if (!valid_owner())
    {
        return -1;
    }

    int spell_extra = wearer->query_skill_extra(SS_SPELLCRAFT);
    int death_extra = wearer->query_skill_extra(SS_ELEMENT_DEATH);

    if (spell_extra >= 0 && wearer->query_base_skill(SS_SPELLCRAFT) >= 90)
    {
        spellcraft_boost = min(SKILL_BOOST, 100 - wearer->query_skill(SS_SPELLCRAFT));
        wearer->set_skill_extra(SS_SPELLCRAFT, spell_extra + spellcraft_boost);
    }

    if (death_extra >= 0 && wearer->query_base_skill(SS_ELEMENT_DEATH) >= 90)
    {
        deathmagic_boost = min(SKILL_BOOST, 100 - wearer->query_skill(SS_ELEMENT_DEATH));
        wearer->set_skill_extra(SS_ELEMENT_DEATH, death_extra + deathmagic_boost);
    }

    return 0;
}

/*
 * Function name: valid_owner
 * Description  : Checks whether the owner has the rights to this robe
 */
public int valid_owner()
{
    object user = this_player();

    if ((user->query_guild_name_occ() != GUILD_NAME) &&
        (!user->query_wiz_level())) {
        return 0;
    }

    return 1;
}

/*
 * Function name: query_recover
 * Description  : no recovery, since the robe autoloads
 * Returns      : 0
 */
public string query_recover()
{
    return 0;
}

/*
 * Function name: leave_env
 * Description:   remove the hood shadow if the robe leaves its
 *                environment 
 * Arguments:     from - old environment, to - new environment
 */
public void
leave_env(object from, object to)
{
    if (objectp(hood_shadow))
    {
        from->remove_nifarist_shadow();
        hood_shadow->remove_hood_shadow();
        hood_shadow = 0;
    }

    ::leave_env(from, to);
}

/*
 * Function name : do_hood
 * Description   : wear the hood
 * Argument      : command verb argument
 * Returns       : 1/0
 */
public int do_hood(string str)
{
    if ((query_verb() == "hood") && (!str || str != "me")) {
        notify_fail("Hood whom?\n");
        return 0;
    }

    if ((query_verb() == "wear") && (!str || str != "hood")) {
        notify_fail("Wear what?\n");
        return 0;
    }

    if (query_worn() != this_player())
    {
        notify_fail("You do not wear your robe!\n");
        return 0;
    }

    if (this_player()->query_mm_mounted())
    {
        notify_fail("You are too busy riding to hood yourself.\n");
        return 0;
    }

    if (this_player()->query_hooded())
    {
        notify_fail("You are already wearing your hood!\n");
        return 0;
    }

    write("You pull the hood of your robe over your head, concealing "
        + "your features.\n");
    say(QCTNAME(this_player()) + " pulls the hood of " 
        + this_player()->query_possessive() + " robe over "
        + this_player()->query_possessive() + " head, concealing "
        + this_player()->query_possessive() + " features.\n");

    setuid();
    seteuid(getuid());
    hood_shadow = clone_object(MORGUL_OBJ_DIR + "mage_robe_shadow");
    hood_shadow->shadow_me(this_player());
    return 1;
}

/*
 * Function name: do_reveal
 * Description:   remove the hood
 * Argument:      str - argument
 *                silent - write no message if 1
 * Returns:       1/0
 */
public int do_reveal( string str, int silent = 0 )
{
    switch (query_verb())
    {
        case "unhood":
        case "reveal":
            if (!str || str != "me") {
                notify_fail(capitalize(query_verb()) + " whom?\n");
                return 0;
            }
            break;
        case "remove":
            if (!str || str != "hood") {
                notify_fail("Remove what?\n");
                return 0;
            }
            break;
    }

    if (!this_player()->query_hooded())
    {
        notify_fail("You are not wearing your hood!\n");
        return 0;
    }

    if (this_player()->query_mm_mounted())
    {
        write("You are too busy riding to remove your hood.\n");
        return 1;
    }

    write("You remove the hood and reveal your face again.\n");
    say(QCTNAME(this_player()) + " removes " 
        + this_player()->query_possessive() + " hood.\n");

    this_player()->remove_nifarist_shadow();
    hood_shadow->remove_hood_shadow();
    hood_shadow = 0;
    return 1;
}

int
do_vitals(string str)
{
    if (strlen(str))
    {
        return CMD_LIVE_STATE->vitals(str);
    }
    CMD_LIVE_STATE->vitals("health");
    CMD_LIVE_STATE->vitals("panic");
    CMD_LIVE_STATE->vitals("alignment");
    CMD_LIVE_STATE->vitals("encumbrance");
    CMD_LIVE_STATE->vitals("age");
    return 1;
}

public void init()
{
    ::init();

    add_action(do_hood  , "hood");
    add_action(do_hood  , "wear");
    add_action(do_reveal, "reveal");
    add_action(do_reveal, "unhood");
    add_action(do_reveal, "remove");
    add_action(do_vitals, "vitals");
    add_action(do_vitals, "v");
}
