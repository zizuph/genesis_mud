/* 
 *
 * Emotes - copied from hobgoblins shell.
 * Louie 2004
 */

#include <macros.h>
#include <composite.h>
#include <filter_funs.h>
#include <ss_types.h>
#include <files.h>
#include <options.h>
#include <cmdparse.h>
#include "/lib/commands.c"
#include "../local.h"

/* proto */
void finish_prayer();
int is_templar(object ob);


/*
 * Function name: emote_cmdlist
 * Description:   Get the emotes available on this soul and
 *                their corresponding function names.
 * Returns:       mapping - a mapping that maps command names
 *                          to function names.
 */
mapping
emote_cmdlist()
{
    return ([
      /* Command name : Function name */

      "templarlist" : "templarlist",
      "templist"    :   "templarlist",
      "tklist"    :    "templarlist",
      "help"        :   "help",
      "tbeckon"     :   "tbeckon",
      "tkbeckon"    :    "tbeckon",
      "tcommend"    :   "tcommend",
      "tkcommend"   :    "tcommend",
      "tcurse"      :   "tcurse",
      "tkcurse"      :    "tcurse",
      "tdismiss"    :   "tdismiss",
       "tkdismiss"    :    "tdismiss",
      "tfare"       :   "tfare",
      "tkfare"    :    "tfare",
      "thail"       :   "thail",
      "tkhail"    :    "thail",
      "timitate"    :   "timitate",
      "tkimitate"    :    "timitate",
      "tjoke"       :   "tjoke",
      "tkjoke"       :    "tjoke",
      "tlook"       :   "tlook",
      "tklook"      :    "tlook",
      "tsmile"      :   "tsmile",
      "tksmile"      :    "tsmile",
      "thalt"       :   "thalt",
      "tkhalt"      :    "thalt",
      "toath"       :   "toath",
      "tkoath"      :    "toath",
      "tpraise"     :   "tpraise",
       "tkpraise"    :    "tpraise",
      "tpray"       :   "tpray",
      "tkpray"     :    "tpray",
        "tempsay"    :    "tempsay",
      "tksay"      :    "tempsay",

    ]);
}



int
is_templar(object ob)
{
    return ob->query_templar_member();
}

/**
 * List the Templars in the game, maybe
 */

int
templarlist(string str)
{


    object *players;
    string txt = "", tmp;
    int i, wwidth = TP->query_option(1);
    int all = 0;

    if (!TP->query_templar_knight() &&
        !TP->query_templar_officer() &&
        !TP->query_templar_lord())
    {
        NF("That is restricted to full Templars.\n");
        return 1;
    }
    
    if(wwidth < 11)
    wwidth = 78;

/*
    if(str && (str == "v" || str == "verbose"))
    all = 1;
 */

    players = filter(users(), "is_templar", this_object());

    write("The following Templars are protecting Her interests:\n\n");
    for(i = 0; i < sizeof(players); i++)
    {
        if(players[i]->query_invis() == 0
            || !players[i]->query_wiz_level())
        {
            txt += break_string(players[i]->query_name() + " the " +
                players[i]->query_guild_title_lay() +"\n",wwidth-10,5)[5..];
        }
    
    }
    
    write(txt);
    return 1;
      
}

/*** old code***
/*
        if(all)
        txt += break_string(players[i]->query_name() + " " +
          players[i]->query_title() + "\n",wwidth-10,5)[5..];
        else
        {
        tmp = players[i]->query_guild_title_race();
        if(players[i]->query_wiz_level())
            tmp = "";
        txt += break_string(players[i]->query_name() + " " +
          (tmp && stringp(tmp) && strlen(tmp) ? tmp +
            ", " : "") +
          (players[i]->query_wiz_level() ? players[i]->query_title() : "the " +
            players[i]->query_guild_title_lay()) + "\n",
          wwidth-10,5)[5..];
 **********/
 

int
help(string str)
{

    string subject, filename;

    if(!str)
    return 0;

    if (str == "templar" || str == "templars"
        || str == "guild")
    {
        subject = "help";
    } 
    else if(
           (sscanf(str, "guild %s", subject) != 1)
        && (sscanf(str, "templars %s", subject) != 1)
        && (sscanf(str, "templar %s", subject) != 1))
    {       
        return 0;
    }

    filename = LIB + subject;
    if(file_size(filename) > 0)
    {
        setuid();
        seteuid(getuid());
        cat(filename);
        return 1;
    }

    NF("No help on that subject found.\n");
    return 0;
  
}

/****
** EMOTES BELOW (in alphabetical order, in theory)
*****/

int
tbeckon(string str)
{
    object *oblist;
    string *how = parse_adverb_with_space(str, "zealously", 0);
    
    if (!strlen(how[0]))
    {
        notify_fail("Beckon [how] whom?\n");
        return 0;
    }
    
    oblist = parse_this(how[0], "[at] [the] %l");
    if (!sizeof(oblist))
    {
        NF("Beckon [how] whom?\n");
        return 0;
    }
    
    if (sizeof(oblist) > 1) 
    {
        write("You can only beckon one person at a time.\n");
        return 0;
    }

    actor("You"+how[1]+" beckon", oblist, 
            " to follow you down the dark path of ecstatic "+
            "pleasures offered by the Dark Temptress.");
    targetbb(how[1]+" beckons you to follow "+HIM(TP)+
        " down the dark path of ecstatic pleasures "+
        "offered by the Dark Temptress.", oblist);
    all2actbb(how[1]+" beckons",oblist,
        " to follow "+HIM(TP)+" down the dark path of "+
        "ecstatic pleasures offered by the Dark Temptress.");
    
    return 1;
    
}

int
tcommend(string str)
{
    object *oblist;
    string *how = parse_adverb_with_space(str, "approvingly", 0);
    
    if (!strlen(how[0]))
    {
        write("You"+how[1]+" commend everyone for "+
            "their services to the Dark Queen.\n");
        allbb(how[1]+" commends everyone for their "+
            "services to the Dark Queen.");
        return 1;
    }
    
    oblist = parse_this(how[0], "[the] %l");
    if (!sizeof(oblist))
    {
        NF("Commend [how] whom?\n");
        return 0;
    }
    
    if (sizeof(oblist) > 1) {
        actor("You"+how[1]+" commend", oblist, 
                " for their services to "+
                "the Dark Queen.");
        targetbb(how[1]+" commends you for your services "+
            "to the Dark Queen.", oblist);
        all2actbb(how[1]+" commends",oblist,
            " for their services to the Dark Queen.");

    }
    else
    {
        actor("You"+how[1]+" commend", oblist, 
                " for "+ HIS(oblist[0])+" services to "+
                "the Dark Queen.");
        targetbb(how[1]+" commends you for your services "+
            "to the Dark Queen.", oblist);
        all2actbb(how[1]+" commends",oblist,
            " for "+HIS(oblist[0])+" services to the Dark Queen.");
    }
    
    return 1;
    
}


int
tcurse(string str)
{
    object *oblist;
    string *how = parse_adverb_with_space(str, "angrily", 0);
    
    if (!strlen(how[0]))
    {
        notify_fail("Curse [how] whom?\n");
        return 0;
    }
    
    oblist = parse_this(how[0], "[at] [the] %l");
    if (!sizeof(oblist))
    {
        NF("Curse [how] whom?\n");
        return 0;
    }
    
    if (sizeof(oblist) > 1) 
    {
        write("You can only curse one person at a time.\n");
        return 0;
    }

    actor("You"+how[1]+" curse", oblist, 
            " and "+HIS(oblist[0])+" offspring for "+
            "six generations to come to suffering, poverty, "+
            "and illness in the name of Takhisis, Queen of Darkness!");
    targetbb(how[1]+" curses you and your offspring for six "+
        "generations to come to suffering, poverty, and illness in "+
        "the name of Takhisis, Queen of Darkness!", oblist);
    all2actbb(how[1]+" curses",oblist,
        " and "+HIS(oblist[0])+" offspring for six "+
        "generations to come to suffering, poverty, and illness "+
        "in the name of Takhisis, Queen of Darkness!");
    
    return 1;
    
}

int
tdismiss(string str)
{
    object *oblist;
    string *how = parse_adverb_with_space(str, "condescendingly", 0);
    
    if (!strlen(how[0]))
    {
        write("You"+how[1]+" dismiss everyone "+
            "with a gesture of your hand.\n");
        allbb(how[1]+" dismisses everyone "+
            "with a gesture of "+HIS(TP)+" hand.");
        return 1;
    }
    
    oblist = parse_this(how[0], "[to] [the] %l");
    if (!sizeof(oblist))
    {
        NF("Dismiss [how] whom?\n");
        return 0;
    }
    
    actor("You"+how[1]+" dismiss", oblist, 
            " with a gesture of your hand.");
    targetbb(how[1]+" dismisses you with a gesture "+
        "of "+HIS(TP)+" hand.", oblist);
    all2actbb(how[1]+" dismisses",oblist,
        " with a gesture of "+HIS(TP)+" hand.");
        
    return 1;
    
}


int
tfare(string str)
{
    object *oblist;
    string *how = parse_adverb_with_space(str, ".", 0);
    
    if (!strlen(how[0]))
    {
        write("You"+how[1]+" bid everyone farewell "+
            "in the name of Takhisis.\n");
        allbb(how[1]+" bids everyone farewell "+
            "in the name of Takhisis.");
        return 1;
    }
    
    oblist = parse_this(how[0], "[to] [the] %l");
    if (!sizeof(oblist))
    {
        NF("Farewell [how] to whom?\n");
        return 0;
    }
    
    actor("You"+how[1]+" bid", oblist, 
            " farewell in the name of Takhisis.");
    targetbb(how[1]+" bids you farewell in the name "+
        "of Takhisis.", oblist);
    all2actbb(how[1]+" bids",oblist,
        " farewell in the name of Takhisis.");
        
    return 1;
            
}

int
thail(string str)
{
    object *oblist;
    string *how = parse_adverb_with_space(str, ".", 0);
    
    if (!strlen(how[0]))
    {
        write("You hail everyone"+how[1]+" in the name "+
            "of Takhisis, Queen of Darkness.\n");
        allbb(" hails everyone"+how[1]+" in the name "+
            "of Takhisis, Queen of Darkness.");
        return 1;
    }
    
    oblist = parse_this(how[0], "[to] [the] %l");
    if (!sizeof(oblist))
    {
        NF("Hail [how] whom?\n");
        return 0;
    }
    
    actor("You hail", oblist, 
            how[1]+" in the name of Takhisis, Queen of Darkness.");
    targetbb(" hails you"+how[1]+
        " in the name of Takhisis, Queen of Darkness.", oblist);
    all2actbb(" hails", oblist, how[1]+
        " in the name of Takhisis, Queen of Darkness.");
        
    return 1;
            
/*
    if (sizeof(oblist) > 1)
    {
        actor("You hail", oblist, 
            how[1]+" in the name of Takhisis, Queen of Darkness.");
        targetbb(" hails you"+how[1]+
            " in the name of Takhisis, Queen of Darkness.", oblist);
        all2actbb(" hails", oblist, how[1]+
            " in the name of Takhisis, Queen of Darkness.");
    }   
    else
    {
        actor("You hail", oblist, 
            how[1]+" in the name of Takhisis, Queen of Darkness.");
        targetbb(" hails you"+how[1]+
            " in the name of Takhisis, Queen of Darkness.", oblist);
        all2actbb(" hails", oblist, how[1]+
            " in the name of Takhisis, Queen of Darkness.");
    }
*/
    
}


int
thalt(string str)
{
    object *oblist;
    
    if (!strlen(str))
    {
        write("You order everyone to cease all hostile "+
            "activities in the name of the Dark Queen!\n");
        allbb(" orders everyone to cease all hostile "+
            "activities in the name of the Dark Queen!");
        return 1;
    }
    
    oblist = parse_this(str, "[at] [the] %l");
    if (!sizeof(oblist))
    {
        NF("Halt whom?\n");
        return 0;
    }
    
    actor("You order", oblist," to cease all hostile "+
        "activities in the name of the Dark Queen!");
    targetbb(" orders you to cease all hostile "+
        "activities in the name of the Dark Queen!", oblist);
    all2actbb(" orders", oblist, 
        " to cease all hostile activities in the name of " +
        "the Dark Queen!");
        
    return 1;
            
}

int
timitate(string str)
{
    string *how = parse_adverb_with_space(str, "mockingly", 0);
    
    write("You pretend to curl your imaginary "+
        "moustache"+how[1]+" in imitation of a "+
        "Solamnian Knight.\n");
    allbb(" pretends to curl "+HIS(TP)+" imaginary "+
        "moustache"+how[1]+" in imitation of a "+
        "Solamnian Knight.");
        
    return 1;
            
}


int
tjoke(string str)
{
    
    write("You display with a series of suggestive movements "+
        "how the Solamnian Knights ride their horses when "+
        "noone is looking.\n");
    allbb(" displays with a series of suggestive movements "+
        "how the Solamnian Knights ride their horses when "+
        "noone is looking.");
        
    return 1;
            
}

int
tlook(string str)
{
    object *oblist;
    string *how = parse_adverb_with_space(str, "quickly", 0);
    
    if (!strlen(how[0]))
    {
        write("You look around and"+how[1]+" disregard "+
            "anything as a potential threat.\n");
        allbb(" looks around and"+how[1]+" disregards "+
            "anything as a potential threat.");
        return 1;
    }
    
    oblist = parse_this(how[0], "[at] [the] %l");
    if (!sizeof(oblist))
    {
        NF("Look [how] at whom?\n");
        return 0;
    }
    
    if (sizeof(oblist) > 1) 
    {
        actor("You look", oblist," up and down,"+how[1]+
            " disregarding them as a potential threat.");
        targetbb(" looks you up and down,"+how[1]+" disregarding "+
            "you as a potential threat.", oblist);
        all2actbb(" looks", oblist, 
            " up and down,"+how[1]+" disregarding them as a "+
            "potential threat.");
    }
    else
    {
        actor("You look", oblist," up and down,"+how[1]+
            " disregarding "+HIM(oblist[0])+" as a potential threat.");
        targetbb(" looks you up and down,"+how[1]+" disregarding "+
            "you as a potential threat.", oblist);
        all2actbb(" looks", oblist, 
            " up and down,"+how[1]+" disregarding "+HIM(oblist[0])+
            " as a potential threat.");
    }
        
    return 1;
            
}


int
toath(string str)
{
    write("You raise your voice like "+
        "the roar of a dragon as you renew your oath "+
        "of service to the Dark Queen!\n");
    allbb(" raises "+HIS(TP)+" voice like the "+
        "roar of a dragon as "+HE(TP)+" renews "+
        HIS(TP)+" oath of service to the Dark Queen!");
    return 1;
            
}


int
tpraise(string str)
{
    object *oblist;
    string *how = parse_adverb_with_space(str, "loudly", 0);

    write("You"+how[1]+" praise the gifts the Dark Temptress "+
        "bestows on Her followers.\n");
    allbb(how[1]+" praises the gifts the Dark Temptress "+
        "bestows on Her followers.");
        
    return 1;
            
}

int
tpray(string str)
{
    object *oblist;
    string *how = parse_adverb_with_space(str, "quietly", 0);
    
    write("You lower your head and"+how[1]+
        " mumble a prayer to the Dark Temptress.\n");
    allbb(" lowers "+HIS(TP)+" head and"
        +how[1]+" mumbles a prayer to the Dark Temptress.");
        
    set_alarm(2.0, 0.0, &finish_prayer());
        
    return 1;
            
}

void
finish_prayer()
{
    write("You end your prayers, feeling comforted by "+
        "your dark passion.\n");
    allbb(" ends "+HIS(TP)+" prayers, "+HIS(TP)+
        " eyes sparkling with dark passion.");
        
}


int
tempsay(string str)
{
    if (TP->query_templar_officer() || TP->query_templar_lord()
        || TP->query_templar_knight()) {
    return "/d/Ansalon/guild/dragonarmy/soul/dragonarmy_soul"->dsay(str);
    }

    NF("Only Officers are trained in that tongue.\n");
    return 0;
}
int
tsmile(string str)
{
    object *oblist;
    string *how = parse_adverb_with_space(str, "amusedly", 0);
    
    if (!strlen(how[0]))
    {
        write("You smile"+how[1]+", not even attempting "+
            "to hide your arrogance.\n");
        allbb(" smiles"+how[1]+", not even attempting "+
            "to hide "+HIS(TP)+" arrogance.");
        return 1;
    }
    
    oblist = parse_this(how[0], "[at] [the] %l");
    if (!sizeof(oblist))
    {
        NF("Smile [how] at whom?\n");
        return 0;
    }
    
    actor("You smile"+how[1]+" at", oblist,", not even attempting "+
        "to hide your arrogance.");
    targetbb(" smiles"+how[1]+
        " at you, not even attempting to hide "+HIS(TP)+
        " arrogance.", oblist);
    all2actbb(" smiles"+how[1]+" at", oblist, 
        ", not even attempting to hide "+HIS(TP)+
        " arrogance.");
        
    return 1;
            
}
