
#include "guild.h"
#include <macros.h>
#define TEMP_M_POST    "_temp_m_post"
#define TEMP_M_POST2   "_temp_m_post_2"
#define EDITOROBJ      "/obj/edit"


mapping allmail = ([]);
/* Format: <player name>:({<filenum>, <filenum>, ...}) */

/* prototype */
void remove_old_entries();


/* The create function is called on creation of the object
 */
void
create()
{
    seteuid(getuid());
    restore_object(MASTER);
    set_alarm(3.0,0.0,"remove_old_entries");
}

/* This removes the empty elements from the mapping
 */
void
remove_old_entries()
{
    int i,j=0;
    string *idx = m_indexes(allmail);
    if (!idx || !sizeof(idx))
      return;
    for(i=0;i<sizeof(idx);i++)
      if (allmail[idx[i]] == ({}))
      {
	  allmail = m_delete(allmail, idx[i]);
	  j = 1;
      }
    if (j)
      save_object(MASTER);
}

/* When a thief leaves the guild, this function is called
 * from the master object.
 */
void
remove_thief(string member)
{
    int i;
    if (allmail[L(member)] && sizeof(allmail[L(member)]))
      for(i=0;i<sizeof(allmail[L(member)]);i++)
	rm(MAILDIR + allmail[L(member)][i]);
    allmail = m_delete(allmail, L(member));
    save_object(MASTER);
}

/* Check if someone has mail.
 * This is called from the postoffice upon entering.
 */
varargs int
check_mail(object player, int ringl=0)
{
    string pname = (ringl?"ringleader":player->query_real_name());
    string *mlist = allmail[pname];
    int i;

    if (!mlist || !sizeof(mlist))
    {
	write("No messages.\n");
	return 1;
    }

    for(i=0;i<sizeof(mlist);i++)
    {
	write("" + (i+1) + ": " + read_file(MAILDIR + mlist[i],1,2));
    }
    write("\n" + i + " message" + (i==1?"":"s") + ".\n");
    if (i>0)
      write("Type 'rread <num> <flag>' to read message number <num>. Give " +
	    "flag = 'd' to delete the message after reading.\n");
    return 1;
}

/* Check if someone has mail.
 */
varargs int
has_mail(object player, int ringl=0)
{
    string pname = (ringl?"ringleader":player->query_real_name());
    string *mlist = allmail[pname];

    return !(!mlist || !sizeof(mlist));
}

/* Someone is reading his/her mail.
 * This function is also used to delete mails by the reader.
 */
varargs int
read_mail(object player, int num, mixed flag, int ringl=0)
{
    string pname = (ringl?"ringleader":player->query_real_name());
    string *mlist = allmail[pname];

    if (!mlist || !sizeof(mlist) || num > sizeof(mlist) ||
	num <= 0)
    {
	write("No such message.\n");
	return 1;
    }

    write(read_file(MAILDIR + mlist[num-1],1));
    if (flag == "d")
    {
	allmail[pname] -= ({ mlist[num-1] });
	rm(MAILDIR + mlist[num-1]);
	save_object(MASTER);
	write("Message deleted.\n");
    }
    return 1;
}

/* This is called from the editing object. Someone is
 * done writing a mail and wants to send it now.
 */
void
done_editing(string message)
{
    string filename;
    string receiver = L(TP->query_prop(TEMP_M_POST));
    int ringl = TP->query_prop(TEMP_M_POST2);
    string pname = (ringl?"ringleader":TP->query_real_name());

    if (!message || message == "")
    {
	write("Aborted.\n");
	return;
    }

    if (!receiver)
    {
	write("No receiver! Message destroyed.\n");
	return;
    }

    filename = "b" + time();
    write_file(MAILDIR + filename,"From: " + C(L(pname)) + "  " +
	       ctime(time())[4..9] + "\n" + message + "\n");
    if (allmail[receiver])
      allmail[receiver] += ({ filename });
    else
      allmail += ([receiver:({ filename })]);
    save_object(MASTER);
    write("Message sent to: " + C(receiver) + "\n");
}

/* Someone wants to send a mail.
 */
varargs int
send_mail(object player, string receiver, int ringl=0)
{
    player->add_prop(TEMP_M_POST,receiver);
    player->add_prop(TEMP_M_POST2,ringl);
    clone_object(EDITOROBJ)->edit();
    return 1;
}
