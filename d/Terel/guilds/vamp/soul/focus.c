/* 
 * focus.c
 *
 * This provides the focus ability.
 *
 */

#include <composite.h>
#include <formulas.h>
#include <language.h>
#include <ss_types.h>
#include <macros.h>
#include <login.h>

#include "../guild.h"

public int filter_skill(string name,mixed * item)
{
    return (item[0]==name);
    
}


public void print_focus(string type)
{
    if (!sizeof(TP->query_drain_focus(type)))
    {
        write("You have no "+type+" focus.\n");
        return;
    }
    mixed * skills = map(TP->query_drain_focus(type), 
        &operator([])(SS_SKILL_DESC, ));
    string * names=map(skills, &operator([])( , 0));
    
    write("You focus on learning the " + type + 
    (sizeof(names)>1 ? " skills" : " skill") + " of " + 
    COMPOSITE_WORDS(names) + " from your prey.\n");

}

public string * get_names_from_ids(int * ids)
{
    return map(ids,&operator ([]) (,0) @ &operator ([]) (SS_SKILL_DESC,));
}

public string add_quotes(string val)
{
    return "'"+val+"'";
}

public void
write_focus_details(object player,string key)
{
    player->catch_msg("Which "+key+" skills would you like to focus "+
    "on?\n");
    
    string * def=get_names_from_ids(player->query_drain_focus(key));
    if (!def || !sizeof(def))
    {
        def=({ "nothing" });
    }
    player->catch_msg("You may choose two from: " + 
        COMPOSITE_WORDS(map(sort_array(get_names_from_ids(
        ALLOWED_SKILLS[key])),add_quotes)) +
        ".\nYou currently absorb "+ COMPOSITE_WORDS(def) +
        " from your prey.\n] ");
}

public mixed test(string key)
{
    return  COMPOSITE_WORDS(map(sort_array(get_names_from_ids(
            ALLOWED_SKILLS[key])),add_quotes));
}


public void next_focus(string str,object player,
                          string * keys, mapping changed)
{
    if (strlen(str))
    {
        if (str=="~q" || str=="q" || str=="quit")
        {
            player->catch_msg("Aborted.\n");
            return;
        }

        string first;
        string second;
        if (!parse_command(str,({ }), "%s 'and' %s", first, second) &&
            !parse_command(str,({ }), "%s",first))
        {
            player->catch_msg("'"+capitalize(str)+
                "' is not a valid choice.\n");
            write_focus_details(player,keys[0]);
            input_to(&next_focus(,TP,keys,changed));
            return;
        }            
        if (first==second)
        {
            player->catch_msg("You cannot focus on '"+first+
            "' twice.\n");
            write_focus_details(player,keys[0]);
            input_to(&next_focus(,TP,keys,changed));
            return;
        }
        int * new_skills=({ });
    
        mapping first_skill=filter(SS_SKILL_DESC,&filter_skill(first));

        if (m_sizeof(first_skill)!=1 || 
            member_array(m_indexes(first_skill)[0],
            ALLOWED_SKILLS[keys[0]])<0)
        {
            player->catch_msg("'"+capitalize(first)+"' is not a valid "+
            "skill for your "+keys[0]+" focus.\n");
            write_focus_details(player,keys[0]);
            input_to(&next_focus(,TP,keys,changed));
            return;
        }
        
        new_skills+=({ m_indexes(first_skill)[0] });
    
        if (second)
        {
            mapping sec_skill=filter(SS_SKILL_DESC,&filter_skill(second));

            if (m_sizeof(sec_skill)!=1 || 
                member_array(m_indexes(sec_skill)[0],
                ALLOWED_SKILLS[keys[0]])<0)
            {
                player->catch_msg("'"+capitalize(second)+"' is not a " 
                +"valid skill for your "+keys[0]+" focus.\n");
                write_focus_details(player,keys[0]);
                input_to(&next_focus(,TP,keys,changed));
                return;
            }
            new_skills+=({ m_indexes(sec_skill)[0] });
            player->catch_msg("You will focus on learning the " + keys[0] + 
            " skills of "+ first + " and " + second + " from your prey.\n");
        }
        else
        {
            player->catch_msg("You will focus on learning the " + keys[0] + 
            " skill of "+ first + " from your prey.\n");
        }
        changed+=([ keys[0] : new_skills ]);
    }
    else
    {
        player->catch_msg("You leave your "+keys[0]+" focus unchanged.\n");
    }


    if (sizeof(keys)<=1)
    {
        if (m_sizeof(changed))
        {
            foreach(string key: m_indexes(changed))
            {
                player->set_drain_focus(key,changed[key]);
            }
            player->save_focuses();
            player->catch_msg("You have updated your focus.\n");
        }
        return;
    }
    write_focus_details(player,keys[1]);
    input_to(&next_focus(,TP,keys[1..],changed));
}

public int focus(string arg)
{
    string * keys=m_indexes(ALLOWED_SKILLS);
    if (arg=="set")
    {    
    
        write_focus_details(TP,keys[0]);    
        input_to(&next_focus(,TP,keys,([ ])));
        return 1;
    }
    foreach (string key: keys)
    {
        print_focus(key);
    }
    write("You may use <"+query_verb()+" set> to change your focus.\n");
    return 1;
    
}
 