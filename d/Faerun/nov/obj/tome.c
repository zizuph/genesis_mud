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
        add_adj("black");
        add_adj("leather-bound");
        set_short("black leather-bound tome on a marble stand");
        set_long("This is a black leather-bound tome. It rests upon a marble stand.\n");

        add_prop(OBJ_M_NO_GET,"It is firmly chained to the marble stand.\n");
        set_max_pages(14);
        
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
                file = read_file(NOV_DIR +"obj/tome/page1");
                this_player()->more(file,0);
        }
        
    if(page == 2)
    {
                file = read_file(NOV_DIR +"obj/tome/page2");
                this_player()->more(file,0);
        }
        
    if(page == 3)
    {
                file = read_file(NOV_DIR +"obj/tome/page3");
                this_player()->more(file,0);
        }
        
    if(page == 4)
    {
                file = read_file(NOV_DIR +"obj/tome/page4");
                this_player()->more(file,0);
        }
    
    if(page == 5)
    {
                file = read_file(NOV_DIR +"obj/tome/page5");
                this_player()->more(file,0);
        }
        
    if(page == 6)
    {
                file = read_file(NOV_DIR +"obj/tome/page6");
                this_player()->more(file,0);
        }
        
    if(page == 7)
    {
                file = read_file(NOV_DIR +"obj/tome/page7");
                this_player()->more(file,0);
        }
        
    if(page == 8)
    {
                file = read_file(NOV_DIR +"obj/tome/page8");
                this_player()->more(file,0);
        }
        
    if(page == 9)
    {
                file = read_file(NOV_DIR +"obj/tome/page9");
                this_player()->more(file,0);
        }
        
    if(page == 10)
    {
                file = read_file(NOV_DIR +"obj/tome/page10");
                this_player()->more(file,0);
        }
        
    if(page == 11)
    {
                file = read_file(NOV_DIR +"obj/tome/page11");
                this_player()->more(file,0);
        }
        
    if(page == 12)
    {
                file = read_file(NOV_DIR +"obj/tome/page12");
                this_player()->more(file,0);
        } 
        
     if(page == 13)
    {
                file = read_file(NOV_DIR +"obj/tome/page13");
                this_player()->more(file,0);
        }
        
    if(page == 14)
    {
                file = read_file(NOV_DIR +"obj/tome/page14");
                this_player()->more(file,0);
        }       
        

}

int
mem_deathcoil()
{
        write("You successfully memorize Deathcoil.\n");
        tell_room(environment(this_object()), QCTNAME(this_player())+ " successfully memorizes " +
        "Deathcoil!\n", this_player());
        this_player()->set_skill(ABILITY1, 1);
        
        return 1;
}

int
mem_deathshield()
{
        write("You successfully memorize Deathshield.\n");
        tell_room(environment(this_object()), QCTNAME(this_player())+ " successfully memorizes Deathshield!\n", this_player());
        this_player()->set_skill(ABILITY1, 2);
        
        return 1;
}

int
mem_firebolt()
{
        write("You successfully memorize Firebolt.\n");
        tell_room(environment(this_object()), QCTNAME(this_player())+ " successfully memorizes Firebolt!\n", this_player());
        this_player()->set_skill(ABILITY1, 3);
        
        return 1;
}

int
mem_windbolt()
{
        write("You successfully memorize Windbolt.\n");
        tell_room(environment(this_object()), QCTNAME(this_player())+ " successfully memorizes Windbolt!\n", this_player());
        this_player()->set_skill(ABILITY1, 4);
        
        return 1;
}

int
mem_claybolt()
{
        write("You successfully memorize Claybolt.\n");
        tell_room(environment(this_object()), QCTNAME(this_player())+ " successfully memorizes Claybolt!\n", this_player());
        this_player()->set_skill(ABILITY1, 5);
        
        return 1;
}

int
mem_waterbolt()
{
        write("You successfully memorize Waterbolt.\n");
        tell_room(environment(this_object()), QCTNAME(this_player())+ " successfully memorizes Waterbolt!\n", this_player());
        this_player()->set_skill(ABILITY1, 6);
        
        return 1;
}

int
mem_shadowbolt()
{
        write("You successfully memorize Shadowbolt.\n");
        tell_room(environment(this_object()), QCTNAME(this_player())+ " successfully memorizes Shadowbolt!\n", this_player());
        this_player()->set_skill(ABILITY1, 7);
        
        return 1;
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
mem_regeneration()
{
        write("You successfully memorize Regeneration.\n");
        tell_room(environment(this_object()), QCTNAME(this_player())+ " successfully memorizes Regeneration!\n", this_player());
        this_player()->set_skill(ABILITY2, 5);
        
        return 1;
}

int
mem_fear()
{
        write("You successfully memorize Fear.\n");
        tell_room(environment(this_object()), QCTNAME(this_player())+ " successfully memorizes Fear!\n", this_player());
        this_player()->set_skill(ABILITY2, 6);
        
        return 1;
}

int
mem_purge()
{
        write("You successfully memorize Purge.\n");
        tell_room(environment(this_object()), QCTNAME(this_player())+ " successfully memorizes Purge!\n", this_player());
        this_player()->set_skill(ABILITY2, 7);
        
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
	
	
	if (str == "deathcoil")
	{
            this_player()->catch_tell("You begin to memorize Deathcoil!\n");
            tell_room(environment(this_object()), QCTNAME(this_player())+" begins to memorize Deathcoil!\n",({this_player()}));
            paralyze = clone_object("/std/paralyze");
            paralyze -> set_remove_time(60);
            paralyze -> set_fail_message("You are busy memorizing Deathcoil!\n");
            paralyze -> set_stop_message("");
            paralyze -> move(this_player(), 1);
            set_alarm(60.0,0.0, &mem_deathcoil());
            return 1;
        }
        
        if (str == "deathshield")
	{
            this_player()->catch_tell("You begin to memorize Deathshield!\n");
            tell_room(environment(this_object()), QCTNAME(this_player())+" begins to memorize Deathshield!\n",({this_player()}));
            paralyze = clone_object("/std/paralyze");
            paralyze -> set_remove_time(60);
            paralyze -> set_fail_message("You are busy memorizing Deathshield!\n");
            paralyze -> set_stop_message("");
            paralyze -> move(this_player());
            set_alarm(60.0,0.0, &mem_deathshield());
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
        
        if (str == "regeneration")
	{
            this_player()->catch_tell("You begin to memorize Regeneration!\n");
            tell_room(environment(this_object()), QCTNAME(this_player())+" begins to memorize Regeneration!\n",({this_player()}));
            paralyze = clone_object("/std/paralyze");
            paralyze -> set_remove_time(60);
            paralyze -> set_fail_message("You are busy memorizing Regeneration!\n");
            paralyze -> set_stop_message("");
            paralyze -> move(this_player());
            set_alarm(60.0,0.0, &mem_regeneration());
            return 1;
        }
        
        if (str == "fear")
	{
            this_player()->catch_tell("You begin to memorize Fear!\n");
            tell_room(environment(this_object()), QCTNAME(this_player())+" begins to memorize Fear!\n",({this_player()}));
            paralyze = clone_object("/std/paralyze");
            paralyze -> set_remove_time(60);
            paralyze -> set_fail_message("You are busy memorizing Fear!\n");
            paralyze -> set_stop_message("");
            paralyze -> move(this_player());
            set_alarm(60.0,0.0, &mem_fear());
            return 1;
        }
        
        if (str == "purge")
	{
            this_player()->catch_tell("You begin to memorize Purge!\n");
            tell_room(environment(this_object()), QCTNAME(this_player())+" begins to memorize Purge!\n",({this_player()}));
            paralyze = clone_object("/std/paralyze");
            paralyze -> set_remove_time(60);
            paralyze -> set_fail_message("You are busy memorizing Purge!\n");
            paralyze -> set_stop_message("");
            paralyze -> move(this_player());
            set_alarm(60.0,0.0, &mem_purge());
            return 1;
        }
        
        if (str == "firebolt")
	{
            this_player()->catch_tell("You begin to memorize Firebolt!\n");
            tell_room(environment(this_object()), QCTNAME(this_player())+" begins to memorize Firebolt!\n",({this_player()}));
            paralyze = clone_object("/std/paralyze");
            paralyze -> set_remove_time(60);
            paralyze -> set_fail_message("You are busy memorizing Firebolt!\n");
            paralyze -> set_stop_message("");
            paralyze -> move(this_player());
            set_alarm(60.0,0.0, &mem_firebolt());
            return 1;
        }
        
        if (str == "windbolt")
	{
            this_player()->catch_tell("You begin to memorize Windbolt!\n");
            tell_room(environment(this_object()), QCTNAME(this_player())+" begins to memorize Windbolt!\n",({this_player()}));
            paralyze = clone_object("/std/paralyze");
            paralyze -> set_remove_time(60);
            paralyze -> set_fail_message("You are busy memorizing Windbolt!\n");
            paralyze -> set_stop_message("");
            paralyze -> move(this_player());
            set_alarm(60.0,0.0, &mem_windbolt());
            return 1;
        }
        
        if (str == "claybolt")
	{
            this_player()->catch_tell("You begin to memorize Claybolt!\n");
            tell_room(environment(this_object()), QCTNAME(this_player())+" begins to memorize Claybolt!\n",({this_player()}));
            paralyze = clone_object("/std/paralyze");
            paralyze -> set_remove_time(60);
            paralyze -> set_fail_message("You are busy memorizing Claybolt!\n");
            paralyze -> set_stop_message("");
            paralyze -> move(this_player());
            set_alarm(60.0,0.0, &mem_claybolt());
            return 1;
        }
        
        if (str == "waterbolt")
	{
            this_player()->catch_tell("You begin to memorize Waterbolt!\n");
            tell_room(environment(this_object()), QCTNAME(this_player())+" begins to memorize Waterbolt!\n",({this_player()}));
            paralyze = clone_object("/std/paralyze");
            paralyze -> set_remove_time(60);
            paralyze -> set_fail_message("You are busy memorizing Waterbolt!\n");
            paralyze -> set_stop_message("");
            paralyze -> move(this_player());
            set_alarm(60.0,0.0, &mem_waterbolt());
            return 1;
        }
        
        if (str == "shadowbolt")
	{
            this_player()->catch_tell("You begin to memorize Shadowbolt!\n");
            tell_room(environment(this_object()), QCTNAME(this_player())+" begins to memorize Shadowbolt!\n",({this_player()}));
            paralyze = clone_object("/std/paralyze");
            paralyze -> set_remove_time(60);
            paralyze -> set_fail_message("You are busy memorizing Shadowbolt!\n");
            paralyze -> set_stop_message("");
            paralyze -> move(this_player());
            set_alarm(60.0,0.0, &mem_shadowbolt());
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

