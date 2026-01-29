/*
 * Notarial document manager
 * v2.0 2003-09-17 by Dargoth  
 *     misc updates and fixes.
 * v1.0 2003-06-27 by Dargoth
 * 
 * Handles the notarial documents:
 *  - registration
 *  - available documents list
 *  - gives a document file contents along with 
 *    info on it
 * 
 */
#pragma no_clone
#pragma no_inherit

#include "notary.h"
#include <options.h>
#include <macros.h>
#include <composite.h>

inherit "/std/object";

static mapping formtypes=([ "agreement":DOC_AGREEMENT, "contract":DOC_CONTRACT, 
    "order":DOC_ORDER, "general":DOC_GENERIC, "request":DOC_REQUEST,
    "announcement":DOC_ANNOUNCEMENT, "treaty":DOC_TREATY ]);

static mapping formaccess=([ "private":DOC_PRIVATE, "public":DOC_PUBLIC, 
    "guild":DOC_GUILD, "guildleaders":DOC_GLEADER ]);

static status gindexBusyFlag=0;
/* if this is set, index manipulation should be postponed... */

/* 
   Global document list,loaded on startup.
   Contains all info about docs except actual contents
*/
mapping gdocIndex;

/* prototypes */
void restore_index();
void save_index();
nomask int rebuild_index();
nomask mixed check_form(mapping doc);
nomask int can_access(object who,string doc);
string *get_guilds_short(object who);
string *get_guilds_long(object who);
string *get_guildleader(object who);
nomask void expire_documents();
static nomask int valid_caller(object who);
static nomask void expire_single_doc(string index);
nomask object get_copy(object who,string docidx);
nomask string get_full_signers(mapping doc);
nomask string get_signers(mapping doc);


void create_object()
{
    setuid(); seteuid(getuid());

    if (time()-file_time(NINDEX+".o") > REBUILD_PERIOD)
    { 
        rebuild_index();
        return;
    }
    restore_index();
}

/* Index file management */

void restore_index()
{
    log_file(NINDEXLOG,ctime(time())+" index restore from "+NINDEX+"... ");

    if (!gindexBusyFlag && (file_size(NINDEX+".o")>0))
    {
        log_file(NINDEXLOG,"success.\n");
        gdocIndex=restore_map(NINDEX);
    }
    else
    {
        log_file(NINDEXLOG,"failure.\n");
        gdocIndex=([]);
    }
}

void save_index()
{
    log_file(NINDEXLOG,ctime(time())+" attempting index save.\n");
    
    if (!gindexBusyFlag && m_sizeof(gdocIndex))
    {
        save_map(gdocIndex, NINDEX);
        log_file(NINDEXLOG,ctime(time())+" saved index to "+NINDEX+".\n");
    }
    else
        log_file(NINDEXLOG,ctime(time())+" failed, empty index or index busy.\n");
}


/*
 * NAME
 *        get_doc_access - gets form/doc access textual name
 *
 * SYNOPSIS
 *        string get_doc_access(int arg|mapping arg)
 * 
 * DESCRIPTION
 *        Function gives document access name, arg can be either
 *        a bitfield, or a mapping containing integer bitfield
 *        in a mapping value arg[BITFIELD]
 *
 * SEE ALSO
 *        get_doc_type, notary_base, notary.h
 */
string get_doc_access(mixed arg)
{
    int access_type=0;
    int i,szval;
    string *indexes;

    if (mappingp(arg))
        access_type=((int)arg[BITFIELD] & DOC_ACCESS);
    else if (intp(arg))
        access_type=arg & DOC_ACCESS;

    if (access_type)
    {
        indexes=m_indexes(formaccess);
        szval=sizeof(indexes);
        for(i=0;i<szval;i++)
            if (formaccess[indexes[i]]==access_type)
                return indexes[i];
    }
    return EMPTYFIELD;
}


/*
 * NAME
 *        get_doc_type - gets doc type textual name
 *
 * SYNOPSIS
 *        string get_doc_type(int arg|mapping arg)
 * 
 * DESCRIPTION
 *        Function gives document type name, arg can be either
 *        a bitfield, or a mapping containing integer bitfield
 *        in a mapping value arg[BITFIELD]
 *
 * SEE ALSO
 *        get_doc_access, notary_base
 */
string get_doc_type(mixed arg)
{
    int form_type=0;
    int i,szval;
    string *indexes;

    if (mappingp(arg))
        form_type=((int)arg[BITFIELD] & DOC_TYPES);
    else if (intp(arg))
        form_type=arg & DOC_TYPES;

    if (form_type)
    {
        indexes=m_indexes(formtypes);
        szval=sizeof(indexes);
        for(i=0;i<szval;i++)
            if (form_type==formtypes[indexes[i]])
                return indexes[i];
    }
    return EMPTYFIELD;
}

/* Gives the valid form types player can use */
string get_valid_types()
{
    return COMPOSITE_WORDS(m_indexes(formtypes));
}

/* Gives the valid access types player can use */
string get_valid_access()
{
    return COMPOSITE_WORDS(m_indexes(formaccess));
}

/*
 * Returns the type of doc based on given string
 * representation. Used when player chooses doc type.
 * A valid type can't be 0, so no additional checking needed.
 */
int get_type(string arg)
{
    return formtypes[arg];
}

/*
 * Returns the access of doc based on given string
 * representation. Used when player chooses doc access.
 * Valid access can't be 0, so no additional checking needed.
 */
int get_access(string arg)
{
    return formaccess[arg];
}

/*
 * Tries to add the document to the storage.
 * Saves the file and updates the index.
 * All checks on doc validity/payment should be 
 * done prior to this in the reader.
 * 
 * Returns: 1/0 success/failure
 */
nomask int add_document(mapping doc)
{

    string fname=""+time();

    if (!gindexBusyFlag && check_form(doc) == 2)
    {
        if (doc[EXPIRY]==0 || doc[EXPIRY]< time())
            return 0;

        /* getting unique filename.. shouldn't be that hard. */
        while (file_size(NDOCS+FPREFIX+fname+".o")>=0)
            fname=""+time();
        
        doc[CREATETIME]=time();
        
        save_map(doc,NDOCS+FPREFIX+fname);

        doc=m_delete(doc,CONTENTS);

        gdocIndex+=([ fname:doc ]);
        log_file(NLOG,ctime(time())+" "+CAP(MYNAME)+" added "
            +FPREFIX+fname+", '"+doc[DOCTITLE]+"'.\n");
        return 1;
    }
    return 0;
}

/* Checks whether form is a valid form, and returns:
 *  1 - it is the first pass, supposedly blankform is being submitted 
 *  2 - it is the second pass, signform is being submitted.
 *  string - the form is not properly filled out, or is not 
 *           wholly signed, this is the err message
 */      
nomask mixed check_form(mapping form)
{
    string *errmsg=({ });
    mapping signers=([]);
    string *signeridx;
    int retval=2;
    int szsigned,szunsign;
    
    signers=form[SIGNERS];
    
    /* are signers specified? */
    if (!m_sizeof(signers))
        errmsg+=({ "no signers specified" });

    /* are signers valid players? */
    signeridx=m_indexes(signers);
    if (sizeof(filter(signeridx,SECURITY->exist_player)) != sizeof(signeridx))
        errmsg+=({ "non-existing signers specified" });
    
    /* is form not signed (blankform), partially signed (error), 
       or fully signed (signform) */
    signeridx=m_values(signers);
    /* anybody hasn't signed yet? */
    szunsign=sizeof(filter(signeridx,intp));
    szsigned=sizeof(filter(signeridx,stringp));
    
    /* if this is not signed, it can only be at pass 1 at best. */
    if (szunsign > 0)
    {
        retval=1;
        /* partially signed? */
        if (szsigned)
            errmsg+=({ "form is only partially signed" });
    }
    
    if (! strlen(form[DOCTITLE]) || form[DOCTITLE]==EMPTYFIELD)
        errmsg+=({ "title missing" });
    if (! strlen(form[CONTENTS]))
        errmsg+=({ "text of the document missing" });
    if (!(form[BITFIELD] & DOC_TYPES))
        errmsg+=({ "missing document type" });
    if (!(form[BITFIELD] & DOC_ACCESS))
        errmsg+=({ "missing document access" });

    if (sizeof(errmsg))
        return COMPOSITE_WORDS(errmsg);
    return retval;

}

/*
 * Attempts to rebuild index from the actual files in the dir,
 * and calls expire_documents & save_index, after done.
 *
 * Returns the total number of entries processed.
 */
nomask int rebuild_index()
{
    string *filelist,fname;
    int i,sz;
    mapping docInfo;

    if (gindexBusyFlag)
    {
        log_file(NERROR,ctime(time())+" Attempting to rebuild index when already busy.\n");
        return 0;
    }

    gindexBusyFlag=1;

    gdocIndex=([ ]);
    
    /* taking only the right files..., regexp '+' not implemented so 
       we use '*' and use 2x '0-9' */
    filelist=get_dir(NDOCS);
    sz=sizeof(filelist);
    if (sz)
        filelist=regexp(get_dir(NDOCS),"^"+FPREFIX+"[0-9][0-9]*\\.o$");
    sz=sizeof(filelist);

    log_file(NINDEXLOG,ctime(time())+" rebuilding index, going thru "+
            sz+" entries.\n");
    for (i=0;i<sz;i++)
    {

        fname=filelist[i][0..strlen(filelist[i])-3];

        docInfo=restore_map(NDOCS+fname);
        gdocIndex+=([ fname[1..]:m_delete(docInfo,CONTENTS) ]);
#ifdef DEBUG_MODE
        log_file(NINDEXLOG,ctime(time())+" added info about "+fname+".\n");
#endif
    }
    
    gindexBusyFlag=0;

    expire_documents();
    save_index();

    return sz;
}

/*
 * Can player 'who' access this doc? 
 * Assuming doc is document index entry in gdocIndex
 */
static nomask int can_access(object who, string doc)
{
    string requester;
    status signer;
    string signfor;
    int access;
    string *docGuilds;
    mapping docInfo;
    
    docInfo=gdocIndex[doc];
    
    if (!mappingp(docInfo) || !interactive(who) || 
        ((int)docInfo[EXPIRY])<time())
            return 0;


    access=docInfo[BITFIELD] & DOC_ACCESS ;
    
    if (access == DOC_PUBLIC)
        return 1;

    requester=who->query_real_name();

    if (!requester)
        return 0;

    /* Has the requester signed this doc? */
    signer=(member_array(requester,m_indexes(docInfo[SIGNERS]))>=0? 1: 0);
    
    if (access == DOC_PRIVATE)
        return signer;

    /* Ok, checking guild access. If he signed, what guild he signed for? */
    if (signer)
        signfor=docInfo[SIGNERS][requester];

    /* What guilds has the document been signed for? */
    docGuilds=m_values(docInfo[SIGNERS]);
    
    switch(access)
    {
        case DOC_GUILD:
                if (signer && signfor==NOGUILD)
                    return 1;
                if (sizeof(get_guilds_short(who) & docGuilds))
                    return 1;
                break;
        case DOC_GLEADER:
                if (sizeof(get_guildleader(who) & docGuilds))
                    return 1;
        default:
                log_file(NERROR,ctime(time())+" Unknown access type "+access+
                    " encountered for index entry "+doc+".\n");
    }
    return 0; 
}

/* 
 * Gets a person's guilds (long names), for use 
 * in signing process.
 */
public nomask string *get_guilds_long(object who)
{
    string *retval=({ });
    
    if (interactive(who))
    {
        retval+= ({ QRACE(who),QOCC(who), QLAY(who) });
        return retval;
    }
    return 0;
}

/* 
 * Gets a person's guilds (short names), misc uses internally
 * and from nreader.
 */
public nomask string *get_guilds_short(object who)
{
    string *retval=({ });

    if (interactive(who))
    {
        retval+= ({ QRACESHORT(who),QOCCSHORT(who), QLAYSHORT(who) });
        return retval;
    }
    return 0;
}

/* 
 * Gives short names of guilds the person is 
 * a leader/council member of.
 */
public nomask string *get_guildleader(object who)
{
    string *retval=({});
    
    if (interactive(who) && who->query_guild_leader())
    {
        if (who->query_guild_leader_race())
            retval+=({ QRACESHORT(who) });
        if (who->query_guild_leader_occ())
            retval+=({ QOCCSHORT(who) });
        if (who->query_guild_leader_lay())
            retval+=({ QLAYSHORT(who) });
    }
    return retval;
}

/* 
 * Get the available doc list for player 'who'
 */
nomask public mapping get_list(object who)
{
    mapping docList=([]);
    string *docIndex;
    string *docFnames;
    int i,sz;
    
    if (!valid_caller(who))
        return 0;
    
    sz=sizeof(docFnames=m_indexes(gdocIndex));
    
    for (i=0;i<sz;i++)
        if (can_access(who,docFnames[i]))
            docList+=([ docFnames[i]:gdocIndex[docFnames[i]] ]);
    
    return docList;
}

/*
 * Goes thru index and deletes all stale entries
 * (expiry time < time())
 */
nomask void expire_documents()
{
    string *docFnames;
    int i,sz;
    
    if (gindexBusyFlag)
    {
        log_file(NINDEX, ctime(time())+" expire_documents failed, index in use.\n");
        return;
    }

    gindexBusyFlag=1;

    sz=sizeof(docFnames=m_indexes(gdocIndex));

    log_file(NINDEXLOG,ctime(time())+" expiring docs, deleting stale ones, "+
        "index length "+sz+".\n");
    
    for (i=0;i<sz;i++)
    {
        if ((int)gdocIndex[docFnames[i]][EXPIRY] < time())
            expire_single_doc(docFnames[i]);
    }
    gindexBusyFlag=0;

}

/*
 * Function name : extend_document
 * Description   : Attempts to extend document storage.
 * Arguments     : string - doc item in the doc index,
 *                 int - extension time in seconds,
 *                       counted from the call time
 * Returns       : 1 - success / 0 - failure
 */
public nomask int extend_document(string docidx,int duration)
{
    mapping doc;
    int extendperiod;
    
    if (!CALL_BY(NREADER))
    {
        log_file(NERROR,ctime(time())+" security: attempt to extend doc "+
            "from without NREADER, by "+TP->query_real_name()+"("+OB_NAME(TP)+").\n");
    }

    extendperiod=time()+duration;

    if (intp(gdocIndex[docidx][EXPIRY]))
    {
        if (gdocIndex[docidx][EXPIRY]<time())
        {
            expire_single_doc(docidx);
            return 0;
        }
        gdocIndex[docidx][EXPIRY]+=duration;
        doc=restore_map(NDOCS+FPREFIX+docidx);
        doc[EXPIRY]+=duration;
        save_map(doc,NDOCS+FPREFIX+docidx);
        save_index();
        log_file(NLOG,ctime(time())+" "+CAP(MYNAME)+" extended "+
            docidx+" for "+duration+"s.\n");

        return 1;
    }
    return 0;
}

/*
 * Deletes a single document from index and harddrive, unconditionally.
 * Can't be called from other objs, use remove_document instead.
 */
static nomask void expire_single_doc(string index)
{
    gdocIndex=m_delete(gdocIndex,index);
#ifdef DEBUG_MODE
    log_file(NINDEXLOG,ctime(time())+"  Deleting "+FPREFIX+
                index+".o ... ");
#endif
    rm(NDOCS+FPREFIX+index+".o");
}

/* 
 * Function name: pretty_print
 * Arguments:     object - player, string - document index
 * Description:   Formats the document in a readable fashion,
 *                and returns it as a string; intended to be
 *                called by nreader.
 * Returns:       string - formatted output, taking into
 *                account player's screenwidth settings.
 */
nomask string pretty_print(object who,string docindex)
{
    object copy;
    mapping doc;
    int swidth;
    string dtype;

    if (valid_caller(who) && can_access(who,docindex))
    {
        swidth=who->query_option(OPT_SCREEN_WIDTH)-1;
        swidth=(swidth<40 ? 79: swidth);

        doc=restore_map(NDOCS+FPREFIX+docindex);

        dtype=(((doc[BITFIELD] & DOC_TYPES )== DOC_GENERIC)? 
            "general document": get_doc_type(doc[BITFIELD]) );

        return "Title   : "+doc[DOCTITLE]+"\n"+
               "Type    : "+CAP(get_doc_access(doc[BITFIELD]))+" "+dtype+"\n"+
               "Created : "+ctime(doc[CREATETIME])+"\n\n"+
               doc[CONTENTS]+"\n"+
               "Signed  :\n"+break_string(get_full_signers(doc),900,10)+"\n";
    }
    return 0;
}

/*
 * Function name:   valid_caller
 * Arguments    :   object - playerobj
 * Description  :   Security checks on whether we are called properly 
 *                  - ie. from reader object go here. This func should be 
 *                    called in any function of this object that gives player 
 *                    any sensitive info (such as document contents).
 * Returns       :  1 - access is ok/0 - caller is not valid
 */
static nomask int valid_caller(object player)
{
    object caller,prev,t;
    int i=0;

    if (CALL_BY(NREADER))
            return 1;

    t=0;
    caller=previous_object();

    log_file(NERROR,ctime(time())+" WRN: secure call attempt as if by "+
            player->query_real_name()+": \n");
    do
    {
        prev=t;
        t=calling_object(i--);
        log_file(NERROR,sprintf("    %s",(objectp(t)?"\n--> "+file_name(t):": "+
            prev->query_real_name()+"\n")));
    }
    while (objectp(t));

    return 0;
}

/*
 * Function name : get_copy
 * Arguments     : object - playerobj, string - document index
 * Description   : Allows a player to get a copy of a document.
 *                 Any fees are applied seperately (in reader).
 * Returns       : object - doccopy object or 0 - if failed.
 */
public nomask object get_copy(object who,string docidx)
{
    object copy;
    mapping doc;
    
    if (valid_caller(who) && can_access(who,docidx))
    {
            doc=restore_map(NDOCS+FPREFIX+docidx);
            copy=clone_object(DOCCOPY);
            copy->set_form_values(doc);
            log_file(NLOG,ctime(time())+" "+CAP(MYNAME)+" got a copy "+
                "of "+docidx+".\n");
            return copy;
    }
    return 0;
}


/*
 * Function name  : get_full_signers
 * Description    : Gets the signer names of the form along with signing info.
 * Arguments      : mapping - notarial document
 * Returns        : string - signer names and guilds they signed for,
 *                  or EMPTYFIELD if none set.
 */
nomask string get_full_signers(mapping doc)
{
    string *retval=({});
    string guild;
    string title;
    string currsig;
    string *signers;
    int i,szval;

    /* if the signers have signed, the values of 
       m_values should be string, not int.
       In the other case implode on ints will give 0 length string */
    signers=m_indexes(doc[SIGNERS]);
    szval=sizeof(signers);
    for (i=0;i<szval;i++)
    {
        guild=doc[SIGNERS][signers[i]];
        if (stringp(guild))
        {
            currsig=CAP(signers[i]);
            if (mappingp(doc[SIGNERTITLES]))
            {
                title=doc[SIGNERTITLES][signers[i]];
                if (stringp(title))
                    currsig+=" "+title;
            }

            currsig+=(guild==NOGUILD ? "" :", for "+QGLONG(guild));

            retval+=({ currsig });
        }
    }

    if (sizeof(retval))
        return implode(retval,",\n");
    return UNSIGNED;
}


/*
 * Function name  : get_signers
 * Description    : Gets the signer names of the form.
 * Arguments      : mapping - notarial document
 * Returns        : string - signer names or EMPTYFIELD if none set.
 */
nomask string get_signers(mapping doc)
{
    if (m_sizeof(doc[SIGNERS]))
        return COMPOSITE_WORDS(map(m_indexes(doc[SIGNERS]),capitalize));
    return EMPTYFIELD;
}

/*
 * Function name : remove_document
 * Description   : Allows wizards to manually remove documents,
 *                 bugfix use only.
 * Arguments     : string - doc index
 * Returns       : 1 - success/ 0 - failure
 *
 */
nomask int remove_document(string doc)
{
    string name;

    name=TP->query_real_name();

    log_file(NINDEX,ctime(time())+" "+CAP(MYNAME)+" attempted to remove "+
        doc+" ");
    if (SECURITY->query_wiz_level(name))
    {
        write("Attempting to remove index entry "+doc+"... ");
        if (mappingp(gdocIndex[doc]))
        {
            expire_single_doc(doc);
            log_file(NINDEX,"succeeded.\n");
            write("removed.\n");
            return 1;
        }
        write("not found.\n");
        log_file(NINDEX,"failed (doc nonexistant).\n");
        return 0;
    }
    write("nasty business, you are not allowed to!\n");
    log_file(NINDEX,"failed (not a wizard).\n");

    return 0;
}
