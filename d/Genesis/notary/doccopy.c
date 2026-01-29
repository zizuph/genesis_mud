/*
 * 2003-07-07 by Dargoth
 * document copy, given to people 
 * 
 */

#include "notary.h"
#include <stdproperties.h>
#include <language.h>
#include <options.h>
#include <time.h>

inherit NFORM;

#define DEBUG_MODE

/* prototypes */
public string get_form_status(int brief=1);
void set_form_values(mapping values);
string query_postfix();
string query_prefix();

void create_object()
{

    setuid();
    seteuid(getuid());
    set_name("document");
    add_name("parchment");
    set_adj("notarial");
    set_long("This is an empty document.\n");

    add_prop(OBJ_I_VOLUME, 10);
    add_prop(OBJ_I_WEIGHT, 50);
    add_prop(OBJ_I_VALUE,50);

    add_prop(OBJ_M_NO_SELL, "The shop does not deal in this "+
        "type of merchandise.\n");
    add_prop(OBJ_M_NO_BUY, 1);

    add_item("seal","The large red wax seal bears the emblem "+
        "of the "+NOTARY_TITLE+" - an open eye over two hands "+
        "grasping each other in a handshake.\n");
               
}

string query_prefix()
{
    return "This elongated piece of parchment bears writing in flowing "+
        "dark-red script, each letter perfectly traced. ";
}

string query_postfix()
{
    return "It is affixed with the official seal of the "+NOTARY_TITLE+
        " confirming both the text and the signatures of the signers.\n";
}

/*
 * Function name   : set_form_values
 * Description     : Sets the form contents, usually managed by NMANAGER
 *                   object.
 * Arguments       : mapping - the doc values
 * Returns         : void 
 */
void set_form_values(mapping values)
{
    string ftype;
    string facc;

    ftype=QDOCTYPE(values[BITFIELD]);
    facc=QDOCACCESS(values[BITFIELD]);

    gdocInfo=values;

    add_adj(facc);
        
    if ((gdocInfo[BITFIELD] & DOC_TYPES )== DOC_GENERIC)
    {
        add_adj(ftype);
        set_short(facc+" "+ftype+" document");
    }
    else
    {
        add_name(ftype);
        set_short(facc+" "+ftype);
    }

    set_long(query_prefix()+"@@get_form_status@@"+query_postfix());
}


/**
 *  Function name : get_form_status
 *  Description   : provides the long description of the 
 *                  contents of the documents, and also 
 *  Arguments     : int =1 , if called from set_long, 
 *                      =0 if called via "read form"
 *  Returns       : The description
 */
public string get_form_status(int brief=1)
{
    string retval="";
    int bitfield=gdocInfo[BITFIELD];
    string doctype;
    string docacc;
    int swidth;

    doctype=QDOCTYPE(bitfield);
    docacc=QDOCACCESS(bitfield);

    if (brief)
    {
        retval+="The document is "+((bitfield & DOC_TYPES)==DOC_GENERIC?
                "of general type":LANG_ART(doctype)+" "+doctype)+
                ", titled \""+gdocInfo[DOCTITLE]+"\", signed by "+
                NMANAGER->get_signers(gdocInfo)+
                " and has been marked as having "+QDOCACCESS(bitfield)+
                " access.\n";
    }
    else
    {
        swidth=TP->query_option(OPT_SCREEN_WIDTH)-1;

        if (swidth < 41)
            swidth=79;
        
        retval+="\n"+sprintf("%"+swidth+"|s",gdocInfo[DOCTITLE])+"\n";
        retval+=sprintf("%"+swidth+"'-'s","")+"\n\n";
        retval+=gdocInfo[CONTENTS]+"\n\n";
        retval+="Signed on "+TIME2FORMAT(gdocInfo[CREATETIME],"mmm d, yyyy")+
        " by:\n"+break_string(NMANAGER->get_full_signers(gdocInfo),900,5)+"\n";
    }
    return retval;
}

#ifdef DEBUG_MODE
/* 
 * Allows to load form from a file, if debugging is on.
 */
void load_form(string fname)
{
    set_form_values(restore_map(NTEMP+fname));
}
#endif
