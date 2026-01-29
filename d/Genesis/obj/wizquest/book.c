inherit "/std/object";

#include <std.h>
#include <macros.h>
#include <stdproperties.h>

string *signatures;

void
create_object()
{
    set_name("book");
    add_adj(({"heavy", "bound", "leather"}));

    set_long(
        "This book is lying open on the table.  The book is quite large,\n" + 
        "perhaps the length of your arm in height and but a third less in\n" + 
        "breadth.  The book shimmers with the magic that is so obviously\n" + 
        "bound up in its pages.\n\n");

    change_prop(OBJ_I_VOLUME, 10*50*30);
    change_prop(OBJ_I_WEIGHT, 2*10*50*30);
    change_prop(OBJ_M_NO_GET, 
        "A magical force resists your best efforts to get the book.\n");

    add_cmd_item("book", ({"sign", "read", "open", "close"}), 
        ({"@@sign_book", "@@read_book",
           "The book is already open.\n",
           "A magical force resists your best efforts to close the book.\n",
        }));
    if (file_size("/d/Genesis/obj/wizquest/signatures") >= 0)
    	restore_object("/d/Genesis/obj/wizquest/signatures");
}

string
sign_book()
{
    string who;

    who = this_player()->query_name();

    if (member_array(who, signatures) > 0)
        write("You have already signed the book!\n");
    else if (SECURITY->wizard_level(this_player()))
        write("As a wizard, you cannot sign this book!");
    else
    {
        write("You boldly sign your name.\n");
        signatures += ({ who });
        seteuid(getuid(this_object()));
        save_object("/d/Genesis/obj/wizquest/signatures");
    }
}

string
read_book()
{
    return("Inscribed in the book are the following names:\n" + 
        break_string(implode(signatures, ", "), 70));
}



erase_name(string who)
{
    signatures -= ({ who });
    seteuid(getuid(this_object()));
    save_object("/d/Genesis/obj/wizquest/signatures");
}
