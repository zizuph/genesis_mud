/*  rack_log_book.c
 *
 *  A rack lok
 *
 *  Created by Znagsnuf.
 *
 *  Date:                      What is done:                           By whom:            
 *  ---------------------------------------------------------------------------
 *  06/05-2017                Started making it.                       Znagsnuf
 *  29/05-2017                Made turnable pages                      Znagsnuf
 *  19/06-2017                Fixed a bug with the dates               Znagsnuf
 */

inherit "/std/scroll";

#include <time.h>
#include <stdproperties.h>
#include <cmdparse.h>
#include <macros.h>

int trim_book();
int turn_page(string str);
int return_page();

int page = 1;

string date = ("/d/Gondor/common/obj/clock")->query_date_s();

// The max size of the file.
int max_size = 30000;

string backup_file;
 
void
create_scroll()
{
    set_name("book");
    set_adj("massive");
    set_short("massive book");
    set_long("This log book is massive! It seems that the scribe records " +
        "the activity in the rack seen through the north window. If you " +
        "want to see a transcript of who has borrowed and donated " +
        "recently from those racks, just <read massive book>.\n");
    set_file("/d/Shire/guild/AA/log/new_rack_log");
    add_prop(OBJ_I_WEIGHT, 1000);
    add_prop(OBJ_I_VOLUME, 1000);
    add_prop(OBJ_I_VALUE, 0);
    add_prop(OBJ_M_NO_GET, "The massive book is chained to the wall.\n");
}

/*
 * Function name: init
 * Description  : Initialize commandverbs.
 */
public void
init()
{
    ::init();
    add_action(read_scroll, "read");
    add_action(turn_page, "turn");
}

int
return_page()
{
    if(!page)
    {
        set_file("/d/Shire/guild/AA/log/new_rack_log");
        page = 1;
        tell_room(environment(this_object()), "A sudden gust of wind turns a "
                           + "page in the " + this_object()->short() + ".\n");
    }    
}

int
turn_page(string str)
{

    notify_fail(capitalize(query_verb()) + " what?\n");
    if(!str)
        return 0;

    notify_fail(capitalize(query_verb()) + " page in which book?\n");
    if (!parse_command(str, ({ }), " [the] [page] [in] [massive] 'book' "))
        return 0;  

    if(page)
    {
        set_file("/d/Shire/guild/AA/log/new_rack_log.backup");
        page = 0;
    }
    else
    {
        set_file("/d/Shire/guild/AA/log/new_rack_log");
        page = 1;
    }    

    tell_object(this_player(), "You carefully turn a page in the " 
                + this_object()->short() + "\n");

    tell_room(environment(this_player()), QCTNAME(this_player()) + " turn "
                 + "a page in the " 
                 + this_object()->short() + ".\n", this_player());

    set_alarm(60.0, 0.0, &return_page());

    return 1;
}

int
trim_book()
{
    int f_size;
    string file_name, print, bottom_file = "";
    string top_file = "";     

    print = "";
    file_name = query_file();
    f_size = file_size(file_name);

    if (f_size > max_size)
    {
        date = ("/d/Gondor/common/obj/clock")->query_date_s();
        bottom_file = sprintf( 
"| |_________________________________________________________________________| |\n"+
"| |                                                                         | |\n"+    
"| | Penned by Gralme. Date: %-22s                          | | \n"+
"|_|_________________________________________________________________________|_|\n",
    date); 

        backup_file = file_name + ".backup";
        print += bottom_file;
        write_file(file_name, print);

        top_file =  sprintf(
" _ _________________________________________________________________________ _\n"+
"| |                                                                         | |\n"+
"| |                         ,..........   ..........,                       | |\n"+
"| |                     ,..,'          '.'          ',..,                   | |\n"+
"| |                    ,' ,'            :            ', ',                  | |\n"+
"| |                   ,' ,'   Angmar's  :    Army      , ',                 | |\n"+
"| |                  ,' ,'              :              ', ',                | |\n"+
"| |                 ,' ,'............., : ,.............', ',               | |\n"+
"| |                ,'  '............   '.'   ............'  ',              | |\n"+
"| |                 '''''''''''''''''';''';''''''''''''''''''               | |\n"+
"| |                                    '''                                  | |\n"+
"| |  Placed in rack:                  Item:             Borrowed from rack: | |\n"+
"| |-------------------------------------------------------------------------| |\n"+
"| | %-22s                                                  | | \n"+
"| | ----------------                                                        | | \n",
    date); 

        rename(file_name, backup_file);
        write_file(file_name, top_file);
        return 1;
    }
    return 1;
}
/*
 * Function name: read_scroll
 * Description  : This function is called when the player wants to read
 *                the scroll.
 * Arguments    : string str - the command line argument.
 * Returns      : int 1/0 - success/failure.
 */
static int
read_scroll(string str)
{
    string vb, file_name;
    object *a;
    int f_size;

    file_name = query_file();
    f_size = file_size(file_name);

    if (this_player()->query_prop(TEMP_STDREAD_CHECKED))
        return 0;

    vb = query_verb();
    notify_fail(capitalize(vb) + " what?\n", 0);
    if (!str)
    return 0;

    a = CMDPARSE_ONE_ITEM(str, "read_access", "read_access");
    if (sizeof(a) > 0)
    {
        a[0]->read_it(vb);
        if((f_size > max_size) && (file_name == "/d/Shire/guild/AA/log/new_rack_log"))
        {
            this_object()->trim_book();
        }
        return 1;
    }

    set_alarm(1.0, 0.0, &(this_player())->remove_prop(TEMP_STDREAD_CHECKED));
    this_player()->add_prop(TEMP_STDREAD_CHECKED, 1);
    return 0;
}