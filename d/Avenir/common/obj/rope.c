// -*-C++-*-
// file name:    /d/Avenir/inherit/rope.c
// creator(s):   GONDOR 
// last update:  Lilith, June 2004: changed lengths, they seemed extreme.
//               Added help info regarding making objects tie-able.
// purpose:      Rope, compatible with what is in Gondor   
// note:         Used with permission from Gondor

/* To use rope, one must define the functions below 
 * IN THE OBJECTS that can be tied with a tope.

int
tie_object(object ob, string str)
{
    set_no_show_composite(1);
    return 1;
}

int
untie_object(object ob) 
{
    unset_no_show_composite();
    return 1;
}

*/

inherit "/std/rope";

#include <cmdparse.h>
#include <language.h>
#include <macros.h>
#include <stdproperties.h>
#include <wa_types.h>
#include "/d/Gondor/defs.h"


int     length;         /* length (in cm) */

int filter_slash(object wep);

void set_length(int i)
{
    length = 100;
    if(i > 0)
        length = i;
}
   
string length_adj()
{
    if(length < 10)
        return "very short";
    if(length < 50)
        return "short";
    if(length < 100)
        return "medium";
    if(length < 250)
        return "long";
    if(length < 1000)
        return "quite long";
    if(length < 5000)
        return "extremely long";

    return "very long";
}

int query_length() { return length; }

void create_rope()
{
    set_name("rope");
    add_name(({"cord","line"}));

    set_adj(({"hemp", "braided"}));

    set_short("@@short_desc");

    set_long("@@long_desc@@");

    set_length(1600);
    add_adj(length_adj());

    add_prop(OBJ_I_WEIGHT,"@@rope_weight@@");
    add_prop(OBJ_I_VOLUME,"@@rope_volume@@");
    add_prop(OBJ_I_VALUE,"@@rope_value@@");
}

void init()
{
    ::init();
    add_action("do_cut","cut");
    add_action("do_pull","pull");
}

int filter_slash(object wep) { return (wep->query_dt() & W_SLASH); }

int do_cut(string str)
{
    string  vb       = query_verb();
    object *weapons  = filter(TP->query_weapon(-1), filter_slash),
            new_rope,
           *ob;
    int     i,
            ol,
            ov;

    NF(CAP(vb) + " what?\n");
    if(!str)
        return 0;


    if(!sizeof(ob = FIND_STR_IN_OBJECT(str,TP)))
        if(!sizeof(ob = FIND_STR_IN_OBJECT(str,ENV(TP))))
            return 0;

    if(sizeof(ob) > 1)
    {
        NF("Which one of the "+str+" do you want to cut?\n");
        return 0;
    }

    if (ob[0] != TO)
    {
        NF("You cannot cut the " + ob[0]->short() + "!\n");
        return 0;
    }

    NF("You need to wield a sharp weapon to cut the "+str+".\n");
    if(!sizeof(weapons))
        return 0;

    NF("Don't be ridiculous! It's short enough as it is now!\n");
    if(length < 35)
        return 0;

    ol = query_prop(OBJ_I_WEIGHT);
    ov = query_prop(OBJ_I_VOLUME);
    if(objectp(tied_to))
    {
        if (living(tied_to))
            move(environment(tied_to));
        write("You cut the "+str+" from the "+tied_to_text+".\n");
        SAY(" cuts the "+str+" from the "+tied_to_text+".");

	tied_to = 0;
        length -= length/5;
        remove_prop(OBJ_M_NO_GET);
        remove_prop(OBJ_M_NO_DROP);
    }
    else
    {
        write("You cut the "+str+" into two parts of about equal length with the "
            + weapons[0]->short() + ".\n");
        SAY(" cuts the "+str+" into two parts.");
        remove_adj(length_adj());
        length /= 2;
        add_adj(length_adj());
        seteuid(getuid());
        new_rope = clone_object(MASTER);
        new_rope->remove_adj(new_rope->length_adj());
        new_rope->set_length(length);
        new_rope->add_adj(new_rope->length_adj());
        new_rope->move(ENV(TO));
    }
    ENV(TO)->update_internal(0,query_prop(OBJ_I_WEIGHT)-ol,query_prop(OBJ_I_VOLUME)-ov);

    return 1;
}

string long_desc()
{
    string  desc;
    int     feet     = query_length() / 31;
  
    desc = "It a hemp rope composed of six smaller roped braided "+
           "together. It is ";

    if(feet == 0)
        desc += "less than one arms-length long.";
    else if(feet == 1)
        desc += "about one arms-length long.";
    else if(feet < 13)
        desc += "about "+LANG_WNUM(feet)+" arms-lengths long.";
    else if(feet < 50)
    {
        feet = (2*feet+5)/10 * 5;
        desc += "about "+LANG_WNUM(feet)+" arms-lengths long.";
    }
    else
    {
        feet = (feet+5)/10 * 10;
        desc += "about "+LANG_WNUM(feet)+" arms-lengths long.";
    }
    return BSN(desc);
}

int rope_weight()
{
    return length * 4;
}

int rope_volume()
{
    return length * 3;
}

int rope_value()
{
    return 25 + (length * length) / 4000;
}

int do_pull(string str)
{
    string  vb       = query_verb();

    NF(CAP(vb) + " what?\n");
    if(!str || !id(str) || !objectp(tied_to))
        return 0;

    write(BSN("You pull at the "+str+" tied to "+(living(tied_to) ? " " : "the ")+
        tied_to_text+". It seems to be securely fastened."));
    SAY(" pulls at the "+str+" tied to "+(living(tied_to) ? " " : "the ")+
        tied_to_text+". It seems to be securely fastened.");
    return 1;
}

string short_desc()
{
    if(length < 10)
        return "very short rope";
    if(length < 50)
        return "short rope";
    if(length < 100)
        return "medium rope";
    if(length < 250)
        return "long rope";
    if(length < 1000)
        return "very long rope";
    if(length < 5000)
        return "extremely long rope";
    return "very long rope";
}
