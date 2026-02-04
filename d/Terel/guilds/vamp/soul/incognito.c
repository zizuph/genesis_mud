

#include "../guild.h"
#include <filter_funs.h>
#include <macros.h>
#include <std.h>
#include <composite.h>

inherit "/lib/commands";

public int
study(string arg)
{
    notify_fail("Study whom?\n");
    
    object *oblist;
    if (!sizeof(oblist = parse_this(arg, "[at] [the] %l")))
    {
        return 0;
    }
    if (sizeof(oblist)!=1)
    {
        write("You can only study one person at a time.\n");
        return 1;
    }
    object target=oblist[0];
    
    TP->catch_msg("You study "+QTNAME(target)+" intently.\n");
    
    targetbb(" studies you intently.",oblist);
    
    all2actbb(" studies",oblist," intently.\n");
    
    if (IS_WIZ(target) && !IS_WIZ(TP) && !IS_JR(TP))
    {
        return 1;
    }
    
    if (!target->query_humanoid())
    {
        return 1;
    }
    
    string * learned=({ });
    
    if (target->query_eyes_colour() && target->query_eyes_type())
    {
        int added=0;
        added+=TP->add_known_incog_attribute("eyes_color",
            target->query_eyes_colour());
        added+=TP->add_known_incog_attribute("eyes_type",
            target->query_eyes_type());
        if (target->query_eyes_number()>=1)
        {    
            added+=TP->add_known_incog_attribute("eyes_number",
            LANG_NUM2WORD(target->query_eyes_number()));   
        }
        string eye=(target->query_eyes_number()==1 ? " eye" : " eyes");    
        if (added)
        {
            learned+=({ POSS(target) + " " + target->query_eyes() + 
                eye });
        }
    }
    
    object colorob=present("colourob",target);
    if (colorob)
    {
        if (TP->add_known_incog_attribute("skin_color",
            colorob->return_colour_desc()))
        {
            learned+=({ POSS(target) + " " + colorob->return_colour_desc()+
               " skin" });
        }
    }
    
    if (target->query_hair_length() && target->query_hair_colour())
    {
        if (TP->add_known_incog_attribute("hair_length",
            target->query_hair_length()) ||
            TP->add_known_incog_attribute("hair_color",
            target->query_hair_colour()))
        {
            learned+=({ POSS(target) + " " + target->query_hair_length()+
                " " + target->query_hair_colour()+ " hair" });
        }
    }
        
    if (target->query_hair_style() 
            && target->query_gender()==TP->query_gender())
    {
        if (TP->add_known_incog_attribute("hair_style",
            target->query_hair_style()))
        {
            learned+=({ "the fact that " + POSS(target) + " hair is " + 
                target->query_hair_style() });  
        }
    }
    string * adjs= target->query_adj(1);
    if (adjs && sizeof(adjs)>2)
    {
        adjs=adjs[..1];
    }
    if (adjs && sizeof(adjs))
    {
        adjs-=TP->query_adjs(1);
    }
    
    if (adjs && sizeof(adjs)>0)
    {
        string * borrowed=({ });
        if (member_array(adjs[0],TP->query_adjs(1))==-1 &&
            TP->add_known_incog_attribute("adj1",adjs[0]))
        {
            borrowed+=({ adjs[0] });
        }
        if (sizeof(adjs)>1 &&
            member_array(adjs[1],TP->query_adjs(1))==-1 &&
            TP->add_known_incog_attribute("adj2",adjs[1]))
        {
            borrowed+=({ adjs[1] });
        }
        if (sizeof(borrowed))
        {
            learned+=({ POSS(target) + " " + COMPOSITE_WORDS(borrowed) +
                " appearance" });
        }
    }
    
    if (target->query_prop(CONT_I_VOLUME)<
        TP->query_prop(CONT_I_VOLUME)*250/100 &&
        target->query_prop(CONT_I_VOLUME)>
        TP->query_prop(CONT_I_VOLUME)*35/100 &&
        target->query_race_name()!=TP->query_race_name() &&
        target->query_humanoid())
    {
        if (TP->add_known_incog_attribute("race",
            target->query_race_name()))
        {
            learned+=({ POSS(target) + " " + target->query_race_name() +
                " traits" });
        }
    }
    
    if (sizeof(learned))
    {
        TP->save_disguises();
        write("You pay attention to "+COMPOSITE_WORDS(learned)+".\n");
    }
    else
    {
        write("You learn nothing more to mimic.\n");
    }
    return 1;

}

public string add_quotes(string val)
{
    return "'"+val+"'";
}

public void
write_disguise_details(object player,string key,mapping known)
{
    switch (key)
    {
        case "race":
            player->catch_msg("Which race would you like to imitate?\n");
            break;
        case "adj1":
            player->catch_msg("Which trait would you like to "+
            "display?\n");
            break;
        case "adj2":
            player->catch_msg("Which second trait would you like to "+
            "show?\n");
            break;
        case "hair_style":
            player->catch_msg("What style of hair do you desire?\n");
            break;
        case "skin_color":
            player->catch_msg("What color will your skin be?\n");
            break;    
        case "hair_color":
            player->catch_msg("What color of hair will you show?\n");
            break;
        case "hair_length":
            player->catch_msg("How long shall your hair be?\n");
            break;
        case "eyes_number":
            player->catch_msg("How many eyes do you wish to show?\n");
            break;
        case "eyes_color":
            player->catch_msg("Which color of eyes will you present?\n");
            break;
        case "eyes_type":
            player->catch_msg("Which style of eyes do you wish to mimic?\n");
            break;    
    }
    string def=player->query_incog_attribute(key);
    if (!def || !strlen(def))
    {
        def="normal";
    }
    player->catch_msg("You may choose from: " + 
        COMPOSITE_WORDS(map(sort_array(known[key])+
            ({"normal"}),add_quotes)) +
            ". Default is '"+ def +"'.\n] ");
}

public void next_disguise(string str,object player,
                          string * keys, mapping known,mapping changed)
{
    if (!strlen(str))
    {
        str=player->query_incog_attribute(keys[0]);
    }
    if (!strlen(str))
    {
        str="normal";
    }
    
    if (str=="~q" || str=="q" || str=="quit")
    {
        player->catch_msg("Aborted.\n");
        return;
    }
    
    if (member_array(str,known[keys[0]])<0 && str!="normal" && strlen(str))
    {
        player->catch_msg("'"+capitalize(str)+
            "' is not a valid choice.\n");
        write_disguise_details(player,keys[0],known);
        input_to(&next_disguise(,TP,keys,known,changed));
        return;
    }
    
    if (str=="normal")
    {
        player->catch_msg("You have chosen not to mask this "+
        "attribute.\n\n");
        changed+=([ keys[0] : "" ]);
    }
    else if (strlen(str))
    {
        player->catch_msg("You have chosen '" + str + "'.\n\n");
        changed+=([ keys[0] : str ]);
    }
    
    if (sizeof(keys)<=1)
    {
        foreach(string key: m_indexes(changed))
        {
            player->set_incog_attribute(key,changed[key]);
        }
        player->save_disguises();
        player->catch_msg("You have updated your incognito "+
        "description.\n");
        
        if (player->query_incognito())
        {   
            object * watchers=WATCHERS(player)- ({ player });
    
            watchers->catch_msg(QCTNAME(player) + " looks a " 
                + "little hazy for a moment.\n");
        }
        return;
    }
    write_disguise_details(player,keys[1],known);
    input_to(&next_disguise(,TP,keys[1..],known,changed));
}

public int 
disguise(string arg)
{
    mapping att=TP->query_all_known_incog_attributes();
    
    if (!m_sizeof(att))
    {
        write("You have not studied anybody to mimic their attributes.\n");
        return 1;
    }
    
    string * keys=sort_array(m_indexes(att));
    
    write_disguise_details(TP,keys[0],att);    
    input_to(&next_disguise(,TP,keys,att,([ ])));
    
    return 1;
    
}