/* an axe wielded by a priestess of Ten Alders
 *  Ten Alders 
 *  Amelia 5/3/97
 *
 * Ckrik 9/2003 Upgrade hit/pen and made magical
 *
 * Make into spell enhancer Ckrik 2/6/2022 
 */

#pragma strict_types

inherit "/std/weapon";
inherit "/lib/keep";
inherit "/d/Genesis/specials/new/lib/spell_enhancer";

#include <wa_types.h>
#include <ss_types.h>
#include <stdproperties.h>
#include <macros.h>
#include <options.h>

#define PEN 45
#define TO_HIT 42
#define SPELL_POWER 43

#define BRAIN "/d/Earthsea/gont/tenalders/obj/items/brain"
#define PLACES ({"left cheek", "right cheek", "right ear", "left ear", \
    "nose", "left thigh", "face", "left calf", "right calf", \
    "left knee", "right knee", "right thigh", "back", "chin", "groin", \
    "buttocks"})
#define HOWS ({ "vigorously", "nastily", "viciously", "evilly", \
    "cruelly", "fiercely", "wickedly", "deftly", "expertly", "brutally", \
    "savagely", "fanatically", "sadistically" })

public void
create_weapon()
{
    set_name("axe");
    set_adj(({"crescent-moon", "mithril", "crescent"}));
    set_short("mithril crescent-moon axe");
    set_long("A crescent-moon mithril axe. The "+
        "head of the axe is shaped like a crescent moon, and "+
        "is honed as sharp as a razor. The long ebony haft "+
        "affixed to the back of the head has an engraving of "+
        "a cobra coiled as if to strike.\n");
    set_default_weapon(TO_HIT, PEN, W_AXE, W_BLUDGEON | W_IMPALE | W_SLASH,
		       W_RIGHT);
    // This value will affect spell damage for spellcasters.
    set_magic_spellpower(SPELL_POWER);
    set_spellpower_elements(({
        SS_ELEMENT_DEATH, SS_ELEMENT_AIR, SS_ELEMENT_FIRE, SS_ELEMENT_WATER
    }));
    add_prop(OBJ_I_WEIGHT, 7500);
    add_prop(OBJ_I_VALUE, 2450);
    add_prop(OBJ_M_NO_BUY, 1);
    add_prop(OBJ_I_IS_MAGIC_WEAPON, 1);
    add_prop(OBJ_S_WIZINFO, 
	     "A good axe that leaves behind a brain if hit by " +
	     "the special. The special is just a 1 in 8 " +
	     "cosmetically different attack.\n");
    add_prop(MAGIC_AM_ID_INFO,
	     ({"This weapon is magically enchanted.\n", 10,
		 "The weapon is enchanted to enable " +
		 "extra damage and hit rates.\n", 51}));
    add_prop(MAGIC_AM_MAGIC, ({ 30, "enchantment" }));
}

public varargs int
did_hit(int aid, string hdesc, int phurt, object enemy,
    int dt, int phit, int dam)
{
    object me, *us, corpse, brain;
    int y = random(20), z = random(4);
    string place = PLACES[random(16)], how = HOWS[random(13)],
        *verbs_third = ({ " hacks ", " chops ", " slices ", " slashes " }),
        *verbs_first = ({ " hack ", " chop ", " slice ", " slash " }),
        who;

    if(random(8))
    {
        return 0; 
    }

    ::did_hit(aid, hdesc, phurt, enemy, dt, phit, dam);

    us = ({ (me = query_wielded()), enemy });

    if(!(who = enemy->query_race_name()))
    {
        who = enemy->query_short();
    }

    if(me->query_npc())
    {
        me->trash_talk(enemy);
    }

    if(enemy->query_humanoid() && enemy->query_hp() <= 0 && phurt >= 0 &&
        !sizeof(enemy->query_leftover("brain")))
    {
        me->catch_msg("You cleave the head of " + QTNAME(enemy) +
            " wide open with the " + query_short() + ", and " +
            "brains and gore fly everywhere!\n");
        tell_room(environment(me), QCTNAME(me) + " cleaves the head " +
            "of " + QTNAME(enemy) + " with the " + query_short() +
            ", and brains and gore fly everywhere!\n", ({ me }));

        setuid();
        seteuid(getuid(this_object()));

        brain = clone_object("/std/leftover");
        brain->leftover_init("brain", who);
        brain->move(environment(me));

        tell_room(environment(me), "As " + QTNAME(enemy) + " dies, " +
            enemy->query_possessive() + " brains fly everywhere!\n",
            ({}));

        enemy->do_die(me);

/*
        corpse = present("corpse", environment(me));

        if(objectp(corpse))
        {
            corpse->set_short("mangled " + corpse->query_short());
        }
*/

        return 1;
    }

    switch(phurt)
    {
        case -1:
        case -2:
	    if (!enemy->query_option(OPT_GAG_MISSES))
	    {
	        enemy->catch_msg(QCTNAME(me) + " runs at you with the " +
                query_short() + "!\nYou dodge just in time and " +
                me->query_pronoun() + " misses you.\n");
	    }
	    if (!me->query_option(OPT_GAG_MISSES))
	    {
                me->catch_msg("You run at " + QTNAME(enemy) + " with your " +
                query_short() + " held aloft to crash " +
                enemy->query_possessive() + " skull, but " +
                enemy->query_pronoun() +
                " dodges just in time and you miss!\n");
	    }
            me->tell_watcher_miss(QCTNAME(me) + " runs at " + QTNAME(enemy) +
                " with the " + query_short() +
                " held aloft, ready to crush "+ enemy->query_possessive() +
                " skull, but " + QTNAME(enemy) +
                " dodges just in time and avoids the blow!\n", enemy, us);
        break;

        case 16..20:
            enemy->catch_msg(QCTNAME(me) + " viciously hacks your head " +
                "with the edge of the " + query_short() + "!\nYou are " +
                "almost decapitated!\n");
            me->catch_msg("You viciously hack at the head of " +
                QTNAME(enemy) + " with your " + query_short() +
                "!\nYou almost succeed in decapitating " +
                enemy->query_objective() + "!\n");
            me->tell_watcher(QCTNAME(me) + " viciously hacks at the " +
                "head of " + QTNAME(enemy) + " with the " + query_short() +
                "!\n" + QCTNAME(enemy) + " is almost decapitated!\n",
                enemy, us);
        break;

        default:
            enemy->catch_msg(QCTNAME(me) + " " + how + verbs_third[z] +
                "your " + place + " with the " + query_short() + ".\n");
            me->catch_msg("You " + how + verbs_first[z] + QTNAME(enemy) +
                "'s " + place + " with the blade of your " +
                query_short() + ".\n");
            me->tell_watcher(QCTNAME(me) + " " + how + verbs_third[z] +
                "at the "+ place + " of " + QTNAME(enemy) + " with " +
                me->query_possessive() + " " + query_short() + ".\n",
                enemy, us);
        break;
    }

    return 1;
}

public int
toss_it(string str)
{
    object tp = this_player(), to = this_object();

    if(!id(str))
    {
        return notify_fail("Toss what? Your cookies??\n");
    }

    if(!present(to, tp))
    {
        return notify_fail("You do not have the " + query_short() + ".\n");
    }

    if(!query_wielded())
    {
        return notify_fail("You do not wield the " + query_short() +".\n");
    }

    if(!CAN_SEE_IN_ROOM(tp))
    {
        return notify_fail("Toss this weapon in the dark? Are you crazy??\n");;
    }

    tp->catch_msg("You deftly toss the " + query_short() +
        " high into the air, light sparkling on the blade as it turns, " +
        "then miraculously catch it without cutting yourself!\n");
    tell_room(environment(tp), QCTNAME(tp) + " deftly tosses the " +
        query_short() + " high into the air, with light sparkling " +
        "on the sharp edges, and then miraculously catches it without " +
        "getting a scratch!\n", ({ tp }));

    return 1;
}

public void
init()
{
    ::init();
    add_action(toss_it, "toss");
}

void 
appraise_object(int num)
{
    ::appraise_object(num);
    write(item_spellpower_desc());
}

string 
stat_object() 
{
    return ::stat_object() + stat_object_spellpower();
}
