/* /d/Faerun/guilds/warlocks/rooms/patron_1.c
 *
 * Fiend patron room in the guildhall.
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
    if (str == "ritual of the soul" || str == "the ritual of the soul"
    || str == "ritual of soul" || str == "the ritual of soul")
    {     
        if (WARLOCK_MAPPINGS->query_desecration_power(this_player()->query_name()) >= SPELL_END)
        {
            write("You have sufficiently proven your worth to your patron! Hence "
            +"no more rituals are necessary.\n");

            return 1;
        }
    
        if (WARLOCK_MASTER->is_patr1_warlock(this_player()->query_name()))     
        {
            // Can't ritual while on cooldown.
            if (present("rit_cooldown_obj", this_player()))
            {
                write("You feel too weak to perform the ritual of mind "
                +"at this time!\n");
        
                return 1;        
            }
            
            // Warlock is already primed. 
            //if (WARLOCK_MAPPINGS->query_desecration_primer(this_player()->query_name())== 1)
            //{
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
            
                //clone_object(WARLOCK_GUILDDIR 
                //+ "obj/rit_cooldown_obj")->move(this_player(), 1);

                write("You approach the altar as you reside the words of the "
                +"ritual of soul. As you come closer a sense of pure dread "
                +"strikes you. A vision of a tall handsome man with "
                +"protruding red horns from his forehead and eyes that "
                +"shine with infernal crimson power fades into view gazing "
                +"into your soul... searching...\nYou loose all control "
                +"over your limbs and they reach for the black-handled "
                +"sickle upon the altar. You grasp "
                +"the sickle and immediately try to let go, but you climb "
                +"the altar and lay upon it. You feel a sense of "
                +"detachment as you see the ethereal form of yourself "
                +"floating above you, only connected to you with a silvery "
                +"trailing line. Unwillingly, You raise the sickle and "
                +"sever the silvery line!\nFor Asmodeus, the Lord of the "
                +"Nine Hells, you sacrifice a part of your soul! Your body "
                +"start convulsing violently and everything goes "
                +"black...\nYou awaken feeling empty inside and your body "
                +"aches terribly. You raise from the altar and take some "
                +"staggering steps but end up on your knees, in need "
                +"of rest..\n");

            
                tell_room(environment(this_player()), QCTNAME(this_player()) 
                +" walks up the the altar and starts reciting ancient words "
                +"with dark intent. "+QCTNAME(this_player())+" suddenly "
                +"stiffens in the middle of reciting and stares ahead with "
                +"dreadfull eyes, before "+this_player()->query_pronoun()
                +" starts to move mechanically and grasps the black-handled "
                +"sickle from the altar. "+QCTNAME(this_player())+" lays "
                +"down on the altar and screams horribly as "
                +this_player()->query_pronoun()+" raises the sickle and "
                +"makes a jerking horizontal cut in the air just an inch "
                +"above "+this_player()->query_possessive()+" chest as if "
                +"aiming at something invisible!\n"
                +QCTNAME(this_player())+" body starts to convulse "
                +"violently for a few moments before it suddenly stills, "
                +"and then it raises and staggers off the altar, slumping "
                +"to its knees, clearly exhausted!\n", this_player());
                
                RIT1_LOG("log/patron_1_ritual_log",
                "The Warlock " +this_player()->query_name() 
                + " performed a Ritual of the Soul.\n");

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
            //}

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
                WARLOCK_MAPPINGS->set_warspell_19(this_player()->query_name(), 4);

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
    if (str == "engraving" || str == "pentagram")
    {
        if (WARLOCK_MASTER->is_patr1_warlock(this_player()->query_name()))
        {
            write("\n\nSuddenly, you are pulled through a fiery portal and back "
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

    set_short("You are standing on a huge pentagram shaped "
    +"pillar somewhere in Nessus, the Ninth layer of Hell");
    
    set_long("You are standing on a huge pentagram shaped "
    +"pillar somewhere in Nessus, the Ninth layer of Hell, entirely "
    +"surrounded by a vast sea of fire. Far above you and to all "
    +"sides, you see molten reddish walls and ceiling, as if you "
    +"were in the middle of some deep underground volcano. In "
    +"the distance, you hear cries from unknown beasts that "
    +"occupy this realm. The searing updraft causes by the "
    +"fiery sea below makes your skin blister. There is a "
    +"sensation of a dreadful presence in the area, "
    +"particularly near or surrounding the jet-black "
    +"altar that sits in the dead center of "
    +"the pillar. You notice a small engraving "
    +"at the south end of the pillar.\n");

   
    add_item(({"floor", "ground"}),
    "The ground is rough and ash-grey, filled with "
    +"purple-glowing runes going in a circular pattern that spirals "
    +"towards a jet-black in the middle of the pillar. At the southern "
    +"end you see a tiny engraving of a pentagram into the ground.\n");
    
    add_item(({"pillar", "pentagram shaped pillar", "huge pillar"}),
    "The blackened pillar rises fifty feet from the surface of the fiery "
    +"sea like a lonely tower. It has five horizontal edges, conforming "
    +"perfectly to the shape of a pentagram. From point to point, the "
    +"length is approximately thirty feet. In its center surrounded by "
    +"spiraling purple runes, you see a "
    +"jet-black altar.\n");
    
    add_item(({"sea", "sea of fire", "fiery sea", "flame sea"}),
    "As far as the eye can see is a sea of hot searing "
    +"red flames raging wildly.\n");
    
    add_item(({"runes", "rune", "purple runes", "purple-glowing runes"}),
    "The runes start at each of the five tips and move inwards "
    +"in a circle like a serpent towards the altar. They glow "
    +"with a fierce purple light in a language that your mind "
    +"can't even begin to comprehend.\n");
    
    add_item(({"altar", "jet-black altar"}),
    "The altar seems to be made of volcanic glass, and has a "
    +"slight oval form. It is large enough to fit a very large "
    +"humanoid creature. You notice a black-handled sickle in the "
    +"middle of the altar.\n");
    
    add_item(({"engraving", "pentagram"}),
    "The engraving of a pentagram looks like chiseled into the ground at "
    +"the south end of the pillar and measures about ten inches. Maybe "
    +"you can touch it?\n");
    
    add_item(({"sickle", "black-handled sickle"}),
    "A black handle connects to a slightly oversized but perfect "
    +"piece of metal in the shape of a sickle. in the reflective "
    +"surface of the metal, you see yourself, and oddly enough "
    +"a silhouette of yourself outside your reflection. Warlocks "
    +"use this sickle to perform the ritual of the soul, the sacrifice "
    +"to their patron, Asmodeus, the Lord of the Nine Hells.\n");
    
    room_add_object(WARLOCK_OBJ_DIR + "iron_chest");
   
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
            this_player()->catch_tell("\n\nYour patron, Asmodeus, the "
            +"Lord of the Nine Hells, is offering you a pact "
            +"magic gift. May you 'choose' wisely.\n\n");
            
            return;
        }
        
        if (WARLOCK_MAPPINGS->query_desecration_power(this_player()->query_name()) 
        >= FEAR_UNLOCK && !WARLOCK_MAPPINGS->query_warspell_17(this_player()->query_name()))
        {
            this_player()->catch_tell("\n\nYour patron, Asmodeus, the "
            +"Lord of the Nine Hells, is offering you a pact "
            +"magic gift. May you 'choose' wisely.\n\n");
            
            return;
        }
        
        if (WARLOCK_MAPPINGS->query_desecration_power(this_player()->query_name()) 
        >= MAGICSHIELD_UNLOCK && !WARLOCK_MAPPINGS->query_warspell_18(this_player()->query_name()))
        {
            this_player()->catch_tell("\n\nYour patron, Asmodeus, the "
            +"Lord of the Nine Hells, is offering you a pact "
            +"magic gift. May you 'choose' wisely.\n\n");
            
            return;
        }    
        
        if (WARLOCK_MAPPINGS->query_desecration_power(this_player()->query_name()) 
        >= NUKE_UNLOCK && !WARLOCK_MAPPINGS->query_warspell_19(this_player()->query_name()))
        {
            this_player()->catch_tell("\n\nYour patron, Asmodeus, the "
            +"Lord of the Nine Hells, is offering you a pact "
            +"magic gift. May you 'choose' wisely.\n\n");
            
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
    
    //Testfunction - Should be disabled.
    //add_action(do_testytes, "max");
}
