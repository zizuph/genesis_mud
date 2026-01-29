/* 
 * The training room of Morgul mages, 
 *     by Randor
 *
 * Modification log:
 * 06-jan-1994 Olorin: skills added
 * 10-jan-1994 Olorin: morgul/tower/tower Master
 * 13-jan-1994 Olorin: here the upper skills are trained
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
#include "/d/Gondor/common/guild2/lib/morgul_defs.h"

/* A few definitions */
#define CLOSED          0       /* 1 = closed,   0 = open.  */

#define SS_MAGIC_ELEMENTS ({SS_ELEMENT_DEATH, SS_ELEMENT_LIFE,  \
                            SS_ELEMENT_FIRE,  SS_ELEMENT_WATER, \
                            SS_ELEMENT_EARTH, SS_ELEMENT_AIR   })
#define SS_MAGIC_FORMS    ({SS_FORM_TRANSMUTATION, SS_FORM_ILLUSION,    \
                            SS_FORM_ENCHANTMENT,   SS_FORM_DIVINATION,  \
                            SS_FORM_CONJURATION,   SS_FORM_ABJURATION  })

/* Function declaration */
void set_up_skills();

int closed = 0;

public void 
create_morgul_tower_room()
{
    closed = CLOSED;
    set_level(5);
    set_room_type("large hall");
    set_extra_long(
        "This is the upper training hall of the Society of Morgul Mages. Here "+
        "an old archmage teaches important skills to aspiring young mages. "+
        "The walls are covered by bookcases that are full "+
        "of old, thick books. Here you may <learn> new skills, or <improve> "+
        "the skills you already have.");
    add_prop(OBJ_S_WIZINFO, "@@wizinfo");
    add_prop(ROOM_I_NO_ATTACK,1);
    add_prop(ROOM_I_NO_MAGIC_ATTACK,1);

    add_exit(MAGES_DIR + "tower/tower_5c", "south", 0);

    create_skill_raise();
    set_up_skills();

    add_item(({"mage","teacher","archmage"}), BSN(
        "He seems to be very old. A black hood covers his "+
        "head, but you can see fiery eyes under the hood. He begins to stare "+
        "you as you look at him. You shiver slightly and turn your gaze away "+
        "from him."));
    add_item(({"bookcase", "bookcases", "books", "book"}), BSN(
        "The bookcases are full of old books. However, the library of the "+
        "tower is probably a better place if you want to learn ancient "+
        "knowledge.\n"));
    WALLS
    FLOOR
    ROOF

    add_prop(ROOM_I_LIGHT, 1);
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

public void 
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);

    if (!query_ip_number(ob) || !closed)
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

public void 
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

/* Sum = 640, of these 20 are tax free (20 of SPELLCRAFT) */
/* The Elements (Sum <= 200)  Sum = 200 */
    me = "cast death spells";
    sk_add_train(SS_ELEMENT_DEATH,    ({ me, me }),  0,0, 90);
    me = "cast air spells";
    sk_add_train(SS_ELEMENT_AIR,      ({ me, me }),  0,0, 70);
    me = "cast fire spells";
    sk_add_train(SS_ELEMENT_FIRE,     ({ me, me }),  0,0, 40);
/* The Forms (Sum <= 200) Sum = 200 */
    me = "cast conjuration spells";
    sk_add_train(SS_FORM_CONJURATION, ({ me, me }),  0,0, 80);
    me = "make powerful enchantments";
    sk_add_train(SS_FORM_ENCHANTMENT, ({ me, me }),  0,0, 80);
    me = "cast transmutation spells";
    sk_add_train(SS_FORM_TRANSMUTATION, ({ me, me }),  0,0, 40);
/* others skills Sum = 180 */
    me = "understand magic";
    sk_add_train(SS_SPELLCRAFT,       ({ me, me }),  0,0, 90);
    me = "recognize and handle herbs and plants";
    sk_add_train(SS_HERBALISM,        ({ me, me }),  0,0, 60);
    me = "mix potions from herbs and liquids";
    sk_add_train(SS_ALCHEMY,          ({ me, me }),  0,0, 30);
/* combat skills  Sum =  60 */
/*  me = "use a knife in combat";
    sk_add_train(SS_WEP_KNIFE,        ({ me, me }),  0,0, 70); */
    me = "to defend oneself";
    sk_add_train(SS_DEFENCE,          ({ me, me }),  0,0, 60);
}

int
sk_improve(string str)
{
    if (TP->query_guild_name_occ() != GUILD_NAME ||
        TP->query_morgul_level() <= APPRENTICE_LEVEL)
    {
        write(BSN("The archmage says: Go away! Only the higher ranks of Morgul mages "+
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
    int     occup_stat = TP->query_stat(SS_OCCUP),
            stat_max = 90,
            max;

    if (member_array(sknum,SS_MAGIC_ELEMENTS) >= 0)
    {
        stat_max = TP->query_stat(SS_INT);
    }
    else if (member_array(sknum, SS_MAGIC_FORMS) >= 0)
    {
        stat_max = TP->query_stat(SS_WIS);
    }

    if (stat_max > occup_stat)
        stat_max = occup_stat;

    max = ::sk_query_max(sknum, silent);

    return (stat_max > max ? max : stat_max);
}
 
