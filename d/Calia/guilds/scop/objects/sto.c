

inherit "/std/object";
inherit "/d/Genesis/newmagic/spellcasting.c";

#include <stdproperties.h>
#include <macros.h>
#include "defs.h"

#define TEST_BOOK_LOG "spirit_circle/spirit_test_spellbook_log"

void
create_object()
{
    if (!IS_CLONE)
    {
        return;
    }

    set_name("book");
    add_name("spellbook");
    add_name("spirit_circle_test_book");
    set_short("midnight black spellbook");
    
    set_long("This is a midnight black spellbook used to "+
        "test the spells for the Spirit Circle of Psuchae.\n");
        
    add_prop(OBJ_M_NO_INS, 1);
    add_prop(OBJ_I_NO_DROP, 1);
    add_prop(OBJ_M_NO_STEAL, 1);
    add_prop(OBJ_M_NO_SELL, 1);
    add_prop(OBJ_I_NO_STEAL,1);
    
    seteuid(getuid());
    add_spell(clone_object(SPIRIT_SPELLS+"psychi"));
    add_spell(SPIRIT_SPELLS+"siopi");
    add_spell(SPIRIT_SPELLS+"therapeaou");
    add_spell(SPIRIT_SPELLS+"lamafragma");
    add_spell(SPIRIT_SPELLS+"gsechon");
    add_spell(SPIRIT_SPELLS+"anagnorizo");
    add_spell(SPIRIT_SPELLS+"eirini");
    add_spell(SPIRIT_SPELLS+"magikos");
    add_spell(SPIRIT_SPELLS+"exevrisko");
    add_spell(SPIRIT_SPELLS+"skiamorfi");
    add_spell(SPIRIT_SPELLS+"skiamati");
    add_spell(SPIRIT_SPELLS+"fos");
    add_spell(SPIRIT_SPELLS+"synithis");
    add_spell(SPIRIT_SPELLS+"giatreou");
    add_spell(SPIRIT_SPELLS+"metaballo");
    add_spell(SPIRIT_SPELLS+"energia");
    add_spell(SPIRIT_SPELLS+"anakalo");
    add_spell(SPIRIT_SPELLS+"vekpos");
    add_spell(SPIRIT_SPELLS+"apergo");
    add_spell(SPIRIT_SPELLS+"bdella");
    log_file(TEST_BOOK_LOG, ctime(time())+" Test spellbook cloned by "+ 
            TP->query_name() +".\n",-1);

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

/*
 * Function name: list_spells
 * Description:   This function is called to list the spells from
 *                the player soul when the command "spells" is used.
 */
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
        write("You have not been granted any gifts yet.\n");
        return;
    }

    /* sort the verbs */
    verbs = sort_array(verbs, "str_compare", TO);

    write("Spell Testing Object Spells:\n"+
          "============================\n");

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

            s = sprintf("%-15s  %-20s\n",verbs[i], desc[0]);
            for (j=1; j<sizeof(desc); j++)
            {
                s += sprintf("%-15s  %-20s\n","", desc[j]);
            }
            write(s);
        }
    }
}

public void
remove_object()
{
    /* Remove any cloned instances of spells that are registered with this
     * spellcasting object so that they aren't sitting around just taking up
     * memory.  You can either call remove_object() in the spells yourself,
     * or use the utility function cleanup_spells() to do it.
     */
    cleanup_spells();
    ::remove_object();
}

void
enter_env(object env, object from)
{
    ::enter_env(env, from);
    add_spell_object(env);
}

void
leave_env(object env, object to)
{
    ::leave_env(env, to);
    remove_spell_object(env);
}

