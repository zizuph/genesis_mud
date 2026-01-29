/*
 * 2003-07-11 by Dargoth
 *
 * Notarial "reader" object, cloned in a notarial services room
 * to each player upon entering, 
 * A bit similar to mailreader.
 * Allows one to:
 *  - list documents he can access,
 *  - read particular document, 
 *  - request a copy of a document,
 *  - extend the document storage
 *
 *  Somewhat based on /secure/mail_reader - I peeked there every now and then,
 *  therefore some code and comments within code are based on the stuff 
 *  implemented in mail_reader
 *  2003-10-08 - removed extension time check, as extension was
 *               reworked to be cumulative.
 */
#pragma no_inherit

#include "notary.h"
#include <stdproperties.h>
#include <time.h>
#include <money.h>
#include <macros.h>
#include <composite.h>

#define N_COPY_OK_SELF "A notary takes out the original from the archive "+ \
    "and carefully makes a copy for you. "+(random(2)>0?"He":"She")+ \
    " then proceeds to seal it with the Notary Service seal, "+ \
    "and gives the parchment to you.\n"

inherit NBASE;

#include "fees.h"

static mapping gdocIndex=([]); /* document mapping available to user */
static string *gdocList=({}); /* document list containing indexes */
static int szGld=0;
static int szPriv=0;

int read(string arg);
int list(string arg);
int request(string arg);
int extend_storage(string arg);
static nomask void check_status();
nomask static void build_list();

void create_object()
{

    set_name(({ "reader", "index", NREADER_ID }));
    set_short("paper index");

    setuid();
    seteuid(getuid());

    set_long("This is an index bearing the list of notarial documents already in the Archive, which "+
"are available to you.\nYou can use it to do the following:\n"+
"   list all/public/private/guild   - list the documents available to you.\n"+
"   read <number>                   - read a particular document.\n"+
"  *request <number>                - request a copy of a particular document.\n"+
"   extend <number> for <duration>  - extend the storage of a document for\n"+
"                                     a particular duration.\n"+
"  *A copy will cost you "+COPY_FEE+"cc ("+(COPY_FEE/1728)+"pc).\n");

    add_prop(OBJ_M_NO_DROP,"There is no reason to drop the document reader.\n");
    add_prop(OBJ_M_NO_GIVE,"You may not give away your document reader.\n");
    add_prop(OBJ_M_NO_TELEPORT, 1);
    add_prop(OBJ_M_NO_STEAL,    1);
    add_prop(OBJ_M_NO_SELL,     1);
    add_prop(OBJ_M_NO_BUY,      1);

    remove_prop(OBJ_I_WEIGHT);
    remove_prop(OBJ_I_VOLUME);
    remove_prop(OBJ_I_VALUE);

}

void init()
{
    /* Paranoid check! Don't mess with documents! */
    if ((TP != environment()) || (!interactive(environment())))
            return;

    add_action(read,"read");
    add_action(list,"list");
    add_action(request,"request");
    add_action(extend_storage,"extend");

    /* if the player just dropped in on his way and is going away,
       we won't be loading his messages, hopefully. */
    set_alarm(0.1, 0.0, &check_status());
}

/*
 * Function name: read
 * Description  : Read documents
 * Arguments    : string arg - User input
 * Returns      : int        - 1/0 - success/failure.
 */
nomask static int read(string arg)
{
    int docno;
    string doctext;

    check_status();
    
    NF("Read what?\n");
    if (!stringp(arg))
        return 0;
    if (sscanf(arg,"%d",docno)<1)
        return 0;
    
    if (docno < 1 || docno > sizeof(gdocList))
    {
        write("There seems to be no such document number.\n");
        return 1;
    }
    
    docno--;
    
    doctext="\n"+NMANAGER->pretty_print(TP,gdocList[docno])+"\n";
    
    if (!stringp(doctext) || !strlen(doctext))
        write("It seems you are trying to read something you "+
            "really shouldn't be able to.\n");
    else
        TP->more(doctext);
    return 1;
}

/*
 * Function name: list
 * Description  : list documents
 * Arguments    : string arg - User input
 * Returns      : int        - 1/0 - success/failure.
 */
static int list(string arg)
{
    string accstr;
    string list="";
    int start,stop,i,acc;
    mapping doc;

    check_status();

    NF("List what?\n");
    
    switch (arg)
    {
        case "private": start=0;
                        stop=szPriv;
                        break;
        case "guild":   start=szPriv;
                        stop=szPriv+szGld;
                        break;
        case "public":  start=szGld+szPriv;
                        stop=sizeof(gdocList);
                        break;
        case "all":     start=0;
                        stop=sizeof(gdocList);
                        break;
        default:        return 0;        
    }

    if (stop-start <=0)
    {
        write("There seem to be no such documents available to you.\n");
        return 1;
    }
    list +="You have access to "+(stop-start)+" document(s).\n";

    list+=sprintf("%-3s %-40.40s %-10.10s - %-10.10s  %-4s\n%80'-'s\n",
        "Nr.", "Title", "Type", "  Expires", " Access","");

        
    for (i=start;i<stop;i++)
    {
        doc=gdocIndex[gdocList[i]];
        acc=doc[BITFIELD] & DOC_ACCESS;
        switch (acc)
        {
            case DOC_PRIVATE:accstr="prv";break;
            case DOC_GLEADER:accstr="lead";break;
            case DOC_PUBLIC:accstr="pub";break;
            case DOC_GUILD:accstr="gld";break;
            default: accstr="---";
        }

        list+=sprintf("%2d: %-40.40'.'s %-10.10s -  %-10.10s  %4s\n",
            i+1,
            doc[DOCTITLE],
            NMANAGER->get_doc_type(doc[BITFIELD]),
            TIME2STR((int)doc[EXPIRY]-time(),2),
            accstr);
    }
    list+="\n";

    TP->more(list);

    return 1;
}

/*
 * Function name: request
 * Description  : request a copy of a document
 * Arguments    : string arg - User input
 * Returns      : int        - 1/0 - success/failure.
 */
static int request(string arg)
{
    int docno;
    object copy;


    check_status();
    
    NF("Request what?\n");
    if (!stringp(arg) || sscanf(arg,"%d",docno)<1)
        return 0;
    
    if (docno < 1 || docno > sizeof(gdocList))
    {
        write("No such document number.\n");
        return 1;
    }
    docno--;

    copy=NMANAGER->get_copy(TP,gdocList[docno]);
    
    if (objectp(copy))
    {
        if (MONEY_ADD(TP,-COPY_FEE))
        {
            write(N_COPY_OK_SELF);
            copy->move(TP);
        }
        else
        {
            write("It seems that you lack the funds for getting "+
                "a copy.\n");
            copy->remove_object();
        }
    }
    else
    {
        write("It seems you didn't have the right to access "+
            "that document.\n");
    }
    return 1;
}

/*
 * Function name: extend_storage
 * Description  : extend storage time of a document
 * Arguments    : string arg - User input
 * Returns      : int        - 1/0 - success/failure.
 */
static int extend_storage(string arg)
{
    string duration;
    string *valid_periods;
    int docno,extendperiod,acc,feetype,fee;
    mapping doc;
    
    check_status();

    valid_periods=m_indexes(storage_times);

    NF("Extend what? Correct form is \"extend <#> for <duration>\", where "+
    "<duration> can be be: "+COMPOSITE_WORDS(valid_periods)+".\n");
    
    if (!stringp(arg) || sscanf(arg,"%d for %s",docno,duration)<2)
        return 0;
    if (docno < 1 || docno > sizeof(gdocList))
    {
        write("Invalid document number specified.\n");
        return 1;
    }
    docno--; /* decing docno so it corresponds to the array number */

    extendperiod=member_array(duration,valid_periods);
    if (extendperiod < 0)
    {
        write("Invalid period. Valid extension periods are:  "+
            COMPOSITE_WORDS(valid_periods)+".\n");
        return 1;
    }
    extendperiod=storage_times[duration];
    
    /* check for what kind of doc this is, pub/priv/gld?
       according to that storage fees will be taken 
       from fees.h */
    doc=gdocIndex[gdocList[docno]];

    /*
     * This check is not needed, as extension times
     * are cumulative now.
     *  
    if ((int)doc[EXPIRY] >= (time()+extendperiod))
    {
        write("This document is already paid for the next "+
            CONVTIME((int)doc[EXPIRY]-time())+".\n");
        return 1;
    }
    */
    acc=doc[BITFIELD] & DOC_ACCESS;
   
    switch(acc)
    {
        case DOC_PRIVATE:feetype=FEE_PRIVATE;break;
        case DOC_GUILD:feetype=FEE_GUILD;break;
        case DOC_PUBLIC:feetype=FEE_PUBLIC;break;
        default: 
            write("Some kind of wrongness sensed. Storage "+
            "extension refused. Please report this via 'bug'.\n");
            log_file(NERROR,ctime(time())+" Invalid doc access "+
                acc+" in nreader, for doc "+gdocList[docno]+"!\n");
            return 1;
    }
    
    fee=storage_fees[extendperiod][feetype];
    
    if (MONEY_ADD(TP, -fee*PLATINUMS))
    {
        log_file(NLOG,ctime(time())+" "+CAP(MYNAME)+" paid "+(fee*PLATINUMS)+" "+
        "to extend "+gdocList[docno]+" for "+extendperiod+".\n");
        if (NMANAGER->extend_document(gdocList[docno],extendperiod))
            write("You extend the storage of the "+
                NMANAGER->get_doc_type(doc[BITFIELD])+" titled \""+
                doc[DOCTITLE]+"\" for "+duration+".\n");
        else
        {
            write("You seem to have been a a tad too late to extend "+
                "the document storage.\n");
            MONEY_ADD(TP,fee*PLATINUMS);
        }
    }
    else
        write("You seem to lack the funds to extend the storage "+
            "of this document for "+duration+". The fee is: "+
            fee+"pc.\n");
    return 1;
}

/*
 * Function name: check_status
 * Description  : checks if still held by player, and reloads doclist.
 * Arguments    : none
 * Returns      : void
 */
static nomask void check_status()
{
    if (!interactive(environment()) || environment()!=TP)
        remove_object();
    
    gdocIndex=NMANAGER->get_list(TP);
    build_list();
   
}

/* Function name: build_list
 * Description  : build an ordered list of documents indexed on type,
 * Arguments    : none
 * Returns      : void
 */
nomask static void build_list()
{
    int sz,i,access;
    string *pubList=({});
    string *privList=({});
    string *gldList=({});
    mapping tmpIndex;
    string *indexes;
    
    if (!mappingp(gdocIndex))
        return 0;

    tmpIndex=gdocIndex+([ ]);

    indexes=m_indexes(tmpIndex);
    sz=sizeof(indexes);
    
    for (i=0;i<sz;i++)
    {
        access=tmpIndex[indexes[i]][BITFIELD] & DOC_ACCESS;
        switch (access)
        {
            case DOC_PUBLIC:pubList+=({ indexes[i] });
                            break;
            case DOC_PRIVATE:privList+=({ indexes[i] });
                            break;
            case DOC_GLEADER: /* fall-through */
            case DOC_GUILD:gldList+=({ indexes[i] });
                            break;
            default: log_file(NERROR,ctime(time())+" nreader: invalid access "+
                        access+" in "+indexes[i]+".\n");
        }
    }
    gdocList= privList + gldList + pubList;
    szPriv=sizeof(privList);
    szGld=sizeof(gldList);
}
