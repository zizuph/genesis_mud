#include "defs.h"

inherit "/lib/guild_support";
inherit "/lib/skill_raise";

#include <ss_types.h>
#include <stdproperties.h>
#include <macros.h>
#include <language.h>
#include <money.h>

void set_up_skills();

void
create_rivendell_room()
{
    set_short("Training Hall");
    set_long(
	"This is the place where the Healers gain knowledge upon "+
	"the art of spellcasting. Here you can <learn> and <improve> skills "+
	"related to spellcasting, and you can <meditate> to set your preferred"+
	"settings with regards to what stats you would like to improve.");

    add_exit(STAND_DIR+"passage2", "north");

    add_prop(ROOM_I_INSIDE, 1);
    add_prop(ROOM_I_LIGHT,  1);

    create_skill_raise();
    create_guild_support();
    set_up_skills();
}

void
init()
{
    ::init();
    init_guild_support();
    init_skill_raise();
}

void
set_up_skills()
{
    sk_add_train(SS_SPELLCRAFT, "cast spells",			0, 0, 90);
    sk_add_train(SS_HERBALISM,	({ "herblore",	"herblore" }),	0, 0, 50);
    sk_add_train(SS_ALCHEMY,	"use alchemical knowledge",	0, 0, 30);
    sk_add_train(SS_LANGUAGE,	"understand languages",		0, 0, 50);

    sk_add_train(SS_FORM_CONJURATION,  "conjure",		0, 0, 40);
    sk_add_train(SS_FORM_ABJURATION,   "abjure",		0, 0, 75);
    sk_add_train(SS_FORM_DIVINATION,   "make divinations",	0, 0, 35);
    sk_add_train(SS_FORM_ENCHANTMENT,  "enchant",		0, 0, 50);

    sk_add_train(SS_ELEMENT_LIFE, "cast life-giving spells",	0, 0, 90);
    sk_add_train(SS_ELEMENT_AIR,  "control air",		0, 0, 70);
    sk_add_train(SS_ELEMENT_FIRE, "control fire",		0, 0, 60);
    sk_add_train(SS_ELEMENT_WATER,"control water",		0, 0, 50);
    sk_add_train(SS_ELEMENT_EARTH,"control earth",		0, 0, 30);
}

int
sk_improve(string str)
{
    /* Is the player a guildmember? */
    if (!(this_player()->test_bit("Shire", 1, 0)))
    {
	write("Only members of the Sula a Imladris can do that here!\n");
	return 1;
    }
    return ::sk_improve(str);
}
