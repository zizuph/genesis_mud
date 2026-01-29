/* Elder tablet. To make it easier to communicate w/o 
 * relying on crowded mailboxes
 */
#pragma strict_types
#pragma save_binary

inherit "/std/board";

#include <std.h>
#include <macros.h>
#include <language.h>
#include <stdproperties.h>

#include "../defs.h"

#define MIN_HEADER_LENGTH   1
#define MAX_HEADER_LENGTH  50
#define MIN_NAME_LENGTH     2
#define MAX_NAME_LENGTH    11
#define AUTHOR_BEGIN       46
#define AUTHOR_END         56

string *styles  = ({ "leather", "suede", "wooden", "black", "grey", "dark" });
string style;
public void set_style(string str)    {    style = str;     }

string 
my_long()
{
    string str;

    if(IS_MEMBER(TP))
	str ="This folio can hold a great many notes, up to "+
	"a hundred pages. It works rather a lot like a board "+
	"does, and can be used to store mails and notes to "+
	"yourself and to other Elders. If this folio gets "+
	"into the wrong hands, do not fear, for it will fade "+
	"away into nothingness.\n";
    else 
	str ="It is an odd folio.\n";
    return str;
}   

void 
create_board()
{
    int s;
    s = (random(sizeof(styles)));
    style = (styles[s]);

    set_board_name(GUILDLOG +"elder_b");
    set_num_notes(99);
    set_silent(1);
    set_show_lvl(0);
    set_keep_discarded(1);
    set_no_report(1);
    set_remove_rank(0);
    set_remove_str("You are not permitted.\n");
    remove_name("board");
    set_name("folio");
    add_name("av_e_folio");
    set_adj(style);
    set_adj("elder");
    set_short(style +" folio");
    set_long(VBFC_ME("my_long"));
    remove_prop(OBJ_M_NO_GET);
    add_prop(OBJ_I_VOLUME, 100);
    add_prop(OBJ_I_WEIGHT, 100);

}


/*
 * Function name: reset_board
 * Description  : Since reset_object() is nomasked, you must mask this
 *                function at reset time. Enable_reset() is already
 *                called, so you do not have to do that yourself.
 */
void
reset_board()
{
}

int block_reader()
{
    object tp;
    string name;
    tp = this_player();
    name = tp->query_real_name();

    if(!IS_ELDER(TP) && !IS_GMASTER(TP))
    {
	if (environment(tp) == environment(TO))
	    write("You are not permitted to view this.\n");
	return 1;
    }

    return 0;
}

int block_writer()
{
    return block_reader();
}

int allow_remove()
{ 
    if(IS_ELDER(TP))
    {
	if(present(TP, ENV(TO))) // present is for mbs support
	    write("Since you are an Elder, you may remove the note.\n");
	return 1; 
    }

    if(SECURITY->query_wiz_dom(TP->query_real_name()) == "Avenir")
	return 1;

    return 0;
}

void 
dust()
{
    object where = ENV(TO);
    string msg = CAP(LANG_THESHORT(TO))+" vanishes!\n";

    if(living(where))
	where->catch_msg(msg);
    else
	tell_room(ENV(TO), msg);

    remove_object();
}

// Don't want wrong people getting it, but also want it to be
// able to be put in packs and such.
void 
enter_env(object to, object from)
{
    object *obs;
    int i;

    ::enter_env(to, from);

    //If dropped in a room, dust it.
    if (to->query_prop(ROOM_I_IS))
	set_alarm(1.0, 0.0, dust);

    // If wrong living gets it, dust it
    if (living(to))
    {
	if(!IS_ELDER(to) && !IS_GMASTER(to))
	    set_alarm(1.0, 0.0, dust);            
    }

    /* Only ever one at a time in a person's inventory */ 
    obs = all_inventory(to);
    for (i = 0; i < sizeof(obs); i++)
    {
	if (obs[i]->id("av_e_folio") && obs[i] != this_object())
	{
	    obs[i]->remove_object();
	}
    }

}

string 
query_recover()
{
    return 0;
}

string
query_auto_load()
{
    if(!IS_GMASTER(TP))
	return MASTER;
}
