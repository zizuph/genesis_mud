/*
 *  /d/Gondor/warfare/obj/ideabook.c
 *
 *  Book containing the collection of thoughts on the warfare
 *  system, so that mortals can easily read the various topics
 *  that interest them.
 *
 *  Created by Eowul, June 14th, 2009
 */
 
#include <stdproperties.h>

inherit "/std/book";

string *pages;

#define TEXT_DIR "/d/Gondor/warfare/obj/ideabook/"

public void create_book() {
    add_name("tome");
    set_adj(({"important", "looking"}));
    set_short("important looking tome");
    set_long("This important looking tome contains a collection of " 
        + "ideas and plans for what will one day form the war system "
        + "of Middle Earth.\n");
    
    add_prop(OBJ_I_NO_GET, 1);    
    
    pages = ({ 
        TEXT_DIR + "00_introduction.txt",
        TEXT_DIR + "01_index.txt",
        TEXT_DIR + "02_main_concept.txt",
        TEXT_DIR + "03_playerkilling.txt",
        TEXT_DIR + "04_questions.txt",
        TEXT_DIR + "05_assistance.txt"
    });
    
    set_max_pages(sizeof(pages));
}

varargs void read_book_at_page(int which, string verb)
{ 
    string filename = pages[which - 1];
    setuid();
    seteuid(getuid());
    this_player()->more(read_file(filename, 1));
}

