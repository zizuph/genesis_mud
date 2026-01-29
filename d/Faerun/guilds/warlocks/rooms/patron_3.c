/* /d/Faerun/guilds/warlocks/rooms/patron_3.c
 *
 * Patron room in the guildhall.
 * Nerull, 2017
 *
 */

#include "/d/Faerun/defs.h"
#include <stdproperties.h>
#include "../guild.h";

inherit WARLOCK_STD_ROOM;

void
received_gift()
{
    this_player()->catch_tell("\n\nIn return for your sacrifice, your "
    +"patron has granted you a new gift!\n\n");
    
    return;
}


void
offer_pactmagic()
{
    this_player()->catch_tell("\n\nIn return for your sacrifice, your "
    +"patron wishes to offer you a new pact magic spell! You may 'choose' "
    +"one spell of what is offered.\n\n");
    
    return;
}


void
offer_pactmagic_last()
{
    this_player()->catch_tell("\n\nIn return for your sacrifice, your "
    +"patron wishes to offer you the very last pact magic spell! You may 'choose' "
    +"one spell of what is offered.\n\n");
    
    return;
}


// FOR TESTING ONLY
int do_testytest(string str)
{
    
    if (str == "max")
    {
        this_player()->catch_tell("\n\nYou earn the max favour of your Patron for "
        +"testing purposes!\n\n");
        
        WARLOCK_MAPPINGS->set_desecration_power(this_player()->query_name(), 60);
    
        return 1;
    }
    
    if (str == "min")
    {
        this_player()->catch_tell("\n\nYou earn some favour of your Patron for "
        +"testing purposes!\n\n");
        
        WARLOCK_MAPPINGS->set_desecration_power(this_player()->query_name(), 59);
    
        return 1;
    }
    
    return 0;
}


int 
do_ritual(string str)
{
    if (str == "ritual of the blood" || str == "the ritual of the blood" 
    || str == "ritual of blood" || str == "the ritual of blood")
    {
        if (WARLOCK_MAPPINGS->query_desecration_power(this_player()->query_name()) >= SPELL_END)
        {
            write("You have sufficiently proven your worth to your "
            +"patron! Hence "
            +"no more rituals are necessary.\n");

            return 1;
        }
    
        if (WARLOCK_MASTER->is_patr3_warlock(this_player()->query_name()))
        {
            // Can't ritual while on cooldown.
            if (present("rit_cooldown_obj", this_player()))
            {
                write("You feel too weak to perform a ritual at this "
                +"time!\n");
        
                return 1;        
            }
            
            //Warlock is already primed. 
            if (WARLOCK_MAPPINGS->query_desecration_primer(this_player()->query_name())== 1)
            {
                int power = WARLOCK_MAPPINGS->query_desecration_power(this_player()->query_name());
        
                power = power + 1;
                
                if (power > SPELL_END)
                {
                    power = SPELL_END;
                }

                WARLOCK_MAPPINGS->set_desecration_power(this_player()->query_name(), power);
        
                WARLOCK_MAPPINGS->set_desecration_primer(this_player()->query_name(), 0);
            
                setuid();
                seteuid(getuid());
            
                clone_object(WARLOCK_GUILDDIR + "obj/rit_cooldown_obj")->move(this_player(), 1);

                write("You grab the wicked dagger from the rugged stone "
                +"altar and icily carve an ancient rune into your hand! The "
                +"blood that flows from this ritual falls not on the altar "
                +"nor ground, but adheres to the blade of the dagger. Upon "
                +"finishing your rune, you grasp the dagger firmly in both "
                +"hands and hold it above your head. Violently, you stab "
                +"downward into the altar! As the blade pierces the stone "
                +"altar, blood spurts out in all directions. The "
                +"blood begins to boil turning to mist and burning all "
                +"your skin it touches in the process. As quickly as it "
                +"begins it ends. The pain so intense caused you to close "
                +"your eyes. You open them to see the altar as it was "
                +"when you arrived. Your sacrifice was accepted.\n");
            
                tell_room(environment(this_player()), QCTNAME(this_player()) 
                +" grabs the wicked dagger from the rugged stone altar and "
                +"with eyes glazed over begins to carve a deep symbol "
                +"into "+this_player()->query_possessive()
                +" hand! The blood that should fall from "
                +QTNAME(this_player())+" wound instead is pulled up the "
                +"shaft of the blade. As "+QTNAME(this_player())+" finishes "
                +"the symbol, "+this_player()->query_pronoun()+" clutches "
                +"the blade into both hands while lifting it high above "
                +this_player()->query_possessive()+" head. Swiftly, "
                +QTNAME(this_player())+" stabs the blade into the altar!\n"
                +"Blood flies everywhere so heated it turns to mist and "
                +"burns "+QTNAME(this_player())+" skin. You smell burned "
                +"flesh and hair and lose sight of "+QTNAME(this_player())
                +" within the glistening mists of blood. Suddenly, as if "
                +"reality blurred, you see "+QTNAME(this_player())
                +" standing before the altar as if nothing has "
                +"transpired.\n", this_player());
                
                RIT3_LOG("log/patron_3_ritual_log",
                "The Warlock " +this_player()->query_name() 
                + " performed a Ritual of the Blood.\n");
                
                if (WARLOCK_MAPPINGS->query_desecration_power(this_player()->query_name()) == MASK_UNLOCK)
                {
                    set_alarm(1.0, 0.0, &received_gift());
                }
                
                if (WARLOCK_MAPPINGS->query_desecration_power(this_player()->query_name()) == ELDRITCH_SIGHT_UNLOCK)
                {
                    set_alarm(1.0, 0.0, &received_gift());
                }
                
                if (WARLOCK_MAPPINGS->query_desecration_power(this_player()->query_name()) == FALSELIFE_UNLOCK)
                {
                    set_alarm(1.0, 0.0, &received_gift());
                }
                
                if (WARLOCK_MAPPINGS->query_desecration_power(this_player()->query_name()) == REJUVENATION_UNLOCK)
                {
                    set_alarm(1.0, 0.0, &received_gift());
                }
                
                if (WARLOCK_MAPPINGS->query_desecration_power(this_player()->query_name()) == SCRY_UNLOCK)
                {
                    set_alarm(1.0, 0.0, &received_gift());
                }
                
                if (WARLOCK_MAPPINGS->query_desecration_power(this_player()->query_name()) == WARP_REALITY_UNLOCK)
                {
                    set_alarm(1.0, 0.0, &received_gift());
                }
                
                if (WARLOCK_MAPPINGS->query_desecration_power(this_player()->query_name()) == DEPTH_UNLOCK)
                {
                    set_alarm(1.0, 0.0, &received_gift());
                }
                
                if (WARLOCK_MAPPINGS->query_desecration_power(this_player()->query_name()) == INFUSION_UNLOCK)
                {
                    set_alarm(1.0, 0.0, &received_gift());
                }
                
                //---------------- Pact Magic -----------------
                
                if (WARLOCK_MAPPINGS->query_desecration_power(this_player()->query_name()) == SHIELD_UNLOCK)
                {
                    set_alarm(1.0, 0.0, &offer_pactmagic());
                }
                
                if (WARLOCK_MAPPINGS->query_desecration_power(this_player()->query_name()) == FEAR_UNLOCK)
                {
                    set_alarm(1.0, 0.0, &offer_pactmagic());
                }
                
                if (WARLOCK_MAPPINGS->query_desecration_power(this_player()->query_name()) == MAGICSHIELD_UNLOCK)
                {
                    set_alarm(1.0, 0.0, &offer_pactmagic());
                }
                
                if (WARLOCK_MAPPINGS->query_desecration_power(this_player()->query_name()) == NUKE_UNLOCK)
                {
                    set_alarm(1.0, 0.0, &offer_pactmagic_last());
                }
        
                return 1;        
            }

            write("You are not sufficiently prepared to perform any "
            +"ritual here!\n");
        
            return 1;
        }
    
        write("You are not eligible to perform a ritual here.\n");
        
        return 1;        
    }  

    write("Perform what?\n");
        
    return 1;       
}


int
reset_pactmagic(string str)
{
    if (str == "pact magic")
    {
        if (WARLOCK_MAPPINGS->query_desecration_power(this_player()->query_name()) < SHIELD_UNLOCK)
        {
            write("Nothing happens.\n");

            return 1;
        }
        
        if (present("_protect_life_death_object_", this_player()) ||
        present("_protect_earth_water_object_", this_player()) ||
        present("_protect_air_fire_object_", this_player()) ||
        present("_agathys_shield_object", this_player()) ||
        present("_barkskin_object_", this_player()) ||        
        present("_spikes_object_", this_player()))
        {
            write("You must dispel all your defensive "
            +"persistent spells before you can nullify pact magic!\n");
            return 1;
        }

        WARLOCK_MAPPINGS->clean_warspell_16(this_player()->query_name());
        WARLOCK_MAPPINGS->clean_warspell_17(this_player()->query_name());
        WARLOCK_MAPPINGS->clean_warspell_18(this_player()->query_name());
        WARLOCK_MAPPINGS->clean_warspell_19(this_player()->query_name());

        write("You return the Pact Magic back to your patron. You may "
        +"'choose' the gifts again.\n");

        return 1;
    }

    return 0;
}


int
choose_pactmagic(string str)
{
    if (WARLOCK_MAPPINGS->query_desecration_power(this_player()->query_name()) < SHIELD_UNLOCK)
    {
        write("You are not eligible yet for pact magic.\n");

        return 1;
    }
    
    if (WARLOCK_MAPPINGS->query_desecration_power(this_player()->query_name()) >= SHIELD_UNLOCK)
    {
        if (!WARLOCK_MAPPINGS->query_warspell_16(this_player()->query_name()))
        {
            // treashi
            if (str == "treashi")
            {
                WARLOCK_MAPPINGS->set_warspell_16(this_player()->query_name(), 1);

                write("Through your patron, you learn the spell Treashi!\n");

                return 1;
            }
            
            // viehra
            if (str == "viehra")
            {
                WARLOCK_MAPPINGS->set_warspell_16(this_player()->query_name(), 2);

                write("Through your patron, you learn the spell Viehra!\n");

                return 1;
            }

            // ormule
            if (str == "ormule")
            {
                WARLOCK_MAPPINGS->set_warspell_16(this_player()->query_name(), 3);

                write("Through your patron, you learn the spell Ormule!\n");

                return 1;
            }

            write("Your patron offers you a new gift of protection: You may "
            +"'choose' between "
            +"[treashi}, [viehra}, "
            +"or [ormule].\n"
            +"The gift of Treashi: Barkskin, increase skin toughness.\n"
            +"The gift of Viehra:  Armor of Agathys, increase attack evasion.\n"
            +"The gift of Ormule:  Shadowy Spikes, damageshield.\n");

            return 1;
        }
    }

    
    if (WARLOCK_MAPPINGS->query_desecration_power(this_player()->query_name()) >= FEAR_UNLOCK)
    {
        if (!WARLOCK_MAPPINGS->query_warspell_17(this_player()->query_name()))
        {
            if (str == "urhaese")
            {
                WARLOCK_MAPPINGS->set_warspell_17(this_player()->query_name(), 1);

                write("Through your patron, you learn the spell Urhaese!\n");

                return 1;
            }

            if (str == "urnerulla")
            {
                WARLOCK_MAPPINGS->set_warspell_17(this_player()->query_name(), 2);

                write("Through your patron, you learn the spell Urnerulla!\n");

                return 1;
            }

            if (str == "urgashe")
            {
                WARLOCK_MAPPINGS->set_warspell_17(this_player()->query_name(), 3);

                write("Through your patron, you learn the spell Urgashe!\n");

                return 1;
            }

            write("Your patron offers you a new gift: You may 'choose' "
            +"between [urhaese], [urnerulla], "
            +"or [urgashe].\n"
            +"The gift of Urhaese:    Spook Humans and Elves.\n"
            +"The gift of Urnerulla:  Spook Goblins and Dwarves.\n"
            +"The gift of Urgashe:    Spook Hobbits and Gnomes.\n");

            return 1;
        }
    }


    if (WARLOCK_MAPPINGS->query_desecration_power(this_player()->query_name()) >= MAGICSHIELD_UNLOCK)
    {
        if (!WARLOCK_MAPPINGS->query_warspell_18(this_player()->query_name()))
        {
            if (str == "urluir")
            {
                WARLOCK_MAPPINGS->set_warspell_18(this_player()->query_name(), 1);

                write("Through your patron, you learn the spell Urluir!\n");

                return 1;
            }

            if (str == "urvaesa")
            {
                WARLOCK_MAPPINGS->set_warspell_18(this_player()->query_name(), 2);

                write("Through your patron, you learn the spell Urvaesa!\n");

                return 1;
            }

            if (str == "urwem")
            {
                WARLOCK_MAPPINGS->set_warspell_18(this_player()->query_name(), 3);

                write("Through your patron, you learn the spell Urwem!\n");

                return 1;
            }

            write("Your patron offers you a new gift: You may 'choose' "
            +"between "
            +"[urluir], [urvaesa], "
            +"or [urwem].\n"
            +"The gift of Urluir:  Armor of Mist, protect against air and fire magic.\n"
            +"The gift of Urvaesa: Armor of Shadows, protect against life and death magic.\n"
            +"The gift of Urwem:   Reflecting Shroud, protect against earth and water magic.\n");

            return 1;
        }
    }


    if (WARLOCK_MAPPINGS->query_desecration_power(this_player()->query_name()) >= NUKE_UNLOCK)
    {
        if (!WARLOCK_MAPPINGS->query_warspell_19(this_player()->query_name()))
        {
            if (str == "wachiel")
            {
                WARLOCK_MAPPINGS->set_warspell_19(this_player()->query_name(), 1);

                write("Through your patron, you learn the spell Wachiel!\nYou "
                +"have sufficiently proven your worth, hence no more rituals "
                +"are needed!\n");

                return 1;
            }

            if (str == "ngasha")
            {
                WARLOCK_MAPPINGS->set_warspell_19(this_player()->query_name(), 2);

                write("Through your patron, you learn the spell Ngasha!\nYou "
                +"have sufficiently proven your worth, hence no more rituals "
                +"are needed!\n");

                return 1;
            }

            if (str == "heurmun")
            {
                WARLOCK_MAPPINGS->set_warspell_19(this_player()->query_name(), 3);

                write("Through your patron, you learn the spell Heurmun!\nYou "
                +"have sufficiently proven your worth, hence no more rituals "
                +"are needed!\n");

                return 1;
            }

            write("Your patron offers you a new gift: You may 'choose' "
            +"between these offensive spells:"
            +"[wachiel}, [ngasha}, "
            +"or [heurmun].\n"
            +"The gift of Wachiel:  Witchbolt, air-based harm spell.\n"
            +"The gift of Ngasha:   Dream, illusion-based harm spell.\n"
            +"The gift of Heurmun:  Detonate, Earth-based harm spell.\n");

            return 1;
        }
    }
    
    if (WARLOCK_MAPPINGS->query_desecration_power(this_player()->query_name()) >= SPELL_END)
    {
        write("Your patron is not willing to provide you "
        +"with more gifts no more!\n");

        return 1;
    }

    write("Your patron has nothing more to offer you...for now!\n");

    return 1;
}


/*
* Function name: do_port_home
* Description  : Sets up what happens when a member touches a symbol/sign
*/
int
do_port_home(string str)
{
    if (str == "rune" || str == "glowing rune")
    {
        if (WARLOCK_MASTER->is_patr3_warlock(this_player()->query_name()))
        {
            write("\n\nSuddenly, you are teleported back "
            +"to the temple!\n\n");

            tell_room(WARLOCK_ROOMS_DIR + "patron", QCNAME(this_player())
            + " suddenly is!\n", this_player());

            tell_room(environment(this_object()), QCTNAME(this_player())
            + " fades away.\n", this_player());

            this_player()->move_living("M", WARLOCK_ROOMS_DIR + "patron", 1);

            return 1;
        }
        
        return 0;
    }
      
    return 0;
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
    
    add_prop(ROOM_M_NO_TELEPORT_TO, 1);
    add_prop(ROOM_M_NO_TELEPORT_FROM, 1);
    add_prop(ROOM_M_NO_TELEPORT, 1);

    set_short("Inside an eerie wooden hut somewhere in the Feywild");
    
    set_long("You are inside an eerie wooden hut somewhere in the "
    +"Feywild. It's slightly illuminated by only the flickering light "
    +"of a black candle "
    +"in the middle of a wooden table next to the potbellied stove. "
    +"At the southwestern corner you notice a worn down wooden "
    +"bed, with a quilt of woven leaves and a pillow stuffed with moss. "
    +"There are a window in each wall that are shuttered tightly, except "
    +"the one next to the door to the south. Skulls and bones from various "
    +"animals and humanoid infants hangs from the ceiling by thin hair like "
    +"threads. At the north wall there is a large tapestry with a rugged "
    +"stone altar at its base. You notice a tiny rune carved into the "
    +"wooden board next to the door.\n");
    
    add_item(({"black candle", "candle"}),
    "The candle consists of some blackened wax of sorts, not entirely "
    +"unlike dried blood in appearance. It illuminates the small "
    +"cabin while giving away a rather peculiar odor...\n");
    
    add_item(({"skulls", "bones"}),
    "These are various bones and tiny skulls from infant elves "
    +"humans and other various animals. They hang together like chains "
    +"supported by thin hairlike threads. It's quite macabre.\n");
    
     add_item(({"wooden table", "table"}),
    "This simple table is made of a couple of wooden boards roughly "
    +"nailed together with the help of two underlying wooden "
    +"beams. It is entirely clean with the exception of the "
    +"lit black candle sitting on top it.\n");
    
    add_item(({"wooden bed", "bed"}),
    "The bed is just a simple frame of branches that is "
    +"tied together into a mesh-like structure. You see a "
    +"quilt and a pillow on it.\n");
    
    add_item(({"quilt"}),
    "Woven together with fine hair like threads and dead "
    +"leaves, the quilt will be able to keep someone warm "
    +"during the night.\n");
    
    add_item(({"pillow"}),
    "The pillow seems to be made of fine pale smooth hide, "
    +"not entirely unlike the skin of a human infant. It is "
    +"stuffed with some moss to give comfort to a weary head "
    +"during the night.\n");
    
    add_item(({"large stove", "large potbellied stove",
    "potbellied stove", "stove"}),
    "The large potbellied stove is made of cast "
    +"iron, and is shut. While it's not in use, you still "
    +"sense the stink of burned human flesh emanating from it, "
    +"filling the cabin.\n");
    
    add_item(({"door"}),
    "Four wooden boards make up this relatively simple door and is "
    +"blocking the entrance to the south. It "
    +"hangs on something resembling human sinew and looks rather "
    +"unsteady and fragile, until you notice a faint shimmering "
    +"that covers it.\n");
    
    add_item(({"shimmering", "faint shimmering"}),
    "It's like a forcewall or an invisible object that bends the "
    +"light in an unnatural fashion around the door. It looks rather "
    +"impassable. On the wall right next to the door, you spot a "
    +"glowing rune.\n");
  
    add_item(({"rune", "glowing rune"}),
    "This tiny rune glows fiercely with magical powers, and has the "
    +"shape as an 'Y'. It is "
    +"carved into the wooden board next to the door. You wonder "
    +"if you can touch it.\n");
    
    add_item(({"window", "windows", "shutters"}),
    "There is a window in each wall of the cabin with simple wooden "
    +"shutters. The window to the south next to the door is "
    +"wide open, and you see various trees and branches, accompanied "
    +"with a little speck of stars in a dawn-like sky.\n");
    
    add_item(({"rugged stone altar", "stone altar", "altar"}),
    "It is placed at the base of the large tapestry, and resembles "
    +"a rough slab or a square-like stone. Hint of red blood "
    +"stains prides the entire surface of the altar, and in the "
    +"center you see a wicked dagger.\n");
    
    add_item(({"wicked dagger", "dagger"}),
    "This blade is triangular in shape and prided with tiny talon-like"
    +"hooks along the edges. A simple wooden handle is tied to it "
    +"with fine hair like threads. Patrons of Baba Zirana use this "
    +"dagger to perform the ritual of the blood.\n");
    
    add_item(({"large tapestry", "tapestry"}),
    "Woven together by fine human hair, the tapestry depicts a "
    +"beautiful naked maiden holding a wicked "
    +"dagger and a human infant over a bubbling cauldron. Her smiling lips "
    +"are drenched in infant blood while her gorgeous eyes seem "
    +"to be fixed at...You!\n");
    
    add_item(({"wall", "walls"}),
    "The walls are made of various rugged wooden boards. There is "
    +"nothing special about them.\n");
    
    add_item(({"roof", "ceiling"}),
    "Like the walls, the ceiling consists of rough wooden boards, "
    +"forming a shelter from the environments.\n");
    
    add_item(({"magic rocks", "rocks", "red-glowing rocks"}),
    "The rocks glow red with fiery magic, and is seated under "
    +"the huge iron cauldron in a circular pattern, giving "
    +"away constant heat.\n");
    
    add_item(({"ground", "floor"}),
    "The naked floor is made of dry wooden boards.\n");
    
    room_add_object(WARLOCK_OBJ_DIR + "stone_chest");
        
    reset_faerun_room();
}


void
reset_faerun_room()
{
    ::reset_faerun_room();
}


void
do_offer_pactmagic()
{
    if (WARLOCK_MASTER->is_patr1_warlock(this_player()->query_name()))
    {
        if (WARLOCK_MAPPINGS->query_desecration_power(this_player()->query_name()) 
        >= SHIELD_UNLOCK && !WARLOCK_MAPPINGS->query_warspell_16(this_player()->query_name()))
        {
            this_player()->catch_tell("\n\nYour patron, the Archfey Baba "
            +"Zirana, is offering you a pact magic gift. May "
            +"you 'choose' wisely.\n\n");
            
            return;
        }
        
        if (WARLOCK_MAPPINGS->query_desecration_power(this_player()->query_name()) 
        >= FEAR_UNLOCK && !WARLOCK_MAPPINGS->query_warspell_17(this_player()->query_name()))
        {
            this_player()->catch_tell("\n\nYour patron, the Archfey Baba "
            +"Zirana, is offering you a pact magic gift. May "
            +"you 'choose' wisely.\n\n");
            
            return;
        }
        
        if (WARLOCK_MAPPINGS->query_desecration_power(this_player()->query_name()) 
        >= MAGICSHIELD_UNLOCK && !WARLOCK_MAPPINGS->query_warspell_18(this_player()->query_name()))
        {
            this_player()->catch_tell("\n\nYour patron, the Archfey Baba "
            +"Zirana, is offering you a pact magic gift. May "
            +"you 'choose' wisely.\n\n");
            
            return;
        }    
        
        if (WARLOCK_MAPPINGS->query_desecration_power(this_player()->query_name()) 
        >= NUKE_UNLOCK && !WARLOCK_MAPPINGS->query_warspell_19(this_player()->query_name()))
        {
            this_player()->catch_tell("\n\nYour patron, the Archfey Baba "
            +"Zirana, is offering you a pact magic gift. May "
            +"you 'choose' wisely.\n\n");
            
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
        set_alarm(2.0, 0.0, &do_offer_pactmagic());
    }
}


void
init()
{
    ::init();

    add_action(reset_pactmagic, "nullify");
    add_action(choose_pactmagic, "choose");
    
    add_action(do_ritual, "perform");
    add_action(do_port_home, "touch");
    
    //Testfunction - should be disabled when live.
    //add_action(do_testytes, "max");
}
