/* 
 * Base scroll containing a magic spell
 *
 * The spell can be copied into a sohm spell book or cast immediately
 *
 * Coded by Britanica 20160403 
 * Modified by Arman  20160507
 */
 
inherit "/std/scroll";
#include <macros.h>
#include <cmdparse.h>
#include <tasks.h>
#include <ss_types.h>
#include <wa_types.h>
#define SCROLL_I_FURLED "_scroll_i_furled"

#define SCROLL_SPELL_SHADOW  "/d/Krynn/common/scrolls/scroll_spell_shadow"
#define SOHM_GUILD_NAME "School of High Magic"
#define WOHS_GUILD_NAME "Wizards of High Sorcery"
#define SOHM_MANAGER "/d/Krynn/guilds/sohm/lib/sohm_manager"

#define TO this_object()
#define TP this_player()

int unfurl(string str);
int furl(string str);
int study_cmd(string str);
// public int cast_spell(string text);

int spell_level = 0;
private string scroll_spell_path;

/*
 * Function name: create_scroll
 * Description  : constructor.
 * Arguments    : n/a
 * Returns      : n/a
 */
void
create_scroll()
{
    set_name("parchment");
    add_name("scroll");
    add_name("_anti_magic_scroll_");
    set_pname("parchments");
    add_pname("scrolls");
    set_adj("crinkled");
    add_adj("magic");
    set_short("furled crinkled parchment");
    add_adj("furled");
    set_pshort("crinkled parchments");
    set_long("This crinkled parchment is currently furled tightly. " +
        "You could unfurl it if you want.\n");

    add_prop(SCROLL_I_FURLED, 1);
}

/*
 * Function name: init
 * Description  : add actions to players
 * Arguments    : n/a
 * Returns      : n/a
 */
init()
{
    add_action(furl, "furl");
    add_action(unfurl, "unfurl");
    ::init();

    // Until we figure out how to get around the unmaskable functions
    // can_execute_ability and resolve_spell, this action is commented out
    // add_action(cast_spell, "cast");

    add_action(study_cmd, "scribe");
}

/*
 * Function name: furl
 * Description  : furl up the scroll
 * Arguments    : string str - target of action
 * Returns      : 1 or handled, 0 for ignored
 */
int 
furl(string str)
{
    object target = PARSE_COMMAND_ONE(str,
            all_inventory(environment(TP)) + all_inventory(TP), "[the] %i");

    if (!target && PARSE_COMMAND_SIZE > 0)
    {
        notify_fail("You can only " + query_verb() + " one thing at a time.\n");
        return 0;
    }
    
    if (target != TO)
    {
        notify_fail(capitalize(query_verb()) + " what?\n");
        return 0;
    }

    if (environment(TO) != TP)
    {
        write("You need to be holding it..\n");
        return 1;
    }
            
    if (TO->query_prop(SCROLL_I_FURLED))
    {
        write("The " + query_short() + " is already furled!\n");
        return 1;
    }
    write("You furl the " + query_short() + ".\n");
    say(QCTNAME(TP) + " furls the " + QSHORT(TO) + ".\n");
    TO->add_prop(SCROLL_I_FURLED, 1);
    TO->remove_adj("unfurled");
    TO->set_short("furled crinkled parchment");
    TO->add_adj("furled");
    TO->remove_item("symbols");
    TO->remove_item("black symbols");
    TO->remove_item("runes");
    TO->remove_item("black runes");
    TO->set_long("This tattered parchment is currently furled tightly. " +
        "You could unfurl it if you want.\n");
    return 1;
}

/*
 * Function name: unfurl
 * Description  : unfurl up the scroll
 * Arguments    : string str - target of action
 * Returns      : 1 or handled, 0 for ignored
 */
int 
unfurl(string str)
{
    object target = PARSE_COMMAND_ONE(str,
            all_inventory(environment(TP)) + all_inventory(TP), "[the] %i");

    if (!target && PARSE_COMMAND_SIZE > 0)
    {
        notify_fail("You can only " + query_verb() + " one thing at a time.\n");
        return 0;
    }
    
    if (target != TO)
    {
        notify_fail(capitalize(query_verb()) + " what?\n");
        return 0;
    }

    if (environment(TO) != TP)
    {
        write("You need to be holding it.\n");
        return 1;
    }
 
    if (!(TO->query_prop(SCROLL_I_FURLED)))
    {
        write("The " + query_short() + " is already unfurled!\n");
        return 1;
    }
    write("You unfurl the " + query_short() + ".\n");
    say(QCTNAME(TP) + " unfurls the " + QSHORT(TO) + ".\n");
    TO->remove_prop(SCROLL_I_FURLED);
    TO->remove_adj("furled");
    TO->set_short("unfurled crinkled parchment");
    TO->add_adj("unfurled");
    TO->set_long("This unfurled parchment is covered with mystical black " +
         "runes and symbols.\n");
    TO->add_item(({"black runes","runes","symbols","symbols of magic"}),
         "Mystical black runes and symbols of magic have been " +
                 "neatly penned upon this scroll, no doubt a spell " +
                 "of some sort. You'd have to read the scroll to have a " +
                 "chance of discerning what this spell might be.\n");
    return 1;
}

/*
 * Function name: read_access
 * Description  : check if scroll can be read 
 * Arguments    : ob - this scroll
 * Returns      : 1 for success, 0 for access denied
 */
public int
read_access(object ob)
{
    if (environment(ob) != this_player())
    {
      notify_fail("You must be holding the scroll to read it properly!\n");
      return 0;
    }
    if (ob->query_prop(SCROLL_I_FURLED))
    {
        notify_fail("You can only read unfurled scrolls!\n");
        return 0;
    }
    if ((environment(this_player()))->query_prop(ROOM_M_NO_MAGIC))
    {
        notify_fail("The text on the scroll shimmers and waves, but does " +
	   "not allow you to read it here.\n");
        return 0;
    }
    return (function_exists("create_object", ob) == SCROLL_OBJECT);
}

/*
 * Function name: perform_task_check
 * Description  : calculate the task check to determine if the player 
 *                is able to read or cast the scroll
 * Arguments    : object player - the player reading or casting
 * Returns      : task result - value out of 1000 of requested difficulty achieved.
 *                              may be larger than 1000.
 */
public int 
perform_task_check(object player)
{
    int result = 0;
    if ((TP->query_guild_style_occ() == "magic") ||
        (TP->query_guild_style_occ() == "cleric") ||
        (TP->query_guild_style_occ() == "ranger") ||
        (TP->query_guild_style_lay() == "magic") ||
        (TP->query_guild_style_lay() == "cleric") ||
        (TP->query_wiz_level()))
    {
        result = TP->resolve_task(TASK_ROUTINE,
          ({TS_INT, TS_WIS, SS_LANGUAGE}));
    }
    else 
    {
        result = TP->resolve_task(TASK_DIFFICULT, 
                   ({TS_INT, TS_WIS, SS_LANGUAGE}));
    }
    return result;
}

// SCRIBING FUNCTIONS

void
remove_scroll()
{
    write("As you finish scribing the spell, the black runes on the " + query_short() + 
          " begin glowing furiously and it combusts!\n");
    say("As " +QTNAME(this_player()) + " completes scribing, the black runes on the " +
        QSHORT(TO)+ " begin to glow furiously, and the parchment combusts!\n");

    this_object()->remove_object();
}


int
study_cmd(string str)
{
    object spell;
    string spell_name;

    object target = PARSE_COMMAND_ONE(str,
            all_inventory(environment(TP)) + all_inventory(TP), "[the] %i");

    if (!target && PARSE_COMMAND_SIZE > 0)
    {
        notify_fail("You can only " + query_verb() + " one spell at a time.\n");
        return 0;
    }

    if (target != TO)
    {
        notify_fail(capitalize(query_verb()) + " what?\n");
        return 0;
    }

    if (environment(TO) != TP)
    {
        write("You need to be holding it.\n");
        return 1;
    }
 
    if(this_player()->query_guild_name_occ() != SOHM_GUILD_NAME &&
       this_player()->query_guild_name_occ() != WOHS_GUILD_NAME) 
    {
        write("You don't have the training to scribe the spell " +
        "on the " + query_short() + ".\n");
        return 1;
    } 

    if(!this_player()->query_prop("_sohm_read_magic_active")) 
    {
        write("You are not mentally focused enough to scribe the magical " +
        "runes on the " + query_short() + ". Perhaps try again after preparing " +
        "yourself to read magic?\n");
        return 1;
    } 

    spell = find_object(scroll_spell_path);
    spell_name = spell->query_spell_name();

    if(spell_level > 2)
    {
       if(this_player()->query_lesser_spells_max() < 1 ||
         ((this_player()->query_greater_spells_max() < 1) && (spell_level > 3)) ||
         ((this_player()->query_advanced_spells_max() < 1) && (spell_level > 4)))
         {
            write("This spell is too advanced for you to learn at this " +
                        "time.\n");
            return 1;
          }
    }

    if(SOHM_MANAGER->query_scribed_spell(this_player(), spell_name))
    {
        write("This scroll seems to have the spell " +spell_name+
            " scribed on it. This spell you already know.\n");
        return 1;
    }
     
    write("You begin to carefully study the scroll. You scribe the " +
        spell_name + " spell in to your spellbook!\n");
    say(QCTNAME(this_player()) + " begins copying the scroll in to " +
        this_player()->query_possessive() + " spellbook.\n");
    
    SOHM_MANAGER->scribe_spell_to_spellbook(this_player(), spell_name);

    set_alarm(2.0,0.0,"remove_scroll");

    return 1;

}


// CASTING FUNCTIONS

/*
 * Function name: cast_spell
 * Description  : Perform the actual cast. This function prints the text
 *                to the player and displays a message to the people in
 *                the room.
 * Arguments    : string - spell and arguments
 * Returns      : 1 for handled, 0 ignored
 */

/* Commented out until we work out masking issues

public int
cast_spell(string text)
{
    string spell;
    string spell_args = "";
    this_player()->catch_tell("Casting spell " + text + "\n");
    this_player()->catch_tell("Spell path set " + scroll_spell_path + "\n");
    string* args = explode(text, " ");
    if (sizeof(args))
    {    
        object scroll_shadow = clone_object(SCROLL_SPELL_SHADOW);
        object spell = clone_object(scroll_spell_path);
        int shadow_result = scroll_shadow->shadow_me(spell);
        if (!shadow_result)
        {
            this_player()->catch_tell("Shadow failed");
        }
        
        this_player()->add_spellobj(spell);
        string spell_name = spell->query_spell_name();
        
        if (args[0] == spell_name)
        {
            if (sizeof(args) > 1)
            {
                spell_args = implode(args[1..], " ");
            }
            object* targets = spell->target_ability(this_player(), spell_args);
            TP->catch_tell(sprintf("targets %i.\n", sizeof(targets)));
            
            int setup_result = spell->execute_ability(this_player(), 
                                                       targets, spell_args);
                                                       
            
            TP->catch_tell(sprintf("execute ability result %i.\n",
                           setup_result));

            int taskcheck = perform_task_check(TP);
            write(sprintf("task check = %i\n", taskcheck));
            if (taskcheck < 75)
            {
                write("The runes and symbols of the scroll writhe before your " 
                  + "eyes, then erupt from the page and invade your mind!\n");
                say(QCTNAME(TP) + " attempts to cast the " + QSHORT(TO) 
                  + ", but fails!\n");
                TP->command("$shout My head!");
                TP->command("$scream");
                TP->set_mana(0);
                TP->command("$groan");
                TP->command("$wince");
                TP->heal_hp(-200);
                if (TP->query_hp() <= 0)
                    TP->do_die(TO);
                write("The " + query_short() + " bursts into flames and " 
                  + "disappears!\n");
                say("The " + QSHORT(TO) + " bursts into flames and disappears!\n");
                remove_object();
            }
            if (taskcheck >= 75)
            {
                write("You cast the " + query_short() + ".\n");
                say(QCTNAME(TP) + " casts the " + QSHORT(TO) + ".\n");


                spell->set_ability_startloc(this_player(),environment(this_player()));
                
                // Notify the player of the ability starting
                spell->ability_msg(this_player(), targets, "");

                int can_result = spell->can_execute_ability(this_player(), targets, "");
                if (can_result)
                {
                    write("FAIL: can_execute_ability returned 1.\n");
                }
                else
                {
                    write("can_execute_ability returned 0.\n");
                }
                

                //mixed result = resolve_ability(this_player()
                
                // Call the ability scheduler, defined in timed_ability
                int exe_result = spell->execute_ability(this_player(), targets, "");
                if (exe_result)
                {
                    write("execute_ability returned 1.\n");
                }
                else
                {
                    write("execute_ability returned 0.\n");
                }
                
                
                
                // int result = spell->start_ability(this_player(), targets);
                // if (result == 0)
                // {
                    // write("start ability successful.\n");
                // }
                // else
                // {
                    // write("failed to start ability.\n");
                // }

                // mixed * items = spell->check_required_items(this_player(),targets,"",1);
                // mixed * found = spell->find_components(this_player(), items);
                
                // if (pointerp(found))
                // {
                    // write("found object.\n");
                // }
                // else
                // {
                    // write("did not find object.\n");
                // }
                
                
                // if (!pointerp(items))
                // {
                    // write("Failed check_required_items.\n");
                // }
                // else
                // {
                    // write("check_required_items succeeded.\n");
                // }

                
                //Spell effects
                TP->command("$say " + spell->query_spell_name() 
                  + " with args " + spell_args);
                
                int casted = 0;//spell->do_ability(spell_args);
                if (casted)
                {
                    write("The " + query_short() + " bursts into flames and "
                     + "disappears!\n");
                    say("The "+QSHORT(TO)+" bursts into flames and disappears!\n");
                    setuid();
                    seteuid(getuid());
                    //remove_object();
                }
            }
            return 1;
        }
    }
}

*/

/*
 * Function:    safely_load_master_file
 * Description: This safely loads the master file if it hasn't already
 *              been loaded. Otherwise, it just returns the existing
 *              master file. If the file is not loadable, then it
 *              simply returns 0
 * Argument:    filename of the file to load
 */

public object
safely_load_master_file(string filename)
{
    if (!strlen(filename))
    {
        return 0;
    }
    object master_obj;
    if (!objectp(master_obj = find_object(filename)))
    {
        LOAD_ERR(filename);
        master_obj = find_object(filename);
    }
    
    return master_obj;
}

/*
 * Function name: read_it
 * Description  : Perform the actual read. This function prints the text
 *                to the player and displays a message to the people in
 *                the room.
 * Arguments    : string - the command the player executed, only 'read'
 * Returns      : n/a
 */
void
read_it(string str)
{
    int taskcheck;
    object no_magic_obj;
    
    seteuid(getuid(TO));
    if (str == "read")
    {
        taskcheck = perform_task_check(TP);
        if (taskcheck < 75)
        {
            write("The runes and symbols of the " +query_short()+ " writhe before " 
              + "your eyes as you attempt to decypher what they mean, causing " +
             "you to fail in your attempt and give you a mild headache.\n");
            say(QCTNAME(TP) + " attempts to read the " + QSHORT(TO) 
              + ", but fails!\n");
            return;
        }
        if (taskcheck >= 75)
        {
            write("You read the " + query_short() + ".\n");
            say(QCTNAME(TP) + " reads the " + QSHORT(TO) + ".\n");

            safely_load_master_file(scroll_spell_path);

            object spell = find_object(scroll_spell_path);
            TP->catch_tell("The " + query_short() + " contains the spell " 
              + spell->query_spell_name() + " - " 
              + spell->query_spell_desc() + ". Wizards of High Sorcery " +
              "and students of the School of High Magic may be able to " +
              "scribe this spell in to their spellbook.\n");
        }
    }
    if (str=="mread")
    {
      write("Due to the nature of scrolls, they must be read.\n");
    }
    return;
}

/*
 * Function name: set_spell
 * Description  : set the object path for the spell contained on the scroll
 *                this method also set MAGIC properties required for magic items
 * Arguments    : string - path to the spell file
 * Returns      : n/a
 */
public void 
set_spell(string spell_path)
{
    scroll_spell_path = spell_path;
    object spell = find_object(spell_path);
    if (objectp(spell))
    {
        int form_needed = spell->query_spell_form_needed();
        int sk = (sizeof(SS_SKILL_DESC[form_needed]) 
              ? SS_SKILL_DESC[form_needed][4] 
              : 0);
        
        int form_skill = spell->query_spell_form_skill();
        add_prop(MAGIC_AM_MAGIC, ({ form_skill, sk }));
        
        string description = spell->query_spell_desc();
        add_prop(MAGIC_AM_ID_INFO, ({"This scroll bears magical " 
          + "enchantment.\n", 5, "Casting it without skill in language " 
          + "and a measure of intelligence may cause mental pain.\n", 10,
            "It is used more easily by clerics and magic-users, " 
          + "as well as people who are rangers as their main " 
          + "profession.\n", 15, 
            description, 35}));
        add_prop(OBJ_S_WIZINFO, "This is a scroll of " + spell->query_spell_name()
          + "[" + sk + "] : " + description + " when cast. The scroll "
          + "must be unfurled to be read. Chances of reading the scroll " 
          + "are done with resolve_task. Routine resolve_task for " 
          + "clerics and magic-users, and occ rangers, difficult " 
          + "for everyone else. Cast will attempt the do_action\n");
    }
}

/*
 * Function name: set_spell_level
 * Description  : sets the spell level of the spell
 *
 *  SOHM_CANTRIP_SPELL      1
 *  SOHM_MINOR_SPELL        2
 *  SOHM_LESSER_SPELL       3
 *  SOHM_GREATER_SPELL      4 
 *  SOHM_ADVANCED_SPELL     5
 *
 */

public void
set_spell_level(int level)
{
    spell_level = level;
}
