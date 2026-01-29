/*
 * 2003-07-03 by Dargoth
 * base notarial form. Contains things pertinent for all forms.
 * 
 */
#pragma no_clone

#include "notary.h"
#include <macros.h>

inherit NBASE;

/* prototypes */
public int destroy_form(string arg);
public int read_form(string what);
public string get_form_status(int brief=1);
static nomask int this_item(string arg);

/* 
 * All forms are readable and destructible
 */
public void init()
{
    ::init();

    if (interactive(TP))
    {
        add_action(read_form,"read");
        add_action(destroy_form,"tear");
    }
}

void create_object()
{
    set_name("form");
    set_adj("notarial");
    set_short("notarial form");
    add_prop(OBJ_I_IS_NFORM,1);
    setuid();
    seteuid(getuid());
}

/* 
 * Destroys the form.
 */
int destroy_form(string arg)
{
    if (this_item(arg))
    {
        write("You tear up and discard the "+query_short()+
            (gdocInfo[DOCTITLE]!=EMPTYFIELD?" titled \""+gdocInfo[DOCTITLE]+"\"":"")+
            ".\n");
        tell_room(ENV(TP),QCTNAME(TP)+" tears up and discards a "+
            query_short()+".\n",NOTLOOKERS + ({ TP }),TP);

        remove_object();
        return 1;
    }
}

/*
 * Reads the full form, instead of just examining it.
 * Exa does not return contents, read does not give the fluff
 * around the contents.
 */
int read_form(string what)
{
    string x;
    mixed formlist;
    int fidx;

    NF("Read which form?\n");
    if (this_item(what))
    {
        x=get_form_status(0);
        if (strlen(x))
            TP->more(x);
        return 1;
    }
    return 0;
}

/**
 *    Get the form status: filled in fields and text.
 *  brief=1 , if called from set_long, =0 if called via "read form"
 */
public string get_form_status(int brief=1)
{
    string retval="";
    string doctype;
    int bitfield=gdocInfo[BITFIELD];

    doctype=QDOCTYPE(bitfield);

    if (!brief)
        retval+=NOTARY_TITLE+"\n";
    retval+=SEPARATOR;
    retval+="* Title:   "+gdocInfo[DOCTITLE]+"\n";
    retval+="* Signers: "+NMANAGER->get_signers(gdocInfo)+"\n";
    retval+="* Type:    "+doctype+"\t"+(strlen(doctype)<8?"\t":"");
    retval+="* Access: "+QDOCACCESS(bitfield)+"\n";
    retval+=SEPARATOR;
    retval+="* Text:    ";
    if (brief)
        retval+=(strlen(gdocInfo[CONTENTS])? "The document has been filled out and "+
        "is readable.": "The form is empty")+"\n";
    else
        retval+=(strlen(gdocInfo[CONTENTS])?gdocInfo[CONTENTS]:"")+"\n";

    return retval;
}

/* 
 * Checks whether player is actually trying to manipulate this 
 * object or any other (second, etc.)
 */
static nomask int this_item(string arg)
{
    mixed formlist;
    int fidx;
    
    if (!arg || !strlen(arg))
        return 0;

     if (parse_command(arg,INV(TP),"%i",formlist))
    {
        fidx=formlist[0];
        if ((ABS(fidx)<sizeof(formlist)) && (fidx == 1 || fidx<0))
            if (formlist[ABS(fidx)]==TO)
                return 1;
    }
    return 0;
}
