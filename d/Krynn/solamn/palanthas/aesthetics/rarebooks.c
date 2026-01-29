/* 
 * Abandoned Scroll Trade Guilde.
 * 
 */

#include "../local.h"
#include "/d/Krynn/common/defs.h"
#include CLOCKH
#include <macros.h>
#include <ss_types.h>
#include <cmdparse.h>
#include <stdproperties.h>

inherit MONKS_ROOMBASE;

int buttons_pressed = 0;
int random_order = random(3);
int compartment_found = 0;

string * order_0 = ({"red burl","yellow burl","brown burl"});
string * order_1 = ({"yellow burl","red burl","brown burl"});
string * order_2 = ({"brown burl","yellow burl","red burl"});

#define FOUND_BURL   "_palanthas_found_burls" 
#define JOURNAL  "/d/Krynn/solamn/palanthas/aesthetics/obj/battered_journal"

void
reset_palan_room()
{
    if(compartment_found)
        compartment_found = 0;
}

void
create_palan_room()
{
    SHORT("an abandoned book store");
    LONG("You stand within a small abandoned book store, its floor space " +
        "covered with a chaotic maze of dusty and cobwebbed bookshelves. " +
        "Near the exit of the store is an old shadowy counter, where " +
        "business may have once been conducted.\n");

    ITEM(({"store","book store","abandoned book store"}),
        "You stand with what was once a book store, now long abandoned " +
        "and ransacked of anything valuable by looks.\n");
    ITEM(({"floor space","space","floor","shadows","maze"}),
        "The floor of the book store is covered with a maze of chaotically-" +
        "organised bookshelves, largely empty and covered with dust and " +
        "cobwebs.\n");
    ITEM(({"bookshelves", "bookshelf","cobwebbed bookshelves","shelves"}),
        "Bookshelves have been placed chaotically across the floor of the " +
        "store, creating a confusing maze of sorts. These bookshelves are " +
        "empty, with the exception of dust and cobwebs, having long ago " +
        "been ransacked of anything of value.\n");
    ITEM(({"books","book","tomes","tome"}),
        "Long abandoned and ransacked, no books remain in this store.\n");
    ITEM(({"darkened doorway","doorway"}),
        "A darkened doorway to your northwest is the only exit out of " +
        "this abandoned book store.\n");
    ITEM(({"counter","shadowy counter","old shadowy counter","sales counter"}),
        "Near the exit of the store is a sales counter of heavy oak. While " +
        "covered in dust, the grain of the wooden counter swirls with " +
        "chaotic burls that twist and interlock - a type of wood that is " +
        "rare in its beauty and highly prized by woodturners - and of " +
        "considerable value.\n");
    ITEM(({"burls","chaotic burls","grain"}),
        "@@exa_burls"); 
    ITEM(({"circular burl","circular deep red burl","deep red burl",
        "red burl"}),"@@exa_red_burl");
    ITEM(({"triangular burl","triangular golden yellow burl",
        "golden yellow burl","yellow burl"}), "@@exa_yellow_burl");
    ITEM(({"leaf-like brown burl","brown burl","leaf-like burl",
        "leaf burl"}), "@@exa_leaf_burl");
    ITEM(({"secret compartment","compartment"}),
        "@@exa_compartment");

    EXIT(MONKS + "a24", "northwest", "@@leave_store", 0);
	
    reset_palan_room();
}

string
exa_compartment()
{
    if(compartment_found)
    {
        return "Slightly underneath the counter you notice a secret " +
            "compartment, now unlocked and hanging empty.\n";
    }
    else
        return "Examine what?\n";
}

string
exa_burls()
{
    if(TP->query_skill(SS_AWARENESS) > 29)
    {
        TP->add_prop(FOUND_BURL, 1);
        return "The grain of the wooden counter has burls that swirl " +
            "chaotically across the table like turbulent waves. Three " +
            "burls of differing colours on the edge of the counter " +
            "catch your eye - a circular deep red burl, a triangular " +
            "golden yellow burl, and a leaf-like brown burl.\n";
    }
    else
        return "The grain of the wooden counter has burls that swirl " +
            "chaotically across the table like turbulent waves.\n";
}

string
exa_red_burl()
{
    if(!TP->query_prop(FOUND_BURL))
        return "Examine what?\n";
    else
    {
        say(QCTNAME(TP)+ " lowers " +HIM(TP)+ "self down to look at the " +
            "counter closely.\n");
        return "This circular deep red burl reminds you of a whirlpool " +
            "that progressively gets darker towards the centre where it " +
            "is almost black. Looking at it closely, you realise it is an " +
            "ingenious button! You could probably press it.\n";
    }
}

string
exa_leaf_burl()
{
    if(!TP->query_prop(FOUND_BURL))
        return "Examine what?\n";
    else
    {
        say(QCTNAME(TP)+ " lowers " +HIM(TP)+ "self down to look at the " +
            "counter closely.\n");
        return "This burl is curls like a spring leaf and is deep brown " +
            "in colour. Looking at it closely, you realise " +
            "it is an ingenious button! You could probably press it.\n";
    }
}

string
exa_yellow_burl()
{
    if(!TP->query_prop(FOUND_BURL))
        return "Examine what?\n";
    else
    {
        say(QCTNAME(TP)+ " lowers " +HIM(TP)+ "self down to look at the " +
            "counter closely.\n");
        return "This curious burl is triangular in shape and a beautiful " +
            "golden-yellow in colour. Looking at it closely, you realise " +
            "it is an ingenious button! You could probably press it.\n";
    }
}

int
leave_store()
{
    write("You push through the darkened doorway and exit the abandoned " +
        "book store.\n");
    return 0;
}

void
init()
{
	::init();
	ADA("press");
}

int
press(string str)
{
    string burl;
    string * order;
    string fail_message = ".";

    if(!random_order)
        order = order_0;
    else if(random_order == 1)
        order = order_1;
    else
        order = order_2;

    if (!str || !TP->query_prop(FOUND_BURL))
    {
        notify_fail("Press what?\n"); 
	return 0;
    }

    if (parse_command(str, environment(TP), 
        "[the] [circular] [triangular] [deep] [leaf-like] %s", burl))
    {
        if(!TP->query_prop(FOUND_BURL))
        {
            write("Press what?\n");
            return 1;
        }
       
        if(order[buttons_pressed] == burl)
        {
            if(compartment_found)
            {
                write("The " +burl+ " looks like it has already been " +
                    "depressed. It looks like someone has " +
                    "activated this button recently.\n");
                return 1;
            }

            if(buttons_pressed == 2)
            {
                write("You press down on the " +burl+ " and it locks in " +
                    "to a depressed state with a 'click'. The sound of cogs " +
                    "spinning within the counter begin, and suddenly " +
                    "a secret compartment opens up and drops a " +
                    "battered journal on to the floor!\n");
                say("You hear a 'click' as " +QTNAME(TP)+ " presses something " +
                "on the counter, followed by a whirl of cogs. A battered " +
                "journal suddenly drops from a secret compartment to the " +
                "floor!\n");
                buttons_pressed = 0;
                random_order = random(3);
                compartment_found = 1;
                clone_object(JOURNAL)->move(TO, 1);
                return 1;
            }
            write("You press down on the " +burl+ " on the counter and " +
                "it locks in to a depressed state with a 'click'.\n");
            say("You hear a 'click' as " +QTNAME(TP)+ " presses something " +
                "on the counter.\n");
            buttons_pressed += 1;
            return 1;
        }
        else if(burl == "red burl" || burl == "yellow burl" ||
            burl == "brown burl")
        {
            if(compartment_found)
            {
                write("The " +burl+ " looks like it has already been " +
                    "depressed. It looks like someone has " +
                    "activated this button recently.\n");
                return 1;
            }

            if(buttons_pressed > 0)
                fail_message = ", along with the other depressed " +
                    "burl.";

            write("You press down on the " +burl+ " on the counter and it " +
                "clicks down briefly before popping back up" +fail_message+ 
                "\n");
            say(QCTNAME(TP)+ " presses something on the counter.\n");

            buttons_pressed = 0;
            return 1;
        }
    }

    write("You can't find " +str+ " to press.\n");
    return 1;
}

