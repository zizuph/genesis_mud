#include <tasks.h>
#include <macros.h>
#include <ss_types.h>
#include <composite.h>
#include "../nov.h"
#include <stdproperties.h>

inherit "/std/book";

void 
create_book()
{
        set_name("tome");
        add_adj("brown");
        add_adj("leather-bound");
        set_short("brown leather-bound tome on a marble stand");
        set_long("This is a brown leather-bound tome. It rests upon a marble stand.\n");

        add_prop(OBJ_M_NO_GET,"It is firmly chained to the marble stand.\n");
        set_max_pages(7);
        
        setuid();
    seteuid(getuid());
}

void
open_me()
{
        ::open_me();

        return;
}

void
close_me()
{
        ::close_me();
        return;
}

void
read_book_at_page(int page, string verb)
{
        string file;

    seteuid(getuid());


    if(page == 1)
    {
                file = read_file(NOV_DIR +"obj/tome3/page1");
                this_player()->more(file,0);
        }
        
    if(page == 2)
    {
                file = read_file(NOV_DIR +"obj/tome2/page2");
                this_player()->more(file,0);
        }
        
    if(page == 3)
    {
                file = read_file(NOV_DIR +"obj/tome2/page3");
                this_player()->more(file,0);
        }
        
    if(page == 4)
    {
                file = read_file(NOV_DIR +"obj/tome2/page4");
                this_player()->more(file,0);
        }
    
    
        
    
        

}


//-------------------------------------------------------------

int
mem_darkvision()
{
        write("You successfully memorize Darkvision.\n");
        tell_room(environment(this_object()), QCTNAME(this_player())+ " successfully memorizes Darkvision!\n", this_player());
        this_player()->set_skill(ABILITY2, 1);
        
        return 1;
}

int
mem_ghostsight()
{
        write("You successfully memorize Ghostsight.\n");
        tell_room(environment(this_object()), QCTNAME(this_player())+ " successfully memorizes Ghostsight!\n", this_player());
        this_player()->set_skill(ABILITY2, 2);
        
        return 1;
}

int
mem_ghostform()
{
        write("You successfully memorize Ghostform.\n");
        tell_room(environment(this_object()), QCTNAME(this_player())+ " successfully memorizes Ghostform!\n", this_player());
        this_player()->set_skill(ABILITY2, 3);
        
        return 1;
}

int
mem_scrutinize()
{
        write("You successfully memorize Scrutinize.\n");
        tell_room(environment(this_object()), QCTNAME(this_player())+ " successfully memorizes Scrutinize!\n", this_player());
        this_player()->set_skill(ABILITY2, 4);
        
        return 1;
}





int
select_1(string str)
{
	object paralyze;
	
	if (!str)
	{
		write("memorize <spell>, perhaps?\n");
		return 1;
	}
	

        if (str == "darkvision")
	{
            this_player()->catch_tell("You begin to memorize Darkvision!\n");
            tell_room(environment(this_object()), QCTNAME(this_player())+" begins to memorize Darkvision!\n",({this_player()}));
            paralyze = clone_object("/std/paralyze");
            paralyze -> set_remove_time(60);
            paralyze -> set_fail_message("You are busy memorizing Darkvision!\n");
            paralyze -> set_stop_message("");
            paralyze -> move(this_player());
            set_alarm(60.0,0.0, &mem_darkvision());
            return 1;
        }
        
        if (str == "ghostsight")
	{
            this_player()->catch_tell("You begin to memorize Ghostsight!\n");
            tell_room(environment(this_object()), QCTNAME(this_player())+" begins to memorize Ghostsight!\n",({this_player()}));
            paralyze = clone_object("/std/paralyze");
            paralyze -> set_remove_time(60);
            paralyze -> set_fail_message("You are busy memorizing Ghostsight!\n");
            paralyze -> set_stop_message("");
            paralyze -> move(this_player());
            set_alarm(60.0,0.0, &mem_ghostsight());
            return 1;
        }
        
        if (str == "ghostform")
	{
            this_player()->catch_tell("You begin to memorize Ghostform!\n");
            tell_room(environment(this_object()), QCTNAME(this_player())+" begins to memorize Ghostform!\n",({this_player()}));
            paralyze = clone_object("/std/paralyze");
            paralyze -> set_remove_time(60);
            paralyze -> set_fail_message("You are busy memorizing Ghostform!\n");
            paralyze -> set_stop_message("");
            paralyze -> move(this_player());
            set_alarm(60.0,0.0, &mem_ghostform());
            return 1;
        }
        
        if (str == "scrutinize")
	{
            this_player()->catch_tell("You begin to memorize Scrutinize!\n");
            tell_room(environment(this_object()), QCTNAME(this_player())+" begins to memorize Scrutinize!\n",({this_player()}));
            paralyze = clone_object("/std/paralyze");
            paralyze -> set_remove_time(60);
            paralyze -> set_fail_message("You are busy memorizing Scrutinize!\n");
            paralyze -> set_stop_message("");
            paralyze -> move(this_player());
            set_alarm(60.0,0.0, &mem_scrutinize());
            return 1;
        }
        

        write("memorize <spell>, perhaps?\n");
        return 1;
}

          



void
init()
{
        ::init();
        add_action(select_1, "memorize");
       // add_action(select_2, "memorize second");
       // add_action(select_3, "memorize third");
}

