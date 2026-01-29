/* /d/Faerun/guilds/warlocks/rooms/patron.c
 *
 * Patron room in the guildhall.
 * Nerull, 2018
 *
 */

#include "/d/Faerun/defs.h"
#include <stdproperties.h>
#include "../guild.h";

inherit WARLOCK_STD_ROOM;

#define PATRON_ABANDON_WARNING   "_patron_abandon_warning"

int destination;


int
select_patron(string str)
{
    setuid();
    seteuid(getuid());
    
    object emblem;
    
    // Asmodeus, Lord of the Nine Hells
    if (str == "asmodeus" || str == "Asmodeus")
    {
        if (WARLOCK_MASTER->is_lay_warlock(this_player()->query_name()))
        {
            if (this_player()->query_guild_level_lay() >= MIN_PATRON_LEVEL)
            {
                if (WARLOCK_MASTER->is_patr1_warlock(this_player()->query_name())
                || WARLOCK_MASTER->is_patr2_warlock(this_player()->query_name())
                || WARLOCK_MASTER->is_patr3_warlock(this_player()->query_name()))
                {
                    write("You already serve a patron!\n");

                    return 1;
                }
                
                if (present("war_cooldwn_ptr1_obj", this_player()))
                {
                    write(PATRON1_NAME + " will not "
                    +"accept you as one of his servants at this time!\n");
                    
                    return 1;        
                }

                WARLOCK_MASTER->add_patr1_warlock(this_player()->query_name());
                
                write("You fall onto your knees and stretches out your arms while "
                +"with absolute conviction beg " + PATRON1_NAME + " for your "
                +"attention! Without warning, you suddenly feel excruciating pain in "
                +"your head when some alien unseen entity touches your mind!\n"
                +"Paralyzed "
                +"by overwhelming the pain, you try to scream but you fail to utter "
                +"anything at all. You feel a part of you wither and die, as if being "
                +"consumed by the alien entity! Suddenly, the pain fades away, and "
                +"you feel...changed. You feel a strong bond is formed and locked "
                +"with "+PATRON1_NAME + ", as you now are in his servitude! You "
                +"stand up again.\nYou are now a Warlock.\n");
                
                tell_room(environment(this_player()), this_player()->query_name()
                + " falls to " + this_player()->query_possessive() +" knees "
                +"with outstreched arms, muttering incessantly. "
                +capitalize(this_player()->query_pronoun()) +" suddenly utters a "
                +"shrill "
                +"shriek and grimaces painfully, before getting back to "
                +this_player()->query_possessive()+" feet.\n", this_player());
                
                    
                WARLOCK_MAPPINGS->set_desecration_power(this_player()->query_name(), 6);
                
                while (emblem = present(GUILD_ITEM_NAME, this_player()))
                {
                    write("Your robe changes appearance!\nThe woven tapestry "
                    +"suddenly flicker for a brief moment.\n");
                    emblem->remove_object();
                }
                
                if (!present("patr1_guild_object", this_player()))
                {
                    clone_object(GUILD_ITEM1)->move(this_player(), 1);
                }

                return 1;
            }
        }
        
        if (WARLOCK_MASTER->is_occ_warlock(this_player()->query_name()))
        {
            if (this_player()->query_guild_level_occ() >= MIN_PATRON_LEVEL)
            {
                if (WARLOCK_MASTER->is_patr1_warlock(this_player()->query_name())
                || WARLOCK_MASTER->is_patr2_warlock(this_player()->query_name())
                || WARLOCK_MASTER->is_patr3_warlock(this_player()->query_name()))
                {
                    write("You already serve a patron!\n");

                    return 1;
                }
                
                if (present("war_cooldwn_ptr1_obj", this_player()))
                {
                    write(PATRON1_NAME + " will not "
                    +"accept you as one of his servants at this time!\n");
                    
                    return 1;        
                }

                WARLOCK_MASTER->add_patr1_warlock(this_player()->query_name());
                
                write("You fall onto your knees and stretches out your arms while "
                +"with absolute conviction beg " + PATRON1_NAME + " for your "
                +"attention! Without warning, you suddenly feel excruciating pain in "
                +"your head when some alien unseen entity touches your mind!\n"
                +"Paralyzed "
                +"by overwhelming the pain, you try to scream but you fail to utter "
                +"anything at all. You feel a part of you wither and die, as if being "
                +"consumed by the alien entity! Suddenly, the pain fades away, and "
                +"you feel...changed. You feel a strong bond is formed and locked "
                +"with "+PATRON1_NAME + ", as you now are in his servitude! You "
                +"stand up again.\nYou are now a Warlock.\n");
                
                tell_room(environment(this_player()), this_player()->query_name()
                + " falls to " + this_player()->query_possessive() +" knees "
                +"with outstreched arms, muttering incessantly. "
                +capitalize(this_player()->query_pronoun()) +" suddenly utters a "
                +"shrill "
                +"shriek and grimaces painfully, before getting back to "
                +this_player()->query_possessive()+" feet.\n", this_player());
                
                    
                WARLOCK_MAPPINGS->set_desecration_power(this_player()->query_name(), 6);
                
                while (emblem = present(GUILD_ITEM_NAME, this_player()))
                {
                    write("Your robe changes appearance!\nThe woven tapestry "
                    +"suddenly flicker for a brief moment.\n");
                    emblem->remove_object();
                }
                
                if (!present("patr1_guild_object", this_player()))
                {
                    clone_object(GUILD_ITEM1)->move(this_player(), 1);
                }

                return 1;
            }
        }
    }   

    // Great Old One, Hastur the Yellow King
    if (str == "hastur" || str == "Hastur")
    {
        if (WARLOCK_MASTER->is_lay_warlock(this_player()->query_name()))
        {
            if (this_player()->query_guild_level_lay() >= MIN_PATRON_LEVEL)
            {
                if (WARLOCK_MASTER->is_patr1_warlock(this_player()->query_name())
                || WARLOCK_MASTER->is_patr2_warlock(this_player()->query_name())
                || WARLOCK_MASTER->is_patr3_warlock(this_player()->query_name()))
                {
                    write("You already serve a patron!\n");

                    return 1;
                }
                
                if (present("war_cooldwn_ptr2_obj", this_player()))
                {
                    write(PATRON2_NAME + " will not "
                    +"accept you as one of his servants at this time!\n");
                    
                    return 1;        
                }

                WARLOCK_MASTER->add_patr2_warlock(this_player()->query_name());

                write("You fall onto your knees and stretches out your arms while "
                +"with absolute conviction beg " + PATRON2_NAME + " for your "
                +"attention! Without warning, you suddenly feel excruciating pain in "
                +"your head when some alien unseen entity touches your mind!\n"
                +"Paralyzed "
                +"by overwhelming the pain, you try to scream but you fail to utter "
                +"anything at all. You feel a part of you wither and die, as if being "
                +"consumed by the alien entity! Suddenly, the pain fades away, and "
                +"you feel...changed. You feel a strong bond is formed and locked "
                +"with "+PATRON2_NAME + ", as you now are in his servitude! You "
                +"stand up again.\nYou are now a Warlock.\n");

                tell_room(environment(this_player()), this_player()->query_name()
                + " falls to " + this_player()->query_possessive() +" knees "
                +"with outstreched arms, muttering incessantly. "
                +capitalize(this_player()->query_pronoun()) +" suddenly utters a "
                +"shrill "
                +"shriek and grimaces painfully, before getting back to "
                +this_player()->query_possessive()+" feet.\n", this_player());
                
                WARLOCK_MAPPINGS->set_desecration_power(this_player()->query_name(), 6);
                
                while (emblem = present(GUILD_ITEM_NAME, this_player()))
                {
                    write("Your robe changes appearance!\nThe woven tapestry "
                    +"suddenly flicker for a brief moment.\n");
                    emblem->remove_object();
                }
                
                if (!present("patr2_guild_object", this_player()))
                {
                    clone_object(GUILD_ITEM2)->move(this_player(), 1);
                }

                return 1;
            }
        }
        
        if (WARLOCK_MASTER->is_occ_warlock(this_player()->query_name()))
        {
            if (this_player()->query_guild_level_occ() >= MIN_PATRON_LEVEL)
            {
                if (WARLOCK_MASTER->is_patr1_warlock(this_player()->query_name())
                || WARLOCK_MASTER->is_patr2_warlock(this_player()->query_name())
                || WARLOCK_MASTER->is_patr3_warlock(this_player()->query_name()))
                {
                    write("You already serve a patron!\n");

                    return 1;
                }
                
                if (present("war_cooldwn_ptr2_obj", this_player()))
                {
                    write(PATRON2_NAME + " will not "
                    +"accept you as one of his servants at this time!\n");
                    
                    return 1;        
                }

                WARLOCK_MASTER->add_patr2_warlock(this_player()->query_name());

                write("You fall onto your knees and stretches out your arms while "
                +"with absolute conviction beg " + PATRON2_NAME + " for your "
                +"attention! Without warning, you suddenly feel excruciating pain in "
                +"your head when some alien unseen entity touches your mind!\n"
                +"Paralyzed "
                +"by overwhelming the pain, you try to scream but you fail to utter "
                +"anything at all. You feel a part of you wither and die, as if being "
                +"consumed by the alien entity! Suddenly, the pain fades away, and "
                +"you feel...changed. You feel a strong bond is formed and locked "
                +"with "+PATRON2_NAME + ", as you now are in his servitude! You "
                +"stand up again.\nYou are now a Warlock.\n");

                tell_room(environment(this_player()), this_player()->query_name()
                + " falls to " + this_player()->query_possessive() +" knees "
                +"with outstreched arms, muttering incessantly. "
                +capitalize(this_player()->query_pronoun()) +" suddenly utters a "
                +"shrill "
                +"shriek and grimaces painfully, before getting back to "
                +this_player()->query_possessive()+" feet.\n", this_player());
                
                WARLOCK_MAPPINGS->set_desecration_power(this_player()->query_name(), 6);
                
                while (emblem = present(GUILD_ITEM_NAME, this_player()))
                {
                    write("Your robe changes appearance!\nThe woven tapestry "
                    +"suddenly flicker for a brief moment.\n");
                    emblem->remove_object();
                }
                
                if (!present("patr2_guild_object", this_player()))
                {
                    clone_object(GUILD_ITEM2)->move(this_player(), 1);
                }

                return 1;
            }
        }
    }   
 
    // Baba Zirana, Archfey
    if (str == "baba zirana" || str == "Baba Zirana")
    {
        if (WARLOCK_MASTER->is_lay_warlock(this_player()->query_name()))
        {
            if (this_player()->query_guild_level_lay() >= MIN_PATRON_LEVEL)
            {
                if (WARLOCK_MASTER->is_patr1_warlock(this_player()->query_name())
                || WARLOCK_MASTER->is_patr2_warlock(this_player()->query_name())
                || WARLOCK_MASTER->is_patr3_warlock(this_player()->query_name()))
                {
                    write("You already serve a patron!\n");

                    return 1;
                }
                
                if (present("war_cooldwn_ptr3_obj", this_player()))
                {
                    write(PATRON3_NAME + " will not "
                    +"accept you as one of her servants at this time!\n");
                    
                    return 1;        
                }

                WARLOCK_MASTER->add_patr3_warlock(this_player()->query_name());

                write("You fall onto your knees and stretches out your arms while "
                +"with absolute conviction beg " + PATRON3_NAME + " for your "
                +"attention! Without warning, you suddenly feel excruciating pain in "
                +"your head when some alien unseen entity touches your mind!\n"
                +"Paralyzed "
                +"by overwhelming the pain, you try to scream but you fail to utter "
                +"anything at all. You feel a part of you wither and die, as if being "
                +"consumed by the alien entity! Suddenly, the pain fades away, and "
                +"you feel...changed. You feel a strong bond is formed and locked "
                +"with "+PATRON3_NAME + ", as you now are in his servitude! You "
                +"stand up again.\nYou are now a Warlock.\n");

                tell_room(environment(this_player()), this_player()->query_name()
                + " falls to " + this_player()->query_possessive() +" knees "
                +"with outstreched arms, muttering incessantly. "
                +capitalize(this_player()->query_pronoun()) +" suddenly utters a "
                +"shrill "
                +"shriek and grimaces painfully, before getting back to "
                +this_player()->query_possessive()+" feet.\n", this_player());
                
                WARLOCK_MAPPINGS->set_desecration_power(this_player()->query_name(), 6);
                
                while (emblem = present(GUILD_ITEM_NAME, this_player()))
                {
                    write("Your robe changes appearance!\nThe woven tapestry "
                    +"suddenly flicker for a brief moment.\n");
                    emblem->remove_object();
                }
                
                if (!present("patr3_guild_object", this_player()))
                {
                    clone_object(GUILD_ITEM3)->move(this_player(), 1);
                }

                return 1;
            }
        }
        
        if (WARLOCK_MASTER->is_occ_warlock(this_player()->query_name()))
        {
            if (this_player()->query_guild_level_occ() >= MIN_PATRON_LEVEL)
            {
                if (WARLOCK_MASTER->is_patr1_warlock(this_player()->query_name())
                || WARLOCK_MASTER->is_patr2_warlock(this_player()->query_name())
                || WARLOCK_MASTER->is_patr3_warlock(this_player()->query_name()))
                {
                    write("You already serve a patron!\n");

                    return 1;
                }
                
                 if (present("war_cooldwn_ptr3_obj", this_player()))
                {
                    write(PATRON3_NAME + " will not "
                    +"accept you as one of her servants at this time!\n");
                    
                    return 1;        
                }

                WARLOCK_MASTER->add_patr3_warlock(this_player()->query_name());

                write("You fall onto your knees and stretches out your arms while "
                +"with absolute conviction beg " + PATRON3_NAME + " for your "
                +"attention! Without warning, you suddenly feel excruciating pain in "
                +"your head when some alien unseen entity touches your mind!\n"
                +"Paralyzed "
                +"by overwhelming the pain, you try to scream but you fail to utter "
                +"anything at all. You feel a part of you wither and die, as if being "
                +"consumed by the alien entity! Suddenly, the pain fades away, and "
                +"you feel...changed. You feel a strong bond is formed and locked "
                +"with "+PATRON3_NAME + ", as you now are in his servitude! You "
                +"stand up again.\nYou are now a Warlock.\n");

                tell_room(environment(this_player()), this_player()->query_name()
                + " falls to " + this_player()->query_possessive() +" knees "
                +"with outstreched arms, muttering incessantly. "
                +capitalize(this_player()->query_pronoun()) +" suddenly utters a "
                +"shrill "
                +"shriek and grimaces painfully, before getting back to "
                +this_player()->query_possessive()+" feet.\n", this_player());
                
                WARLOCK_MAPPINGS->set_desecration_power(this_player()->query_name(), 6);
                
                while (emblem = present(GUILD_ITEM_NAME, this_player()))
                {
                    write("Your robe changes appearance!\nThe woven tapestry "
                    +"suddenly flicker for a brief moment.\n");
                    emblem->remove_object();
                }
                
                if (!present("patr3_guild_object", this_player()))
                {
                    clone_object(GUILD_ITEM3)->move(this_player(), 1);
                }

                return 1;
            }
        }
    }   
    
    if (WARLOCK_MASTER->is_lay_warlock(this_player()->query_name()))
    {
        if (this_player()->query_guild_level_lay() < MIN_PATRON_LEVEL)
        {
            return 0;
        }
    }
    
    if (WARLOCK_MASTER->is_occ_warlock(this_player()->query_name()))
    {
        if (this_player()->query_guild_level_occ() < MIN_PATRON_LEVEL)
        {
            return 0;
        }
    }

    write("Select <name of patron> you wish to serve!\n");
    return 1;
}


int
leave_patron(string str)
{
    object emblem;
    
    if (str == "patron")
    { 
        if (!this_player()->query_prop(PATRON_ABANDON_WARNING) == 1)
        {
            write("Be warned! Leaving your current patron will cost you "
            +"dearly! All gifts given by the patron and the sacrificial "
            +"progress will be removed, and you will again be just a "
            +"servant under the guidance of the Whispess!\nIf you are "
            +"absolutely sure you wish to do this, then 'abandon patron' again!\n");
            
            this_player()->add_prop(PATRON_ABANDON_WARNING, 1);
            
            return 1;
        }
        
        if (WARLOCK_MASTER->is_patr1_warlock(this_player()->query_name()))
        {
            WARLOCK_MASTER->remove_patr1_warlock(this_player()->query_name());

            write("You abandon " + PATRON1_NAME + "!\nYou feel "
            +"a significant part of your power fade away "
            +"when the bond to your former patron is severed!\nYou are no "
            +"longer a Warlock, but a Follower again.\n");

            tell_room(environment(this_player()),
            this_player()->query_name()
            + " suddenly looks greatly reduced!\n", this_player());
            
            /* Remove any instances of the guild emblem on the player */
            while (emblem = present(GUILD_ITEM_NAME, this_player()))
            {
                write("Your robe changes appearance!\n");
                emblem->remove_object();
            }
            
            if (!present("nopatron_guild_object", this_player()))
            {
                clone_object(GUILD_ITEM4)->move(this_player(), 1);
            }
            
            clone_object(WARLOCK_GUILDDIR 
            + "obj/war_cooldwn_ptr1_obj")->move(this_player(), 1);

            return 1;
        }
    
        if (WARLOCK_MASTER->is_patr2_warlock(this_player()->query_name()))
        {
            WARLOCK_MASTER->remove_patr2_warlock(this_player()->query_name());

            write("You abandon " + PATRON2_NAME + "!\nYou feel "
            +"a significant part of your power fade away "
            +"when the bond to your former patron is severed!\nYou are no "
            +"longer a Warlock, but a Follower again.");

            tell_room(environment(this_player()),
            this_player()->query_name()
            + " suddenly looks greatly reduced!\n", this_player());
            
            /* Remove any instances of the guild emblem on the player */
            while (emblem = present(GUILD_ITEM_NAME, this_player()))
            {
                write("Your robe changes appearance!\n");
                emblem->remove_object();
            }
            
            if (!present("nopatron_guild_object", this_player()))
            {
                clone_object(GUILD_ITEM4)->move(this_player(), 1);
            }
            
            clone_object(WARLOCK_GUILDDIR 
            + "obj/war_cooldwn_ptr2_obj")->move(this_player(), 1);

            return 1;
        }
        
        if (WARLOCK_MASTER->is_patr3_warlock(this_player()->query_name()))
        {
            WARLOCK_MASTER->remove_patr3_warlock(this_player()->query_name());

           write("You abandon " + PATRON3_NAME + "!\nYou feel "
            +"a significant part of your power fade away "
            +"when the bond to your former patron is severed!\nYou are no "
            +"longer a Warlock, but a Follower again.");

            tell_room(environment(this_player()),
            this_player()->query_name()
            + " suddenly looks greatly reduced!\n", this_player());
            
            WARLOCK_MAPPINGS->clean_desecration_power(this_player()->query_name());
            WARLOCK_MAPPINGS->clean_desecration_primer(this_player()->query_name());
        
            /* Remove any instances of the guild emblem on the player */
            while (emblem = present(GUILD_ITEM_NAME, this_player()))
            {
                write("Your robe changes appearance!\n");
                emblem->remove_object();
            }
            
            if (!present("nopatron_guild_object", this_player()))
            {
                clone_object(GUILD_ITEM4)->move(this_player(), 1);
            }
            
            clone_object(WARLOCK_GUILDDIR 
            + "obj/war_cooldwn_ptr3_obj")->move(this_player(), 1);

            return 1;
        }
        
         write("You don't have a patron!\n");
         
         return 1;
    }

    return 0;
}


/*
* Function name: touch_symbol
* Description  : Sets up what happens when a member touches a symbol/sign
*/
int
touch_tapestry(string str)
{
    // Patron 1
    if (str == "woven tapestry" || str == "tapestry")
    {
        if (WARLOCK_MASTER->is_patr1_warlock(this_player()->query_name()))
        {
            write("\nYou touch the tapestry, and suddenly, you are pulled "
            +"through time and space to somewhere else!\n\n");

            tell_room(WARLOCK_ROOMS_DIR + "patron_1", QCTNAME(this_player())
            + " suddenly is!\n", this_player());

            tell_room(environment(this_object()), QCTNAME(this_player())
            + " leaves south.\n", this_player());

            this_player()->move_living("M", WARLOCK_ROOMS_DIR + "patron_1", 1);

            return 1;
        }
        
        // Patron 2
        if (WARLOCK_MASTER->is_patr2_warlock(this_player()->query_name()))
        {
            write("\nYou touch the tapestry, and suddenly, you are "
            +"pulled through time and space to somewhere else!\n\n");

            tell_room(WARLOCK_ROOMS_DIR + "patron_2", QCTNAME(this_player())
            + " suddenly is!\n", this_player());

            tell_room(environment(this_object()), QCTNAME(this_player())
            + " leaves south.\n", this_player());

            this_player()->move_living("M", WARLOCK_ROOMS_DIR + "patron_2", 1);

            return 1;
        }
        
        // Patron 3
        if (WARLOCK_MASTER->is_patr3_warlock(this_player()->query_name()))
        {
            write("\nYou touch the tapestry, and suddenly, you are "
            +"pulled through time and space to somewhere else!\n\n");

            tell_room(WARLOCK_ROOMS_DIR + "patron_3", QCTNAME(this_player())
            + " suddenly is!\n", this_player());

            tell_room(environment(this_object()), QCTNAME(this_player())
            + " leaves south.\n", this_player());

            this_player()->move_living("M", WARLOCK_ROOMS_DIR + "patron_3", 1);

            return 1;
        }
        
        return 0;
    }
      
    return 0;
}


string
query_destination()
{
    if (destination == 0)
    {
        return "Engraved into the smooth claystone ground "
        +"and glowing in a purple fashion, the teleporation "
        +"circle is in the dead center of the chamber and "
        +"measures about ten feet in diameter. Anyone "
        +"that 'enter circle' will be teleported "
        +"somewhere else. You may 'set <destination>' for "
        +"the teleport circle. The available settings "
        +"are: Middle Earth, Sparkle and Flotsam. The "
        +"current setting is at: Middle Earth.\n";
    }
    
    if (destination == 1)
    {
        return "Engraved into the smooth claystone ground "
        +"and glowing in a purple fashion, the teleporation "
        +"circle is in the dead center of the chamber and "
        +"measures about ten feet in diameter. Anyone "
        +"that 'enter circle' will be teleported "
        +"somewhere else. You may 'set <destination>' for "
        +"the teleport circle. The available settings "
        +"are: Middle Earth, Sparkle and Flotsam. The "
        +"current setting is at: Sparkle.\n";
    }
    
    if (destination == 2)
    {
        return "Engraved into the smooth claystone ground "
        +"and glowing in a purple fashion, the teleporation "
        +"circle is in the dead center of the chamber and "
        +"measures about ten feet in diameter. Anyone "
        +"that 'enter circle' will be teleported "
        +"somewhere else. You may 'set <destination>' for "
        +"the teleport circle. The available settings "
        +"are: Middle Earth, Sparkle and Flotsam. The "
        +"current setting is at: Flotsam.\n";
    }
    
    return "None";
}

int
set_destination(string str)
{
    if (str == "middle earth")
    {
        destination = 0;
        
        write("You set the destination of the "
        +"teleport circle at: Middle Earth.\n");
        
        return 1;
    }
    
    if (str == "sparkle")
    {
        destination = 1;
        
        write("You set the destination of the "
        +"teleport circle at: Sparkle.\n");
        
        return 1;
    }        
    
    if (str == "flotsam")
    {
        destination = 2;
        
        write("You set the destination of the "
        +"teleport circle at: Flotsam.\n");
        
        return 1;
    }        
    
    write("The only possible settings are: "
    +"Middle earth, Sparkle and Flotsam.\n");
    
    return 1;
}


/*
* Function name: touch_symbol
* Description  : Sets up what happens when a member touches a symbol/sign
*/
int
enter_tepcircle(string str)
{
    setuid();
    seteuid(getuid());
    
    int diceroll = random(4);
    
    // Patron 1
    if (str == "circle" || str == "teleportation circle" || str == "field"
    || str == "teleport circle" || str == "teleport field" 
    || str == "teleportation field")
    {
        write("\nYou step into the teleportation circle, and suddenly you "
        +"are teleported to somewhere else!\n\n");

        tell_room(environment(this_object()), QCTNAME(this_player())
        + " enters the teleportation circle and vanishes!\n", this_player());
        
    
        object void_room;
        
 
        if (destination == 0)
        {
            //this_player()->move_living("M", "/d/Gondor/rohan/plains/j06", 1);
            void_room=clone_object(WARLOCK_GUILDDIR + "rooms/void_1");
            
            this_player()->move_living("M", void_room, 1);
            
            
        
            //tell_room("/d/Gondor/rohan/plains/j06", QCTNAME(this_player())
            //+" arrives in a puff of smoke.\n", this_player());
            
        }
        
        if (destination == 1)
        {
            //this_player()->move_living("M", "/d/Genesis/start/human/wild2/peninsula", 1);
            
            void_room=clone_object(WARLOCK_GUILDDIR + "rooms/void_2");
            
            this_player()->move_living("M", void_room, 1);
        
            //tell_room("/d/Genesis/start/human/wild2/peninsula", QCTNAME(this_player())
            //+" arrives in a puff of smoke.\n", this_player());
            
        }
        
        if (destination == 2)
        {
            //this_player()->move_living("M", "/d/Ansalon/balifor/flotsam/room/street28", 1);
            
            void_room=clone_object(WARLOCK_GUILDDIR + "rooms/void_3");
            
            this_player()->move_living("M", void_room, 1);
        
            //tell_room("/d/Ansalon/balifor/flotsam/room/street28", QCTNAME(this_player())
            //+" arrives in a puff of smoke.\n", this_player());
        }
        
                   
        return 1;
    }
      
    write("Enter what? the teleportation circle?\n");
    return 1;
}


string tapestry()
{
    if (WARLOCK_MASTER->is_patr1_warlock(this_player()->query_name()))
    {
        return "The tapestry hangs on the north wall, and is approximaetly "
        +"ten by three feet in size. As you inspect the tapestry closer, you "
        +"realize it's made by human hair! For a moment, it doesn't portray "
        +"anything but random patterns of shapes and swirling colours, but "
        +"suddenly your mind adjusts, and for you, the pattern starts to "
        +"resemble a red-glowing fiery inverted pentagram on a crimson "
        +"background. You feel an urge to touch it.\n";
    }
    
    if (WARLOCK_MASTER->is_patr2_warlock(this_player()->query_name()))
    {
        return "The tapestry hangs on the north wall, and is approximaetly "
        +"ten by three feet in size. As you inspect the tapestry closer, you "
        +"realize it's made by human hair! For a moment, it doesn't portray "
        +"anything but random patterns of shapes and swirling colours, but "
        +"suddenly your mind adjusts, and for you, the pattern starts to "
        +"resemble a yellow sign, resembling a twisted weird triskelion on "
        +"a pitch black background. You feel an urge to touch it.\n";
    }
    
    if (WARLOCK_MASTER->is_patr3_warlock(this_player()->query_name()))
    {
        return "The tapestry hangs on the north wall, and is approximaetly "
        +"ten by three feet in size. As you inspect the tapestry closer, you "
        +"realize it's made by human hair! For a moment, it doesn't portray "
        +"anything but random patterns of shapes and swirling colours, but "
        +"suddenly your mind adjusts, and for you, the pattern starts to "
        +"resemble a hut or a cabin put in top of a huge walking tree around "
        +"in a deep forest environment. You feel an urge to touch it.\n";
    }

    return "The tapestry hangs on the north wall, and is approximaetly "
    +"ten by three feet in size. As you inspect the tapestry closer, you "
    +"realize it's made by human hair! It doesn't portray anything but "
    +"random patterns of shapes and swirling colours, giving no "
    +"apparent meaning to you.\n";
}


string mural()
{
    if (WARLOCK_MASTER->is_lay_warlock(this_player()->query_name()))
    {
        if (this_player()->query_guild_level_lay() >= MIN_PATRON_LEVEL)
        {
            if (WARLOCK_MASTER->is_patr1_warlock(this_player()->query_name())
            || WARLOCK_MASTER->is_patr2_warlock(this_player()->query_name())
            || WARLOCK_MASTER->is_patr3_warlock(this_player()->query_name()))
            {
                return "The mural is divided into two sections. The first "
                +"section depicts a kneeling male follower in an ebony-colored "
                +"robe that tries to reach out to someone or something "
                +"unseen. The second section shows an exaggerated silvery "
                +"cord, bond or tether forming between the kneeling follower "
                +"and some blurred undefined entity. You know that this is "
                +"the step where the follower selects his "
                +"patron and becomes a Warlock, similar to what you did.\n";
            }
            
            return "The mural is divided into two sections. The first section "
            +"depicts a kneeling male follower in an ebony-colored robe that tries "
            +"to "
            +"reach out to someone or something unseen. The second section shows "
            +"an exaggerated silvery cord, bond or tether forming between the "
            +"kneeling follower and some blurred undefined entity. You believe "
            +"this scenery is about the creation of the strong bond between "
            +"the follower and his 'selected' patron. The follower becomes a "
            +"Warlock. Judging by the "
            +"surroundings of the follower, the bonding takes place in this "
            +"very chamber.\n";
        }
    }
    
    if (WARLOCK_MASTER->is_occ_warlock(this_player()->query_name()))
    {
        if (this_player()->query_guild_level_occ() >= MIN_PATRON_LEVEL)
        {
            if (WARLOCK_MASTER->is_patr1_warlock(this_player()->query_name())
            || WARLOCK_MASTER->is_patr2_warlock(this_player()->query_name())
            || WARLOCK_MASTER->is_patr3_warlock(this_player()->query_name()))
            {
                return "The mural is divided into two sections. The first "
                +"section depicts a kneeling male follower in an ebony-colored "
                +"robe that tries to reach out to someone or something "
                +"unseen. The second section shows an exaggerated silvery "
                +"cord, bond or tether forming between the kneeling follower "
                +"and some blurred undefined entity. You know that this is "
                +"the step where the follower selects his "
                +"patron and becomes a Warlock, similar to what you did.\n";
            }
            
            return "The mural is divided into two sections. The first section "
            +"depicts a kneeling male follower in an ebony-colored robe that tries "
            +"to "
            +"reach out to someone or something unseen. The second section shows "
            +"an exaggerated silvery cord, bond or tether forming between the "
            +"kneeling follower and some blurred undefined entity. You believe "
            +"this scenery is about the creation of the strong bond between "
            +"the follower and his 'selected' patron. The follower becomes a "
            +"Warlock. Judging by the "
            +"surroundings of the follower, the bonding takes place in this "
            +"very chamber.\n";
        }
    }

    return "The mural is divided into two sections, but none of them "
    +"depict anything comprehensible to you.\n";
}


/*
 * Function name: create_warlock_room
 * Description  : Constructor, redefine this to configure your room
 */
public void
create_warlock_room()
{
    seteuid(getuid());

    add_prop(ROOM_I_INSIDE, 1);

    set_short("In a large dim claystone chamber");
    
    set_long("In a large dim claystone chamber. A large "
    +"purple-glowing teleporation circle engraved into the smooth "
    +"polished ground is the only source of illumination here, which "
    +"gives the large tapestry hanging on the north wall an eerie purple "
    +"glow. A large mural covers the ceiling.\n");
    
    add_item(({"chamber"}),
    "The chamber is quite dim and seems to be excavated by purpose, "
    +"possibly by expanding on some former natural eroded cavity. It "
    +"is nearly featureless except for the large mural, the large "
    +"tapestry and the large teleportation circle.\n");
   
    add_item(({"wall", "walls"}),
    "The walls here are smooth and completely featureless except "
    +"for the large tapestry hanging on the north wall. They reflect "
    +"some of the purple glow emanating from the teleportation "
    +"circle.\n");
    
    add_item(({"ground", "floor"}),
    "The ground is perfectly smooth and features a large engraved "
    +"purple-glowing teleportation circle in the center.\n");
    
    add_item(({"ceiling", "roof"}),
    "The smooth claystone ceiling is barren except for a large mural.\n");
        
    add_item(({"circle", "teleport", "teleportation circle", "field",
    "teleportation field", "teleport circle"}),
    query_destination);
        
    add_item(({"tapestry", "woven tapestry", "large tapestry"}), tapestry);
    
    add_item(({"mural", "large mural", "weird mural", 
    "interesting mural"}), mural);
    
    add_exit(WARLOCK_ROOMS_DIR + "central", "south");

    reset_faerun_room();
}


void
reset_faerun_room()
{
    ::reset_faerun_room();
}


void
do_whispers()
{
    if (WARLOCK_MASTER->is_patr1_warlock(this_player()->query_name()))
    {
        if (WARLOCK_MAPPINGS->query_desecration_power(this_player()->query_name()) == 1)
        {
            this_player()->catch_tell("Your patron, Asmodeus, the Lord of the "
            +"Nine Hells, demands a sacrifice from you in Nessus!\n");
        }
        
        return;
    }
    
    if (WARLOCK_MASTER->is_patr2_warlock(this_player()->query_name()))
    {
        if (WARLOCK_MAPPINGS->query_desecration_power(this_player()->query_name()) == 1)
        {
            this_player()->catch_tell("Your patron, the Great Old One "
            +"Hastur, the King "
            +"in Yellow, demands a sacrifice from you in Carcosa!\n");
        }
        
        return;
    }
    
    if (WARLOCK_MASTER->is_patr3_warlock(this_player()->query_name()))
    {
        if (WARLOCK_MAPPINGS->query_desecration_power(this_player()->query_name()) == 1)
        {
            this_player()->catch_tell("Your patron, Archfey Baba Zirana, "
            +"demands a sacrifice from you in the Feywild!\n");
        }
        
        return;
    }
    
    if (WARLOCK_MASTER->is_lay_warlock(this_player()->query_name()))
    {
        if (this_player()->query_guild_level_lay() >= MIN_PATRON_LEVEL)
        {
            this_player()->catch_tell("In your mind, you hear the rasping voice "
            +"of the Whispess echoing in your mind, saying: Servant, I deemed "
            +"you ready to merge as a Warlock, bound in servitude to even more "
            +"powerful entities than I! You must 'select' a patron! They are "
            +"impatiently awaiting your decision of whom to serve!\n");
            
            return;
        }
    }
    
    if (WARLOCK_MASTER->is_occ_warlock(this_player()->query_name()))
    {
        if (this_player()->query_guild_level_occ() >= MIN_PATRON_LEVEL)
        {
            this_player()->catch_tell("In your mind, you hear the rasping voice "
            +"of the Whispess echoing in your mind, saying: Servant, I deemed "
            +"you ready to merge as a Warlock, bound in servitude to even more "
            +"powerful entities than I! You must 'select' a patron! They are "
            +"impatiently awaiting your decision of whom to serve!\n");
            
            return;
        }
    }
    
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


void
init()
{
    ::init();

    add_action(touch_tapestry, "touch");
    add_action(select_patron, "select");
    add_action(enter_tepcircle, "enter");
    add_action(leave_patron, "abandon");
    add_action(set_destination, "set");
}
