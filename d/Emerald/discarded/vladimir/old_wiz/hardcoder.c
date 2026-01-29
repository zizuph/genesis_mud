#pragma strict_types
#pragma no_clone
#pragma no_inherit
#pragma save_binary
 
#include "syntax.h"
 
private string *e;
 
private int vis;
 
static varargs string
break_nicely(string s, int ind = 2, int first = 1, int i = 0)
{
    string space = "                                                 ";
    string s2 = "", *stuff;
    int j, l;
    if (i)
        s = "\"" + s;
    if (!first)
        s = extract(space, 0, ind * 4 - 1) + s;
    else
        if (sscanf(s, "        %s") == 1)
            ind = 3;
    if (strlen(s) < 75)
        return s;
    stuff = explode(s, " ");
    l = 0;
    while (pointerp(stuff) && (strlen(stuff[0]) + l < 75))
    {
        if (!strlen(s2))
            s2 = stuff[0] + " ";
        else
            s2 += stuff[0] + " ";
        l = strlen(s2);
        stuff = exclude_array(stuff, 0, 0);
    }
    i = sizeof(explode(s2, "\"")) % 2 - 1;
    s2 = extract(s2, 0, -1);
    if (i)
        s2 += "\" +\n";
    else
        s2 += "\n";
    return s2 + break_nicely(implode(stuff, " "), ind, 0, i);
}
 
static string
fix_spacing(string s)
{
    string s1, s2;
    if (sscanf(s, "%sall2actbb(\" %s", s1, s2) == 2)
        s = sprintf("%sall2actbb(\"%s", s1, s2);
    if (sscanf(s, "%sall2act(\" %s", s1, s2) == 2)
        s = sprintf("%sall2act(\"%s", s1, s2);
    return s;
}
 
static string
convert_string(string s)
{
    string s1, s2;
    if (sscanf(s, "%s#emote#%s", s1, s2) == 2)
        s = sprintf("%s%s%s", s1, e[0], s2);
    if(sscanf(s, "%s#fail#%s", s1, s2) == 2)
        s = sprintf("%s\"%s\\n\"%s", s1, e[1], s2);
    if(sscanf(s, "%s#default#%s", s1, s2) == 2)
        s = sprintf("%s\"%s\"%s", s1, e[2], s2);
    if(sscanf(s, "%s#trail#%s", s1, s2) == 2)
        s = sprintf("%s%s%s", s1, e[3], s2);
    if(sscanf(s, "%s#parse#%s", s1, s2) == 2)
        s = sprintf("%s\"%s\"%s", s1, e[4], s2);
    if(sscanf(s, "%s#actor#%s", s1, s2) == 2)
        s = sprintf("%s\"%s\"%s", s1, e[5], s2);
    if(sscanf(s, "%s#bb#%s", s1, s2) == 2)
        s = sprintf("%s%s%s", s1, (vis & 1 ? "" : "bb"), s2);
    if(sscanf(s, "%s#btb#%s", s1, s2) == 2)
        s = sprintf("%s%s%s", s1, (vis & 2 ? "" : "bb"), s2);
    if(sscanf(s, "%s#all2act#%s", s1, s2) == 2)
        s = sprintf("%s\"%s\"%s", s1, e[6], s2);
    if(sscanf(s, "%s#target#%s", s1, s2) == 2)
        s = sprintf("%s\"%s\", oblist%s", s1, e[7], s2);
    if(sscanf(s, "%s#write#%s", s1, s2) == 2)
        s = sprintf("%s\"%s\\n\"%s", s1, e[8], s2);
    if(sscanf(s, "%s#all#%s", s1, s2) == 2)
        s = sprintf("%s\"%s\"%s", s1, e[9], s2);
    if(sscanf(s, "%s#name#%s", s1, s2) == 2)
        s = sprintf("%s%s", s1, s2);
    if(sscanf(s, "%s #targ#%s", s1, s2) == 2)
        s = sprintf("%s\", oblist, \"%s", s1, s2);
    while(sscanf(s, "%s #adv#%s", s1, s2) == 2)
        s = sprintf("%s\" + how[1] + \"%s", s1, s2);
    while(sscanf(s, "%s#he#%s", s1, s2) == 2)
        s = sprintf("%s\" + this_player()->query_pronoun() + \"%s", s1, s2);
    while(sscanf(s, "%s#him#%s", s1, s2) == 2)
        s = sprintf("%s\" + this_player()->query_objective() + \"%s", s1, s2);
    while(sscanf(s, "%s#his#%s", s1, s2) == 2)
        s = sprintf("%s\" + this_player()->query_possessive() + \"%s", s1, s2);
    while(sscanf(s, "%s#He#%s", s1, s2) == 2)
        s = sprintf("%s\" + capitalize(this_player()->query_pronoun()) + \"%s",
            s1, s2);
    while(sscanf(s, "%s#Him#%s", s1, s2) == 2)
        s = sprintf("%s\" + capitalize(this_player()->query_objective()) + \""
            + "%s", s1, s2);
    while(sscanf(s, "%s#His#%s", s1, s2) == 2)
        s = sprintf("%s\" + capitalize(this_player()->query_possessive()) " +
            "+ \"%s", s1, s2);
    s = fix_spacing(s);
    return break_nicely(s);
}
  
public void
write_emote(int options, string *arg, int see)
{
    int i;
    string emote = "";
    int *ltr = OPTIONS[options];
    vis = see;
    e = arg;
    i = sizeof(ltr);
    while(i--)
        emote = convert_string(LINES[ltr[i]]) + "\n" + emote;
    previous_object()->catch_emote(emote, arg[0]);
}
