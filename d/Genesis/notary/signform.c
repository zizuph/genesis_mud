/*
 * 2003-06-29 by Dargoth
 *
 * Notarial form, intended to be filled by notary from the blankform.c and 
 * resubmitted to notary after being signed.
 *
 */
#include "notary.h"
#include <stdproperties.h>
#include <macros.h>
#include <composite.h>
    
inherit NFORM;

/* reqd number of signatures, set at time of reading form values,
   then decreased as people sign 
*/
int sRequired=1;

/* prototypes */
int sign_form(string what);

public string get_form_status(int brief=1);

string query_prefix();
string query_postfix();

void create_object()
{
    
    ::create_object();
    /* we set the proper description at the time 
       values are set via set_form_values() */
    set_long("An unfilled notarial form, it must have come to you by mistake. "+
        "Just tear it up and discard. There is nothing else you can "+
        "do with it.\n");

    add_prop(OBJ_M_NO_SELL,"It has no market value.\n");
    add_prop(OBJ_M_NO_BUY,1);
    add_prop(OBJ_I_VALUE,1);
    add_prop(OBJ_I_WEIGHT, 100);
    add_prop(OBJ_I_VOLUME, 10);

}

public void init()
{
    ::init();

    if (interactive(TP))
    {
        add_action(sign_form,"sign");
    }
}

string query_prefix()
{
    return "It is an elongated piece of paper, bearing a letterhead "+
        "in elegant block letters: \""+NOTARY_TITLE+"\".\n";
}

string query_postfix()
{
    return "The form has been verified and only needs to be signed and "+
        "resubmitted to the notary. You can use command 'sign form [fully] "+
        " [for <guild>] to do so, if you are listed as a signer.\n";
}

string get_form_status(int brief=1)
{
    string retval="";

    retval=::get_form_status(brief);

    retval+=SEPARATOR;
    retval+="* Signatures:\n";
    retval+=break_string(NMANAGER->get_full_signers(gdocInfo),900,14);

    return retval;
}

/* sets the form values from a previously prepared form
 * checking should be done by notary previously!
 */
void set_form_values(mapping values)
{
    string ftype=QDOCTYPE(values[BITFIELD]);

    gdocInfo=values;
    sRequired=(m_sizeof(values[SIGNERS]));
    
    add_adj(ftype);
    set_short(ftype+" form");

    set_long(query_prefix()+"@@get_form_status@@\n"+query_postfix());

}

mapping get_form_values()
{
    return gdocInfo+([ ]);
}

/* 
 * Function name: sign_form
 * Arguments    : string - player input
 * Description  : Called when player attempts to sign 
 *                the form. Makes all the neccessary
 *                checks and either signs or fails.
 * Returns      : 1 - if arg matched, 0 - if not.
 */
nomask static int sign_form(string arg)
{
    string signfor;
    string signshort;
    string *membership=({ });
    string ftype;
    object form;
    mixed oblist;
    status fullsig=0;
    int fidx;

    NF("Sign what?\n");

    if (!arg)
        return 0;

    if (parse_command(arg,INV(TP),"%i %s",oblist,signfor))
    {
        
        fidx=oblist[0];
        if ((ABS(fidx)<sizeof(oblist)) && (fidx == 1 || fidx<0))
        {
            /* we fallthrough to other form, if signing
                doesn't match our one... */
            form=oblist[ABS(fidx)];
            if (form!=TO)
                return 0;
        }
        else
            return 0;
        if (wildmatch("fully*",signfor))
        {
            /* we ignore the next char after 'fully', 
               it should be a space. */
            signfor=signfor[6..];
            fullsig=1;
        }
        if (!stringp(signfor) || signfor=="" || !strlen(signfor))
        {
            signfor=NOGUILD;
            signshort=signfor;
        }
        else
            if (sscanf(signfor,"for %s",signfor))
            {    
                signshort=QGSHORT(signfor);
            }
            else
                return 0;

        
        membership = NMANAGER->get_guilds_long(TP);
        membership -= ({ 0 });
    
        /* can we sign for this guild? */
        if (!signshort || (member_array(signfor, membership+ ({ NOGUILD }))<0))
        {
            write("Invalid guild name. You can sign for the following "+
                  "guilds: "+(sizeof(membership)?COMPOSITE_WORDS(membership)+
                 ". Please use exact spelling.":"none.")+"\n");
            return 1;
        }
    }
    else
        return 0;

    if (!sRequired)
    {   
       write("This form has already been fully signed.\n");
       return 1;
    }   
    /* are we in signers' list ? */
    if ( member_array(MYNAME,
                      m_indexes(gdocInfo[SIGNERS])) < 0 )
    {
        write("You are not marked as a signer of this form, therefore "+
        "you can't sign it.\n");
        return 1;
    }

    /* have we already signed this particular form ? */
    if (TP->query_prop(LIVE_O_MARK_SIGNED)==OB_NAME(TO))
    {
        write("You have already signed this form.\n");
        return 1;
    }
    
    if ((gdocInfo[BITFIELD] & (DOC_GUILD|DOC_GLEADER)) && signshort == NOGUILD)
    {
        write("You have chosen guild/guildleader access, but have chosen to sign for yourself. "+
           "That would mean nobody, but you can access the document. "+
           "If you want to let guild/guildleaders have access, please sign for the "+
           "appropriate guild, by \"sign [fully] for <guild name>\".\n\n");
        return 1;
    }

    TP->add_prop(LIVE_O_MARK_SIGNED,OB_NAME(TO));
    
    gdocInfo[SIGNERS]+=([ MYNAME:signshort ]);
    
    if (fullsig)
        gdocInfo[SIGNERTITLES]+=([ MYNAME:(TP->query_title()) ]);

    ftype=QDOCTYPE(gdocInfo);

    write("You sign the "+ftype+" form titled \""+
        gdocInfo[DOCTITLE]+"\" for "+
        (signshort == NOGUILD? NOGUILD :QGLONG(signshort))+".\n");

    tell_room(ENV(TP),QCTNAME(TP)+" puts a signature on "+
        LANG_ART(ftype)+" "+ftype+" form.\n", 
        NOTLOOKERS+({ TP }), TP);

    sRequired--;
    return 1;
}


int get_signercount_required()
{
    return sRequired;
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
