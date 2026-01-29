/*
 * 2003-09-17 by Dargoth,
 *   v1.2 - added some more info to player in tear();
 * 2003-06-20 by Dargoth
 *
 * Notarial form 
 * players can fill it out and submit to notary for confirmation
 * fillable fields:
 *  - contents
 *  - title 
 *  - type (agreement/contract/order/other)
 *  - access type: public  - everybody can view
 *                 private - only signers can view
 *                 guild   - only the respective guilds of signers 
 *                 leaders - only the leaders of the respective guilds 
 *  -- the above two fields are contained in a single bitfield
 *  - signers
 *  - the signing process is done outside the form in the archive
 *    room, as the notary is there to actually witness the signing.
 *    so, the signatures and signing dates are outside the form
 */
#include "notary.h"
#include <stdproperties.h>
#include <language.h>
#include <composite.h>
#include <macros.h>

inherit NFORM;

/* prototypes */
private int notary_help(string str);
private int fill_form(string what);
private int set_signers(string who);
private int set_form_access(string access);
private int set_form_type(string type);
private int set_form_title(string what);
private int set_form_contents();

void create_object()
{
   ::create_object();

   set_long("It is an elongated piece of paper, bearing a letterhead "+
        "in elegant block letters: \""+NOTARY_TITLE+"\".\n"+
        "@@get_form_status@@\n"+
        "The fine print at the bottom of the paper reads: \"This "+
        "form is used to prepare documents for submission "+
        "to notarial archives. See usage with the command: 'help form'. "+
        "Note that this is an unsigned and notarially unaffirmed document. "+
        "All officially signed and confirmed documents bear the "+
        "appropriate seal of the Notarial service.\"\n");

    add_prop(OBJ_M_NO_SELL,"It has no market value.\n");
    add_prop(OBJ_M_NO_BUY,1);
    add_prop(OBJ_I_VALUE,1);
    add_prop(OBJ_I_WEIGHT, 100);
    add_prop(OBJ_I_VOLUME, 10);
    
    gdocInfo[BITFIELD] = (DOC_GENERIC | DOC_PRIVATE);

}

public void init()
{
    ::init();

    if (interactive(TP))
    {
        add_action(notary_help,"help");
        add_action(fill_form,"fill");
    }
}

/**
 * Help system, just prints out associated file in the help
 * directory defined
 */
private int notary_help(string str)
{
    string helpfile="general";
    string *args;

    if (!strlen(str))
        return 0;

    args=explode(str," ");

    NF("Help with what?\n");
    if (wildmatch("form*",str))
    {
        if (sizeof(args)>1)
            helpfile=args[1];
        
        /* these helpfiles shouldn't be large,
           so we can use cat instead of more */
        if (!cat(NHELP("form/"+helpfile)))
        {
            notify_fail("No such form help topic found.\n",1);
            return 0;
        }
        return 1;
    }
    return 0;
}

/***
 * Here we can fill out various form fields.
 * Tries to parse player's given command, expects it in format:
 * "fill form <field> <value>" or "fill form contents"
 */
private int fill_form(string what)
{
    string field;
    string content;
    string *arg;
    int szarg;

    NF("Fill what?\n");

    if (!strlen(what))
        return 0;
    
    arg=explode(what," ");

    szarg=sizeof(arg);
    if (szarg && arg[0]=="form")
    {
        if (szarg < 2 || (szarg < 3 && arg[1] !=CONTENTS))
        {
            NF("Please use: \"fill form <field> <value>\".\n");
            return 0;
        }
        switch(arg[1])
        {
            case SIGNERS:
                    return set_signers(implode(arg[2..]," "));
            case DOCTITLE:
                    return set_form_title(implode(arg[2..]," "));
            case "type":
                    return set_form_type(arg[2]);
            case "access":
                    return set_form_access(arg[2]);
            case CONTENTS:
                    return set_form_contents();
            default: 
                    NF("Fill which form field?\n");
        }
    }
    return 0;
}

/*
 * Attempt to set form type, must be in valid form types list
 * Returns: 1 if success
 */
private int set_form_type(string type)
{
    int ftype;
    
    ftype=NMANAGER->get_type(type);

    if (ftype)
    {
        gdocInfo[BITFIELD] &= (~DOC_TYPES); /* clear all previous types */
        gdocInfo[BITFIELD] |= ftype; /* set this type */

        write("You mark the document to be "+
            (ftype==DOC_GENERIC ? "of general type": 
                LANG_ART(type)+" "+type)+".\n");
        return 1;
    }
    NF("No such form type. Valid types are: "+
        NMANAGER->get_valid_types()+".\n");
    return 0;
}

/*
 * Attempt to set form access, must be in valid form types list
 * Returns: 1 if success
 */
int set_form_access(string access)
{
    int facc;
    
    facc=NMANAGER->get_access(access);

    if (facc)
    {
        gdocInfo[BITFIELD] &= (~DOC_ACCESS);
        gdocInfo[BITFIELD] |= facc;
        write("You mark the form to have "+access+" access.\n");
        return 1;
    }

    NF("No such form access type. Valid access type are: "+
        NMANAGER->get_valid_access()+".\n");
    return 0;
}

/* 
 * NAME
 *        get_form_values - gets the actual mapping containing all current 
 *                    values for form.
 *
 * SYNOPSIS
 *      mapping get_form_values()
 * 
 * DESCRIPTION
 *      This function returns a mapping containing all the elements
 *      of the form: signers, etc. 
 *
 * SEE ALSO
 *      base, notary.h
 *      
 */
public mapping get_form_values()
{
    return gdocInfo + ([ ]);
}

/*
 * Accepts a comma-separated list of signers
 * (case insensitive), checks for general player name
 * validity via SECURITY->exist_player() 
 */
private int set_signers(string who)
{
    string *names;
    int sz,i;

    NF("Empty or wrong signers' names. Use comma or space "+
        "separated names. Example of valid signers: "+
        "\"Mrpr,Mercade\".\n");

    if (!strlen(who))
        return 0;

    /* taken from mail_reader cleanup_string() to 
       allow space/comma separation of names */
    /* Change all spaces to commas. */
    who = implode(explode(lower_case(who), " "), ",");
    /* Remove all empty spaces from the string. */
    names = (explode(who, ",") - ({ "", 0 }));

    sz=sizeof(names);

    if (sz)
    {
        for (i=0; i<sz; i++ )
            if (!SECURITY->exist_player(names[i]))
                return 0;
        gdocInfo[SIGNERS]=mkmapping(names,0);
        write("You carefully enter: \""+COMPOSITE_WORDS(map(names,capitalize))+"\" in the "+
            "signers field.\n");
        return 1;
    }
    return 0;
}

/*
 * Sets the notarial form title, only checks for size 
 * not to exceed MAX_TITLE_LEN 
 */
private int set_form_title(string what)
{
    if (strlen(what) > MAX_TITLE_LEN)
    {
        NF("Title length too long. Maximum of "+MAX_TITLE_LEN+
            " characters.\n");
        return 0;
    }
    gdocInfo[DOCTITLE]=what;
    write("You fill in the title of your document to be: \""+what+"\".\n");
    return 1;
}

/*
 * Allow player to actually write the contents of the document,
 * via EDITOR_OBJECT
 * afterwards call done_editing();
 */
private int set_form_contents()
{
    object msged;

    setuid();
    seteuid(getuid());

    write("You begin to fill in the contents of your document.\n");
    tell_room(ENV(TP),QCTNAME(TP)+" starts writing "+
        "a document.\n",NOTLOOKERS + ({ TP }),TP);

    msged=clone_object(EDITOR_OBJECT);
    msged->set_activity("a notarial form.");
    msged->edit();

    return 1;
}

void done_editing(string text)
{
    if (stringp(text) && strlen(text))
    {
        write("You finish writing the contents of the document "+
            "and wave the paper in the air a bit to let the ink dry.\n");

        tell_room(ENV(TP),QCTNAME(TP)+" finishes writing "+
            "a document and waves it in the air a bit, letting the ink dry.\n",
            NOTLOOKERS + ({ TP }),TP);
        
        gdocInfo[CONTENTS]=text;
    }
    else
    {
        write("You decide against writing the document.\n");
        tell_room(ENV(TP),QCTNAME(TP)+" scratches all the text from "+
            "a document "+HE(TP)+" was writing.\n", NOTLOOKERS + ({ TP }),TP);
    }
}

/*
 * Saves the form contents to intermediary file for later
 * loading by other form(s).
 */
void save_tempfile(string fname)
{
    save_map(gdocInfo,NTEMP+fname);
}

void load_form(string fname)
{
    gdocInfo=restore_map(NTEMP+fname);
}
