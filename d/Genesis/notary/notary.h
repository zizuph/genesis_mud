/*
 * Include for all notary related stuff
 * 2003-06-20 Dargoth
 */

#ifndef __NOTARY_H_
#define __NOTARY_H_

#include <files.h> /* Provides SECURITY and EDITOR_OBJECT */
#include <filter_funs.h>

/* General defines */    
#define TP (this_player())
#define TO (this_object())
#define ENV(X) (environment((X)))
#define CAP(X) (capitalize((X)))
#define NF(X) notify_fail((X))
#define INV(X) all_inventory(X)
#define HE(X)  (((X))->query_pronoun())


/* ======Directories */
#define NOTARY_DIR "/d/Genesis/notary/"
/* prefix of filenames of the documents */
#define NOTARY(X)	(NOTARY_DIR+(X))
/* help topics */
#define NHELP(X)	NOTARY("help/"+(X))
/* documents dir */
#define NDOCS      "/d/Genesis/private/notary/"
/* index file for documents */
#define NINDEX     NDOCS+"INDEX"
/* temporary dir */
#define NTEMP   NOTARY("temp/")

/* Logfiles:
   all normal doc ops logged here */
#define NLOG       "archive_main"
/* expiry functions log here */
#define NEXPIRE "archive_expired"
    
#define NERROR  "archive_errors"
#define NINDEXLOG "archive_indexops"


/* Objects */
/* base object for common notarial things */
#define NBASE NOTARY_DIR+"base"
/* service object handling all kinds of stuff */
#define NMANAGER (NOTARY_DIR+"manager")
/* base form for common form things */
#define NFORM (NOTARY_DIR+"baseform")
/* blank form given to players for filling out */
#define BLANKFORM (NOTARY_DIR+"blankform")
/* form that is given back to player after verifying
    his input, can be signed and submitted for storage */
#define SIGNFORM (NOTARY_DIR+"signform")
/* document copy */
#define DOCCOPY (NOTARY_DIR+"doccopy")
/* Notarial document reader. Much like the mailreader, really. */
#define NREADER (NOTARY_DIR+"nreader")


/* guild querying stuff */
#define QGSHORT(X) SECURITY->query_guild_short_name((X))
#define QGLONG(X) SECURITY->query_guild_long_name((X))

#define QRACE(X) ((X))->query_guild_name_race()
#define QOCC(X) ((X))->query_guild_name_occ()
#define QLAY(X) ((X))->query_guild_name_lay()

#define QRACESHORT(X) QGSHORT(QRACE(X))
#define QOCCSHORT(X) QGSHORT(QOCC(X))
#define QLAYSHORT(X) QGSHORT(QLAY(X))

#define QLEADRACE(X) ((X)->query_guild_leader_race())
#define QLEADOCC(X)  ((X)->query_guild_leader_occ())
#define QLEADLAY(X)  ((X)->query_guild_leader_lay())

#define FPREFIX "d" /* File prefix for notarial docs */
#define NREADER_ID	"_notary_reader_"
    
#define MAX_TITLE_LEN 70
#define NOTARY_TITLE "Notarial services of Genesis"

/* time between two forced index rebuilds, as per Mercade's suggestion,
   by default once a week. */
#define REBUILD_PERIOD	(60*60*24*7)

/* Notarial document fields */
#define BITFIELD "bitfield"
#define DOCTITLE "title"
#define CONTENTS "contents"
#define EXPIRY "expiry"
#define SIGNERS "signers"
#define SIGNERTITLES "titles"
#define CREATETIME "created"

/* bit positions to check for different form related stuff */
/* form access types */
#define DOC_PRIVATE 1
#define DOC_PUBLIC  2
#define DOC_GUILD   4
#define DOC_GLEADER 8
/* DOC types */
#define DOC_AGREEMENT 16
#define DOC_CONTRACT 32
#define DOC_ORDER 64
#define DOC_GENERIC 128
#define DOC_REQUEST 256
#define DOC_ANNOUNCEMENT 512
#define DOC_TREATY 1024

#define DOC_ACCESS (DOC_PRIVATE | DOC_PUBLIC | DOC_GUILD | \
					DOC_GLEADER)
#define DOC_TYPES (DOC_AGREEMENT | DOC_CONTRACT | DOC_ORDER | DOC_GENERIC | \
					DOC_REQUEST | DOC_ANNOUNCEMENT | DOC_TREATY )

#define QDOCTYPE(X)	((NMANAGER)->get_doc_type(X))
#define QDOCACCESS(X)	((NMANAGER)->get_doc_access(X))

/* misc visual and filling things */
#define EMPTYFIELD "___"
#define NOGUILD "yourself"
#define UNSIGNED ""
#define SEPARATOR "-----------------------------------------------------\n"

#define LIVE_O_MARK_SIGNED "__live_mark_signed_notary_form"
#define OBJ_I_IS_NFORM "__obj_i_is_nform"

/* we can't let people have lots of forms...
   cloning objects out of nothing */
#define LIVE_I_FORMS_GOT "__live_i_notary_forms_got"
#define MAX_FORMS_GIVEN 30
    

/* those who are in room with us and can see us */
#define LOOKERS (FILTER_PLAYERS(INV(ENV(TP))) & \
				FILTER_CAN_SEE_IN_ROOM(INV(ENV(TP))))

/* those who are in room but can't see in it */
#define NOTLOOKERS (FILTER_PLAYERS(INV(ENV(TP))) - \
				FILTER_CAN_SEE_IN_ROOM(INV(ENV(TP))))

#endif
