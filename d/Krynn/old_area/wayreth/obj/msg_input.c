inherit "/std/object";

#include <macros.h>

string text = "";
int line = 1;
object book;

void
new_msg()
{
    book = previous_object();
    write("Enter message text. End with '**', list with '~l', " +
	"abort with '~q'.\n");
    write(line + ">>");
    input_to("get_msg");
}

void
get_msg(string str)
{
    if (str == "~q")
    {
	say(QCTNAME(this_player()) + " erases everything written.\n");
	write("Writing erased.\n");
	remove_object();
	return;
    }
    
    if (str == "~l")
    {
	write(text + "\n" + line + ">>");
	input_to("get_msg");
	return;
    }
    
    if (str == "**")
    {
	if (line == 1)
	{
	    write("No text entered. Writing discarded.\n");
	    say(QCTNAME(this_player()) + " quits writing.\n");
	    remove_object();
	    return;
	}
	say(QCTNAME(this_player()) + " has completed a book.\n");
	write("Ok.\n");
	book->set_tmp(text);
	remove_object();
	return;
    }

    text = text + str + "\n";
    line++;
    write(line + ">>");
    input_to("get_msg");
}
