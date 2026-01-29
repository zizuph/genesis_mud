/*
 *  /doc/examples/guild_library/advanced/library_scroll.c
 * 
 *  Custom book for use in the advanced example of the guild library.
 *
 *  Created by Eowul, May 10th, 2009
 */
 
inherit "/std/guild_library_book";

public void create_library_book()
{
    string *adjs = ({ "weathered", "dusty", "faded"});
    string adj = adjs[random(sizeof(adjs))];

    add_adj(adj);
    set_name("book");
    set_pname("books");
    set_short(adj + " book");
    set_long("The " + adj + " cover is made of leather and full of " +
        "blank parchment pages.\n");
}

/*
 * Function name: read_it
 * Description:   Perform the actual read
 */
void
read_it(string answer)
{
    // Read from file if no text is set, otherwise, display the text
    if(strlen(filename))   
    {
        ::read_it(answer);
        return;
    }

    if(!strlen(text))
    {
        write("The book is empty.\n");
    }
    else
    {
        // No more for now
        this_player()->more(text, 0);
    }
}
