/*
 * /d/Gondor/common/guild2/morgul_shadow.c
 *
 * The guild shadow for the Morgul Mages of Gondor
 *
 * Created: Olorin, 5-jan-1994
 *          using /doc/examples/solamn/occ_shadow.c by Nick
 *          and   /d/Gondor/common/guild/ranger_shadow.c by Elessar
 *
 * Modification log:
 *
 * ====> Total Tax: 25% (upper levels)
 * ====> Total Tax: 15% (lower levels)
 *
 */

inherit "/std/guild/guild_occ_sh";

#include <language.h>
#include <stdproperties.h>
#include <ss_types.h>

#include "/d/Gondor/defs.h"
#include "/d/Gondor/common/lib/binbit.h"
#include "/d/Gondor/common/guild2/lib/morgul_defs.h"

#define GUILD_TAX             25
#define APPRENTICE_GUILD_TAX  15
#define TRAIN_HALL            (GUILD_DIR + "train_high")
#define APPRENTICE_TRAIN_HALL (GUILD_DIR + "train_low")
#define HANDICAP ({ \
	"is worthless to the Dark Lord", "is despised by the Nazgul", \
	"would be well advised to grovel before the Nazgul", \
	"has done little in service to the Dark Lord", \
	"is of small importance in the eyes of the Nazgul", \
	"has come to be accepted by the Nine", \
        "has rendered what is due to the Dark Lord", \
	"is spoken of with appreciation by the Black Captain", \
	"held in high esteem by those in Mordor", \
	"has been of great service to the mighty Nazgul", \
	"is held in the highest regard by the Dark Lord", \
	})

/*
 * Global variables
 */
int     nazgul;			// = 1: Nazgul, = 2: Lord/Lady of the Nazgul

varargs int
query_morgul_level(int flag = 0)
{
    int     m_stat = shadow_who->query_stat(SS_OCCUP),
            mlevel,
            nlevels = sizeof(MORGUL_AS_MALE_TITLES);

    if (m_stat > 100)
        m_stat = 100;

    mlevel = ((m_stat * (nlevels - 1)) / 100);
    if (flag <= 0)
    {
        mlevel /= 2;
        mlevel += shadow_who->query_skill(SS_MORGUL_PENALTY);
        if (mlevel >= nlevels)
            mlevel = nlevels - 1;
    }
    if (flag >= 0)
    {
         mlevel += (nazgul * nlevels);
    }
    else
    {
        switch (nazgul)
        {
            case 1:
            case 2:
                mlevel = (nazgul+1) * nlevels;
                break;
            case 0:
            default:
                break;
        }
    }

    if (mlevel < 0)
        mlevel = 0;
    return mlevel;
}

int
query_guild_tax_occ()
{
    if (query_morgul_level() <= APPRENTICE_LEVEL)
        return APPRENTICE_GUILD_TAX;
    return GUILD_TAX;
}

public mixed
query_guild_trainer_occ()
{
    if (query_morgul_level() <= APPRENTICE_LEVEL)
        return APPRENTICE_TRAIN_HALL;
    return TRAIN_HALL;
}

string query_guild_style_occ() { return GUILD_STYLE; }

string query_guild_name_occ() { return GUILD_NAME; }

int
query_guild_not_allow_join_occ(object player, string type, 
                                   string style, string name)
{
    if (::query_guild_not_allow_join_occ(player, type, style, name))
        return 1;

    NF("The Lord of Morgul does not tolerate clerics in his service!\n");
    if (style == "cleric")
        return 1;

    return 0;
}

void force_leave_guild(object player)
{
    seteuid(getuid());
    MORGUL_MASTER->load_me();
    MORGUL_MASTER->remove_player_from_guild(player);
}

int
query_guild_keep_player(object ob)
{
    string  race = ob->query_race_name();

    ob->add_subloc(MORGUL_S_SUBLOC, TO);
    ob->add_prop(LIVE_I_UNDEAD,"@@query_undead@@");
    ob->add_prop(LIVE_I_NO_CORPSE, 1);

    if (member_array(race,MORGUL_AS_ILLEGAL_RACE) > -1)
    {
	write("The Lord of Morgul does not accept " +
            LANG_ADDART(race) + " in his service!\n");
        call_out("force_leave_guild",2,ob);
    }

    if (ob->query_guild_style("cleric"))
    {
        write("The Lord of Morgul does not tolerate clerics in his service!\n");
        call_out("force_leave_guild",2,ob);
    }

    if(ob->query_alignment() > MORGUL_I_ALIGN_REMOVE)
    {
        write("The Dark Lord demands complete allegiance.\n" +
              "Your actions have been found wanting.\n" +
              "You left the Dark Path, now you will be punished!\n");
        call_out("force_leave_guild",2,ob);
    }
    else if(ob->query_alignment() > MORGUL_I_ALIGN_WARN)
        write("The Dark Lord demands complete allegiance.\n" +
              "Be warned and return to the Paths of Shadow and Darkness!\n");
    else if(ob->query_alignment() > MORGUL_I_ALIGN_JOIN)
        write("The Dark Lord demands complete allegiance.\n" +
              "Walk the Paths of Shadow and Darkness to please the Lord of Morgul!\n");

    return 1;
}

/*
 * set_nazgul(), query_nazgul()
 * nazgul = 1: Nazgul
 * nazgul = 2: Lord or Lady of the Nazgul
 */
void
set_nazgul(int i)
{
    nazgul = i;
}

int
query_nazgul()
{
    return nazgul;
}

/*
 * set_morgul_penalty(), query_morgul_penalty()
 * effective morgul_level = morgul_level - morgul_penalty
 */
int
set_morgul_penalty(int i)
{
    shadow_who->set_skill(SS_MORGUL_PENALTY, i);
    shadow_who->set_guild_pref(SS_OCCUP, query_guild_tax_occ());
    return 1;
}

int
query_morgul_penalty()
{
    return shadow_who->query_skill(SS_MORGUL_PENALTY);
}

string
query_morgul_title()
{
    if (nazgul)
    {
        if (shadow_who->query_gender() == 1)
            return MORGUL_AS_FEMALE_NAZGUL_TITLES[nazgul-1];
        else
            return MORGUL_AS_MALE_NAZGUL_TITLES[nazgul-1];
    }

    if (shadow_who->query_gender() == 1)
        return MORGUL_AS_FEMALE_TITLES[query_morgul_level()];
    return MORGUL_AS_MALE_TITLES[query_morgul_level()];
}

string
query_guild_title_occ()
{
    return query_morgul_title();
} 

string
query_def_post() { return MORGUL_POST; }

mixed
query_guild_skill_name(int type)
{
    if (type == SS_MORGUL_PENALTY)
    {
        if (objectp(TP) && TP->query_wiz_level())
            return "Morgul Penalty";
        else
            return "";
    }

    return 0;
}

/*
 * Function name: show_subloc
 * Description:   This function is called each time someone looks at us
 * Arguments:     subloc  - Our subloc
 *		  me      - I
 *		  for_obj - The looker
 * Returns:	  The string the looker shall see
 */
string
show_subloc(string subloc, object me, object for_obj)
{
    int     hs,
            ml, mml,
            hl;
    string  str;

    if (me->query_prop(TEMP_SUBLOC_SHOW_ONLY_THINGS))
	return "";

    if (subloc != MORGUL_S_SUBLOC)
        return shadow_who->show_subloc(subloc, me, for_obj);

    if (for_obj == me)
	str = "You are ";
    else
	str = CAP(me->query_pronoun()) + " is ";

    switch(query_nazgul())
    {
        case 1:
            str += "one of the Nazgul of the Society of Morgul Mages.\n";
            break;
        case 2:
            str += "the Lord of the Nazgul, King of Minas Morgul.\n";
            break;
        case 0:
        default:
            str += "a Member of the Society of Morgul Mages";
            if (for_obj->query_nazgul())
            {
                hs = sizeof(HANDICAP);
                ml = query_morgul_level();
                mml = query_morgul_level(1);
                hl = (ml * hs / mml);

                if (hl > (hs-1))
                    hl = hs - 1;
                if (hl < 0)
                    hl = 0;
                str += " who "+HANDICAP[hl];
            }
            str += ".\n";
            break;
    }

    return str;
}

int
query_undead()
{
    return shadow_who->query_stat(SS_OCCUP);
}

/*
 * Function name:	query_spells
 * Returns:		Active Morgul spells
 */
string *
query_spells()
{
    object  spell_obj;

    if (!objectp(spell_obj = present(MORGUL_S_SPELL_OBJECT, shadow_who)))
        return 0;

    return spell_obj->query_verbs();
}

/*
 * Function name:   second_life
 * Description:     Handles all that should happen to a dying player.
 * Argument:        Object that caused the kill.
 * Returns:         True if the living object should get a second life
 */
public int
second_life(object killer)
{
    if (query_nazgul())
    {
        shadow_who->catch_msg("The Dark Lord does not accept failures.\n"
                            + "You are not a Nazgul anymore!\n");
        FIX_EUID
        MORGUL_NAZGUL_MASTER->demote_nazgul_alarm(shadow_who->query_real_name(), "death");
    }

    return shadow_who->second_life(killer);
}

