/*
 * /d/Faerun/guilds/vampires/obj/elder_book
 *
 * Nerull 2017
 */

inherit "/std/book";
#include "../../guild.h"
#include <composite.h>
#include <formulas.h>
#include <macros.h>
#include <stdproperties.h>
#include <cmdparse.h>


void
create_book()
{
    setuid();
    seteuid(getuid());

    set_name("binding");
    add_name("book");
    add_name("_elder_binding");
    set_adj("large");
    add_adj("red");
    add_adj("leather");

    set_short("large red leather binding on a simple iron book stand");

    set_long("This is a large binding of red cured leather. You notice it "
    +"contains a few pages. It "
    +"sits on top of a simple iron book stand.\n");
    
    add_item(({"stand", "book stand", "simple stand", 
    "simple iron book stand", "simple book stand", 
    "iron stand", "iron book stand"}),
    "The symbol on the leather binding is yellow on a black "
    +"background, and resembles a weird yellow triskelion. You "
    +"feel rather weird by looking at it.\n");

    add_prop(OBJ_M_NO_BUY, 1);
    add_prop(OBJ_M_NO_SELL, 1);
    
    add_prop(OBJ_I_NO_GET,"Uhm, no...you don't dare to.\n");
    
    add_prop(OBJ_I_NO_STEAL,"Uhm, no...you don't dare to.\n");

    set_max_pages(6);
}


void
read_book_at_page(int page, string verb)
{
    if (VAMPIRES_MASTER->is_occ_vampires(this_player()->query_name()) == 0)
    {
        write("As you merely think about approach the large red "
        +"leather binding, a whisper in your head suddenly echoes: 'No!'\n");  
        
        return;
    }
    
    if (VAMPIRES_MAPPINGS->query_vampires_gauge(this_player()->query_name()) < 13001);
    {
        write("As you merely think about approach the large red "
        +"leather binding, a whisper in your head suddenly echoes: 'No!'\n");  
        
        return;
    }
    
    if (VAMPIRES_MAPPINGS->query_vampire_reputation(this_player()->query_name()) < 40)
    {
        write("As you merely think about approach the large red "
        +"leather binding, a whisper in your head suddenly echoes: 'No!'\n");  
        
        return;
    }
    
    if (VAMPIRES_MAPPINGS->query_vampire_pathprogression(this_player()->query_name()) < 40)
    {
        write("As you merely think about approach the large red "
        +"leather binding, a whisper in your head suddenly echoes: 'No!'\n");  
       
       return;
    }
    
    if (VAMPIRES_MASTER->is_vamp_progenitor(this_player()->query_name()))
    {
        write("As you merely think about approach the large red "
        +"leather binding, a whisper in your head suddenly echoes: 'No!'\n");  
        
        return;
    }
    
    if (VAMPIRES_MASTER->is_vamp_antediluvian(this_player()->query_name()))
    {
        write("As you merely think about approach the large red "
        +"leather binding, a whisper in your head suddenly echoes: 'No!'\n");  
        
        return;
    }
    
    if (VAMPIRES_MASTER->is_vamp_methuselah(this_player()->query_name()))
    {
        write("As you merely think about approach the large red "
        +"leather binding, a whisper in your head suddenly echoes: 'No!'\n");  
        
        return;
    }
    
    if (VAMPIRES_MASTER->is_vamp_elder(this_player()->query_name()))
    {
        write("As you merely think about approach the large red "
        +"leather binding, a whisper in your head suddenly echoes: 'No!'\n");  
        
        return;
    }

    int factor1 = VAMPIRES_MAPPINGS->query_vampire_main_special(this_player()->query_name());
    int factor2 = VAMPIRES_MAPPINGS->query_weaponskill_selection(this_player()->query_name());
    
    if {factor2 > 3)
    {
        factor2 = 3;
    }
    
    int factor3 = VAMPIRES_MAPPINGS->query_vampires_rank(this_player()->query_name());
    
    if {factor3 > 3)
    {
        factor3 = 3;
    }
               
    //if (VAMPIRES_MASTER->elder_check() < 4)
    //{   
    // 27 possible puzzles
    if (page == 1)
    {
        if (factor1 == 1)
        {
            if (factor2 == 1)
            {
                switch(factor3)
                {
                    case 1:
                    this_player()->more(read_file(VAMPIRES_GUILD_DIR +
                    "obj/page1-1-1.txt",0));
                    break;
                    
                    case 2:
                    this_player()->more(read_file(VAMPIRES_GUILD_DIR +
                    "obj/page1-1-2.txt",0));
                    break;
                    
                    case 3:
                    this_player()->more(read_file(VAMPIRES_GUILD_DIR +
                    "obj/page1-1-3.txt",0));
                    break;
                }
            }
            
            
            if (factor2 == 2)
            {
                switch(factor3)
                {
                    case 1:
                    this_player()->more(read_file(VAMPIRES_GUILD_DIR +
                    "obj/page1-2-1.txt",0));
                    break;
                    
                    case 2:
                    this_player()->more(read_file(VAMPIRES_GUILD_DIR +
                    "obj/page1-2-2.txt",0));
                    break;
                    
                    case 3:
                    this_player()->more(read_file(VAMPIRES_GUILD_DIR +
                    "obj/page1-2-3.txt",0));
                    break;
                }
            }
            
            
            if (factor2 == 3)
            {
                switch(factor3)
                {
                    case 1:
                    this_player()->more(read_file(VAMPIRES_GUILD_DIR +
                    "obj/page1-3-1.txt",0));
                    break;
                    
                    case 2:
                    this_player()->more(read_file(VAMPIRES_GUILD_DIR +
                    "obj/page1-3-2.txt",0));
                    break;
                    
                    case 3:
                    this_player()->more(read_file(VAMPIRES_GUILD_DIR +
                    "obj/page1-3-3.txt",0));
                    break;
                }
            }
        }
        
        if (factor1 == 2)
        {
            if (factor2 == 1)
            {
                switch(factor3)
                {
                    case 1:
                    this_player()->more(read_file(VAMPIRES_GUILD_DIR +
                    "obj/page2-1-1.txt",0));
                    break;
                    
                    case 2:
                    this_player()->more(read_file(VAMPIRES_GUILD_DIR +
                    "obj/page2-1-2.txt",0));
                    break;
                    
                    case 3:
                    this_player()->more(read_file(VAMPIRES_GUILD_DIR +
                    "obj/page2-1-3.txt",0));
                    break;
                }
            }
            
            
            if (factor2 == 2)
            {
                switch(factor3)
                {
                    case 1:
                    this_player()->more(read_file(VAMPIRES_GUILD_DIR +
                    "obj/page2-2-1.txt",0));
                    break;
                    
                    case 2:
                    this_player()->more(read_file(VAMPIRES_GUILD_DIR +
                    "obj/page2-2-2.txt",0));
                    break;
                    
                    case 3:
                    this_player()->more(read_file(VAMPIRES_GUILD_DIR +
                    "obj/page2-2-3.txt",0));
                    break;
                }
            }
            
            
            if (factor2 == 3)
            {
                switch(factor3)
                {
                    case 1:
                    this_player()->more(read_file(VAMPIRES_GUILD_DIR +
                    "obj/page2-3-1.txt",0));
                    break;
                    
                    case 2:
                    this_player()->more(read_file(VAMPIRES_GUILD_DIR +
                    "obj/page2-3-2.txt",0));
                    break;
                    
                    case 3:
                    this_player()->more(read_file(VAMPIRES_GUILD_DIR +
                    "obj/page2-3-3.txt",0));
                    break;
                }
            }
        }
        
          
        if (factor1 == 3)
        {
            if (factor2 == 1)
            {
                switch(factor3)
                {
                    case 1:
                    this_player()->more(read_file(VAMPIRES_GUILD_DIR +
                    "obj/page3-1-1.txt",0));
                    break;
                    
                    case 2:
                    this_player()->more(read_file(VAMPIRES_GUILD_DIR +
                    "obj/page3-1-2.txt",0));
                    break;
                    
                    case 3:
                    this_player()->more(read_file(VAMPIRES_GUILD_DIR +
                    "obj/page3-1-3.txt",0));
                    break;
                }
            }
            
            
            if (factor2 == 2)
            {
                switch(factor3)
                {
                    case 1:
                    this_player()->more(read_file(VAMPIRES_GUILD_DIR +
                    "obj/page3-2-1.txt",0));
                    break;
                    
                    case 2:
                    this_player()->more(read_file(VAMPIRES_GUILD_DIR +
                    "obj/page3-2-2.txt",0));
                    break;
                    
                    case 3:
                    this_player()->more(read_file(VAMPIRES_GUILD_DIR +
                    "obj/page3-2-3.txt",0));
                    break;
                }
            }
            
            
            if (factor2 == 3)
            {
                switch(factor3)
                {
                    case 1:
                    this_player()->more(read_file(VAMPIRES_GUILD_DIR +
                    "obj/page3-3-1.txt",0));
                    break;
                    
                    case 2:
                    this_player()->more(read_file(VAMPIRES_GUILD_DIR +
                    "obj/page3-3-2.txt",0));
                    break;
                    
                    case 3:
                    this_player()->more(read_file(VAMPIRES_GUILD_DIR +
                    "obj/page3-3-3.txt",0));
                    break;
                }
            }
        }
        
        return;
    }
        
    if (page == 2)
    {
        this_player()->more(read_file(VAMPIRES_GUILD_DIR +
        "obj/page2.txt",0));
                    
        return;
    }

    write("As you merely think about approach the large red "
    +"leather binding, a whisper in your head suddenly echoes: 'No!'\n");  
    
    return;
}








   