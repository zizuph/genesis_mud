/* 
 * The training room of Morgul mages, 
 *     by Randor
 *
 * Modification log:
 * 06-jan-1994 Olorin: skills added
 * 10-jan-1994 Olorin: morgul/tower/tower Master
 * 13-jan-1994 Olorin: here the upper skills are trained
 * 12-Jan-2019 Arman: AoB rebalancing of skills.
 *
 */
#pragma save_binary
#pragma strict_types

inherit "/d/Gondor/morgul/tower/tower";
inherit "/lib/skill_raise";
inherit "/d/Shire/lib/training";

#include <ss_types.h>
#include <stdproperties.h>
#include <macros.h>
#include <language.h>

#include "/d/Gondor/defs.h"
#include "/d/Gondor/morgul/tower/tower_defs.h"
#include "/d/Gondor/guilds/morgulmage/morgulmage.h"

/* A few definitions */
#define SS_MAGIC_ELEMENTS ({SS_ELEMENT_DEATH, SS_ELEMENT_LIFE,  \
                            SS_ELEMENT_FIRE,  SS_ELEMENT_WATER, \
                            SS_ELEMENT_EARTH, SS_ELEMENT_AIR   })
#define SS_MAGIC_FORMS    ({SS_FORM_TRANSMUTATION, SS_FORM_ILLUSION,    \
                            SS_FORM_ENCHANTMENT,   SS_FORM_DIVINATION,  \
                            SS_FORM_CONJURATION,   SS_FORM_ABJURATION  })

/* Function declaration */
void set_up_skills();

object murazor;

public void 
create_morgul_tower_room()
{
    set_level(5);
    set_room_type("large hall");
    set_extra_long(
        "This is the upper training hall of the Society of Morgul Mages. Here "+
        "an old archmage teaches important skills to aspiring young mages. "+
        "The walls are covered by bookcases that are full "+
        "of old, thick books. Here you may <learn> new skills, or <improve> "+
        "the skills you already have.");

    add_prop(ROOM_I_NO_ATTACK,1);
    add_prop(ROOM_I_NO_MAGIC_ATTACK,1);

    add_exit(MORGUL_ROOM_DIR + "tower_5c", "south", 0);

    create_skill_raise();
    set_up_skills();

    add_item(({"bookcase", "bookcases", "books", "book"}), 
        "The bookcases are full of old books. However, the library of the "+
        "tower is probably a better place if you want to learn ancient "+
        "knowledge.\n");
    WALLS
    FLOOR
    ROOF

    add_prop(ROOM_I_LIGHT, 1);
    
    setuid();
    seteuid(getuid());
    
    murazor = clone_object(MORGUL_NPC_DIR + "murazor");
    murazor->move(this_object(), 1);
}

public void 
init()
{
    init_skill_raise();
    ::init();
}

void 
set_up_skills()
{
    string me;

/* The Elements */
    me = "cast death spells";
    sk_add_train(SS_ELEMENT_DEATH,    ({ me, me }),  0,0, 100);
    me = "cast air spells";
    sk_add_train(SS_ELEMENT_AIR,      ({ me, me }),  0,0, 85);
    me = "cast fire spells";
    sk_add_train(SS_ELEMENT_FIRE,     ({ me, me }),  0,0, 90);
/* The Forms */
    me = "cast conjuration spells";
    sk_add_train(SS_FORM_CONJURATION, ({ me, me }),  0,0, 90);
    me = "make powerful enchantments";
    sk_add_train(SS_FORM_ENCHANTMENT, ({ me, me }),  0,0, 80);
    me = "cast illusion spells";
    sk_add_train(SS_FORM_ILLUSION, ({ me, me }),  0,0, 85);
    me = "cast divination spells";
    sk_add_train(SS_FORM_DIVINATION, ({ me, me }),  0,0, 40);
    me = "cast abjuration spells";
    sk_add_train(SS_FORM_ABJURATION, ({ me, me }),  0,0, 75);
/* others skills */
    me = "understand magic";
    sk_add_train(SS_SPELLCRAFT,       ({ me, me }),  0,0, 100);
    me = "recognize and handle herbs and plants";
    sk_add_train(SS_HERBALISM,        ({ me, me }),  0,0, 70);
    me = "mix potions from herbs and liquids";
    sk_add_train(SS_ALCHEMY,          ({ me, me }),  0,0, 50);
    me = "be aware of ones surroundings";
    sk_add_train(SS_AWARENESS,        ({ me, me }),  0,0, 50);
/* combat skills */
    me = "use a sword in combat";
    sk_add_train(SS_WEP_SWORD,        ({ me, me }),  0,0, 50); 
    me = "use a knife in combat";
    sk_add_train(SS_WEP_KNIFE,        ({ me, me }),  0,0, 40); 
    me = "to defend oneself";
    sk_add_train(SS_DEFENCE,          ({ me, me }),  0,0, 60);
}

public varargs int
sk_hook_allow_train(object who, string str, string verb)
{
    return (IS_MEMBER(TP) && !IS_APPRENTICE(TP));
}

public int
sk_hook_not_allow_train()
{
    murazor->command("rasp to " + OB_NAME(this_player())
      + " Go away! Only the higher ranks of Morgul Mages may "
      + "study our secret arts here!");
    return 1;
}

void
sk_hook_raise_rank(int snum, int to_lev, int cost)
{
    string rank, long_str;

    rank = sk_rank(to_lev);

    TP->catch_msg(QCTNAME(murazor) + " teaches you to "+
        sk_tdesc[snum][0] + " better.\n");
    write("You achieve the rank of " + rank + ".\n");    
    say(QCTNAME(murazor) + " teaches " + QTNAME(TP) + " to "
      + sk_tdesc[snum][1] + " better and " + TP->query_pronoun() 
      + " receives the rank of " + rank + ".\n");
}

varargs int
sk_query_max(int sknum, int silent)
{
    int     occup_stat = TP->query_stat(SS_OCCUP),
            stat_max = 90,
            max;

    /* Guru quest completed */
    if(TP->test_bit("gondor", MORGUL_GURU_GROUP, MORGUL_GURU_BIT)) 
        stat_max = 100;

    if (member_array(sknum,SS_MAGIC_ELEMENTS) >= 0)
    {
        stat_max = min(stat_max, TP->query_stat(SS_INT));
    }
    else if (member_array(sknum, SS_MAGIC_FORMS) >= 0)
    {
        stat_max = min(stat_max, TP->query_stat(SS_WIS));
    }

    if (stat_max > occup_stat)
        stat_max = occup_stat;

    max = ::sk_query_max(sknum, silent);

    return (stat_max > max ? max : stat_max);
}
 
