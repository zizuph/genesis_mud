/*
 * 2010-10-02 Lavellan  "submit" with no args no longer bugs.
 * 2010-09-12 Lavellan  Changed check for removal of form as it didn't work due
 *  to bug in mudlib (or at least disagreement with docs...) 
 * v2.0 2003-09-17 by Dargoth
 *   Changed from room to generic interface.
 * 2003-06-30 by Dargoth
 * Notarial services functions. 
 * People can:
 *   - get blank forms
 *   - submit filled-in forms (blankform.c)
 *     those then are checked and 
 *     the info is transfered to a signform.c
 *     and given back to user for signing.
 *   - submit a signed form for storage
 * 
 * This is the obj that must be inherited in objects wishing 
 * to implement Notarial Services functionality (usually rooms).
 *     
 * In addition, those rooms must have:
 *  init_notary_service() in their init();
 *  leave_inv_notary(object obj, object to) in their leave_inv().
 *
 */
#include "notary.h"
#include <macros.h>
#include <money.h>
#include <stdproperties.h>

#include "fees.h"
#include "notary_service.h"    

/* prototypes */
int submit_form(string arg);
int get_blank(string arg);
int notary_help(string str);
void leave_inv_notary(object obj, object to);


void init_notary_service()
{
    setuid();
    seteuid(getuid());

    add_action(submit_form,"submit");
    add_action(get_blank,"get");
    add_action(notary_help,"help");

    if (interactive(TP) && !objectp(present(NREADER_ID, TP)))
        clone_object(NREADER)->move(TP);
}

/* 
 * Getting a blank form
 */
int get_blank(string arg)
{
    int formstatus;
    int fcount;
    
    if (interactive(TP))
    {
        NF("Get what?\n");
        if ( sizeof(regexp(({ arg }),"^(blank |notarial |)form$")) )
        {
            /* we attempt to limit the number of forms one individual can get
                per login. Otherwise, small as the objects are, anybody could 
                just bring MUD down by simply doing "get form" here N thousand 
                times... */
            fcount=TP->query_prop(LIVE_I_FORMS_GOT);
            if (SECURITY->query_wiz_level(TP->query_real_name()) || 
                (fcount < MAX_FORMS_GIVEN))
            {
                formstatus=clone_object(BLANKFORM)->move(TP);
                switch (formstatus)
                {
                    case 0:
                        write(N_GET_OK_SELF);
                        tell_room(ENV(TP),N_GET_OK_OTHERS,NOTLOOKERS + ({ TP }),TP);
                        TP->add_prop(LIVE_I_FORMS_GOT,fcount+1);
                        return 1;
                    case 1:
                    case 8:
                        write(N_TOO_LOADED);
                    default:
                        write(N_FAIL_GET_SELF);
                        tell_room(ENV(TP),N_FAIL_GET_OTHERS,NOTLOOKERS+({TP}),TP);
                        return 1;
                }
            }
           NF(N_TOO_MANY_FORMS);
               
        }
    }
    return 0;
}

/* Help system */
static int notary_help(string str)
{
    string helpfile="general";
    string *args;

    if (!strlen(str))
        return 0;

    args=explode(str," ");

    NF("Help with what?\n");
    if (wildmatch("notary*",str))
    {
        if (sizeof(args)>1)
            helpfile=args[1];
        
        /* these helpfiles shouldn't be large,
           so we can use cat instead of more */
        if (!cat(NHELP("notary/"+helpfile)))
        {
            notify_fail("No such notary help topic found.\n",1);
            return 0;
        }
        return 1;
    }
    return 0;
}

/* 
 * Form can be submitted in 2 readings: 
 * blankform filled -> submit -> signform given back
 * signform signed -> submit -> fee taken & doc entered in storage
 */
static int submit_form(string arg)
{
    mixed formlist;
    int fidx;
    object form, readyform;
    mapping values;
    mixed pass; /* which pass of the form is being submitted?
                   first or second? */
                       
    string not_error=N_FAIL_FORMVALUES1;
    string not_error2=N_FAIL_FORMVALUES2;
    string not_error3=N_FAIL_FORMVALUES3;
    
    string ok_msg1=N_FORM_OK1;

    NF("Submit what?\n");

    if (!arg)
        return 0;

    if(parse_command(arg,INV(TP),"%i",formlist))
    {
        /* we get the 'form' or 'xth form' */
        NF("Submit which/what form?\n");
        fidx=formlist[0];
        if (fidx == 1 || fidx<0)
        {
            NF("You can only submit notarial forms here.\n");

            form=formlist[ABS(fidx)];
            if (form->query_prop(OBJ_I_IS_NFORM))
            {
                write(N_SUBMIT_MSG_SELF);
                  tell_room(ENV(TP),N_SUBMIT_MSG_OTHERS,
                    NOTLOOKERS + ({ TP }),TP);
                
                values=form->get_form_values();
                if (mappingp(values))
                {
                    NF("You can't submit an empty form.\n");
                    if (m_sizeof(values))
                    {
                        pass=NMANAGER->check_form(values);
                        if (stringp(pass))
                        {
                            write(not_error+"you,"+not_error2+pass+not_error3);
                            tell_room(ENV(TP),not_error+QCTNAME(TP)+not_error2+
                                pass+not_error3,TP,TP);
                            return 1;
                        }
                        else 
                            switch(pass)
                            {
                                case 1:
                                    write(N_CHECK_OK);
                                    readyform=clone_object(SIGNFORM);
                                    readyform->set_form_values(values);
                                    write(N_SAY_PREFIX+"you: "+ok_msg1);
                                    tell_room(ENV(TP),N_SAY_PREFIX+
                                        QTNAME(TP)+": "+ok_msg1,TP,TP);
                                    form->remove_object();
                                    readyform->move(TP);
                                    return 1;
                                case 2:
                                    if (MONEY_ADD(TP,-PROCESSING_FEE))
                                    {
                                        write(N_SUBMIT_OK_SELF);
                                        tell_room(ENV(TP),N_SUBMIT_OK_OTHERS,TP,TP);
                                        
                                        values+=([ EXPIRY:time()+INITIAL_EXPIRY ]);
                                       
                                        form->remove_object(); 
                                        if (!objectp(form))
                                        {
//                                        if (form->remove_object())
//                                        {
                                            NMANAGER->add_document(values);
                                            write(N_OK_REMINDER);
                                        }
                                        else
                                            write(N_FAIL_SUBMIT);
                                    }
                                    else
                                        write(N_FAIL_NOMONEY);
                                       
                                    return 1;
                                default: 
                                    log_file(NERROR,ctime(time())+
                                        " Unspecfied error at submitting doc.\n");
                             }
                      }
                  }
                  return 1;
              }
          }
    }
    return 0;
}

/*
 * Function name: leave_inv_notary
 * Description  : Call this function from your leave_inv() function. It will
 *                destruct the notary reader.
 * Arguments    : object obj - the object leaving.
 *                object to  - where 'obj' is leaving to.
 */
void leave_inv_notary(object obj, object to)
{
    object reader;

    /* Remove mailreader from players. */
    if (objectp(reader = present(NREADER_ID, obj)))
    {
        reader->remove_object();
    }
}
