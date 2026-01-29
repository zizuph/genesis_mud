/* 
 * /d/Kalad/common/guilds/khiraa/temple/obj/join_book.c
 * Purpose    : This is the join book of the Khiraa.
 * Located    : ~khiraa/temple/rooms/temple_join
 * Created By : Sarr 07.Apr.97
 * Modified By: Toby, 970919 (fixed typos and refrazed a little in page 4)
 */ 

inherit "/std/book";
#include "/d/Kalad/defs.h"
#include "/d/Kalad/common/guilds/khiraa/khiraa_defs.h"

mapping circle_ma;


void 
create_book()
{
    set_name("book");
    add_adj("mysterious");
    set_short("mysterious book upon a black wooden stand");
    set_long("This is a mysterious black book covered with blood-red "+
    "runes. It rests upon a black wooden stand.\n");
    add_item(({"black wooden stand","wooden stand","black stand","stand"}),
    "A short wooden stand that rests firmly on the ground. Its top "+
    "opens up like a small table, upon which rests a mysterious book.\n");
    add_prop(OBJ_M_NO_GET,"It is firmly stuck in the ground.\n");
    set_max_pages(8);
}

void
read_book_at_page(int page, string verb)
{
    int *indxs,i;
    string file,*names;
    string circle_master;
    string grand_master;
    string circle_members = "";
    circle_ma = ([]);
    seteuid(getuid());
    circle_ma = restore_map(KHIRAA_DIR(log/circle_master));
    indxs = m_values(circle_ma);
    names = m_indexes(circle_ma);
    for(i=0;i<sizeof(indxs);i++)
    {
        if(indxs[i] == 1)
            circle_members += C(names[i])+"\n";
        if(indxs[i] == 2)
            circle_master = C(names[i])+"\n";
        if(indxs[i] == 3)
            grand_master = C(names[i])+"\n";
    }        
    if(!stringp(circle_members))
        circle_members = "None.\n";
    if(!stringp(circle_master))
        circle_master = "None.\n";
    if(!stringp(grand_master))
        grand_master = "None.\n";
  

    if(page == 1)
    {
        file = read_file(KHIRAA_DIR(temple/obj/join_book_cont));
        TP->more(file,0);
    }
    if(page == 2)
    {
        file = read_file(KHIRAA_DIR(temple/obj/join_book_khiraa));
        TP->more(file,0);
    }
    if(page == 3)
    {
        file = read_file(KHIRAA_DIR(temple/obj/join_book_dk));
        TP->more(file,0);
    }
    if(page == 4)
    {
        file = read_file(KHIRAA_DIR(temple/obj/join_book_lp));
        TP->more(file,0);
    }
    if(page == 5)
    {
        file = read_file(KHIRAA_DIR(temple/obj/join_book_rules));
        TP->more(file,0);
    }
    if(page == 6)
    {
        file = read_file(KHIRAA_DIR(temple/obj/join_book_join));
        TP->more(file,0);
    }
    if(page == 7)
    {
        file = read_file(KHIRAA_DIR(temple/obj/join_book_app));
        TP->more(file,0);
    }
    if(page == 8)
    {
        write("Sorry, the guild has been closed for good. You cannot join.\n");
    }
}
