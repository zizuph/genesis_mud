/* /d/Faerun/guilds/warlocks/rooms/join.c
 *
 * Room in the guildhall.
 *
 * Nerull, 2018
 *
 */

#include "/d/Faerun/defs.h"
#include <stdproperties.h>
#include "../guild.h";

inherit WARLOCK_STD_ROOM;

#define HEARD_THE_WHISPERS    "_heard_the_whispers"

#define VAMPIRES_OBJ_DIR  "/d/Faerun/guilds/vampires/obj/"

int searched_here = 0;
object found_item = 0;


// A reasonable way to reset the quest. Every 2.5 minutes.
void
reset_quest()
{
    searched_here = 0;
}


string do_search(object searcher, string str)
{
    object remains;
    
    if (str == "pool" || str == "ground" 
    || str == "muddy ground" || str == "mud"
    || str == "pool of water" || str == "water"
    || str == "swamp water")
    {
        if (searched_here > 0)
        {
            return "";
        }
        
        if (objectp(remains = present("_quest_infant_remains", this_player())))
        {
            return "";
        }
        
        if(this_player()->test_bit(DOMAIN, INFANT_QUEST_GROUP, 
        INFANT_QUEST_BIT))
        {
            return "";
        }
        
        searched_here++;
        
        string item = one_of_list(({
            "obj/infant_remains",
        }));
        
        tell_room(this_object(), QCTNAME(this_player()) + " finds "
        + "the sad skeletal remains of an infant "
        + "girl in the muddy pool of water.\n", this_player());
            
        found_item = clone_object(WARLOCK_GUILDDIR + item);
        
        found_item->move(this_player(), 1);
        
        set_alarm(150.0, 0.0, &reset_quest());
        
        return "You find the sad skeletal remains of an infant "
        +"girl in the muddy pool of water.\n";    
    }
    
    return "";
}


public int
into_shaft()
{
    write("\n\nYou climb up the improvised rope ladder "
    +"and enter the dark hole in the "
    +"soft ceiling.\n\n");
        
    return 0;
}


public int
into_guild()
{
    if (WARLOCK_MASTER->is_lay_warlock(this_player()->query_name()))
    {
        write("\n\nYou enter the large tapestry as it were a "
        +"magical door, and end up somewhere on the other side!\n\n");
        
        return 0;
    }
    
    if (WARLOCK_MASTER->is_occ_warlock(this_player()->query_name()))
    {
        write("\n\nYou enter the large tapestry as it were a "
        +"magical door, and end up somewhere on the other side!\n\n");
        
        return 0;
    }
      
    write("There is no obvious exit north.\n");
        
    return 1;
}


/*
 * Function name: do_join()
 * Description  : The function that adds a member of the guild.
 *
 */
int do_join(string str)
{
    object shadow_lay;
    object shadow_occ;
    object tokena;
    
    if (!this_player()->query_prop(HEARD_THE_WHISPERS))
    {
        return 0;
    }

    // Joining using the Layman slot
    //if (str == "a pact")
    if (str == "layman pact")
    {   
        if (this_player()->query_guild_name_lay())
        {
            write("Return when you have a vacant layman slot, or "
            +"try to join using the occupational slot by "
            +"doing 'make occupatioal pact'.\n");
                
            return 1;
        }
        
        if (this_player()->query_guild_name_lay())
        {
            write("Return when you have a vacant layman slot.\n");
                
            return 1;
        }
        
        if (WARLOCK_MASTER->is_lay_warlock(this_player()->query_name()))
        {
            write("You are already a member of the " + GUILDNAME_STRING + ".\n");
            return 1;
        }
        
        if (WARLOCK_MASTER->is_occ_warlock(this_player()->query_name()))
        {
            write("You are already a member of the " + GUILDNAME_STRING + ".\n");
            return 1;
        }
        
        if (this_player()->query_average() < REQ_AVG)
        {
            write("A terrible, rasping voice of an "
            +"elderly lady echoes through your head, saying: Begone "
            +"fool! You are too weak and to frail for me to even "
            +"consider you as an potential asset!\n");
            
            return 1;        
        }
        
        if (present("warjoin_cooldwn_obj", this_player()))
        {
            write("A terrible, rasping voice of an "
            +"elderly lady echoes through your head, saying: Begone useless "
            +"traitor! "
            +"You breaking the pact is still fresh in "
            +"my memory! Return later! Much...later!\n");
            
            return 1;      
        }
        
        if (!this_player()->query_prop(SECOND_REQUEST) == 1)
        {
            write("Huh..? You really want to trust the rasping voice of "
            +"that unseen eldery woman? It's obviously a trap and damned witchery"
            +", wicked demons lusting for your soul or maybe dreadful "
            +"ghosts or spirits that wants to bind or consume you!\n\nBut, "
            +"if you really has no second doubts, or are willing "
            +"to take such a leap of foolish blind faith, "
            +"then go ahead and 'make layman pact' once more! May whatever "
            +"deity you worship have mercy upon your soul if this "
            +"turns out to be your Doom!\n");
            
            this_player()->add_prop(SECOND_REQUEST, 1);
            
            return 1;
        }
        
        /*if (!this_player()->query_prop(SECOND_REQUEST) == 1)
        {
            write("Huh..? You really want to trust the rasping voice of "
            +"that unseen eldery woman? It's obviously a trap and damned witchery"
            +", wicked demons lusting for your soul or maybe dreadful "
            +"ghosts or spirits that wants to bind or consume you!\n\nBut, "
            +"if you really has no second doubts, or are willing "
            +"to take such a leap of foolish blind faith, "
            +"then go ahead and 'make a pact' once more! May whatever "
            +"deity you worship have mercy upon your soul if this "
            +"turns out to be your Doom!\n");
            
            this_player()->add_prop(SECOND_REQUEST, 1);
            
            return 1;
        }*/

        shadow_lay = clone_object(WARLOCK_GUILD_DIR + "shadows/guild_sh_lay.c");

        if (shadow_lay->shadow_me(this_player(), "layman", "mage",
            GUILDNAME_STRING) != 1)
        {
            write("You make the pact, but nothing happens.\n");
            return 1;
        }

        WARLOCK_MASTER->add_lay_warlock(this_player()->query_name());
            
        write("Doubtfully, you still choose to make a pact with the unseen eldery lady "
        +"by accepting her offer to become a servant of her mysterious "
        +"coven!\n\nImmediately, you feel the doubts starts to build up, but "
        +"you are suddenly unable to move and flee from this cursed place! "
        +"Without warning, you feel for a brief moment a searing pain "
        +"in your heart as if a terrible curse has taken hold on "
        +"you!\n\nAn ebony-colored robe magically appear in your "
        +"inventory, reminding you that you are "
        +"now a new member and a fresh servant of a secret coven of Warlocks "
        +"in Faerun, run by the powerful Witch only known as the "
        +"Whispess!\n");

        write("\nThe tapestry that hangs on the north dirt wall suddenly "
        +"looks like a gate or a portal to you! Go north, servant!\n");

        tell_room(environment(this_player()), this_player()->query_name()
        + " mumbles something, or "
        +"to someone here you can't see!\n", this_player());
        
        if (!present("nopatron_guild_object", this_player()))
        {
            clone_object(GUILD_ITEM4)->move(this_player(), 1);
        }

        this_player()->update_hooks();

        return 1;
    }
    
    // Joining using the OCC slot
    if (str == "occupational pact")
    {   

        //write("Currently under testing. Try later.\n");
                
        //return 1;
        
        if (this_player()->query_guild_name_occ())
        {
            write("Return when you have a vacant occupational slot, or "
            +"try to join using the layman slot by "
            +"doing 'make layman pact'.\n");
                
            return 1;
        }
        
        if (WARLOCK_MASTER->is_occ_warlock(this_player()->query_name()))
        {
            write("You are already a member of the " + GUILDNAME_STRING + ".\n");
            return 1;
        }
        
        if (WARLOCK_MASTER->is_lay_warlock(this_player()->query_name()))
        {
            write("You are already a member of the " + GUILDNAME_STRING + ".\n");
            return 1;
        }
        
        if (this_player()->query_average() < REQ_AVG)
        {
            write("A terrible, rasping voice of an "
            +"elderly lady echoes through your head, saying: Begone "
            +"fool! You are too weak and to frail for me to even "
            +"consider you as an potential asset!\n");
            
            return 1;        
        }
        
        if (present("warjoin_cooldwn_obj", this_player()))
        {
            write("A terrible, rasping voice of an "
            +"elderly lady echoes through your head, saying: Begone useless "
            +"traitor! "
            +"You breaking the pact is still fresh in "
            +"my memory! Return later! Much...later!\n");
            
            return 1;      
        }
        
        if (!this_player()->query_prop(SECOND_REQUEST) == 1)
        {
            write("Huh..? You really want to trust the rasping voice of "
            +"that unseen eldery woman? It's obviously a trap and damned witchery"
            +", wicked demons lusting for your soul or maybe dreadful "
            +"ghosts or spirits that wants to bind or consume you!\n\nBut, "
            +"if you really has no second doubts, or are willing "
            +"to take such a leap of foolish blind faith, "
            +"then go ahead and 'make occupational pact' once more! May whatever "
            +"deity you worship have mercy upon your soul if this "
            +"turns out to be your Doom!\n");
            
            this_player()->add_prop(SECOND_REQUEST, 1);
            
            return 1;
        }

        shadow_occ = clone_object(WARLOCK_GUILD_DIR + "shadows/guild_sh_occ.c");

        if (shadow_occ->shadow_me(this_player(), "occupational", "mage",
            GUILDNAME_STRING) != 1)
        {
            write("You make the pact, but nothing happens.\n");
            return 1;
        }

        WARLOCK_MASTER->add_occ_warlock(this_player()->query_name());
            
        write("Doubtfully, you still choose to make a pact with the unseen eldery lady "
        +"by accepting her offer to become a servant of her mysterious "
        +"coven!\n\nImmediately, you feel the doubts starts to build up, but "
        +"you are suddenly unable to move and flee from this cursed place! "
        +"Without warning, you feel for a brief moment a searing pain "
        +"in your heart as if a terrible curse has taken hold on "
        +"you!\n\nAn ebony-colored robe magically appear in your "
        +"inventory, reminding you that you are "
        +"now a new member and a fresh servant of a secret coven of Warlocks "
        +"in Faerun, run by the powerful Witch only known as the "
        +"Whispess!\n");

        write("\nThe tapestry that hangs on the north dirt wall suddenly "
        +"looks like a gate or a portal to you! Go north, servant!\n");

        tell_room(environment(this_player()), this_player()->query_name()
        + " mumbles something, or "
        +"to someone here you can't see!\n", this_player());
        
        if (!present("nopatron_guild_object", this_player()))
        {
            clone_object(GUILD_ITEM4)->move(this_player(), 1);
        }

        this_player()->update_hooks();
            
        return 1;
    }
    
    write("What do you want to do here? Do you dare "
    +"to 'make <layman | occupational> pact' "
    +"with the unseen eldery lady in order to join her "
    +"mysterious coven?\n");
            
    return 1;
}


void
do_offer_guildjoin()
{ 
    if (present("warjoin_cooldwn_obj", this_player()))
    {
        this_player()->catch_tell("\n\nNothing happens.\n\n");    
        
        return;        
    }
    
    if (this_player()->query_guild_name_lay() == WARLOCK_NAME)
    {
        this_player()->catch_tell("\n\nNothing happens.\n\n");    
        
        return;
    }
    
    if (this_player()->query_guild_name_occ() == WARLOCK_NAME)
    {
        this_player()->catch_tell("\n\nNothing happens.\n\n");    
        
        return;
    }
    
    if (this_player()->query_average() < REQ_AVG)
    {
        this_player()->catch_tell("\n\nA terrible, rasping voice of an "
        +"elderly lady echoes through your head, saying: ...Too small, too "
        +"frail! Begone, useless maggot!\n\n");    
        
        return;        
    }
    
    this_player()->catch_tell("\n\nA terrible, rasping voice of an elderly lady "
    +"echoes through your head, saying: ...What have we here? A curious "
    +"visitor? Strong, able and cunning! If you Dare, 'make "
    +"<layman | occupational> pact' with me!\n\nIn exchange for your servitude, I "
    +"offer you a "
    +"path of purpose, a path of knowledge, and a path of "
    +"Power! As a member and a servant of my humble coven, in time, I may "
    +"even guide you on the path to become a powerful Warlock!  "
    +"    Ha ha ha ha!\n\n");
    
    /*this_player()->catch_tell("\n\nA terrible, rasping voice of an elderly lady "
    +"echoes through your head, saying: ...What have we here? A curious "
    +"visitor? Strong, able and cunning! If you Dare, 'make "
    +"a pact' with me!\n\nIn exchange for your servitude, I "
    +"offer you a "
    +"path of purpose, a path of knowledge, and a path of "
    +"Power! As a member and a servant of my humble coven, in time, I may "
    +"even guide you on the path to become a powerful Warlock!  "
    +"    Ha ha ha ha!\n\n"); */

    this_player()->add_prop(HEARD_THE_WHISPERS, 1);    
    
    return;
}


int do_touch_tapestry(string str)
{
    if (str == "red blood stain" || str == "stain"
    || str == "red stain" || str == "blood stain")
    {
        write("You reluctantly touch the red blood stain on "
        +"the large tapestry.\n");

        tell_room(environment(this_player()), this_player()->query_name()
        +" reluctantly touches the red blood stain on the large "
        +"tapestry.\n", this_player());
        
        set_alarm(1.0, 0.0, &do_offer_guildjoin());
        
        this_player()->add_prop(I_TOUCHED_TAPESTRY, 1);
        
        return 1;
        
    }
    
    return 0;
}


void
do_whispers()
{  
    if (this_player()->query_guild_name_lay() == WARLOCK_NAME)
    {   
        return;
    }
    
    if (this_player()->query_guild_name_occ() == WARLOCK_NAME)
    {   
        return;
    }
    
    this_player()->catch_tell("\n\nYou hear faint whispers echoing "
    +"from the large tapestry.\n\n");    
    
    return;
}


void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);
    
    if (interactive(ob))
    {
        set_alarm(1.0, 0.0, &do_whispers());
    }
}


/*
 * Function name: do_leave()
 * Description  : The function that removes a member of the guild.
 *
 */
int
do_leave(string str)
{
    object emblem;

    if (str != "the pact")
    {
        write("Do 'break the pact' if you want to "
        +"flee from the coven!\n");
        return 1;
    }

    if (this_player()->query_guild_name_lay() == WARLOCK_NAME)
    {
        write("You decide to break the pact you once made with the Whispess "
        +"and her coven of Warlocks!\nA terrible, rasping voice of an elderly "
        +"lady echoes through your head, saying: ... Flee, weakling! Do not Dare "
        +"to return here again anytime soon!\nSuddenly, you feel as if being "
        +"cursed and unwanted in this place!\n\nYou leave the Warlocks of "
        +"Faerun!\nYour robe fades away!\n");

        tell_room(environment(this_player()), this_player()->query_name()
        +" openly breaks the pact, and leaves the Warlocks of "
        +"Faerun!\n", this_player());
        
        // Removes patron 
        WARLOCK_MASTER->remove_patr1_warlock(this_player()->query_name());
        WARLOCK_MASTER->remove_patr2_warlock(this_player()->query_name());
        WARLOCK_MASTER->remove_patr3_warlock(this_player()->query_name());
        WARLOCK_MASTER->remove_lay_warlock(this_player()->query_name());
        
        WARLOCK_MAPPINGS->clean_desecration_power(this_player()->query_name());
        //WARLOCK_MAPPINGS->set_desecration_primer(this_player()->query_name(), 0)
        WARLOCK_MAPPINGS->clean_desecration_primer(this_player()->query_name());
       
        
        WARLOCK_MAPPINGS->clean_warspell_16(this_player()->query_name());
        WARLOCK_MAPPINGS->clean_warspell_17(this_player()->query_name());
        WARLOCK_MAPPINGS->clean_warspell_18(this_player()->query_name());
        WARLOCK_MAPPINGS->clean_warspell_19(this_player()->query_name());
        

        this_player()->remove_guild_lay();

        this_player()->clear_guild_stat(SS_LAYMAN);

        this_player()->remove_cmdsoul("/d/Faerun/guilds/warlocks/souls/guild_soul");

        this_player()->set_default_start_location(this_player()->query_def_start());
        
        /* Remove any instances of the guild emblem on the player */    
        while (emblem = present(GUILD_ITEM_NAME, this_player()))
        {
            emblem->remove_object();
        }
        
        clone_object(WARLOCK_GUILDDIR 
        + "obj/warjoin_cooldwn_obj")->move(this_player(), 1);

        this_player()->update_hooks();
        
        return 1;
    }
    
    if (this_player()->query_guild_name_occ() == WARLOCK_NAME)
    {
        write("You decide to break the pact you once made with the Whispess "
        +"and her coven of Warlocks!\nA terrible, rasping voice of an elderly "
        +"lady echoes through your head, saying: ... Flee, weakling! Do not Dare "
        +"to return here again anytime soon!\nSuddenly, you feel as if being "
        +"cursed and unwanted in this place!\n\nYou leave the Warlocks of "
        +"Faerun!\nYour robe fades away!\n");

        tell_room(environment(this_player()), this_player()->query_name()
        +" openly breaks the pact, and leaves the Warlocks of "
        +"Faerun!\n", this_player());
        
        // Removes patron 
        WARLOCK_MASTER->remove_patr1_warlock(this_player()->query_name());
        WARLOCK_MASTER->remove_patr2_warlock(this_player()->query_name());
        WARLOCK_MASTER->remove_patr3_warlock(this_player()->query_name());
        WARLOCK_MASTER->remove_occ_warlock(this_player()->query_name());
        
        WARLOCK_MAPPINGS->clean_desecration_power(this_player()->query_name());
        WARLOCK_MAPPINGS->clean_desecration_primer(this_player()->query_name());
       
        WARLOCK_MAPPINGS->clean_warspell_16(this_player()->query_name());
        WARLOCK_MAPPINGS->clean_warspell_17(this_player()->query_name());
        WARLOCK_MAPPINGS->clean_warspell_18(this_player()->query_name());
        WARLOCK_MAPPINGS->clean_warspell_19(this_player()->query_name());
        

        this_player()->remove_guild_occ();

        this_player()->clear_guild_stat(SS_OCCUP);

        this_player()->remove_cmdsoul("/d/Faerun/guilds/warlocks/souls/guild_soul");

        this_player()->set_default_start_location(this_player()->query_def_start());
        
        /* Remove any instances of the guild emblem on the player */    
        while (emblem = present(GUILD_ITEM_NAME, this_player()))
        {
            emblem->remove_object();
        }
        
        clone_object(WARLOCK_GUILDDIR 
        + "obj/warjoin_cooldwn_obj")->move(this_player(), 1);

        this_player()->update_hooks();
        
        return 1;
    }

    write("You are not a member of the "+ GUILDNAME_STRING + ".\n");
 
    return 1;
}


// SERVICEFUNCTION - SHOULD BE DISABLED BY DEFAULT
/*
 * Function name: do_leave()
 * Description  : The function that removes a member of the guild.
 *
 */
int
do_leave_service(string str)
{
    object emblem;

    if (str != "the pact")
    {
        write("Do 'service the pact' if you want to "
        +"leave the guild and clean up lingering mess!\n");
        return 1;
    }

    //if (this_player()->query_guild_name_lay() == WARLOCK_NAME)
    //{
        write("You decide to break the pact you once made with the Whispess "
        +"and her coven of Warlocks!\nA terrible, rasping voice of an elderly "
        +"lady echoes through your head, saying: ... Flee, weakling! Do not Dare "
        +"to return here again anytime soon!\nSuddenly, you feel as if being "
        +"cursed and unwanted in this place!\n\nYou leave the Warlocks of "
        +"Faerun!\nYour robe fades away!\n");

        tell_room(environment(this_player()), this_player()->query_name()
        +" openly breaks the pact, and leaves the Warlocks of "
        +"Faerun!\n", this_player());
        
        // Removes patron 
        WARLOCK_MASTER->remove_patr1_warlock(this_player()->query_name());
        WARLOCK_MASTER->remove_patr2_warlock(this_player()->query_name());
        WARLOCK_MASTER->remove_patr3_warlock(this_player()->query_name());
        WARLOCK_MASTER->remove_lay_warlock(this_player()->query_name());
        
        WARLOCK_MAPPINGS->clean_desecration_power(this_player()->query_name());
        //WARLOCK_MAPPINGS->set_desecration_primer(this_player()->query_name(), 0)
        WARLOCK_MAPPINGS->clean_desecration_primer(this_player()->query_name());
       
        
        WARLOCK_MAPPINGS->clean_warspell_16(this_player()->query_name());
        WARLOCK_MAPPINGS->clean_warspell_17(this_player()->query_name());
        WARLOCK_MAPPINGS->clean_warspell_18(this_player()->query_name());
        WARLOCK_MAPPINGS->clean_warspell_19(this_player()->query_name());
        

        this_player()->remove_guild_lay();

        this_player()->clear_guild_stat(SS_LAYMAN);

        this_player()->remove_cmdsoul("/d/Faerun/guilds/warlocks/souls/guild_soul");

        this_player()->set_default_start_location(this_player()->query_def_start());
        
        /* Remove any instances of the guild emblem on the player */    
        while (emblem = present(GUILD_ITEM_NAME, this_player()))
        {
            emblem->remove_object();
        }
        
        //clone_object(WARLOCK_GUILDDIR 
        //+ "obj/warjoin_cooldwn_obj")->move(this_player(), 1);

        this_player()->update_hooks();
        
        return 1;
    //}
    
    /*if (this_player()->query_guild_name_occ() == WARLOCK_NAME)
    {
        write("You decide to break the pact you once made with the Whispess "
        +"and her coven of Warlocks!\nA terrible, rasping voice of an elderly "
        +"lady echoes through your head, saying: ... Flee, weakling! Do not Dare "
        +"to return here again anytime soon!\nSuddenly, you feel as if being "
        +"cursed and unwanted in this place!\n\nYou leave the Warlocks of "
        +"Faerun!\nYour robe fades away!\n");

        tell_room(environment(this_player()), this_player()->query_name()
        +" openly breaks the pact, and leaves the Warlocks of "
        +"Faerun!\n", this_player());
        
        // Removes patron 
        WARLOCK_MASTER->remove_patr1_warlock(this_player()->query_name());
        WARLOCK_MASTER->remove_patr2_warlock(this_player()->query_name());
        WARLOCK_MASTER->remove_patr3_warlock(this_player()->query_name());
        WARLOCK_MASTER->remove_occ_warlock(this_player()->query_name());
        
        WARLOCK_MAPPINGS->clean_desecration_power(this_player()->query_name());
        WARLOCK_MAPPINGS->clean_desecration_primer(this_player()->query_name());
       
        WARLOCK_MAPPINGS->clean_warspell_16(this_player()->query_name());
        WARLOCK_MAPPINGS->clean_warspell_17(this_player()->query_name());
        WARLOCK_MAPPINGS->clean_warspell_18(this_player()->query_name());
        WARLOCK_MAPPINGS->clean_warspell_19(this_player()->query_name());
        

        this_player()->remove_guild_occ();

        this_player()->clear_guild_stat(SS_OCCUP);

        this_player()->remove_cmdsoul("/d/Faerun/guilds/warlocks/souls/guild_soul");

        this_player()->set_default_start_location(this_player()->query_def_start());
        
        /* Remove any instances of the guild emblem on the player */    
        /*while (emblem = present(GUILD_ITEM_NAME, this_player()))
        {
            emblem->remove_object();
        }
        
        clone_object(WARLOCK_GUILDDIR 
        + "obj/warjoin_cooldwn_obj")->move(this_player(), 1);

        this_player()->update_hooks();
        
        return 1;
    }*/

    write("You are not a member of the "+ GUILDNAME_STRING + ".\n");
 
    return 1;
}


string tapestry()
{
    if (WARLOCK_MASTER->is_lay_warlock(this_player()->query_name()))
    {
        return "The large tapestry covers the north dirt wall, and "
        +"is made of fine hair like threads. The top corners are "
        +"anchored to the mesh of roots with thin ropes, preventing "
        +"it from falling into the muddy pool of swamp water. When you "
        +"study it closely, you realize the vague colour patterns are "
        +"just a mirage, designed to keep the uninitiated from "
        +"entering its true form; a magical passage to somewhere "
        +"else! You may enter the tapestry by simply going north. A "
        +"red blood stain is visible at the bottom left corner of it.\n";
    }
    
    return "The large tapestry covers the north dirt wall, and is made of "
    +"fine hairlike threads. The top corners are anchored to the mesh of "
    +"roots with thin ropes, preventing it from falling into the muddy "
    +"pool of swamp water. It seems quite old and doesn't depict "
    +"anything else but vague random colour patterns. Some kind "
    +"of abstract art maybe? Regardless, it reeks of swamp water "
    +"and is rather uninteresting except for the red blood stain "
    +"on the left bottom corner.\n";
}


/*
 * Function name: create_guildhall_room
 * Description  : Constructor, redefine this to configure your room
 */
public void
create_warlock_room()
{
    seteuid(getuid());
    
    add_prop(ROOM_I_INSIDE, 1);
    add_prop(ROOM_I_LIGHT, 0);
    add_prop(ROOM_I_NO_ALLOW_STEED, 1);
    
    add_prop(OBJ_S_SEARCH_FUN, "do_search");
    add_prop(OBJ_I_SEARCH_TIME, 5);

    set_short("In a murky water infested underground earth cavity");
    
    set_long("You are inside a murky water infested underground "
    +"earth cavity. Stinking swamp water constantly trickles in from "
    +"the rough root-infested dirt walls, forming a pool of muddy water "
    +"that cover your feet. The reek of decaying stagnant matter is "
    +"almost unbearable here, but the curious presence of a large tapestry "
    +"covering the north wall makes you almost forgetful about "
    +"it. There is a painting attached to the south wall. An "
    +"improvised rope ladder makes it possible to climb "
    +"back out of this dreadful underground swamp cavity.\n");
    
    add_item(({"tapestry", "large tapestry"}), tapestry);

    add_item(({"sinew"}),
        "Strong sinews from animals maybe, keeping the large "
        +"tapestry from falling into the muddy pool "
        +"of swamp water.\n");
        
    add_item(({"finger imprints", "prints", "finger prints"}),
        "It looks like imprints from different humanoids. You "
        +"conclude that someone tried to touch the blood stain for "
        +"some obscure reason.\n");
        
    add_item(({"red blood stain", "blood stain", "stain", 
    "red stain"}),
        "At the left bottom corner of the large tapestry, there "
        +"is a red blood stain. Near and around it, you "
        +"see finger imprints, as if somebody has touched "
        +"it...\n");
        
    add_item(({"cave", "cavity"}),
        "This whole reeking place looks roughly excavated by manual "
        +"labour. Meshes of strong roots cover the moist "
        +"dirt walls and ceiling, preventing immediate "
        +"collapse.\n");
        
    add_item(({"patterns", "colour", "colour patterns", "circles",
    "random circles"}),
        "The large tapestry depicts a series of random circles "
        +"and shapes of read, blue, yellow and violet colours. "
        +"They are vague in appearance, but don't mean anything "
        +"to you.\n");
    
    add_item(({"up", "ceiling", "roof", "soft ceiling"}),
        "Clad with a mesh of strong roots, the soft earth ceiling is " 
        +"barely kept from caving in. It is saturated by stinking "
        +"swamp water from above.\n");
        
    add_item(({"root", "roots", "strong roots", "mesh", "mesh of roots"}),
        "While everything else in this underground cavity seems loose "
        +"and nearly to give in at any moment, the exception is the "
        +"myriad of roots that form a protective strong mesh that "
        +"keeps it all together. It's as if some strong ancient "
        +"magic is at work here.\n");
        
    add_item(({"walls", "wall", "soft walls", "dirt wall", "dirt walls"}),
        "The walls consist of soft soaked dirt. Swamp water trickles in "
        +"from nearly everywhere, but meshes of roots keeps them from "
        +"caving in.\n");
        
    add_item(({"soft ground", "ground", "floor", "mud"}),
        "You can only feel the soft muddy ground with your "
        +"feet due to the ground being flooded entirely "
        +"by stinking swamp water. The mix of mud and "
        +"water makes it opaque. You feel there is something "
        +"in it though. While repulsing, perhaps searching "
        +"it would uncover something of interest?\n");
        
    add_item(({"rough ladder", "improvised rope ladder", 
    "rope ladder", "ladder"}),
        "When you inspect the improvised ladder more "
        +"carefully, you notice it's made of a combination "
        +"of old ropes, branches and vines. It leads up through "
        +"the dark hole in the soft ceiling.\n");
        
    add_item(({"hole", "dark hole"}),
        "It's a dark hole like a black open maw in the soft "
        +"ceiling that leads up to the surface of the "
        +"mere. An improvised rope ladder hangs in the "
        +"middle of it.\n");
        
    add_item(({"stink", "smell"}),
        "You think the smell is due to a combination of stagnant "
        +"swamp water and decaying matter. It is almost "
        +"unbearable.\n");
        
    room_add_object(VAMPIRES_OBJ_DIR  + "vamp_painting5");
        
    add_item(({"pool", "pool of water", "water", 
    "swamp water","muddy water"}),
        "It's an opaque combination of stinking swamp water and mud "
        +"from the soft ground. While more swamp water keeps trickling "
        +"in, it never seems to rise beyond "
        +"the level of your ankles. Strange.\n");
        
     
    add_exit(WARLOCK_ROOMS_DIR + "central", "north", into_guild,0,1);
    add_exit(WARLOCK_ROOMS_DIR + "shaft2", "up", into_shaft);
    
    reset_faerun_room();
}


void
reset_faerun_room()
{
    searched_here = 0;
    found_item = 0;
}


// Obsolete for now.
int 
respond(int i)
{
    if (i == 1)
    {
        
        write("Ask about what?\n");
        
        return 1;
    }
    
    if (i == 2)
    {
        
        write("jtestutest?\n");
        
        return 1;
    }
    
    return 0;
}


// Obsolete for now.
int
do_ask_stuff(string str)
{
    if (str == "about warlocks" || str == "about warlock")
    {   
        set_alarm(1.0, 0.0, &respond(2));
        
        return 1;
    }
      
    return 0;
}


void
init()
{
    ::init();

    add_action(do_join, "make");
    add_action(do_touch_tapestry, "touch");
    add_action(do_leave, "break");
    
    // SERVICE FUNCTION - SHOULD BE DISABLED
    //add_action(do_leave_service, "service");
    
    //add_action(do_ask_stuff, "ask");
}

