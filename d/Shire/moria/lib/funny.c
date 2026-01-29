/*  -*- LPC -*-  */

#include <composite.h>
#include <language.h>
#include <macros.h>
#include "defs.h"

#define IM_STRING_FILE "/d/Immortal/rogon/open/string"

object *gWho;

string map_tell_one(function f, object to)
{
    return f(to);
}

string tell_one(object to, function *f)
{
    string *arr;
    arr = map(f, &map_tell_one(,to));
    return implode(arr, "");
}

void tell_many(object *to, function *f)
{
    map(to, &tell_one(,f));
}

string only(int num, function *f, object to)
{
    if (to == gWho[num])
        return tell_one(to, f);
    else
        return "";
}

string str(string what)
{
    return what;
}

string your(int num, object to)
{
    if (to == gWho[num])
        return "your";
    else 
        return LANG_POSS(gWho[num]->query_the_name(to));
}

string he(int num, object to)
{
    if (to == gWho[num])
        return "you";
    else
        return HE_SHE(gWho[num]);
}

string him(int num, object to)
{
    if (to == gWho[num])
        return "you";
    else
        return HIM_HER(gWho[num]);
}
 
string his(int num, object to)
{
    if (to == gWho[num])
        return "your";
    else
        return HIS_HER(gWho[num]);
}

string self(int num, object to)
{
    if (to == gWho[num])
        return "yourself";
    else
        return HIM_HER(gWho[num]) + "self";
}

string name(int num, object to)
{
    if (to == gWho[num])
        return "you";
    else
        return gWho[num]->query_the_name(to);
}

string verb(int num, string verb, object to)
{
    if (to == gWho[num])
        return verb;
    else
        return IM_STRING_FILE->verb_for_he_she_it(verb);
}

#ifndef COMPOSITE_ACTUALLY_WORKS

string Your(int num, object to) { return capitalize(your(num, to)); }
string He(int num, object to)   { return capitalize(he(num, to)); }
string Him(int num, object to)  { return capitalize(him(num, to)); }
string His(int num, object to)  { return capitalize(his(num, to)); }
string Self(int num, object to) { return capitalize(self(num, to)); }
string Name(int num, object to) { return capitalize(name(num, to)); }

#else

function Your = capitalize @ your;
function He   = capitalize @ he;
function Him  = capitalize @ him;
function His  = capitalize @ his;
function Self = capitalize @ self;
function Name = capitalize @ name;

#endif

#define SUBJ 0
#define OBJ  1
#define OBJ2 2


function *tell = ({
    &str("Hi, dude! Ain't this fun!\n"),
    &Name(OBJ),
    &str(" "),
    &verb(OBJ, "slash"),
    &str(" "),
    &him(SUBJ),
    &str("!\n"),
    &only(OBJ, ({ &str("For me only!!\n") })),
    &only(SUBJ, ({ 
        &str("Now the hard test:\n"),
        &He(OBJ),
        &str(" "),
        &verb(OBJ, "hurt"),
        &str(" "),
        &self(OBJ)
        }))
    });
    

stuff()
{
    string res;
   
    gWho = ({ this_player(), find_player("fatty") });
    res = tell_one(this_player(), tell);
    write("res = " + res + "\n");
}

#if 0
baddie()
{
    object elessar = find_player("elessar");

    TP->catch_msg("Hi, dude! Ain't this fun!\n"+
                             QCTNAME(elessar)+" slashes "+
                             "you!\n");
    if (TP == elessar)
        TP->catch_msg("For me only!!\n");

#endif    

