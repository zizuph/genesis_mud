/* Ashlar, 22 Aug 97
   The spellcasting object for the Priests of Takhisis
   Redone 11 Feb 98, adjusting to new spellcasting object
   Redone XX Xxx 01 by Milan, adjusting for another new spellcasting object

   Lucius, Jul 2016: Added OBJ_I_IS_MAGIC_ARMOUR prop.

*/
#pragma strict_types

inherit "/std/armour";
inherit "/d/Genesis/newmagic/spellcasting";

#include "/d/Ansalon/common/defs.h"
#include "/d/Ansalon/taman_busuk/neraka/local.h"
#include <wa_types.h>
#include <macros.h>
#include <ss_types.h>
#include <tasks.h>
#include <cmdparse.h>
#include <filter_funs.h>
#include <comb_mag.h>
#include <stdproperties.h>
#include <composite.h>
#include "../guild.h"


object gSoulgem;
string gString;
int gInt;

/*
#include "../spells.h"

static mixed *m_spell_list = SPELL_LIST;
*/

public void
spell_log(string spell, object caster, object tar, int result)
{
    if (caster->query_wiz_level())
    {
        caster->catch_tell("*** "+spell+", "+
            (tar ? C(tar->query_real_name()) : "-")+", "+result+" ***\n");
        return;
    }

    setuid();
    seteuid(getuid());
    
    log_file("pot/spells",
        sprintf("%s (%s) c=%s t=%s r=%d\n",
            spell,
            ctime(time()),
            C(caster->query_real_name()),
            (tar ? C(tar->query_real_name()) : "-"),
            result, 100000)
        );
}
    

void
m_remove_all_spells()
{
    mixed *m_spell_list = SPELLS->query_spell_list();
    int i,sz = sizeof(m_spell_list)-1;

    for (i=0; i<sz; i+=2)
    {
    	remove_spell(m_spell_list[i + 1]);
    }
}

void
m_add_all_spells()
{
    mixed *m_spell_list = SPELLS->query_spell_list();
    int i, sz = sizeof(m_spell_list) - 1;
    
    for (i = 0 ; i < sz ; i += 2)
    {
        add_spell( SPELL_DIR + m_spell_list[i + 1]);
    }
}

varargs void
m_add_spells(int sid = -1)
{
    mixed *m_spell_list = SPELLS->query_spell_list();
    int i, sz = sizeof(m_spell_list)-1;

    for (i=0; i<sz; i+=2)
    {
    	if (m_spell_list[i] & sid)
    	    add_spell( SPELL_DIR + m_spell_list[i + 1] );
    }
}

public void
update_spells()
{
    object e = E(TO);
    
    if (living(e))
    {
    	m_remove_all_spells();
    	m_add_spells(e->query_skill(PS_SPELLS));
    }
}

object
query_soul_gem()
{
    return gSoulgem;
}

void
set_soul_gem(object o)
{
    gSoulgem = o;
}

string
gem_status()
{
    if (gSoulgem)
        return ", which holds " + LANG_ADDART(gSoulgem->short()) +
            " you could remove from the medallion.";
    else
        return ".";
/*
        , which is empty. You can insert a soul gem there " +
            "using the command ginsert <gem>.";
*/
}

void
create_armour()
{
    set_name("medallion");
    add_name("takhisis_medallion");
    set_short("black medallion");
    set_pshort("black medallions");
    add_adj("black");
    set_long("The medallion is a plain disc of metal, blackened, and " +
        "inscribed with a life-like carving of a five-headed dragon. " +
        "In the center of the medallion is a small indentation" +
        "@@gem_status@@\n" +
        "As you gaze upon the medallion, you realise you can use the " +
        "commands <help priest> or <phelp> to get help on the guild!\n");
    set_ac(1);
    set_at(A_NECK);
    set_wf(TO);

    add_prop(OBJ_I_WEIGHT,50);
    add_prop(OBJ_I_VOLUME,20);
    add_prop(OBJ_I_VALUE,850);
    add_prop(OBJ_M_NO_DROP, 1);
    add_prop(OBJ_M_NO_SELL, 1);
    add_prop(OBJ_M_NO_STEAL, 1);
    add_prop(OBJ_M_NO_GIVE, 1);
    add_prop(OBJ_I_IS_MAGIC_ARMOUR, 1);
    add_prop(MAGIC_AM_MAGIC, ({ 80, "divination" }));
    add_prop(MAGIC_AM_ID_INFO, ({ "Magic flows from this medallion.\n", 0,
        "It is a symbol of a dark mythos.\n", 10,
        "The symbol Takhisis covers this medallion.\n", 20,
        "Dark priests uses this medallion in their dark rituals.\n", 30,
        "Through the use of this medallion one comes closer to Takhisis.\n",
        40 }));
}

int
insert_gem(string str)
{
    object *g, med;
    string arg;

    if (!str || !parse_command(str, TP, "%s 'into' %o", arg, med))
    {
        notify_fail("Insert what into what?\n");
        return 0;
    }

    if (med != TO)
    {
        notify_fail("Insert what into what?\n");
        return 0;
    }

    if (!arg || !sizeof(g = FIND_STR_IN_OBJECT(arg, TP)))
    {
        notify_fail("Insert what into what?\n");
        return 0;
    }

    if (sizeof(g) > 1)
    {
        notify_fail("Be more specific. You can insert only one thing " +
            "in the medallion.\n");
        return 0;
    }

    if (g[0]->id("_ansalon_soul_gem"))
    {
        if (gSoulgem)
        {
            write("There is already a gem in the medallion, you better " +
                "remove it first.\n");
    	    return 1;
        }
	
	if(g[0]->query_held())
	{
	  write("You must release the " +
                g[0]->short() +
                " before you can insert into your medallion.\n");
	  return 1;
	}
        write("You insert the " + g[0]->short() + " in the intendation. " +
            "You hear a soft click and the gem grows warm for an instant.\n");
        gSoulgem = g[0];
        gSoulgem->set_no_show();
        return 1;
    }
    else
    {
        notify_fail("The "+g[0]->short()+" does not fit in medallion.\n");
        return 0;
    }
}

int
remove_gem(string str)
{
    object gem, med;

    if (!str || (!parse_command(str, TP, "%o 'from' %o", gem, med) &&
        !parse_command(str, TP, "'all' 'from' %o", med)))
    {
        notify_fail("Remove what from what?\n");
        return 0;
    }
    
    if (gem && gem != gSoulgem)
    {
        notify_fail("Remove what from what?\n");
        return 0;
    }
    
    if (med != TO)
    {
        notify_fail("Remove what from what?\n");
        return 0;
    }

    if (!gSoulgem)
    {
    	notify_fail("There is no gem to remove.\n");
    	return 0;
    }

    write("You tug at the gem and it comes loose in your hand with a soft click.\n");
    gSoulgem->unset_no_show();
    gSoulgem->set_no_show_composite(0);
    gSoulgem->move(TP,1);
    gSoulgem = 0;
    return 1;
}

void
init()
{
    ::init();
    add_action(insert_gem, "insert");
    add_action(remove_gem, "remove");
}

/* We do not want this to recover as it is re-cloned at login */
public string
query_recover()
{
    return 0;
}

public int
wear(object ob)
{
    TP->adjust_standing(TP->query_standing() ? RND_RANGE(3, 5) :
        RND_RANGE(-3, 5));

    set_ac(TP->query_standing() / 100 + TP->query_stat(SS_OCCUP) / 10);
    TP->update_armour(TO);

    return 0;
}

public int
remove(object ob)
{
    if (query_verb() != "quit")
	query_worn()->adjust_standing(RND_RANGE(-35, 10));
    
    return 0;
}

void
leave_env(object env, object to)
{
    ::leave_env(env, to);
    remove_spell_object(env);

    m_remove_all_spells();
}

void
enter_env(object env, object from)
{
    if (living(env))
    {
#ifdef NO_INGREDIENTS
        // Make sure a testing version never gets to a mortal player.
        if (interactive(env) && !env->query_wiz_level())
        {
            env->catch_tell("The black medallion melts away in your grasp!\n");
            set_alarm(0.0,0.0,remove_object());
        }
        else
#endif
#ifdef 0
        m_add_spells(env->query_skill(PS_SPELLS));
#endif
    }
        
    ::enter_env(env, from);
    add_spell_object(env);

}

int
str_compare(string a, string b)
{
    if (b > a)
        return 1;
    else if (b < a)
        return -1;
    else
        return 0;
}   

public void
list_spells()
{
    mapping spells;
    string *verbs;
    int i;
    object ob;

    spells = query_spell_map();

    verbs = m_indices(spells);

    if (!sizeof(verbs))
    {
        write("Takhisis has yet to grant you any prayers.\n");
        return;
    }

    /* sort the verbs */
    verbs = sort_array(verbs, "str_compare", TO);

    write(
        "  ______________________________________________________________\n" +
        " / \\                                                            \\ \n" +
        "( / )                                                            ) \n"+
        " \\\\/____________________________________________________________/ \n" +
        " |                                                             |\n" +
        " |    The following prayers are granted to you by Takhisis     |\n" +
        " |                                                             |\n"
        );

    i = sizeof(verbs);

    while(i--)
    {
    	int j;
    	string s, *desc;
    	
    	if (ob = get_spell_object(verbs[i]))
    	{
    	    desc = ({ ob->query_spell_desc() || "" });

            if (strlen(desc[0]) > 40)
                desc = explode(break_string(desc[0],40),"\n");

            s = sprintf(" |  %-15s  %-40s  |\n",verbs[i], desc[0]);
            for (j=1; j<sizeof(desc); j++)
            {
                s += sprintf(" |  %-15s  %-40s  |\n","", desc[j]);
            }
        
            write(s +
 " |                                                             |\n");
        }
    }

    write(
        " | ____________________________________________________________|\n" +
        " //\\                                                            \\ \n" +
        "( \\ )                                                            ) \n"+
        " \\_/____________________________________________________________/ \n"
        );
}

/* Override as this doesn't break */
varargs int
got_hit(int hid, int ph, object att, int dt, int dam)
{
    hits++;
}

