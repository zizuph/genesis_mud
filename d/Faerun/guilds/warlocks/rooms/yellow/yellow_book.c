/*
 * /d/Faerun/guilds/warlocks/obj/yellow/yellow_book
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
    add_name("_yellow_binding");
    set_adj("leather");
    add_adj("small");

    set_short("small leather binding on a simple iron book stand");

    set_long("This is a small binding of black cured leather with a "
    +"strange yellow symbol on its cover. You notice it "
    +"contains a few pages, but they are in relatively bad condition. It "
    +"sits on top of a simple iron book stand.\n");
    
    add_item(({"yellow symbol", "yellow sign", "sign", "symbol"}),
    "The symbol on the leather binding is yellow on a black "
    +"background, and resembles a weird yellow triskelion. You "
    +"feel rather weird by looking at it.\n");

    add_prop(OBJ_M_NO_BUY, 1);
    add_prop(OBJ_M_NO_SELL, 1);
    add_prop(OBJ_I_NO_GET,"The small leather binding is "
    +"tethered to the simple iron book stand. You don't dare "
    +"to remove it for some reason.\n");
    add_prop(OBJ_I_NO_STEAL,"The small leather binding is "
    +"tethered to the simple iron book stand. You don't dare "
    +"to remove it for some reason.\n");

    set_max_pages(6);
}


void
read_book_at_page(int page, string verb)
{
    if (WARLOCK_MASTER->is_patr1_warlock(this_player()->query_name()) 
    || WARLOCK_MASTER->is_patr3_warlock(this_player()->query_name()))
    {
        write("As you try to read, images too cruesome to "
        +"tell and remember flashes through your mind! You immediately "
        +"step back and leave the binding alone!\n");
        
        return;
    }
    
    if (this_player()->query_guild_level_lay() >= MIN_PATRON_LEVEL)
    {
    
        if(page == 1)
        {
            this_player()->more(read_file(WARLOCK_GUILDDIR +
            "obj/yellow/page0.txt",0));

            return;
        }

        if (page == 2)
        {
            this_player()->more(read_file(WARLOCK_GUILDDIR +
            "obj/yellow/page1.txt",0));

            return;
        }

        if (page == 3)
        {
            this_player()->more(read_file(WARLOCK_GUILDDIR +
            "obj/yellow/page2.txt",0));

            return;
        }

        if (page == 4)
        {
            this_player()->more(read_file(WARLOCK_GUILDDIR +
            "obj/yellow/page3.txt",0));

            return;
        }

        if (page == 5)
        {
            this_player()->more(read_file(WARLOCK_GUILDDIR +
            "obj/yellow/page4.txt",0));

            return;
        }
    
        if (page == 6)
        {
            this_player()->more(read_file(WARLOCK_GUILDDIR +
            "obj/yellow/page5.txt",0));

            return;
        }
        
    }
        
    write("As you approach the binding, images too cruesome to "
    +"tell and remember flashes through your mind! You immediately "
    +"step back and leave the binding alone!\n");
        
    return;
}