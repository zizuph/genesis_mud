/* /d/Faerun/guilds/vampires/rooms/crypt.c
 *
 * Nerull 2021
 *
 */

inherit "/d/Faerun/guilds/vampires/rooms/std/vampires_std_room";

#include "/d/Faerun/defs.h"
#include <stdproperties.h>
#include "../guild.h";

string segment1()
{
    if (this_player()->query_race() != "human")
    {
        return "Strange as it may be, your mind grinds to a "
        +"halt when you try to understand what it means. You "
        +"suspect there is a magical ward or blockade that "
        +"hinder your mind to interpret the segment.\n";
    }
    
    if (this_player()->query_guild_name_race != 0)
    {
        return "Strange as it may be, your mind grinds to a "
        +"halt when you try to understand what it means. You "
        +"suspect there is a magical ward or blockade that "
        +"hinder your mind to interpret the segment.\n";
    }
    
    if (this_player()->query_guild_name_layman != 0)
    {
        return "Strange as it may be, your mind grinds to a "
        +"halt when you try to understand what it means. You "
        +"suspect there is a magical ward or blockade that "
        +"hinder your mind to interpret the segment.\n";
    }
    
    if (VAMPIRES_MAPPINGS->query_vampire_seeker(this_player()->query_name()) == 7)
    {
        return "Whosover reads this archaic text, provided they are "
           +"of human race and no racial nor layman affiliations, "
           +"has passed the trials that "
           +"were laid down eons past, and has proven themselves fit for "
           +"servitude under my ruthless thumb as a "
           +"Vampire Spawn. However, before a life is cast into "
           +"the abyss of unending night, the gravity of the decision must "
           +"be weighed and ancient knowledge must be brought to bare for "
           +"complete understanding...\n";
    }
    
    return "Strange as it may be, your mind grinds to a "
        +"halt when you try to understand what it means. You "
        +"suspect there is a magical ward or blockade that "
        +"hinder your mind to interpret the segment.\n";
}


string segment2()
{
    if (this_player()->query_race() != "human")
    {
        return "Strange as it may be, your mind grinds to a "
        +"halt when you try to understand what it means. You "
        +"suspect there is a magical ward or blockade that "
        +"hinder your mind to interpret the segment.\n";
    }
    
    if (this_player()->query_guild_name_race != 0)
    {
        return "Strange as it may be, your mind grinds to a "
        +"halt when you try to understand what it means. You "
        +"suspect there is a magical ward or blockade that "
        +"hinder your mind to interpret the segment.\n";
    }
    
    if (this_player()->query_guild_name_layman != 0)
    {
        return "Strange as it may be, your mind grinds to a "
        +"halt when you try to understand what it means. You "
        +"suspect there is a magical ward or blockade that "
        +"hinder your mind to interpret the segment.\n";
    }
    
    if (VAMPIRES_MAPPINGS->query_vampire_seeker(this_player()->query_name()) == 7)
    {   
        return "The accursed daystar! Know this - the sun will be an "
        +"unrelenting and everlasting menace, hounding your every "
        +"step. Should one of the Spawns of Vampires be consumed "
        +"by the rays of the sun, they are and will be forever unmade "
        +"and PERMANENTLY DESTROYED! From this, "
        +"there is no return and it is up to each Spawn to develop and "
        +"discover their own ways to survive and avoid this "
        +"immutable end.\n";
    }
    
    return "Strange as it may be, your mind grinds to a "
        +"halt when you try to understand what it means. You "
        +"suspect there is a magical ward or blockade that "
        +"hinder your mind to interpret the segment.\n";
}


string segment3()
{
    if (this_player()->query_race() != "human")
    {
        return "Strange as it may be, your mind grinds to a "
        +"halt when you try to understand what it means. You "
        +"suspect there is a magical ward or blockade that "
        +"hinder your mind to interpret the segment.\n";
    }
    
    if (this_player()->query_guild_name_race != 0)
    {
        return "Strange as it may be, your mind grinds to a "
        +"halt when you try to understand what it means. You "
        +"suspect there is a magical ward or blockade that "
        +"hinder your mind to interpret the segment.\n";
    }
    
    if (this_player()->query_guild_name_layman != 0)
    {
        return "Strange as it may be, your mind grinds to a "
        +"halt when you try to understand what it means. You "
        +"suspect there is a magical ward or blockade that "
        +"hinder your mind to interpret the segment.\n";
    }
    
    if (VAMPIRES_MAPPINGS->query_vampire_seeker(this_player()->query_name()) == 7)
    {           
        return "Throughout the years, I have allowed numerous myths to "
        +"perpetuate and thus cloud the truths regarding Vampire "
        +"kind. Unfortunately, the myths surrounding coffins are not "
        +"untrue. Coffins are a necessity to us as a solace and safe "
        +"harbor, but safety is an illusion! Should the coffin of a "
        +"Vampire Spawn be found and desecrated while the Spawn "
        +"slumbers within, the Spawn will be forever unmade and "
        +"PERMANENTLY DESTROYED.\n";
    }
    
    return "Strange as it may be, your mind grinds to a "
        +"halt when you try to understand what it means. You "
        +"suspect there is a magical ward or blockade that "
        +"hinder your mind to interpret the segment.\n";
}


string segment4()
{
    if (this_player()->query_race() != "human")
    {
        return "Strange as it may be, your mind grinds to a "
        +"halt when you try to understand what it means. You "
        +"suspect there is a magical ward or blockade that "
        +"hinder your mind to interpret the segment.\n";
    }
    
    if (this_player()->query_guild_name_race != 0)
    {
        return "Strange as it may be, your mind grinds to a "
        +"halt when you try to understand what it means. You "
        +"suspect there is a magical ward or blockade that "
        +"hinder your mind to interpret the segment.\n";
    }
    
    if (this_player()->query_guild_name_layman != 0)
    {
        return "Strange as it may be, your mind grinds to a "
        +"halt when you try to understand what it means. You "
        +"suspect there is a magical ward or blockade that "
        +"hinder your mind to interpret the segment.\n";
    }
    
    if (VAMPIRES_MAPPINGS->query_vampire_seeker(this_player()->query_name()) == 7)
    {           
        return "The complexities of Blood will be revealed to a new Spawn "
        +"the moment they enter service unto me. The nature of thirst "
        +"however, is of far greater concern to the unmotivated and "
        +"untried. The Spawn who ignores their thirst, will never "
        +"survive to ascension for it will ceaselessly persist, even "
        +"through slumber, be it one hour or one century, weakening "
        +"with each passing moment, approaching ever closer "
        +"to the threshold of destruction. Spawn must feed!\n";
    }
    
    return "Strange as it may be, your mind grinds to a "
        +"halt when you try to understand what it means. You "
        +"suspect there is a magical ward or blockade that "
        +"hinder your mind to interpret the segment.\n";
}


string segment5()
{
    if (this_player()->query_race() != "human")
    {
        return "Strange as it may be, your mind grinds to a "
        +"halt when you try to understand what it means. You "
        +"suspect there is a magical ward or blockade that "
        +"hinder your mind to interpret the segment.\n";
    }
    
    if (this_player()->query_guild_name_race != 0)
    {
        return "Strange as it may be, your mind grinds to a "
        +"halt when you try to understand what it means. You "
        +"suspect there is a magical ward or blockade that "
        +"hinder your mind to interpret the segment.\n";
    }
    
    if (this_player()->query_guild_name_layman != 0)
    {
        return "Strange as it may be, your mind grinds to a "
        +"halt when you try to understand what it means. You "
        +"suspect there is a magical ward or blockade that "
        +"hinder your mind to interpret the segment.\n";
    }
    
    if (VAMPIRES_MAPPINGS->query_vampire_seeker(this_player()->query_name()) == 7)
    {           
        return "The reward of patience is strength. Strength cannot be "
        +"hastened in its development and can only swell with the passage "
        +"of time. Restless souls who find the burden of the hourglass "
        +"too hefty are doomed to destruction.\n";
    }
    
    return "Strange as it may be, your mind grinds to a "
        +"halt when you try to understand what it means. You "
        +"suspect there is a magical ward or blockade that "
        +"hinder your mind to interpret the segment.\n";
}


string segment6()
{
    if (this_player()->query_race() != "human")
    {
        return "Strange as it may be, your mind grinds to a "
        +"halt when you try to understand what it means. You "
        +"suspect there is a magical ward or blockade that "
        +"hinder your mind to interpret the segment.\n";
    }
    
    if (this_player()->query_guild_name_race != 0)
    {
        return "Strange as it may be, your mind grinds to a "
        +"halt when you try to understand what it means. You "
        +"suspect there is a magical ward or blockade that "
        +"hinder your mind to interpret the segment.\n";
    }
    
    if (this_player()->query_guild_name_layman != 0)
    {
        return "Strange as it may be, your mind grinds to a "
        +"halt when you try to understand what it means. You "
        +"suspect there is a magical ward or blockade that "
        +"hinder your mind to interpret the segment.\n";
    }
    
    if (VAMPIRES_MAPPINGS->query_vampire_seeker(this_player()->query_name()) == 7)
    {           
        return "Know that the path of the Vampire Spawn is a finite one and "
        +"can only be traversed for a limited time. Vampire "
        +"Spawns either persist through the trials and evolve into "
        +"full Vampires, or they are destroyed outright by me. To "
        +"traverse this road is to devote oneself to the rigors "
        +"and demands required, or be discarded entirely.\n";
    }
    
    return "Strange as it may be, your mind grinds to a "
        +"halt when you try to understand what it means. You "
        +"suspect there is a magical ward or blockade that "
        +"hinder your mind to interpret the segment.\n";
}


string segment7()
{
    if (this_player()->query_race() != "human")
    {
        return "Strange as it may be, your mind grinds to a "
        +"halt when you try to understand what it means. You "
        +"suspect there is a magical ward or blockade that "
        +"hinder your mind to interpret the segment.\n";
    }
    
    if (this_player()->query_guild_name_race != 0)
    {
        return "Strange as it may be, your mind grinds to a "
        +"halt when you try to understand what it means. You "
        +"suspect there is a magical ward or blockade that "
        +"hinder your mind to interpret the segment.\n";
    }
    
    if (this_player()->query_guild_name_layman != 0)
    {
        return "Strange as it may be, your mind grinds to a "
        +"halt when you try to understand what it means. You "
        +"suspect there is a magical ward or blockade that "
        +"hinder your mind to interpret the segment.\n";
    }
    
    if (VAMPIRES_MAPPINGS->query_vampire_seeker(this_player()->query_name()) == 7)
    {           
        return "I am an extremely jealous and biased vampire. If any are to "
       +"serve me to the levels that I demand and are required, there "
       +"must be no distraction of purpose. aAny Spawn who "
       +"have managed to survive to the point of ascention have the option to "
       +"distance themselves from any occupational or part-time "
       +"employment and any claimed blood-ties that may inhibit full "
       +"service. Granted, such spawn may remain at that position indefinitely.\n";
    }
    
    return "Strange as it may be, your mind grinds to a "
        +"halt when you try to understand what it means. You "
        +"suspect there is a magical ward or blockade that "
        +"hinder your mind to interpret the segment.\n";
}


string segment8()
{
    if (this_player()->query_race() != "human")
    {
        return "Strange as it may be, your mind grinds to a "
        +"halt when you try to understand what it means. You "
        +"suspect there is a magical ward or blockade that "
        +"hinder your mind to interpret the segment.\n";
    }
    
    if (this_player()->query_guild_name_race != 0)
    {
        return "Strange as it may be, your mind grinds to a "
        +"halt when you try to understand what it means. You "
        +"suspect there is a magical ward or blockade that "
        +"hinder your mind to interpret the segment.\n";
    }
    
    if (this_player()->query_guild_name_layman != 0)
    {
        return "Strange as it may be, your mind grinds to a "
        +"halt when you try to understand what it means. You "
        +"suspect there is a magical ward or blockade that "
        +"hinder your mind to interpret the segment.\n";
    }
    
    if (VAMPIRES_MAPPINGS->query_vampire_seeker(this_player()->query_name()) == 7)
    {           
        return "For centuries uncounted I have been an apex predator, hunting "
       +"as I deem fit, bending all to my desires. Vampire Spawns are "
       +"not as cunning or as seasoned as I am and thus should use "
       +"extreme caution keep the true nature of their being secret "
       +"from all who would attempt to turn them into prey unto utter "
       +"destruction.\n";
    }
    
    return "Strange as it may be, your mind grinds to a "
        +"halt when you try to understand what it means. You "
        +"suspect there is a magical ward or blockade that "
        +"hinder your mind to interpret the segment.\n";
}


/*string segment9()
{
    if (this_player()->query_race() != "human")
    {
        return "Strange as it may be, your mind grinds to a "
        +"halt when you try to understand what it means. You "
        +"suspect there is a magical ward or blockade that "
        +"hinder your mind to interpret the segment.\n";
    }
    
    if (this_player()->query_guild_name_race != 0)
    {
        return "Strange as it may be, your mind grinds to a "
        +"halt when you try to understand what it means. You "
        +"suspect there is a magical ward or blockade that "
        +"hinder your mind to interpret the segment.\n";
    }
    
    if (this_player()->query_guild_name_layman != 0)
    {
        return "Strange as it may be, your mind grinds to a "
        +"halt when you try to understand what it means. You "
        +"suspect there is a magical ward or blockade that "
        +"hinder your mind to interpret the segment.\n";
    }
    
    if (VAMPIRES_MAPPINGS->query_vampire_seeker(this_player()->query_name()) == 7)
    {           
        return "I offer two main paths of existence - apex vampirism and "
       +"timeless vampirism. The apex kind functions as like all "
       +"other guild affiliations, and are to be considered a kind "
       +"that falls under the 'norm'. However, the timeless kind is different - "
       +"Your true stature will be perpetually be frozen, there will "
       +"be no rewards for slaying nor herbing that will effect "
       +"it, and strenght will be only gained by time. Doing quests "
       +"however will work as normal. Death "
       +"will not affect your stature, but sting you in a different "
       +"way, should you succumb to non-regenerative wounds. Only through "
       +"proper aging will you notice your stature to increase. Should you "
       +"be permanently destroyed, for whatever reason, any progression "
       +"made will be null and void, and you will be set back to your "
       +"original stature.\n";
    }
    
    return "Strange as it may be, your mind grinds to a "
        +"halt when you try to understand what it means. You "
        +"suspect there is a magical ward or blockade that "
        +"hinder your mind to interpret the segment.\n";
}*/


string segment9()
{
    if (this_player()->query_race() != "human")
    {
        return "Strange as it may be, your mind grinds to a "
        +"halt when you try to understand what it means. You "
        +"suspect there is a magical ward or blockade that "
        +"hinder your mind to interpret the segment.\n";
    }
    
    if (this_player()->query_guild_name_race != 0)
    {
        return "Strange as it may be, your mind grinds to a "
        +"halt when you try to understand what it means. You "
        +"suspect there is a magical ward or blockade that "
        +"hinder your mind to interpret the segment.\n";
    }
    
    if (this_player()->query_guild_name_layman != 0)
    {
        return "Strange as it may be, your mind grinds to a "
        +"halt when you try to understand what it means. You "
        +"suspect there is a magical ward or blockade that "
        +"hinder your mind to interpret the segment.\n";
    }
    
    if (VAMPIRES_MAPPINGS->query_vampire_seeker(this_player()->query_name()) == 7)
    {           
       return "These glyphs have been collated too educate and warn. I do "
       +"not suffer creatures of weak constitutions or low "
       +"intellect; these beings serve adequately as food. Removing "
       +"oneself, eternally, from the sun is not an advised existence "
       +"for the weak-willed or impatient. Rewards will be few but "
       +"the demands will be enormous compounded with the everpresent "
       +"risk of utter and complete destruction. Consider all of "
       +"these warnings well and to continue, simply <accept offer>. "
       +"Thence, your journey begins under my ever-watchful gaze "
       +"and should your "
       +"perseverance endure, I will seek you in one of the numerous "
       +"graveyards "
       +"throughout the realms. After utterance, there is no "
       +"return. If you have a change of "
       +"heart, <reject the offer> at this time. Now, mortal, "
       + "DECIDE!\n";
    }
    
    return "Strange as it may be, your mind grinds to a "
        +"halt when you try to understand what it means. You "
        +"suspect there is a magical ward or blockade that "
        +"hinder your mind to interpret the segment.\n";
}


/*
 * Function name: create_warlock_room
 * Description  : Constructor, redefine this to configure your room
 */

public void
create_vampires_room()
{
    seteuid(getuid());
    
    add_prop(ROOM_I_INSIDE, 1);
    add_prop(ROOM_I_LIGHT, 0);

    set_short("An ancient and decrepit crypt");
    
    set_long("An ancient and decrepit crypt with high vaulted "
       +"ceilings spilling into an ocean of darkness invites "
       +"your senses to explore. Around the room are four "
       +"strategically placed pillars, doubtlessly positioned to "
       +"ensure the integrity of the crypt endures the passage "
       +"of time, unmarred. The walls throughout the crypt are "
       +"devoid of any marking or ornament save the large mural "
       +"that covers nearly the entirety of the north wall. "
       +"It is likely that the light of the sun has not touched "
       +"these surfaces for ages upon ages.\n");
    
    add_item(({"walls" }),
        "The walls of of the crypt belie centuries of disuse and "
        +"are bereft of any discernable markings except for the "
        +"immense mural on the north wall.\n");

    add_item(({"north wall", "wall" }),
        "Completely dissimilar to the other walls of the crypt, the "
        +"north wall has an immense mural covering its entirety.\n");

    add_item(({"pillar", "pillars", "stone", "column", "columns"  }),
        "Mighty stone columns are erected here to inhibit the "
        +"collapse of this ancient crypt as time uncounted continues "
        +"to press its will.\n");
           
    add_item(({"mural", "large mural" }),
        "An expansive collection of spiraling glyphs encompass the "
        +"entirety of the north wall. Upon closer inspection, the "
        +"movement of the glyphs is not random at all, but instead "
        +"move in a synchronous pattern that reveal a clear and "
        +"distinct separation of segments. There are nine segments "
        +"in total, all scribed in a deep reddish hue set upon a "
        +"beige background. Historical lore might suggest this "
        +"to be a codex of reference, preserved throughout time.\n");
                      
    add_item(({"segment", "segments", "glyphs", "glyph", "codex" }),
        "The spiraling glyphs are separated into different and "
        +"distinct segments. There are nine total segments that "
        +"can be examined.\n");
                      
    add_item(({"first segment" }), segment1);
                      
    add_item(({"second segment" }), segment2);
                      
    add_item(({"third segment" }), segment3);
                      
    add_item(({"fourth segment" }),segment4);
                      
    add_item(({"fifth segment" }),segment5);
                      
    add_item(({"sixth segment"}), segment6);
                      
    add_item(({"seventh segment" }), segment7);
                      
    add_item(({"eighth segment" }), segment8);
       
    add_item(({"ninth segment" }), segment9);
                  
    //add_item(({"tenth segment" }), segment10);
       
    add_exit("/d/Faerun/underdark/dark_dom/rooms/tu55", "south");
    
    reset_faerun_room();
}


int do_accept(string str)
{
    //if (str == "apex spawn")
    if (str == "offer")
    {
        if (VAMPIRES_MAPPINGS->query_vampire_seeker(this_player()->query_name()) == 7)
        {   
            if (this_player()->query_race() != "human")
            {
                write("According to the first segment of the glyphs, "
                +"only humans can accept this offer.\n");
                
                return 1;
            }
            
            if (this_player()->query_guild_name_race != 0)
            {
                write("According to the first segment, you "
                +"can't have any racial affiliations.\n");
                
                return 1;
            }
            
            if (this_player()->query_guild_name_layman != 0)
            {
               write("According to the first segment, you "
                +"can't have any layman affiliations.\n");
                
                return 1;
            }
            
            // 8 is apex vampire, 9 is Timeless vampire        
            VAMPIRES_MAPPINGS->set_vampires_seeker(this_player()->query_name(), 8);
            
            write("You silently utter 'I accept'. Realizing that you now "
            +"have accepted the offer, you start to think about which "
            +"graveyard "
            +"to search in order to find this vampire Vorador...your new Sire and "
            +"Master.\nSuddenly, your feet starts to walk south.\n");
            
            this_player()->command("south");
            
            ACCEPTDENY_LOG("acceptdeny_log",
            "The investigator " +this_player()->query_name() 
            +" has accepted the terms to join the vampire spawns (apex).\n");
            
            return 1;
        }     
    }
    
    /*if (str == "timeless spawn")
    {
        if (VAMPIRES_MAPPINGS->query_vampire_seeker(this_player()->query_name()) == 7)
        {   
            if (this_player()->query_race() != "human")
            {
                write("According to the first segment of the glyphs, "
                +"only humans can accept this offer.\n");
                
                return 1;
            }
            
            if (this_player()->query_guild_name_race != 0)
            {
                write("According to the seventh segment, having "
                +"racial affiliations will not be accepted.\n");
                
                return 1;
            }
            
            if (this_player()->query_guild_name_layman != 0)
            {
                write("According to the seventh segment, having "
                +"layman affiliations will not be accepted.\n");
                
                return 1;
            }
            
            // 8 is apex vampire, 9 is Timeless vampire        
            VAMPIRES_MAPPINGS->set_vampires_seeker(this_player()->query_name(), 9);
            
            write("You silently utter 'I accept'. Realizing that you now "
            +"have accepted the offer, you start to think about which "
            +"graveyard "
            +"to search in order to find this vampire Vorador...your new Sire and "
            +"Master.\nSuddenly, your feet starts to walk south.\n");
            
            this_player()->command("south");
            
            ACCEPTDENY_LOG("acceptdeny_log",
            "The investigator " +this_player()->query_name() 
            +" has accepted the terms to join the vampire spawns (timeless).\n");
            
            return 1;
        }     
    }*/
    
    return 0;
}


int do_reject(string str)
{
    if (str == "the offer" || str == "offer")
    {
        if (VAMPIRES_MAPPINGS->query_vampire_seeker(this_player()->query_name()) == 7)
        {
            VAMPIRES_MAPPINGS->clean_vampire_seeker(this_player()->query_name());
            
            write("You silently reject the offer. For a moment, you "
            +"feel slightly dizzy, but it passes.\nYou have voided "
            +"your chance to serve as a Vampire Spawn under the "
            +"vampire Vorador!\nSuddenly, your feet starts to walk south.\n");
            
            this_player()->command("south");
            
            ACCEPTDENY_LOG("acceptdeny_log",
            "The investigator " +this_player()->query_name() 
            +" has denied the terms to join the vampire spawns.\n");
            
            return 1;
        }
        
        write("You silently reject the offer, though nothing happens.\n");

        return 1;       
    }
    
    return 0;
}


void
do_seekerclean()
{  
    seteuid(getuid());
    
    if (present("seeker_clean_obj", this_player()))
    {   
        return;
    }
    
    clone_object(VAMPIRES_GUILD_DIR 
        + "obj/seeker_clean_obj")->move(this_player(), 1);
        
    this_player()->catch_tell("You feel you are being watched from "
    +"afar. This unholy chamber will only tolerate your presence for "
    +"approximately a couple of days.\n");
    
    return;
}


void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);
    
    if (interactive(ob))
    {
        set_alarm(1.0, 0.0, &do_seekerclean());
    }
}


void
reset_faerun_room()
{
    ::reset_faerun_room();
}


void
init()
{
    ::init();

    add_action(do_accept, "accept");
    add_action(do_reject, "reject");
}

