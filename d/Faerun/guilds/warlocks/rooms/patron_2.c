/* /d/Faerun/guilds/warlocks/rooms/patron_2.c
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
    if (str == "ritual of the mind" || str == "the ritual of the mind"
    || str == "ritual of mind" || str == "the ritual of mind")
    {   
        if (WARLOCK_MAPPINGS->query_desecration_power(this_player()->query_name()) >= SPELL_END)
        {
            write("You have sufficiently proven your worth to your patron! Hence "
            +"no more rituals are necessary.\n");

            return 1;
        }
    
        if (WARLOCK_MASTER->is_patr2_warlock(this_player()->query_name()))     
        {
            // Can't ritual while on cooldown.
            if (present("rit_cooldown_obj", this_player()))
            {
                write("You feel too weak to perform the ritual of mind "
                +"at this time!\n");
        
                return 1;        
            }
            
            // Warlock is already primed. 
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
            
                clone_object(WARLOCK_GUILDDIR 
                + "obj/rit_cooldown_obj")->move(this_player(), 1);

                write("You raise your arms and stare into the abyss of the central "
                +"black star! Your mind starts to wander, and you feel as if a "
                +"part of your mind is fractured, vanishing into the gaping "
                +"void above you of which there is no return! You try to "
                +"scream, but no sound is emitted. Suddenly, from the void, "
                +"time and space, you see a brief vision of a slender yellow-robed "
                +"terrifying figure with a pallid mask facing you! Images of "
                +"tortured souls, people collapsing in utter terror and madness and "
                +"endless brutal carnage runs through your mind in split "
                +"seconds, forever scarring your sanity! You blink, and "
                +"it's all over. In your fractured mind, you know your sacrifice was "
                +"accepted.\n");

                tell_room(environment(this_player()), QCTNAME(this_player()) 
                +" raises "+this_player()->query_possessive()+" hands into "
                +"the sky towards the central black star and starts to mumble with a "
                +"blank dreadfilled stare!\n"
                +QCTNAME(this_player())+" seems to be terrified and absentminded for "
                +"only a brief moment.\n", this_player());
                
                RIT2_LOG("log/patron_2_ritual_log",
                "The Warlock " +this_player()->query_name() 
                + " performed a Ritual of the Mind.\n");
                
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
    if (str == "sign" || str == "yellow sign" || str == "the yellow sign")
    {    
        if (WARLOCK_MASTER->is_patr2_warlock(this_player()->query_name()))
        {
            write("\n\nSuddenly, you are pulled through time and space back"
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

    set_short("You are at a plateau on top of a roofless black "
    +"tower in the lost city of Carcosa");
    
    set_long("You are at a plateau on top of a roofless black "
    +"tower in the lost city of Carcosa. It has an "
    +"circular form and reflects the light from the stars like a giant "
    +"mirror. Large domed spires stretched towards the "
    +"starlit sky like talons for hundreds of feet and partly "
    +"obscures your view in every direction, except to the north, "
    +"where you see a great silent lake at some distance, reflecting "
    +"the light of twin suns setting in the horizon. At the southern "
    +"horizon, you see a pale moon. Far down "
    +"of the edge of the plateau you see empty streets between the "
    +"towers and spires as if the city was long since abandoned. "
    +"Above you, remnants of a shredded star is spiralling into "
    +"a large central black star. On the south edge of the plateaau, "
    +"you see the yellow sign engraved into the surface.\n");
      
    add_item(({"plateau", "black plateau", "circular plateau", 
    "ground", "floor"}),
    "This plateau is obviously the top of a black tower, judging "
    +"by the distance down to the streets, which is about several "
    +"hundred feet. The surface resembles some kind of onyx, polished "
    +"to perfection, mirroring the sky in minute detail. It measures "
    +"about thirty feet in diameter. On the south edge, you see "
    +"the yellow sign engraved into the surface.\n");
    
    add_item(({"tower", "black tower"}),
    "Judging by the height from the streets and the form of the "
    +"plateau, you believe you are on top of some tower made of "
    +"an onyx-like material. There are no obvious entrances or "
    +"exits down from here though.\n");
    
    add_item(({"star", "stars", "sky", "starlight"}),
    "The concentration of stars in the sky and prominent starclusters "
    +"are so dense that even the light of the setting twin sun is "
    +"weak in comparison, giving the scenery a surreal dreamlike "
    +"appearance. Several black stars in the sky projects a "
    +"surreal dreadful appearance, only overshadowed by a "
    +"large central one that looks like circular all-consuming "
    +"maw leading into a black void where there is no escape. Above "
    +"the southern horizon, you see a pale moon.\n");
    
    add_item(({"central star", "central black star"}),
    "Straight above and in the center of the starlit sky, a menacing void "
    +"is present. Smaller stars slowly orbit it, and some are even "
    +"shredded into long glowing trails, creating a spiral form around "
    +"the gaping maw of a central black star. Around the edges you can "
    +"witness a strange phenomenon; Light from the stars behind it "
    +"appears to bend on the edge, creating a strange silhouette. Staring "
    +"into the abyss tempts you to perform the ritual of the mind.\n");
    
    add_item(({"black stars", "black star"}),
    "Unlike the regular shining stars in the sky, these appear as "
    +"voids, or holes, giving a rather menacing appearance. The central "
    +"black star is extraordinary menacing...\n");
    
    add_item(({"towers", "spires", "city", "carcosa", "structure", "structures"}),
    "The city of Carcosa is prided with alien architecture, broad "
    +"smooth streets and large structures and towers that stretches "
    +"towards the starlit sky like countless golden-clad talons. "
    +"Unlike the black tower you are on top of, all other towers and "
    +"structures are metallic yellow in appearance with no visible "
    +"windows in them. No denizens can be seen anywhere.\n");
    
    add_item(({"denizens", "street", "road", "streets", "roads"}),
    "In the distance below, the streets seem to be broad and in perfect "
    +"condition. You don't see a living soul anywhere though, as if they "
    +"all has perished or vanished by unknown means.\n");
    
    add_item(({"lake", "silent lake"}),
    "To the north beyond the city borders, you see a great silent "
    +"lake that reflects the stars and the twin suns with "
    +"absolute perfection, mesmerizing you in the process due to the "
    +"dreamlike surreal appearance it creates.\n");
    
    add_item(({"moon", "pale moon"}),
    "Right above the southern horizon, you see a smooth pale moon "
    +"that reflects the light of the twin suns, giving it a slight "
    +"yellow tint. It appears the surface has no impact craters of "
    +"any sort, and it resembles a distant pristine marble.\n");
    
    add_item(({"sun", "suns", "twin suns"}),
    "Setting in the far north, two suns adjacent to each other are "
    +"peeking over the horizon in a yellowish glare that is reflected "
    +"in the silent lake. They do not illuminate the landscape much "
    +"compared to the starlight.\n");
    
    add_item(({"sign", "yellow sign"}),
    "The yellow sign resembles a a twisted weird triskelion, and you "
    +"feel the urge to touch it.\n");
    
    room_add_object(WARLOCK_OBJ_DIR + "onyx_chest");
    
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
            this_player()->catch_tell("\n\nYour patron, Your patron, the Great "
            +"Old One Hastur, the Yellow King, is offering you a pact "
            +"magic gift. May you 'choose' wisely.\n\n");
            
            return;
        }
        
        if (WARLOCK_MAPPINGS->query_desecration_power(this_player()->query_name()) 
        >= FEAR_UNLOCK && !WARLOCK_MAPPINGS->query_warspell_17(this_player()->query_name()))
        {
            this_player()->catch_tell("\n\nYour patron, the Great "
            +"Old One Hastur, the Yellow King, is offering you a pact "
            +"magic gift. May you 'choose' wisely.\n\n");
            
            return;
        }
        
        if (WARLOCK_MAPPINGS->query_desecration_power(this_player()->query_name()) 
        >= MAGICSHIELD_UNLOCK && !WARLOCK_MAPPINGS->query_warspell_18(this_player()->query_name()))
        {
            this_player()->catch_tell("\n\nYour patron, the Great "
            +"Old One Hastur, the Yellow King, is offering you a pact "
            +"magic gift. May you 'choose' wisely.\n\n");
            
            return;
        }    
        
        if (WARLOCK_MAPPINGS->query_desecration_power(this_player()->query_name()) 
        >= NUKE_UNLOCK && !WARLOCK_MAPPINGS->query_warspell_19(this_player()->query_name()))
        {
            this_player()->catch_tell("\n\nYour patron, Your patron, the Great "
            +"Old One Hastur, the Yellow King, is offering you a pact "
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
    
    //Testfunction - should be disabled.
    //add_action(do_testytes, "max");
}
