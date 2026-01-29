/* 	A generic log book

    coder(s):   Maniac, Glykron
    history:
                13. 4.94      Created                         Maniac
                30. 6.94      Modified for inheritance        Glykron

    quests:     none
    special:    none

    to do:      none
    bug:        none known
*/

#pragma save_binary

inherit "/std/scroll";

static int max_size;

void
set_max_size(int new_max_size)
{
    max_size = new_max_size;
}

void
create_log_book()
{
}

void
create_scroll()
{
    create_log_book();
}

void
read_it(string str)
{
    ::read_it("mread");
}

/* This code maintains the log book by updating the file
   and, when necessary, trimming the file size by losing the first 
   entry.  By Maniac */

int
update_log_book(string new_line)
{
    string text_file,
	whole_file_string, first_line_of_file, rest_of_file, new_file_string;
    int size;

    text_file = query_file();
    whole_file_string = read_file(text_file);
    size = file_size(text_file);
    if (size > max_size)
    {
        sscanf(whole_file_string, "%s\n%s", first_line_of_file, rest_of_file);
        new_file_string = rest_of_file + new_line;
    }
    else
        new_file_string = whole_file_string + new_line;

    rm(text_file);
    write_file(text_file, new_file_string);
    return 1;
}