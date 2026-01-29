/* Poster that lists recruitment info
History:
        26.1.95  query_wiz_rank replaces query_wiz_level   Maniac
	20.11.94	Created			    	   Glykron
*/

#pragma save_binary

inherit "/std/scroll.c";
#include <stdproperties.h>
#include "defs.h"
#include <std.h>
#include COUNCIL_HEADER
#include RECRUITER_HEADER

string
long_string()
{
    return "This golden poster has a list of names listed as recruitment " +
	"officers and a message.  " +
	"A golden marker is attached to the poster by a golden chain.  " +
	RECRUITER_CODE->query_recruiters_string() + "\n";
}

void
create_scroll()
{
    set_name("poster");
    set_adj("golden");
    set_long("@@long_string");
    set_file(TEXT("calian_recruitment_text"));
    add_item("marker",
	"The golden marker is semi-transparent and has the word \"change\" "+
	"inscribed on it.\n");
    add_item("chain", "The golden chain is firmly attached to the wall and " +
	"the poster.\n");
    add_prop(OBJ_M_NO_GET, "The poster is attached to the wall.\n");
}

int
check_write()
{
    object tp = TP;

    return !(RECRUITER_CODE->is_recruiter(tp->query_name()) ||
        COUNCIL_CODE->is_council_member(tp->query_name()) ||
        COUNCIL_CODE->is_calian_wiz(tp) || 
        SECURITY->query_wiz_rank(tp->query_real_name()) >= WIZ_ARCH);
}

int
change_poster(string str)
{
    string text;

    if (str != "poster" && str != "golden poster")
	return 0;

    if (check_write())
    {
	write("Your hand passes through the marker.\n");
	return 1;
    }

    text = read_file(query_file());
    clone_object("/std/edit")->edit("done_editing", text);
    return 1;
}

int
done_editing(string text)
{
    string filename;

    if (text == "")
    {
	write("The old message has been restored.\n");
	return 1;
    }
    filename = query_file();
    rm(filename);
    write_file(filename, text);
    return 1;
}

void
init()
{
    ::init();

    add_action("change_poster", "change");
}