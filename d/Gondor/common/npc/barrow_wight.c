/*
 * A barrow wight coded by Arren July 94
 *
 * Not much to say about this one, except I have never
 * coded a spell attack before.
 *
 * Modification log :
 * 941129 Made the spell work against all enemies. /Arren
 *  7-Feb-1997, Olorin:	Fixed magic resistance.
 *
 */
#pragma strict_types

inherit "/std/monster";

#include <cmdparse.h>
#include <comb_mag.h>
#include <filter_funs.h>
#include <formulas.h>
#include <macros.h>
#include <money.h>
#include <options.h>
#include <ss_types.h>
#include <stdproperties.h>

#include "/d/Gondor/defs.h"

#define MANA_COST 50
#define INCANTATION_PEN 70
#define SPELLCRAFT_NEEDED 40
#define CONCENTRATION_TIME 6.0

/*
 * Prototypes
 */
void arm_me();
void drain_living();
void spell_attack(object me, object enemy);
static void spell_effect(object me);
void do_die(object killer);
int bw_cast_spell(object me);
object *query_all_enemies();

void
create_monster()
{
    set_name("wight");
    add_name(({ "undead", "figure", "barrow-wight" }));
    set_race_name("wight");
    set_gender(G_NEUTER);

    set_long(BSN(
    "A tall and dark figure, gaunt and mummified, clad in tattered "+
    "clothing. Its eyes glowing coldly as if lit by a pale light. "+
    "Jewelry, dull, cold, and unlovely, hangs from its gaunt body. "));
    set_adj("barrow");
    set_alignment(-(650+random(150)));

    set_learn_pref(({2,2,2,1,1,1}));

    set_skill(SS_DEFENCE, 50);
    set_skill(SS_PARRY, 50);
    set_skill(SS_WEP_SWORD, 50);
    set_skill(SS_AWARENESS, 70);
    set_skill(SS_SPELLCRAFT, 70);
    set_skill(SS_FORM_CONJURATION, 70);
    set_skill(SS_FORM_ABJURATION, 50);
    set_skill(SS_FORM_ENCHANTMENT, 50);
    set_skill(SS_ELEMENT_EARTH, 50);
    set_skill(SS_ELEMENT_DEATH, 70);

    add_prop(CONT_I_HEIGHT, 195);
    add_prop(CONT_I_WEIGHT, 75000);
    add_prop(CONT_I_VOLUME, 75000);
    add_prop(LIVE_I_SEE_DARK, 5);
    add_prop(LIVE_I_SEE_INVIS, 1);
    add_prop(OBJ_I_RES_LIFE, 30);
    add_prop(OBJ_I_RES_DEATH, 90);
    add_prop(OBJ_I_RES_ELECTRICITY, 10);
    add_prop(OBJ_I_RES_POISON, 70);
    add_prop(LIVE_O_SPELL_ATTACK, TO);
    add_prop(LIVE_I_UNDEAD, 64);
    add_prop(LIVE_I_NO_CORPSE, 1);
    add_prop(NPC_I_NO_LOOKS, 1);
    add_prop(LIVE_I_NEVERKNOWN, 1);

    set_act_time(7);
    add_act("emote murmurs: Despair, the Dark Lord shall rule the world.");
    add_act("emote murmurs: Cursed be the Sun.");
    add_act("@@drain_living");

    set_cact_time(10);
    add_cact("emote murmurs: You will sleep till the Sun fails and "+
    "the Moon dies.");
    add_cact("emote murmurs: Soon you will be cold as ice.");
    add_cact("emote murmurs: Your bones will become dry and turn to dust.");
    add_cact("emote murmurs: I will relish the moment your heart "+
    "stops beating.");

    set_base_stat(SS_STR, 80 + random(10));
    set_base_stat(SS_DEX, 90 + random(10));
    set_base_stat(SS_CON, 90 + random(10));
    set_base_stat(SS_INT, 100 + random(10));
    set_base_stat(SS_WIS, 100 + random(10));
    set_base_stat(SS_DIS, 90 + random(10));

    set_all_hitloc_unarmed(25);

}

void
drain_living()
{
    object *ob;
    int i;
    object me = TO;

    ob = FILTER_LIVE(all_inventory(environment(me))) - ({ me });
    for (i = 0; i < sizeof(ob); i++)
    {
        if (!ob[i]->query_prop(LIVE_I_UNDEAD))
        {
             ob[i]->catch_msg(QCTNAME(TO) + " emanates cold, and you "+
             "feel faint.\n");
             ob[i]->add_tmp_stat(SS_CON, -(random(5) + 1), random(1000) + 100);
        }
     }
}

void
arm_me()
{
    object me = TO;

    FIX_EUID;

    clone_object(WEP_DIR + "old_sword")->move(me);
    command("wield all");

    clone_object(OBJ_DIR + "gold_ring")->move(me);
    clone_object(OBJ_DIR + "gold_chain")->move(me);
    command("wear all");

    MONEY_MAKE_GC( 1 + random(10))->move(me);
    MONEY_MAKE_SC(13 + random(12))->move(me);
}

int query_knight_prestige() { return 1200; }

static void
spell_effect(object me)
{
    object *ob;
    int i;

    ob = FILTER_LIVE(all_inventory(environment(me))) - ({ me });
    for (i = 0; i < sizeof(ob); i++)
    {
        if (ob[i]->query_option(OPT_BLOOD))
	{
	    if (ob[i]->query_skill(SS_SPELLCRAFT) > SPELLCRAFT_NEEDED)
		ob[i]->catch_msg("A death wave draining the very essence "+
				 "of your being emits from the wight.\n");
	    else 
		ob[i]->catch_msg("A wave of hatred and cold emits from the "+
				 "wight.\n");
	}
    }
}

void
spell_attack(object me, object enemy)
{
    int     i, hurt;
    mixed  *hitresult;
    string  how, how2;
    object *enemies;

    if(me->query_mana() < MANA_COST)
    {
        set_alarm(CONCENTRATION_TIME, 0.0, "bw_cast_spell", me);
        return;
    }
    if(random(10) < 3)
    {
        set_alarm(CONCENTRATION_TIME, 0.0, "bw_cast_spell", me);
        return;
    }
    me->add_mana(-MANA_COST);

    tell_room(ENV(me), QCTNAME(me) + " incants with a dreary "+
    "voice, using harsh and cold words.\n", me);
    me->catch_msg("You incant a song of despair and cold that pulls life "+
    "from the living.\n");
    spell_effect(me);

/*
 * The skill should really be me->query_skill(SS_SPELLCRAFT) but
 * INCANTATION_PEN is quicker. :)
 */
    hurt = F_PENMOD(INCANTATION_PEN, INCANTATION_PEN);

    enemies = query_all_enemies();
    for (i = 0; i < sizeof(enemies); i++)
    {

        hurt -= hurt * enemies[i]->query_magic_res(MAGIC_I_RES_DEATH) / 100;
        if (present(enemies[i], ENV(me)))
            hitresult = enemies[i]->hit_me(hurt, MAGIC_DT, me, 0);

        how = "unaffected.";
        how2 = "seems unaffected.";

        if (hitresult[0] > 0)
        {
            how = "the bite of a bitter wind.";
            how2 = "turns pale.";
        }
        if (hitresult[0] > 10)
        {
            how = "a cold numbing you.";
            how2 = "turns pale.";
        }
        if (hitresult[0] > 20)
        {
            how = "chilled to the marrow.";
            how2 = "start shivering.";
        }
        if (hitresult[0] > 30)
        {
            how = "icy claws gripping your body.";
            how2 = "start shivering.";
        }
        if (hitresult[0] > 50)
        {
            how = "your body becoming lifeless.";
            how2 = "gets an ashen face.";
        }
        if (hitresult[0] > 100)
        {
            how = "your last feeling. Your heart is frozen.";
            how2 = "becomes stiff as a corpse.";
        }
        enemies[i]->catch_msg("You feel " + how + "\n");
        tell_watcher(QCTNAME(enemies[i]) + " " + how2 + "\n", me, enemies[i]); 

        if (enemies[i]->query_hp() <= 0)
            enemies[i]->do_die(me);
    }
  
    set_alarm(CONCENTRATION_TIME, 0.0, "bw_cast_spell", me);
}

int
bw_cast_spell(object me)
{
    add_prop(LIVE_O_SPELL_ATTACK, me);
    return 1;
}

public object *
query_all_enemies()
{
    object *ob, *enemies, me = TO;
    int i;

    ob = FILTER_LIVE(all_inventory(ENV(me))) - ({ me });

    enemies = ({ });
    for (i = 0; i < sizeof(ob); i++)
    {
        if (member_array(me, ob[i]->query_enemy(-1)) >= 0)
            enemies += ({ ob[i] });
    }
    return enemies;
}

void
do_die(object killer)
{
    object me = TO;

    tell_room(ENV(me), QCTNAME(me) + " shrivels away to nothing with a "+
    "shriek of despair.\n", me);
    
    ::do_die(killer);
}
