#pragma save_binary
#pragma strict_types

#include <stdproperties.h>
#include <macros.h>
#include <composite.h>
#include <cmdparse.h>
#include "../guild.h"

inherit SHIRE_ROOM;

#define SAVE_FILE  AA_DIR+"save_files/AA_LIBRARY"
#define BOOK_DIR   AA_DIR+"books/composed"
#define WRITER     "_aa_writer_"
#define BOOK_NAME  "_aa_book_"

#define BOOKS ({"book","scroll","papyrus","pamphlet", \
                "parchment","vellum","booklet" })
#define VERBS ({"write","record","formulate","compose","scribble",\
                "scrawl","scratch","draw","depict","design","draft",\
                "paint","sketch","score","outline" })

private mapping lib_books  = ([ ]);
/*
 *  lib_books = ([ name#i : ({ type, title, how }), ... ])
 */

static mapping types = ([ ]);
static mapping titles = ([ ]);
static mapping hows = ([ ]);

// prototypes
int tear_scroll(string str);
int make_scroll(string str);

object make_book(string fname)
{
    object book;
    FIXEUID;
    book = clone_object(AA_DIR+"books/scroll");
    book->set_file(BOOK_DIR+"/"+fname);
    book->remove_name("scroll");
    book->set_name(({ lib_books[fname][0], BOOK_NAME }));
    book->add_adj(lib_books[fname][2]);
    book->set_short(lib_books[fname][2]+" "+lib_books[fname][0]);
    book->set_long("This "+lib_books[fname][0]+" is "+lib_books[fname][2]+
        " by "+explode(fname,"#")[0]+" and has title:\n"+
        lib_books[fname][1]+"\n");
    book->add_prop(WRITER, fname);
    book->move(TO, 1);
    return book;
}

void make_books()
{
    string *arr = m_indexes(lib_books);
    int i;
    FIXEUID;
    for(i=0; i<sizeof(arr); i++)
        if(file_size(BOOK_DIR+"/"+arr[i]) != -1)
            set_alarm(0.0, 0.0, &make_book(arr[i]));
        else
            lib_books = m_delete(lib_books, arr[i]);
    save_object(SAVE_FILE);   
}

int block_exit()
{
    if(present(BOOK_NAME, TP))
    {
        write("First drop everything that belongs to the library!\n");
        return 1;
    }
    return 0;
}

string sign()
{
    return "\n           WELCOME TO THE LIBRARY!\n\n"+
        "You can freely take and read or mread anything you may find lying "+
        "around here. You are also encouradged to put your experiences, "+
        "stories, songs, maps (or anything else you may think of) into "+
        "a solid form so that future generations of soldiers may benefit and "+
        "enjoy it as well. If you wish to do so you just have to 'write book'. "+
        "Well actually there are little bit more possibilities to suit "+
        "everyone and every purpose (we know our goblin brothers have little "+
        "problems with 'writing'). Hence you can replace 'write' above with "+
        "anything from:\n"+COMPOSITE_WORDS(VERBS)+"\n\nand also replace 'book' "+
        "above with anything from:\n"+COMPOSITE_WORDS(BOOKS)+"\n\n"+
        "In case you happen to dislike what you have created you can 'tear' it "+
        "and start again. Captain can tear any of your books. Enjoy!\n"+
        "\n           PLEASE RETURN EVERYTHING BACK BEFORE LEAVING!\n";
}

string list()
{
    string s, *arr = m_indexes(lib_books);
    int i;
    
    s = " Type:                 Author:       Title:\n"+
        "-------------------------------------------------------\n";
    for(i=0; i<sizeof(arr); i++)
        s += sprintf(" %-21s %-13s %-41s\n",
                    lib_books[arr[i]][2]+" "+lib_books[arr[i]][0],
                    explode(arr[i],"#")[0],
                    lib_books[arr[i]][1]);
    return s;
}

void create_shire_room()
{
    set_short("library room");
    set_long("Library of Angmar's army... Well, it does not look like a real "+
        "library because it is quite small and there are no shelves "+
        "for keeping books in. The only things you see on the wall is "+
        "a sign and a list. Everything else must be simply stored on "+
        "the floor.\n");
    
    add_prop(ROOM_I_INSIDE,1);  /* This is a real room */
    
    add_item("sign", "It is quite plain with some instructions on it.\n");
    add_cmd_item("sign", "read", &sign());
    add_item("list", "It contains list of books.\n");
    add_cmd_item("list", "read", &list());
    
    add_exit(AA_DIR+"rooms/vote", "west", &block_exit());
    
    FIXEUID;
    restore_object(SAVE_FILE);
    make_books();
}

void init()
{
    int i;
    ::init();
    for(i=0; i<sizeof(VERBS); i++)
        add_action(make_scroll,VERBS[i]);
    add_action(tear_scroll,"tear");
}

int tear_scroll(string str)
{
    object *a;
    string fname, name = TP->query_name();
    NF("Tear what?\n");
    if(!str) return 0;
    a = CMDPARSE_ONE_ITEM(str, "tear_access", "tear_access");
    if (sizeof(a) == 0) return 0;
    fname = a[0]->query_prop(WRITER);
    if (fname && (explode(fname,"#")[0] == name || AA_RANKS_OBJ->is_captain(name) ))
    {
        FIXEUID;
        rm(BOOK_DIR+"/"+fname);
        lib_books = m_delete(lib_books, fname);
        save_object(SAVE_FILE);
        write("You tear the "+a[0]->short()+" to the small pieces.\n");
        say(QCTNAME(TP)+" tears the "+a[0]->short()+" to the small pieces.\n");
        a[0]->remove_object();
        return 1;
    }
    NF("You can't tear "+a[0]->short()+".\n");
    return 0;
}

int tear_access(object ob)
{
    if((ENV(ob) == TP) && (function_exists("create_object", ob) == "/std/scroll"))
        return 1;
    else
        return 0;
}

int make_scroll(string str)
{
    string verb = query_verb();
    string name = TP->query_name();
    int i;
    if(member_array(str, BOOKS) == -1)
    {
        NF(CAP(verb)+" what?\n");
        return 0;
    }
    write("You take an empty "+str+" and start to "+verb+" in it.\n");
    say(QCTNAME(TP)+" takes an empty "+str+" and starts to "+verb+" in it.\n");
    i = strlen(verb)-1;
    if(verb == "draw") hows[TP] = "drawn";
    else if(verb == "write") hows[TP] = "written";
    else if(verb[i..i] == "e") hows[TP] = verb+"d";
    else hows[TP] = verb+"ed";
    types[TP] = str;
    write("First "+verb+" the title of "+str+" (max 40 characters).\nTitle: ");
    input_to("get_title");
    return 1;
}

void get_title(string str)
{
    if(!strlen(str))
    {
        write("No title selected. Aborting.\n");
        types = m_delete(types, TP);
        hows = m_delete(hows, TP);
        return;
    }
    if(strlen(str) > 40)
    {
        write("Title can be at most 40 characters long. Try again.\nTitle: ");
        input_to("get_title");
        return;
    }
    titles[TP] = str;
    write("You choosed title:\n'"+str+"'\n");
    write("Please type one of c/r/a to confirm/rewrite/abort: ");
    input_to("confirm_title");
    return;
}

void confirm_title(string str)
{
    if(member_array(str, ({"c","r","a"})) == -1)
    {
        write("Please type one of c/r/a to confirm/rewrite/abort: ");
        input_to("confirm_title");
        return;
    }
    
    if(str == "a")
    {
        types = m_delete(types, TP);
        titles = m_delete(titles, TP);
        hows = m_delete(hows, TP);
    }
    if(str == "r"){ write("Title: "); input_to("get_title"); return; }
    
    if(member_array(TP, m_indexes(titles)) == -1)
    {
        write("You have not selected any title. Aborting.\n");
        return;
    }
    write("Now the "+types[TP]+" itself...\n");
    
    FIXEUID;
    clone_object("/obj/edit")->edit("done_editing", "");
}

/*
 * Function name: done_editing
 * Description  : When the player is done editing the book, this function
 *                will be called with the text as parameter.
 * Arguments    : string text - the text typed by the player.
 * Returns      : int - 1/0 - true if the note was added.
 */
public int done_editing(string text)
{
    string fname, name = TP->query_name();
    int i;
    if (!strlen(text))
    {
        write("No text entered. Aborting.\n");
        types = m_delete(types, TP);
        titles = m_delete(titles, TP);
        hows = m_delete(hows, TP);
        return 0;
    }
    if (!strlen(titles[TP]))
    {
        write("Missing title... Bug.\n");
        types = m_delete(types, TP);
        titles = m_delete(titles, TP);
        hows = m_delete(hows, TP);
        return 0;
    }
    FIXEUID;
    if(file_size(BOOK_DIR) == -1) mkdir(BOOK_DIR);
    i = 1;
    fname = name+"#"+i;
    for(i=1; file_size(BOOK_DIR+"/"+fname) != -1; i++)
        fname = name+"#"+i;
    write_file(BOOK_DIR+"/"+fname, "\n"+titles[TP]+"\n");
    write_file(BOOK_DIR+"/"+fname, hows[TP]+" by "+name+"\n\n");
    write_file(BOOK_DIR+"/"+fname, text);
    lib_books[fname] = ({ types[TP], titles[TP], hows[TP] });
    save_object(SAVE_FILE);
    make_book(fname);
    say(QCTNAME(TP)+" has completed a "+types[TP]+" titled:\n "+titles[TP]+"\n");
    write("You have completed a "+types[TP]+" titled:\n "+titles[TP]+"\n");
    return 1;
}
