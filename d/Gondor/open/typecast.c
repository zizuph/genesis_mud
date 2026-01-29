/*
Every function returns a value.
Let's look at an example:
 */
inherit "/d/Gondor/common/room";

#include <macros.h>

#include "/d/Gondor/defs.h"

// templates
string read_poster();

/*
 * create_room() does not return any value, so the type is 'void'
 */
void
create_room()
{
    set_short("dummy room");
    set_long("A dummy room.\n");

    // I want to add a poster to the room.
    // One should be able to look at the poster and to read it.
    // Since the contents of the poster are fixed, I do not need a VBFC
    // here!
    // The function 'read_poster()' has to return a string.
    // I will define the function further down in the file, so I have to
    // use the template above.
    add_item(({"poster"}), read_poster() );
    add_cmd_item(({"poster"}), "read", read_poster());
}

/*
 * init() does not return any value, so the type is 'void'
 */
void
init()
{
    ::init();    // always call to ::init();

    // I add the action 'sing' to the room.
    // Note that function which exectue actions added with add_action 
    // are always of the type 'int'. If they return '0', the action is
    // assumed to have failed, else it is assumed that the action succeeded.
    // If several object define an action using the same verb ('sing'),
    // one function after the other is tested. If one function returns
    // '1' (= success), the evaluation ends. If a function returns '0',
    // the next function is tested. If no function returns '1', the
    // message that was last set using notify_fail() is printed.
    add_action("do_sing", "sing");
}

int
do_sing(string str)
{
    // The player typed 'sing' w/o argument.
    if (!strlen(str))
    {
        notify_fail("Sing what?\n");
        return 0;
    }

    if (str == "song")
    {
        write("You sing a song.\n");
        say(QCTNAME(this_player()) + " sings a song.\n");
    // Success!
        return 1;
    }

    // If the argument was not 'song', then the function fails, too.
    notify_fail("You do not know that song!\n");
    return 0;
}

string
read_poster()
{
    return "You read the poster:\n"
      + "\t\tTO WHOM IT MAY CONCERN!\n"
      + break_string(
        "It is required that wizards in the domain Gondor typecast "
      + "all functions of their code! For a short example with some "
      + "explanations, read the file for this room!\n",
        50, "\t");
}

/*
Whatever you put behind the return is what the function returns.
That value can be an integer, a float, a string, an object, an array
of string, etc or it can be nothing at all when there is no return
statement or is the return statement is just: 'return;'.
In that case, the function has the type 'void'.
Now the gd would like to know what the function returns. You can tell
it by typing: 'void create_room()', for example, or 'int do_read(string str)'.

The advantage is twofold:
If you make a mistake, like you actually return a string, but another
function expects an integer, you'll get an error message when you compile
the file. If you do not typecast, you will either get no error message
or you won't get it before the function is actually executed.

The other advantage is that a function that is not typecast is assumed to be
of type 'mixed'. 'mixed' can be everything, so the gd has to compile the
function so that just about every type of variable can be returned.
Also, if a value is returned, the gd has to check the type of the value.
If you tell the gd what type to expect, it has less to do and compiling
is faster, and the compiled object most probably takes less memory,
_especially_ if the function actually is of type void.

I know that most old code in the domain is not typecasted, but all new
code should be typecasted.

There are only two things to keep in mind:

1) Decide which type of variable you would like to return.
2) If you typecast your functions, the gd makes more extensive checking
when compiling your code than for code that is not typecasted. That
requires that a function which you call in your code has to be declared
_before_ you call it.

You can do that in either of two ways:
Either you actually define your function before it is called or you use
so called 'templates'. A 'template' is just the head of a function which
you put at the top of your file; an example:
string read_poster();
Note the ';' at the end of that line, a 'template' is a full statement,
so it has to be terminated by a ';'.
 */


