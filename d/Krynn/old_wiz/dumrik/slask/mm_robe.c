/* 
 * The robe of the Mogul Mages
 *
 * modified from the ranger ring
 *
 * Olorin, 05-jan-1994
 * Modification log:
 */
inherit "/std/armour";

#include <formulas.h>
#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>
#include <wa_types.h>

#include "/d/Gondor/defs.h"
#include "/d/Gondor/common/guild2/lib/morgul_defs.h"

#define HIS(x)	(x)->query_possessive()

int     inited;
object  shadow;

int query_value() { return 0; }

void
create_armour()
{
    set_name(({"robe","cloak"}));
    add_name(({"morgul_guild_object", "token", "guild token", 
               "mage token","morgul token"}));
    set_adj(({"black", "hooded"}));
    set_short("black hooded robe");
    set_long("This is a large black robe, with a wide hood.\n");
    set_ac(1);
    set_af(TO);
    set_at(A_ROBE);
    add_prop(OBJ_I_VALUE,0);
    add_prop(OBJ_I_WEIGHT, 1200);
    add_prop(OBJ_I_VOLUME,  650);
    add_prop(OBJ_I_NO_DROP, 1);
    seteuid(getuid(TO));
}

int
query_nazgul()
{
    object  pl = ENV(TO);

    if (pl->query_guild_name_occ() != GUILD_NAME)
        return 0;
    return pl->query_nazgul();
}

int
query_morgul_penalty()
{
    object  pl = ENV(TO);

    if (pl->query_guild_name_occ() != GUILD_NAME)
        return 0;
    return pl->query_morgul_penalty();
}
    
string
query_auto_load()
{
    return MASTER + ":";
}

void
check_spell_object(object player)
{
    if (!present("Morgul_Spell_Object", player))
        clone_object(GUILD_DIR + "spells/morgul_spells")->move(player, 1);
}

mixed
remove(object ob)
{
    if (ob != TO)
        return -1;

    if (TP->query_hooded())
        shadow->remove_shadow();

    return 0;
}

mixed
wear(object ob)
{
    object  tp = TP;

    if (ob != TO)
        return -1;

    if (tp->query_guild_name_occ() == GUILD_NAME)
    {
        write("You wear the "+query_short()+" around your body.\n"+
              "You feel the dark power of Black Sorcery flowing through you.\n");
        say(QCTNAME(tp)+" wears "+LANG_ASHORT(TO)+".\n");
        check_spell_object(tp);
        present("Morgul_Spell_Object", tp)->update_morgul_spells();
        return 1;
    }
    tp->heal_hp(-(tp->query_max_hp()/20));
    set_alarm(0.0, 0.0, remove_object);
    return "When you try to wear the "+query_short()+", it bursts out in flames and disappears.\n";
}

varargs void 
initiate(object pl, string str)
{
    string  dummy;
    object  room;
    int     nl,
            mp;

    inited = 1;

    if (pl->query_guild_name_occ() != GUILD_NAME)
    {
        room = ENV(TO);
        while (!room->query_prop(ROOM_I_IS))
            room = ENV(room);
        pl->catch_msg("The "+query_short()+" bursts out in flames and disappears!\n");
        set_alarm(0.0, 0.0, remove_object);
        return;
    }

    MORGUL_MASTER->short();
    if (MORGUL_MASTER->keep_player(pl)) 
    {
        pl->add_cmdsoul(MORGUL_SOUL_FILE);
        pl->update_hooks();

        // Keep this only to update old penalty levels
        if (strlen(str))
        {
            sscanf(str, "%s#nl#%d#mp#%d#%s", dummy, nl, mp, dummy);
            pl->set_morgul_penalty(-mp);
        }

        // Is the mage a nazgul?
        nl = MORGUL_NAZGUL_MASTER->query_is_nazgul(pl->query_name());

        // No wizard may be a nazgul!
        if (nl && pl->query_wiz_level())
        {
            MORGUL_NAZGUL_MASTER->demote_nazgul(pl->query_name(), "wizard");
            nl = 0;
            pl->catch_msg("As wizard, you cannot remain one of the Nazgul!\n"+
                          "The Dark Lord removes you from the ranks of the Nazgul!");
        }
        pl->set_nazgul(nl);

        // Clone the nazgul crown
        if (nl > 1)
            clone_object(MAGES_DIR + "obj/morgul_crown")->move(pl, 1);

        // Give them the spell object
        set_alarm(1.0, 0.0, "check_spell_object", pl);
        return;
    }
    write("The Lord of Morgul removes you from the Society of Morgul Mages!\n");
    call_out("throw_out",0,pl);
    return;
}

void
throw_out(object pl)
{
    if (!pl) 
        return;
    MORGUL_MASTER->remove_mage(pl, 2);
}

void
init_arg(string str)
{
    if (!inited) 
        set_alarm(0.0, 0.0, "initiate", TP, str);
}

void
init()
{
    object  tp = TP;

    ::init();

    add_action("do_hood", "hood");
    add_action("do_hood", "wear");
    add_action("do_reveal", "reveal");
    add_action("do_reveal", "unhood");
    add_action("do_reveal", "remove");

    if (tp != ENV(TO))
        return;

    if (MORGUL_NAZGUL_MASTER->query_is_nazgul(tp->query_real_name()))
        set_alarm(0.0, 0.0, "check_for_death");
}

void
check_for_death()
{
    object  tp = TP;

    // The player is a Nazgul and had died!
    if (MASTER_OB(tp) == "/d/Genesis/login/ghost_player")
        MORGUL_NAZGUL_MASTER->demote_nazgul(tp->query_real_name(), "death");
}

string query_recover() { return 0; }

void
leave_env(object from, object to)
{
    if (from->query_hooded())
    {
        shadow->remove_shadow();
    }

    ::leave_env(from, to);
}

int
do_hood(string str)
{
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

    if (ENV(TO) != TP)
    {
        NFN("You do not have the robe!");
        return 0;
    }

    if (query_worn() != TP)
    {
        NFN("You do not wear your robe!");
        return 0;
    }

    if (TP->query_hooded())
    {
        NFN("You are already wearing your hood!");
        return 0;
    }

    write("You pull the hood of your robe over your head, concealing your features.\n");
    say(QCTNAME(TP)+" pulls the hood of "+HIS(TP)+" robe over "
      + HIS(TP) + " head, concealing " + HIS(TP) + " features.\n");

    shadow = clone_object(GUILD_DIR + "obj/hood_shadow");
    shadow->shadow_me(TP);
    return 1;
}

varargs int
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

    if (!TP->query_hooded())
    {
        NFN("You are not wearing your hood!");
        return 0;
    }

    if (!silent)
    {
        write("You remove the hood and reveal your face again.\n");
        say(QCTNAME(TP)+" removes "+HIS(TP)+" hood.\n");
    }

    shadow->remove_shadow();
    return 1;
}

