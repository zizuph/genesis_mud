inherit "/lib/commands";

#pragma save_binary
#pragma no_clone
#pragma strict_types

#include "../guild.h"
#include <cmdparse.h>
#include <formulas.h>
#include <stdproperties.h>
#include <macros.h>
#include <stdproperties.h>
#include <files.h>
#include <filter_funs.h>
#include <composite.h>
#include <language.h>



#define SOULDESC(x)  (this_player()->add_prop(LIVE_S_SOULEXTRA, x))
#define POSSTP        (this_player()->query_possessive())
#define PROTP        (this_player()->query_pronoun())
#define OBJTP        (this_player()->query_objective())
#define CQV          capitalize(query_verb())
#define TP           this_player()

varargs
void tell_others(string str, object *exclude)
{
    object *players;
    
    players = all_inventory(environment(this_player()));
    if(sizeof(exclude))
    {
        players= players - exclude;
    }
    players = FILTER_PLAYERS(FILTER_CAN_SEE_IN_ROOM(players));

    if (sizeof(players))
    {
        players->catch_msg(str);
    }
}


public string pluralize_if_needed(string word, object* targets)
{
    if (sizeof(targets)>1)
    {
        return LANG_PWORD(word);
    }
    
    return word;
}


public string query_eyes_desc(object player)
{
    string desc=player->query_eyes();
    if (!desc)
    {
        return "eyes";
    }
    return desc+(player->query_eyes_number()==1 ? " eye" : " eyes");
}
     
  
public string query_target_pronouns(object *targets)
{
    int targetCount = sizeof(targets);
    if(targetCount>1)
    {
        return "they";
    }
    else
    {
        return targets[0]->query_pronoun();
    }
}
 
 
public string query_target_possessives(object *targets) 
{
    int targetCount = sizeof(targets);
    if(targetCount>1)
    {
        return "their";
    }
    else
    {
        return targets[0]->query_possessive();
    }
}


public string query_target_objectives(object *targets)
{
    int targetCount = sizeof(targets);
    if(targetCount>1)
    {
        return "them";
    }
    else
    {
        return targets[0]->query_objective();
    }
}




// EMOTES
int
bfregard(string str)
{
    object *oblist;
    string *how =parse_adverb_with_space(str, "thoughtfully", 0);
    
    if (!strlen(str) ||
        !sizeof(oblist = parse_this(how[0], "[the] %l")))
    {
        notify_fail(CQV + " [how] to whom?\n");
        return 0;
    }
         
    string eyes=query_eyes_desc(TP);

    targetbb(" regards you"+ how[1]+", "+POSSTP+" "+eyes+" glowing like"
    +" smoldering embers as "+PROTP+" considers how flammable you might"
    +" be.",oblist);
     
    actor("Your "+eyes+" glow like smoldering embers as you regard",
    oblist, how[1]+" while contemplating how flammable "
    +query_target_pronouns(oblist)+" might be.");  

    all2actbb(" regards",oblist, how[1]+", "+POSSTP
    +" "+eyes+" glowing like smoldering embers as he contemplates"
    +" how flammable "+query_target_pronouns(oblist)+" might be.");
 
    return 1;
}
 

int
bfhail(string str)
{
    object *oblist;
    
    if (!strlen(str) ||
        !sizeof(oblist = parse_this(str, "[the] %l")))
    {
        notify_fail(CQV + " whom?\n");
        return 0;
    }
 
    target(" raises " + POSSTP + " scarred fist towards you and"
    +" exclaims: Hail in the name of Kossuth, the Fire Lord!", oblist);

    actor("You raise your scarred fist towards",oblist," and "
    +"exclaim: Hail in the name of Kossuth, the Fire Lord!");
 
    all2act(" raises "+POSSTP+" scarred fist towards",oblist,
    " and exclaims: Hail in the name of Kossuth, the Fire Lord!");
 
    return 1;
}


int
bfack(string str)
{
    object *oblist;
 
    if (!strlen(str) ||
        !sizeof(oblist = parse_this(str, "[the] %l")))
    {
        notify_fail(CQV + " whom?\n");
        return 0;
    }
 
    targetbb(" tilts "+POSSTP+" head toward you in acknowledgement.",
        oblist);
    actor("Your tilt your head at",oblist," in acknowledgement.");
    all2actbb(" tilts "+POSSTP+" head at",oblist," in acknowledgement.");
 
    return 1;
}


int
bfbless(string str)
{
   object *oblist;
   string *how=parse_adverb_with_space(str, "exuberantly", 0);
  
   oblist = parse_this(how[0], "[the] %l", ACTION_OTHER);

   if (!stringp(how[0]))
   {
       write("Your scarred hand erupts into black flames as you raise it"
       +" above your head "+how[1]+" and proclaim: Blessed be the Lord"
       +" of Fire, may the worthy be purified and the weak"
       +" extinguished!\n");
   
       all(" raises "+POSSTP+" scarred hand "+how[1]+" above "+POSSTP
       +" head. As it suddenly erupts into black flames "+PROTP
       +" exclaims: "
       +"Blessed be the Lord of Fire, may the worthy be purified and"
       +" the weak extinguished!");
       return 1;
    }

    if (!sizeof(oblist))
    {
        if (strlen(parse_msg))
        {
            write(parse_msg);
            return 1;
        }
        notify_fail("bfbless [how] whom?\n");
        return 0;
    }
    target(" looks straight at you as he raises his scarred hand"+how[1]
    +" above "+POSSTP+" head and proclaims: Blessed be the Lord of Fire,"
    +" may the worthy be purified and the weak extinguished!",oblist);
     
    actor("You look straight at",oblist," as you raise your scarred hand"
    +how[1]+" above your head and proclaim: Blessed be the Lord of Fire,"
    +" may the worthy be purified and the weak extinguished!");

    all2act(" looks straight at",oblist," as "+PROTP+" raises "+POSSTP
    +" scarred hand"+how[1]+" above "+POSSTP+" head and proclaims: "
    + "Blessed be the Lord of Fire, may the"
    +" worthy be purified and the weak extinguished!");
   return 1;
}
 
 
int
bfassess(string str)
{
    object *oblist;
    string *how=parse_adverb_with_space(str,"slowly",0);
    string eyes=query_eyes_desc(TP);

    oblist = parse_this(how[0], "[the] %l", ACTION_OTHER);
 
    if (!strlen(str) ||
        !sizeof(oblist = parse_this(str, "[the] %l")))
    {
        notify_fail(CQV + " [how] whom?\n");
        return 0;
    }
      
    targetbb(" turns "+POSSTP+" "+eyes+how[1]+" toward you. They glow "
    +" as if burning from within as "+PROTP+" scrutinizes you up and "
    +" down, assessing "
    +" your chances to survive purification.");
     
    actor("Your "+eyes+" seem to almost burn from within as you"
    +" turn them"+how[1]+" toward",oblist,
    ". Scrutinizing "+query_target_objectives(oblist)
    +" up and down, you assess whether "
    +query_target_pronouns(oblist)+" could survive purification.");

    all2actbb(" turns "+POSSTP+" "+eyes+how[1]+" toward",oblist,
    " as "+PROTP+" scrutinizes them up and down,"
    +" assessing "+query_target_possessives(oblist)
    +" "+pluralize_if_needed("chance",oblist)
    +" to survive purification.");
  
    return 1;
}
 
 
int
bfrage(string str)
{
    object *oblist;
    string *how=parse_adverb_with_space(str,"colourfully",0);
    string eyes=query_eyes_desc(TP);
    if (!stringp(how[0]))
    {
        write("Your "+eyes+" glow like burning embers as you curse"+how[1]
        +".\n");
   
        all(" curses"+how[1]+", "+POSSTP+" "+eyes+" glowing like burning "
        +"embers.");
        return 1;
    }
    
    oblist = parse_this(how[0], "[the] %l", ACTION_OTHER);

    target(" curses"+how[1]+" at you, "+POSSTP+" "+eyes+" glowing like"
    +" burning embers.",oblist);

    actor("Your "+eyes+" glow like burning embers as you curse"+how[1]
    +" at",oblist);
    
    all2act(" curses"+how[1]+" at",oblist,", "+POSSTP+" "+eyes+" glowing"
    +" like burning embers.");
    return 1;
}
 
 
int
bfbored(string str)
{
    object *oblist;
    string *how=parse_adverb_with_space(str,"casually",0);

    if (!stringp(how[0]))
    {
        write("You try to entertain yourself by"+how[1]+" letting the "
        +"black flames covering your hand jump from fingertip to "
        +"fingertip.\n");
   
        all(" tries to entertain "+OBJTP+"self by"+how[1]+" letting the "
        +"black flames covering "+POSSTP+" hand jump from fingertip to "
        +"fingertip.\n");
        return 1;
    }

    oblist = parse_this(how[0], "[the] %l", ACTION_OTHER);
    
    actor("You turn away from",oblist," with a bored expression, and"
    +" proceed to entertain yourself by"+how[1]+" letting the"
    +" black flames covering your hand jump from fingertip to"
    +" fingertip.",oblist);

    targetbb("turns away from you with a bored expression, and"
    +" proceeds to entertain "+OBJTP+"self by"+how[1]+" letting the "
    +"black flames covering "+POSSTP+" hand jump from fingertip to "
    +"fingertip.",oblist);

    all2actbb("turns away from",oblist," with a bored expression, and"
    +" proceeds to entertain "+OBJTP+"self by"+how[1]+" letting the "
    +"black flames covering "+POSSTP+" hand jump from fingertip to "
    +"fingertip.");
    return 1;
 
}
 
 
int
bfcelebrate(string str)
{
    object *oblist;
    string *how=parse_adverb_with_space(str,"exuberantly",0);

    if (!stringp(how[0]))
    {
        write("You"+how[1]+" raises your hands and shoot a "
        +"series of small black fireballs into the air in a "
        +"celebratory manner, in homage to the Fire Lord.\n");
   
        all(" raises "+POSSTP+" hands"+how[1]+" and shoots a"
        +" series of small black fireballs into the air in a"
        +" celebratory manner, in homage to the Fire Lord.\n");
        return 1;
    }

    oblist = parse_this(how[0], "[the] %l", ACTION_OTHER);
    actor("You turn to",oblist,", celebrating"+how[1]
    +" by raising your hands and shooting a small series of"
    +" fireballs into the air in a celebratory manner, in"
    +" homage to the Fire Lord.",oblist);

    targetbb("turns to you, celebrating"+how[1]
    +" by raising "+POSSTP+" hands and shooting a small series of"
    +" fireballs into the air in a celebratory manner, in"
    +" homage to the Fire Lord.",oblist);

    all2actbb(" turns to",oblist,", celebrating"+how[1]
    +" by raising "+POSSTP+" hands and shooting a small series of"
    +" fireballs into the air in a celebratory manner, in"
    +" homage to the Fire Lord.",oblist);

    return 1;
    
}


int
bfshowoff(string str)
{
    object *oblist;
    string *how=parse_adverb_with_space(str,"slowly",0);

    if (!stringp(how[0]))
    {
        write("You"+how[1]+" raise your fist while whispering a"
        +" prayer to the Fire Lord. Your hand flares up, displaying"
        +" the Black Flame in all its power and glory.\n");
   
        all(" raises "+POSSTP+" fist"+how[1]+" while whispering a"
        +" prayer to the Fire Lord. "+POSSTP+" hand flares up, displaying"
        +" the Black Flame in all its power and glory.\n");
        return 1;
    }
    
    oblist = parse_this(how[0], "[the] %l", ACTION_OTHER);
    actor("You raise your fist toward",oblist,how[1]
    +" while whispering a prayer to the Fire Lord. Your"
    +" hand flares up, displaying "
    +"the Black Flame in all its power and glory.");

    targetbb(" raises "+POSSTP+" fist toward you"+how[1]
    +" while whispering a prayer to the Fire Lord. "
    + "As "+PROTP+" does so "+POSSTP+" hand flares up,"
    +" displaying the Black Flame in all its power and glory.",oblist);

    all2actbb(" raises "+POSSTP+" fist toward",oblist,how[1]
    +" while whispering a prayer to the Fire Lord. "
    + "As "+PROTP+" does so "+POSSTP+" hand flares up,"
    +" displaying the Black Flame in all its power and glory.");

    return 1;
}
 

int
bfsuggest (string str)
{
    object *oblist;
    string *how=parse_adverb_with_space(str,"accusingly",0);

    if (!stringp(how[0]))
    {
        write("You point a flame-engulfed finger around you"+how[1]
        +", indicating there are people nearby in dire need of"
        +"purification.\n");
   
        all(" points "+POSSTP+" flame-engulfed finger around "+OBJTP
        +"self, indicating there are people nearby in dire need of"
        +"purification.\n");
        return 1;
    }

    oblist = parse_this(how[0], "[the] %l", ACTION_OTHER);
    actor("You"+how[1]+" point your flame-engulfed finger at",oblist,
    ", suggesting there is a dire need of purification there.\n");

    targetbb(" points "+POSSTP+" flame-engulfed finger"+how[1]+" at you"
    +", suggesting there is a dire need of purification there.\n",oblist);

    all2actbb(" points "+POSSTP+" flame-engulfed finger"+how[1]
    +" at",oblist,
    ", suggesting there is a dire need of purification there.\n");

    return 1;
    
}