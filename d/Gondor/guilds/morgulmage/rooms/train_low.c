/* 
 * The training room of Morgul mages, by Randor
 *
 * Modification log:
 * 06-jan-1994 Olorin: skills added
 * 10-jan-1994 Olorin: morgul/tower/tower Master
 * 13-jan-1994 Olorin: here only the lower skills are trained
 *  5-feb-1997 Olorin: changed skill levels that can be trained
 * 21-apr-1997 Gorboth: added ROOM_I_NO_CLEANUP for droproom purposes
 * 30-aug-2006 Toby: Fixed typo 'stare you' -> 'stare you down'
 * 28-feb-2009 Eowul: Moved to the new guild directory
 * 27-may-2014 Gorboth: Added needed skills for new apprentice-level spells
 *                    :   - Illusion (10), Divination (10)
 * 10-jan-2015 Mercade: Increased illusion to 30, minimum maxtrain at 25.
 * 12-Jan-2019 Arman: AoB rebalancing of skills, min maxtrain now 35.
 */
#pragma save_binary
#pragma strict_types

inherit "/d/Gondor/morgul/tower/tower";
inherit "/lib/skill_raise";
inherit "/d/Shire/lib/training";

#include <language.h>
#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>

#include "/d/Gondor/defs.h"
#include "/d/Gondor/morgul/tower/tower_defs.h"
#include "/d/Gondor/guilds/morgulmage/morgulmage.h"

/* A few definitions */
#define CLOSED          0       /* 1 = closed,   0 = open.  */

#define SS_MAGIC_ELEMENTS ({SS_ELEMENT_DEATH, SS_ELEMENT_LIFE,  \
                            SS_ELEMENT_FIRE,  SS_ELEMENT_WATER, \
                            SS_ELEMENT_EARTH, SS_ELEMENT_AIR   })
#define SS_MAGIC_FORMS    ({SS_FORM_TRANSMUTATION, SS_FORM_ILLUSION,    \
                            SS_FORM_ENCHANTMENT,   SS_FORM_DIVINATION,  \
                            SS_FORM_CONJURATION,   SS_FORM_ABJURATION  })

/* 
 *	Function declaration 
 */
private void    set_up_skills();

/*
 *	Global variables:
 */
static  int     closed = CLOSED;

void 
create_morgul_tower_room()
{
    set_level(4);
    set_room_type("large hall");
    set_extra_long(
        "This is the apprentice training hall of the Society of Morgul Mages. " +
        "Here an old mage teaches important skills to young apprentices who shall "+
        "once become mages. The walls are covered by bookcases that are full "+
        "of old, thick books. Here you may <learn> new skills, or <improve> "+
        "the skills you already have. A wire cage hangs from the ceiling,"
      + " and a deep alcove is set in the western wall. ");
    add_prop(OBJ_S_WIZINFO, "@@wizinfo");

    add_exit(MORGUL_ROOM_DIR + "tower_4c", "east", 0);

    create_skill_raise();
    set_up_skills();

    add_item(({"mage","teacher","archmage"}), 
        "He seems to be rather old. A black hood covers his "+
        "head, but you can see fiery eyes under the hood. He begins to stare "+
        "you down as you look at him. You shiver slightly and turn your gaze "+
        "away from him.\n");
    add_item(({"bookcase", "bookcases", "books", "book"}), 
        "The bookcases are full of old books. However, the library of the "+
        "tower is probably a better place if you want to learn ancient "+
        "knowledge.\n");
    WALLS
    FLOOR
    ROOF

    add_prop(ROOM_I_LIGHT, 1);
    add_prop(ROOM_I_NO_CLEANUP, 1); // For droproom purposes

    clone_object(MORGUL_OBJ_DIR + "wire_cage")->move(this_object(), 1);
    room_add_object(MORGUL_OBJ_DIR + "alcove");
}

string 
wizinfo()
{
   return ("This is one of the training rooms of the Morgul mages. All low\n"+
           "level skills are taught here.\n"+
           "If there should be due cause to close down the guild, do so by\n"+
           "typing:  Call here close_guild\n"+
           "This will temporarily prevent mortals from entering. After a\n"+
           "reboot, the guild will be open by default. Please send me some\n"+
           "mail if there is anything that needs to be fixed.\n\n   /Olorin.\n");
}

void 
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);

    if (!interactive(ob) || !closed)
        return;

    if (ob->query_wiz_level())
        write("\n\nWARNING!\nYou shouldn't be here. "+
            "I'm doing some work on the guild.\n");
    else
    {
        write("The guild is closed. Come back later.\n");
        ob->move(MAGES_DIR+"tow2");
    }
}

void 
init()
{
    init_skill_raise();
    ::init();
}

string 
close_guild()
{
    if (closed)
    {
        closed = 0;
        return "  **The guild is now open**";
    }
    closed = 1;
    return "  **The guild is now closed**";
}

int query_closed() { return closed; }

void 
set_up_skills()
{
    string me;

/* The Elements */
    me = "cast death spells";
    sk_add_train(SS_ELEMENT_DEATH,    ({ me, me }),  0,0, 50);
    me = "cast air spells";
    sk_add_train(SS_ELEMENT_AIR,      ({ me, me }),  0,0, 75);
    me = "cast fire spells";
    sk_add_train(SS_ELEMENT_FIRE,     ({ me, me }),  0,0, 60);
/* The Forms */
    me = "cast conjuration spells";
    sk_add_train(SS_FORM_CONJURATION, ({ me, me }),  0,0, 60);
    me = "make powerful enchantments";
    sk_add_train(SS_FORM_ENCHANTMENT, ({ me, me }),  0,0, 50);
    me = "cast protection spells";
    sk_add_train(SS_FORM_ABJURATION, ({ me, me }),  0,0, 40);
    me = "cast illusion spells";
    sk_add_train(SS_FORM_ILLUSION, ({ me, me }),  0,0, 35);
    me = "cast divination spells";
    sk_add_train(SS_FORM_DIVINATION, ({ me, me }),  0,0, 40);
/* others skills */
    me = "understand magic";
    sk_add_train(SS_SPELLCRAFT,       ({ me, me }),  0,0, 75);
    me = "recognize and handle herbs and plants";
    sk_add_train(SS_HERBALISM,        ({ me, me }),  0,0, 60);
    me = "mix potions from herbs and liquids";
    sk_add_train(SS_ALCHEMY,          ({ me, me }),  0,0, 30);
/* combat skills */
    me = "use a sword in combat";
    sk_add_train(SS_WEP_SWORD,        ({ me, me }),  0,0, 50);  
    me = "defend oneself";
    sk_add_train(SS_DEFENCE,          ({ me, me }),  0,0, 50);
}

int
sk_improve(string str)
{
    if (TP->query_guild_name_occ() != GUILD_NAME)
    {
        write(BSN("The archmage says: Go away! Only the members of Morgul mages "+
           "may study our secret arts here!"));
        return 1;
    }

    return ::sk_improve(str);
}

void
sk_hook_raise_rank(int snum, int to_lev, int cost)
{
    string rank, long_str;

    rank = sk_rank(to_lev);

    TP->catch_msg("The archmage teaches you to "+
        sk_tdesc[snum][0] + " better.\n");
    write("You achieve the rank of " + rank + ".\n");
    say("The archmage teaches " + QTNAME(TP) + " to "+
        sk_tdesc[snum][1] + " better and " + TP->query_pronoun() + " receives "+
        "the rank of " + rank + "\n.");
}

varargs int
sk_query_max(int sknum, int silent)
{
    int occup_stat = max(35, TP->query_stat(SS_OCCUP));
    int learnmax = 90;

    if (IN_ARRAY(sknum, SS_MAGIC_ELEMENTS))
    {
        learnmax = TP->query_stat(SS_INT);
    }
    if (IN_ARRAY(sknum, SS_MAGIC_FORMS))
    {
        learnmax = TP->query_stat(SS_WIS);
    }

    return min(learnmax, occup_stat, ::sk_query_max(sknum, silent));
}
