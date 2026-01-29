inherit "/std/book";

#include "/d/Kalad/defs.h"
#include "/d/Kalad/common/guilds/khiraa/khiraa_defs.h"

mapping herb_map;
string *entries;

void load_herbmap();

void 
create_book()
{
    set_name("book");
    add_adj(({"black","iron-bound"}));
    set_short("black iron-bound book");

    set_long("This is a black, iron-bound book which rests on the "+
    "table here. It is chained to the floor with an iron chain. Upon "+
    "the cover, you read the title 'Khiraa herb transactions'.\n");

    add_prop(OBJ_M_NO_GET,"It is chained to the ground.\n");

    load_herbmap();

    set_max_pages(100);
}

void
load_herbmap()
{
    seteuid(getuid());
    herb_map = restore_map(KHIRAA_DIR(log/buy_log));
    if(!m_sizeof(herb_map))
    {
        entries = ({});
        return;
    }
    entries = m_indexes(herb_map);
}


void
read_book_at_page(int page, string verb)
{
    int i;
    string str;
    mapping herbs;
    string *herb_names;

    load_herbmap(); // update the logs

    if(page > sizeof(entries))
    {
        write("This page seems to be empty.\n");
        return;
    }
    if(page == 1)
    {
        write("This book contains my entries for the transactions with "+
        "the Khiraa. I have the following entries made in my book:\n");
        for(i=0;i<sizeof(entries);i++)
        {
            write(sprintf("%-20s - %s",entries[i],"Page "+(i+2)+"\n"));
        }
        return;
    }
    str = "The entry for "+entries[page - 2]+":\n";

    herbs = herb_map[entries[page - 2]];

    herb_names = m_indexes(herbs);

    for(i=0;i<sizeof(herb_names);i++)
    {
        str += herb_names[i]+" : "+herbs[herb_names[i]]+"\n";
    }
    str +=
    "Positive indicates the person has sold more than bought.\n"+
    "Negative indicates the person has bought more than sold.\n"+
    "Penned by The Fallen.\n";
    
    TP->more(str);
}
