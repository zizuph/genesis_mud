/* 
 * The robe of the Mogul Mages for a npc mage and nazgul
 *
 * Olorin, 28-jul-1994
 * Modification log:
 */
#pragma save_binary
#pragma strict_types

inherit "/std/armour.c";

#include <formulas.h>
#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>
#include <wa_types.h>

#include "/d/Gondor/defs.h"
#include "/d/Gondor/common/guild2/lib/morgul_defs.h"

#define HIS(x)	(x)->query_possessive()

int     do_hood(string str);
int     do_reveal(string str, int silent = 0);

int     is_hooded;
string *save_adjs;

int     query_value() { return 0; }

void
create_armour()
{
    set_name(({"robe","cloak"}));
    add_name(({"morgul_guild_object", "token", "guild token", 
               "mage token","morgul token"}));
    set_adj(({"black", "hooded"}));
    set_short("black hooded robe");
    set_long("This is a large black robe, with a wide hood.\n");
    add_item(({"hood", "wide hood", }), BSN("When worn over the head "
      + "the wide hood of the robe will hide the features of the person "
      + "wearing the robe."));
    set_ac(2);
    set_af(TO);
    set_at(A_ROBE);
    add_prop(OBJ_I_VALUE,0);
    add_prop(OBJ_I_WEIGHT, 1200);
    add_prop(OBJ_I_VOLUME,  650);
    add_prop(OBJ_I_NO_DROP, 1);

    add_prop(MAGIC_I_RES_MAGIC, 20);
    add_prop(MAGIC_I_RES_DEATH, 80);
    add_prop(MAGIC_I_RES_ACID,  50);
    add_prop(OBJ_I_RES_MAGIC, 20);
    add_prop(OBJ_I_RES_DEATH, 80);
    add_prop(OBJ_I_RES_ACID,  50);

    add_prop(OBJ_I_IS_MAGIC_ARMOUR, 1);
    add_prop(OBJ_S_WIZINFO,
	     "This is the robe worn by npc members of the Society "
	   + "Morgul mages.\n");
    add_prop(MAGIC_AM_MAGIC,(({70,"abjuration"})));
    add_prop(MAGIC_AM_ID_INFO,({
        "The black robe looks like the robe Death is wearing.\n", 10,
        "It will not protect you much against attacks with a skillfully wielded weapon.\n",20,
        "But it emanates the air of magic.\n",50,
        "It protect you magically against foul and pestilent liquids.\n",70,
        "It will help the wearer to resist the power of deathly magic.\n",80 }));
    FIX_EUID;
}

void
check_spell_object(object player)
{
    if (!present("Morgul_Spell_Object", player))
        clone_object(GUILD_DIR + "spells/morgul_spells")->move(player, 1);
}

void
remove_hood(object wearer)
{
    if (wearer != ENV(TO))
        return;

    wearer->remove_adj(({"black-robed", "hooded", }));
    wearer->set_adj(save_adjs);
    wearer->set_hooded(0);

    is_hooded = 0;
}

mixed
remove(object ob)
{
    object  tp = TP;

    if ((ob != TO) || (tp != query_worn()))
        return -1;

    if (is_hooded)
        remove_hood(tp);

    if (!living(tp))
        return 0;

    tp->remove_magic_effect(TO);

    return 0;
}

mixed
wear(object ob)
{
    object  tp = ENV(TO);

    if ((ob != TO) || (TP != tp))
        return -1;

    if (tp->query_guild_name_occ() == GUILD_NAME)
    {
        tp->catch_msg("You wear the "+query_short()+" around your body.\n"+
              "You feel the dark power of Black Sorcery flowing through you.\n");
        tell_room(ENV(tp), QCTNAME(tp) + " wears the " + query_short() + ".\n", tp);
        check_spell_object(tp);
        present("Morgul_Spell_Object", tp)->update_morgul_spells();
        tp->add_magic_effect(TO);
        return 1;
    }
    tp->heal_hp(tp->query_max_hp()/20);
    tell_room(ENV(tp), "When "+QTNAME(tp)+" tries to wear the "+query_short()
      + ", it bursts out in flame in disappears.\n", tp);
    set_alarm(0.0, 0.0, remove_object);
    return "When you try to wear the "+query_short()+", it bursts out in flame and disappears.\n";
}

void
leave_env(object from, object to)
{
    if (is_hooded)
        remove_hood(from);

    ::leave_env(from, to);
}

mixed
query_magic_protection(string prop, object who = previous_object())
{
    if (who == query_worn())
    {
        switch(prop)
        {
        case MAGIC_I_RES_MAGIC:  return ({ 10, 1 });
        case MAGIC_I_RES_DEATH:  return ({ 40, 1 });
        case MAGIC_I_RES_ACID:   return ({ 25, 0 });
        }
    }

    return ::query_magic_protection(prop, who);
}

/* 
 * The robe of the Mogul Mages
 *
 * modified from the ranger ring
 *
 * Olorin, 05-jan-1994
 * Modification log:
 */

void
init()
{
    object  tp = TP;

    ::init();

    add_action(do_hood, "hood");
    add_action(do_hood, "wear");
    add_action(do_reveal, "reveal");
    add_action(do_reveal, "unhood");
    add_action(do_reveal, "remove");
}

int
do_hood(string str)
{
    object  tp = TP;
    string  vb = query_verb(),
            pron;

    if (vb == "hood")
        pron = "whom";
    else
        pron = "what";

    NFN(CAP(vb)+" "+pron+"?");
    if (!strlen(str))
        return 0;

    if ((vb == "hood") && (str != "me" && LOW(str) != ENV(TO)->query_real_name()))
        return 0;

    if ((vb == "wear") && (str != "hood"))
        return 0;

    if (ENV(TO) != tp)
    {
        NFN("You do not have the robe!");
        return 0;
    }

    if (query_worn() != tp)
    {
        NFN("You do not wear your robe!");
        return 0;
    }

    if (is_hooded)
    {
        NFN("You are already wearing your hood!");
        return 0;
    }

    write("You pull the hood of your robe over your head, concealing your features.\n");
    say(QCTNAME(tp)+" pulls the hood of "+HIS(tp)+" robe over "
      + HIS(tp) + " head, concealing " + HIS(tp) + " features.\n");

    save_adjs = tp->query_adjs();
    tp->remove_adj(save_adjs);
    tp->set_adj(({"black-robed","hooded"}));
    tp->set_hooded(1);
    is_hooded = 1;
    return 1;
}

int
do_reveal(string str, int silent = 0)
{
    string  vb = query_verb(),
            pron;

    switch (vb)
    {
        case "unhood":
        case "reveal":
            pron = "whom";
            break;
        case "mreveal":
            vb = "remove";
        case "remove":
            pron = "what";
            break;
    }

    NFN(CAP(vb)+ " "+pron+"?");
    if (!strlen(str))
        return 0;

    switch (vb)
    {
        case "unhood":
        case "reveal":
            if (str == "me")
                break;
            if (LOW(str) == ENV(TO)->query_real_name())
                break;
            NFN("You can only remove your own hood!");
            return 0;
            break;
        case "remove":
            if (str != "hood")
                return 0;
            break;
    }

    if (ENV(TO) != TP)
    {
        NFN("You do not have the robe!");
        return 0;
    }

    if (!is_hooded)
    {
        NFN("You are not wearing your hood!");
        return 0;
    }

    if (!silent)
    {
        write("You remove the hood and reveal your face again.\n");
        say(QCTNAME(TP)+" removes "+HIS(TP)+" hood.\n");
    }

    remove_hood(TP);
    return 1;
}
